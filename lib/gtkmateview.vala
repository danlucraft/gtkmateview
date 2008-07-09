

using GLib;
using Gtk;
using Gee;

namespace Gtk {
	public class MateView : SourceView {
		public static ArrayList<Mate.Bundle> bundles;
		public static ArrayList<Mate.Theme>  themes;

		public static Mate.Grammar grammar {get; set;}

		// Sets the grammar with the file extension, then checks the
		// first line for matches as a fallback. If unable to find
		// a grammar, sets the grammar to null. Returns the grammar
		// name or null.
		public string? set_grammar_by_extension(string extension) {
			foreach (var bundle in bundles)
				foreach (var gr in bundle.grammars)
					foreach (var ext in gr.file_types)
						if (ext == extension) {
							this.grammar = gr;
							return gr.name;
						}
			Oniguruma.Regex re;
			var buf = (SourceBuffer) get_buffer();
			var first_line = buf.get_text(iter_(0), iter_line_start(1), false);
			foreach (var bundle in bundles)
				foreach (var gr in bundle.grammars)
					if ((re = gr.first_line_match) != null)
						if (re.search(first_line, 0, (int)first_line.size()) != null) {
							this.grammar = gr;
							return gr.name;
						}
			this.grammar = null;
			return null;
		}

		public TextIter iter_(int offset) {
			TextIter i;
			this.get_buffer().get_iter_at_offset(out i, offset);
			return i;
		}

		public TextIter iter_line_start(int line) {
			TextIter i;
			this.get_buffer().get_iter_at_line(out i, line);
			return i;
		}

		static construct {
			MateView.bundles = new ArrayList<Mate.Bundle>();
			MateView.themes  = new ArrayList<Mate.Theme>();
		}

		public static int load_bundles() {
			string syntax_dir, name;
			Mate.Bundle bundle;
			Mate.Grammar grammar;
			PList.Dict plist;
			foreach (string bundle_dir in bundle_dirs()) {
				bundle = new Mate.Bundle(bundle_dir.split(".")[0]);
				MateView.bundles.add(bundle);
				syntax_dir = textmate_share_dir() + "/Bundles/" + bundle_dir + "/Syntaxes";
				if (FileUtils.test(syntax_dir, FileTest.EXISTS)) {
					try {
						var d = Dir.open(syntax_dir);
						while ((name = d.read_name()) != null) {
							if (name != ".svn" &&
								(name.has_suffix(".tmLanguage") || 
								 name.has_suffix(".plist"))
								) {
								try {
									plist = PList.parse(syntax_dir + "/" + name);
								}
								catch (XmlError e) {
									stdout.printf("error opening %s\n", syntax_dir + "/" + name);
								}
								if (plist != null) {
									grammar = new Mate.Grammar(plist);
									bundle.grammars.add(grammar);
								}
							}
						}
					}
					catch(FileError e) {
						stdout.printf("error opening %s\n", syntax_dir);
					}
				}
			}
			
			foreach (var b in bundles)
				foreach (var g in b.grammars)
					g.init_for_reference();
			return -1;
		}

		public static ArrayList<string>? bundle_dirs() {
			string name;
			var share_dir = textmate_share_dir();
			var names = new ArrayList<string>();
			try {
				var d = Dir.open(share_dir+"/Bundles");
				while ((name = d.read_name()) != null) {
					if(name.has_suffix(".tmbundle")) {
						names.add(name);
					}
				}
				return names;
			}
			catch(FileError e) {
				stdout.printf("couldn't open: %s\n", share_dir+"/Bundles");
			}
			return null;
		}

		public static string? textmate_share_dir() {
			string share_dir = "/usr/local/share/textmate";
			if (FileUtils.test(share_dir, FileTest.EXISTS)) {
				return share_dir;
			}
			share_dir = "/usr/share/textmate";
			if (FileUtils.test(share_dir, FileTest.EXISTS)) {
				return share_dir;
			}
			stdout.printf("couldn't find /usr/share/textmate or /usr/local/share/textmate\n");
			return null;
		}

		public static string[]? bundle_dirs_rb() {
			string[] arr_names;
			ArrayList<string>? names = bundle_dirs();
			if (names != null) {
				arr_names = get_string_array(names);
				return arr_names;
			}
			else
				return null;
		}

		private static string[] get_string_array(ArrayList<string> al) {
			var arr = new string[al.size];
			int i = 0;
			foreach(string n in al) {
				arr[i] = n;
				i++;
			}
			return arr;
		}
	}

	namespace Mate {
		
		errordomain MateError {
			INIT_ERROR
		}

		public class Pattern : Object {

		}

		public class Theme : Object {

		}

		public class SinglePattern : Pattern {

		}

		public class DoublePattern : Pattern {

		}

	}
}
