
using GLib;
using Gee;

namespace Gtk.Mate {
	public class Buffer : SourceBuffer {
		public static ArrayList<Mate.Bundle> bundles;
		public static ArrayList<Mate.Theme>  themes;

		public Parser parser;
		
		construct {
			Mate.load_bundles();
			Mate.load_themes();
		}

		// Sets the grammar explicitly by name.
		public int set_grammar_by_name(string name) {
			foreach (var bundle in Buffer.bundles) {
				foreach (var gr in bundle.grammars) {
					if (gr.name == name) {
						this.parser = Parser.create(gr, this);
						return 1;
					}
				}
			}
			return 0;
		}

		// Sets the grammar by the file extension, then checks the
		// first line for matches as a fallback. If unable to find
		// a grammar, sets the grammar to null. Returns the grammar
		// name or null.
		public string? set_grammar_by_extension(string extension) {
			foreach (var bundle in Buffer.bundles)
				foreach (var gr in bundle.grammars)
					foreach (var ext in gr.file_types)
						if (ext == extension) {
							this.parser = Parser.create(gr, this);
							return gr.name;
						}
			Oniguruma.Regex re;
			var first_line = get_text(iter_(0), line_start_iter(1), false);
			foreach (var bundle in Buffer.bundles)
				foreach (var gr in bundle.grammars)
					if ((re = gr.first_line_match) != null)
						if (re.search(first_line, 0, (int) first_line.size()) != null) {
							this.parser = Parser.create(gr, this);
							return gr.name;
						}
			this.parser = null;
			return null;
		}

		// HELPER METHODS
		
		// Offset from start of document -> Iter
		public TextIter iter_(int offset) {
			TextIter i;
			get_iter_at_offset(out i, offset);
			return i;
		}

		public TextIter start_iter() {
			TextIter i;
			get_iter_at_offset(out i, 0);
			return i;
		}

		public TextIter end_iter() {
			TextIter i;
			get_iter_at_offset(out i, get_char_count());
			return i;
		}

		public TextIter cursor_iter() {
			TextIter i;
			get_iter_at_mark(out i, cursor_mark());
			return i;
		}

		public TextIter line_start_iter(int line) {
			TextIter i;
			get_iter_at_line(out i, line);
			return i;
		}

		// Iter at end of line, after the "\n" (if present).
	  	public TextIter line_end_iter(int line) {
	  		if (line >= get_line_count() - 1) {
				return end_iter();
	  		}
	  		else {
				return line_start_iter(line+1);
	  		}
	  	}

		// Iter at end of line, before the "\n" (if present).
		public TextIter line_end_iter1(int line) {
	  		if (line >= get_line_count() - 1) {
				return end_iter();
	  		}
	  		else {
				TextIter i = line_start_iter(line+1);
				i.backward_char();
				return i;
	  		}
		}

		public TextMark start_mark() {
			return get_mark("start_mark");
		}

		public TextMark end_mark() {
			return get_mark("end_mark");
		}

		public TextMark cursor_mark() {
			return get_mark("insert");
		}

		public TextMark selection_mark() {
			return get_mark("selection");
		}

		// Get text of line, including the "\n". Returns null if line does
		// not exist.
		public string? get_line(int line) {
			TextIter ei;
			if (line == get_line_count() - 1) {
				ei = end_iter();
			}
			else if (line > get_line_count() - 1 || line < 0) {
				return null;
			}
			else {
				ei = line_start_iter(line+1);
			}
			return get_slice(line_start_iter(line), ei, true);
		}

		public int get_line_length(int line) {
			if (line >= get_line_count() || line < 0) {
				return -1;
			}
			if (line == get_line_count() - 1)
				return end_iter().get_offset() - line_start_iter(line).get_offset();
			else
				return line_end_iter(line).get_offset() - line_start_iter(line).get_offset() - 1;
		}

		public int cursor_line() {
			return cursor_iter().get_line();
		}

		public int cursor_line_offset() {
			return cursor_iter().get_line_offset();
		}

		public int cursor_offset() {
			return cursor_iter().get_offset();
		}
	}
}