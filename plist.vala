
// PList reader in Vala
// valac -o plist --pkg libxml-2.0 --pkg gee-1.0 plist.vala

using GLib;
using Gee;

using Xml;

public errordomain XmlError {
    FILE_NOT_FOUND,
    XML_DOCUMENT_EMPTY
}

namespace PList {
	public class Node {
	}

	public class String : Node {
		public string str;
	}

	public class Array : ArrayList<Node> {
	}

	public class Dict : HashMap<string, Node> {
		public string filename {get; set;}
		
		public void parse() throws XmlError {
			stdout.printf("filename: %s\n", this.filename);
			Xml.Doc* xml_doc = Xml.Parser.parse_file (this.filename);
			if (xml_doc == null) {
				throw new XmlError.FILE_NOT_FOUND ("file "+ this.filename + " not found or permissions missing");
			}

			Xml.Node* root_node = xml_doc->get_root_element ();
			if (root_node == null) {
				//free the document manually before throwing because the garbage collector can't work on pointers
				delete xml_doc;
				throw new XmlError.XML_DOCUMENT_EMPTY ("the xml'"+ this.filename + "' is empty");
			}
			Xml.Node* top_node;

			for (Xml.Node* iter = root_node->children; iter != null; iter = iter->next) {
				stdout.printf("child node:  %s\n", iter->name);
				if (iter->type != ElementType.ELEMENT_NODE)
					continue;
				top_node = iter;
			}
			stdout.printf("root node: %s\n", root_node->name);
			stdout.printf("top node:  %s\n", top_node->name);
			if (top_node->name != "dict") {
				stdout.printf("error top node is not a dict");
			}
			PList.Dict.parse_dict(this, top_node);
			//free the document
			delete xml_doc;
		}

		public static void parse_dict(Dict dict, Xml.Node* node) {
			stdout.printf("parsing dictionary\n");
			string key;
			String string_node;
			for (Xml.Node* iter = node->children; iter != null; iter = iter->next) {
				if (iter->type != ElementType.ELEMENT_NODE)
					continue;
				if (key == null)
					key = iter->get_content();
				else {
					stdout.printf("child node: %s -> %s\n", key, iter->name);
					if (iter->name == "string") {
						string_node = new String();
						string_node.str = iter->get_content();
						stdout.printf("set(%s, %s)", key);
						dict.set(key, string_node);
					}
//					if (iter->name == "dict") {
//						parse_dict(dict, iter);
//					}
					key = null;
				}
			}
		}

		public Dict(HashFunc f1, EqualFunc f2) {
			
		}

		public static void main (string[] args) {
			stdout.printf("%s\n", args[1]);
			// HashMap<string, Node> foo = new HashMap<string, Node>(str_hash, str_equal);
			// String string_node = new String();
			// string_node.str = "barbar";
			// stdout.printf("%s:%s\n", "foo", string_node.str);
			// foo.set("foo", string_node);
			// stdout.printf("out: %s\n", ((String) foo.get("foo")).str);
			PList.Dict pl = new PList.Dict(str_hash, str_equal);
			pl.filename = args[1];
			try {
				pl.parse();
			}
			catch (XmlError e) {}
		}
	}
}