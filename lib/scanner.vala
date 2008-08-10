
using GLib;
using Gee;

namespace Gtk.Mate {
	// The Scanner returns these to indicate successful pattern matches in a line.
	public class Marker : Object {
		public int     from;  // the line offset where it begins
		public int     hint;  // ??
		public Pattern pattern; // the pattern that was matched
		public Oniguruma.Match match; // the matchdata of the successful match
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
		// simply return the next cached marker
		public Marker? get_cached_marker() {
			Marker? m;
			foreach (var m1 in cached_markers) {
				if (m == null || m.from > m1.from) {
					m = m1;
				}
			}
			return m;
		}

		public Oniguruma.Match? scan_for_match(int from, Pattern p) {
			Oniguruma.Match match;
			if (p is SinglePattern) {
				match = ((SinglePattern) p).match.search(line, from, line_length);
			}
			else if (p is DoublePattern) {
				match = ((DoublePattern) p).begin.search(line, from, line_length);
			}
			return match;
		}

		public Marker? find_next_marker() {
			Marker m;
			if ((m = get_cached_marker()) != null) {
				stdout.printf("got cached marker\n");
				cached_markers.remove(m);
				return m;
			}
			stdout.printf("no cached marker\n");
			assert(cached_markers.size == 0);
			foreach (var p in ((DoublePattern) current_scope.pattern).patterns) {
				int position_now = position;
				Oniguruma.Match match;
				while ((match = scan_for_match(position_now, p)) != null) {
					stdout.printf("matched: %s\n", p.name);
					var nm = new Marker();
					nm.pattern = p;
					nm.match = match;
					nm.from = match.begin(0);
					cached_markers.add(nm);
					if (m == null || nm.from < m.from) {
						//stdout.printf("(current first)\n");
						m = nm;
					}
					position_now = match.end(0);
				}
			}
			if (m != null)
				cached_markers.remove(m);
			return m;
		}

		// called when the current_scope property is set.
		private void updated_current_scope() {
			// clear markers cached for this scope: 
			// (optimization potential? keep them for each scope in a hashmap)
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