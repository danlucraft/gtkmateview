
#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gtksourceview/gtksourceview.h>
#include <gee/arraylist.h>
#include <gee/hashmap.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>
#include <stdio.h>
#include <gee/map.h>


#define GTK_MATE_TYPE_TEXT_LOC (gtk_mate_text_loc_get_type ())
#define GTK_MATE_TEXT_LOC(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_TEXT_LOC, GtkMateTextLoc))
#define GTK_MATE_TEXT_LOC_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_TEXT_LOC, GtkMateTextLocClass))
#define GTK_MATE_IS_TEXT_LOC(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_TEXT_LOC))
#define GTK_MATE_IS_TEXT_LOC_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_TEXT_LOC))
#define GTK_MATE_TEXT_LOC_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_TEXT_LOC, GtkMateTextLocClass))

typedef struct _GtkMateTextLoc GtkMateTextLoc;
typedef struct _GtkMateTextLocClass GtkMateTextLocClass;
typedef struct _GtkMateTextLocPrivate GtkMateTextLocPrivate;

#define GTK_MATE_TYPE_PARSER (gtk_mate_parser_get_type ())
#define GTK_MATE_PARSER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_PARSER, GtkMateParser))
#define GTK_MATE_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_PARSER, GtkMateParserClass))
#define GTK_MATE_IS_PARSER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_PARSER))
#define GTK_MATE_IS_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_PARSER))
#define GTK_MATE_PARSER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_PARSER, GtkMateParserClass))

typedef struct _GtkMateParser GtkMateParser;
typedef struct _GtkMateParserClass GtkMateParserClass;
typedef struct _GtkMateParserPrivate GtkMateParserPrivate;

#define GTK_MATE_TYPE_SCOPE (gtk_mate_scope_get_type ())
#define GTK_MATE_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SCOPE, GtkMateScope))
#define GTK_MATE_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SCOPE, GtkMateScopeClass))
#define GTK_MATE_IS_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SCOPE))
#define GTK_MATE_IS_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SCOPE))
#define GTK_MATE_SCOPE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SCOPE, GtkMateScopeClass))

typedef struct _GtkMateScope GtkMateScope;
typedef struct _GtkMateScopeClass GtkMateScopeClass;

#define TYPE_RANGE_SET (range_set_get_type ())
#define RANGE_SET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_RANGE_SET, RangeSet))
#define RANGE_SET_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_RANGE_SET, RangeSetClass))
#define IS_RANGE_SET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_RANGE_SET))
#define IS_RANGE_SET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_RANGE_SET))
#define RANGE_SET_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_RANGE_SET, RangeSetClass))

typedef struct _RangeSet RangeSet;
typedef struct _RangeSetClass RangeSetClass;

#define GTK_MATE_TYPE_GRAMMAR (gtk_mate_grammar_get_type ())
#define GTK_MATE_GRAMMAR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammar))
#define GTK_MATE_GRAMMAR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammarClass))
#define GTK_MATE_IS_GRAMMAR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_GRAMMAR))
#define GTK_MATE_IS_GRAMMAR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_GRAMMAR))
#define GTK_MATE_GRAMMAR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammarClass))

typedef struct _GtkMateGrammar GtkMateGrammar;
typedef struct _GtkMateGrammarClass GtkMateGrammarClass;

#define GTK_MATE_TYPE_COLOURER (gtk_mate_colourer_get_type ())
#define GTK_MATE_COLOURER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_COLOURER, GtkMateColourer))
#define GTK_MATE_COLOURER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_COLOURER, GtkMateColourerClass))
#define GTK_MATE_IS_COLOURER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_COLOURER))
#define GTK_MATE_IS_COLOURER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_COLOURER))
#define GTK_MATE_COLOURER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_COLOURER, GtkMateColourerClass))

typedef struct _GtkMateColourer GtkMateColourer;
typedef struct _GtkMateColourerClass GtkMateColourerClass;

#define GTK_MATE_TYPE_BUFFER (gtk_mate_buffer_get_type ())
#define GTK_MATE_BUFFER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_BUFFER, GtkMateBuffer))
#define GTK_MATE_BUFFER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_BUFFER, GtkMateBufferClass))
#define GTK_MATE_IS_BUFFER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_BUFFER))
#define GTK_MATE_IS_BUFFER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_BUFFER))
#define GTK_MATE_BUFFER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_BUFFER, GtkMateBufferClass))

typedef struct _GtkMateBuffer GtkMateBuffer;
typedef struct _GtkMateBufferClass GtkMateBufferClass;
typedef struct _GtkMateGrammarPrivate GtkMateGrammarPrivate;

#define ONIG_TYPE_RX (onig_rx_get_type ())
#define ONIG_RX(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIG_TYPE_RX, OnigRx))
#define ONIG_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIG_TYPE_RX, OnigRxClass))
#define ONIG_IS_RX(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIG_TYPE_RX))
#define ONIG_IS_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIG_TYPE_RX))
#define ONIG_RX_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIG_TYPE_RX, OnigRxClass))

typedef struct _OnigRx OnigRx;
typedef struct _OnigRxClass OnigRxClass;

#define GTK_MATE_TYPE_PATTERN (gtk_mate_pattern_get_type ())
#define GTK_MATE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_PATTERN, GtkMatePattern))
#define GTK_MATE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_PATTERN, GtkMatePatternClass))
#define GTK_MATE_IS_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_PATTERN))
#define GTK_MATE_IS_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_PATTERN))
#define GTK_MATE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_PATTERN, GtkMatePatternClass))

typedef struct _GtkMatePattern GtkMatePattern;
typedef struct _GtkMatePatternClass GtkMatePatternClass;
typedef struct _GtkMateScopePrivate GtkMateScopePrivate;

#define ONIG_TYPE_MATCH (onig_match_get_type ())
#define ONIG_MATCH(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIG_TYPE_MATCH, OnigMatch))
#define ONIG_MATCH_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIG_TYPE_MATCH, OnigMatchClass))
#define ONIG_IS_MATCH(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIG_TYPE_MATCH))
#define ONIG_IS_MATCH_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIG_TYPE_MATCH))
#define ONIG_MATCH_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIG_TYPE_MATCH, OnigMatchClass))

typedef struct _OnigMatch OnigMatch;
typedef struct _OnigMatchClass OnigMatchClass;

#define GTK_MATE_TYPE_THEME_SETTING (gtk_mate_theme_setting_get_type ())
#define GTK_MATE_THEME_SETTING(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSetting))
#define GTK_MATE_THEME_SETTING_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSettingClass))
#define GTK_MATE_IS_THEME_SETTING(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_THEME_SETTING))
#define GTK_MATE_IS_THEME_SETTING_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_THEME_SETTING))
#define GTK_MATE_THEME_SETTING_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSettingClass))

typedef struct _GtkMateThemeSetting GtkMateThemeSetting;
typedef struct _GtkMateThemeSettingClass GtkMateThemeSettingClass;

#define GTK_MATE_TYPE_DOUBLE_PATTERN (gtk_mate_double_pattern_get_type ())
#define GTK_MATE_DOUBLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePattern))
#define GTK_MATE_DOUBLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePatternClass))
#define GTK_MATE_IS_DOUBLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN))
#define GTK_MATE_IS_DOUBLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_DOUBLE_PATTERN))
#define GTK_MATE_DOUBLE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePatternClass))

typedef struct _GtkMateDoublePattern GtkMateDoublePattern;
typedef struct _GtkMateDoublePatternClass GtkMateDoublePatternClass;
typedef struct _GtkMatePatternPrivate GtkMatePatternPrivate;
typedef struct _GtkMateDoublePatternPrivate GtkMateDoublePatternPrivate;

#define RANGE_SET_TYPE_RANGE (range_set_range_get_type ())
#define RANGE_SET_RANGE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RANGE_SET_TYPE_RANGE, RangeSetRange))
#define RANGE_SET_RANGE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RANGE_SET_TYPE_RANGE, RangeSetRangeClass))
#define RANGE_SET_IS_RANGE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RANGE_SET_TYPE_RANGE))
#define RANGE_SET_IS_RANGE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RANGE_SET_TYPE_RANGE))
#define RANGE_SET_RANGE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RANGE_SET_TYPE_RANGE, RangeSetRangeClass))

typedef struct _RangeSetRange RangeSetRange;
typedef struct _RangeSetRangeClass RangeSetRangeClass;
typedef struct _RangeSetRangePrivate RangeSetRangePrivate;
typedef struct _RangeSetPrivate RangeSetPrivate;

#define GTK_MATE_TYPE_SCANNER (gtk_mate_scanner_get_type ())
#define GTK_MATE_SCANNER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SCANNER, GtkMateScanner))
#define GTK_MATE_SCANNER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SCANNER, GtkMateScannerClass))
#define GTK_MATE_IS_SCANNER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SCANNER))
#define GTK_MATE_IS_SCANNER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SCANNER))
#define GTK_MATE_SCANNER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SCANNER, GtkMateScannerClass))

typedef struct _GtkMateScanner GtkMateScanner;
typedef struct _GtkMateScannerClass GtkMateScannerClass;

#define GTK_MATE_TYPE_MARKER (gtk_mate_marker_get_type ())
#define GTK_MATE_MARKER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_MARKER, GtkMateMarker))
#define GTK_MATE_MARKER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_MARKER, GtkMateMarkerClass))
#define GTK_MATE_IS_MARKER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_MARKER))
#define GTK_MATE_IS_MARKER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_MARKER))
#define GTK_MATE_MARKER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_MARKER, GtkMateMarkerClass))

typedef struct _GtkMateMarker GtkMateMarker;
typedef struct _GtkMateMarkerClass GtkMateMarkerClass;
typedef struct _GtkMateScannerPrivate GtkMateScannerPrivate;
typedef struct _GtkMateMarkerPrivate GtkMateMarkerPrivate;

#define GTK_MATE_TYPE_SINGLE_PATTERN (gtk_mate_single_pattern_get_type ())
#define GTK_MATE_SINGLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePattern))
#define GTK_MATE_SINGLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePatternClass))
#define GTK_MATE_IS_SINGLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SINGLE_PATTERN))
#define GTK_MATE_IS_SINGLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SINGLE_PATTERN))
#define GTK_MATE_SINGLE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePatternClass))

typedef struct _GtkMateSinglePattern GtkMateSinglePattern;
typedef struct _GtkMateSinglePatternClass GtkMateSinglePatternClass;
typedef struct _GtkMateSinglePatternPrivate GtkMateSinglePatternPrivate;

#define GTK_MATE_TYPE_THEME (gtk_mate_theme_get_type ())
#define GTK_MATE_THEME(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_THEME, GtkMateTheme))
#define GTK_MATE_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_THEME, GtkMateThemeClass))
#define GTK_MATE_IS_THEME(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_THEME))
#define GTK_MATE_IS_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_THEME))
#define GTK_MATE_THEME_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_THEME, GtkMateThemeClass))

typedef struct _GtkMateTheme GtkMateTheme;
typedef struct _GtkMateThemeClass GtkMateThemeClass;

struct _GtkMateTextLoc {
	GtkObject parent_instance;
	GtkMateTextLocPrivate * priv;
	gint line;
	gint line_offset;
};

struct _GtkMateTextLocClass {
	GtkObjectClass parent_class;
};

struct _GtkMateParser {
	GtkObject parent_instance;
	GtkMateParserPrivate * priv;
	GtkMateScope* root;
	gint deactivation_level;
	GtkTextTag* dummy_tag;
	GtkTextTag* dummy_tag2;
	GSequence* tags;
	RangeSet* changes;
	gint parsed_upto;
	gint last_visible_line;
	gboolean always_parse_all;
};

struct _GtkMateParserClass {
	GtkObjectClass parent_class;
};

struct _GtkMateParserPrivate {
	GtkMateGrammar* _grammar;
	GtkMateColourer* _colourer;
	GtkMateBuffer* _buffer;
	gint _look_ahead;
};

struct _GtkMateGrammar {
	GtkObject parent_instance;
	GtkMateGrammarPrivate * priv;
	char** file_types;
	gint file_types_length1;
	OnigRx* first_line_match;
	char* key_equivalent;
	char* scope_name;
	char* comment;
	GeeArrayList* all_patterns;
	OnigRx* folding_start_marker;
	OnigRx* folding_stop_marker;
	GeeArrayList* patterns;
	GeeHashMap* repository;
	gboolean loaded;
};

struct _GtkMateGrammarClass {
	GtkObjectClass parent_class;
};

struct _GtkMateScope {
	GtkObject parent_instance;
	GtkMateScopePrivate * priv;
	GtkMatePattern* pattern;
	OnigMatch* open_match;
	OnigMatch* close_match;
	OnigRx* closing_regex;
	GtkTextMark* start_mark;
	GtkTextMark* inner_start_mark;
	GtkTextMark* inner_end_mark;
	GtkTextMark* end_mark;
	GtkTextTag* tag;
	GtkTextTag* inner_tag;
	gboolean is_open;
	char* bg_colour;
	char* fg_colour;
	gboolean is_capture;
	GtkMateTextLoc* dummy_start_loc;
	GtkMateTextLoc* dummy_end_loc;
	char* begin_match_string;
	char* end_match_string;
	GtkMateScope* parent;
	GString* pretty_string;
	gint indent;
	GtkMateThemeSetting* theme_setting;
};

struct _GtkMateScopeClass {
	GtkObjectClass parent_class;
};

struct _GtkMatePattern {
	GtkObject parent_instance;
	GtkMatePatternPrivate * priv;
	char* name;
	char* comment;
	gboolean disabled;
};

struct _GtkMatePatternClass {
	GtkObjectClass parent_class;
};

struct _GtkMateDoublePattern {
	GtkMatePattern parent_instance;
	GtkMateDoublePatternPrivate * priv;
	char* content_name;
	OnigRx* begin;
	OnigRx* end;
	char* end_string;
	char* begin_string;
	GeeHashMap* begin_captures;
	GeeHashMap* end_captures;
	GeeHashMap* both_captures;
	GeeArrayList* patterns;
};

struct _GtkMateDoublePatternClass {
	GtkMatePatternClass parent_class;
};

struct _RangeSetRange {
	GObject parent_instance;
	RangeSetRangePrivate * priv;
	gint a;
	gint b;
};

struct _RangeSetRangeClass {
	GObjectClass parent_class;
};

/* This data structure stores sets of ranges 
 like 1, 4-8, 10, 12, 15-20*/
struct _RangeSet {
	GObject parent_instance;
	RangeSetPrivate * priv;
	GeeArrayList* ranges;
};

struct _RangeSetClass {
	GObjectClass parent_class;
};

/* the matchdata of the successful match
 Scans lines for patterns. Handles caching of what has already been seen etc.*/
struct _GtkMateScanner {
	GtkObject parent_instance;
	GtkMateScannerPrivate * priv;
	gint position;
	GeeArrayList* cached_markers;
};

struct _GtkMateScannerClass {
	GtkObjectClass parent_class;
};

/* The Scanner returns these to indicate successful pattern matches in a line.*/
struct _GtkMateMarker {
	GtkObject parent_instance;
	GtkMateMarkerPrivate * priv;
	gint from;
	gint hint;
	gboolean is_close_scope;
	GtkMatePattern* pattern;
	OnigMatch* match;
};

struct _GtkMateMarkerClass {
	GtkObjectClass parent_class;
};

struct _GtkMateSinglePattern {
	GtkMatePattern parent_instance;
	GtkMateSinglePatternPrivate * priv;
	OnigRx* match;
	GeeHashMap* captures;
};

struct _GtkMateSinglePatternClass {
	GtkMatePatternClass parent_class;
};



GType gtk_mate_text_loc_get_type (void);
enum  {
	GTK_MATE_TEXT_LOC_DUMMY_PROPERTY
};
GtkMateTextLoc* gtk_mate_text_loc_new (void);
GtkMateTextLoc* gtk_mate_text_loc_construct (GType object_type);
GtkMateTextLoc* gtk_mate_text_loc_make (gint l, gint lo);
gboolean gtk_mate_text_loc_equal (GtkMateTextLoc* t1, GtkMateTextLoc* t2);
gboolean gtk_mate_text_loc_gt (GtkMateTextLoc* t1, GtkMateTextLoc* t2);
gboolean gtk_mate_text_loc_lt (GtkMateTextLoc* t1, GtkMateTextLoc* t2);
gboolean gtk_mate_text_loc_gte (GtkMateTextLoc* t1, GtkMateTextLoc* t2);
gboolean gtk_mate_text_loc_lte (GtkMateTextLoc* t1, GtkMateTextLoc* t2);
char* gtk_mate_text_loc_to_s (GtkMateTextLoc* self);
GtkMateTextLoc* gtk_mate_text_loc_new (void);
static gpointer gtk_mate_text_loc_parent_class = NULL;
static void gtk_mate_text_loc_finalize (GObject* obj);
GType gtk_mate_parser_get_type (void);
GType gtk_mate_scope_get_type (void);
GType range_set_get_type (void);
GType gtk_mate_grammar_get_type (void);
GType gtk_mate_colourer_get_type (void);
GType gtk_mate_buffer_get_type (void);
#define GTK_MATE_PARSER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_TYPE_PARSER, GtkMateParserPrivate))
enum  {
	GTK_MATE_PARSER_DUMMY_PROPERTY,
	GTK_MATE_PARSER_GRAMMAR,
	GTK_MATE_PARSER_COLOURER,
	GTK_MATE_PARSER_BUFFER,
	GTK_MATE_PARSER_LOOK_AHEAD
};
extern GeeArrayList* gtk_mate_parser_existing_parsers;
GeeArrayList* gtk_mate_parser_existing_parsers = NULL;
GtkMateBuffer* gtk_mate_parser_get_buffer (GtkMateParser* self);
GtkMateGrammar* gtk_mate_parser_get_grammar (GtkMateParser* self);
GType onig_rx_get_type (void);
GType gtk_mate_pattern_get_type (void);
GtkMateScope* gtk_mate_scope_new (GtkMateBuffer* buf, const char* name);
GtkMateScope* gtk_mate_scope_construct (GType object_type, GtkMateBuffer* buf, const char* name);
GType onig_match_get_type (void);
GType gtk_mate_theme_setting_get_type (void);
void gtk_mate_scope_start_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity);
void gtk_mate_scope_end_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity);
GtkTextIter gtk_mate_buffer_end_iter (GtkMateBuffer* self);
GtkMateDoublePattern* gtk_mate_double_pattern_new (void);
GtkMateDoublePattern* gtk_mate_double_pattern_construct (GType object_type);
GType gtk_mate_double_pattern_get_type (void);
const char* gtk_mate_grammar_get_name (GtkMateGrammar* self);
void gtk_mate_pattern_set_grammar (GtkMatePattern* self, GtkMateGrammar* value);
void gtk_mate_parser_make_root (GtkMateParser* self);
void gtk_mate_parser_stop_parsing (GtkMateParser* self);
static void gtk_mate_parser_process_changes (GtkMateParser* self);
void gtk_mate_parser_start_parsing (GtkMateParser* self);
gboolean gtk_mate_parser_is_parsing (GtkMateParser* self);
GType range_set_range_get_type (void);
gint gtk_mate_parser_get_look_ahead (GtkMateParser* self);
static gint gtk_mate_parser_parse_range (GtkMateParser* self, gint from_line, gint to_line);
static gboolean gtk_mate_parser_parse_line (GtkMateParser* self, gint line_ix);
void gtk_mate_scope_clear_after (GtkMateScope* self, gint line_ix, gint line_offset);
static void gtk_mate_parser_remove_colour_after (GtkMateParser* self, gint line_ix, gint line_offset);
GtkTextIter gtk_mate_buffer_iter_at_line_offset (GtkMateBuffer* self, gint line, gint line_offset);
char* gtk_mate_buffer_get_line (GtkMateBuffer* self, gint line);
GtkMateScope* gtk_mate_scope_scope_at (GtkMateScope* self, gint line, gint line_offset);
const char* gtk_mate_scope_get_name (GtkMateScope* self);
GtkMateScope* gtk_mate_scope_containing_double_scope (GtkMateScope* self, gint line_ix);
GtkMateScanner* gtk_mate_scanner_new (GtkMateScope* s, const char* line, gint line_length);
GtkMateScanner* gtk_mate_scanner_construct (GType object_type, GtkMateScope* s, const char* line, gint line_length);
GType gtk_mate_scanner_get_type (void);
GType gtk_mate_marker_get_type (void);
GtkMateScope* gtk_mate_parser_get_expected_scope (GtkMateParser* self, GtkMateScope* current_scope, gint line, gint line_offset);
GtkMateScope* gtk_mate_scanner_get_current_scope (GtkMateScanner* self);
GtkMateTextLoc* gtk_mate_scope_start_loc (GtkMateScope* self);
gint onig_match_end (OnigMatch* self, gint capture);
void gtk_mate_parser_close_scope (GtkMateParser* self, GtkMateScanner* scanner, GtkMateScope* expected_scope, gint line_ix, const char* line, gint length, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes, GeeArrayList* removed_scopes);
void gtk_mate_parser_open_scope (GtkMateParser* self, GtkMateScanner* scanner, GtkMateScope* expected_scope, gint line_ix, const char* line, gint length, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes, GeeArrayList* removed_scopes);
void gtk_mate_parser_single_scope (GtkMateParser* self, GtkMateScanner* scanner, GtkMateScope* expected_scope, gint line_ix, const char* line, gint length, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes, GeeArrayList* removed_scopes);
void gtk_mate_parser_clear_line (GtkMateParser* self, gint line_ix, GtkMateScope* start_scope, GeeArrayList* all_scopes, GeeArrayList* closed_scopes, GeeArrayList* removed_scopes);
char* gtk_mate_scope_pretty (GtkMateScope* self, gint indent);
GtkMateColourer* gtk_mate_parser_get_colourer (GtkMateParser* self);
void gtk_mate_colourer_uncolour_scopes (GtkMateColourer* self, GeeArrayList* scopes);
void gtk_mate_colourer_colour_line_with_scopes (GtkMateColourer* self, GeeArrayList* scopes);
GeeArrayList* gtk_mate_scope_delete_any_on_line_not_in (GtkMateScope* self, gint line_ix, GeeArrayList* scopes);
gint gtk_mate_scope_inner_end_line (GtkMateScope* self);
void gtk_mate_scope_delete_child (GtkMateScope* self, GtkMateScope* s);
void gtk_mate_colourer_uncolour_scope (GtkMateColourer* self, GtkMateScope* scope, gboolean recurse);
void gtk_mate_scope_inner_end_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity);
GtkMateScope* gtk_mate_scope_first_child_after (GtkMateScope* self, GtkMateTextLoc* loc);
gint gtk_mate_scope_start_line (GtkMateScope* self);
GtkMateTextLoc* gtk_mate_scope_end_loc (GtkMateScope* self);
GtkMateTextLoc* gtk_mate_scope_inner_end_loc (GtkMateScope* self);
GSequence* gtk_mate_scope_get_children (GtkMateScope* self);
void gtk_mate_parser_set_inner_end_mark_safely (GtkMateParser* self, GtkMateScope* scope, GtkMateMarker* m, gint line_ix, gint length, gint cap);
void gtk_mate_parser_set_end_mark_safely (GtkMateParser* self, GtkMateScope* scope, GtkMateMarker* m, gint line_ix, gint length, gint cap);
void gtk_mate_parser_handle_captures (GtkMateParser* self, gint line_ix, gint length, const char* line, GtkMateScope* scope, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes);
void gtk_mate_scanner_set_current_scope (GtkMateScanner* self, GtkMateScope* value);
void gtk_mate_parser_set_start_mark_safely (GtkMateParser* self, GtkMateScope* scope, GtkMateMarker* m, gint line_ix, gint length, gint cap);
void gtk_mate_parser_set_inner_start_mark_safely (GtkMateParser* self, GtkMateScope* scope, GtkMateMarker* m, gint line_ix, gint length, gint cap);
gboolean gtk_mate_scope_surface_identical_to_modulo_ending (GtkMateScope* self, GtkMateScope* other);
gboolean gtk_mate_scope_overlaps_with (GtkMateScope* self, GtkMateScope* other);
void gtk_mate_scope_add_child (GtkMateScope* self, GtkMateScope* s);
gboolean gtk_mate_scope_surface_identical_to (GtkMateScope* self, GtkMateScope* other);
OnigRx* gtk_mate_parser_make_closing_regex (GtkMateParser* self, const char* line, GtkMateScope* scope, GtkMateMarker* m);
void gtk_mate_parser_collect_child_captures (GtkMateParser* self, gint line_ix, gint length, GtkMateScope* scope, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes);
OnigRx* onig_rx_make1 (const char* pattern);
OnigMatch* onig_rx_search (OnigRx* self, const char* target, gint start, gint end);
gint onig_match_begin (OnigMatch* self, gint capture);
void gtk_mate_scope_inner_start_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity);
GType gtk_mate_single_pattern_get_type (void);
gint gtk_mate_scope_end_offset (GtkMateScope* self);
gint gtk_mate_scope_start_offset (GtkMateScope* self);
void gtk_mate_parser_reset_table_priorities (GtkMateParser* self);
void gtk_mate_parser_remove_tags (GtkMateParser* self);
GType gtk_mate_theme_get_type (void);
void gtk_mate_colourer_set_theme (GtkMateColourer* self, GtkMateTheme* value);
void gtk_mate_parser_recolour_children (GtkMateParser* self, GtkMateScope* scope);
void gtk_mate_parser_change_theme (GtkMateParser* self, GtkMateTheme* theme);
void gtk_mate_colourer_colour_scope (GtkMateColourer* self, GtkMateScope* scope, gboolean inner, gboolean force);
void gtk_mate_parser_last_visible_line_changed (GtkMateParser* self, gint new_last_visible_line);
gint gtk_mate_scope_end_line (GtkMateScope* self);
gint gtk_mate_parser_last_line_parsed (GtkMateParser* self);
void gtk_mate_parser_insert_text_handler (GtkMateParser* self, GtkMateBuffer* bf, const GtkTextIter* pos, const char* text, gint length);
static void _gtk_mate_parser_insert_text_handler_gtk_text_buffer_insert_text (GtkMateBuffer* _sender, const GtkTextIter* pos, const char* text, gint length, gpointer self);
void gtk_mate_parser_delete_range_handler (GtkMateParser* self, GtkMateBuffer* bf, const GtkTextIter* pos, const GtkTextIter* pos2);
static void _gtk_mate_parser_delete_range_handler_gtk_text_buffer_delete_range (GtkMateBuffer* _sender, const GtkTextIter* start, const GtkTextIter* end, gpointer self);
void gtk_mate_parser_static_insert_text_after_handler (GtkMateBuffer* bf, const GtkTextIter* pos, const char* text, gint length);
void gtk_mate_parser_static_delete_range_after_handler (GtkMateBuffer* bf, const GtkTextIter* pos, const GtkTextIter* pos2);
void gtk_mate_parser_connect_buffer_signals (GtkMateParser* self);
void range_set_add (RangeSet* self, gint a, gint b);
gboolean range_set_is_empty (RangeSet* self);
void gtk_mate_parser_insert_text_after_handler (GtkMateParser* self, GtkMateBuffer* bf, const GtkTextIter* pos, const char* text, gint length);
void gtk_mate_parser_delete_range_after_handler (GtkMateParser* self, GtkMateBuffer* bf, const GtkTextIter* pos, const GtkTextIter* pos2);
gint gtk_mate_parser_tag_compare (GtkTextTag* tag1, GtkTextTag* tag2, void* data);
void gtk_mate_parser_added_tag (GtkMateParser* self, GtkTextTag* tag);
void gtk_mate_parser_close (GtkMateParser* self);
void gtk_mate_grammar_init_for_use (GtkMateGrammar* self);
GtkMateParser* gtk_mate_parser_new (void);
GtkMateParser* gtk_mate_parser_construct (GType object_type);
void gtk_mate_parser_set_look_ahead (GtkMateParser* self, gint value);
void gtk_mate_parser_set_grammar (GtkMateParser* self, GtkMateGrammar* value);
void gtk_mate_parser_set_buffer (GtkMateParser* self, GtkMateBuffer* value);
RangeSet* range_set_new (void);
RangeSet* range_set_construct (GType object_type);
GtkMateColourer* gtk_mate_colourer_new (GtkMateBuffer* buffer);
GtkMateColourer* gtk_mate_colourer_construct (GType object_type, GtkMateBuffer* buffer);
void gtk_mate_parser_set_colourer (GtkMateParser* self, GtkMateColourer* value);
GtkMateParser* gtk_mate_parser_create (GtkMateGrammar* grammar, GtkMateBuffer* buffer);
GtkMateParser* gtk_mate_parser_new (void);
static gpointer gtk_mate_parser_parent_class = NULL;
static void gtk_mate_parser_finalize (GObject* obj);
static void gtk_mate_parser_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void gtk_mate_parser_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static gint _vala_array_length (gpointer array);
static int _vala_strcmp0 (const char * str1, const char * str2);



GtkMateTextLoc* gtk_mate_text_loc_make (gint l, gint lo) {
	GtkMateTextLoc* tl;
	tl = g_object_ref_sink (gtk_mate_text_loc_new ());
	tl->line = l;
	tl->line_offset = lo;
	return tl;
}


gboolean gtk_mate_text_loc_equal (GtkMateTextLoc* t1, GtkMateTextLoc* t2) {
	gboolean _tmp0_;
	g_return_val_if_fail (t1 != NULL, FALSE);
	g_return_val_if_fail (t2 != NULL, FALSE);
	_tmp0_ = FALSE;
	if (t1->line == t2->line) {
		_tmp0_ = t1->line_offset == t2->line_offset;
	} else {
		_tmp0_ = FALSE;
	}
	return _tmp0_;
}


gboolean gtk_mate_text_loc_gt (GtkMateTextLoc* t1, GtkMateTextLoc* t2) {
	gboolean _tmp0_;
	g_return_val_if_fail (t1 != NULL, FALSE);
	g_return_val_if_fail (t2 != NULL, FALSE);
	_tmp0_ = FALSE;
	if (t1->line > t2->line) {
		_tmp0_ = TRUE;
	} else {
		gboolean _tmp1_;
		_tmp1_ = FALSE;
		if (t1->line >= t2->line) {
			_tmp1_ = t1->line_offset > t2->line_offset;
		} else {
			_tmp1_ = FALSE;
		}
		_tmp0_ = _tmp1_;
	}
	return _tmp0_;
}


gboolean gtk_mate_text_loc_lt (GtkMateTextLoc* t1, GtkMateTextLoc* t2) {
	gboolean _tmp0_;
	g_return_val_if_fail (t1 != NULL, FALSE);
	g_return_val_if_fail (t2 != NULL, FALSE);
	_tmp0_ = FALSE;
	if (!gtk_mate_text_loc_equal (t1, t2)) {
		_tmp0_ = !gtk_mate_text_loc_gt (t1, t2);
	} else {
		_tmp0_ = FALSE;
	}
	return _tmp0_;
}


gboolean gtk_mate_text_loc_gte (GtkMateTextLoc* t1, GtkMateTextLoc* t2) {
	g_return_val_if_fail (t1 != NULL, FALSE);
	g_return_val_if_fail (t2 != NULL, FALSE);
	return !gtk_mate_text_loc_lt (t1, t2);
}


gboolean gtk_mate_text_loc_lte (GtkMateTextLoc* t1, GtkMateTextLoc* t2) {
	g_return_val_if_fail (t1 != NULL, FALSE);
	g_return_val_if_fail (t2 != NULL, FALSE);
	return !gtk_mate_text_loc_gt (t1, t2);
}


char* gtk_mate_text_loc_to_s (GtkMateTextLoc* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return g_strdup_printf ("{%d,%d}", self->line, self->line_offset);
}


GtkMateTextLoc* gtk_mate_text_loc_construct (GType object_type) {
	GtkMateTextLoc * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


GtkMateTextLoc* gtk_mate_text_loc_new (void) {
	return gtk_mate_text_loc_construct (GTK_MATE_TYPE_TEXT_LOC);
}


static void gtk_mate_text_loc_class_init (GtkMateTextLocClass * klass) {
	gtk_mate_text_loc_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_text_loc_finalize;
}


static void gtk_mate_text_loc_instance_init (GtkMateTextLoc * self) {
}


static void gtk_mate_text_loc_finalize (GObject* obj) {
	GtkMateTextLoc * self;
	self = GTK_MATE_TEXT_LOC (obj);
	G_OBJECT_CLASS (gtk_mate_text_loc_parent_class)->finalize (obj);
}


GType gtk_mate_text_loc_get_type (void) {
	static GType gtk_mate_text_loc_type_id = 0;
	if (gtk_mate_text_loc_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateTextLocClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_text_loc_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateTextLoc), 0, (GInstanceInitFunc) gtk_mate_text_loc_instance_init, NULL };
		gtk_mate_text_loc_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateTextLoc", &g_define_type_info, 0);
	}
	return gtk_mate_text_loc_type_id;
}


void gtk_mate_parser_make_root (GtkMateParser* self) {
	GtkMateScope* _tmp0_;
	GtkTextIter _tmp2_ = {0};
	GtkTextIter _tmp1_ = {0};
	GtkMateDoublePattern* dp;
	char* _tmp4_;
	const char* _tmp3_;
	GeeArrayList* _tmp6_;
	GeeArrayList* _tmp5_;
	GtkMatePattern* _tmp8_;
	GtkMatePattern* _tmp7_;
	g_return_if_fail (self != NULL);
	_tmp0_ = NULL;
	self->root = (_tmp0_ = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, self->priv->_grammar->scope_name)), (self->root == NULL) ? NULL : (self->root = (g_object_unref (self->root), NULL)), _tmp0_);
	self->root->is_open = TRUE;
	gtk_mate_scope_start_mark_set (self->root, 0, 0, TRUE);
	gtk_mate_scope_end_mark_set (self->root, gtk_text_iter_get_line ((_tmp1_ = gtk_mate_buffer_end_iter (self->priv->_buffer), &_tmp1_)), gtk_text_iter_get_line_index ((_tmp2_ = gtk_mate_buffer_end_iter (self->priv->_buffer), &_tmp2_)), FALSE);
	dp = g_object_ref_sink (gtk_mate_double_pattern_new ());
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	((GtkMatePattern*) dp)->name = (_tmp4_ = (_tmp3_ = gtk_mate_grammar_get_name (self->priv->_grammar), (_tmp3_ == NULL) ? NULL : g_strdup (_tmp3_)), ((GtkMatePattern*) dp)->name = (g_free (((GtkMatePattern*) dp)->name), NULL), _tmp4_);
	_tmp6_ = NULL;
	_tmp5_ = NULL;
	dp->patterns = (_tmp6_ = (_tmp5_ = self->priv->_grammar->patterns, (_tmp5_ == NULL) ? NULL : g_object_ref (_tmp5_)), (dp->patterns == NULL) ? NULL : (dp->patterns = (g_object_unref (dp->patterns), NULL)), _tmp6_);
	gtk_mate_pattern_set_grammar ((GtkMatePattern*) dp, self->priv->_grammar);
	_tmp8_ = NULL;
	_tmp7_ = NULL;
	self->root->pattern = (_tmp8_ = (_tmp7_ = (GtkMatePattern*) dp, (_tmp7_ == NULL) ? NULL : g_object_ref (_tmp7_)), (self->root->pattern == NULL) ? NULL : (self->root->pattern = (g_object_unref (self->root->pattern), NULL)), _tmp8_);
	(dp == NULL) ? NULL : (dp = (g_object_unref (dp), NULL));
}


void gtk_mate_parser_stop_parsing (GtkMateParser* self) {
	g_return_if_fail (self != NULL);
	self->deactivation_level = self->deactivation_level + 1;
}


void gtk_mate_parser_start_parsing (GtkMateParser* self) {
	g_return_if_fail (self != NULL);
	if (self->deactivation_level > 0) {
		self->deactivation_level = self->deactivation_level - 1;
	}
	if (self->deactivation_level == 0) {
		gtk_mate_parser_process_changes (self);
	}
}


gboolean gtk_mate_parser_is_parsing (GtkMateParser* self) {
	g_return_val_if_fail (self != NULL, FALSE);
	return self->deactivation_level == 0;
}


/* Process all change ranges.*/
static void gtk_mate_parser_process_changes (GtkMateParser* self) {
	gint this_parsed_upto;
	g_return_if_fail (self != NULL);
	this_parsed_upto = -1;
	/* stdout.printf("process_changes (last_visible_line: %d)\n", last_visible_line);*/
	{
		GeeIterator* _range_it;
		/* stdout.printf("process_changes (last_visible_line: %d)\n", last_visible_line);*/
		_range_it = gee_iterable_iterator ((GeeIterable*) self->changes);
		/* stdout.printf("process_changes (last_visible_line: %d)\n", last_visible_line);*/
		while (gee_iterator_next (_range_it)) {
			RangeSetRange* range;
			gboolean _tmp0_;
			/* stdout.printf("process_changes (last_visible_line: %d)\n", last_visible_line);*/
			range = (RangeSetRange*) gee_iterator_get (_range_it);
			_tmp0_ = FALSE;
			if (range->b > this_parsed_upto) {
				_tmp0_ = range->a <= (self->last_visible_line + self->priv->_look_ahead);
			} else {
				_tmp0_ = FALSE;
			}
			if (_tmp0_) {
				gint range_end;
				range_end = MIN (self->last_visible_line + self->priv->_look_ahead, range->b);
				this_parsed_upto = gtk_mate_parser_parse_range (self, range->a, range_end);
			}
			(range == NULL) ? NULL : (range = (g_object_unref (range), NULL));
		}
		(_range_it == NULL) ? NULL : (_range_it = (g_object_unref (_range_it), NULL));
	}
	/*//stdout.printf("%s\n", root.pretty(0));*/
	gee_collection_clear ((GeeCollection*) self->changes->ranges);
}


/* Parse from from_line to *at least* to_line. Will parse
 more if necessary. Returns the index of the last line
 parsed.*/
static gint gtk_mate_parser_parse_range (GtkMateParser* self, gint from_line, gint to_line) {
	gint line_ix;
	gboolean scope_changed;
	gboolean scope_ever_changed;
	gint end_line;
	g_return_val_if_fail (self != NULL, 0);
	/* stdout.printf("parse_range(%d, %d)\n", from_line, to_line);*/
	line_ix = from_line;
	scope_changed = FALSE;
	scope_ever_changed = FALSE;
	end_line = MIN (self->last_visible_line + 100, gtk_text_buffer_get_line_count ((GtkTextBuffer*) self->priv->_buffer) - 1);
	while (TRUE) {
		gboolean _tmp0_;
		_tmp0_ = FALSE;
		if (line_ix <= to_line) {
			_tmp0_ = TRUE;
		} else {
			gboolean _tmp1_;
			_tmp1_ = FALSE;
			if (scope_ever_changed) {
				_tmp1_ = line_ix <= end_line;
			} else {
				_tmp1_ = FALSE;
			}
			_tmp0_ = _tmp1_;
		}
		if (!_tmp0_) {
			break;
		}
		scope_changed = gtk_mate_parser_parse_line (self, line_ix++);
		if (scope_changed) {
			scope_ever_changed = TRUE;
			/* In the old scheme this wasn't necessary because 
			 the scope_at used a simple scan from the front. The GSequences
			 on the other hand can get confused if the later scopes
			 are inconsistent with earler ones. So we have to clear everything.
			 TODO: figure out a way to OPTIMIZE this again.*/
			gtk_mate_scope_clear_after (self->root, line_ix, -1);
			gtk_mate_parser_remove_colour_after (self, line_ix, 0);
			self->parsed_upto = line_ix;
		}
	}
	/* stdout.printf("parse_line returned: %s\n", scope_changed ? "true" : "false");
	stdout.printf("pretty:\n%s\n", root.pretty(2));*/
	return to_line;
}


static void gtk_mate_parser_remove_colour_after (GtkMateParser* self, gint line_ix, gint line_offset) {
	GSequenceIter* iter;
	GtkTextIter start_iter;
	GtkTextIter end_iter;
	g_return_if_fail (self != NULL);
	iter = g_sequence_get_begin_iter (self->tags);
	start_iter = gtk_mate_buffer_iter_at_line_offset (self->priv->_buffer, line_ix, line_offset);
	end_iter = gtk_mate_buffer_end_iter (self->priv->_buffer);
	while (!g_sequence_iter_is_end (g_sequence_iter_next (iter))) {
		GtkTextTag* _tmp0_;
		GtkTextTag* t;
		_tmp0_ = NULL;
		t = (_tmp0_ = (GtkTextTag*) g_sequence_get (iter), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
		gtk_text_buffer_remove_tag ((GtkTextBuffer*) self->priv->_buffer, t, &start_iter, &end_iter);
		iter = g_sequence_iter_next (iter);
		(t == NULL) ? NULL : (t = (g_object_unref (t), NULL));
	}
}


/* Parse line line_ix. Returns true if the ending
 scope of the line has changed.*/
static gboolean gtk_mate_parser_parse_line (GtkMateParser* self, gint line_ix) {
	char* line;
	gint length;
	GtkMateScope* start_scope;
	GtkMateScope* end_scope1;
	GtkMateScanner* scanner;
	GeeArrayList* all_scopes;
	GeeArrayList* closed_scopes;
	GeeArrayList* removed_scopes;
	GtkMateScope* end_scope2;
	char* _tmp5_;
	gboolean _tmp6_;
	g_return_val_if_fail (self != NULL, FALSE);
	line = gtk_mate_buffer_get_line (self->priv->_buffer, line_ix);
	length = (gint) strlen (line);
	/*buffer.get_line_length(line_ix);*/
	fprintf (stdout, "p%d, ", line_ix);
	fflush (stdout);
	if (line_ix > self->parsed_upto) {
		self->parsed_upto = line_ix;
	}
	/* stdout.flush();*/
	start_scope = gtk_mate_scope_scope_at (self->root, line_ix, 0);
	if (start_scope != NULL) {
		GtkMateScope* _tmp0_;
		fprintf (stdout, "start_scope is: %s\n", gtk_mate_scope_get_name (start_scope));
		_tmp0_ = NULL;
		start_scope = (_tmp0_ = gtk_mate_scope_containing_double_scope (start_scope, line_ix), (start_scope == NULL) ? NULL : (start_scope = (g_object_unref (start_scope), NULL)), _tmp0_);
	}
	fprintf (stdout, "start_scope is: %s\n", gtk_mate_scope_get_name (start_scope));
	end_scope1 = gtk_mate_scope_scope_at (self->root, line_ix, G_MAXINT);
	if (end_scope1 != NULL) {
		GtkMateScope* _tmp1_;
		_tmp1_ = NULL;
		end_scope1 = (_tmp1_ = gtk_mate_scope_containing_double_scope (end_scope1, line_ix), (end_scope1 == NULL) ? NULL : (end_scope1 = (g_object_unref (end_scope1), NULL)), _tmp1_);
	}
	fprintf (stdout, "end_scope1: %s\n", gtk_mate_scope_get_name (end_scope1));
	scanner = g_object_ref_sink (gtk_mate_scanner_new (start_scope, line, length));
	all_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	gee_collection_add ((GeeCollection*) all_scopes, start_scope);
	closed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	removed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	gee_collection_add ((GeeCollection*) all_scopes, start_scope);
	{
		GeeIterator* _m_it;
		_m_it = gee_iterable_iterator ((GeeIterable*) scanner);
		while (gee_iterator_next (_m_it)) {
			GtkMateMarker* m;
			GtkMateScope* expected_scope;
			m = (GtkMateMarker*) gee_iterator_get (_m_it);
			expected_scope = gtk_mate_parser_get_expected_scope (self, gtk_mate_scanner_get_current_scope (scanner), line_ix, scanner->position);
			if (expected_scope != NULL) {
				GtkMateTextLoc* _tmp3_;
				GtkMateTextLoc* _tmp2_;
				_tmp3_ = NULL;
				_tmp2_ = NULL;
				fprintf (stdout, "expected_scope: %s (%d, %d)\n", gtk_mate_scope_get_name (expected_scope), (_tmp2_ = gtk_mate_scope_start_loc (expected_scope))->line, (_tmp3_ = gtk_mate_scope_start_loc (expected_scope))->line_offset);
				(_tmp3_ == NULL) ? NULL : (_tmp3_ = (g_object_unref (_tmp3_), NULL));
				(_tmp2_ == NULL) ? NULL : (_tmp2_ = (g_object_unref (_tmp2_), NULL));
			} else {
				fprintf (stdout, "no expected scope\n");
			}
			fprintf (stdout, "  scope: %s (%d, %d) (line length: %d)\n", m->pattern->name, m->from, onig_match_end (m->match, 0), length);
			if (m->is_close_scope) {
				fprintf (stdout, "     (closing)\n");
				gtk_mate_parser_close_scope (self, scanner, expected_scope, line_ix, line, length, m, all_scopes, closed_scopes, removed_scopes);
			} else {
				if (GTK_MATE_IS_DOUBLE_PATTERN (m->pattern)) {
					fprintf (stdout, "     (opening)\n");
					gtk_mate_parser_open_scope (self, scanner, expected_scope, line_ix, line, length, m, all_scopes, closed_scopes, removed_scopes);
				} else {
					fprintf (stdout, "     (single)\n");
					gtk_mate_parser_single_scope (self, scanner, expected_scope, line_ix, line, length, m, all_scopes, closed_scopes, removed_scopes);
				}
			}
			/*stdout.printf("pretty:\n%s\n", root.pretty(2));*/
			scanner->position = onig_match_end (m->match, 0);
			(m == NULL) ? NULL : (m = (g_object_unref (m), NULL));
			(expected_scope == NULL) ? NULL : (expected_scope = (g_object_unref (expected_scope), NULL));
		}
		(_m_it == NULL) ? NULL : (_m_it = (g_object_unref (_m_it), NULL));
	}
	gtk_mate_parser_clear_line (self, line_ix, start_scope, all_scopes, closed_scopes, removed_scopes);
	end_scope2 = gtk_mate_scope_scope_at (self->root, line_ix, G_MAXINT);
	if (end_scope2 != NULL) {
		GtkMateScope* _tmp4_;
		_tmp4_ = NULL;
		end_scope2 = (_tmp4_ = gtk_mate_scope_containing_double_scope (end_scope2, line_ix), (end_scope2 == NULL) ? NULL : (end_scope2 = (g_object_unref (end_scope2), NULL)), _tmp4_);
	}
	fprintf (stdout, "end_scope2: %s\n", gtk_mate_scope_get_name (end_scope2));
	_tmp5_ = NULL;
	fprintf (stdout, "%s\n", _tmp5_ = gtk_mate_scope_pretty (self->root, 0));
	_tmp5_ = (g_free (_tmp5_), NULL);
	if (self->priv->_colourer != NULL) {
		/*stdout.printf("before_uncolour_scopes\n");*/
		gtk_mate_colourer_uncolour_scopes (self->priv->_colourer, removed_scopes);
		/*stdout.printf("before_colour_line_with_scopes\n");*/
		gtk_mate_colourer_colour_line_with_scopes (self->priv->_colourer, all_scopes);
	} else {
	}
	/*stdout.printf("after_colour_line_with_scopes\n");
	 stdout.printf("no colourer");*/
	return (_tmp6_ = end_scope1 != end_scope2, line = (g_free (line), NULL), (start_scope == NULL) ? NULL : (start_scope = (g_object_unref (start_scope), NULL)), (end_scope1 == NULL) ? NULL : (end_scope1 = (g_object_unref (end_scope1), NULL)), (scanner == NULL) ? NULL : (scanner = (g_object_unref (scanner), NULL)), (all_scopes == NULL) ? NULL : (all_scopes = (g_object_unref (all_scopes), NULL)), (closed_scopes == NULL) ? NULL : (closed_scopes = (g_object_unref (closed_scopes), NULL)), (removed_scopes == NULL) ? NULL : (removed_scopes = (g_object_unref (removed_scopes), NULL)), (end_scope2 == NULL) ? NULL : (end_scope2 = (g_object_unref (end_scope2), NULL)), _tmp6_);
}


void gtk_mate_parser_clear_line (GtkMateParser* self, gint line_ix, GtkMateScope* start_scope, GeeArrayList* all_scopes, GeeArrayList* closed_scopes, GeeArrayList* removed_scopes) {
	GtkMateScope* _tmp0_;
	GtkMateScope* cs;
	GeeArrayList* scopes_that_closed_on_line;
	GtkMateScope* _tmp3_;
	GtkMateScope* ts;
	g_return_if_fail (self != NULL);
	g_return_if_fail (start_scope != NULL);
	g_return_if_fail (all_scopes != NULL);
	g_return_if_fail (closed_scopes != NULL);
	g_return_if_fail (removed_scopes != NULL);
	/* If we are reparsing, we might find that some scopes have disappeared,
	 delete them:*/
	_tmp0_ = NULL;
	cs = (_tmp0_ = start_scope, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	while (cs != NULL) {
		GeeArrayList* removed;
		GtkMateScope* _tmp2_;
		GtkMateScope* _tmp1_;
		fprintf (stdout, "  removing_scopes from: %s\n", gtk_mate_scope_get_name (cs));
		removed = gtk_mate_scope_delete_any_on_line_not_in (cs, line_ix, all_scopes);
		{
			GeeIterator* _rs_it;
			_rs_it = gee_iterable_iterator ((GeeIterable*) removed);
			while (gee_iterator_next (_rs_it)) {
				GtkMateScope* rs;
				rs = (GtkMateScope*) gee_iterator_get (_rs_it);
				gee_collection_add ((GeeCollection*) removed_scopes, rs);
				(rs == NULL) ? NULL : (rs = (g_object_unref (rs), NULL));
			}
			(_rs_it == NULL) ? NULL : (_rs_it = (g_object_unref (_rs_it), NULL));
		}
		_tmp2_ = NULL;
		_tmp1_ = NULL;
		cs = (_tmp2_ = (_tmp1_ = cs->parent, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (cs == NULL) ? NULL : (cs = (g_object_unref (cs), NULL)), _tmp2_);
		(removed == NULL) ? NULL : (removed = (g_object_unref (removed), NULL));
	}
	/* @removed_scopes += removed_scopes
	 any that we expected to close on this line that now don't?
	 first build list of scopes that close on this line (including ones
	 that did but haven't been removed yet).*/
	scopes_that_closed_on_line = gee_array_list_new (GTK_MATE_TYPE_SCOPE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	_tmp3_ = NULL;
	ts = (_tmp3_ = start_scope, (_tmp3_ == NULL) ? NULL : g_object_ref (_tmp3_));
	while (ts->parent != NULL) {
		GtkMateScope* _tmp5_;
		GtkMateScope* _tmp4_;
		fprintf (stdout, "checking for closing scope: %s (%d)\n", gtk_mate_scope_get_name (ts), gtk_mate_scope_inner_end_line (ts));
		if (gtk_mate_scope_inner_end_line (ts) == line_ix) {
			fprintf (stdout, "scope that closed on line: %s\n", gtk_mate_scope_get_name (ts));
			gee_collection_add ((GeeCollection*) scopes_that_closed_on_line, ts);
		}
		_tmp5_ = NULL;
		_tmp4_ = NULL;
		ts = (_tmp5_ = (_tmp4_ = ts->parent, (_tmp4_ == NULL) ? NULL : g_object_ref (_tmp4_)), (ts == NULL) ? NULL : (ts = (g_object_unref (ts), NULL)), _tmp5_);
	}
	{
		GeeIterator* _s_it;
		_s_it = gee_iterable_iterator ((GeeIterable*) scopes_that_closed_on_line);
		while (gee_iterator_next (_s_it)) {
			GtkMateScope* s;
			s = (GtkMateScope*) gee_iterator_get (_s_it);
			if (!gee_collection_contains ((GeeCollection*) closed_scopes, s)) {
				if (s->is_capture) {
					/* stdout.printf("    removing scope: %s\n", s.name);*/
					gtk_mate_scope_delete_child (s->parent, s);
					gee_collection_add ((GeeCollection*) removed_scopes, s);
				} else {
					GtkTextIter end_iter;
					gint end_line;
					gint end_line_index;
					/* @removed_scopes << s*/
					if (self->priv->_colourer != NULL) {
						gtk_mate_colourer_uncolour_scope (self->priv->_colourer, s, FALSE);
					}
					/* s.inner_end_mark = null;
					 s.end_mark = null;
					 s.is_open = true;*/
					end_iter = gtk_mate_buffer_end_iter (self->priv->_buffer);
					end_line = gtk_text_iter_get_line (&end_iter);
					end_line_index = gtk_text_iter_get_line_index (&end_iter);
					gtk_mate_scope_inner_end_mark_set (s, end_line, end_line_index, FALSE);
					gtk_mate_scope_end_mark_set (s, end_line, end_line_index, FALSE);
					s->is_open = TRUE;
				}
			}
			(s == NULL) ? NULL : (s = (g_object_unref (s), NULL));
		}
		(_s_it == NULL) ? NULL : (_s_it = (g_object_unref (_s_it), NULL));
	}
	(cs == NULL) ? NULL : (cs = (g_object_unref (cs), NULL));
	(scopes_that_closed_on_line == NULL) ? NULL : (scopes_that_closed_on_line = (g_object_unref (scopes_that_closed_on_line), NULL));
	(ts == NULL) ? NULL : (ts = (g_object_unref (ts), NULL));
}


GtkMateScope* gtk_mate_parser_get_expected_scope (GtkMateParser* self, GtkMateScope* current_scope, gint line, gint line_offset) {
	GtkMateTextLoc* _tmp0_;
	GtkMateScope* _tmp1_;
	GtkMateScope* expected_scope;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (current_scope != NULL, NULL);
	/*stdout.printf("get_expected_scope(%s, %d, %d)\n", current_scope.name, line, line_offset);*/
	_tmp0_ = NULL;
	_tmp1_ = NULL;
	expected_scope = (_tmp1_ = gtk_mate_scope_first_child_after (current_scope, _tmp0_ = gtk_mate_text_loc_make (line, line_offset)), (_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_object_unref (_tmp0_), NULL)), _tmp1_);
	/*stdout.printf("first_child_after: %s\n", expected_scope.name);*/
	g_assert (expected_scope != current_scope);
	if (expected_scope != NULL) {
		if (gtk_mate_scope_start_line (expected_scope) != line) {
			GtkMateScope* _tmp2_;
			_tmp2_ = NULL;
			expected_scope = (_tmp2_ = NULL, (expected_scope == NULL) ? NULL : (expected_scope = (g_object_unref (expected_scope), NULL)), _tmp2_);
		}
		while (TRUE) {
			gboolean _tmp3_;
			GtkMateScope* _tmp5_;
			GtkMateScope* _tmp4_;
			_tmp3_ = FALSE;
			if (expected_scope != NULL) {
				_tmp3_ = expected_scope->is_capture;
			} else {
				_tmp3_ = FALSE;
			}
			if (!_tmp3_) {
				break;
			}
			_tmp5_ = NULL;
			_tmp4_ = NULL;
			expected_scope = (_tmp5_ = (_tmp4_ = expected_scope->parent, (_tmp4_ == NULL) ? NULL : g_object_ref (_tmp4_)), (expected_scope == NULL) ? NULL : (expected_scope = (g_object_unref (expected_scope), NULL)), _tmp5_);
		}
	}
	return expected_scope;
}


static char* string_substring (const char* self, glong offset, glong len) {
	glong string_length;
	const char* start;
	g_return_val_if_fail (self != NULL, NULL);
	string_length = g_utf8_strlen (self, -1);
	if (offset < 0) {
		offset = string_length + offset;
		g_return_val_if_fail (offset >= 0, NULL);
	} else {
		g_return_val_if_fail (offset <= string_length, NULL);
	}
	if (len < 0) {
		len = string_length - offset;
	}
	g_return_val_if_fail ((offset + len) <= string_length, NULL);
	start = g_utf8_offset_to_pointer (self, offset);
	return g_strndup (start, ((gchar*) g_utf8_offset_to_pointer (start, len)) - ((gchar*) start));
}


void gtk_mate_parser_close_scope (GtkMateParser* self, GtkMateScanner* scanner, GtkMateScope* expected_scope, gint line_ix, const char* line, gint length, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes, GeeArrayList* removed_scopes) {
	char* end_match_string;
	gboolean _tmp0_;
	gboolean _tmp1_;
	gboolean _tmp2_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scanner != NULL);
	g_return_if_fail (line != NULL);
	g_return_if_fail (m != NULL);
	g_return_if_fail (all_scopes != NULL);
	g_return_if_fail (closed_scopes != NULL);
	g_return_if_fail (removed_scopes != NULL);
	end_match_string = string_substring (line, (glong) m->from, (glong) (onig_match_end (m->match, 0) - m->from));
	_tmp0_ = FALSE;
	_tmp1_ = FALSE;
	_tmp2_ = FALSE;
	if (gtk_mate_scanner_get_current_scope (scanner)->end_mark != NULL) {
		GtkMateTextLoc* _tmp4_;
		GtkMateTextLoc* _tmp3_;
		_tmp4_ = NULL;
		_tmp3_ = NULL;
		_tmp2_ = gtk_mate_text_loc_equal (_tmp3_ = gtk_mate_scope_end_loc (gtk_mate_scanner_get_current_scope (scanner)), _tmp4_ = gtk_mate_text_loc_make (line_ix, onig_match_end (m->match, 0)));
		(_tmp4_ == NULL) ? NULL : (_tmp4_ = (g_object_unref (_tmp4_), NULL));
		(_tmp3_ == NULL) ? NULL : (_tmp3_ = (g_object_unref (_tmp3_), NULL));
	} else {
		_tmp2_ = FALSE;
	}
	if (_tmp2_) {
		GtkMateTextLoc* _tmp6_;
		GtkMateTextLoc* _tmp5_;
		_tmp6_ = NULL;
		_tmp5_ = NULL;
		_tmp1_ = gtk_mate_text_loc_equal (_tmp5_ = gtk_mate_scope_inner_end_loc (gtk_mate_scanner_get_current_scope (scanner)), _tmp6_ = gtk_mate_text_loc_make (line_ix, m->from));
		(_tmp6_ == NULL) ? NULL : (_tmp6_ = (g_object_unref (_tmp6_), NULL));
		(_tmp5_ == NULL) ? NULL : (_tmp5_ = (g_object_unref (_tmp5_), NULL));
	} else {
		_tmp1_ = FALSE;
	}
	if (_tmp1_) {
		_tmp0_ = _vala_strcmp0 (gtk_mate_scanner_get_current_scope (scanner)->end_match_string, end_match_string) == 0;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		GSequenceIter* iter;
		/* we have already parsed this line and this scope ends here
		 Re-add the captures from the end of the current scope to the 
		 tracking arrays*/
		iter = g_sequence_get_begin_iter (gtk_mate_scope_get_children (gtk_mate_scanner_get_current_scope (scanner)));
		while (!g_sequence_iter_is_end (iter)) {
			GtkMateScope* _tmp7_;
			GtkMateScope* child;
			gboolean _tmp8_;
			_tmp7_ = NULL;
			child = (_tmp7_ = (GtkMateScope*) g_sequence_get (iter), (_tmp7_ == NULL) ? NULL : g_object_ref (_tmp7_));
			_tmp8_ = FALSE;
			if (child->is_capture) {
				_tmp8_ = gtk_mate_scope_start_line (child) == line_ix;
			} else {
				_tmp8_ = FALSE;
			}
			if (_tmp8_) {
				if (!gee_collection_contains ((GeeCollection*) closed_scopes, child)) {
					gee_collection_add ((GeeCollection*) closed_scopes, child);
				}
				if (!gee_collection_contains ((GeeCollection*) all_scopes, child)) {
					gee_collection_add ((GeeCollection*) all_scopes, child);
				}
			}
			iter = g_sequence_iter_next (iter);
			(child == NULL) ? NULL : (child = (g_object_unref (child), NULL));
		}
	} else {
		char* _tmp11_;
		char* *_tmp10_;
		const char* _tmp9_;
		/* stdout.printf("closing scope matches expected\n");
		 stdout.printf("closing scope at %d\n", m.from);*/
		if (self->priv->_colourer != NULL) {
			gtk_mate_colourer_uncolour_scope (self->priv->_colourer, gtk_mate_scanner_get_current_scope (scanner), FALSE);
		}
		gtk_mate_parser_set_inner_end_mark_safely (self, gtk_mate_scanner_get_current_scope (scanner), m, line_ix, length, 0);
		gtk_mate_parser_set_end_mark_safely (self, gtk_mate_scanner_get_current_scope (scanner), m, line_ix, length, 0);
		gtk_mate_scanner_get_current_scope (scanner)->is_open = FALSE;
		_tmp11_ = NULL;
		_tmp9_ = NULL;
		_tmp10_ = &gtk_mate_scanner_get_current_scope (scanner)->end_match_string;
		(*_tmp10_) = (_tmp11_ = (_tmp9_ = end_match_string, (_tmp9_ == NULL) ? NULL : g_strdup (_tmp9_)), (*_tmp10_) = (g_free ((*_tmp10_)), NULL), _tmp11_);
		/*stdout.printf("end_match_string: '%s'\n", scanner.current_scope.end_match_string);*/
		gtk_mate_parser_handle_captures (self, line_ix, length, line, gtk_mate_scanner_get_current_scope (scanner), m, all_scopes, closed_scopes);
		if (expected_scope != NULL) {
			gtk_mate_scope_delete_child (gtk_mate_scanner_get_current_scope (scanner), expected_scope);
			gee_collection_add ((GeeCollection*) removed_scopes, expected_scope);
		}
	}
	/* @removed_scopes << expected_scope*/
	gee_collection_add ((GeeCollection*) removed_scopes, gtk_mate_scanner_get_current_scope (scanner));
	/* so it gets uncoloured*/
	gee_collection_add ((GeeCollection*) closed_scopes, gtk_mate_scanner_get_current_scope (scanner));
	gtk_mate_scanner_set_current_scope (scanner, gtk_mate_scanner_get_current_scope (scanner)->parent);
	gee_collection_add ((GeeCollection*) all_scopes, gtk_mate_scanner_get_current_scope (scanner));
	end_match_string = (g_free (end_match_string), NULL);
}


void gtk_mate_parser_open_scope (GtkMateParser* self, GtkMateScanner* scanner, GtkMateScope* expected_scope, gint line_ix, const char* line, gint length, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes, GeeArrayList* removed_scopes) {
	GtkMateScope* s;
	GtkMatePattern* _tmp1_;
	GtkMatePattern* _tmp0_;
	OnigMatch* _tmp3_;
	OnigMatch* _tmp2_;
	char* _tmp4_;
	GtkTextIter end_iter;
	gint end_line;
	gint end_line_index;
	GtkMateScope* _tmp6_;
	GtkMateScope* _tmp5_;
	GtkMateScope* _tmp7_;
	GtkMateScope* new_scope;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scanner != NULL);
	g_return_if_fail (line != NULL);
	g_return_if_fail (m != NULL);
	g_return_if_fail (all_scopes != NULL);
	g_return_if_fail (closed_scopes != NULL);
	g_return_if_fail (removed_scopes != NULL);
	/* stdout.printf("[opening with %d patterns], \n", ((DoublePattern) m.pattern).patterns.size);*/
	s = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, m->pattern->name));
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	s->pattern = (_tmp1_ = (_tmp0_ = m->pattern, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (s->pattern == NULL) ? NULL : (s->pattern = (g_object_unref (s->pattern), NULL)), _tmp1_);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	s->open_match = (_tmp3_ = (_tmp2_ = m->match, (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (s->open_match == NULL) ? NULL : (s->open_match = (g_object_unref (s->open_match), NULL)), _tmp3_);
	gtk_mate_parser_set_start_mark_safely (self, s, m, line_ix, length, 0);
	gtk_mate_parser_set_inner_start_mark_safely (self, s, m, line_ix, length, 0);
	_tmp4_ = NULL;
	s->begin_match_string = (_tmp4_ = string_substring (line, (glong) m->from, (glong) (onig_match_end (m->match, 0) - m->from)), s->begin_match_string = (g_free (s->begin_match_string), NULL), _tmp4_);
	end_iter = gtk_mate_buffer_end_iter (self->priv->_buffer);
	end_line = gtk_text_iter_get_line (&end_iter);
	end_line_index = gtk_text_iter_get_line_index (&end_iter);
	gtk_mate_scope_inner_end_mark_set (s, end_line, end_line_index, FALSE);
	gtk_mate_scope_end_mark_set (s, end_line, end_line_index, FALSE);
	s->is_open = TRUE;
	s->is_capture = FALSE;
	_tmp6_ = NULL;
	_tmp5_ = NULL;
	s->parent = (_tmp6_ = (_tmp5_ = gtk_mate_scanner_get_current_scope (scanner), (_tmp5_ == NULL) ? NULL : g_object_ref (_tmp5_)), (s->parent == NULL) ? NULL : (s->parent = (g_object_unref (s->parent), NULL)), _tmp6_);
	_tmp7_ = NULL;
	new_scope = (_tmp7_ = s, (_tmp7_ == NULL) ? NULL : g_object_ref (_tmp7_));
	/* is this a bug? captures aren't necessarily to be put into all_scopes yet surely?*/
	if (expected_scope != NULL) {
		/* check mod ending scopes as the new one will not have a closing marker
		 but the expected one will:*/
		if (gtk_mate_scope_surface_identical_to_modulo_ending (s, expected_scope)) {
			GtkMateScope* _tmp9_;
			GtkMateScope* _tmp8_;
			GSequenceIter* iter;
			/* stdout.printf("surface_identical_mod_ending: keep expected\n");
			 don't need to do anything as we have already found this,
			 but let's keep the old scope since it will have children and what not.*/
			_tmp9_ = NULL;
			_tmp8_ = NULL;
			new_scope = (_tmp9_ = (_tmp8_ = expected_scope, (_tmp8_ == NULL) ? NULL : g_object_ref (_tmp8_)), (new_scope == NULL) ? NULL : (new_scope = (g_object_unref (new_scope), NULL)), _tmp9_);
			iter = g_sequence_get_begin_iter (gtk_mate_scope_get_children (expected_scope));
			while (!g_sequence_iter_is_end (iter)) {
				GtkMateScope* _tmp10_;
				GtkMateScope* child;
				_tmp10_ = NULL;
				child = (_tmp10_ = (GtkMateScope*) g_sequence_get (iter), (_tmp10_ == NULL) ? NULL : g_object_ref (_tmp10_));
				gee_collection_add ((GeeCollection*) closed_scopes, child);
				gee_collection_add ((GeeCollection*) all_scopes, child);
				iter = g_sequence_iter_next (iter);
				(child == NULL) ? NULL : (child = (g_object_unref (child), NULL));
			}
			gtk_mate_scanner_set_current_scope (scanner, expected_scope);
		} else {
			/*stdout.printf("surface_NOT_identical_mod_ending: replace expected\n");*/
			if (gtk_mate_scope_overlaps_with (s, expected_scope)) {
				gtk_mate_scope_delete_child (gtk_mate_scanner_get_current_scope (scanner), expected_scope);
				/* removed_scopes << expected_scope*/
				gee_collection_add ((GeeCollection*) removed_scopes, expected_scope);
			}
			gtk_mate_parser_handle_captures (self, line_ix, length, line, s, m, all_scopes, closed_scopes);
			gtk_mate_scope_add_child (gtk_mate_scanner_get_current_scope (scanner), s);
			gtk_mate_scanner_set_current_scope (scanner, s);
		}
	} else {
		gtk_mate_parser_handle_captures (self, line_ix, length, line, s, m, all_scopes, closed_scopes);
		gtk_mate_scope_add_child (gtk_mate_scanner_get_current_scope (scanner), s);
		gtk_mate_scanner_set_current_scope (scanner, s);
	}
	gee_collection_add ((GeeCollection*) all_scopes, new_scope);
	(s == NULL) ? NULL : (s = (g_object_unref (s), NULL));
	(new_scope == NULL) ? NULL : (new_scope = (g_object_unref (new_scope), NULL));
}


void gtk_mate_parser_single_scope (GtkMateParser* self, GtkMateScanner* scanner, GtkMateScope* expected_scope, gint line_ix, const char* line, gint length, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes, GeeArrayList* removed_scopes) {
	GtkMateScope* s;
	GtkMatePattern* _tmp1_;
	GtkMatePattern* _tmp0_;
	OnigMatch* _tmp3_;
	OnigMatch* _tmp2_;
	char* _tmp4_;
	GtkMateScope* _tmp6_;
	GtkMateScope* _tmp5_;
	GtkMateScope* _tmp7_;
	GtkMateScope* new_scope;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scanner != NULL);
	g_return_if_fail (line != NULL);
	g_return_if_fail (m != NULL);
	g_return_if_fail (all_scopes != NULL);
	g_return_if_fail (closed_scopes != NULL);
	g_return_if_fail (removed_scopes != NULL);
	s = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, m->pattern->name));
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	s->pattern = (_tmp1_ = (_tmp0_ = m->pattern, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (s->pattern == NULL) ? NULL : (s->pattern = (g_object_unref (s->pattern), NULL)), _tmp1_);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	s->open_match = (_tmp3_ = (_tmp2_ = m->match, (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (s->open_match == NULL) ? NULL : (s->open_match = (g_object_unref (s->open_match), NULL)), _tmp3_);
	gtk_mate_parser_set_start_mark_safely (self, s, m, line_ix, length, 0);
	gtk_mate_parser_set_end_mark_safely (self, s, m, line_ix, length, 0);
	s->is_open = FALSE;
	s->is_capture = FALSE;
	_tmp4_ = NULL;
	s->begin_match_string = (_tmp4_ = string_substring (line, (glong) m->from, (glong) (onig_match_end (m->match, 0) - m->from)), s->begin_match_string = (g_free (s->begin_match_string), NULL), _tmp4_);
	/*stdout.printf("_match_string: '%s'\n", s.begin_match_string);*/
	_tmp6_ = NULL;
	_tmp5_ = NULL;
	s->parent = (_tmp6_ = (_tmp5_ = gtk_mate_scanner_get_current_scope (scanner), (_tmp5_ == NULL) ? NULL : g_object_ref (_tmp5_)), (s->parent == NULL) ? NULL : (s->parent = (g_object_unref (s->parent), NULL)), _tmp6_);
	_tmp7_ = NULL;
	new_scope = (_tmp7_ = s, (_tmp7_ == NULL) ? NULL : g_object_ref (_tmp7_));
	if (expected_scope != NULL) {
		if (gtk_mate_scope_surface_identical_to (s, expected_scope)) {
			GtkMateScope* _tmp9_;
			GtkMateScope* _tmp8_;
			GSequenceIter* iter;
			_tmp9_ = NULL;
			_tmp8_ = NULL;
			new_scope = (_tmp9_ = (_tmp8_ = expected_scope, (_tmp8_ == NULL) ? NULL : g_object_ref (_tmp8_)), (new_scope == NULL) ? NULL : (new_scope = (g_object_unref (new_scope), NULL)), _tmp9_);
			iter = g_sequence_get_begin_iter (gtk_mate_scope_get_children (expected_scope));
			while (!g_sequence_iter_is_end (iter)) {
				gee_collection_add ((GeeCollection*) closed_scopes, (GtkMateScope*) g_sequence_get (iter));
				iter = g_sequence_iter_next (iter);
			}
		} else {
			gtk_mate_parser_handle_captures (self, line_ix, length, line, s, m, all_scopes, closed_scopes);
			if (gtk_mate_scope_overlaps_with (s, expected_scope)) {
				/* stdout.printf("%s overlaps with expected %s (current: %s)\n", s.name, expected_scope.name, scanner.current_scope.name);*/
				if (expected_scope == gtk_mate_scanner_get_current_scope (scanner)) {
				} else {
					/* we expected this scope to close, but it doesn't*/
					gtk_mate_scope_delete_child (gtk_mate_scanner_get_current_scope (scanner), expected_scope);
					/* removed_scopes << expected_scope*/
					gee_collection_add ((GeeCollection*) removed_scopes, expected_scope);
				}
			}
			gtk_mate_scope_add_child (gtk_mate_scanner_get_current_scope (scanner), s);
		}
	} else {
		gtk_mate_parser_handle_captures (self, line_ix, length, line, s, m, all_scopes, closed_scopes);
		gtk_mate_scope_add_child (gtk_mate_scanner_get_current_scope (scanner), s);
	}
	gee_collection_add ((GeeCollection*) all_scopes, new_scope);
	gee_collection_add ((GeeCollection*) closed_scopes, new_scope);
	(s == NULL) ? NULL : (s = (g_object_unref (s), NULL));
	(new_scope == NULL) ? NULL : (new_scope = (g_object_unref (new_scope), NULL));
}


/* Opens scopes for captures AND creates closing regexp from
 captures if necessary.*/
void gtk_mate_parser_handle_captures (GtkMateParser* self, gint line_ix, gint length, const char* line, GtkMateScope* scope, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes) {
	OnigRx* _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (line != NULL);
	g_return_if_fail (scope != NULL);
	g_return_if_fail (m != NULL);
	g_return_if_fail (all_scopes != NULL);
	g_return_if_fail (closed_scopes != NULL);
	_tmp0_ = NULL;
	_tmp0_ = gtk_mate_parser_make_closing_regex (self, line, scope, m);
	(_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_object_unref (_tmp0_), NULL));
	gtk_mate_parser_collect_child_captures (self, line_ix, length, scope, m, all_scopes, closed_scopes);
}


static glong string_get_length (const char* self) {
	g_return_val_if_fail (self != NULL, 0L);
	return g_utf8_strlen (self, -1);
}


OnigRx* gtk_mate_parser_make_closing_regex (GtkMateParser* self, const char* line, GtkMateScope* scope, GtkMateMarker* m) {
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (line != NULL, NULL);
	g_return_val_if_fail (scope != NULL, NULL);
	g_return_val_if_fail (m != NULL, NULL);
	_tmp0_ = FALSE;
	if (GTK_MATE_IS_DOUBLE_PATTERN (m->pattern)) {
		_tmp0_ = !m->is_close_scope;
	} else {
		_tmp0_ = FALSE;
	}
	/*stdout.printf("make_closing_regex\n");
	 new_end = pattern.end.gsub(/\\([0-9]+)/) do
	 md.captures.send(:[], $1.to_i-1)
	 end*/
	if (_tmp0_) {
		GtkMateDoublePattern* _tmp1_;
		GtkMateDoublePattern* dp;
		OnigRx* rx;
		OnigMatch* match;
		gint pos;
		GString* src;
		gboolean found;
		OnigMatch* _tmp2_;
		OnigRx* _tmp5_;
		_tmp1_ = NULL;
		dp = (_tmp1_ = GTK_MATE_DOUBLE_PATTERN (m->pattern), (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_));
		/*stdout.printf("making closing regex: %s (%d)\n", dp.end_string, (int) dp.end_string.length);*/
		rx = onig_rx_make1 ("\\\\(\\d+)");
		match = NULL;
		pos = 0;
		src = g_string_new ("");
		found = FALSE;
		_tmp2_ = NULL;
		while ((match = (_tmp2_ = onig_rx_search (rx, dp->end_string, pos, (gint) string_get_length (dp->end_string)), (match == NULL) ? NULL : (match = (g_object_unref (match), NULL)), _tmp2_)) != NULL) {
			char* _tmp3_;
			char* numstr;
			gint num;
			char* capstr;
			found = TRUE;
			_tmp3_ = NULL;
			g_string_append (src, _tmp3_ = string_substring (dp->end_string, (glong) pos, (glong) (onig_match_begin (match, 0) - pos)));
			_tmp3_ = (g_free (_tmp3_), NULL);
			numstr = string_substring (dp->end_string, (glong) onig_match_begin (match, 1), (glong) (onig_match_end (match, 1) - onig_match_begin (match, 1)));
			num = atoi (numstr);
			/*stdout.printf("capture found: %d\n", num);*/
			capstr = string_substring (line, (glong) onig_match_begin (m->match, num), (glong) (onig_match_end (m->match, num) - onig_match_begin (m->match, num)));
			g_string_append (src, capstr);
			pos = onig_match_end (match, 1);
			numstr = (g_free (numstr), NULL);
			capstr = (g_free (capstr), NULL);
		}
		if (found) {
			char* _tmp4_;
			_tmp4_ = NULL;
			g_string_append (src, _tmp4_ = string_substring (dp->end_string, (glong) pos, string_get_length (dp->end_string) - pos));
			_tmp4_ = (g_free (_tmp4_), NULL);
		} else {
			g_string_append (src, dp->end_string);
		}
		/*stdout.printf("src: '%s'\n", src.str);*/
		_tmp5_ = NULL;
		scope->closing_regex = (_tmp5_ = onig_rx_make1 (src->str), (scope->closing_regex == NULL) ? NULL : (scope->closing_regex = (g_object_unref (scope->closing_regex), NULL)), _tmp5_);
		(dp == NULL) ? NULL : (dp = (g_object_unref (dp), NULL));
		(rx == NULL) ? NULL : (rx = (g_object_unref (rx), NULL));
		(match == NULL) ? NULL : (match = (g_object_unref (match), NULL));
		(src == NULL) ? NULL : (src = (g_string_free (src, TRUE), NULL));
	}
	return NULL;
}


void gtk_mate_parser_set_start_mark_safely (GtkMateParser* self, GtkMateScope* scope, GtkMateMarker* m, gint line_ix, gint length, gint cap) {
	gint to;
	gboolean _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	g_return_if_fail (m != NULL);
	to = onig_match_begin (m->match, cap);
	_tmp0_ = FALSE;
	if (to == length) {
		_tmp0_ = gtk_text_buffer_get_line_count ((GtkTextBuffer*) self->priv->_buffer) > (line_ix + 1);
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		gtk_mate_scope_start_mark_set (scope, line_ix + 1, 0, FALSE);
	} else {
		gtk_mate_scope_start_mark_set (scope, line_ix, MIN (to, length), FALSE);
	}
}


void gtk_mate_parser_set_inner_start_mark_safely (GtkMateParser* self, GtkMateScope* scope, GtkMateMarker* m, gint line_ix, gint length, gint cap) {
	gint to;
	gboolean _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	g_return_if_fail (m != NULL);
	to = onig_match_end (m->match, cap);
	_tmp0_ = FALSE;
	if (to == length) {
		_tmp0_ = gtk_text_buffer_get_line_count ((GtkTextBuffer*) self->priv->_buffer) > (line_ix + 1);
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		gtk_mate_scope_inner_start_mark_set (scope, line_ix + 1, 0, TRUE);
	} else {
		gtk_mate_scope_inner_start_mark_set (scope, line_ix, MIN (to, length), TRUE);
	}
}


void gtk_mate_parser_set_inner_end_mark_safely (GtkMateParser* self, GtkMateScope* scope, GtkMateMarker* m, gint line_ix, gint length, gint cap) {
	gint to;
	gboolean _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	g_return_if_fail (m != NULL);
	to = onig_match_end (m->match, cap);
	_tmp0_ = FALSE;
	if (to == length) {
		_tmp0_ = gtk_text_buffer_get_line_count ((GtkTextBuffer*) self->priv->_buffer) > (line_ix + 1);
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		gtk_mate_scope_inner_end_mark_set (scope, line_ix, length - 1, TRUE);
	} else {
		gtk_mate_scope_inner_end_mark_set (scope, line_ix, MIN (to, length), TRUE);
	}
}


void gtk_mate_parser_set_end_mark_safely (GtkMateParser* self, GtkMateScope* scope, GtkMateMarker* m, gint line_ix, gint length, gint cap) {
	gint to;
	gboolean _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	g_return_if_fail (m != NULL);
	to = onig_match_end (m->match, cap);
	_tmp0_ = FALSE;
	if (to == length) {
		_tmp0_ = gtk_text_buffer_get_line_count ((GtkTextBuffer*) self->priv->_buffer) > (line_ix + 1);
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		gtk_mate_scope_end_mark_set (scope, line_ix, length - 1, TRUE);
	} else {
		gtk_mate_scope_end_mark_set (scope, line_ix, MIN (to, length), TRUE);
	}
}


void gtk_mate_parser_collect_child_captures (GtkMateParser* self, gint line_ix, gint length, GtkMateScope* scope, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes) {
	GtkMateScope* s;
	GeeHashMap* captures;
	GeeArrayList* capture_scopes;
	gint best_length;
	gint new_length;
	GeeArrayList* placed_scopes;
	GtkMateScope* parent_scope;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	g_return_if_fail (m != NULL);
	g_return_if_fail (all_scopes != NULL);
	g_return_if_fail (closed_scopes != NULL);
	s = NULL;
	captures = NULL;
	if (GTK_MATE_IS_SINGLE_PATTERN (m->pattern)) {
		GeeHashMap* _tmp1_;
		GeeHashMap* _tmp0_;
		_tmp1_ = NULL;
		_tmp0_ = NULL;
		captures = (_tmp1_ = (_tmp0_ = GTK_MATE_SINGLE_PATTERN (m->pattern)->captures, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (captures == NULL) ? NULL : (captures = (g_object_unref (captures), NULL)), _tmp1_);
	} else {
		if (m->is_close_scope) {
			GeeHashMap* _tmp3_;
			GeeHashMap* _tmp2_;
			_tmp3_ = NULL;
			_tmp2_ = NULL;
			captures = (_tmp3_ = (_tmp2_ = GTK_MATE_DOUBLE_PATTERN (m->pattern)->end_captures, (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (captures == NULL) ? NULL : (captures = (g_object_unref (captures), NULL)), _tmp3_);
		} else {
			GeeHashMap* _tmp5_;
			GeeHashMap* _tmp4_;
			_tmp5_ = NULL;
			_tmp4_ = NULL;
			captures = (_tmp5_ = (_tmp4_ = GTK_MATE_DOUBLE_PATTERN (m->pattern)->begin_captures, (_tmp4_ == NULL) ? NULL : g_object_ref (_tmp4_)), (captures == NULL) ? NULL : (captures = (g_object_unref (captures), NULL)), _tmp5_);
		}
		if (GTK_MATE_DOUBLE_PATTERN (m->pattern)->both_captures != NULL) {
			GeeHashMap* _tmp7_;
			GeeHashMap* _tmp6_;
			_tmp7_ = NULL;
			_tmp6_ = NULL;
			captures = (_tmp7_ = (_tmp6_ = GTK_MATE_DOUBLE_PATTERN (m->pattern)->both_captures, (_tmp6_ == NULL) ? NULL : g_object_ref (_tmp6_)), (captures == NULL) ? NULL : (captures = (g_object_unref (captures), NULL)), _tmp7_);
		}
	}
	capture_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	/* create capture scopes*/
	if (captures != NULL) {
		{
			GeeSet* _tmp8_;
			GeeIterator* _tmp9_;
			GeeIterator* _cap_it;
			_tmp8_ = NULL;
			_tmp9_ = NULL;
			_cap_it = (_tmp9_ = gee_iterable_iterator ((GeeIterable*) (_tmp8_ = gee_map_get_keys ((GeeMap*) captures))), (_tmp8_ == NULL) ? NULL : (_tmp8_ = (g_object_unref (_tmp8_), NULL)), _tmp9_);
			while (gee_iterator_next (_cap_it)) {
				gint cap;
				cap = GPOINTER_TO_INT (gee_iterator_get (_cap_it));
				if (onig_match_begin (m->match, cap) != (-1)) {
					GtkMateScope* _tmp11_;
					char* _tmp10_;
					GtkMatePattern* _tmp13_;
					GtkMatePattern* _tmp12_;
					GtkMateScope* _tmp15_;
					GtkMateScope* _tmp14_;
					_tmp11_ = NULL;
					_tmp10_ = NULL;
					s = (_tmp11_ = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, _tmp10_ = (char*) gee_map_get ((GeeMap*) captures, GINT_TO_POINTER (cap)))), (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), _tmp11_);
					_tmp10_ = (g_free (_tmp10_), NULL);
					_tmp13_ = NULL;
					_tmp12_ = NULL;
					s->pattern = (_tmp13_ = (_tmp12_ = scope->pattern, (_tmp12_ == NULL) ? NULL : g_object_ref (_tmp12_)), (s->pattern == NULL) ? NULL : (s->pattern = (g_object_unref (s->pattern), NULL)), _tmp13_);
					gtk_mate_scope_start_mark_set (s, line_ix, MIN (onig_match_begin (m->match, cap), length - 1), FALSE);
					gtk_mate_parser_set_end_mark_safely (self, s, m, line_ix, length, cap);
					s->is_open = FALSE;
					s->is_capture = TRUE;
					_tmp15_ = NULL;
					_tmp14_ = NULL;
					s->parent = (_tmp15_ = (_tmp14_ = scope, (_tmp14_ == NULL) ? NULL : g_object_ref (_tmp14_)), (s->parent == NULL) ? NULL : (s->parent = (g_object_unref (s->parent), NULL)), _tmp15_);
					gee_collection_add ((GeeCollection*) capture_scopes, s);
					gee_collection_add ((GeeCollection*) all_scopes, s);
					gee_collection_add ((GeeCollection*) closed_scopes, s);
				}
			}
			(_cap_it == NULL) ? NULL : (_cap_it = (g_object_unref (_cap_it), NULL));
		}
	}
	/* Now we arrange the capture scopes into a tree under the matched
	 scope. We do this by processing the captures in order of offset and 
	 length. For each capture, we check to see if it is a child of an already 
	 placed capture, and if so we add it as a child (we know that the latest 
	 such capture is the one to add it to by the ordering). If not we
	 add it as a child of the matched scope.*/
	best_length = 0;
	new_length = 0;
	placed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	parent_scope = NULL;
	while (gee_collection_get_size ((GeeCollection*) capture_scopes) > 0) {
		GtkMateScope* _tmp16_;
		GtkMateScope* _tmp21_;
		_tmp16_ = NULL;
		s = (_tmp16_ = NULL, (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), _tmp16_);
		/* find first and longest remaining scope (put it in 's')*/
		{
			GeeIterator* _cs_it;
			/* find first and longest remaining scope (put it in 's')*/
			_cs_it = gee_iterable_iterator ((GeeIterable*) capture_scopes);
			/* find first and longest remaining scope (put it in 's')*/
			while (gee_iterator_next (_cs_it)) {
				GtkMateScope* cs;
				gboolean _tmp17_;
				/* find first and longest remaining scope (put it in 's')*/
				cs = (GtkMateScope*) gee_iterator_get (_cs_it);
				new_length = gtk_mate_scope_end_offset (cs) - gtk_mate_scope_start_offset (cs);
				_tmp17_ = FALSE;
				if (s == NULL) {
					_tmp17_ = TRUE;
				} else {
					gboolean _tmp18_;
					_tmp18_ = FALSE;
					if (gtk_mate_scope_start_offset (cs) < gtk_mate_scope_start_offset (s)) {
						_tmp18_ = new_length >= best_length;
					} else {
						_tmp18_ = FALSE;
					}
					_tmp17_ = _tmp18_;
				}
				if (_tmp17_) {
					GtkMateScope* _tmp20_;
					GtkMateScope* _tmp19_;
					_tmp20_ = NULL;
					_tmp19_ = NULL;
					s = (_tmp20_ = (_tmp19_ = cs, (_tmp19_ == NULL) ? NULL : g_object_ref (_tmp19_)), (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), _tmp20_);
					best_length = new_length;
				}
				(cs == NULL) ? NULL : (cs = (g_object_unref (cs), NULL));
			}
			(_cs_it == NULL) ? NULL : (_cs_it = (g_object_unref (_cs_it), NULL));
		}
		/* look for somewhere to put it from placed_scopes*/
		_tmp21_ = NULL;
		parent_scope = (_tmp21_ = NULL, (parent_scope == NULL) ? NULL : (parent_scope = (g_object_unref (parent_scope), NULL)), _tmp21_);
		{
			GeeIterator* _ps_it;
			_ps_it = gee_iterable_iterator ((GeeIterable*) placed_scopes);
			while (gee_iterator_next (_ps_it)) {
				GtkMateScope* ps;
				gboolean _tmp22_;
				ps = (GtkMateScope*) gee_iterator_get (_ps_it);
				_tmp22_ = FALSE;
				if (gtk_mate_scope_start_offset (s) >= gtk_mate_scope_start_offset (ps)) {
					_tmp22_ = gtk_mate_scope_end_offset (s) <= gtk_mate_scope_end_offset (ps);
				} else {
					_tmp22_ = FALSE;
				}
				if (_tmp22_) {
					GtkMateScope* _tmp24_;
					GtkMateScope* _tmp23_;
					_tmp24_ = NULL;
					_tmp23_ = NULL;
					parent_scope = (_tmp24_ = (_tmp23_ = ps, (_tmp23_ == NULL) ? NULL : g_object_ref (_tmp23_)), (parent_scope == NULL) ? NULL : (parent_scope = (g_object_unref (parent_scope), NULL)), _tmp24_);
				}
				(ps == NULL) ? NULL : (ps = (g_object_unref (ps), NULL));
			}
			(_ps_it == NULL) ? NULL : (_ps_it = (g_object_unref (_ps_it), NULL));
		}
		if (parent_scope != NULL) {
			GtkMateScope* _tmp25_;
			GtkMateScope* _tmp27_;
			GtkMateScope* _tmp26_;
			_tmp25_ = NULL;
			g_sequence_append (gtk_mate_scope_get_children (parent_scope), (_tmp25_ = s, (_tmp25_ == NULL) ? NULL : g_object_ref (_tmp25_)));
			_tmp27_ = NULL;
			_tmp26_ = NULL;
			s->parent = (_tmp27_ = (_tmp26_ = parent_scope, (_tmp26_ == NULL) ? NULL : g_object_ref (_tmp26_)), (s->parent == NULL) ? NULL : (s->parent = (g_object_unref (s->parent), NULL)), _tmp27_);
		} else {
			GtkMateScope* _tmp28_;
			_tmp28_ = NULL;
			g_sequence_append (gtk_mate_scope_get_children (scope), (_tmp28_ = s, (_tmp28_ == NULL) ? NULL : g_object_ref (_tmp28_)));
		}
		gee_collection_add ((GeeCollection*) placed_scopes, s);
		gee_collection_remove ((GeeCollection*) capture_scopes, s);
	}
	(s == NULL) ? NULL : (s = (g_object_unref (s), NULL));
	(captures == NULL) ? NULL : (captures = (g_object_unref (captures), NULL));
	(capture_scopes == NULL) ? NULL : (capture_scopes = (g_object_unref (capture_scopes), NULL));
	(placed_scopes == NULL) ? NULL : (placed_scopes = (g_object_unref (placed_scopes), NULL));
	(parent_scope == NULL) ? NULL : (parent_scope = (g_object_unref (parent_scope), NULL));
}


void gtk_mate_parser_reset_table_priorities (GtkMateParser* self) {
	GSequenceIter* iter;
	gint i;
	g_return_if_fail (self != NULL);
	/* stdout.printf("\nreset_table_priorities() for %d tags\n", buffer.get_tag_table().get_size());*/
	iter = g_sequence_get_begin_iter (self->tags);
	i = 0;
	while (!g_sequence_iter_is_end (g_sequence_iter_next (iter))) {
		GtkTextTag* _tmp0_;
		GtkTextTag* t;
		_tmp0_ = NULL;
		t = (_tmp0_ = (GtkTextTag*) g_sequence_get (iter), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
		gtk_text_tag_set_priority (t, i);
		/* stdout.printf("tag: '%s', pri: %d\n", t.name, i);*/
		i++;
		iter = g_sequence_iter_next (iter);
		(t == NULL) ? NULL : (t = (g_object_unref (t), NULL));
	}
}


void gtk_mate_parser_remove_tags (GtkMateParser* self) {
	GSequenceIter* iter;
	GtkTextTagTable* _tmp0_;
	GtkTextTagTable* table;
	g_return_if_fail (self != NULL);
	iter = g_sequence_get_begin_iter (self->tags);
	_tmp0_ = NULL;
	table = (_tmp0_ = gtk_text_buffer_get_tag_table ((GtkTextBuffer*) self->priv->_buffer), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	while (!g_sequence_iter_is_end (iter)) {
		gtk_text_tag_table_remove (table, (GtkTextTag*) g_sequence_get (iter));
		iter = g_sequence_iter_next (iter);
	}
	g_sequence_remove_range (g_sequence_get_begin_iter (self->tags), g_sequence_get_end_iter (self->tags));
	(table == NULL) ? NULL : (table = (g_object_unref (table), NULL));
}


void gtk_mate_parser_change_theme (GtkMateParser* self, GtkMateTheme* theme) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (theme != NULL);
	/* stdout.printf("parser.change_theme(%s)\n", theme.name);*/
	gtk_mate_colourer_uncolour_scope (self->priv->_colourer, self->root, TRUE);
	gtk_mate_colourer_set_theme (self->priv->_colourer, theme);
	gtk_mate_parser_remove_tags (self);
	gtk_mate_parser_recolour_children (self, self->root);
}


/* stdout.printf("parser.change_theme(%s):out\n", theme.name);*/
void gtk_mate_parser_recolour_children (GtkMateParser* self, GtkMateScope* scope) {
	GSequenceIter* iter;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	iter = g_sequence_get_begin_iter (gtk_mate_scope_get_children (scope));
	while (!g_sequence_iter_is_end (iter)) {
		GtkMateScope* _tmp0_;
		GtkMateScope* child;
		gboolean _tmp1_;
		gboolean _tmp2_;
		_tmp0_ = NULL;
		child = (_tmp0_ = (GtkMateScope*) g_sequence_get (iter), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
		gtk_mate_colourer_colour_scope (self->priv->_colourer, child, FALSE, TRUE);
		_tmp1_ = FALSE;
		_tmp2_ = FALSE;
		if (GTK_MATE_IS_DOUBLE_PATTERN (child->pattern)) {
			_tmp2_ = GTK_MATE_DOUBLE_PATTERN (child->pattern)->content_name != NULL;
		} else {
			_tmp2_ = FALSE;
		}
		if (_tmp2_) {
			_tmp1_ = child->is_capture == FALSE;
		} else {
			_tmp1_ = FALSE;
		}
		if (_tmp1_) {
			gtk_mate_colourer_colour_scope (self->priv->_colourer, child, TRUE, TRUE);
		}
		gtk_mate_parser_recolour_children (self, child);
		iter = g_sequence_iter_next (iter);
		(child == NULL) ? NULL : (child = (g_object_unref (child), NULL));
	}
}


void gtk_mate_parser_last_visible_line_changed (GtkMateParser* self, gint new_last_visible_line) {
	g_return_if_fail (self != NULL);
	self->last_visible_line = new_last_visible_line;
	/* stdout.printf("last_visible_line: %d\n", last_visible_line);
	 stdout.printf("already_parsed_upto: %d\n", parsed_upto);*/
	if ((self->last_visible_line + self->priv->_look_ahead) >= self->parsed_upto) {
		gint end_range;
		end_range = MIN (gtk_text_buffer_get_line_count ((GtkTextBuffer*) self->priv->_buffer) - 1, self->last_visible_line + self->priv->_look_ahead);
		/* stdout.printf("parse_range(%d, %d)\n", parsed_upto, end_range);*/
		gtk_mate_parser_parse_range (self, self->parsed_upto, end_range);
	}
}


gint gtk_mate_parser_last_line_parsed (GtkMateParser* self) {
	g_return_val_if_fail (self != NULL, 0);
	/*GLib.SequenceIter iter = root.children.get_end_iter();
	if (!iter.is_begin()) {
	iter = iter.prev();
	var child = root.children.get(iter);
	return child.end_line();
	}
	else {
	return 0;
	}*/
	return gtk_mate_scope_end_line (self->root);
}


static void _gtk_mate_parser_insert_text_handler_gtk_text_buffer_insert_text (GtkMateBuffer* _sender, const GtkTextIter* pos, const char* text, gint length, gpointer self) {
	gtk_mate_parser_insert_text_handler (self, _sender, pos, text, length);
}


static void _gtk_mate_parser_delete_range_handler_gtk_text_buffer_delete_range (GtkMateBuffer* _sender, const GtkTextIter* start, const GtkTextIter* end, gpointer self) {
	gtk_mate_parser_delete_range_handler (self, _sender, start, end);
}


void gtk_mate_parser_connect_buffer_signals (GtkMateParser* self) {
	g_return_if_fail (self != NULL);
	g_signal_connect_object ((GtkTextBuffer*) self->priv->_buffer, "insert-text", (GCallback) _gtk_mate_parser_insert_text_handler_gtk_text_buffer_insert_text, self, 0);
	g_signal_connect_object ((GtkTextBuffer*) self->priv->_buffer, "delete-range", (GCallback) _gtk_mate_parser_delete_range_handler_gtk_text_buffer_delete_range, self, 0);
	/* buffer.get_tag_table().tag_added += this.tag_added_handler;
	 remove when signal_connect_after works:*/
	g_signal_connect_after (self->priv->_buffer, "insert_text", (GCallback) gtk_mate_parser_static_insert_text_after_handler, NULL);
	g_signal_connect_after (self->priv->_buffer, "delete_range", (GCallback) gtk_mate_parser_static_delete_range_after_handler, NULL);
}


/* Signal.connect_after(buffer.get_tag_table(), "tag_added", 
  (GLib.Callback) Parser.static_tag_added_after_handler, null);*/
void gtk_mate_parser_insert_text_handler (GtkMateParser* self, GtkMateBuffer* bf, const GtkTextIter* pos, const char* text, gint length) {
	char** _tmp1_;
	gint ss_size;
	gint ss_length1;
	char** _tmp0_;
	char** ss;
	gint num_lines;
	g_return_if_fail (self != NULL);
	g_return_if_fail (bf != NULL);
	g_return_if_fail (text != NULL);
	/*//stdout.printf("insert_text(pos, \"%s\", %d)\n", text, length);*/
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	ss = (_tmp1_ = _tmp0_ = g_strsplit (text, "\n", 0), ss_length1 = _vala_array_length (_tmp0_), ss_size = ss_length1, _tmp1_);
	num_lines = -1;
	{
		char** s_collection;
		int s_collection_length1;
		int s_it;
		s_collection = ss;
		s_collection_length1 = ss_length1;
		for (s_it = 0; s_it < ss_length1; s_it = s_it + 1) {
			const char* _tmp2_;
			char* s;
			_tmp2_ = NULL;
			s = (_tmp2_ = s_collection[s_it], (_tmp2_ == NULL) ? NULL : g_strdup (_tmp2_));
			{
				num_lines++;
				s = (g_free (s), NULL);
			}
		}
	}
	/*//stdout.printf("add_change(%d, %d)\n", pos.get_line(), pos.get_line() + num_lines);*/
	range_set_add (self->changes, gtk_text_iter_get_line (&(*pos)), gtk_text_iter_get_line (&(*pos)) + num_lines);
	ss = (_vala_array_free (ss, ss_length1, (GDestroyNotify) g_free), NULL);
}


void gtk_mate_parser_delete_range_handler (GtkMateParser* self, GtkMateBuffer* bf, const GtkTextIter* pos, const GtkTextIter* pos2) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (bf != NULL);
	/*//stdout.printf("delete_range(%d, %d)\n", pos.get_offset(), pos2.get_offset());*/
	range_set_add (self->changes, gtk_text_iter_get_line (&(*pos)), gtk_text_iter_get_line (&(*pos)));
}


void gtk_mate_parser_insert_text_after_handler (GtkMateParser* self, GtkMateBuffer* bf, const GtkTextIter* pos, const char* text, gint length) {
	gboolean _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (bf != NULL);
	g_return_if_fail (text != NULL);
	_tmp0_ = FALSE;
	if (gtk_mate_parser_is_parsing (self)) {
		_tmp0_ = !range_set_is_empty (self->changes);
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		gtk_mate_parser_process_changes (self);
	}
}


void gtk_mate_parser_delete_range_after_handler (GtkMateParser* self, GtkMateBuffer* bf, const GtkTextIter* pos, const GtkTextIter* pos2) {
	gboolean _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (bf != NULL);
	_tmp0_ = FALSE;
	if (gtk_mate_parser_is_parsing (self)) {
		_tmp0_ = !range_set_is_empty (self->changes);
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		gtk_mate_parser_process_changes (self);
	}
}


void gtk_mate_parser_static_insert_text_after_handler (GtkMateBuffer* bf, const GtkTextIter* pos, const char* text, gint length) {
	g_return_if_fail (bf != NULL);
	g_return_if_fail (text != NULL);
	{
		GeeIterator* _parser_it;
		_parser_it = gee_iterable_iterator ((GeeIterable*) gtk_mate_parser_existing_parsers);
		while (gee_iterator_next (_parser_it)) {
			GtkMateParser* parser;
			parser = (GtkMateParser*) gee_iterator_get (_parser_it);
			gtk_mate_parser_insert_text_after_handler (parser, bf, &(*pos), text, length);
			(parser == NULL) ? NULL : (parser = (g_object_unref (parser), NULL));
		}
		(_parser_it == NULL) ? NULL : (_parser_it = (g_object_unref (_parser_it), NULL));
	}
}


void gtk_mate_parser_static_delete_range_after_handler (GtkMateBuffer* bf, const GtkTextIter* pos, const GtkTextIter* pos2) {
	g_return_if_fail (bf != NULL);
	{
		GeeIterator* _parser_it;
		_parser_it = gee_iterable_iterator ((GeeIterable*) gtk_mate_parser_existing_parsers);
		while (gee_iterator_next (_parser_it)) {
			GtkMateParser* parser;
			parser = (GtkMateParser*) gee_iterator_get (_parser_it);
			gtk_mate_parser_delete_range_after_handler (parser, bf, &(*pos), &(*pos2));
			(parser == NULL) ? NULL : (parser = (g_object_unref (parser), NULL));
		}
		(_parser_it == NULL) ? NULL : (_parser_it = (g_object_unref (_parser_it), NULL));
	}
}


void gtk_mate_parser_added_tag (GtkMateParser* self, GtkTextTag* tag) {
	gboolean _tmp0_;
	char* _tmp2_;
	char* _tmp1_;
	gboolean _tmp3_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (tag != NULL);
	_tmp0_ = FALSE;
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	if ((_tmp3_ = (_tmp2_ = (g_object_get (tag, "name", &_tmp1_, NULL), _tmp1_)) != NULL, _tmp2_ = (g_free (_tmp2_), NULL), _tmp3_)) {
		char* _tmp5_;
		char* _tmp4_;
		_tmp5_ = NULL;
		_tmp4_ = NULL;
		_tmp0_ = g_str_has_prefix (_tmp5_ = (g_object_get (tag, "name", &_tmp4_, NULL), _tmp4_), "gmv(");
		_tmp5_ = (g_free (_tmp5_), NULL);
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		GtkTextTag* _tmp6_;
		_tmp6_ = NULL;
		g_sequence_insert_sorted (self->tags, (_tmp6_ = tag, (_tmp6_ == NULL) ? NULL : g_object_ref (_tmp6_)), (GCompareDataFunc) gtk_mate_parser_tag_compare, NULL);
	}
	gtk_mate_parser_reset_table_priorities (self);
}


gint gtk_mate_parser_tag_compare (GtkTextTag* tag1, GtkTextTag* tag2, void* data) {
	char* _tmp1_;
	char* _tmp0_;
	gint _tmp2_;
	gint pri1;
	char* _tmp4_;
	char* _tmp3_;
	gint _tmp5_;
	gint pri2;
	g_return_val_if_fail (tag1 != NULL, 0);
	g_return_val_if_fail (tag2 != NULL, 0);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	pri1 = (_tmp2_ = g_unichar_digit_value (g_utf8_get_char (g_utf8_offset_to_pointer (_tmp1_ = (g_object_get (tag1, "name", &_tmp0_, NULL), _tmp0_), 4))), _tmp1_ = (g_free (_tmp1_), NULL), _tmp2_);
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	pri2 = (_tmp5_ = g_unichar_digit_value (g_utf8_get_char (g_utf8_offset_to_pointer (_tmp4_ = (g_object_get (tag2, "name", &_tmp3_, NULL), _tmp3_), 4))), _tmp4_ = (g_free (_tmp4_), NULL), _tmp5_);
	if (pri1 > pri2) {
		return 1;
	} else {
		if (pri2 > pri1) {
			return -1;
		}
	}
	return 0;
}


void gtk_mate_parser_close (GtkMateParser* self) {
	g_return_if_fail (self != NULL);
	gee_collection_remove ((GeeCollection*) gtk_mate_parser_existing_parsers, self);
}


GtkMateParser* gtk_mate_parser_create (GtkMateGrammar* grammar, GtkMateBuffer* buffer) {
	GtkMateParser* p;
	GSequence* _tmp1_;
	RangeSet* _tmp2_;
	GtkMateColourer* _tmp3_;
	g_return_val_if_fail (grammar != NULL, NULL);
	g_return_val_if_fail (buffer != NULL, NULL);
	gtk_mate_grammar_init_for_use (grammar);
	p = g_object_ref_sink (gtk_mate_parser_new ());
	/* remove when signal_connect_after works:*/
	if (gtk_mate_parser_existing_parsers == NULL) {
		GeeArrayList* _tmp0_;
		_tmp0_ = NULL;
		gtk_mate_parser_existing_parsers = (_tmp0_ = gee_array_list_new (GTK_MATE_TYPE_PARSER, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (gtk_mate_parser_existing_parsers == NULL) ? NULL : (gtk_mate_parser_existing_parsers = (g_object_unref (gtk_mate_parser_existing_parsers), NULL)), _tmp0_);
	}
	gee_collection_add ((GeeCollection*) gtk_mate_parser_existing_parsers, p);
	gtk_mate_parser_set_look_ahead (p, 100);
	p->last_visible_line = 0;
	gtk_mate_parser_set_grammar (p, grammar);
	gtk_mate_parser_set_buffer (p, buffer);
	_tmp1_ = NULL;
	p->tags = (_tmp1_ = g_sequence_new (NULL), (p->tags == NULL) ? NULL : (p->tags = (g_sequence_free (p->tags), NULL)), _tmp1_);
	_tmp2_ = NULL;
	p->changes = (_tmp2_ = range_set_new (), (p->changes == NULL) ? NULL : (p->changes = (g_object_unref (p->changes), NULL)), _tmp2_);
	_tmp3_ = NULL;
	gtk_mate_parser_set_colourer (p, _tmp3_ = g_object_ref_sink (gtk_mate_colourer_new (buffer)));
	(_tmp3_ == NULL) ? NULL : (_tmp3_ = (g_object_unref (_tmp3_), NULL));
	p->deactivation_level = 0;
	gtk_mate_parser_make_root (p);
	gtk_mate_parser_connect_buffer_signals (p);
	p->parsed_upto = 0;
	p->always_parse_all = FALSE;
	return p;
}


GtkMateParser* gtk_mate_parser_construct (GType object_type) {
	GtkMateParser * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


GtkMateParser* gtk_mate_parser_new (void) {
	return gtk_mate_parser_construct (GTK_MATE_TYPE_PARSER);
}


GtkMateGrammar* gtk_mate_parser_get_grammar (GtkMateParser* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_grammar;
}


void gtk_mate_parser_set_grammar (GtkMateParser* self, GtkMateGrammar* value) {
	GtkMateGrammar* _tmp2_;
	GtkMateGrammar* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_grammar = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->priv->_grammar == NULL) ? NULL : (self->priv->_grammar = (g_object_unref (self->priv->_grammar), NULL)), _tmp2_);
	g_object_notify ((GObject *) self, "grammar");
}


GtkMateColourer* gtk_mate_parser_get_colourer (GtkMateParser* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_colourer;
}


void gtk_mate_parser_set_colourer (GtkMateParser* self, GtkMateColourer* value) {
	GtkMateColourer* _tmp2_;
	GtkMateColourer* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_colourer = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->priv->_colourer == NULL) ? NULL : (self->priv->_colourer = (g_object_unref (self->priv->_colourer), NULL)), _tmp2_);
	g_object_notify ((GObject *) self, "colourer");
}


GtkMateBuffer* gtk_mate_parser_get_buffer (GtkMateParser* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_buffer;
}


void gtk_mate_parser_set_buffer (GtkMateParser* self, GtkMateBuffer* value) {
	GtkMateBuffer* _tmp2_;
	GtkMateBuffer* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_buffer = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->priv->_buffer == NULL) ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL)), _tmp2_);
	g_object_notify ((GObject *) self, "buffer");
}


gint gtk_mate_parser_get_look_ahead (GtkMateParser* self) {
	g_return_val_if_fail (self != NULL, 0);
	return self->priv->_look_ahead;
}


void gtk_mate_parser_set_look_ahead (GtkMateParser* self, gint value) {
	g_return_if_fail (self != NULL);
	self->priv->_look_ahead = value;
	g_object_notify ((GObject *) self, "look-ahead");
}


static void gtk_mate_parser_class_init (GtkMateParserClass * klass) {
	gtk_mate_parser_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GtkMateParserPrivate));
	G_OBJECT_CLASS (klass)->get_property = gtk_mate_parser_get_property;
	G_OBJECT_CLASS (klass)->set_property = gtk_mate_parser_set_property;
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_parser_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_PARSER_GRAMMAR, g_param_spec_object ("grammar", "grammar", "grammar", GTK_MATE_TYPE_GRAMMAR, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_PARSER_COLOURER, g_param_spec_object ("colourer", "colourer", "colourer", GTK_MATE_TYPE_COLOURER, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_PARSER_BUFFER, g_param_spec_object ("buffer", "buffer", "buffer", GTK_MATE_TYPE_BUFFER, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_PARSER_LOOK_AHEAD, g_param_spec_int ("look-ahead", "look-ahead", "look-ahead", G_MININT, G_MAXINT, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void gtk_mate_parser_instance_init (GtkMateParser * self) {
	self->priv = GTK_MATE_PARSER_GET_PRIVATE (self);
}


static void gtk_mate_parser_finalize (GObject* obj) {
	GtkMateParser * self;
	self = GTK_MATE_PARSER (obj);
	(self->priv->_grammar == NULL) ? NULL : (self->priv->_grammar = (g_object_unref (self->priv->_grammar), NULL));
	(self->priv->_colourer == NULL) ? NULL : (self->priv->_colourer = (g_object_unref (self->priv->_colourer), NULL));
	(self->priv->_buffer == NULL) ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL));
	(self->root == NULL) ? NULL : (self->root = (g_object_unref (self->root), NULL));
	(self->dummy_tag == NULL) ? NULL : (self->dummy_tag = (g_object_unref (self->dummy_tag), NULL));
	(self->dummy_tag2 == NULL) ? NULL : (self->dummy_tag2 = (g_object_unref (self->dummy_tag2), NULL));
	(self->tags == NULL) ? NULL : (self->tags = (g_sequence_free (self->tags), NULL));
	(self->changes == NULL) ? NULL : (self->changes = (g_object_unref (self->changes), NULL));
	G_OBJECT_CLASS (gtk_mate_parser_parent_class)->finalize (obj);
}


GType gtk_mate_parser_get_type (void) {
	static GType gtk_mate_parser_type_id = 0;
	if (gtk_mate_parser_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateParserClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_parser_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateParser), 0, (GInstanceInitFunc) gtk_mate_parser_instance_init, NULL };
		gtk_mate_parser_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateParser", &g_define_type_info, 0);
	}
	return gtk_mate_parser_type_id;
}


static void gtk_mate_parser_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateParser * self;
	gpointer boxed;
	self = GTK_MATE_PARSER (object);
	switch (property_id) {
		case GTK_MATE_PARSER_GRAMMAR:
		g_value_set_object (value, gtk_mate_parser_get_grammar (self));
		break;
		case GTK_MATE_PARSER_COLOURER:
		g_value_set_object (value, gtk_mate_parser_get_colourer (self));
		break;
		case GTK_MATE_PARSER_BUFFER:
		g_value_set_object (value, gtk_mate_parser_get_buffer (self));
		break;
		case GTK_MATE_PARSER_LOOK_AHEAD:
		g_value_set_int (value, gtk_mate_parser_get_look_ahead (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_parser_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GtkMateParser * self;
	self = GTK_MATE_PARSER (object);
	switch (property_id) {
		case GTK_MATE_PARSER_GRAMMAR:
		gtk_mate_parser_set_grammar (self, g_value_get_object (value));
		break;
		case GTK_MATE_PARSER_COLOURER:
		gtk_mate_parser_set_colourer (self, g_value_get_object (value));
		break;
		case GTK_MATE_PARSER_BUFFER:
		gtk_mate_parser_set_buffer (self, g_value_get_object (value));
		break;
		case GTK_MATE_PARSER_LOOK_AHEAD:
		gtk_mate_parser_set_look_ahead (self, g_value_get_int (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
}


static gint _vala_array_length (gpointer array) {
	int length;
	length = 0;
	if (array) {
		while (((gpointer*) array)[length]) {
			length++;
		}
	}
	return length;
}


static int _vala_strcmp0 (const char * str1, const char * str2) {
	if (str1 == NULL) {
		return -(str1 != str2);
	}
	if (str2 == NULL) {
		return str1 != str2;
	}
	return strcmp (str1, str2);
}




