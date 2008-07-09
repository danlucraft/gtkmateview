/* gtkmateview.vapi generated by valac, do not modify. */

[CCode (cprefix = "Gtk", lower_case_cprefix = "gtk_")]
namespace Gtk {
	[CCode (cprefix = "GtkMate", lower_case_cprefix = "gtk_mate_")]
	namespace Mate {
		[CCode (cheader_filename = "grammar.h")]
		public class Grammar : Gtk.Object {
			public string[] file_types;
			public Oniguruma.Regex first_line_match;
			public string key_equivalent;
			public string scope_name;
			public string comment;
			public Grammar (PList.Dict plist);
			public void init_for_reference ();
			public void init_for_use ();
			public string name { get; set; }
			public PList.Dict plist { get; set; }
		}
		[CCode (cheader_filename = "gtkmateview.h")]
		public class Pattern : Gtk.Object {
			public Pattern ();
		}
		[CCode (cheader_filename = "gtkmateview.h")]
		public class Theme : Gtk.Object {
			public Theme ();
		}
		[CCode (cheader_filename = "gtkmateview.h")]
		public class SinglePattern : Gtk.Mate.Pattern {
			public SinglePattern ();
		}
		[CCode (cheader_filename = "gtkmateview.h")]
		public class DoublePattern : Gtk.Mate.Pattern {
			public DoublePattern ();
		}
		[CCode (cheader_filename = "bundle.h")]
		public class Bundle : Gtk.Object {
			public Gee.ArrayList<Gtk.Mate.Grammar> grammars;
			public Bundle (string name);
			public string name { get; set; }
		}
	}
	[CCode (cheader_filename = "gtkmateview.h")]
	public class MateView : Gtk.SourceView {
		public Gee.ArrayList<Gtk.Mate.Bundle> bundles;
		public Gee.ArrayList<Gtk.Mate.Theme> themes;
		public string? set_grammar_by_extension (string extension);
		public Gtk.TextIter iter_ (int offset);
		public Gtk.TextIter iter_line_start (int line);
		public static int load_bundles ();
		public static Gee.ArrayList<string>? bundle_dirs ();
		public static string? textmate_share_dir ();
		public static string[] bundle_dirs_rb ();
		public MateView ();
		public Gtk.Mate.Grammar grammar { get; set; }
	}
}
[CCode (cprefix = "Oniguruma", lower_case_cprefix = "oniguruma_")]
namespace Oniguruma {
	[CCode (cheader_filename = "onig_wrap.h")]
	public class OnigError : GLib.Object {
		public int code;
		public Oniguruma.OnigErrorInfo error_info;
		public OnigError ();
	}
	[CCode (cheader_filename = "onig_wrap.h")]
	public class Match : GLib.Object {
		public int begin (int capture);
		public int end (int capture);
		public Match ();
		public Oniguruma.RegexT rx { get; set; }
		public Oniguruma.Region rg { get; set; }
	}
	[CCode (cheader_filename = "onig_wrap.h")]
	public class Regex : GLib.Object {
		public Oniguruma.Match? search (string target, int start, int end);
		public static Oniguruma.Regex? make (string pattern, Oniguruma.OnigOptionType options, out Oniguruma.OnigError error);
		public static Oniguruma.Regex? make1 (string pattern);
		public Regex ();
		public Oniguruma.RegexT rx { get; set; }
	}
}
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
}
[CCode (cprefix = "XML_ERROR_", cheader_filename = "plist.h")]
public errordomain XmlError {
	FILE_NOT_FOUND,
	XML_DOCUMENT_EMPTY,
}
