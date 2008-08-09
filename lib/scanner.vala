
using GLib;
using Gee;

namespace Gtk.Mate {
	// The Scanner returns these to indicate successful pattern matches in a line.
	public class Marker : Object {
		public int from;  // the line offset where it begins
		public int hint;  // ??
		public Pattern pattern; // the pattern that was matched
		public Oniguruma.Match match; // the matchdata of the successful match
	}

	// Scans lines for patterns. Handles caching of what has already been seen etc.
	public class Scanner : Object, Iterable<Marker> {
		public Scope current_scope {get; set;}
		public string line {get; set;}
		public int line_length {get; set;}
		public int position;

		public Scanner(Scope s, string line, int line_length) {
			this.current_scope = s;
			this.line = line;
			this.line_length = line_length;
		}

		construct {
			position = 0;
		}

		public GLib.Type get_element_type () {
			return typeof (Marker);
		}
		
		public Gee.Iterator<Marker> iterator () {
			return new Iterator<Marker>(this);
		}
		
		public Marker? find_next_marker() {
			Marker m;
			foreach (var p in ((DoublePattern) current_scope.pattern).patterns) {
				Oniguruma.Match match;
				if (p is SinglePattern) {
					match = ((SinglePattern) p).match.search(line, position, line_length);
					if (match != null && (m == null || match.begin(0) < m.from)) {
						m = new Marker();
						m.pattern = p;
						m.match = match;
						m.from = match.begin(0);
					}
				}
				else if (p is DoublePattern) {
					match = ((DoublePattern) p).begin.search(line, position, line_length);
					if (match != null && (m == null || match.begin(0) < m.from)) {
						m = new Marker();
						m.pattern = p;
						m.match = match;
						m.from = match.begin(0);
					}
				}
			}
			return m;
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