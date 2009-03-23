
using GLib;
using Gee;

namespace Gtk.Mate {
	public class Exporter : Object {
		public View view;

		public Exporter(View v) {
			this.view = v;
		}

		public string to_html(string title) {
			var result = new StringBuilder();
			result.append(html_header(title));
			result.append(css());
			result.append(body_start());
			result.append(body_end());
			return result.str;
		}

		private string html_header(string title) {
			string header = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\">\n" + 
                      "<head>\n" + 
   										"\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n" + 
											"\t<title>" + title + "</title>\n" + 
											"\t<style type=\"text/css\">\n";
			return header;
		}
		
		private string body_start() {
			string html = "\t</style>\n</head>\n\n<body>";
			return html;
		}
		
		private string body_end() {
			string html = "</body>\n</html>";
			return html;
		}
		
		private string colour(string colour) {
			var result = new StringBuilder();
			if (colour.length == 9) {
				result.append("\tbackground-color: rgba(");
				result.append("%d".printf(Colourer.hex_to_int(colour[1], colour[2])) + ", ");
				result.append("%d".printf(Colourer.hex_to_int(colour[3], colour[4])) + ", ");
				result.append("%d".printf(Colourer.hex_to_int(colour[5], colour[6])) + ", ");
				result.append("%0.2f".printf(((double) Colourer.hex_to_int(colour[7], colour[8]))/256.0));
				result.append(");\n");
			}
			else if (colour.length == 7) {
				result.append("\tbackground-color: " + colour + ";\n");
			}
			return result.str;
		}
		
		private string css() {
			Colourer colourer = ((Gtk.Mate.Buffer) this.view.buffer).parser.colourer;
			var result = new StringBuilder();
			string theme_name = colourer.theme.name;
			result.append("/* Stylesheet generated from theme: " + theme_name + " */\n\n");
			result.append("body {\n\tmargin: 0;\n\tpadding: 0;\n}\n\n");
			result.append("pre.textmate-source {\n\tmargin: 0;\n\tpadding: 0 0 0 2px;\n\tfont-family: Monaco, monospace;\n" + 
										"\tfont-size: 11px;\n\tline-height: 1.3em;\n\tword-wrap: break-word;\n\twhite-space: pre;\n" + 
										"\twhite-space: pre-wrap;\n\twhite-space: -moz-pre-wrap;\n\twhite-space: -o-pre-wrap;\n}\n\n");
			result.append("pre.textmate-source." + theme_name.down() + " {\n" + 
										"\tcolor: " + colourer.global_foreground_colour() + 
										";\n\tbackground-color: " + colourer.global_background_colour() + ";\n}\n\n");
			result.append("pre.textmate-source .linenum {\n");
			result.append("\twidth: 75px;\n");
			result.append("\tpadding: 0.1em 1em 0.2em 0;\n");
			result.append("\tcolor: #888;\n");
			result.append("\tbackground-color: #eee;\n");
			result.append("}\n\n");
			result.append("pre.textmate-source." + theme_name.down() + " span {\n");
			result.append("\tpadding-top: 0.2em;\n");
			result.append("\tpadding-bottom: 0.1em;\n");
			result.append("}\n\n");

			var selection_colour = colourer.theme.global_settings.get("selection");
			if (selection_colour != null && selection_colour != "") {
				result.append("pre.textmate-source." + theme_name.down() + " ::selection {\n");
				result.append(colour(selection_colour));
				result.append("}\n\n");
			}

			foreach(var setting in colourer.theme.settings) {
				result.append("/* " + setting.name + " */\n");
				result.append("pre.textmate-source." + theme_name.down() + " ." + 
				    StringHelper.gsub(StringHelper.gsub(StringHelper.gsub(setting.selector, 
									".", "_"), 
									" ", " ."),
									", ", ", pre.textmate-source." + theme_name.down() + " ") + " {\n");
				if (setting.settings.get("foreground") != null)
					result.append("\tcolor: " + setting.settings.get("foreground") + ";\n");
				if (setting.settings.get("fontStyle") == "italic")
				  result.append("\tfont-style: italic;\n");
				var bg_colour = setting.settings.get("background");
				if (bg_colour != null) {
					result.append(colour(bg_colour));
				}
				result.append("}\n\n");
			}
			return result.str;
		}

		private string html() {
			return "";
		}
	}
}
