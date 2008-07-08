
using Gee;

namespace Gtk.Mate {

	public class Grammar : Object {
		public string name {get; private set;}
		public PList.Dict plist {get; private set;}
		public string[] file_types;
		public Oniguruma.Regex first_line_match;
		public string key_equivalent;
		public string scope_name;
		public string comment;

		public Grammar(PList.Dict plist) {
			this.plist = plist;
		}

		public void init_for_reference() {
			PList.Node? nm = plist.get("name");
			if (nm != null) {
				name = ((PList.String) nm).str;
			}
			PList.Node? flm = plist.get("firstLineMatch");
			if (flm != null) {
				first_line_match = Oniguruma.Regex.make1(((PList.String) flm).str);
			}
			PList.Node? ke = plist.get("keyEquivalent");
			if (ke != null) {
				key_equivalent = ((PList.String) ke).str;
			}
			PList.Node? sn = plist.get("scopeName");
			if (sn != null) {
				scope_name = ((PList.String) sn).str;
			}
			PList.Node? cm = plist.get("comment");
			if (cm != null) {
				comment = ((PList.String) cm).str;
			}
			stdout.printf("%s     %s.\n", name, scope_name);
			PList.Node? filetypes = plist.get("fileTypes");
			if (filetypes != null) {
				PList.Array fts = (PList.Array) filetypes;
				file_types = new string[fts.array.size];
				int i = 0;
				foreach (var n in fts.array) {
					file_types[i++] = ((PList.String) n).str;
				}
			}
		}

		public void init_for_use() {
			
		}
	}

}