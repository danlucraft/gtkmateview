
using GLib;
using Gee;

namespace Gtk.Mate {
	// The Scanner returns these to indicate successful pattern matches in a line.
	public class Marker : Object {
		public int     from;  // the line offset where it begins
		public int     hint;  // ??
		public bool    is_close_scope; // whether this represents a closing of the current scope
		public Pattern pattern;        // the pattern that was matched
		public Onig.Match match;  // the matchdata of the successful match
	}

	// Scans lines for patterns. Handles caching of what has already been seen etc.
	public class Scanner : Object, Iterable<Marker> {
		private Scope _current_scope;
		public Scope  current_scope {
			get { return _current_scope; }
			set { 
				_current_scope = value;
				updated_current_scope();
			}
		}
		public string line {get; set;}
		public int    line_length {get; set;}
		public int    position;
		public ArrayList<Marker> cached_markers;

		public Scanner(Scope s, string line, int line_length) {
			this.current_scope = s;
			this.line = line;
			this.line_length = line_length;
		}

		construct {
			position = 0;
			cached_markers = new ArrayList<Marker>();
		}

		public GLib.Type get_element_type () {
			return typeof (Marker);
		}
		
		public Gee.Iterator<Marker> iterator () {
			return new Iterator<Marker>(this);
		}
		
		// if we have already scanned this line for this scope then
		// simply return the next cached marker (choosing the longest
		// match in case of a tie).
		public Marker? get_cached_marker() {
			Marker? m = null;
			int best_length = 0;
			int new_length;
			foreach (var m1 in cached_markers) {
				new_length = m1.match.end(0) - m1.from;
				if (m == null || 
					m1.from < m.from || 
					(m1.from == m.from && new_length > best_length) ||
					(m1.from == m.from && new_length == best_length && m1.is_close_scope)
					) {
					m = m1;
					best_length = new_length;
				}
			}
			return m;
		}
		
		// if we have gone beyond the marker, toss it out.
		public void remove_preceding_cached_markers(Marker m) {
			int ix = 0;
			int len = cached_markers.size;
			//stdout.printf("num cached: %d\n", len);
			for(int i = 0; i < len; i++, ix++) {
				if (cached_markers.get(ix).from < m.match.end(0)) {
					cached_markers.remove_at(ix);
					ix--;
				}
			}
			//stdout.printf("num cached after removals: %d\n", cached_markers.size);
		}
		
		public Onig.Match? scan_for_match(int from, Pattern p) {
			Onig.Match match = null;
			if (p is SinglePattern) {
				var sp = (SinglePattern) p;
				match = sp.match.search(line, from, line_length);
			}
			else if (p is DoublePattern) {
				match = ((DoublePattern) p).begin.search(line, from, line_length);
			}
			return match;
		}

		public Marker? find_next_marker() {
			// stdout.printf("find_next_marker (current_scope is %s)\n", current_scope.name);
			// stdout.printf("scanning: '%s' from %d to %d\n", line, position, line_length);
			Marker m;
			int best_length = 0;
			int new_length;
			bool is_close_match = false;
			if ((m = get_cached_marker()) != null) {
				//stdout.printf("got cached marker\n");
				cached_markers.remove(m);
				remove_preceding_cached_markers(m);
				return m;
			}
			//stdout.printf("no cached marker\n");
			assert(cached_markers.size == 0);
			var closing_regex = current_scope.closing_regex;
			if (closing_regex != null) {
				var match = closing_regex.search(line, position, line_length);
				if (match != null) {
					// stdout.printf("closing match: %s (%d-%d)\n", current_scope.name, match.begin(0), match.end(0));
					var nm = new Marker();
					nm.pattern = current_scope.pattern;
					nm.match = match;
					nm.from = match.begin(0);
					nm.is_close_scope = true;
					cached_markers.add(nm);
					m = nm;
					best_length = nm.match.end(0) - nm.from;
					is_close_match = true;
				}
			}
			foreach (var p in ((DoublePattern) current_scope.pattern).patterns) {
				if (p.disabled)
					continue;
				int position_now = position;
				int position_prev = position-1;
				Onig.Match match;
				while ((match = scan_for_match(position_now, p)) != null &&
					   position_now != position_prev // some regex's have zero width (meta.selector.css)
					) {
					position_prev = position_now;
					// stdout.printf("matched: %s (%d-%d)\n", p.name, match.begin(0), match.end(0));
					var nm = new Marker();
					nm.pattern = p;
					nm.match = match;
					nm.from = match.begin(0);
					nm.is_close_scope = false;
					cached_markers.add(nm);
					new_length = nm.match.end(0) - nm.from;
					if (m == null || nm.from < m.from || new_length == 0 || (nm.from == m.from && new_length > best_length && best_length != 0 && !is_close_match)) {
						m = nm;
						best_length = new_length;
					}
					position_now = match.end(0);
					// stdout.printf("  new position: %d\n", position_now);
				}
			}
			if (m != null) {
				cached_markers.remove(m);
				remove_preceding_cached_markers(m);
			}
			return m;
		}

		// called when the current_scope property is set.
		private void updated_current_scope() {
			// clear markers cached for this scope: 
			// (optimization potential: keep them for each scope in a hashmap)
			// (optimization potential: be aware of when a subscope can contain
			//  all the parents scopes, so we don't need to clear.)
			cached_markers.clear();
		}

		public class Iterator<Marker> : Object, Gee.Iterator<Marker> {
			public Scanner scanner {get; construct set;}
			public Marker? next_marker;

			construct {
			}

			public Iterator(Scanner s) {
				this.scanner = s;
			}

			public bool next() {
				next_marker = scanner.find_next_marker();
				return (next_marker != null);
			}

			public Marker? get() {
				return next_marker;
			}
		}
	}
}
