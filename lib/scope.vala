
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

		public string begin_match_string;
		public string end_match_string;

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

		public bool surface_identical_to_modulo_ending(Scope other) {
			// stdout.printf("%s == %s and %s == %s and %s == %s and %s == %s and %s == %s",
			// 			  name, other.name, pattern.name, other.pattern.name, start_loc().to_s(),
			// 			  other.start_loc().to_s(), inner_start_loc().to_s(), other.inner_start_loc().to_s(),
			// 			  begin_match_string, other.begin_match_string);
			if (name == other.name &&
				pattern == other.pattern &&
				TextLoc.equal(start_loc(), other.start_loc()) &&
				TextLoc.equal(inner_start_loc(), other.inner_start_loc()) &&
				begin_match_string == other.begin_match_string) {
				return true;
			}
			return false;
		}

		public bool surface_identical_to(Scope other) {
			if (surface_identical_to_modulo_ending(other) &&
				TextLoc.equal(end_loc(), other.end_loc()) &&
				TextLoc.equal(inner_end_loc(), other.inner_end_loc()) &&
				begin_match_string == other.begin_match_string) {
				return true;
			}
			return false;
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
						var next_scope = children.get(iter); // .next());
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

		public Scope? first_child_after(TextLoc loc) {
			// stdout.printf("\"%s\".first_child_after(%d, %d)\n", name, loc.line, loc.line_offset);
			if (children.get_length() == 0)
				return null;
			
			// OPTIMIZE: should use g_sequence_search
			var iter = children.get_begin_iter();
			while (!iter.is_end()) {
				var child = children.get(iter);
				if (TextLoc.gte(child.start_loc(), loc))
					return child;
				iter = iter.next();
			}
			return null;
		}

		public bool contains_loc(TextLoc loc) {
			if (TextLoc.lte(start_loc(), loc) && TextLoc.gt(end_loc(), loc))
				return true;
			else 
				return false;
		}

		public bool overlaps_with(Scope other) {
			// sd1    +---
			// sd2  +---
			if (start_iter().compare(other.start_iter()) >= 0) {
				if (start_iter().compare(other.end_iter()) < 0) {
					return true;
				}
				return false;
			}

			// sd1 +---
			// sd2   +---
			if (end_iter().compare(other.start_iter()) > 0) {
				return true;
			}
			return false;
		}

		public void add_child(Scope s) {
			children.insert_sorted(s, (CompareDataFunc) Scope.compare_by_loc);
		}

		public void delete_child(Scope s) {
			var iter = children.search(s, (CompareDataFunc) Scope.compare_by_loc);
			// The gsequence docs don't say whether iter will now be pointing to
			// the equal element, so we have to look on the left and on the right.
			if (!iter.is_begin()) {
				var prev_scope = children.get(iter.prev());
				if (prev_scope == s) {
					// stdout.printf("leftremove\n");
					children.remove(iter.prev());
					return;
				}
			}
			if (!iter.is_end()) {
				var next_scope = children.get(iter);
				if (next_scope == s) {
 					// stdout.printf("rightremove\n");
					children.remove(iter);
					return;
				}
			}
		}
		
		public ArrayList<Scope> delete_any_on_line_not_in(int line_ix, ArrayList<Scope> scopes) {
//			var start_scope = scope_at(line_ix, -1);
			var removed_scopes = new ArrayList<Scope>();
			var iter = children.get_begin_iter();
			bool removed;
			while (!iter.is_end()) {
				removed = false;
				var child = children.get(iter);
				if (child.start_line() > line_ix) {
					return removed_scopes;
				}
				if (child.start_line() == line_ix) {
					if (!scopes.contains(child)) {
						removed_scopes.add(child);
						iter = iter.next();
						children.remove(iter.prev());
						removed = true;
					}
				}
				if (!removed) {
					iter = iter.next();
				}
			}
			return removed_scopes;
		}

		public void clear_after(int line_ix, int line_offset) {
			var loc = TextLoc.make(line_ix, line_offset);
			var s = new Scope(this.buffer, "");
			s.dummy_start_loc = loc;
			s.dummy_end_loc = loc;

			var iter = children.search(s, (CompareDataFunc) Scope.compare_by_loc);
			var prev_iter = iter.prev();
			if (!prev_iter.is_end()) {
				var prev_child = children.get(iter.prev());
				if (TextLoc.gt(prev_child.end_loc(), loc)) {
					prev_child.clear_after(line_ix, line_offset);
				}
			}
			var end_iter = children.get_end_iter();
			children.remove_range(iter, end_iter);
		}

		public string pretty(int indent) {
			pretty_string = new StringBuilder("");
			this.indent = indent;
			for (int i = 0; i < this.indent; i++)
				pretty_string.append("  ");
			if (is_capture)
				pretty_string.append("c");
			else
				pretty_string.append("+");
			pretty_string.append(" " + name);
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

		public TextIter start_iter() {
			return buffer.iter_from_mark(start_mark);
		}

		public TextIter inner_start_iter() {
			return buffer.iter_from_mark(inner_start_mark);
		}

		public TextIter inner_end_iter() {
			if (inner_end_mark != null)
				return buffer.iter_from_mark(inner_end_mark);
			else
				return end_iter();
		}

		public TextIter end_iter() {
			if (end_mark != null)
				return buffer.iter_from_mark(end_mark);
			else
				return buffer.iter_(buffer.get_char_count());
		}

		public int start_offset() {
			return buffer.iter_from_mark(start_mark).get_offset();
		}

		public int inner_start_offset() {
			return buffer.iter_from_mark(inner_start_mark).get_offset();
		}

		public int inner_end_offset() {
			if (inner_end_mark != null)
				return buffer.iter_from_mark(inner_end_mark).get_offset();
			else
				return int.MAX;
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

		public int inner_start_line() {
			return buffer.iter_from_mark(inner_start_mark).get_line();
		}

		public int inner_end_line() {
			if (inner_end_mark != null) 
				return buffer.iter_from_mark(inner_end_mark).get_line();
			else
				return int.MAX;
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

		public int inner_start_line_offset() {
			return buffer.iter_from_mark(inner_start_mark).get_line_offset();
		}

		public int inner_end_line_offset() {
			if (inner_end_mark != null) 
				return buffer.iter_from_mark(inner_end_mark).get_line_offset();
			else
				return int.MAX;
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

		public TextLoc inner_start_loc() {
			if (inner_start_mark != null) {
				return TextLoc.make(inner_start_line(), inner_start_line_offset());
			}
			else {
				return start_loc();
			}
		}

		public TextLoc inner_end_loc() {
			if (inner_end_mark != null) {
				return TextLoc.make(inner_end_line(), inner_end_line_offset());
			}
			else {
				return end_loc();
			}
		}

		public TextLoc end_loc() {
			if (dummy_end_loc != null)
				return dummy_end_loc;
			else
				return TextLoc.make(end_line(), end_line_offset());
		}

		public Scope root() {
			if (parent == null)
				return this;
			else
				return parent.root();
		}
	}
}