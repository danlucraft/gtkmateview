
// Oniguruma wrapper code
// see also vapi/oniguruma.vapi

using GLib;
using Oniguruma;

namespace Oniguruma {

	public class OnigError : Object {
		public int code;
		public OnigErrorInfo error_info;
	}

	public class Regex : Object {
		public RegexT rx {get; set;}

		public void search(string target, int start, int end) {
			Region rg = new Region();
			stdout.printf("allocated region\n");
			char* ctarget = (char *) target;
			rx.search(ctarget, (ctarget+target.size()), ctarget+start, (ctarget+end), rg, Option.NONE);
			stdout.printf("count: %d\n", rg.num_regs);
			for(int i = 0; i < rg.num_regs; i ++) {
				stdout.printf("  %d begins at %d\n", i, rg.beg[i]); 
			}
		}
		
		public static Regex? make(string pattern, OnigOptionType options, out OnigError error) {
			var rx = new Regex();
			char* c_pattern = (char *) pattern;
			RegexT rx1;
			Oniguruma.OnigErrorInfo err_info;
			int r = Oniguruma.onig_new(out rx1, 
									   c_pattern, (c_pattern+pattern.size()), 
									   options,
									   Encoding.ASCII, Syntax.DEFAULT, 
									   ref err_info);
			if (r < 0) {
				error = new OnigError();
				error.code = r;
				error.error_info = err_info;
				return null;
			}
			rx.rx = rx1;
			return rx;
		}
		
	}
}