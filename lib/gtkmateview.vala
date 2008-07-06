
using GLib;

public class GtkMateView : Object {
	public static void main(string[] args) {
		string pattern = args[1];
		string target = args[2];
		Oniguruma.Regex? rx;
		Oniguruma.OnigError err;
		rx = Oniguruma.Regex.make(pattern, Oniguruma.Option.NONE, out err);
		if (rx == null) {
			string err_buf = "                                                                                                    ";
//				char* cerr_buf = err_buf;
			Oniguruma.error_code_to_string(err_buf, err.code);
			stdout.printf("caught onigerror: %d, '%s'\n", err.code, err_buf);
		}
		else {
			rx.search(target, 0, 11);
		}
	}
}
