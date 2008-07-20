
using Gee;
using GLib;

namespace Gtk.Mate {
	public class Parser : Object {
		public Grammar grammar {get; set;}
		public Mate.Buffer buffer {get; set;}

		public Mate.Scope root;

		public void make_root() {
			this.root = new Scope();
			this.root.name = this.grammar.scope_name;
		}

		public Parser() {}
		
		public static Parser create(Grammar grammar, Mate.Buffer buffer) {
			var p = new Parser();
			p.grammar = grammar;
			grammar.init_for_use();
			p.buffer = buffer;
			p.make_root();
			return p;
		}
	}
}