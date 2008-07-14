
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

		public ArrayList<Pattern> all_patterns() {
			return this.patterns;
		}

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
					stdout.printf("convert repo name: %s\n", key);
					var repo_array = new ArrayList<Pattern>();
					pd1 = (PList.Dict?) pd.get(key);
					// repository name can go straight to a pattern
					if (pd1.get("begin") != null || pd1.get("match") != null) {
						pattern = Pattern.create_from_plist((PList.Dict) pd1);
						if (pattern != null)
							repo_array.add(pattern);
					}
					// or it can go to an array of patterns
					else {
						pa1 = pd1.get("patterns");
						foreach (PList.Node ps1 in ((PList.Array) pa1).array) {
							pattern = Pattern.create_from_plist((PList.Dict) ps1);
							if (pattern != null)
								repo_array.add(pattern);
						}
					}
					repository.set(key, repo_array);
				}
			}

			stdout.printf("replaceing repository %d\n", repository.size);

			foreach (string key in repository.get_keys()) {
				var al = repository.get(key);
				stdout.printf("key: %s, %d\n", key, al.size);
				replace_include_patterns(null, repository.get(key));
				if (al == null)
					stdout.printf("key null: %s\n", key);
				foreach (Pattern pt in repository.get(key)) {
					if (pt is DoublePattern)
						replace_include_patterns((DoublePattern) pt, ((DoublePattern) pt).patterns);
				}
			}

			stdout.printf("replaceing patterns %d\n", patterns.size);
			foreach (Pattern pt in patterns) {
				if (pt != null && pt is DoublePattern)
//					stdout.printf("null!\n");
//				else
					replace_include_patterns((DoublePattern) pt, ((DoublePattern) pt).patterns);
			}

			
			// repository = null;

			loaded = true;
		}

		public void replace_include_patterns(DoublePattern? pattern, ArrayList<Pattern> ps) {
			if (pattern == null)
				stdout.printf("replace include patterns for null\n");
			else
				stdout.printf("replace include patterns for %s\n", pattern.name);
			var include_patterns = new ArrayList<IncludePattern>();
			var patterns_to_include = new ArrayList<Pattern>();

			// find include patterns (and deal with subpatterns)
			foreach (Pattern p in ps) {
				if (p is IncludePattern) {
					include_patterns.add((IncludePattern) p);
				}
				else {
					if (p is DoublePattern)
						replace_include_patterns((DoublePattern) p, ((DoublePattern) p).patterns);
				}
			}

			// remove include patterns
			foreach (Pattern ip in include_patterns)
				ps.remove(ip);
			
			// add referenced patterns
			foreach (Pattern ip in include_patterns) {
				stdout.printf("includename: %s\n", ip.name);
				if (ip.name == "$self") {
					foreach (var p in ps) {
						patterns_to_include.add(p);
					}
				}
				else if (ip.name == "$base") {
					foreach (var p in this.patterns) {
						patterns_to_include.add(p);
					}
				}
				else if (ip.name.has_prefix("#")) {
					// stdout.printf("get reponame: %s\n", ip.name.substring(1, ((int) ip.name.size())-1));
// 					patterns_to_include = repository.get(ip.name.substring(1, ((int) ip.name.size())-1));
				}
				else {
					// stdout.printf("get reponame: %s\n", ip.name);
				}
				
				
			}
		}
	}

}