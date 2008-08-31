
using GLib;
using Gee;

namespace Gtk.Mate {
	public class Matcher : Object {
		public static int compare_match(string scope_string, Oniguruma.Match m1, Oniguruma.Match m2) {
			var space_ixs = StringHelper.occurrences(scope_string, " ");
			// foreach (var ix in space_ixs)
			// 	stdout.printf("space at %d\n", ix);
			int max_cap1 = m1.num_captures();
			int max_cap2 = m2.num_captures();
			// stdout.printf("m1 has %d matches\n", m1.num_captures());
			// stdout.printf("m2 has %d matches\n", m2.num_captures());
			int cap1_ix, cap1_el_ix, len1;
			int cap2_ix, cap2_el_ix, len2;
			for (var i = 0; i < int.min(max_cap1, max_cap2); i++) {
				// first try element depth:
				cap1_ix = m1.begin(max_cap1-1-i);
				cap2_ix = m2.begin(max_cap2-1-i);
				// stdout.printf("m1 capture %d at %d\n", max_cap1-1-i, cap1_ix);
				// stdout.printf("m2 capture %d at %d\n", max_cap2-1-i, cap2_ix);
				cap1_el_ix = Matcher.sorted_ix(space_ixs, cap1_ix);
				cap2_el_ix = Matcher.sorted_ix(space_ixs, cap2_ix);
				// stdout.printf("m1 capture %d at el %d\n", max_cap1-1-i, cap1_el_ix);
				// stdout.printf("m2 capture %d at el %d\n", max_cap2-1-i, cap2_el_ix);
				if (cap1_el_ix > cap2_el_ix) {
					return 1;
				}
				else if (cap1_el_ix < cap2_el_ix) {
					return -1;
				}

				// next try length of match
				len1 = m1.end(max_cap1-1-i) - cap1_ix;
				len2 = m2.end(max_cap2-1-i) - cap2_ix;
				if (len1 > len2) {
					return 1;
				}
				else if (len1 < len2) {
					return -1;
				}
			}
			return 0;
		}
		
		private static int sorted_ix(ArrayList<int> ixs, int val) {
			if (ixs.size == 0)
				return 0;
			if (val < ixs[0])
				return 0;
			for (var i = 0; i < ixs.size; i++) {
				if (val > ixs[i])
					return i+1;
			}
			return ixs.size;
		}

		// this method is mainly for testing in the Ruby specs
		public static string test_rank(string selector_a, string selector_b, string scope_string) {
			Oniguruma.Match m1, m2;
			match(selector_a, scope_string, out m1);
			match(selector_b, scope_string, out m2);
			int r = compare_match(scope_string, m1, m2);
			if (r > 0) {
				return selector_a;
			}
			else if (r == 0 ){
				return selector_a + " == " + selector_b;
			}
			else {
				return selector_b;
			}
		}
		
		// this method is mainly for testing in the Ruby specs
		public static bool test_match(string selector_string, string scope_string) {
			Oniguruma.Match m;
			return match(selector_string, scope_string, out m);
		}

		public static bool match(string selector_string, string scope_string, out Oniguruma.Match match) {
			// FIXME should validate and throw UTF8 error if bad.
			string[] scope_ors1 = selector_string.split(",");
			foreach (var selector_string1 in scope_ors1) {
				Oniguruma.Regex pos_rx;
				var neg_rxs = new ArrayList<Oniguruma.Regex>();
				string[] positives_and_negatives = selector_string1.split(" -");
				foreach (var sub_selector_string in positives_and_negatives) {
					if (pos_rx == null) {
						var s1 = StringHelper.gsub(sub_selector_string.strip(), ".", "\\.");
						var s2 = StringHelper.gsub(s1, " ", ").*(");
						// stdout.printf("positive '%s' -> '%s'\n", selector_string, "("+s2+")");
						pos_rx = Oniguruma.Regex.make1("("+s2+")");
					}
					else {
						var s1 = StringHelper.gsub(sub_selector_string.strip(), ".", "\\.");
						var s2 = StringHelper.gsub(s1, " ", ".*");
						// stdout.printf("negative '%s' -> '%s'\n", selector_string, s2);
						neg_rxs.add(Oniguruma.Regex.make1(s2));
					}
				}
				if (test_match_re(pos_rx, neg_rxs, scope_string, out match))
					return true;
			}
			return false;
		}

		// public static void compile_re(string selector, out Oniguruma.Regex pos_re, 
		// 							  out ArrayList<Oniguruma.Regex> neg_res) {
			
		// }

		public static bool test_match_re(Oniguruma.Regex positive_selector_regex, 
										 ArrayList<Oniguruma.Regex> negative_selector_regex,
										 string scope_string,
										 out Oniguruma.Match match) {
			var m = positive_selector_regex.search(scope_string, 0, (int) scope_string.size() - 1);
			if (m != null) {
				foreach (var neg_rx in negative_selector_regex) {
					var m1 = neg_rx.search(scope_string, 0, (int) scope_string.size() - 1);
					if (m1 != null) {
						return false;
					}
				}
				match = m;
				return true;
			}
			else {
				return false;
			}
		}
	}
}