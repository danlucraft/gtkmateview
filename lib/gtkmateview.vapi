/* gtkmateview.vapi generated by valac, do not modify. */

[CCode (cprefix = "Gtk", lower_case_cprefix = "gtk_")]
namespace Gtk {
	[CCode (cprefix = "GtkMate", lower_case_cprefix = "gtk_mate_")]
	namespace Mate {
		[CCode (cheader_filename = "theme.h")]
		public class ThemeSetting : Gtk.Object {
			public string name;
			public string scope;
			public Gee.HashMap<string,string> settings;
			public static Gtk.Mate.ThemeSetting create_from_plist (PList.Dict dict);
			public ThemeSetting ();
		}
		[CCode (cheader_filename = "theme.h")]
		public class Theme : Gtk.Object {
			public static Gee.ArrayList<Gtk.Mate.Theme> themes;
			public string author;
			public string name;
			public Gee.HashMap<string,string> global_settings;
			public Gee.ArrayList<Gtk.Mate.ThemeSetting> settings;
			public static Gtk.Mate.Theme create_from_plist (PList.Dict dict);
			public static Gee.ArrayList<string>? theme_filenames ();
			public Theme ();
		}
		[CCode (cheader_filename = "pattern.h")]
		public class Pattern : Gtk.Object {
			public string name;
			public string comment;
			public static Gee.ArrayList<Gtk.Mate.Pattern> all_patterns;
			public static Gtk.Mate.Pattern? create_from_plist (Gee.ArrayList<Gtk.Mate.Pattern> all_patterns, PList.Dict pd);
			public static Gee.HashMap<int,string> make_captures_from_plist (PList.Dict? pd);
			public Pattern ();
		}
		[CCode (cheader_filename = "pattern.h")]
		public class SinglePattern : Gtk.Mate.Pattern {
			public Oniguruma.Regex match;
			public Gee.HashMap<int,string> captures;
			public static Gtk.Mate.SinglePattern? create_from_plist (Gee.ArrayList<Gtk.Mate.Pattern> all_patterns, PList.Dict pd);
			public SinglePattern ();
		}
		[CCode (cheader_filename = "pattern.h")]
		public class DoublePattern : Gtk.Mate.Pattern {
			public Oniguruma.Regex begin;
			public Oniguruma.Regex end;
			public string begin_string;
			public Gee.HashMap<int,string> begin_captures;
			public Gee.HashMap<int,string> end_captures;
			public Gee.ArrayList<Gtk.Mate.Pattern> patterns;
			public static Gtk.Mate.DoublePattern? create_from_plist (Gee.ArrayList<Gtk.Mate.Pattern> all_patterns, PList.Dict pd);
			public void replace_include_patterns (Gtk.Mate.Grammar g);
			public void replace_repository_includes (Gtk.Mate.Grammar g);
			public void replace_base_and_self_includes (Gtk.Mate.Grammar g);
			public DoublePattern ();
		}
		[CCode (cheader_filename = "pattern.h")]
		public class IncludePattern : Gtk.Mate.Pattern {
			public static Gtk.Mate.IncludePattern? create_from_plist (PList.Dict pd);
			public IncludePattern ();
		}
		[CCode (cheader_filename = "scope.h")]
		public class Scope : Gtk.Object {
			public Gtk.Mate.Pattern pattern;
			public Oniguruma.Match open_match;
			public Oniguruma.Match close_match;
			public Oniguruma.Regex closing_regex;
			public Gtk.TextMark start_mark;
			public Gtk.TextMark inner_start_mark;
			public Gtk.TextMark inner_end_mark;
			public Gtk.TextMark end_mark;
			public Gtk.TextTag tag;
			public Gtk.TextTag inner_tag;
			public bool is_open;
			public string bg_color;
			public bool is_capture;
			public Gtk.Mate.Scope parent;
			public GLib.StringBuilder pretty_string;
			public int indent;
			public Scope (Gtk.Mate.Buffer buf, string name);
			public bool is_root ();
			public static int compare (Gtk.Mate.Scope a, Gtk.Mate.Scope b);
			public string pretty (int indent);
			public void start_mark_set (int line, int line_offset, bool has_left_gravity);
			public void inner_start_mark_set (int line, int line_offset, bool has_left_gravity);
			public void inner_end_mark_set (int line, int line_offset, bool has_left_gravity);
			public void end_mark_set (int line, int line_offset, bool has_left_gravity);
			public int start_offset ();
			public int end_offset ();
			public string name { get; set; }
			public Gtk.Mate.Buffer buffer { get; set; }
			public GLib.Sequence<Gtk.Mate.Scope> children { get; }
		}
		[CCode (cheader_filename = "grammar.h")]
		public class Grammar : Gtk.Object {
			public string[] file_types;
			public Oniguruma.Regex first_line_match;
			public string key_equivalent;
			public string scope_name;
			public string comment;
			public Gee.ArrayList<Gtk.Mate.Pattern> all_patterns;
			public Oniguruma.Regex folding_start_marker;
			public Oniguruma.Regex folding_stop_marker;
			public Gee.ArrayList<Gtk.Mate.Pattern> patterns;
			public Gee.HashMap<string,Gee.ArrayList<Gtk.Mate.Pattern>> repository;
			public bool loaded;
			public Grammar (PList.Dict plist);
			public void init_for_reference ();
			public void init_for_use ();
			public string name { get; set; }
			public PList.Dict plist { get; set; }
		}
		[CCode (cheader_filename = "view.h")]
		public class View : Gtk.SourceView {
			public View ();
		}
		[CCode (cheader_filename = "buffer.h")]
		public class Buffer : Gtk.SourceBuffer {
			public static Gee.ArrayList<Gtk.Mate.Bundle> bundles;
			public static Gee.ArrayList<Gtk.Mate.Theme> themes;
			public Gtk.Mate.Parser parser;
			public int set_grammar_by_name (string name);
			public string? set_grammar_by_extension (string extension);
			public Gtk.TextIter iter_ (int offset);
			public Gtk.TextIter start_iter ();
			public Gtk.TextIter end_iter ();
			public Gtk.TextIter cursor_iter ();
			public Gtk.TextIter iter_from_mark (Gtk.TextMark mark);
			public Gtk.TextIter iter_at_line_offset (int line, int line_offset);
			public Gtk.TextIter line_start_iter (int line);
			public Gtk.TextIter line_end_iter (int line);
			public Gtk.TextIter line_end_iter1 (int line);
			public Gtk.TextMark start_mark ();
			public Gtk.TextMark end_mark ();
			public Gtk.TextMark cursor_mark ();
			public Gtk.TextMark selection_mark ();
			public string? get_line (int line);
			public int get_line_length (int line);
			public int cursor_line ();
			public int cursor_line_offset ();
			public int cursor_offset ();
			public Buffer ();
		}
		[CCode (cheader_filename = "parser.h")]
		public class Parser : Gtk.Object {
			public Gtk.Mate.Scope root;
			public RangeSet changes;
			public int deactivation_level;
			public static Gtk.Mate.Parser current;
			public void make_root ();
			public void stop_parsing ();
			public void start_parsing ();
			public bool is_parsing ();
			public void handle_captures (int line_ix, Gtk.Mate.Scope scope, Gtk.Mate.Marker m);
			public Oniguruma.Regex? make_closing_regex (Gtk.Mate.Marker m);
			public void collect_child_captures (int line_ix, Gtk.Mate.Scope scope, Gtk.Mate.Marker m);
			public void connect_buffer_signals ();
			public void insert_text_handler (Gtk.Mate.Buffer bf, Gtk.TextIter pos, string text, int length);
			public void delete_range_handler (Gtk.Mate.Buffer bf, Gtk.TextIter pos, Gtk.TextIter pos2);
			public void insert_text_after_handler (Gtk.Mate.Buffer bf, Gtk.TextIter pos, string text, int length);
			public void delete_range_after_handler (Gtk.Mate.Buffer bf, Gtk.TextIter pos, Gtk.TextIter pos2);
			public static void static_insert_text_after_handler (Gtk.Mate.Buffer bf, Gtk.TextIter pos, string text, int length);
			public static void static_delete_range_after_handler (Gtk.Mate.Buffer bf, Gtk.TextIter pos, Gtk.TextIter pos2);
			public static Gtk.Mate.Parser create (Gtk.Mate.Grammar grammar, Gtk.Mate.Buffer buffer);
			public Parser ();
			public Gtk.Mate.Grammar grammar { get; set; }
			public Gtk.Mate.Buffer buffer { get; set; }
		}
		[CCode (cheader_filename = "scanner.h")]
		public class Marker : Gtk.Object {
			public int from;
			public int hint;
			public bool is_close_scope;
			public Gtk.Mate.Pattern pattern;
			public Oniguruma.Match match;
			public Marker ();
		}
		[CCode (cheader_filename = "scanner.h")]
		public class Scanner : Gtk.Object, Gee.Iterable<Gtk.Mate.Marker> {
			public int position;
			public Gee.ArrayList<Gtk.Mate.Marker> cached_markers;
			public Scanner (Gtk.Mate.Scope s, string line, int line_length);
			public Gtk.Mate.Marker? get_cached_marker ();
			public void remove_preceding_cached_markers (Gtk.Mate.Marker m);
			public Oniguruma.Match? scan_for_match (int from, Gtk.Mate.Pattern p);
			public Gtk.Mate.Marker? find_next_marker ();
			public Gtk.Mate.Scope current_scope { get; set; }
			public string line { get; set; }
			public int line_length { get; set; }
			[CCode (cheader_filename = "scanner.h")]
			public class Iterator<Marker> : Gtk.Object, Gee.Iterator<Marker> {
				public Marker? next_marker;
				public Iterator (Gtk.Mate.Scanner s);
				public Gtk.Mate.Scanner scanner { get; set construct; }
			}
		}
		[CCode (cheader_filename = "bundle.h")]
		public class Bundle : Gtk.Object {
			public Gee.ArrayList<Gtk.Mate.Grammar> grammars;
			public Bundle (string name);
			public string name { get; set; }
		}
		[CCode (cheader_filename = "parser.h")]
		public struct TextLoc {
			public int line;
			public int line_offset;
			public static Gtk.Mate.TextLoc make (int l, int lo);
		}
		[CCode (cheader_filename = "gtkmateview.h")]
		public static int load_bundles ();
		[CCode (cheader_filename = "gtkmateview.h")]
		public static void load_themes ();
		[CCode (cheader_filename = "gtkmateview.h")]
		public static Gee.ArrayList<string>? bundle_dirs ();
		[CCode (cheader_filename = "gtkmateview.h")]
		public static string? textmate_share_dir ();
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
[CCode (cheader_filename = "range_set.h")]
public class RangeSet : GLib.Object, Gee.Iterable<RangeSet.Range> {
	public Gee.ArrayList<RangeSet.Range> ranges;
	public int length ();
	public int size ();
	public bool is_empty ();
	public void add (int a, int b);
	public void merge (int ix);
	public string present ();
	public int max (int a, int b);
	public int min (int a, int b);
	public RangeSet ();
	[CCode (cheader_filename = "range_set.h")]
	public class Range : GLib.Object {
		public int a;
		public int b;
		public Range ();
	}
}
