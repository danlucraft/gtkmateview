
using Gee;
using GLib;

namespace Gtk.Mate {

	public class Grammar : Object {
		// reference properties
		public string name {get; private set;}
		public PList.Dict plist {get; private set;}
		public string[] file_types;
		public Onig.Rx first_line_match;
		public string key_equivalent;
		public string scope_name;
		public string comment;
		public ArrayList<Pattern> all_patterns;

		public Onig.Rx folding_start_marker;
		public Onig.Rx folding_stop_marker;
		public ArrayList<Pattern> patterns;
		public HashMap<string, ArrayList<Pattern>> repository;

		// rest of properties (loaded on demand)
		public bool loaded;
		
		public Grammar(PList.Dict plist) {
			this.plist = plist;
		}

		public static Grammar? find_by_scope_name(string scope) {
			foreach (var bundle in Buffer.bundles) {
				foreach (var gr in bundle.grammars) {
					if (gr.scope_name == scope) {
						return gr;
					}
				}
			}
			return null;
		}

		// Loads the properties that are needed whether or not 
		// the grammar ever used.
		public void init_for_reference() {
			PList.Node? nm = plist.get("name");
			if (nm != null)
				name = ((PList.String) nm).str;

			PList.Node? flm = plist.get("firstLineMatch");
			if (flm != null)
				first_line_match = Onig.Rx.make1(((PList.String) flm).str);

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

		// Loads the properties of the grammar that are required
		// for parsing. Loads patterns into memory, and sets
		// up possible patterns.
		public void init_for_use() {
			if (loaded)
				return;
			loaded = true;
			stdout.printf("initializing grammar for use: %s\n", name);

			PList.Node? fsm = plist.get("foldingStartMarker");
			if (fsm != null)
				folding_start_marker = Onig.Rx.make1(((PList.String) fsm).str);

			PList.Node? ftm = plist.get("foldingStopMarker");
			if (ftm != null)
				folding_stop_marker = Onig.Rx.make1(((PList.String) ftm).str);

			this.all_patterns = new ArrayList<Pattern>();

			// stdout.printf("getting patterns\n");
			patterns = new ArrayList<Pattern>();
			PList.Node? ps = plist.get("patterns");
			Pattern pattern;
			if (ps != null)
				foreach (var p in ((PList.Array) ps).array) {
					pattern = Pattern.create_from_plist(this.all_patterns, (PList.Dict) p);
					if (pattern != null)
						patterns.add(pattern);
				}

			// stdout.printf("getting repository\n");
			repository = new HashMap<string, ArrayList<Pattern>>(str_hash, str_equal);
			PList.Dict? pd = (PList.Dict?) plist.get("repository");
			PList.Dict? pd1;
			PList.Node? pa1;
			ArrayList<Pattern> repo_array;
			if (pd != null) {
				foreach (string key in pd.map.get_keys()) {
					// stdout.printf("convert repo name: %s\n", key);
					var repo_array = new ArrayList<Pattern>();
					pd1 = (PList.Dict?) pd.get(key);
					// repository name can go straight to a pattern
					if (pd1.get("begin") != null || pd1.get("match") != null) {
						pattern = Pattern.create_from_plist(this.all_patterns, (PList.Dict) pd1);
						if (pattern != null) {
							repo_array.add(pattern);
						}
					}
					// or it can go to an array of patterns
					else {
						pa1 = pd1.get("patterns");
						foreach (PList.Node ps1 in ((PList.Array) pa1).array) {
							pattern = Pattern.create_from_plist(this.all_patterns, (PList.Dict) ps1);
							if (pattern != null) {
								repo_array.add(pattern);
							}
						}
					}
					repository.set(key, repo_array);
				}
			}

			// stdout.printf("all_patterns: %d\n", all_patterns.size);
			foreach (var p in this.all_patterns) {
				if (p is DoublePattern) {
					Pattern.replace_include_patterns(((DoublePattern) p).patterns, this);
				}
			}

			Pattern.replace_include_patterns(this.patterns, this);
		}
	}
}