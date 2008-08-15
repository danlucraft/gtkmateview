
using Gee;
using GLib;

namespace Gtk.Mate {
	public class Scope : Object {
		public Pattern pattern;
		public string name {get; set;}

		public Oniguruma.Match open_match;
		public Oniguruma.Match close_match;
		public Oniguruma.Regex closing_regex;

		public SourceMark start_mark;
		public SourceMark inner_start_mark;
		public SourceMark inner_end_mark;
		public SourceMark end_mark;
		public TextTag tag;
		public TextTag inner_tag;
		// public bool is_open;

		public string bg_color;
		public bool is_capture;

		private Sequence<Scope> _children;
		public Sequence<Scope> children {
			get { 
				if (_children == null)
					_children = new Sequence<Scope>(null);
				return _children;
			}
		}
		public Scope parent;

		public StringBuilder pretty_string;
		public int indent;

		public Scope(string name) {
			this.name = name;
		}

		public bool is_root() {
			if (parent == null)
				return true;
			return false;
		}

		// compare two Scope's. Returns 1 if b is later than a,
		// -1 if b is before a and 0 if b is overlapping with a
		public static int compare(Scope a, Scope b) {
			TextIter a_start, b_start;
			if (a.start_mark == null) {
				if (b.start_mark == null)
					return 0;
				else 
					return 1;
			}
			else if (b.start_mark == null)
				return -1;
		    var buf = a.start_mark.get_buffer();
			buf.get_iter_at_mark(out a_start, a.start_mark);
			buf.get_iter_at_mark(out b_start, b.start_mark);
			if (a_start.get_line() > b_start.get_line())
				return -1;
			else if (a_start.get_line() < b_start.get_line())
				return 1;
			else if (a_start.get_line() == b_start.get_line()) {
				if (a_start.get_line_offset() > b_start.get_line_offset())
					return -1;
				else if (a_start.get_line_offset() < b_start.get_line_offset())
					return 1;
			}
			return 0;
		}

		public string pretty(int indent) {
			pretty_string = new StringBuilder("");
			this.indent = indent;
			for (int i = 0; i < this.indent; i++)
				pretty_string.append("  ");
			pretty_string.append(name+" (");
			if (start_mark == null)
				pretty_string.append("inf");
			pretty_string.append(")-(");
			if (end_mark == null)
				pretty_string.append("inf");
			pretty_string.append(")\n");
			this.indent += 1;
			if (children != null)
				children.foreach((Func) this.append_pretty);
			return pretty_string.str;
		}

		public void append_pretty(Scope child) {
			pretty_string.append(child.pretty(this.indent));
		}

		// public void set_start_mark(Mate.Buffer buf, int offset, bool has_left_gravity) {
		// 	// start_mark = (Gtk.SourceMark) buf.create_mark(null, buf.iter_(offset), has_left_gravity);
		// }

		// public void set_inner_start_mark(Mate.Buffer buf, int offset, bool has_left_gravity) {
		// 	// inner_start_mark = (Gtk.SourceMark) buf.create_mark(null, buf.iter_(offset), has_left_gravity);
		// }

		// public void set_inner_end_mark(Mate.Buffer buf, int offset, bool has_left_gravity) {
		// 	// inner_end_mark = (Gtk.SourceMark) buf.create_mark(null, buf.iter_(offset), has_left_gravity);
		// }

		// public void set_end_mark(Mate.Buffer buf, int offset, bool has_left_gravity) {
		// 	// end_mark = (Gtk.SourceMark) buf.create_mark(null, buf.iter_(offset), has_left_gravity);
		// }
	}
}