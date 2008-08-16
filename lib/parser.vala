
using Gee;
using GLib;

namespace Gtk.Mate {

	public struct TextLoc {
		public int line;
		public int line_offset;
		public static TextLoc make(int l, int lo) {
			var tl = TextLoc();
			tl.line = l;
			tl.line_offset = lo;
			return tl;
		}
	}
	
	public class Parser : Object {
		public Grammar grammar {get; set;}
		public Mate.Buffer buffer {get; set;}
		public Mate.Scope root;
		public RangeSet changes;
		public int deactivation_level;
		
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
			foreach (RangeSet.Range range in changes) {
				if (range.b > parsed_upto)
					parsed_upto = parse_range(range.a, range.b);
			}
			changes.ranges.clear();
		}

		// Parse from from_line to *at least* to_line. Will parse
		// more if necessary. Returns the index of the last line
		// parsed.
		private int parse_range(int from_line, int to_line) {
			//stdout.printf("parse_from(%d, %d)\n", from_line, to_line);
			int line_ix = from_line;
			bool scope_changed = false;
			while (line_ix <= to_line || scope_changed) {
				scope_changed = parse_line(line_ix++);
			}
			return to_line;
		}

		// Parse line line_ix. Returns whether or not the ending
		// scope of the line has changed.
		private bool parse_line(int line_ix) {
			string? line = buffer.get_line(line_ix);
			int length = buffer.get_line_length(line_ix);
			stdout.printf("parse line: %d (%d): '%s'\n", line_ix, length, line.substring(0, length));
			var scanner = new Scanner(this.root, line, length);
			int i = 0;
			Scope s;
			foreach (Marker m in scanner) {
				if (m.pattern is DoublePattern) {
//					stdout.printf("[opening with %d patterns], \n", ((DoublePattern) m.pattern).patterns.size);
					s = new Scope(this.buffer, m.pattern.name);
					s.pattern = m.pattern;
					s.open_match = m.match;
					s.start_mark_set(line_ix, m.from, false);
					s.inner_start_mark_set(line_ix, int.min(m.match.end(0), length), false);
					var end_iter = buffer.end_iter();
					var end_line = end_iter.get_line();
					var end_line_offset = end_iter.get_line_offset();
					s.inner_end_mark_set(end_line, end_line_offset, false);
					s.end_mark_set(end_line, end_line_offset, false);
					s.is_open = true;
					scanner.current_scope.children.append(s);
					scanner.current_scope = s;
				}
				else {
					s = new Scope(this.buffer, m.pattern.name);
					s.pattern = m.pattern;
					s.open_match = m.match;
					s.start_mark_set(line_ix, m.from, false);
					s.end_mark_set(line_ix, int.min(m.match.end(0), length), true);
					s.is_open = false;
					scanner.current_scope.children.append(s);
				}
				handle_captures(line_ix, s, m);
				stdout.printf("pretty: %s\n", s.pretty(0));
				scanner.position = m.match.end(0);
			}
			return false;
		}

		// Opens scopes for captures AND creates closing regexp from
		// captures if necessary.
		public void handle_captures(int line_ix, Scope scope, Marker m) {
			make_closing_regex(m);
			collect_child_captures(line_ix, scope, m);
		}

		public Oniguruma.Regex? make_closing_regex(Marker m) {
			// new_end = pattern.end.gsub(/\\([0-9]+)/) do
			// 	md.captures.send(:[], $1.to_i-1)
			// end			
			return null;
		}
		
		public void collect_child_captures(int line_ix, Scope scope, Marker m) {
			Scope s;
			HashMap<int, string> captures;
			if (m.pattern is SinglePattern) {
				captures = ((SinglePattern) m.pattern).captures;
			}
			else {
				captures = ((DoublePattern) m.pattern).begin_captures;
			}
			var capture_scopes = new ArrayList<Scope>();
			// create capture scopes
			foreach (int cap in captures.get_keys()) {
				if (m.match.begin(cap) != -1) {
					s = new Scope(this.buffer, captures.get(cap));
					s.start_mark_set(line_ix, m.match.begin(cap), false);
					s.end_mark_set(line_ix, m.match.end(cap), true);
					s.is_open = false;
					capture_scopes.add(s);
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
				}
				else {
					scope.children.append(s);
				}
				placed_scopes.add(s);
				capture_scopes.remove(s);
			}
		}

		public void connect_buffer_signals() {
			buffer.insert_text += this.insert_text_handler;
			buffer.delete_range += this.delete_range_handler;
			// remove when signal_connect_after works:
			Signal.connect_after(buffer, "insert_text", (GLib.Callback) Parser.static_insert_text_after_handler, null);
			Signal.connect_after(buffer, "delete_range", (GLib.Callback) Parser.static_delete_range_after_handler, null);
		}

		public void insert_text_handler(Buffer bf, TextIter pos, string text, int length) {
			//stdout.printf("insert_text(pos, \"%s\", %d)\n", text, length);
			var ss = text.split("\n");
			int num_lines = -1;
			foreach (var s in ss) num_lines++;
			//stdout.printf("add_change(%d, %d)\n", pos.get_line(), pos.get_line() + num_lines);
			changes.add(pos.get_line(), pos.get_line() + num_lines);
		}
		
		public void delete_range_handler(Buffer bf, TextIter pos, TextIter pos2) {
			//stdout.printf("delete_range(%d, %d)\n", pos.get_offset(), pos2.get_offset());
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

		// These static methods are hack to get around Vala not supporting singal_connect_after_yet
		public static Parser current;
		public static void static_insert_text_after_handler(Buffer bf, TextIter pos, string text, int length) {
			Parser.current.insert_text_after_handler(bf, pos, text, length);
		}
		public static void static_delete_range_after_handler(Buffer bf, TextIter pos, TextIter pos2) {
			Parser.current.delete_range_after_handler(bf, pos, pos2);
		}

		public static Parser create(Grammar grammar, Mate.Buffer buffer) {
			grammar.init_for_use();

			var p = new Parser();
			//stdout.printf("grammar: %s\n", grammar.name);
			p.grammar = grammar;
			p.buffer = buffer;
			p.changes = new RangeSet();
			p.deactivation_level = 0;
			p.make_root();
			p.connect_buffer_signals();
			Parser.current = p; // remove when signal_connect_after works
			return p;
		}
	}
}