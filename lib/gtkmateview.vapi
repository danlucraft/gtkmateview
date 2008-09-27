/* gtkmateview.vapi generated by valac, do not modify. */

[CCode (cprefix = "Gtk", lower_case_cprefix = "gtk_")]
namespace Gtk {
	[CCode (cprefix = "GtkMate", lower_case_cprefix = "gtk_mate_")]
	namespace Mate {
		[CCode (cheader_filename = "theme.h")]
		public class ThemeSetting : Gtk.Object {
			public string name;
			public string selector;
			public Gee.HashMap<string,string> settings;
			public Gee.ArrayList<Gtk.Mate.Matcher> matchers;
			public static Gtk.Mate.ThemeSetting create_from_plist (PList.Dict dict);
			public void compile_scope_matchers ();
			public bool match (string scope, out Onig.Match match);
			public ThemeSetting ();
		}
		[CCode (cheader_filename = "theme.h")]
		public class Theme : Gtk.Object {
			public static Gee.ArrayList<Gtk.Mate.Theme> themes;
			public string author;
			public string name;
			public Gee.HashMap<string,string> global_settings;
			public Gee.ArrayList<Gtk.Mate.ThemeSetting> settings;
			public bool is_initialized;
			public Gee.HashMap<string,Gtk.Mate.ThemeSetting> cached_setting_for_scopes;
			public static Gtk.Mate.Theme create_from_plist (PList.Dict dict);
			public void init_for_use ();
			public static Gee.ArrayList<string>? theme_filenames ();
			public Gtk.Mate.ThemeSetting settings_for_scope (Gtk.Mate.Scope scope, bool inner);
			public Theme ();
		}
		[CCode (cheader_filename = "pattern.h")]
		public class Pattern : Gtk.Object {
			public string name;
			public string comment;
			public static Gee.ArrayList<Gtk.Mate.Pattern> all_patterns;
			public bool disabled;
			public static Gtk.Mate.Pattern? create_from_plist (Gee.ArrayList<Gtk.Mate.Pattern> all_patterns, PList.Dict pd);
			public static Gee.HashMap<int,string> make_captures_from_plist (PList.Dict? pd);
			public static void replace_include_patterns (Gee.ArrayList<Gtk.Mate.Pattern> patlist, Gtk.Mate.Grammar g);
			public static void replace_repository_includes (Gee.ArrayList<Gtk.Mate.Pattern> patlist, Gtk.Mate.Grammar g);
			public static void replace_base_and_self_includes (Gee.ArrayList<Gtk.Mate.Pattern> patlist, Gtk.Mate.Grammar g);
			public Pattern ();
		}
		[CCode (cheader_filename = "pattern.h")]
		public class SinglePattern : Gtk.Mate.Pattern {
			public Onig.Rx match;
			public Gee.HashMap<int,string> captures;
			public static Gtk.Mate.SinglePattern? create_from_plist (Gee.ArrayList<Gtk.Mate.Pattern> all_patterns, PList.Dict pd);
			public SinglePattern ();
		}
		[CCode (cheader_filename = "pattern.h")]
		public class DoublePattern : Gtk.Mate.Pattern {
			public string content_name;
			public Onig.Rx begin;
			public Onig.Rx end;
			public string end_string;
			public string begin_string;
			public Gee.HashMap<int,string> begin_captures;
			public Gee.HashMap<int,string> end_captures;
			public Gee.HashMap<int,string> both_captures;
			public Gee.ArrayList<Gtk.Mate.Pattern> patterns;
			public static Gtk.Mate.DoublePattern? create_from_plist (Gee.ArrayList<Gtk.Mate.Pattern> all_patterns, PList.Dict pd);
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
			public Onig.Match open_match;
			public Onig.Match close_match;
			public Onig.Rx closing_regex;
			public Gtk.TextMark start_mark;
			public Gtk.TextMark inner_start_mark;
			public Gtk.TextMark inner_end_mark;
			public Gtk.TextMark end_mark;
			public Gtk.TextTag tag;
			public Gtk.TextTag inner_tag;
			public bool is_open;
			public string bg_colour;
			public bool is_capture;
			public Gtk.Mate.TextLoc dummy_start_loc;
			public Gtk.Mate.TextLoc dummy_end_loc;
			public string begin_match_string;
			public string end_match_string;
			public Gtk.Mate.Scope parent;
			public GLib.StringBuilder pretty_string;
			public int indent;
			public Scope (Gtk.Mate.Buffer buf, string? name);
			public bool is_root ();
			public static int compare (Gtk.Mate.Scope a, Gtk.Mate.Scope b, void* data);
			public static int compare_by_loc (Gtk.Mate.Scope a, Gtk.Mate.Scope b, void* data);
			public bool surface_identical_to_modulo_ending (Gtk.Mate.Scope other);
			public bool surface_identical_to (Gtk.Mate.Scope other);
			public Gtk.Mate.Scope? scope_at (int line, int line_offset);
			public Gtk.Mate.Scope? first_child_after (Gtk.Mate.TextLoc loc);
			public bool contains_loc (Gtk.Mate.TextLoc loc);
			public bool overlaps_with (Gtk.Mate.Scope other);
			public void add_child (Gtk.Mate.Scope s);
			public void delete_child (Gtk.Mate.Scope s);
			public Gee.ArrayList<Gtk.Mate.Scope> delete_any_on_line_not_in (int line_ix, Gee.ArrayList<Gtk.Mate.Scope> scopes);
			public void clear_after (int line_ix, int line_offset);
			public string pretty (int indent);
			public void start_mark_set (int line, int line_offset, bool has_left_gravity);
			public void inner_start_mark_set (int line, int line_offset, bool has_left_gravity);
			public void inner_end_mark_set (int line, int line_offset, bool has_left_gravity);
			public void end_mark_set (int line, int line_offset, bool has_left_gravity);
			public Gtk.TextIter start_iter ();
			public Gtk.TextIter inner_start_iter ();
			public Gtk.TextIter inner_end_iter ();
			public Gtk.TextIter end_iter ();
			public int start_offset ();
			public int inner_start_offset ();
			public int inner_end_offset ();
			public int end_offset ();
			public int start_line ();
			public int inner_start_line ();
			public int inner_end_line ();
			public int end_line ();
			public int start_line_offset ();
			public int inner_start_line_offset ();
			public int inner_end_line_offset ();
			public int end_line_offset ();
			public Gtk.Mate.TextLoc start_loc ();
			public Gtk.Mate.TextLoc inner_start_loc ();
			public Gtk.Mate.TextLoc inner_end_loc ();
			public Gtk.Mate.TextLoc end_loc ();
			public Gtk.Mate.Scope root ();
			public int priority ();
			public string hierarchy_names (bool inner);
			public string? nearest_background_colour ();
			public string? name { get; set; }
			public Gtk.Mate.Buffer buffer { get; set; }
			public GLib.Sequence<Gtk.Mate.Scope> children { get; }
			public bool is_coloured { get; set; }
		}
		[CCode (cheader_filename = "grammar.h")]
		public class Grammar : Gtk.Object {
			public string[] file_types;
			public Onig.Rx first_line_match;
			public string key_equivalent;
			public string scope_name;
			public string comment;
			public Gee.ArrayList<Gtk.Mate.Pattern> all_patterns;
			public Onig.Rx folding_start_marker;
			public Onig.Rx folding_stop_marker;
			public Gee.ArrayList<Gtk.Mate.Pattern> patterns;
			public Gee.HashMap<string,Gee.ArrayList<Gtk.Mate.Pattern>> repository;
			public bool loaded;
			public Grammar (PList.Dict plist);
			public static Gtk.Mate.Grammar? find_by_scope_name (string scope);
			public void init_for_reference ();
			public void init_for_use ();
			public string name { get; set; }
			public PList.Dict plist { get; set; }
		}
		[CCode (cheader_filename = "view.h")]
		public class View : Gtk.SourceView {
			public bool set_theme_by_name (string name);
			public void set_global_theme_settings ();
			public View ();
		}
		[CCode (cheader_filename = "matcher.h")]
		public class Matcher : Gtk.Object {
			public Onig.Rx pos_rx;
			public Gee.ArrayList<Onig.Rx> neg_rxs;
			public static int compare_match (string scope_string, Onig.Match m1, Onig.Match m2);
			public static string test_rank (string selector_a, string selector_b, string scope_string);
			public static bool test_match (string selector_string, string scope_string);
			public static bool match (string selector_string, string scope_string, out Onig.Match match);
			public static Gee.ArrayList<Gtk.Mate.Matcher> compile (string selector_string);
			public static bool test_match_re (Onig.Rx positive_selector_regex, Gee.ArrayList<Onig.Rx> negative_selector_regex, string scope_string, out Onig.Match match);
			public Matcher ();
		}
		[CCode (cheader_filename = "buffer.h")]
		public class Buffer : Gtk.SourceBuffer {
			public static Gee.ArrayList<Gtk.Mate.Bundle> bundles;
			public static Gee.ArrayList<Gtk.Mate.Theme> themes;
			public Gtk.Mate.Parser parser;
			public bool set_grammar_by_name (string name);
			public string? set_grammar_by_filename (string filename);
			public string? set_grammar_by_first_line ();
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
			public string? get_line1 (int line_ix);
			public int get_line_length (int line);
			public int cursor_line ();
			public int cursor_line_offset ();
			public int cursor_offset ();
			public Buffer ();
		}
		[CCode (cheader_filename = "parser.h")]
		public class TextLoc : Gtk.Object {
			public int line;
			public int line_offset;
			public static Gtk.Mate.TextLoc make (int l, int lo);
			public static bool equal (Gtk.Mate.TextLoc t1, Gtk.Mate.TextLoc t2);
			public static bool gt (Gtk.Mate.TextLoc t1, Gtk.Mate.TextLoc t2);
			public static bool lt (Gtk.Mate.TextLoc t1, Gtk.Mate.TextLoc t2);
			public static bool gte (Gtk.Mate.TextLoc t1, Gtk.Mate.TextLoc t2);
			public static bool lte (Gtk.Mate.TextLoc t1, Gtk.Mate.TextLoc t2);
			public string to_s ();
			public TextLoc ();
		}
		[CCode (cheader_filename = "parser.h")]
		public class Parser : Gtk.Object {
			public Gtk.Mate.Scope root;
			public RangeSet changes;
			public int deactivation_level;
			public Gtk.TextTag dummy_tag;
			public Gtk.TextTag dummy_tag2;
			public GLib.Sequence<Gtk.TextTag> tags;
			public static Gee.ArrayList<Gtk.Mate.Parser> existing_parsers;
			public bool tag_added;
			public void make_root ();
			public void stop_parsing ();
			public void start_parsing ();
			public bool is_parsing ();
			public void clear_line (int line_ix, Gtk.Mate.Scope start_scope, Gee.ArrayList<Gtk.Mate.Scope> all_scopes, Gee.ArrayList<Gtk.Mate.Scope> closed_scopes, Gee.ArrayList<Gtk.Mate.Scope> removed_scopes);
			public Gtk.Mate.Scope? get_expected_scope (Gtk.Mate.Scope current_scope, int line, int line_offset);
			public void close_scope (Gtk.Mate.Scanner scanner, Gtk.Mate.Scope? expected_scope, int line_ix, string line, Gtk.Mate.Marker m, Gee.ArrayList<Gtk.Mate.Scope> all_scopes, Gee.ArrayList<Gtk.Mate.Scope> closed_scopes, Gee.ArrayList<Gtk.Mate.Scope> removed_scopes);
			public void open_scope (Gtk.Mate.Scanner scanner, Gtk.Mate.Scope? expected_scope, int line_ix, string line, int length, Gtk.Mate.Marker m, Gee.ArrayList<Gtk.Mate.Scope> all_scopes, Gee.ArrayList<Gtk.Mate.Scope> closed_scopes, Gee.ArrayList<Gtk.Mate.Scope> removed_scopes);
			public void single_scope (Gtk.Mate.Scanner scanner, Gtk.Mate.Scope? expected_scope, int line_ix, string line, int length, Gtk.Mate.Marker m, Gee.ArrayList<Gtk.Mate.Scope> all_scopes, Gee.ArrayList<Gtk.Mate.Scope> closed_scopes, Gee.ArrayList<Gtk.Mate.Scope> removed_scopes);
			public void handle_captures (int line_ix, string line, Gtk.Mate.Scope scope, Gtk.Mate.Marker m, Gee.ArrayList<Gtk.Mate.Scope> all_scopes, Gee.ArrayList<Gtk.Mate.Scope> closed_scopes);
			public Onig.Rx? make_closing_regex (string line, Gtk.Mate.Scope scope, Gtk.Mate.Marker m);
			public void collect_child_captures (int line_ix, Gtk.Mate.Scope scope, Gtk.Mate.Marker m, Gee.ArrayList<Gtk.Mate.Scope> all_scopes, Gee.ArrayList<Gtk.Mate.Scope> closed_scopes);
			public void reset_table_priorities ();
			public void connect_buffer_signals ();
			public void insert_text_handler (Gtk.Mate.Buffer bf, Gtk.TextIter pos, string text, int length);
			public void delete_range_handler (Gtk.Mate.Buffer bf, Gtk.TextIter pos, Gtk.TextIter pos2);
			public void insert_text_after_handler (Gtk.Mate.Buffer bf, Gtk.TextIter pos, string text, int length);
			public void delete_range_after_handler (Gtk.Mate.Buffer bf, Gtk.TextIter pos, Gtk.TextIter pos2);
			public static void static_insert_text_after_handler (Gtk.Mate.Buffer bf, Gtk.TextIter pos, string text, int length);
			public static void static_delete_range_after_handler (Gtk.Mate.Buffer bf, Gtk.TextIter pos, Gtk.TextIter pos2);
			public void added_tag (Gtk.TextTag tag);
			public static int tag_compare (Gtk.TextTag tag1, Gtk.TextTag tag2, void* data);
			public void close ();
			public static Gtk.Mate.Parser create (Gtk.Mate.Grammar grammar, Gtk.Mate.Buffer buffer);
			public Parser ();
			public Gtk.Mate.Grammar grammar { get; set; }
			public Gtk.Mate.Colourer colourer { get; set; }
			public Gtk.Mate.Buffer buffer { get; set; }
		}
		[CCode (cheader_filename = "scanner.h")]
		public class Marker : Gtk.Object {
			public int from;
			public int hint;
			public bool is_close_scope;
			public Gtk.Mate.Pattern pattern;
			public Onig.Match match;
			public Marker ();
		}
		[CCode (cheader_filename = "scanner.h")]
		public class Scanner : Gtk.Object, Gee.Iterable<Gtk.Mate.Marker> {
			public int position;
			public Gee.ArrayList<Gtk.Mate.Marker> cached_markers;
			public Scanner (Gtk.Mate.Scope s, string line, int line_length);
			public Gtk.Mate.Marker? get_cached_marker ();
			public void remove_preceding_cached_markers (Gtk.Mate.Marker m);
			public Onig.Match? scan_for_match (int from, Gtk.Mate.Pattern p);
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
		[CCode (cheader_filename = "colourer.h")]
		public class Colourer : Gtk.Object {
			public void set_global_settings (Gtk.Mate.View view);
			public Colourer (Gtk.Mate.Buffer buffer);
			public Gdk.Color parse_colour (string colour);
			public void colour_line_with_scopes (Gee.ArrayList<Gtk.Mate.Scope> scopes);
			public void colour_scope (Gtk.Mate.Scope scope, bool inner);
			public void set_tag_properties (Gtk.Mate.Scope scope, Gtk.TextTag tag, Gtk.Mate.ThemeSetting setting);
			public static int char_to_hex (unichar ch);
			public static string? merge_colour (string? parent_colour, string colour);
			public void uncolour_scopes (Gee.ArrayList<Gtk.Mate.Scope> scopes);
			public void uncolour_scope (Gtk.Mate.Scope scope, bool recurse);
			public Gtk.Mate.Buffer buffer { get; set; }
			public Gtk.Mate.Theme theme { get; set; }
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
[CCode (cprefix = "Onig", lower_case_cprefix = "onig_")]
namespace Onig {
	[CCode (cheader_filename = "onig_wrap.h")]
	public class OnigError : GLib.Object {
		public int code;
		public Oniguruma.OnigErrorInfo error_info;
		public OnigError ();
	}
	[CCode (cheader_filename = "onig_wrap.h")]
	public class Match : GLib.Object {
		public int num_captures ();
		public int begin (int capture);
		public int end (int capture);
		public Match ();
		public Oniguruma.RegexT rx { get; set; }
		public Oniguruma.Region rg { get; set; }
	}
	[CCode (cheader_filename = "onig_wrap.h")]
	public class Rx : GLib.Object {
		public bool matches_start_of_line;
		public Onig.Match? search (string target, int start, int end);
		public static Onig.Rx? make (string pattern, Oniguruma.OnigOptionType options, out Onig.OnigError error);
		public static Onig.Rx? make1 (string pattern);
		public Rx ();
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
	public class Integer : PList.Node {
		public int value;
		public Integer ();
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
[CCode (cheader_filename = "string_helper.h")]
public class StringHelper : GLib.Object {
	public static string gsub (string start_string, string match_string, string replacement_string);
	public static Gee.ArrayList<int> occurrences (string s, string t);
	public StringHelper ();
}
