
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
			this.root = new Scope();
			this.root.name = this.grammar.scope_name;
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

		private void process_changes() {
			for (int i = 0; i < changes.length(); i++) {
				parse_from(changes.ranges[i].a, changes.ranges[i].b);
			}
			changes.ranges.clear();
		}

		private void parse_from(int from_line, int to_line) {
			stdout.printf("parse_from(%d, %d)\n", from_line, to_line);
		}

		public void connect_buffer_signals() {
			buffer.insert_text += this.insert_text_handler;
			buffer.delete_range += this.delete_range_handler;
			// remove when signal_connect_after works:
			Signal.connect_after(buffer, "insert_text", (GLib.Callback) Parser.static_insert_text_after_handler, null);
			Signal.connect_after(buffer, "delete_range", (GLib.Callback) Parser.static_delete_range_after_handler, null);
		}

		public void insert_text_handler(Buffer bf, TextIter pos, string text, int length) {
			stdout.printf("insert_text(pos, \"%s\", %d)\n", text, length);
			var ss = text.split("\n");
			int num_lines = -1;
			foreach (var s in ss) num_lines++;
			changes.add(pos.get_line(), pos.get_line() + num_lines);
		}
		
		public void delete_range_handler(Buffer bf, TextIter pos, TextIter pos2) {
			stdout.printf("delete_range(%d, %d)\n", pos.get_offset(), pos2.get_offset());
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
			p.grammar = grammar;
			p.buffer = buffer;
			p.changes = new RangeSet();
//			p.is_parsing = true;
			p.deactivation_level = 0;
			p.make_root();
			p.connect_buffer_signals();
			Parser.current = p; // remove when signal_connect_after works
			return p;
		}
	}
}