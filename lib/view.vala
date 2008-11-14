
using GLib;
using Gee;

namespace Gtk.Mate {
	public class View : SourceView {
		public bool set_theme_by_name(string name) {
			foreach (var theme in Theme.themes) {
				if (theme.name == name) {
					theme.init_for_use();
					((Gtk.Mate.Buffer) buffer).parser.change_theme(theme);
					set_global_theme_settings();
					return true;
				}
			}
			return false;
		}
		
		public void set_global_theme_settings() {
			if (((Gtk.Mate.Buffer) buffer).parser != null && ((Gtk.Mate.Buffer) buffer).parser.colourer != null) {
				((Gtk.Mate.Buffer) buffer).parser.colourer.set_global_settings(this);
			}
		}

		// TODO finish this off once Vala gets signal_connect_after support
		// public void connect_signals() {
		// 	stdout.printf("mateview connect_signals\n");
		// 	this.parent_set += (prev_parent) => {
		// 		if (this.get_parent() is Gtk.ScrolledWindow) {
		// 			stdout.printf("parent is scrolled window\n");
		// 		}
		// 	};
		// }

		public void value_changed_handler() {
			var parser = get_parser();
			if (parser != null)
				parser.last_visible_line_changed(last_visible_line());
		}

		public Gtk.Mate.Parser? get_parser() {
			return ((Gtk.Mate.Buffer) buffer).parser;
		}
		
		public int last_visible_line() {
			Gdk.Rectangle rect;
			get_visible_rect(out rect);
			int bufy = rect.y + rect.height;
			Gtk.TextIter iter;
			get_line_at_y(out iter, bufy, null);
			int line = iter.get_line();
			return line;
		}
	}
}