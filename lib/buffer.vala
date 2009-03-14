using GLib;
using Gee;

namespace Gtk.Mate {
	public class Buffer : SourceBuffer {
		public static ArrayList<Mate.Bundle> bundles;
		public static ArrayList<Mate.Theme>  themes;

		// TODO: fix up valar to make this work.
		public signal	void grammar_changed(string name);

		public Parser parser;
		
		construct {
			Mate.load_bundles();
			Mate.load_themes();
		}

		// Sets the grammar explicitly by name.
		public bool set_grammar_by_name(string name) {
			if (this.parser != null && this.parser.grammar.name == name)
				return true;
		  
			foreach (var bundle in Buffer.bundles) {
				foreach (var gr in bundle.grammars) {
					if (gr.name == name) {
						int parsed_upto = 150;
						Theme theme = null;
						if (this.parser != null) {
							theme = this.parser.colourer.theme;
							this.parser.colourer.uncolour_scope(this.parser.root, true);
							parsed_upto = this.parser.parsed_upto;
							this.parser.close();
						}
						this.parser = Parser.create(gr, this);
						this.parser.last_visible_line_changed(parsed_upto);
						if (theme != null)
						  this.parser.change_theme(theme);
						return true;
					}
				}
			}
			return false;
		}

		// Sets the grammar by the file extension. If unable to find
		// a grammar, sets the grammar to null. Returns the grammar
		// name or null.
		public string? set_grammar_by_filename(string filename) {
			string best_name = null;
			long best_length = 0;
			foreach (var bundle in Buffer.bundles) {
				foreach (var gr in bundle.grammars) {
					foreach (var ext in gr.file_types) {
						if (filename.has_suffix(ext) && (best_name == null || ext.length > best_length)) {
							best_name = gr.name;
							best_length = ext.length;
						}
					}
				}
			}
			if (best_name != null) {
				if (this.parser == null || this.parser.grammar.name != best_name) {
					set_grammar_by_name(best_name);
				}
				return best_name;
			}
			return null;
		}

		// Sets the grammar by examining the first line. If unable to find
		// a grammar, sets the grammar to null. Returns the grammar
		// name or null.
		public string? set_grammar_by_first_line(string first_line) {
			Onig.Rx re;
			foreach (var bundle in Buffer.bundles)
				foreach (var gr in bundle.grammars)
					if ((re = gr.first_line_match) != null)
						if (re.search(first_line, 0, (int) first_line.size()) != null) {
							set_grammar_by_name(gr.name);
							return gr.name;
						}
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

		public TextIter iter_from_mark(TextMark mark) {
			TextIter i;
			get_iter_at_mark(out i, mark);
			return i;
		}

		public TextIter iter_at_line_offset(int line, int line_offset) {
			TextIter i;
			get_iter_at_line_offset(out i, line, line_offset);
			return i;
		}

		public TextIter iter_at_line_index(int line, int line_offset) {
			TextIter i;
			get_iter_at_line_index(out i, line, line_offset);
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
			return get_mark("selection_bound");
		}

		// Get text of line, including the "\n" if present. Returns null if line 
		// does not exist.
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

		// Get text of line, not including the "\n". Returns null if line
		// does not exist.
		public string? get_line1(int line_ix) {
			string? line;
			if ((line = get_line(line_ix)) != null) {
				if (line_ix == get_line_count() - 1)
					return line;
				else
					return line.substring(0, line.length-1);
			}
			return null;
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
		
		public void select_current_scope() {
			var current_scope = this.parser.root.scope_at(cursor_iter().get_line(), cursor_iter().get_line_offset());
			var start_iter = current_scope.start_iter();
			var end_iter = current_scope.end_iter();
			move_mark(selection_mark(), start_iter);
			move_mark(cursor_mark(), end_iter);
		}
		
		public ArrayList<int> current_scope_range() {
			var current_scope = this.parser.root.scope_at(cursor_iter().get_line(), cursor_iter().get_line_offset());
			var start_iter = current_scope.start_iter();
			var end_iter = current_scope.end_iter();
			var range = new ArrayList<int>();
			range.add(start_iter.get_offset());
			range.add(end_iter.get_offset());
			return range;
		}
	}
}


