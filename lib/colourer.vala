
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
				stdout.printf("colouring scope: %s\n", scope.name);
				if (scope.parent == null) {
					stdout.printf("  no parent\n");
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

		public void colour_scope(Scope scope, bool colour_inner) {
			stdout.printf("  colouring\n");
			int priority = scope.priority();
			TextTag tag;

			stdout.printf("  priority: %d\n", priority);
			scope.is_coloured = true;

			if (colour_inner) {
				var start_iter = buffer.iter_from_mark(scope.inner_start_mark);
				var end_iter = buffer.iter_from_mark(scope.inner_end_mark);
				if (scope.inner_tag != null) {
					tag = scope.inner_tag;
				}
			}
			else {
				var start_iter = buffer.iter_from_mark(scope.start_mark);
				var end_iter = buffer.iter_from_mark(scope.end_mark);
				if (scope.tag != null) {
					tag = scope.tag;
				}
			}
			if (tag == null) {
				ArrayList<ThemeSetting> settings = theme.settings_for_scope(scope);
			}
		}
	}
}