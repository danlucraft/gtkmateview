
using GLib;
using Gee;

namespace Gtk.Mate {
	public class View : SourceView {
		public bool set_theme_by_name(string name) {
			foreach (var theme in Theme.themes) {
				if (theme.name == name) {
					theme.init_for_use();
					((Gtk.Mate.Buffer) buffer).parser.colourer.theme = theme;
					set_global_theme_settings();
					return true;
				}
			}
			return false;
		}
		
		public void set_global_theme_settings() {
			if (((Gtk.Mate.Buffer) buffer).parser != null && ((Gtk.Mate.Buffer) buffer).parser.colourer != null)
				((Gtk.Mate.Buffer) buffer).parser.colourer.set_global_settings(this);
		}
	}
}