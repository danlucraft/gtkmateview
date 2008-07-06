
// oniguruma test
// valac -o onig_test onig_test.vala --save-temps --vapidir=./../vapi/ --pkg=oniguruma --Xcc="-lonig"

using GLib;
using Oniguruma;
public class OnigTest : Object {
	public static void main(string[] args) {
		string pattern = args[1]; //"(a)s(df)";
		string target = args[2]; //"fooasdfgoo";
		search(pattern, target);
	}
	
	public static void search(string str_pattern, string str_target) {
		char* pattern = str_pattern;
		char* target = str_target;
		Oniguruma.Regex rx;
		stdout.printf("pattern: %s\n", (string) pattern);
		stdout.printf("target: %s\n", (string) target);
		Oniguruma.OnigErrorInfo err_info;
		int r = Oniguruma.onig_new(out rx, pattern, (pattern+str_pattern.size()), Option.IGNORECASE,
								   Encoding.ASCII, Syntax.DEFAULT, ref err_info);
		if (r < 0) {
			stdout.printf("error code: %d\n", r);
			return;
		}
		stdout.printf("code: %d\n", r);
		stdout.printf("allocated re. num_captures: %d\n", rx.number_of_captures());
		Region rg = new Region();
		stdout.printf("allocated region\n");
		rx.search(target, (target+str_target.size()), target, (target+str_target.size()), rg, Option.NONE);
		stdout.printf("count: %d\n", rg.num_regs);
		for(int i = 0; i < rg.num_regs; i ++) {
			stdout.printf("  %d begins at %d\n", i, rg.beg[i]); 
		}
	}
	public static int strlen(char* str) {
		int i = 0;
	    char c;
		while ((c = str[i]) != '\0')
			i += 1;
		return i;
	}
}