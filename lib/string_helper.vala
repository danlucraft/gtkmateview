// Vala string utility functions
// Started: 30 Aug 08

using GLib;
using Gee;

public class StringHelper : Object {
	// Replace all occurences of match_string with replacement_string inside start_string.
	public static string gsub(string start_string, string match_string, string replacement_string) {
		GLib.Regex grx;
		string result;
		try {
			grx = new GLib.Regex(GLib.Regex.escape_string(match_string));
			result = grx.replace_literal(start_string, start_string.size(), 0, replacement_string);
		}
		catch(GLib.RegexError e) {
			return "";
		} 
		return result;
	}

	public static ArrayList<int> occurrences(string s, string t) {
		GLib.Regex grx;
		var poss = new ArrayList<int>();
		GLib.MatchInfo m;
		try {
			grx = new GLib.Regex(GLib.Regex.escape_string(t));
			if (grx.match(s, 0, out m)) {
				int spos, epos;
				m.fetch_pos(0, out spos, out epos);
				poss.add(spos);
				while (m.next()) {
					int mspos, mepos;
					m.fetch_pos(0, out mspos, out mepos);
					poss.add(mspos);
				}
			}
		}
		catch(GLib.RegexError e) {
			return new ArrayList<int>();
		}
		return poss;
	}
		// string cs = s;
		// int pos;
		// var poss = new ArrayList<int>();
		// while (cs != null) {
		// 	cs = cs.chr(-1, c);
		// 	pos = (int) s.pointer_to_offset(cs);
		// 	stdout.printf("found occurrence at: %d\n", pos);
		// 	poss.add(pos);
		// }
		// return poss;
	// }
}
