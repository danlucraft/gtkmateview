
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
	public class Node : Object {
		public static Node? parse_xml_node(Xml.Node* node) {
			if (node->name == "string") {
				var string_node = new String();
				string_node.str = node->get_content();
				return string_node;
			}
			if (node->name == "integer") {
				var int_node = new Integer();
				int_node.value = (node->get_content()).to_int();
				return int_node;
			}
			if (node->name == "dict") {
				return Dict.parse_dict(node);
			}
			if (node->name == "array") {
				return Array.parse_array(node);
			}
			return null;
		}
	}

	public class String : Node {
		public string str;
	}

	public class Integer : Node {
		public int value;
	}

	public class Array : Node {
		public ArrayList<Node> array;

		construct {
			this.array = new ArrayList<Node>();
		}

		public Node get(int ix) {
			return this.array.get(ix);
		}

		public static Array parse_array(Xml.Node* node) {
			var array = new Array();
			for (Xml.Node* iter = node->children; iter != null; iter = iter->next) {
				if (iter->type != ElementType.ELEMENT_NODE)
					continue;
				array.array.add(Node.parse_xml_node(iter));
			}
			return array;
		}
	}

	public class Dict : Node {
		public HashMap<string, Node> map;

		construct {
			this.map = new HashMap<string, Node>(str_hash, str_equal);
		}
		
		public Node get(string key) {
			return this.map.get(key);
		}

		public string[] keys() {
			string[] ks = new string[this.map.get_keys().size];
			int i = 0;
			foreach(string s in this.map.get_keys()) {
				ks[i] = s;
				i += 1;
			}
			return ks;
		}

		public void print_keys() {
			foreach(string s in this.keys())
				stdout.printf("key: %s\n", s);
		}

		public static Dict parse_dict(Xml.Node* node) {
			var dict = new Dict();
			string key = null;
			for (Xml.Node* iter = node->children; iter != null; iter = iter->next) {
				if (iter->type != ElementType.ELEMENT_NODE)
					continue;
				if (key == null)
					key = iter->get_content();
				else {
					dict.map.set(key, Node.parse_xml_node(iter));
					key = null;
				}
			}
			return dict;
		}
	}

	public static Dict? parse(string filename) throws FileError {
		string file_contents;
		ulong len;
		FileUtils.get_contents(filename, out file_contents, out len);
		
		// libxml doesn't like vertical tabs 
		file_contents = StringHelper.gsub(file_contents, "\v", "");
		
		if (!file_contents.validate()) {
			stdout.printf("%s contents not UTF-8\n", filename);
			return null;
		}
		
		Xml.Doc* xml_doc = Xml.Parser.parse_memory (file_contents, (int) len);
		if (xml_doc == null) {
//			throw new XmlError.FILE_NOT_FOUND ("file "+ filename + " not found or permissions missing");
			return null;
		}

		Xml.Node* root_node = xml_doc->get_root_element ();
		if (root_node == null) {
			// free the document manually before throwing because the garbage collector can't work on pointers
			delete xml_doc;
			stdout.printf("XML document is empty when opening %s\n", filename);
			return null;
		}
		Xml.Node* top_node = null;

		for (Xml.Node* iter = root_node->children; iter != null; iter = iter->next) {
			if (iter->type != ElementType.ELEMENT_NODE)
				continue;
			top_node = iter;
		}

		if (top_node->name != "dict") {
			stdout.printf("error top node is not a dict");
		}

		var dict = PList.Dict.parse_dict(top_node);

		//free the document
		delete xml_doc;
		return dict;
	}

	public static void print_plist(int indent, Node node) {
		string str_indent = string.nfill(indent * 2, ' ');
		if (node is String) {
			stdout.printf("%s%s,\n", str_indent, ((String) node).str);
		}
		if (node is Dict) {
			stdout.printf("%s{\n", str_indent);
			str_indent = string.nfill((indent+1)*2, ' ');
			foreach(string key in ((Dict) node).map.get_keys()) {
				stdout.printf("%s%s => ", str_indent, key);
				Node value = ((Dict) node).map.get(key);
				if (value is String)
					stdout.printf("\"%s\",\n", ((String) value).str);
				else {
					stdout.printf("\n");
					print_plist(indent+1, value);
				}
			}
			str_indent = string.nfill(indent*2, ' ');
			stdout.printf("%s},\n", str_indent);
		}
		if (node is Array) {
			stdout.printf("%s[\n", str_indent);
			str_indent = string.nfill((indent+1)*2, ' ');
			foreach(Node sub_node in ((Array) node).array) {
				print_plist(indent+1, sub_node);
			}
			str_indent = string.nfill(indent*2, ' ');
			stdout.printf("%s],\n", str_indent);
		}
	}
}
