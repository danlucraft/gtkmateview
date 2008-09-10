
using Gee;
using GLib;

namespace Gtk.Mate {
	public class Scope : Object {
		public Pattern pattern;
		public string? name {get; set;}
		public Mate.Buffer buffer {get; set;}

		public Onig.Match open_match;
		public Onig.Match close_match;
		public Onig.Rx closing_regex;

		public TextMark start_mark;
		public TextMark inner_start_mark;
		public TextMark inner_end_mark;
		public TextMark end_mark;
		public TextTag tag;
		public TextTag inner_tag;
		public bool is_open;

		public string bg_colour;
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

		public bool is_coloured {get; set;}

		// public static int id_count = 0;
		// public int id;

		public Scope(Mate.Buffer buf, string? name) {
			this.name = name;
			this.buffer = buf;
			this.is_coloured = false;
		}

		public bool is_root() {
			if (parent == null)
				return true;
			return false;
		}

		// compare two Scope's. Returns 1 if a is later than b,
		// -1 if a is before b and 0 if b is overlapping with a
		public static int compare(Scope a, Scope b, void* data) {
			return a.start_iter().compare(b.start_iter());
		}

		public static int compare_by_loc(Scope a, Scope b, void* data) {
			var a_start = a.start_loc();
			var b_start = b.start_loc();
			if (TextLoc.lt(a_start, b_start)) {
				return -1;
			}
			else if (TextLoc.equal(a_start, b_start)) {
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
			
			var s = new Scope(this.buffer, "");
			s.dummy_start_loc = loc;
			s.dummy_end_loc = loc;
			var iter = children.search(s, (CompareDataFunc) Scope.compare_by_loc);
			if (!iter.is_end())
				return children.get(iter);
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
			children.insert_sorted(s, (CompareDataFunc) Scope.compare);
		}

		public void delete_child(Scope s) {
			var iter = children.search(s, (CompareDataFunc) Scope.compare);
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
//			var iter = children.get_begin_iter();
			bool removed;
			var s = new Scope(this.buffer, "");
			var loc = TextLoc.make(line_ix, -1);
			s.dummy_start_loc = loc;
			s.dummy_end_loc = loc;
			var iter = children.search(s, (CompareDataFunc) Scope.compare_by_loc);
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
				var s_iter = start_iter();
				return TextLoc.make(s_iter.get_line(), s_iter.get_line_offset());
			}
		}

		public TextLoc inner_start_loc() {
			if (inner_start_mark != null) {
				var is_iter = inner_start_iter();
				return TextLoc.make(is_iter.get_line(), is_iter.get_line_offset());
			}
			else {
				return start_loc();
			}
		}

		public TextLoc inner_end_loc() {
			if (inner_end_mark != null) {
				var ie_iter = inner_end_iter();
				return TextLoc.make(ie_iter.get_line(), ie_iter.get_line_offset());
			}
			else {
				return end_loc();
			}
		}

		public TextLoc end_loc() {
			if (dummy_end_loc != null) {
				return dummy_end_loc;
			}
			else {
				var e_iter = end_iter();
				return TextLoc.make(e_iter.get_line(), e_iter.get_line_offset());
			}
		}

		public Scope root() {
			if (parent == null)
				return this;
			else
				return parent.root();
		}
		
		public int priority() {
			if (parent == null)
				return 1;
			else
				return parent.priority() + 1;
		}

		public string hierarchy_names(bool inner) {
			string self_name;
			// stdout.printf("'%s'.hierarchy_names(%s)\n", name, inner ? "true" : "false");
			if (pattern is DoublePattern &&
				((DoublePattern) pattern).content_name != null &&
				inner) {
				self_name = name + " " + ((DoublePattern) pattern).content_name;
			}
			else {
				self_name = name;
			}
			if (parent != null) {
				bool next_inner;
				if (is_capture)
					next_inner = false;
				else
					next_inner = true;
				return parent.hierarchy_names(next_inner) + " " + self_name;
			}
			else {
				return self_name;
			}
		}

		// public int scope_id() {
		// 	if (id == null) {
		// 		Scope.id_count++;
		// 		id = Scope.id_count;
		// 	}
		// 	return id;
		// }

		public string? nearest_background_colour() {
			if (bg_colour == null) {
				if (parent != null) {
					return parent.nearest_background_colour();
				}
				return null;
			}
			else {
				return bg_colour;
			}
			
		}
	}
}