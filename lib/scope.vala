
using Gee;
using GLib;

namespace Gtk.Mate {
	public class Scope : Object {
		public Pattern pattern;
		public string? name {get; set;}
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
		
		// these are for when we want to compare scopes without
		// having to create TextMarks
		public TextLoc dummy_start_loc;
		public TextLoc dummy_end_loc;

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

		public Scope(Mate.Buffer buf, string? name) {
			this.name = name;
			this.buffer = buf;
		}

		public bool is_root() {
			if (parent == null)
				return true;
			return false;
		}

		// compare two Scope's. Returns 1 if a is later than b,
		// -1 if a is before b and 0 if b is overlapping with a
		public static int compare(Scope a, Scope b, void* data) {
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
				return 1;
			else if (a_start.get_line() < b_start.get_line())
				return -1;
			else if (a_start.get_line() == b_start.get_line()) {
				if (a_start.get_line_offset() > b_start.get_line_offset())
					return 1;
				else if (a_start.get_line_offset() < b_start.get_line_offset())
					return -1;
			}
			return 0;
		}

		public static int compare_by_loc(Scope a, Scope b, void* data) {
			if (TextLoc.lt(a.start_loc(), b.start_loc())) {
				return -1;
			}
			else if (TextLoc.equal(a.start_loc(), b.start_loc())) {
				return 0;
			}
			else {
				return 1;
			}
		}

		public Scope? scope_at(int line, int line_offset) {
			var loc = TextLoc.make(line, line_offset);
			TextLoc? start = start_loc();
			if (TextLoc.lte(start, loc) || parent == null) {
				if (TextLoc.gte(end_loc(), loc)) {
					if (children.get_length() == 0) {
						return this;
					}
					var s = new Scope(this.buffer, "");
					s.dummy_start_loc = loc;
					s.dummy_end_loc = loc;
					var iter = children.search(s, (CompareDataFunc) Scope.compare_by_loc);
					if (!iter.is_begin()) {
						var prev_scope = children.get(iter.prev());
						if (prev_scope.contains_loc(loc)) {
							return prev_scope.scope_at(line, line_offset);
						}
					}
					if (!iter.is_end()) {
						var next_scope = children.get(iter.next());
						if (next_scope.contains_loc(loc)) {
							return next_scope.scope_at(line, line_offset);
						}
					}
					return this;
				}
				else {
					return null;
				}
			}
			else {
				return null;
			}
		}

		public bool contains_loc(TextLoc loc) {
			if (TextLoc.lte(start_loc(), loc) && TextLoc.gt(end_loc(), loc))
				return true;
			else 
				return false;
		}

		public string pretty(int indent) {
			pretty_string = new StringBuilder("");
			this.indent = indent;
			for (int i = 0; i < this.indent; i++)
				pretty_string.append("  ");
			pretty_string.append("+ " + name);
			if (pattern is DoublePattern && ((DoublePattern) pattern).content_name != null) 
				pretty_string.append(" " + ((DoublePattern) pattern).content_name);
			pretty_string.append(" (");
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

		public int start_line() {
			return buffer.iter_from_mark(start_mark).get_line();
		}

		public int end_line() {
			if (end_mark != null) 
				return buffer.iter_from_mark(end_mark).get_line();
			else
				return int.MAX;
		}

		public int start_line_offset() {
			return buffer.iter_from_mark(start_mark).get_line_offset();
		}

		public int end_line_offset() {
			if (end_mark != null) 
				return buffer.iter_from_mark(end_mark).get_line_offset();
			else
				return int.MAX;
		}

		public TextLoc start_loc() {
			if (dummy_start_loc != null) {
				return dummy_start_loc;
			}
			else {
				return TextLoc.make(start_line(), start_line_offset());
			}
		}

		public TextLoc end_loc() {
			if (dummy_end_loc != null)
				return dummy_end_loc;
			else
				return TextLoc.make(end_line(), end_line_offset());
		}
	}
}