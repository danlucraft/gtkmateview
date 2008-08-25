
using GLib;

public class ProfTest : Object {
	public static void main(string[] args) {
		stdout.printf("setting up...\n");
		var buf = new Gtk.Mate.Buffer();
		buf.set_grammar_by_name("Ruby");
		string filename = "file.vala";
		string content;
		ulong len;
		FileUtils.get_contents ("samples/rak", out content, out len);
		for(var i = 0; i < 1; i++) {
			buf.set_text(content, (int) len);
			buf.set_text("", 0);
		}
//		stdout.printf("%s\n", buf.parser.root.pretty(0));
		stdout.printf("done.\n");
	}
}