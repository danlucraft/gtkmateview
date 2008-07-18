
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
			else if (pd.get("begin") != null) {
				p = DoublePattern.create_from_plist(pd);
			}
			return p;
		}
		
		public static HashMap<int, string> make_captures_from_plist(PList.Dict pd) {
			PList.Dict? pcd;
			PList.String ns;
			var captures = new HashMap<int, string>(direct_hash, direct_equal);
			foreach (string s_capnum in pd.keys()) {
				int capnum = s_capnum.to_int();
				pcd = (PList.Dict) pd.get(s_capnum);
				ns = (PList.String) pcd.get("name");
				stdout.printf("capture: %s\n", ns.str);
				captures.set(capnum, ns.str);
			}
			return captures;
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

			PList.Node? n = pd.get("captures");
			PList.Dict? pcs, pcd;
			if (n != null) {
				pattern.captures = Pattern.make_captures_from_plist((PList.Dict) n);
			}
			
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
			stdout.printf("begin: %s\n", ns.str);
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

			PList.Node? n = pd.get("begin_captures");
			stdout.printf("before borb\n");
			if (n != null) {
				stdout.printf("got begin_captures\n");
				pattern.begin_captures = Pattern.make_captures_from_plist((PList.Dict) n);
			}
			else {
				stdout.printf("in backup\n");
				n = pd.get("captures");
				if (n != null) {
					pattern.begin_captures = Pattern.make_captures_from_plist((PList.Dict) n);
				}
			}
			
			n = pd.get("end_captures");
			if (n != null) {
				pattern.end_captures = Pattern.make_captures_from_plist((PList.Dict) n);
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