
using Gee;
using GLib;

namespace Gtk.Mate {
	public class ThemeSetting : Object {
		public string name;
		public string selector;
		public HashMap<string, string> settings;
		public ArrayList<Matcher> matchers;

		public static ThemeSetting create_from_plist(PList.Dict dict) {
			var tsetting = new ThemeSetting();
			
			PList.Node? nm = dict.get("name");
			if (nm != null)
				tsetting.name = ((PList.String) nm).str;
			nm = dict.get("scope");
			if (nm != null)
				tsetting.selector = ((PList.String) nm).str;

			tsetting.settings = new HashMap<string, string>(str_hash, str_equal);
			PList.Dict pd = (PList.Dict) dict.get("settings");
			foreach (string key in pd.map.get_keys()) {
				tsetting.settings.set(key, ((PList.String) pd.map.get(key)).str);
			}

			return tsetting;
		}

		public void compile_scope_matchers() {
			//stdout.printf("  compiling '%s'\n", selector);
			this.matchers = Matcher.compile(selector);
		}

		public bool match(string scope, out Onig.Match match) {
			if (this.matchers == null)
				compile_scope_matchers();
			foreach(var matcher in this.matchers) {
				if (Matcher.test_match_re(matcher.pos_rx, matcher.neg_rxs, scope, out match))
					return true;
			}
			return false;
		}
	}
	
	public class Theme : Object {
		public static ArrayList<Theme> _themes;
		public static ArrayList<Theme> themes() {
			if (Theme._themes == null) {
				Gtk.Mate.load_themes();
			}
			return Theme._themes;
		}

		public string author;
		public string name;
		public HashMap<string, string> global_settings;
		public ArrayList<ThemeSetting> settings;
		public bool is_initialized;
		public HashMap<string, ThemeSetting> cached_setting_for_scopes;

		public static Theme create_from_plist(PList.Dict dict) {
			var theme = new Theme();
			theme.is_initialized = false;

			PList.Node? nm = dict.get("name");
			if (nm != null) {
				theme.name = ((PList.String) nm).str;
			}
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
			// stdout.printf("initializing theme for use: %s\n", name);
			this.cached_setting_for_scopes = new HashMap<string, ThemeSetting>(str_hash, str_equal);
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

		// TODO make this return multiple themes if they are identical
		// (see 13.5 of Textmate manual)
		public ThemeSetting settings_for_scope(Scope scope, bool inner, ThemeSetting? exclude_setting) {
			string scope_name = scope.hierarchy_names(inner);
			//stdout.printf("  finding settings for '%s'\n", scope_name);
			ThemeSetting cached;
			if (this.cached_setting_for_scopes.contains(scope_name)) {
				cached = this.cached_setting_for_scopes.get(scope_name);
				return cached;
			}
			Onig.Match current_m = null, m;
			ThemeSetting current = null;
			foreach (var setting in settings) {
				if (setting == exclude_setting && exclude_setting != null) {
//					stdout.printf("    setting '%s' excluded due to parent\n", exclude_setting.name);
				}
				else {
					if (setting.match(scope_name, out m)) {
//						stdout.printf("    setting '%s' matches selector '%s'\n", setting.name, setting.selector); 
						if (current == null) {
							current = setting;
							current_m = m;
						}
						else if (Matcher.compare_match(scope_name, current_m, m) < 0) {
							current = setting;
							current_m = m;
						}
					}
				}
			}
//			if (current == null) {
//				stdout.printf("none match\n");
//			}
//			else {
//				stdout.printf("    best: '%s'\n", current.name);
//			}
			this.cached_setting_for_scopes.set(scope_name, current);
			return current;
		}
	}
}
