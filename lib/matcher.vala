
using GLib;
using Gee;

namespace Gtk.Mate {
	public class Matcher : Object {
		// public static int compare_match(Oniguruma.Match m1, Oniguruma.Match m2) {
			
		// }
		
		public static bool test_match(string selector_string, string scope_string){
			// FIXME should validate and throw UTF8 error if bad.
			string[] scope_ors1 = selector_string.split(",");
			foreach (var selector_string1 in scope_ors1) {
				Oniguruma.Regex pos_rx;
				var neg_rxs = new ArrayList<Oniguruma.Regex>();
				string[] positives_and_negatives = selector_string1.split("-");
				foreach (var sub_selector_string in positives_and_negatives) {
					if (pos_rx == null) {
						var s1 = StringHelper.gsub(sub_selector_string.strip(), ".", "\\.");
						var s2 = StringHelper.gsub(s1, " ", ").*(");
						stdout.printf("positive '%s' -> '%s'\n", selector_string, "("+s2+")");
						pos_rx = Oniguruma.Regex.make1("("+s2+")");
					}
					else {
						var s1 = StringHelper.gsub(sub_selector_string.strip(), ".", "\\.");
						var s2 = StringHelper.gsub(s1, " ", ".*");
						stdout.printf("negative '%s' -> '%s'\n", selector_string, s2);
						neg_rxs.add(Oniguruma.Regex.make1(s2));
					}
				}
				if (test_match_re(pos_rx, neg_rxs, scope_string))
					return true;
			}
			return false;
		}

		public static bool test_match_re(Oniguruma.Regex positive_selector_regex, 
										 ArrayList<Oniguruma.Regex> negative_selector_regex,
										 string scope_string) {
			var m = positive_selector_regex.search(scope_string, 0, (int) scope_string.size() - 1);
			if (m != null) {
				foreach (var neg_rx in negative_selector_regex) {
					var m1 = neg_rx.search(scope_string, 0, (int) scope_string.size() - 1);
					if (m1 != null) {
						return false;
					}
				}
				return true;
			}
			else {
				return false;
			}
		}
	}
}