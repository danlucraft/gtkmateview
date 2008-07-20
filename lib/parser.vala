
using Gee;
using GLib;

namespace Gtk.Mate {
	public enum ChangeType { INSERTION, DELETION }

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
	
	public struct Change {
		public TextLoc from;
		public TextLoc to;
		public ChangeType type;
		public int length;
		public int num_lines;
	}
	
	public class Parser : Object {
		public Grammar grammar {get; set;}
		public Mate.Buffer buffer {get; set;}
		public Mate.Scope root;
		public ArrayList<Change?> changes;

		public void make_root() {
			this.root = new Scope();
			this.root.name = this.grammar.scope_name;
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
			Change c = Change();
			c.type = ChangeType.INSERTION;
			c.from = TextLoc.make(pos.get_line(), pos.get_line_offset());
			c.length = length;
			var ss = text.split("\n");
			c.num_lines = -1;
			foreach (var s in ss) c.num_lines++;
			// stdout.printf("lines: %d\n", c.num_lines);
			changes.add(c);
		}
		
		public void delete_range_handler(Buffer bf, TextIter pos, TextIter pos2) {
			stdout.printf("delete_range(%d, %d)\n", pos.get_offset(), pos2.get_offset());
			Change c = Change();
			c.type = ChangeType.DELETION;
			c.from = TextLoc.make(pos.get_line(), pos.get_line_offset());
			c.to = TextLoc.make(pos.get_line(), pos.get_line_offset());
			c.length = pos2.get_offset() - pos.get_offset();
			c.num_lines = pos2.get_line() - pos.get_line();
			stdout.printf("lines: %d\n", c.num_lines);
			changes.add(c);
		}

		public void insert_text_after_handler(Buffer bf, TextIter pos, string text, int length) {
			stdout.printf("insert_text_after(pos, \"%s\", %d)\n", text, length);
		}

		public void delete_range_after_handler(Buffer bf, TextIter pos, TextIter pos2) {
			stdout.printf("delete_range_after(%d, %d)\n", pos.get_offset(), pos2.get_offset());
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
			p.changes = new ArrayList<Change?>();
			p.make_root();
			p.connect_buffer_signals();

			Parser.current = p; // remove when signal_connect_after works
			return p;
		}
	}
}