/* gtkmateview.vapi generated by valac, do not modify. */

[CCode (cprefix = "PList", lower_case_cprefix = "plist_")]
namespace PList {
	[CCode (cheader_filename = "plist.h")]
	public class Node : GLib.Object {
		public static PList.Node? parse_xml_node (Xml.Node* node);
		public Node ();
	}
	[CCode (cheader_filename = "plist.h")]
	public class String : PList.Node {
		public string str;
		public String ();
	}
	[CCode (cheader_filename = "plist.h")]
	public class Array : PList.Node {
		public Gee.ArrayList<PList.Node> array;
		public PList.Node get (int ix);
		public static PList.Array parse_array (Xml.Node* node);
		public Array ();
	}
	[CCode (cheader_filename = "plist.h")]
	public class Dict : PList.Node {
		public Gee.HashMap<string,PList.Node> map;
		public PList.Node get (string key);
		public string[] keys ();
		public void print_keys ();
		public static PList.Dict parse_dict (Xml.Node* node);
		public Dict ();
	}
	[CCode (cheader_filename = "plist.h")]
	public static PList.Dict parse (string filename) throws XmlError;
	[CCode (cheader_filename = "plist.h")]
	public static void print_plist (int indent, PList.Node node);
	[CCode (cheader_filename = "plist.h")]
	public static void main (string[] args);
}
[CCode (cprefix = "XML_ERROR_", cheader_filename = "plist.h")]
public errordomain XmlError {
	FILE_NOT_FOUND,
	XML_DOCUMENT_EMPTY,
}
