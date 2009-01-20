
using GLib;
using Gee;

namespace Gtk.Mate {
	public class Pattern : Object {
		public string name;
		public string comment;
		public static ArrayList<Pattern> all_patterns;
		public bool disabled;
		public Grammar grammar {get; set;}
		
		public static Pattern? create_from_plist(ArrayList<Pattern> all_patterns, PList.Dict pd) {
			Pattern p = null;
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

		public static void replace_include_patterns(ArrayList<Pattern> patlist, Grammar g) {
			// first replace repository, as repository can include $self
			replace_repository_includes(patlist, g);
			replace_base_and_self_includes(patlist, g);
		}

		public static void replace_repository_includes(ArrayList<Pattern> patlist, Grammar g) {
			var include_patterns = new ArrayList<Pattern>();
			var patterns_to_include = new ArrayList<Pattern>();
			bool any_included = true;
			// stdout.printf("%s.replace_repository_includes (%d)\n", this.name, this.patterns.size);
			while (any_included) {
				// stdout.printf("repo replacement pass\n");
				any_included = false;
				foreach (Pattern p in patlist) {
					if (p is IncludePattern && p.name.has_prefix("#")) {
						include_patterns.add(p);
						string reponame = p.name.substring(1, ((int) p.name.size())-1);
						ArrayList<Pattern> ps = g.repository.get(reponame);
						// stdout.printf("(%s) getting reponame: %s (%d)\n", this.name, reponame, ps.size);
						if (ps != null) {
							foreach (var p1 in ps) {
								any_included = true;
								patterns_to_include.add(p1);
							}
						}
						else {
							stdout.printf("warning: couldn't find repository key '%s' in grammar '%s'\n", reponame, g.name);
						}
					}
				}
				remove_patterns(patlist, include_patterns);
				add_patterns(patlist, patterns_to_include);
				include_patterns.clear();
				patterns_to_include.clear();
			}
		}

		public static void replace_base_and_self_includes(ArrayList<Pattern> patlist, Grammar g) {
			var include_patterns = new ArrayList<Pattern>();
			var patterns_to_include = new ArrayList<Pattern>();
			bool already_self = false; // some patterns have $self twice
			Grammar ng;
			foreach (Pattern p in patlist) {
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
//						stdout.printf("unknown include pattern: %s\n", p.name);
					}
				}
			}
			remove_patterns(patlist, include_patterns);
			add_patterns(patlist, patterns_to_include);
		}

		private static void remove_patterns(ArrayList<Pattern> patlist, ArrayList<Pattern> ps) {
			foreach (var p in ps) {
				patlist.remove(p);
			}
		}

		private static void add_patterns(ArrayList<Pattern> patlist, ArrayList<Pattern> ps) {
			foreach (var p in ps) {
				patlist.add(p);
			}
		}
	}
	
	public class SinglePattern : Pattern {
		public Onig.Rx match;
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
			pattern.match = Onig.Rx.make1(ns.str);

			PList.Node? n = pd.get("captures");
			pattern.captures = Pattern.make_captures_from_plist((PList.Dict?) n);

			n = pd.get("disabled");
			if (n != null && n is PList.Integer && ((PList.Integer) n).value == 1)
				pattern.disabled = true;
			else if (n != null && n is PList.String && ((PList.String) n).str == "1")
				pattern.disabled = true;
			else
				pattern.disabled = false;
				
			all_patterns.add(pattern);
			return pattern;
		}
	}
	
	public class DoublePattern : Pattern {
		public string content_name;
		public Onig.Rx begin;
		public Onig.Rx end;
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
			pattern.begin = Onig.Rx.make1(ns.str);
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

			n = pd.get("disabled");
			if (n != null && n is PList.Integer && ((PList.Integer) n).value == 1)
				pattern.disabled = true;
			else if (n != null && n is PList.String && ((PList.String) n).str == "1")
				pattern.disabled = true;
			else
				pattern.disabled = false;

			all_patterns.add(pattern);
			return pattern;
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
