
// Oniguruma wrapper code
// see also vapi/oniguruma.vapi

using GLib;
using Oniguruma;

namespace Oniguruma {

	public class OnigError : Object {
		public int code;
		public OnigErrorInfo error_info;
	}

	public class Match : Object {
		public RegexT rx {get; set;}
		public Region rg {get; set;}

		public int begin(int capture) {
			if (capture >= this.rg.num_regs || capture < 0)
				return -1;
			return this.rg.beg[capture];
		}

		public int end(int capture) {
			if (capture >= this.rg.num_regs || capture < 0)
				return -1;
			return this.rg.end[capture];
		}
	}

	public class Regex : Object {
		public RegexT rx {get; set;}

		public Match? search(string target, int start, int end) {
			Region rg = new Region();
			char* ctarget = (char *) target;
			int r = rx.search(ctarget, (ctarget+target.size()), ctarget+start, (ctarget+end), rg, Option.NONE);
			if (r < 0) {
				return null;
			}
			else {
				var md = new Match();
				md.rg = rg;
				md.rx = rx;
				return md;
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

		public static Regex? make1(string pattern) {
			OnigError e;
			return make(pattern, Option.MULTILINE, out e);
		}
	}
}
		// public static void test_regex(string[] args) {
		// 	string pattern = args[1];
		// 	string target = args[2];
		// 	Oniguruma.Regex? rx;
		// 	Oniguruma.OnigError err;
		// 	rx = Oniguruma.Regex.make(pattern, Oniguruma.Option.NONE, out err);
		// 	if (rx == null) {
		// 		string err_buf = "                                                                                                    ";
		// 		Oniguruma.error_code_to_string(err_buf, err.code);
		// 		stdout.printf("caught onigerror: %d, '%s'\n", err.code, err_buf);
		// 	}
		// 	else {
		// 		rx.search(target, 0, 11);
		// 	}
		// }