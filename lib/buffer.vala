
using GLib;
using Gee;

namespace Gtk.Mate {
	public class Buffer : SourceBuffer {
		public static ArrayList<Mate.Bundle> bundles;
		public static ArrayList<Mate.Theme>  themes;
		
		private static Grammar _grammar;
		public static Grammar grammar {
			get {
				return this._grammar;
			}
			set {
				if (value != null)
					value.init_for_use();
				this._grammar = value;
			}
		}
		
		// Sets the grammar with the file extension, then checks the
		// first line for matches as a fallback. If unable to find
		// a grammar, sets the grammar to null. Returns the grammar
		// name or null.
		public string? set_grammar_by_extension(string extension) {
			foreach (var bundle in Buffer.bundles)
				foreach (var gr in bundle.grammars)
					foreach (var ext in gr.file_types)
						if (ext == extension) {
							this.grammar = gr;
							return gr.name;
						}
			Oniguruma.Regex re;
			var first_line = get_text(iter_(0), iter_line_start(1), false);
			foreach (var bundle in Buffer.bundles)
				foreach (var gr in bundle.grammars)
					if ((re = gr.first_line_match) != null)
						if (re.search(first_line, 0, (int) first_line.size()) != null) {
							this.grammar = gr;
							return gr.name;
						}
			this.grammar = null;
			return null;
		}

		public TextIter iter_(int offset) {
			TextIter i;
			get_iter_at_offset(out i, offset);
			return i;
		}

		public TextIter iter_line_start(int line) {
			TextIter i;
			get_iter_at_line(out i, line);
			return i;
		}

		construct {
			Mate.load_bundles();
		}

	}
}