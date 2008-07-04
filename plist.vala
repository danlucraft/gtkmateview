
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
		public string item;
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
		PList.parse_dict(this, top_node);
        //free the document
        delete xml_doc;
	}

	public static void parse_dict(PList dict, Xml.Node* node) {
		stdout.printf("parsing dictionary\n");
		string key;
        for (Xml.Node* iter = node->children; iter != null; iter = iter->next) {
            if (iter->type != ElementType.ELEMENT_NODE)
                continue;
			if (key == null)
				key = iter->get_content();
			else {
				stdout.printf("child node: %s -> %s\n", key, iter->name);
				if (iter->name == "string") {
					stdout.printf("set(%s, %s)", key, iter->get_content());
					// dict.set(key, iter->get_content());
				}
				if (iter->name == "dict") {
					parse_dict(dict, iter);
				}
				key = null;
			}
        }
	}

	public PList(string filename) {
		this.filename = filename;
	}

	public static void main (string[] args) {
		stdout.printf("%s\n", args[1]);
		PList pl = new PList(args[1]);
		try {
			pl.parse();
		}
		catch (XmlError e) {}
	}
}