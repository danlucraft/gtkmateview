
using GLib;
using Gee;

namespace Gtk.Mate {
	public class Pattern : Object {
		public string name;
		public string comment;
		public static ArrayList<Pattern> all_patterns;

		public static Pattern? create_from_plist(PList.Dict pd) {
			PList.String? ns;
			Pattern p;
			if (pd.get("match") != null) {
				p = SinglePattern.create_from_plist(pd);
			}
			else if (pd.get("include") != null) {
				p = IncludePattern.create_from_plist(pd);
			}
			else if (pd.get("begin") != null){
				p = DoublePattern.create_from_plist(pd);
			}
			return p;
		}

	}
	
	public class SinglePattern : Pattern {
		public Oniguruma.Regex match;
		public HashMap<int, string> captures;

		public static SinglePattern? create_from_plist(PList.Dict pd) {
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
			return pattern;
		}
	}
	
	public class DoublePattern : Pattern {
		public Oniguruma.Regex begin;
		public Oniguruma.Regex end;
		public HashMap<int, string> begin_captures;
		public HashMap<int, string> end_captures;
		public ArrayList<Pattern> patterns;

		public static DoublePattern? create_from_plist(PList.Dict pd) {
			PList.String? ns;

			var pattern = new DoublePattern();
			ns = (PList.String) pd.get("name");
			if (ns != null) {
				pattern.name = ns.str;
//				stdout.printf("dp: %s\n", ((PList.String) pd.get("name")).str);
			}
			// else
			// 	stdout.printf("dp: no name\n");
			ns = (PList.String) pd.get("begin");
			pattern.begin = Oniguruma.Regex.make1(ns.str);
			ns = (PList.String) pd.get("end");
			pattern.end = Oniguruma.Regex.make1(ns.str);

			pattern.patterns = new ArrayList<Pattern>();
			PList.Node? ps = pd.get("patterns");
			Pattern subpattern;
			if (ps != null) {
				foreach (var p in ((PList.Array) ps).array) {
					subpattern = Pattern.create_from_plist((PList.Dict) p);
					if (subpattern != null)
						pattern.patterns.add(subpattern);
				}
			}
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