
using Gee;

namespace Gtk.Mate {
	public class Bundle : Object {
		public string name {get; private set;}
		public ArrayList<Grammar> grammars;
		
		construct {
			this.grammars = new ArrayList<Grammar>();
		}
		
		public Bundle(string name) {
			this.name = name;
		}
	}
}