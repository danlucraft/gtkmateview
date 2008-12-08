
using Gee;
using GLib;

namespace Gtk.Mate {

	public class TextLoc : Object {
		public int line;
		public int line_offset;
		public static TextLoc make(int l, int lo) {
			var tl = new TextLoc();
			tl.line = l;
			tl.line_offset = lo;
			return tl;
		}

		public static bool equal(TextLoc t1, TextLoc t2) {
			return (t1.line == t2.line && t1.line_offset == t2.line_offset);
		}

		public static bool gt(TextLoc t1, TextLoc t2) {
			return ((t1.line > t2.line) || (t1.line >= t2.line && t1.line_offset > t2.line_offset));
		}

		public static bool lt(TextLoc t1, TextLoc t2) {
			return (!TextLoc.equal(t1, t2) && !TextLoc.gt(t1, t2));
		}
		
		public static bool gte(TextLoc t1, TextLoc t2) {
			return (!TextLoc.lt(t1, t2));
		}
		
		public static bool lte(TextLoc t1, TextLoc t2) {
			return (!TextLoc.gt(t1, t2));
		}
		
		public string to_s() {
			return "{%d,%d}".printf(line, line_offset);
		}
	}
	
	public class Parser : Object {
		public Grammar grammar {get; set;}
		public Colourer colourer {get; set;}
		public Mate.Buffer buffer {get; set;}
		public Mate.Scope root;
		public int deactivation_level;
		public TextTag dummy_tag;
		public TextTag dummy_tag2;
		public Sequence<TextTag> tags;
		public RangeSet changes;
		public int parsed_upto;
		public int last_visible_line;
		public bool always_parse_all;
		
		public int look_ahead {get; set;}
		
		public void make_root() {
			this.root = new Scope(this.buffer, this.grammar.scope_name);
			this.root.is_open = true;
			this.root.start_mark_set(0, 0, true);
			this.root.end_mark_set(buffer.end_iter().get_line(), buffer.end_iter().get_line_offset(), false);
			var dp = new DoublePattern();
			dp.name = this.grammar.name;
			dp.patterns = this.grammar.patterns;
			this.root.pattern = dp;
		}

		public void stop_parsing() {
			deactivation_level += 1;
		}
		
		public void start_parsing() {
			if (deactivation_level > 0)
				deactivation_level -= 1;
			if (deactivation_level == 0)
				process_changes();
		}

		public bool is_parsing() {
			return (deactivation_level == 0);
		}

		// Process all change ranges.
		private void process_changes() {
			int parsed_upto = -1;
			// stdout.printf("process_changes (last_visible_line: %d)\n", last_visible_line);
			foreach (RangeSet.Range range in changes) {
				if (range.b > parsed_upto && range.a <= last_visible_line + look_ahead) {
					int range_end = int.min(last_visible_line + look_ahead, range.b);
					parsed_upto = parse_range(range.a, range_end);
				}
			}
//			//stdout.printf("%s\n", root.pretty(0));
			changes.ranges.clear();
		}

		// Parse from from_line to *at least* to_line. Will parse
		// more if necessary. Returns the index of the last line
		// parsed.
		private int parse_range(int from_line, int to_line) {
			// stdout.printf("parse_range(%d, %d)\n", from_line, to_line);
			int line_ix = from_line;
			bool scope_changed = false;
			bool scope_ever_changed = false;
			int end_line = int.min(last_visible_line + 100, buffer.get_line_count() - 1);
			while (line_ix <= to_line || scope_ever_changed && line_ix <= end_line) {
				scope_changed = parse_line(line_ix++);
				if (scope_changed) {
					scope_ever_changed = true;
					// In the old scheme this wasn't necessary because 
					// the scope_at used a simple scan from the front. The GSequences
					// on the other hand can get confused if the later scopes
					// are inconsistent with earler ones. So we have to clear everything.
					// TODO: figure out a way to OPTIMIZE this again.
					root.clear_after(line_ix, -1);
					remove_colour_after(line_ix, 0);
				}
				//stdout.printf("parse_line returned: %s\n", scope_changed ? "true" : "false");
				//stdout.printf("pretty:\n%s\n", root.pretty(2));
			}
			//stdout.printf("parse_from:out\n");
			return to_line;
		}

		private void remove_colour_after(int line_ix, int line_offset) {
			GLib.SequenceIter iter = tags.get_begin_iter();
			var start_iter = buffer.iter_at_line_offset(line_ix, line_offset);
			var end_iter = buffer.end_iter();
			while (!iter.next().is_end()) {
				var t = tags.get(iter);
				this.buffer.remove_tag(t, start_iter, end_iter);
				iter = iter.next();
			}
		}
	
		// Parse line line_ix. Returns true if the ending
		// scope of the line has changed.
		private bool parse_line(int line_ix) {
			string? line = buffer.get_line(line_ix);
			int length = (int) line.length;//buffer.get_line_length(line_ix);
			stdout.printf("p%d, ", line_ix);
			// stdout.flush();
			var start_scope = this.root.scope_at(line_ix, 0);
			while (start_scope.pattern is SinglePattern || start_scope.is_capture)
			  start_scope = start_scope.parent;
			var end_scope1 = this.root.scope_at(line_ix, int.MAX);
			stdout.printf("start_scope is: %s\n", start_scope.name);
//			if (start_scope == null)
				//stdout.printf("pretty:\n%s\n", root.pretty(2));
			//stdout.printf("end_scope1: %s\n", end_scope1.name);
			var scanner = new Scanner(start_scope, line, length);
			var all_scopes = new ArrayList<Scope>();
			all_scopes.add(start_scope);
			var closed_scopes = new ArrayList<Scope>();
			var removed_scopes = new ArrayList<Scope>();
			all_scopes.add(start_scope);
			foreach (Marker m in scanner) {
				stdout.printf("foo\n");
				var expected_scope = get_expected_scope(scanner.current_scope, line_ix, scanner.position);
				// if (expected_scope != null)
				// 	stdout.printf("expected_scope: %s\n", expected_scope.name);
				// else
				// 	stdout.printf("no expected scope\n");
				// stdout.printf("  scope: %s\n", m.pattern.name);
				if (m.is_close_scope) {
					close_scope(scanner, expected_scope, line_ix, line, m, 
								all_scopes, closed_scopes, removed_scopes);
				}
				else if (m.pattern is DoublePattern) {
					open_scope(scanner, expected_scope, line_ix, line, length, m, 
							   all_scopes, closed_scopes, removed_scopes);
				}
				else {
					single_scope(scanner, expected_scope, line_ix, line, length, m, 
								 all_scopes, closed_scopes, removed_scopes);
				}
				scanner.position = m.match.end(0);
			}
			stdout.printf("bar\n");
			clear_line(line_ix, start_scope, all_scopes, closed_scopes, removed_scopes);
			var end_scope2 = this.root.scope_at(line_ix, int.MAX);
			//stdout.printf("end_scope2: %s\n", end_scope2.name);
			if (colourer != null) {
				//stdout.printf("before_uncolour_scopes\n");
				colourer.uncolour_scopes(removed_scopes);
				//stdout.printf("before_colour_line_with_scopes\n");
				colourer.colour_line_with_scopes(all_scopes);
				//stdout.printf("after_colour_line_with_scopes\n");
			}
			else {
				// stdout.printf("no colourer");
			}
			// stdout.printf("%s\n", this.root.pretty(0));
			return (end_scope1 != end_scope2);
		}
		
		public void clear_line(int line_ix, Scope start_scope, 
							   ArrayList<Scope> all_scopes, 
							   ArrayList<Scope> closed_scopes, 
							   ArrayList<Scope> removed_scopes) {
			// If we are reparsing, we might find that some scopes have disappeared,
			// delete them:
			var cs = start_scope;
			while (cs != null) {
				//stdout.printf("  removing_scopes from: %s\n", cs.name);
				var removed = cs.delete_any_on_line_not_in(line_ix, all_scopes);
				foreach (var rs in removed) {
					removed_scopes.add(rs);
				}
				cs = cs.parent;
			}
			// @removed_scopes += removed_scopes
			
			// any that we expected to close on this line that now don't?
			//  first build list of scopes that close on this line (including ones
			//  that did but haven't been removed yet).
			var scopes_that_closed_on_line = new ArrayList<Scope>();
			var ts = start_scope;
			while (ts.parent != null) {
				if (ts.end_line() == line_ix) {
					scopes_that_closed_on_line.add(ts);
				}
				ts = ts.parent;
			}
			foreach (var s in scopes_that_closed_on_line) {
				if (!closed_scopes.contains(s)) {
					if (s.is_capture) {
						s.parent.delete_child(s);
						removed_scopes.add(s);
						// @removed_scopes << s
					}
					else {
						if (colourer != null)
							colourer.uncolour_scope(s, false);
						s.inner_end_mark = null;
						s.end_mark = null;
						s.is_open = true;
					}
				}
			}
			
		}

		public Scope? get_expected_scope(Scope current_scope, int line, int line_offset) {
			// //stdout.printf("get_expected_scope(%s, %d, %d)\n", current_scope.name, line, line_offset);
			var expected_scope = current_scope.first_child_after(TextLoc.make(line, line_offset));
			// //stdout.printf("first_child_after: %s\n", expected_scope.name);
			assert(expected_scope != current_scope);
			if (expected_scope != null) {
				if (expected_scope.start_line() != line)
					expected_scope = null;
				while (expected_scope != null && expected_scope.is_capture) {
					expected_scope = expected_scope.parent;
				}
			}
			return expected_scope;
		}

		public void close_scope(Scanner scanner, Scope? expected_scope, 
								int line_ix, string line, Marker m,
								ArrayList<Scope> all_scopes,
								ArrayList<Scope> closed_scopes, 
								ArrayList<Scope> removed_scopes
			) {
			var end_match_string = line.substring(m.from, m.match.end(0)-m.from);
			if (scanner.current_scope.end_mark != null &&
				TextLoc.equal(scanner.current_scope.end_loc(), TextLoc.make(line_ix, m.match.end(0))) &&
				TextLoc.equal(scanner.current_scope.inner_end_loc(), TextLoc.make(line_ix, m.from)) &&
				scanner.current_scope.end_match_string == end_match_string) {
				// we have already parsed this line and this scope ends here

				// Re-add the captures from the end of the current scope to the 
				// tracking arrays
				var iter = scanner.current_scope.children.get_begin_iter();
				while (!iter.is_end()) {
					var child = scanner.current_scope.children.get(iter);
					if (child.is_capture && 
						child.start_line() == line_ix) {
						if (!closed_scopes.contains(child))
							closed_scopes.add(child);
						if (!all_scopes.contains(child))
							all_scopes.add(child);
					}
					iter = iter.next();
				}
				// stdout.printf("closing scope matches expected\n");
			}
			else {
				// stdout.printf("closing scope at %d\n", m.from);
				if (colourer != null) {
					colourer.uncolour_scope(scanner.current_scope, false);
				}
				scanner.current_scope.inner_end_mark_set(line_ix, m.from, true);
				scanner.current_scope.end_mark_set(line_ix, m.match.end(0), true);
				scanner.current_scope.is_open = false;
				scanner.current_scope.end_match_string = end_match_string;
				//stdout.printf("end_match_string: '%s'\n", scanner.current_scope.end_match_string);
				handle_captures(line_ix, line, scanner.current_scope, m, all_scopes, closed_scopes);
				if (expected_scope != null) {
					scanner.current_scope.delete_child(expected_scope);
					removed_scopes.add(expected_scope);
					// @removed_scopes << expected_scope
				}
			}
			removed_scopes.add(scanner.current_scope); // so it gets uncoloured
			closed_scopes.add(scanner.current_scope);
			scanner.current_scope = scanner.current_scope.parent;
			all_scopes.add(scanner.current_scope);
		}

		public void open_scope(Scanner scanner, Scope? expected_scope, 
							   int line_ix, string line, int length, Marker m,
							   ArrayList<Scope> all_scopes,
							   ArrayList<Scope> closed_scopes, 
							   ArrayList<Scope> removed_scopes
			) {
			//stdout.printf("[opening with %d patterns], \n", ((DoublePattern) m.pattern).patterns.size);
			var s = new Scope(this.buffer, m.pattern.name);
			s.pattern = m.pattern;
			s.open_match = m.match;
			s.start_mark_set(line_ix, m.from, false);
			s.inner_start_mark_set(line_ix, int.min(m.match.end(0), length), true); // had right gravity in Ruby version. Important?
			s.begin_match_string = line.substring(m.from, m.match.end(0)-m.from);
			//stdout.printf("begin_match_string: '%s'\n", s.begin_match_string);
			var end_iter = buffer.end_iter();
			var end_line = end_iter.get_line();
			var end_line_offset = end_iter.get_line_offset();
			s.inner_end_mark_set(end_line, end_line_offset, false);
			s.end_mark_set(end_line, end_line_offset, false);
			s.is_open = true;
			s.is_capture = false;
			s.parent = scanner.current_scope;
			var new_scope = s;
			// is this a bug? captures aren't necessarily to be put into all_scopes yet surely?
			handle_captures(line_ix, line, s, m, all_scopes, closed_scopes);
			if (expected_scope != null) {
				// check mod ending scopes as the new one will not have a closing marker
				// but the expected one will:
				if (s.surface_identical_to_modulo_ending(expected_scope)) {
					//stdout.printf("surface_identical_mod_ending: keep expected\n");
					// don't need to do anything as we have already found this,
					// but let's keep the old scope since it will have children and what not.
					new_scope = expected_scope;
					var iter = expected_scope.children.get_begin_iter();
					while (!iter.is_end()) {
						closed_scopes.add(expected_scope.children.get(iter));
						iter = iter.next();
					}
					scanner.current_scope = expected_scope;
				}
				else {
					//stdout.printf("surface_NOT_identical_mod_ending: replace expected\n");
					if (s.overlaps_with(expected_scope)) {
						scanner.current_scope.delete_child(expected_scope);
						// removed_scopes << expected_scope
						removed_scopes.add(expected_scope);
					}
					scanner.current_scope.add_child(s);
					scanner.current_scope = s;
				}
			}
			else {
				scanner.current_scope.add_child(s);
				scanner.current_scope = s;
			}
			all_scopes.add(new_scope);
		}

		public void single_scope(Scanner scanner, Scope? expected_scope, 
								 int line_ix, string line, int length, Marker m,
								 ArrayList<Scope> all_scopes,
								 ArrayList<Scope> closed_scopes, 
								 ArrayList<Scope> removed_scopes
			) {
			var s = new Scope(this.buffer, m.pattern.name);
			s.pattern = m.pattern;
			s.open_match = m.match;
			s.start_mark_set(line_ix, m.from, false);
			if (m.match.end(0) == length && this.buffer.get_line_count() > line_ix+1) 
				s.end_mark_set(line_ix+1, 0, true);
			else
				s.end_mark_set(line_ix, int.min(m.match.end(0), length), true);
			s.is_open = false;
			s.is_capture = false;
			s.begin_match_string = line.substring(m.from, m.match.end(0)-m.from);
			//stdout.printf("_match_string: '%s'\n", s.begin_match_string);
			s.parent = scanner.current_scope;
			var new_scope = s;
			if (expected_scope != null) {
				if (s.surface_identical_to(expected_scope)) {
					new_scope = expected_scope;
					var iter = expected_scope.children.get_begin_iter();
					while (!iter.is_end()) {
						closed_scopes.add(expected_scope.children.get(iter));
						iter = iter.next();
					}
				}
				else {
					handle_captures(line_ix, line, s, m, all_scopes, closed_scopes);
					if (s.overlaps_with(expected_scope)) {
						scanner.current_scope.delete_child(expected_scope);
						// removed_scopes << expected_scope
						removed_scopes.add(expected_scope);
					}
					scanner.current_scope.add_child(s);
				}
			}
			else {
				handle_captures(line_ix, line, s, m, all_scopes, closed_scopes);
				scanner.current_scope.add_child(s);
			}
			all_scopes.add(new_scope);
			closed_scopes.add(new_scope);
		}

		// Opens scopes for captures AND creates closing regexp from
		// captures if necessary.
		public void handle_captures(int line_ix, string line, Scope scope, Marker m, ArrayList<Scope> all_scopes, ArrayList<Scope> closed_scopes) {
			make_closing_regex(line, scope, m);
			collect_child_captures(line_ix, scope, m, all_scopes, closed_scopes);
		}

		public Onig.Rx? make_closing_regex(string line, Scope scope, Marker m) {
			// new_end = pattern.end.gsub(/\\([0-9]+)/) do
			// 	md.captures.send(:[], $1.to_i-1)
			// end
			if (m.pattern is DoublePattern && !m.is_close_scope) {
				var dp = (DoublePattern) m.pattern;
				//stdout.printf("making closing regex: %s (%d)\n", dp.end_string, (int) dp.end_string.length);
				var rx = Onig.Rx.make1("\\\\(\\d+)");
				Onig.Match match;
				int pos = 0;
				var src = new StringBuilder("");
				bool found = false;
				while ((match = rx.search(dp.end_string, pos, (int) dp.end_string.length)) != null) {
					found = true;
					src.append(dp.end_string.substring(pos, match.begin(0)-pos));
					var numstr = dp.end_string.substring(match.begin(1), match.end(1)-match.begin(1));
					var num = numstr.to_int();
					//stdout.printf("capture found: %d\n", num);
					var capstr = line.substring(m.match.begin(num), m.match.end(num)-m.match.begin(num));
					src.append(capstr);
					pos = match.end(1);
				}
				if (found)
					src.append(dp.end_string.substring(pos, dp.end_string.length-pos));
				else
					src.append(dp.end_string);
				//stdout.printf("src: '%s'\n", src.str);
				scope.closing_regex = Onig.Rx.make1(src.str);
			}
			return null;
		}
		
		public void collect_child_captures(int line_ix, Scope scope, Marker m, 
										   ArrayList<Scope> all_scopes,
										   ArrayList<Scope> closed_scopes) {
			Scope s;
			HashMap<int, string> captures;
			if (m.pattern is SinglePattern) {
				captures = ((SinglePattern) m.pattern).captures;
			}
			else {
				if (m.is_close_scope) {
					captures = ((DoublePattern) m.pattern).end_captures;
				}
				else {
					captures = ((DoublePattern) m.pattern).begin_captures;
				}
				if (((DoublePattern) m.pattern).both_captures != null) {
					captures = ((DoublePattern) m.pattern).both_captures;
				}
			}
			var capture_scopes = new ArrayList<Scope>();
			// create capture scopes
			if (captures != null) {
				foreach (int cap in captures.get_keys()) {
					if (m.match.begin(cap) != -1) {
						s = new Scope(this.buffer, captures.get(cap));
						s.start_mark_set(line_ix, m.match.begin(cap), false);
						s.end_mark_set(line_ix, m.match.end(cap), true);
						s.is_open = false;
						s.is_capture = true;
						s.parent = scope;
						capture_scopes.add(s);
						all_scopes.add(s);
						closed_scopes.add(s);
					}
				}
			}
			// Now we arrange the capture scopes into a tree under the matched
			// scope. We do this by processing the captures in order of offset and 
			// length. For each capture, we check to see if it is a child of an already 
			// placed capture, and if so we add it as a child (we know that the latest 
			// such capture is the one to add it to by the ordering). If not we
			// add it as a child of the matched scope.
			int best_length = 0;
			int new_length;
			var placed_scopes = new ArrayList<Scope>();
			Scope parent_scope;
			while (capture_scopes.size > 0) {
				s = null;
				// find first and longest remaining scope (put it in 's')
				foreach (var cs in capture_scopes) {
					new_length = cs.end_offset() - cs.start_offset();
					if (s == null || (cs.start_offset() < s.start_offset() && new_length >= best_length)) {
						s = cs;
						best_length = new_length;
					}
				}
				// look for somewhere to put it from placed_scopes
				parent_scope = null;
				foreach (var ps in placed_scopes) {
					if (s.start_offset() >= ps.start_offset() && s.end_offset() <= ps.end_offset()) {
						parent_scope = ps;
					}
				}
				if (parent_scope != null) {
					parent_scope.children.append(s);
					s.parent = parent_scope;
				}
				else {
					scope.children.append(s);
				}
				placed_scopes.add(s);
				capture_scopes.remove(s);
			}
		}

		public void reset_table_priorities() {
			// stdout.printf("\nreset_table_priorities() for %d tags\n", buffer.get_tag_table().get_size());
			GLib.SequenceIter iter = tags.get_begin_iter();
			int i = 0;
			while (!iter.next().is_end()) {
				var t = tags.get(iter);
				t.set_priority(i);
				// stdout.printf("tag: '%s', pri: %d\n", t.name, i);
				i++;
				iter = iter.next();
			}
		}

		public void remove_tags() {
			GLib.SequenceIter iter = tags.get_begin_iter();
			var table = buffer.get_tag_table();
			while (!iter.is_end()) {
				table.remove(tags.get(iter));
				iter = iter.next();
			}
			tags.remove_range(tags.get_begin_iter(), tags.get_end_iter());
		}

		public void change_theme(Theme theme) {
			// stdout.printf("parser.change_theme(%s)\n", theme.name);
			colourer.uncolour_scope(root, true);
			colourer.theme = theme;
			remove_tags();
			recolour_children(root);
			// stdout.printf("parser.change_theme(%s):out\n", theme.name);
		}

		public void recolour_children(Scope scope) {
			GLib.SequenceIter iter = scope.children.get_begin_iter();
			while (!iter.is_end()) {
				var child = scope.children.get(iter);
				colourer.colour_scope(child, false, true);
				if (child.pattern is DoublePattern && ((DoublePattern) child.pattern).content_name != null)
					colourer.colour_scope(child, true, true);
				recolour_children(child);
				iter = iter.next();
			}
		}

		public void last_visible_line_changed(int new_last_visible_line) {
			this.last_visible_line = new_last_visible_line;
			// stdout.printf("last_visible_line: %d\n", last_visible_line);
			// stdout.printf("already_parsed_upto: %d\n", last_line_parsed());
			if (last_visible_line + look_ahead >= last_line_parsed()) {
				int end_range = int.min(buffer.get_line_count() - 1, last_visible_line + look_ahead);
				// stdout.printf("parse_range(%d, %d)\n", last_line_parsed(), end_range);
				parse_range(last_line_parsed(), end_range);
			}
		}

		public int last_line_parsed() {
			GLib.SequenceIter iter = root.children.get_end_iter();
			if (!iter.is_begin()) {
				iter = iter.prev();
				var child = root.children.get(iter);
				return child.end_line();
			}
			else {
				return 0;
			}
		}

		public void connect_buffer_signals() {
			buffer.insert_text += this.insert_text_handler;
			buffer.delete_range += this.delete_range_handler;
			// buffer.get_tag_table().tag_added += this.tag_added_handler;
			// remove when signal_connect_after works:
			Signal.connect_after(buffer, "insert_text", (GLib.Callback) Parser.static_insert_text_after_handler, null);
			Signal.connect_after(buffer, "delete_range", (GLib.Callback) Parser.static_delete_range_after_handler, null);
			// Signal.connect_after(buffer.get_tag_table(), "tag_added", 
			// 					 (GLib.Callback) Parser.static_tag_added_after_handler, null);
		}

		public void insert_text_handler(Buffer bf, TextIter pos, string text, int length) {
			////stdout.printf("insert_text(pos, \"%s\", %d)\n", text, length);
			var ss = text.split("\n");
			int num_lines = -1;
			foreach (var s in ss) num_lines++;
			////stdout.printf("add_change(%d, %d)\n", pos.get_line(), pos.get_line() + num_lines);
			changes.add(pos.get_line(), pos.get_line() + num_lines);
		}
		
		public void delete_range_handler(Buffer bf, TextIter pos, TextIter pos2) {
			////stdout.printf("delete_range(%d, %d)\n", pos.get_offset(), pos2.get_offset());
			changes.add(pos.get_line(), pos.get_line());
		}

		public void insert_text_after_handler(Buffer bf, TextIter pos, string text, int length) {
			if (is_parsing() && !changes.is_empty())
				process_changes();
		}

		public void delete_range_after_handler(Buffer bf, TextIter pos, TextIter pos2) {
			if (is_parsing() && !changes.is_empty())
				process_changes();
		}

		// These static methods are hack to get around Vala not supporting signal_connect_after_yet
		public static ArrayList<Parser> existing_parsers;

		public static void static_insert_text_after_handler(Buffer bf, TextIter pos, string text, int length) {
			foreach(var parser in existing_parsers) {
				parser.insert_text_after_handler(bf, pos, text, length);
			}
		}
		public static void static_delete_range_after_handler(Buffer bf, TextIter pos, TextIter pos2) {
			foreach(var parser in existing_parsers) {
				parser.delete_range_after_handler(bf, pos, pos2);
			}
		}

		public void added_tag(TextTag tag) {
			if (tag.name != null && tag.name.has_prefix("gmv(")) {
				this.tags.insert_sorted(tag, (CompareDataFunc) Parser.tag_compare);
			}
			this.reset_table_priorities();
		}

		public static int tag_compare(TextTag tag1, TextTag tag2, void* data) {
			int pri1 = tag1.name[4].digit_value();
			int pri2 = tag2.name[4].digit_value();
			if (pri1 > pri2) {
				return 1;
			}
			else if (pri2 > pri1) {
				return -1;
			}
			return 0;
		}

		public void close() {
			Parser.existing_parsers.remove(this);
		}
		
		public static Parser create(Grammar grammar, Mate.Buffer buffer) {
			grammar.init_for_use();

			var p = new Parser();
			// remove when signal_connect_after works:
			if (Parser.existing_parsers == null) 
				Parser.existing_parsers = new ArrayList<Parser>();
			Parser.existing_parsers.add(p);
			p.look_ahead = 100;
			p.last_visible_line = 0;
			p.grammar = grammar;
			p.buffer = buffer;
			p.tags = new Sequence<TextTag>(null);
			p.changes = new RangeSet();
			p.colourer = new Colourer(buffer);
			p.deactivation_level = 0;
			p.make_root();
			p.connect_buffer_signals();
			p.parsed_upto = 0;
			p.always_parse_all = false;
			return p;
		}
	}
}
