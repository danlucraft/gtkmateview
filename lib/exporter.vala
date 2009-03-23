
using GLib;
using Gee;

namespace Gtk.Mate {
	public class Exporter : Object {
		public View view;

		public Exporter(View v) {
			this.view = v;
		}

		public string to_html(string title) {
			string html = html_header(title);
			
			return html + css();
		}

		private string html_header(string title) {
			string header = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\">\n" + 
                      "<head>\n" + 
   										"\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n" + 
											"\t<title>" + title + "</title>\n" + 
											"\t<style type=\"text/css\">\n";
			return header;
		}

		private string css() {
			return ((Gtk.Mate.Buffer) this.view.buffer).parser.colourer.theme.name;
		}

		private string html() {
			return "";
		}
	}
}
