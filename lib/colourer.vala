
using Gee;
using GLib;

namespace Gtk.Mate {
	public class Colourer : Object {
		public Buffer buffer {get; set;}
		public Theme theme {get; set;}
		
		public void set_global_settings(Gtk.Mate.View view) {
			//stdout.printf("set_theme_settings()\n");
			string bg_colour = theme.global_settings.get("background");
			if (bg_colour != null && bg_colour != "") {
				bg_colour = Colourer.merge_colour("#FFFFFF", bg_colour);
				stdout.printf("bg_colour: %s\n", bg_colour);
				((Gtk.Widget) view).modify_base(Gtk.StateType.NORMAL, parse_colour(bg_colour));
				// ((Gtk.SourceView) view).background = bg_colour;
			}

			string fg_colour = theme.global_settings.get("foreground");
			if (fg_colour != null && fg_colour != "") {
				fg_colour = Colourer.merge_colour("#FFFFFF", fg_colour);
				((Gtk.Widget) view).modify_text(Gtk.StateType.NORMAL, parse_colour(fg_colour));
			}
		}

		public Colourer(Gtk.Mate.Buffer buffer) {
			this.buffer = buffer;
		}

		public Gdk.Color parse_colour(string colour) {
			Gdk.Color c;
			Gdk.Color.parse(colour, out c);
			return c;
		}

		public void colour_line_with_scopes(ArrayList<Scope> scopes) {
			if (theme == null)
				return;
			foreach (var scope in scopes) {
				if (scope.parent == null) {
					continue;
				}
				if (scope.name == null && scope.pattern != null &&
					(scope.pattern is SinglePattern || ((DoublePattern) scope.pattern).content_name == null)) {
					//stdout.printf("  no pattern name\n");
					continue;
				}
				// if (scope.is_coloured) {
				// 	//stdout.printf("  already coloured\n");
				// 	continue;
				// }
				colour_scope(scope, false);
				if (scope.pattern is DoublePattern && ((DoublePattern) scope.pattern).content_name != null)
					colour_scope(scope, true);
			}
		}

		public void colour_scope(Scope scope, bool inner, bool force=true) {
	//		stdout.printf("colour_scope: %s (%s) [%d - %d]\n", scope.name, inner ? "true" : "false",
 	//	 			  scope.start_offset(), scope.end_offset());
			int priority = scope.priority(inner);
			TextTag tag = null;
			TextIter start_iter, end_iter;

//			stdout.printf("  priority: %d\n", priority);
			scope.is_coloured = true;

			if (inner) {
				start_iter = scope.inner_start_iter();
				end_iter = scope.inner_end_iter();
				if (scope.inner_tag != null) {
					tag = scope.inner_tag;
				}
			}
			else {
				start_iter = scope.start_iter();
				end_iter = scope.end_iter();
				if (scope.tag != null) {
					tag = scope.tag;
				}
			}
			// TODO: allow for multiple settings that set different 
			// parts of the style.
			ThemeSetting setting = null;
			ThemeSetting exclude_setting = null;
			if (scope.parent != null) 
				exclude_setting = scope.parent.theme_setting;
			string tag_name = null;
			if (tag == null || force) {
				setting = theme.settings_for_scope(scope, inner, null);//exclude_setting);
				if (setting == null) {
					tag_name = "gmv(%d):default".printf(priority-1);
				}
				else {				
					scope.theme_setting = setting;
					tag_name = "gmv(%d):%s".printf(priority-1, scope.name);
				}
			}

			var tag_table = buffer.get_tag_table();
			bool new_tag = false;
			if (tag == null || force) {
				tag = tag_table.lookup(tag_name);
				if (tag == null) {
					// stdout.printf("create_tag\n");
					tag = buffer.create_tag(tag_name);
					new_tag = true;
				}
			}
			// stdout.printf("      tag: '%s'\n", tag_name);
			if (setting != null)
				set_tag_properties(scope, tag, setting);
			
			if (inner)
				scope.inner_tag = tag;
			else
				scope.tag = tag;
			
			buffer.apply_tag(tag, start_iter, end_iter);

			if (new_tag) {
				buffer.parser.added_tag(tag);
			}
		}

		public void set_tag_properties(Scope scope, TextTag tag, ThemeSetting setting) {
			string font_style = setting.settings.get("fontStyle");
			if (font_style == "italic") {
				tag.style = Pango.Style.ITALIC | tag.style;
			}
			else
				tag.style = Pango.Style.NORMAL | tag.style;

			if (font_style == "underline")
				tag.underline = Pango.Underline.SINGLE;
			else
				tag.underline = Pango.Underline.NONE;
			
			string background = setting.settings.get("background");
//			stdout.printf("        scope background:        %s\n", background);
			string merged_bg_colour;
			var parent_bg = theme.global_settings.get("background");
//			stdout.printf("        global background: %s\n", parent_bg);
			// TODO: wasn't this a better way of creating the background colours?
//			var parent_bg = scope.nearest_background_colour();
//			if (parent_bg == null) {
//			}
//			else {
//				stdout.printf("        parent background: %s\n", parent_bg);
//			}
			if (background != null && background != "") {
//				if (parent_bg != null) {
//					merged_bg_colour = parent_bg;
//				}
//				else {
					merged_bg_colour = Colourer.merge_colour(parent_bg, background);
//				}
				if (merged_bg_colour != null) {
					scope.bg_colour = merged_bg_colour;
					tag.background = merged_bg_colour;
//					stdout.printf("       tag.background = %s\n", merged_bg_colour);
				}
			}
			else {
				merged_bg_colour = parent_bg;
			}
//			stdout.printf("        merged_bg_colour:  %s\n", merged_bg_colour);
			string foreground = setting.settings.get("foreground");
//			stdout.printf("        scope foreground:        %s\n", foreground);
			var parent_fg = scope.nearest_foreground_colour();
			if (parent_fg == null) {
				parent_fg = theme.global_settings.get("foreground");
//				stdout.printf("        global foreground:        %s\n", parent_fg);
			}
			if (foreground != null && foreground != "") {
				string merged_fg_colour;
				if (parent_fg != null && !scope.is_capture)
					merged_fg_colour = Colourer.merge_colour(parent_fg, foreground);
				else
					merged_fg_colour = foreground;
				if (merged_fg_colour != null) {
					scope.fg_colour = merged_fg_colour;
					tag.foreground = merged_fg_colour;
				}
//				stdout.printf("       merged_fg_colour: %s\n", merged_fg_colour);
			}
//			stdout.printf("\n");
		}

		public static int char_to_hex(unichar ch) {
			if (ch.isxdigit()) {
				return ch.xdigit_value();
			}
			return 0;
		}
		
        // Here parent_colour is like '#FFFFFF' and
        // colour is like '#000000DD'.
		public static string? merge_colour(string? parent_colour, string colour) {
			int pre_r, pre_g, pre_b;
			int post_r, post_g, post_b;
			int opacity;
			int new_r, new_g, new_b;
			string new_colour = null;
			if (parent_colour == null)
				return null;
			if (colour.length == 7)
				return colour;
			if (colour.length == 9) {
				pre_r = char_to_hex(parent_colour[1])*16+char_to_hex(parent_colour[2]);
				pre_g = char_to_hex(parent_colour[3])*16+char_to_hex(parent_colour[4]);
				pre_b = char_to_hex(parent_colour[5])*16+char_to_hex(parent_colour[6]);
				
				post_r = char_to_hex(colour[1])*16+char_to_hex(colour[2]);
				post_g = char_to_hex(colour[3])*16+char_to_hex(colour[4]);
				post_b = char_to_hex(colour[5])*16+char_to_hex(colour[6]);
				opacity = char_to_hex(colour[7])*16+char_to_hex(colour[8]);
				
				new_r = (pre_r*(255-opacity) + post_r*opacity)/255;
				new_g = (pre_g*(255-opacity) + post_g*opacity)/255;
				new_b = (pre_b*(255-opacity) + post_b*opacity)/255;
				new_colour = "#%.2x%.2x%.2x".printf(new_r, new_g, new_b);
				// stdout.printf("%s/%s/%s - %d,%d,%d\n", parent_colour, colour, new_colour, new_r, new_g, new_b);
				return new_colour;
			}
			return "#000000";
		}

		public void uncolour_scopes(ArrayList<Scope> scopes) {
			foreach (var scope in scopes)
				uncolour_scope(scope, true);
		}
		
		public void uncolour_scope(Scope scope, bool recurse) {
			// stdout.printf("uncolour scope: %s\n", scope.name);
			if (scope.inner_tag != null) {
				buffer.remove_tag(scope.inner_tag, scope.inner_start_iter(), scope.inner_end_iter());
			}
			if (scope.tag != null) {
				buffer.remove_tag(scope.tag, scope.start_iter(), scope.end_iter());
			}
			scope.is_coloured = false;
			if (recurse) {
				GLib.SequenceIter iter = scope.children.get_begin_iter();
				while (!iter.is_end()) {
					uncolour_scope(scope.children.get(iter), recurse);
					iter = iter.next();
				}
			}
		}
	}
}
