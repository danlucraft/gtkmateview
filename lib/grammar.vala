
using Gee;
using GLib;

namespace Gtk.Mate {

	public class Grammar : Object {
		// reference properties
		public string name {get; private set;}
		public PList.Dict plist {get; private set;}
		public string[] file_types;
		public Oniguruma.Regex first_line_match;
		public string key_equivalent;
		public string scope_name;
		public string comment;

		// rest of properties (loaded on demand)
		public bool loaded;
		
		public Grammar(PList.Dict plist) {
			this.plist = plist;
		}

		public void init_for_reference() {
			PList.Node? nm = plist.get("name");
			if (nm != null)
				name = ((PList.String) nm).str;

			PList.Node? flm = plist.get("firstLineMatch");
			if (flm != null)
				first_line_match = Oniguruma.Regex.make1(((PList.String) flm).str);

			PList.Node? ke = plist.get("keyEquivalent");
			if (ke != null)
				key_equivalent = ((PList.String) ke).str;

			PList.Node? sn = plist.get("scopeName");
			if (sn != null)
				scope_name = ((PList.String) sn).str;

			PList.Node? cm = plist.get("comment");
			if (cm != null)
				comment = ((PList.String) cm).str;

			PList.Node? filetypes = plist.get("fileTypes");
			if (filetypes != null) {
				PList.Array fts = (PList.Array) filetypes;
				file_types = new string[fts.array.size];
				int i = 0;
				foreach (var n in fts.array) {
					file_types[i++] = ((PList.String) n).str;
				}
			}
		}

		public Oniguruma.Regex folding_start_marker;
		public Oniguruma.Regex folding_stop_marker;
		public ArrayList<Pattern> patterns;
		public HashMap<string, ArrayList<Pattern>> repository;

		public void init_for_use() {
			if (loaded)
				return;
			stdout.printf("initializing grammar for use: %s\n", name);

			PList.Node? fsm = plist.get("foldingStartMarker");
			if (fsm != null)
				folding_start_marker = Oniguruma.Regex.make1(((PList.String) fsm).str);

			PList.Node? ftm = plist.get("foldingStopMarker");
			if (ftm != null)
				folding_stop_marker = Oniguruma.Regex.make1(((PList.String) ftm).str);
			
			patterns = new ArrayList<Pattern>();
			PList.Node? ps = plist.get("patterns");
			Pattern pattern;
			if (ps != null)
				foreach (var p in ((PList.Array) ps).array) {
					pattern = Pattern.create_from_plist((PList.Dict) p);
					if (pattern != null)
						patterns.add(pattern);
				}

			repository = new HashMap<string, ArrayList<Pattern>>(str_hash, str_equal);
			PList.Dict? pd = (PList.Dict?) plist.get("repository");
			PList.Dict? pd1;
			PList.Node? pa1;
			ArrayList<Pattern> repo_array;
			if (pd != null) {
				foreach (string key in pd.map.get_keys()) {
					var repo_array = new ArrayList<Pattern>();
					pd1 = (PList.Dict?) pd.get(key);
					pa1 = pd1.get("patterns");
					if (pa1 is PList.Array) {
						foreach (PList.Node ps1 in ((PList.Array) pa1).array) {
							pattern = Pattern.create_from_plist((PList.Dict) ps1);
							if (pattern != null)
								repo_array.add(pattern);
						}
					}
					else if (pa1 == null) {
						pattern = Pattern.create_from_plist((PList.Dict) pd1);
						if (pattern != null)
							repo_array.add(pattern);
					}
					repository.set(key, repo_array);
				}
			}

			stdout.printf("replaceing %d\n", patterns.size);
			foreach (Pattern pt in patterns) {
				if (pt == null)
					stdout.printf("null!\n");
				else
					replace_include_patterns(pt);
			}

			foreach (string key in repository.get_keys()) {
				var al = repository.get(key);
				stdout.printf("key: %s, %d\n", key, al.size);
				if (al == null)
					stdout.printf("key null: %s\n", key);
				foreach (Pattern pt in repository.get(key)) {
					replace_include_patterns(pt);
				}
			}
			
			// repository = null;

			loaded = true;
		}

		public void replace_include_patterns(Pattern pattern) {
			stdout.printf("replace include patterns for %s\n", pattern.name);
		}
	}

}