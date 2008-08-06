
using GLib;
using Gee;

namespace Gtk.Mate {
	// The Scanner returns these to indicate successful pattern matches in a line.
	public class Marker : Object {
		int from;  // the line offset where it begins
		int hint;  // ??
		Pattern p; // the pattern that was matched
		Oniguruma.Match match; // the matchdata of the successful match
	}

	// Scans lines for patterns. Handles caching of what has already been seen etc.
	public class Scanner : Object, Iterable<Marker> {
		public Scope current_scope {get; set;}
		public string line {get; set;}

		public Scanner(Scope s, string line) {
			this.current_scope = s;
			this.line = line;
		}

		public GLib.Type get_element_type () {
			return typeof (Marker);
		}
		
		public Gee.Iterator<Marker> iterator () {
			return new Iterator<Marker>(this);
		}

		public class Iterator<Marker> : Object, Gee.Iterator<Marker> {
			public Scanner scanner {get; set;}

			public Iterator(Scanner s) {
				this.scanner = s;
			}

			public bool next() {
				return true;
			}

			public Marker? get() {
				return new Gtk.Mate.Marker();
			}
		}
	}
}