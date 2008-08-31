
using Gee;
using GLib;

namespace Gtk.Mate {
	public class Colourer : Object {
		public Buffer buffer {get; set;}
		public Theme theme {get; set;}

		public Colourer(Gtk.Mate.Buffer buffer) {
			this.buffer = buffer;
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
					stdout.printf("  no pattern name\n");
					continue;
				}
				if (scope.is_coloured) {
					stdout.printf("  already coloured\n");
					continue;
				}
				colour_scope(scope, false);
				if (scope.pattern is DoublePattern && ((DoublePattern) scope.pattern).content_name != null)
					colour_scope(scope, true);
			}
		}

		public void colour_scope(Scope scope, bool inner) {
			stdout.printf("  colouring %s\n", scope.name);
			int priority = scope.priority();
			TextTag tag;
			TextIter start_iter, end_iter;

			stdout.printf("  priority: %d\n", priority);
			scope.is_coloured = true;

			if (inner) {
				start_iter = buffer.iter_from_mark(scope.inner_start_mark);
				end_iter = buffer.iter_from_mark(scope.inner_end_mark);
				if (scope.inner_tag != null) {
					tag = scope.inner_tag;
				}
			}
			else {
				start_iter = buffer.iter_from_mark(scope.start_mark);
				end_iter = buffer.iter_from_mark(scope.end_mark);
				if (scope.tag != null) {
					tag = scope.tag;
				}
			}
			// TODO: allow for multiple settings that set different 
			// parts of the style.
			ThemeSetting setting;
			string tag_name;
			if (tag == null) {
				setting = theme.settings_for_scope(scope, false);
				if (setting == null) {
					tag_name = "gmv(%d):default".printf(priority-1);
				}
				else {
					tag_name = "gmv(%d):%s".printf(priority-1, scope.name);
				}
			}

			var tag_table = buffer.get_tag_table();
			if (tag == null) {
				tag = tag_table.lookup(tag_name);
				if (tag == null) {
					tag = buffer.create_tag(tag_name);
				}
			}
			stdout.printf("      tag: '%s'\n", tag_name);
			if (setting != null)
				set_tag_properties(scope, tag, setting);
			
			if (inner)
				scope.inner_tag = tag;
			else
				scope.tag = tag;
			
			buffer.apply_tag(tag, start_iter, end_iter);
		}

		public static void set_tag_properties(Scope scope, TextTag tag, ThemeSetting setting) {
			string font_style = setting.settings.get("fontStyle");
			if (font_style == "italic")
				tag.style = Pango.Style.ITALIC;
			else
				tag.style = Pango.Style.NORMAL;

			if (font_style == "underline")
				tag.style = Pango.Underline.SINGLE;
			else
				tag.style = Pango.Underline.NONE;
			
			string foreground = setting.settings.get("foreground");
			if (foreground != null && foreground != "") {
				tag.foreground = foreground;
			}
			string background = setting.settings.get("background");
			if (background != null && background != "") {
				var parent_bg = scope.nearest_background_colour();
				var merged_colour = Colourer.merge_colour(parent_bg, background);
				if (merged_colour != null) {
					scope.bg_colour = merged_colour;
					tag.background = merged_colour;
				}
			}
		}

		public static int char_to_hex(unichar ch) {
			if (ch.isxdigit()) {
				return ch.xdigit_value();
			}
			return 0;
		}
		
        // Here parent_colour is like '#FFFFFF' and
        // colour is like '#000000DD'.
		public static string? merge_colour(string parent_colour, string colour) {
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
				stdout.printf("%s/%s/%s - %d,%d,%d\n", parent_colour, colour, new_colour, new_r, new_g, new_b);
				return new_colour;
			}
			return "#000000";
		}

		public void uncolour_scopes(ArrayList<Scope> scopes) {
			foreach (var scope in scopes)
				uncolour_scope(scope, true);
		}
		
		public void uncolour_scope(Scope scope, bool recurse) {
			stdout.printf("uncolour scope: %s\n", scope.name);
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