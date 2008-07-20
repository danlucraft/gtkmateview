
using GLib;
using Gee;

namespace Gtk.Mate {
	public class Buffer : SourceBuffer {
		public static ArrayList<Mate.Bundle> bundles;
		public static ArrayList<Mate.Theme>  themes;

		public Parser parser;
		
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
			var first_line = get_text(iter_(0), iter_line_start(1), false);
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

		// Offset from start of document -> Iter
		public TextIter iter_(int offset) {
			TextIter i;
			get_iter_at_offset(out i, offset);
			return i;
		}

		// Line number -> Iter
		public TextIter iter_line_start(int line) {
			TextIter i;
			get_iter_at_line(out i, line);
			return i;
		}

		construct {
			Mate.load_bundles();
			Mate.load_themes();
		}

	}
}