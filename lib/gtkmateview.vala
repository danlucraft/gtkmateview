

using GLib;
using Gtk;
using Gee;

namespace Gtk {
	public class MateView : SourceView {
		public static int load_grammars() {
			foreach(string bundle_dir in bundle_dirs()) {
				stdout.printf("%s\n", textmate_share_dir() + "/Bundles/" + bundle_dir);
			}
			return 1;
		}

		public static ArrayList<string>? bundle_dirs() {
			string name;
			var share_dir = textmate_share_dir();
			var names = new ArrayList<string>();
			try {
				var d = Dir.open(share_dir+"/Bundles");
				while ((name = d.read_name()) != null && name.has_suffix(".tmbundle")) {
					names.add(name);
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

		public class Grammar : Object {

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
