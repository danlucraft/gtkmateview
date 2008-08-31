// Vala string utility functions
// Started: 30 Aug 08

using GLib;

public class StringHelper {
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
}