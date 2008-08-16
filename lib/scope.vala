
using Gee;
using GLib;

namespace Gtk.Mate {
	public class Scope : Object {
		public Pattern pattern;
		public string name {get; set;}
		public Mate.Buffer buffer {get; set;}

		public Oniguruma.Match open_match;
		public Oniguruma.Match close_match;
		public Oniguruma.Regex closing_regex;

		public TextMark start_mark;
		public TextMark inner_start_mark;
		public TextMark inner_end_mark;
		public TextMark end_mark;
		public TextTag tag;
		public TextTag inner_tag;
		public bool is_open;

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

		public Scope(Mate.Buffer buf, string name) {
			this.name = name;
			this.buffer = buf;
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
			pretty_string.append("+ " + name + " (");
			if (start_mark == null) {
				pretty_string.append("inf");
			}
			else {
				pretty_string.append("%d,%d".printf(buffer.iter_from_mark(start_mark).get_line(), 
													 buffer.iter_from_mark(start_mark).get_line_offset()));
			}
			pretty_string.append(")-(");
			if (end_mark == null) {
				pretty_string.append("inf");
			}
			else {
				pretty_string.append("%d,%d".printf(buffer.iter_from_mark(end_mark).get_line(), 
													 buffer.iter_from_mark(end_mark).get_line_offset()));
			}
			pretty_string.append(")");
			pretty_string.append((is_open ? " open" : " closed"));
			pretty_string.append("\n");

			this.indent += 1;
			GLib.SequenceIter iter = children.get_begin_iter();
			while (!iter.is_end()) {
				pretty_string.append(children.get(iter).pretty(this.indent));
				iter = iter.next();
			} 
			this.indent -= 1;
			return pretty_string.str;
		}

		public void start_mark_set(int line, int line_offset, bool has_left_gravity) {
			start_mark = buffer.create_mark(null, buffer.iter_at_line_offset(line, line_offset), has_left_gravity);
		}

		public void inner_start_mark_set(int line, int line_offset, bool has_left_gravity) {
			inner_start_mark = buffer.create_mark(null, buffer.iter_at_line_offset(line, line_offset), has_left_gravity);
		}

		public void inner_end_mark_set(int line, int line_offset, bool has_left_gravity) {
			inner_end_mark = buffer.create_mark(null, buffer.iter_at_line_offset(line, line_offset), has_left_gravity);
		}

		public void end_mark_set(int line, int line_offset, bool has_left_gravity) {
			end_mark = buffer.create_mark(null, buffer.iter_at_line_offset(line, line_offset), has_left_gravity);
		}

		public int start_offset() {
			return buffer.iter_from_mark(start_mark).get_offset();
		}

		public int end_offset() {
			if (end_mark != null)
				return buffer.iter_from_mark(end_mark).get_offset();
			else
				return int.MAX;
		}
	}
}