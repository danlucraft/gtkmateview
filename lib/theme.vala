
using Gee;
using GLib;

namespace Gtk.Mate {
	public class ThemeSetting : Object {
		public string name;
		public string scope;
		public HashMap<string, string> settings;
		public Oniguruma.Regex positive_rx;
		public Oniguruma.Regex negative_rx;
		public int specificity;

		public static ThemeSetting create_from_plist(PList.Dict dict) {
			var tsetting = new ThemeSetting();
			
			PList.Node? nm = dict.get("name");
			if (nm != null)
				tsetting.name = ((PList.String) nm).str;
			nm = dict.get("scope");
			if (nm != null)
				tsetting.scope = ((PList.String) nm).str;

			tsetting.settings = new HashMap<string, string>(str_hash, str_equal);
			PList.Dict pd = (PList.Dict) dict.get("settings");
			foreach (string key in pd.map.get_keys()) {
				tsetting.settings.set(key, ((PList.String) pd.map.get(key)).str);
			}

			return tsetting;
		}

		public void compile_scope_matchers() {
			stdout.printf("compiling '%s'\n", scope);
			
		}
	}
	
	public class Theme : Object {
		public static ArrayList<Theme> themes;

		public string author;
		public string name;
		public HashMap<string, string> global_settings;
		public ArrayList<ThemeSetting> settings;
		public bool is_initialized;

		public static Theme create_from_plist(PList.Dict dict) {
			var theme = new Theme();
			theme.is_initialized = false;

			PList.Node? nm = dict.get("name");
			if (nm != null)
				theme.name = ((PList.String) nm).str;
			nm = dict.get("author");
			if (nm != null)
				theme.author = ((PList.String) nm).str;	

			theme.global_settings = new HashMap<string, string>(str_hash, str_equal);
			theme.settings = new ArrayList<ThemeSetting>();
			PList.Array na = (PList.Array) dict.get("settings");
			foreach (PList.Node nn in na.array) {
				var nd = (PList.Dict) nn;
				if (nd.get("scope") == null) {
					var gsd = ((PList.Dict) nd.get("settings"));
					foreach (string key in gsd.keys()) {
						theme.global_settings.set(key, ((PList.String) gsd.get(key)).str);
					}
				}
				else {
					theme.settings.add(ThemeSetting.create_from_plist(nd));
				}
			}
			
			return theme;
		}

		public void init_for_use() {
			if (is_initialized)
				return;
			is_initialized = true;
			stdout.printf("initializing theme for use: %s\n", name);
			foreach (var setting in settings) {
				setting.compile_scope_matchers();
			}
		}

		public static ArrayList<string>? theme_filenames() {
			var names = new ArrayList<string>();
			var share_dir = Gtk.Mate.textmate_share_dir();
			string name;
			try {
				var d = Dir.open(share_dir+"/Themes");
				while ((name = d.read_name()) != null) {
					if(name.has_suffix(".tmTheme")) {
						names.add(share_dir + "/Themes/" + name);
					}
				}
				return names;
			}
			catch(FileError e) {
				stdout.printf("couldn't open: %s\n", share_dir+"/Bundles");
			}
			return null;
		}

		public ArrayList<ThemeSetting> settings_for_scope(Scope scope) {
			
			return new ArrayList<ThemeSetting>();
		}
	}
}