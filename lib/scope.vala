
using Gee;
using GLib;

namespace Gtk.Mate {
	public class Scope : Object {
		public Pattern pattern;
		public string name;

		public Oniguruma.Match open_match;
		public Oniguruma.Match close_match;
		public Oniguruma.Regex closing_regex;

		public SourceMark start_mark;
		public SourceMark inner_start_mark;
		public SourceMark inner_end_mark;
		public SourceMark end_mark;
		public TextTag tag;
		public TextTag inner_tag;

		public string bg_color;
		public bool is_capture;

		public ArrayList<Scope> children;
		public Scope parent;

		public bool is_root() {
			if (parent == null)
				return true;
			return false;
		}

		public string pretty(int indent) {
			var s = new StringBuilder("");
			for (int i = 0; i < indent; i++)
				s.append("  ");
			s.append(name+" (");
			if (start_mark == null)
				s.append("inf");
			s.append(")-(");
			if (end_mark == null)
				s.append("inf");
			s.append(")\n");
			if (children != null)
				foreach (var ss in children)
					s.append(ss.pretty(indent+1));
			return s.str;
		}
	}
}