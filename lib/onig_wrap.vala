
// Oniguruma wrapper code
// see also vapi/oniguruma.vapi

using GLib;
using Oniguruma;

namespace Onig {

	public class OnigError : Object {
		public int code;
		public OnigErrorInfo error_info;
	}

	public class Match : Object {
		public RegexT rx {get; set;}
		public Region rg {get; set;}

		public static int count = 0;

		public int num_captures() {
			return this.rg.num_regs;
		}

		construct {
			Match.count++;
		}

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

	public class Rx : Object {
		public RegexT rx {get; set;}
		public bool matches_start_of_line;

		public Match? search(string target, int start, int end) {

			Region rg = new Region();
			char* ctarget = (char *) target;
			int r = rx.search(ctarget, (ctarget+target.size()), ctarget+start, (ctarget+end), rg, (Oniguruma.OnigOptionType*) Option.NONE);
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

		public static Rx? make(string pattern, OnigOptionType* options, out OnigError error) {
			var rx = new Rx();
			char* c_pattern = (char *) pattern;
			RegexT rx1;
			var err_info = Oniguruma.OnigErrorInfo();
			int r = Oniguruma.onig_new(out rx1, 
									   c_pattern, (c_pattern+pattern.size()), 
									   options,
									   (Oniguruma.OnigEncoding*) Encoding.ASCII, *Syntax.DEFAULT, 
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

		public static Rx? make1(string pattern) {
			OnigError e;
			return make(pattern, (Oniguruma.OnigOptionType*) Option.MULTILINE, out e);
		}
	}
}
