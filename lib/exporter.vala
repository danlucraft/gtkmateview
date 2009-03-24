
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
			result.append(code());
			result.append(body_end());
			return result.str;
		}

    private void add_indent(StringBuilder sb, int indent) {
 			for(int i = 0; i < indent; i++) {
				sb.append("\t");
			}
		}

		private string code() {
			var result = new StringBuilder();
			add_indent(result, 1);
			result.append("<pre class=\"textmate-source " + theme_name_css() + "\">");
			scope_to_html(result, buffer().parser.root);
			result.append("</pre>\n");
			return result.str;
		}		

		private string css_names(Scope scope, bool inner = false) {
			string this_name;
			if (scope.pattern is DoublePattern &&
				   ((DoublePattern) scope.pattern).content_name != null &&
				   inner) {
				this_name = ((DoublePattern) scope.pattern).content_name;
			}
			else {
				this_name = scope.name;
			}
			if (this_name != null) {
				string[] bits = this_name.split("."); // bits == ["meta", "class", "ruby"]
				string current = bits[0];
				var result = new StringBuilder();
				for(int i = 1; i < bits.length; i++ ) {
					result.append(current);
					current = current + "_" + bits[i];
					result.append(" ");
				}
				result.append(current);
				this_name = result.str;
			}
			return this_name;
		}

		private bool scope_has_inner(Scope scope) {
			return scope.pattern is DoublePattern && 
							((DoublePattern) scope.pattern).content_name != null && 
							((DoublePattern) scope.pattern).content_name != "";
		}

		private void scope_to_html(StringBuilder result, Scope scope) {
			string names = css_names(scope);
			if (names != "" && names != null)
				result.append("<span class=\"" + names + "\">");
			var position = scope.start_iter();
			bool opened_inner = false;
			bool closed_inner = false;
			if (scope.children.get_length() > 0) {
				GLib.SequenceIter iter = scope.children.get_begin_iter();
				Scope? child = null;
				while (!iter.is_end()) {
					if (scope_has_inner(scope)) {
						if (position.compare(scope.inner_start_iter()) >= 0 && !opened_inner) {
							string inner_names = css_names(scope, true);
						  result.append("<span class=\"" + inner_names + "\">");
							opened_inner = true;
						}
					}
					child = scope.children.get(iter);
					if (child.start_iter().compare(position) > 0) {
						result.append(Markup.escape_text(buffer().get_slice(position, child.start_iter(), true)));
						position = child.start_iter();
					}
					if (scope_has_inner(scope)) {
						if (position.compare(scope.inner_end_iter()) >= 0 && !closed_inner) {
							result.append("</span>");
							closed_inner = true;
						}
					}
					scope_to_html(result, child);
					position = child.end_iter();
					iter = iter.next();
				}
				if (child != null && child.end_iter().compare(scope.end_iter()) < 0) {
					result.append(Markup.escape_text(buffer().get_slice(child.end_iter(), scope.end_iter(), true)));
				}
			}
			else {
				result.append(Markup.escape_text(buffer().get_slice(scope.start_iter(), scope.end_iter(), true)));
			}
			if (names != "" && names != null)
				result.append("</span>");
			return;
		}

		private Buffer buffer() {
			return ((Gtk.Mate.Buffer) this.view.buffer);
		}

		private string theme_name() {
			return buffer().parser.colourer.theme.name;
		}
		
		private string theme_name_css() {
			return StringHelper.gsub(buffer().parser.colourer.theme.name.down(), " ", "_");
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
			string html = "\t</style>\n</head>\n\n<body>\n";
			return html;
		}
		
		private string body_end() {
			string html = "</body>\n</html>\n";
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
			result.append("/* Stylesheet generated from theme: " + theme_name() + " */\n\n");
			result.append("body {\n\tmargin: 0;\n\tpadding: 0;\n}\n\n");
			result.append("pre.textmate-source {\n\tmargin: 0;\n\tpadding: 0 0 0 2px;\n\tfont-family: Monaco, monospace;\n" + 
										"\tfont-size: 11px;\n\tline-height: 1.3em;\n\tword-wrap: break-word;\n\twhite-space: pre;\n" + 
										"\twhite-space: pre-wrap;\n\twhite-space: -moz-pre-wrap;\n\twhite-space: -o-pre-wrap;\n}\n\n");
			result.append("pre.textmate-source." + theme_name_css() + " {\n" + 
										"\tcolor: " + colourer.global_foreground_colour() + 
										";\n\tbackground-color: " + colourer.global_background_colour() + ";\n}\n\n");
			result.append("pre.textmate-source .linenum {\n");
			result.append("\twidth: 75px;\n");
			result.append("\tpadding: 0.1em 1em 0.2em 0;\n");
			result.append("\tcolor: #888;\n");
			result.append("\tbackground-color: #eee;\n");
			result.append("}\n\n");
			result.append("pre.textmate-source." + theme_name_css() + " span {\n");
			result.append("\tpadding-top: 0.2em;\n");
			result.append("\tpadding-bottom: 0.1em;\n");
			result.append("}\n\n");

			var selection_colour = colourer.theme.global_settings.get("selection");
			if (selection_colour != null && selection_colour != "") {
				result.append("pre.textmate-source." + theme_name_css() + " ::selection {\n");
				result.append(colour(selection_colour));
				result.append("}\n\n");
			}
			
			foreach(var setting in colourer.theme.settings) {
				result.append("/* " + setting.name + " */\n");
				result.append("pre.textmate-source." + theme_name_css() + " ." + 
				    StringHelper.gsub(StringHelper.gsub(StringHelper.gsub(setting.selector, 
									".", "_"), 
									" ", " ."),
									", ", ", pre.textmate-source." + theme_name_css() + " ") + " {\n");
				if (setting.settings.get("foreground") != null)
					result.append("\tcolor: " + setting.settings.get("foreground") + ";\n");
					
				string? font_style = setting.settings.get("fontStyle");
				if (font_style != null && font_style.str("italic") != null)
				  result.append("\tfont-style: italic;\n");
				if (font_style != null && font_style.str("underline") != null)
				  result.append("\ttext-decoration: underline;\n");
				if (font_style != null && font_style.str("bold") != null)
				  result.append("\tfont-weight: bold;\n");
						
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
