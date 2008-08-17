
using GLib;
using Gee;

namespace Gtk.Mate {
	public class Pattern : Object {
		public string name;
		public string comment;
		public static ArrayList<Pattern> all_patterns;

		public static Pattern? create_from_plist(ArrayList<Pattern> all_patterns, PList.Dict pd) {
			PList.String? ns;
			Pattern p;
			if (pd.get("match") != null) {
				p = SinglePattern.create_from_plist(all_patterns, pd);
			}
			else if (pd.get("include") != null) {
				p = IncludePattern.create_from_plist(pd);
			}
			else if (pd.get("begin") != null) {
				p = DoublePattern.create_from_plist(all_patterns, pd);
			}
			return p;
		}
		
		public static HashMap<int, string> make_captures_from_plist(PList.Dict? pd) {
			if (pd == null)
				return new HashMap<int, string>(direct_hash, direct_equal);
			PList.Dict? pcd;
			PList.String ns;
			var captures = new HashMap<int, string>(direct_hash, direct_equal);
			foreach (string s_capnum in pd.keys()) {
				int capnum = s_capnum.to_int();
				pcd = (PList.Dict) pd.get(s_capnum);
				ns = (PList.String) pcd.get("name");
				// stdout.printf("capture: %d, %s\n", capnum, ns.str);
				captures.set(capnum, ns.str);
			}
			return captures;
		}
	}
	
	public class SinglePattern : Pattern {
		public Oniguruma.Regex match;
		public HashMap<int, string> captures;

		public static SinglePattern? create_from_plist(ArrayList<Pattern> all_patterns, PList.Dict pd) {
			PList.String? ns;
			var pattern = new SinglePattern();
			ns = (PList.String) pd.get("name");
			if (ns != null) {
				pattern.name = ns.str;
//				stdout.printf("sp: %s\n", ((PList.String) pd.get("name")).str);
			}
//			else
//				stdout.printf("sp: no name\n");
			ns = (PList.String) pd.get("match");
			pattern.match = Oniguruma.Regex.make1(ns.str);

			PList.Node? n = pd.get("captures");
			PList.Dict? pcs, pcd;
			pattern.captures = Pattern.make_captures_from_plist((PList.Dict?) n);
			all_patterns.add(pattern);
			return pattern;
		}
	}
	
	public class DoublePattern : Pattern {
		public string content_name;
		public Oniguruma.Regex begin;
		public Oniguruma.Regex end;
		public string end_string;
		public string begin_string;
		public HashMap<int, string> begin_captures;
		public HashMap<int, string> end_captures;
		public HashMap<int, string> both_captures;
		public ArrayList<Pattern> patterns;

		public static DoublePattern? create_from_plist(ArrayList<Pattern> all_patterns, PList.Dict pd) {
			PList.String? ns;

			var pattern = new DoublePattern();
			ns = (PList.String) pd.get("name");
			if (ns != null) {
				pattern.name = ns.str;
			}
			ns = (PList.String) pd.get("begin");
			pattern.begin_string = ns.str;
			pattern.begin = Oniguruma.Regex.make1(ns.str);
			ns = (PList.String) pd.get("end");
			pattern.end_string = ns.str;

			ns = (PList.String) pd.get("contentName");
			if (ns != null) {
				pattern.content_name = ns.str;
			}

			PList.Node? n = pd.get("beginCaptures");
			if (n != null) {
				pattern.begin_captures = Pattern.make_captures_from_plist((PList.Dict?) n);
			}

			n = pd.get("captures");
			if (n != null) {
				pattern.both_captures = Pattern.make_captures_from_plist((PList.Dict?) n);
			}
			
			n = pd.get("endCaptures");
			pattern.end_captures = Pattern.make_captures_from_plist((PList.Dict?) n);

			pattern.patterns = new ArrayList<Pattern>();
			PList.Node? ps = pd.get("patterns");
			Pattern subpattern;
			if (ps != null) {
				foreach (var p in ((PList.Array) ps).array) {
					subpattern = Pattern.create_from_plist(all_patterns, (PList.Dict) p);
					if (subpattern != null)
						pattern.patterns.add(subpattern);
				}
			}
			all_patterns.add(pattern);
			return pattern;
		}			

		public void replace_include_patterns(Grammar g) {
			// first replace repository, as repository can include $self
			replace_repository_includes(g);
			replace_base_and_self_includes(g);
		}

		public void replace_repository_includes(Grammar g) {
			var include_patterns = new ArrayList<Pattern>();
			var patterns_to_include = new ArrayList<Pattern>();
			bool any_included = true;
			// stdout.printf("%s.replace_repository_includes (%d)\n", this.name, this.patterns.size);
			while (any_included) {
				// stdout.printf("repo replacement pass\n");
				any_included = false;
				foreach (Pattern p in this.patterns) {
					if (p is IncludePattern && p.name.has_prefix("#")) {
						include_patterns.add(p);
						string reponame = p.name.substring(1, ((int) p.name.size())-1);
						ArrayList<Pattern> ps = g.repository.get(reponame);
						// stdout.printf("(%s) getting reponame: %s (%d)\n", this.name, reponame, ps.size);
						foreach (var p1 in ps) {
							any_included = true;
							patterns_to_include.add(p1);
						}
					}
				}
				remove_patterns(include_patterns);
				add_patterns(patterns_to_include);
				include_patterns.clear();
				patterns_to_include.clear();
			}
		}

		public void replace_base_and_self_includes(Grammar g) {
			var include_patterns = new ArrayList<Pattern>();
			var patterns_to_include = new ArrayList<Pattern>();
			bool already_self = false; // some patterns have $self twice
			Grammar ng;
			foreach (Pattern p in this.patterns) {
				if (p is IncludePattern) {
					if (p.name.has_prefix("$")) {
						include_patterns.add(p);
						if ((p.name == "$self" || p.name == "$base") && !already_self) {
							already_self = true;
							foreach (var p in g.patterns) {
								patterns_to_include.add(p);
							}
						}
					}
					else if ((ng = Grammar.find_by_scope_name(p.name)) != null) {
						ng.init_for_use();
						include_patterns.add(p);
						foreach (var p in ng.patterns) {
							patterns_to_include.add(p);
						}
					}
					else {
						stdout.printf("(%s) unknown include pattern: %s\n", this.name, p.name);
					}
				}
			}
			remove_patterns(include_patterns);
			add_patterns(patterns_to_include);
		}

		private void remove_patterns(ArrayList<Pattern> ps) {
			foreach (var p in ps) {
				this.patterns.remove(p);
			}
		}

		private void add_patterns(ArrayList<Pattern> ps) {
			foreach (var p in ps) {
				this.patterns.add(p);
			}
		}
	}

	public class IncludePattern : Pattern {
		public static IncludePattern? create_from_plist(PList.Dict pd) {
			PList.String? ns;

			var pattern = new IncludePattern();
			ns = (PList.String) pd.get("include");
			pattern.name = ns.str;
			// stdout.printf("ip: %s\n", ns.str);
			return pattern;
		}
	}
}