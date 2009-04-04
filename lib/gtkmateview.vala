
using GLib;
using Gtk;
using Gee;

namespace Gtk {
	namespace Mate {
    public static string textmate_dir = null;

		// Loads bundles (in particular, grammars) from 
		// /usr/share/textmate/Bundles or from the location in
    // textmate_dir
		public static int load_bundles() {
			if (Buffer.bundles != null)
				return 1;
			Buffer.bundles = new ArrayList<Mate.Bundle>();
			Buffer.themes  = new ArrayList<Mate.Theme>();
			string syntax_dir, name;
			Mate.Bundle bundle;
			Mate.Grammar grammar;
			PList.Dict plist = null;
			foreach (string bundle_dir in bundle_dirs()) {
				bundle = new Mate.Bundle(bundle_dir.split(".")[0]);
				Buffer.bundles.add(bundle);
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
									grammar.filename = name;
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
			
			foreach (var b in Buffer.bundles)
				foreach (var g in b.grammars)
					g.init_for_reference();
			return -1;
		}

		// Loads themes from /usr/share/textmate/Themes/. 
		public static void load_themes() {
			if (Theme._themes != null)
				return;
			Theme._themes = new ArrayList<Theme>();
			foreach (string fn in Theme.theme_filenames()) {
				try {
					var plist = PList.parse(fn);
					var theme = Theme.create_from_plist((PList.Dict) plist);
					if (theme != null)
						Theme._themes.add(theme);
				}
				catch(XmlError e) {
					stdout.printf("error opening %s\n", fn);
				}
			}
		}

		// Return a list of bundle names like "Ruby.tmbundle"
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

		// Return the textmate assets directory path,
		// e.g. /usr/share/textmate
		public static string? textmate_share_dir() {
      if (Gtk.Mate.textmate_dir != null) 
        return Gtk.Mate.textmate_dir;
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
	}
}
