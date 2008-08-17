
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
		public bool matches_start_of_line;

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
			// OnigSyntaxType syntax;
			// stdout.printf("foo\n");
			// Oniguruma.Syntax.copy(&syntax, Syntax.DEFAULT);
			// // stdout.printf("bar\n");
			// // stdout.printf("op2; %d\n", (int) syntax.get_op2()); 
			// int newop2 = (int) (syntax.get_op2() | Syntax.Op2.ATMARK_CAPTURE_HISTORY);
			// // stdout.printf("newop2; %d\n", newop2);
			// syntax.set_op2((int) newop2);
			// stdout.printf("baz\n");
			int r = Oniguruma.onig_new(out rx1, 
									   c_pattern, (c_pattern+pattern.size()), 
									   options,
									   Encoding.ASCII, *Syntax.DEFAULT, 
									   ref err_info);
			rx.matches_start_of_line = pattern.has_prefix("^");
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