
#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <gtksourceview/gtksourceview.h>
#include <stdlib.h>
#include <string.h>
#include <gee/hashmap.h>
#include <gee/arraylist.h>
#include <gee/map.h>
#include <gee/iterable.h>
#include <gee/iterator.h>


#define GTK_MATE_TYPE_EXPORTER (gtk_mate_exporter_get_type ())
#define GTK_MATE_EXPORTER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_EXPORTER, GtkMateExporter))
#define GTK_MATE_EXPORTER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_EXPORTER, GtkMateExporterClass))
#define GTK_MATE_IS_EXPORTER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_EXPORTER))
#define GTK_MATE_IS_EXPORTER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_EXPORTER))
#define GTK_MATE_EXPORTER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_EXPORTER, GtkMateExporterClass))

typedef struct _GtkMateExporter GtkMateExporter;
typedef struct _GtkMateExporterClass GtkMateExporterClass;
typedef struct _GtkMateExporterPrivate GtkMateExporterPrivate;

#define GTK_MATE_TYPE_VIEW (gtk_mate_view_get_type ())
#define GTK_MATE_VIEW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_VIEW, GtkMateView))
#define GTK_MATE_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_VIEW, GtkMateViewClass))
#define GTK_MATE_IS_VIEW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_VIEW))
#define GTK_MATE_IS_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_VIEW))
#define GTK_MATE_VIEW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_VIEW, GtkMateViewClass))

typedef struct _GtkMateView GtkMateView;
typedef struct _GtkMateViewClass GtkMateViewClass;

#define GTK_MATE_TYPE_SCOPE (gtk_mate_scope_get_type ())
#define GTK_MATE_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SCOPE, GtkMateScope))
#define GTK_MATE_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SCOPE, GtkMateScopeClass))
#define GTK_MATE_IS_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SCOPE))
#define GTK_MATE_IS_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SCOPE))
#define GTK_MATE_SCOPE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SCOPE, GtkMateScopeClass))

typedef struct _GtkMateScope GtkMateScope;
typedef struct _GtkMateScopeClass GtkMateScopeClass;

#define GTK_MATE_TYPE_BUFFER (gtk_mate_buffer_get_type ())
#define GTK_MATE_BUFFER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_BUFFER, GtkMateBuffer))
#define GTK_MATE_BUFFER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_BUFFER, GtkMateBufferClass))
#define GTK_MATE_IS_BUFFER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_BUFFER))
#define GTK_MATE_IS_BUFFER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_BUFFER))
#define GTK_MATE_BUFFER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_BUFFER, GtkMateBufferClass))

typedef struct _GtkMateBuffer GtkMateBuffer;
typedef struct _GtkMateBufferClass GtkMateBufferClass;
typedef struct _GtkMateBufferPrivate GtkMateBufferPrivate;

#define GTK_MATE_TYPE_PARSER (gtk_mate_parser_get_type ())
#define GTK_MATE_PARSER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_PARSER, GtkMateParser))
#define GTK_MATE_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_PARSER, GtkMateParserClass))
#define GTK_MATE_IS_PARSER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_PARSER))
#define GTK_MATE_IS_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_PARSER))
#define GTK_MATE_PARSER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_PARSER, GtkMateParserClass))

typedef struct _GtkMateParser GtkMateParser;
typedef struct _GtkMateParserClass GtkMateParserClass;
typedef struct _GtkMateParserPrivate GtkMateParserPrivate;

#define TYPE_RANGE_SET (range_set_get_type ())
#define RANGE_SET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_RANGE_SET, RangeSet))
#define RANGE_SET_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_RANGE_SET, RangeSetClass))
#define IS_RANGE_SET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_RANGE_SET))
#define IS_RANGE_SET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_RANGE_SET))
#define RANGE_SET_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_RANGE_SET, RangeSetClass))

typedef struct _RangeSet RangeSet;
typedef struct _RangeSetClass RangeSetClass;
typedef struct _GtkMateScopePrivate GtkMateScopePrivate;

#define GTK_MATE_TYPE_PATTERN (gtk_mate_pattern_get_type ())
#define GTK_MATE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_PATTERN, GtkMatePattern))
#define GTK_MATE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_PATTERN, GtkMatePatternClass))
#define GTK_MATE_IS_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_PATTERN))
#define GTK_MATE_IS_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_PATTERN))
#define GTK_MATE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_PATTERN, GtkMatePatternClass))

typedef struct _GtkMatePattern GtkMatePattern;
typedef struct _GtkMatePatternClass GtkMatePatternClass;

#define ONIG_TYPE_MATCH (onig_match_get_type ())
#define ONIG_MATCH(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIG_TYPE_MATCH, OnigMatch))
#define ONIG_MATCH_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIG_TYPE_MATCH, OnigMatchClass))
#define ONIG_IS_MATCH(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIG_TYPE_MATCH))
#define ONIG_IS_MATCH_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIG_TYPE_MATCH))
#define ONIG_MATCH_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIG_TYPE_MATCH, OnigMatchClass))

typedef struct _OnigMatch OnigMatch;
typedef struct _OnigMatchClass OnigMatchClass;

#define ONIG_TYPE_RX (onig_rx_get_type ())
#define ONIG_RX(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIG_TYPE_RX, OnigRx))
#define ONIG_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIG_TYPE_RX, OnigRxClass))
#define ONIG_IS_RX(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIG_TYPE_RX))
#define ONIG_IS_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIG_TYPE_RX))
#define ONIG_RX_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIG_TYPE_RX, OnigRxClass))

typedef struct _OnigRx OnigRx;
typedef struct _OnigRxClass OnigRxClass;

#define GTK_MATE_TYPE_TEXT_LOC (gtk_mate_text_loc_get_type ())
#define GTK_MATE_TEXT_LOC(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_TEXT_LOC, GtkMateTextLoc))
#define GTK_MATE_TEXT_LOC_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_TEXT_LOC, GtkMateTextLocClass))
#define GTK_MATE_IS_TEXT_LOC(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_TEXT_LOC))
#define GTK_MATE_IS_TEXT_LOC_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_TEXT_LOC))
#define GTK_MATE_TEXT_LOC_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_TEXT_LOC, GtkMateTextLocClass))

typedef struct _GtkMateTextLoc GtkMateTextLoc;
typedef struct _GtkMateTextLocClass GtkMateTextLocClass;

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

#define GTK_MATE_TYPE_COLOURER (gtk_mate_colourer_get_type ())
#define GTK_MATE_COLOURER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_COLOURER, GtkMateColourer))
#define GTK_MATE_COLOURER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_COLOURER, GtkMateColourerClass))
#define GTK_MATE_IS_COLOURER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_COLOURER))
#define GTK_MATE_IS_COLOURER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_COLOURER))
#define GTK_MATE_COLOURER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_COLOURER, GtkMateColourerClass))

typedef struct _GtkMateColourer GtkMateColourer;
typedef struct _GtkMateColourerClass GtkMateColourerClass;

#define GTK_MATE_TYPE_THEME (gtk_mate_theme_get_type ())
#define GTK_MATE_THEME(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_THEME, GtkMateTheme))
#define GTK_MATE_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_THEME, GtkMateThemeClass))
#define GTK_MATE_IS_THEME(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_THEME))
#define GTK_MATE_IS_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_THEME))
#define GTK_MATE_THEME_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_THEME, GtkMateThemeClass))

typedef struct _GtkMateTheme GtkMateTheme;
typedef struct _GtkMateThemeClass GtkMateThemeClass;
typedef struct _GtkMateThemePrivate GtkMateThemePrivate;
typedef struct _GtkMateThemeSettingPrivate GtkMateThemeSettingPrivate;

#define GTK_MATE_TYPE_MATCHER (gtk_mate_matcher_get_type ())
#define GTK_MATE_MATCHER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_MATCHER, GtkMateMatcher))
#define GTK_MATE_MATCHER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_MATCHER, GtkMateMatcherClass))
#define GTK_MATE_IS_MATCHER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_MATCHER))
#define GTK_MATE_IS_MATCHER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_MATCHER))
#define GTK_MATE_MATCHER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_MATCHER, GtkMateMatcherClass))

typedef struct _GtkMateMatcher GtkMateMatcher;
typedef struct _GtkMateMatcherClass GtkMateMatcherClass;

struct _GtkMateExporter {
	GtkObject parent_instance;
	GtkMateExporterPrivate * priv;
	GtkMateView* view;
};

struct _GtkMateExporterClass {
	GtkObjectClass parent_class;
};

struct _GtkMateBuffer {
	GtkSourceBuffer parent_instance;
	GtkMateBufferPrivate * priv;
	GtkMateParser* parser;
};

struct _GtkMateBufferClass {
	GtkSourceBufferClass parent_class;
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

struct _GtkMateTheme {
	GtkObject parent_instance;
	GtkMateThemePrivate * priv;
	char* author;
	char* name;
	GeeHashMap* global_settings;
	GeeArrayList* settings;
	gboolean is_initialized;
	GeeHashMap* cached_setting_for_scopes;
};

struct _GtkMateThemeClass {
	GtkObjectClass parent_class;
};

struct _GtkMateThemeSetting {
	GtkObject parent_instance;
	GtkMateThemeSettingPrivate * priv;
	char* name;
	char* selector;
	GeeHashMap* settings;
	GeeArrayList* matchers;
};

struct _GtkMateThemeSettingClass {
	GtkObjectClass parent_class;
};



GType gtk_mate_exporter_get_type (void);
GType gtk_mate_view_get_type (void);
enum  {
	GTK_MATE_EXPORTER_DUMMY_PROPERTY
};
GtkMateExporter* gtk_mate_exporter_new (GtkMateView* v);
GtkMateExporter* gtk_mate_exporter_construct (GType object_type, GtkMateView* v);
GtkMateExporter* gtk_mate_exporter_new (GtkMateView* v);
static char* gtk_mate_exporter_html_header (GtkMateExporter* self, const char* title);
static char* gtk_mate_exporter_css (GtkMateExporter* self);
static char* gtk_mate_exporter_body_start (GtkMateExporter* self);
static char* gtk_mate_exporter_code (GtkMateExporter* self);
static char* gtk_mate_exporter_body_end (GtkMateExporter* self);
char* gtk_mate_exporter_to_html (GtkMateExporter* self, const char* title);
static void gtk_mate_exporter_add_indent (GtkMateExporter* self, GString* sb, gint indent);
static char* gtk_mate_exporter_theme_name_css (GtkMateExporter* self);
GType gtk_mate_scope_get_type (void);
static void gtk_mate_exporter_scope_to_html (GtkMateExporter* self, GString* _result_, GtkMateScope* scope);
GType gtk_mate_buffer_get_type (void);
static GtkMateBuffer* gtk_mate_exporter_buffer (GtkMateExporter* self);
GType gtk_mate_parser_get_type (void);
GType range_set_get_type (void);
GType gtk_mate_pattern_get_type (void);
GType onig_match_get_type (void);
GType onig_rx_get_type (void);
GType gtk_mate_text_loc_get_type (void);
GType gtk_mate_theme_setting_get_type (void);
GType gtk_mate_double_pattern_get_type (void);
const char* gtk_mate_scope_get_name (GtkMateScope* self);
static char* gtk_mate_exporter_css_names (GtkMateExporter* self, GtkMateScope* scope, gboolean inner);
static gboolean gtk_mate_exporter_scope_has_inner (GtkMateExporter* self, GtkMateScope* scope);
GtkTextIter gtk_mate_scope_start_iter (GtkMateScope* self);
GSequence* gtk_mate_scope_get_children (GtkMateScope* self);
GtkTextIter gtk_mate_scope_inner_start_iter (GtkMateScope* self);
GtkTextIter gtk_mate_scope_inner_end_iter (GtkMateScope* self);
GtkTextIter gtk_mate_scope_end_iter (GtkMateScope* self);
GType gtk_mate_colourer_get_type (void);
GtkMateColourer* gtk_mate_parser_get_colourer (GtkMateParser* self);
GType gtk_mate_theme_get_type (void);
GtkMateTheme* gtk_mate_colourer_get_theme (GtkMateColourer* self);
static char* gtk_mate_exporter_theme_name (GtkMateExporter* self);
char* string_helper_gsub (const char* start_string, const char* match_string, const char* replacement_string);
gint gtk_mate_colourer_hex_to_int (gunichar ch1, gunichar ch2);
static char* gtk_mate_exporter_colour (GtkMateExporter* self, const char* colour);
char* gtk_mate_colourer_global_foreground_colour (GtkMateColourer* self);
char* gtk_mate_colourer_global_background_colour (GtkMateColourer* self);
GType gtk_mate_matcher_get_type (void);
static char* gtk_mate_exporter_html (GtkMateExporter* self);
static gpointer gtk_mate_exporter_parent_class = NULL;
static void gtk_mate_exporter_finalize (GObject* obj);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static gint _vala_array_length (gpointer array);
static int _vala_strcmp0 (const char * str1, const char * str2);



GtkMateExporter* gtk_mate_exporter_construct (GType object_type, GtkMateView* v) {
	GtkMateExporter * self;
	GtkMateView* _tmp1_;
	GtkMateView* _tmp0_;
	g_return_val_if_fail (v != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->view = (_tmp1_ = (_tmp0_ = v, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->view == NULL) ? NULL : (self->view = (g_object_unref (self->view), NULL)), _tmp1_);
	return self;
}


GtkMateExporter* gtk_mate_exporter_new (GtkMateView* v) {
	return gtk_mate_exporter_construct (GTK_MATE_TYPE_EXPORTER, v);
}


char* gtk_mate_exporter_to_html (GtkMateExporter* self, const char* title) {
	GString* _result_;
	char* _tmp0_;
	char* _tmp1_;
	char* _tmp2_;
	char* _tmp3_;
	char* _tmp4_;
	const char* _tmp5_;
	char* _tmp6_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (title != NULL, NULL);
	_result_ = g_string_new ("");
	_tmp0_ = NULL;
	g_string_append (_result_, _tmp0_ = gtk_mate_exporter_html_header (self, title));
	_tmp0_ = (g_free (_tmp0_), NULL);
	_tmp1_ = NULL;
	g_string_append (_result_, _tmp1_ = gtk_mate_exporter_css (self));
	_tmp1_ = (g_free (_tmp1_), NULL);
	_tmp2_ = NULL;
	g_string_append (_result_, _tmp2_ = gtk_mate_exporter_body_start (self));
	_tmp2_ = (g_free (_tmp2_), NULL);
	_tmp3_ = NULL;
	g_string_append (_result_, _tmp3_ = gtk_mate_exporter_code (self));
	_tmp3_ = (g_free (_tmp3_), NULL);
	_tmp4_ = NULL;
	g_string_append (_result_, _tmp4_ = gtk_mate_exporter_body_end (self));
	_tmp4_ = (g_free (_tmp4_), NULL);
	_tmp5_ = NULL;
	_tmp6_ = NULL;
	return (_tmp6_ = (_tmp5_ = _result_->str, (_tmp5_ == NULL) ? NULL : g_strdup (_tmp5_)), (_result_ == NULL) ? NULL : (_result_ = (g_string_free (_result_, TRUE), NULL)), _tmp6_);
}


static void gtk_mate_exporter_add_indent (GtkMateExporter* self, GString* sb, gint indent) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (sb != NULL);
	{
		gint i;
		i = 0;
		for (; i < indent; i++) {
			g_string_append (sb, "\t");
		}
	}
}


static char* gtk_mate_exporter_code (GtkMateExporter* self) {
	GString* _result_;
	char* _tmp2_;
	char* _tmp1_;
	char* _tmp0_;
	GtkMateBuffer* _tmp3_;
	const char* _tmp4_;
	char* _tmp5_;
	g_return_val_if_fail (self != NULL, NULL);
	_result_ = g_string_new ("");
	gtk_mate_exporter_add_indent (self, _result_, 1);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	g_string_append (_result_, _tmp2_ = g_strconcat (_tmp1_ = g_strconcat ("<pre class=\"textmate-source ", _tmp0_ = gtk_mate_exporter_theme_name_css (self), NULL), "\">", NULL));
	_tmp2_ = (g_free (_tmp2_), NULL);
	_tmp1_ = (g_free (_tmp1_), NULL);
	_tmp0_ = (g_free (_tmp0_), NULL);
	_tmp3_ = NULL;
	gtk_mate_exporter_scope_to_html (self, _result_, (_tmp3_ = gtk_mate_exporter_buffer (self))->parser->root);
	(_tmp3_ == NULL) ? NULL : (_tmp3_ = (g_object_unref (_tmp3_), NULL));
	g_string_append (_result_, "</pre>\n");
	_tmp4_ = NULL;
	_tmp5_ = NULL;
	return (_tmp5_ = (_tmp4_ = _result_->str, (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_)), (_result_ == NULL) ? NULL : (_result_ = (g_string_free (_result_, TRUE), NULL)), _tmp5_);
}


static char* gtk_mate_exporter_css_names (GtkMateExporter* self, GtkMateScope* scope, gboolean inner) {
	char* this_name;
	gboolean _tmp0_;
	gboolean _tmp1_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (scope != NULL, NULL);
	this_name = NULL;
	_tmp0_ = FALSE;
	_tmp1_ = FALSE;
	if (GTK_MATE_IS_DOUBLE_PATTERN (scope->pattern)) {
		_tmp1_ = GTK_MATE_DOUBLE_PATTERN (scope->pattern)->content_name != NULL;
	} else {
		_tmp1_ = FALSE;
	}
	if (_tmp1_) {
		_tmp0_ = inner;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		char* _tmp3_;
		const char* _tmp2_;
		_tmp3_ = NULL;
		_tmp2_ = NULL;
		this_name = (_tmp3_ = (_tmp2_ = GTK_MATE_DOUBLE_PATTERN (scope->pattern)->content_name, (_tmp2_ == NULL) ? NULL : g_strdup (_tmp2_)), this_name = (g_free (this_name), NULL), _tmp3_);
	} else {
		char* _tmp5_;
		const char* _tmp4_;
		_tmp5_ = NULL;
		_tmp4_ = NULL;
		this_name = (_tmp5_ = (_tmp4_ = gtk_mate_scope_get_name (scope), (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_)), this_name = (g_free (this_name), NULL), _tmp5_);
	}
	if (this_name != NULL) {
		char** _tmp7_;
		gint bits_size;
		gint bits_length1;
		char** _tmp6_;
		char** bits;
		const char* _tmp8_;
		char* current;
		GString* _result_;
		char* _tmp12_;
		const char* _tmp11_;
		_tmp7_ = NULL;
		_tmp6_ = NULL;
		bits = (_tmp7_ = _tmp6_ = g_strsplit (this_name, ".", 0), bits_length1 = _vala_array_length (_tmp6_), bits_size = bits_length1, _tmp7_);
		/* bits == ["meta", "class", "ruby"]*/
		_tmp8_ = NULL;
		current = (_tmp8_ = bits[0], (_tmp8_ == NULL) ? NULL : g_strdup (_tmp8_));
		_result_ = g_string_new ("");
		{
			gint i;
			i = 1;
			for (; i < bits_length1; i++) {
				char* _tmp10_;
				char* _tmp9_;
				g_string_append (_result_, current);
				_tmp10_ = NULL;
				_tmp9_ = NULL;
				current = (_tmp10_ = g_strconcat (_tmp9_ = g_strconcat (current, "_", NULL), bits[i], NULL), current = (g_free (current), NULL), _tmp10_);
				_tmp9_ = (g_free (_tmp9_), NULL);
				g_string_append (_result_, " ");
			}
		}
		g_string_append (_result_, current);
		_tmp12_ = NULL;
		_tmp11_ = NULL;
		this_name = (_tmp12_ = (_tmp11_ = _result_->str, (_tmp11_ == NULL) ? NULL : g_strdup (_tmp11_)), this_name = (g_free (this_name), NULL), _tmp12_);
		bits = (_vala_array_free (bits, bits_length1, (GDestroyNotify) g_free), NULL);
		current = (g_free (current), NULL);
		(_result_ == NULL) ? NULL : (_result_ = (g_string_free (_result_, TRUE), NULL));
	}
	return this_name;
}


static gboolean gtk_mate_exporter_scope_has_inner (GtkMateExporter* self, GtkMateScope* scope) {
	gboolean _tmp0_;
	gboolean _tmp1_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (scope != NULL, FALSE);
	_tmp0_ = FALSE;
	_tmp1_ = FALSE;
	if (GTK_MATE_IS_DOUBLE_PATTERN (scope->pattern)) {
		_tmp1_ = GTK_MATE_DOUBLE_PATTERN (scope->pattern)->content_name != NULL;
	} else {
		_tmp1_ = FALSE;
	}
	if (_tmp1_) {
		_tmp0_ = _vala_strcmp0 (GTK_MATE_DOUBLE_PATTERN (scope->pattern)->content_name, "") != 0;
	} else {
		_tmp0_ = FALSE;
	}
	return _tmp0_;
}


static void gtk_mate_exporter_scope_to_html (GtkMateExporter* self, GString* _result_, GtkMateScope* scope) {
	char* names;
	gboolean _tmp0_;
	GtkTextIter position;
	gboolean opened_inner;
	gboolean closed_inner;
	gboolean _tmp26_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (_result_ != NULL);
	g_return_if_fail (scope != NULL);
	names = gtk_mate_exporter_css_names (self, scope, FALSE);
	_tmp0_ = FALSE;
	if (_vala_strcmp0 (names, "") != 0) {
		_tmp0_ = names != NULL;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		char* _tmp2_;
		char* _tmp1_;
		_tmp2_ = NULL;
		_tmp1_ = NULL;
		g_string_append (_result_, _tmp2_ = g_strconcat (_tmp1_ = g_strconcat ("<span class=\"", names, NULL), "\">", NULL));
		_tmp2_ = (g_free (_tmp2_), NULL);
		_tmp1_ = (g_free (_tmp1_), NULL);
	}
	position = gtk_mate_scope_start_iter (scope);
	opened_inner = FALSE;
	closed_inner = FALSE;
	if (g_sequence_get_length (gtk_mate_scope_get_children (scope)) > 0) {
		GSequenceIter* iter;
		GtkMateScope* child;
		gboolean _tmp15_;
		iter = g_sequence_get_begin_iter (gtk_mate_scope_get_children (scope));
		child = NULL;
		while (!g_sequence_iter_is_end (iter)) {
			GtkMateScope* _tmp8_;
			GtkMateScope* _tmp7_;
			GtkTextIter _tmp9_ = {0};
			if (gtk_mate_exporter_scope_has_inner (self, scope)) {
				gboolean _tmp3_;
				GtkTextIter _tmp4_ = {0};
				_tmp3_ = FALSE;
				if (gtk_text_iter_compare (&position, (_tmp4_ = gtk_mate_scope_inner_start_iter (scope), &_tmp4_)) >= 0) {
					_tmp3_ = !opened_inner;
				} else {
					_tmp3_ = FALSE;
				}
				if (_tmp3_) {
					char* inner_names;
					char* _tmp6_;
					char* _tmp5_;
					inner_names = gtk_mate_exporter_css_names (self, scope, TRUE);
					_tmp6_ = NULL;
					_tmp5_ = NULL;
					g_string_append (_result_, _tmp6_ = g_strconcat (_tmp5_ = g_strconcat ("<span class=\"", inner_names, NULL), "\">", NULL));
					_tmp6_ = (g_free (_tmp6_), NULL);
					_tmp5_ = (g_free (_tmp5_), NULL);
					opened_inner = TRUE;
					inner_names = (g_free (inner_names), NULL);
				}
			}
			_tmp8_ = NULL;
			_tmp7_ = NULL;
			child = (_tmp8_ = (_tmp7_ = (GtkMateScope*) g_sequence_get (iter), (_tmp7_ == NULL) ? NULL : g_object_ref (_tmp7_)), (child == NULL) ? NULL : (child = (g_object_unref (child), NULL)), _tmp8_);
			if (gtk_text_iter_compare ((_tmp9_ = gtk_mate_scope_start_iter (child), &_tmp9_), &position) > 0) {
				char* _tmp12_;
				GtkTextIter _tmp11_ = {0};
				GtkMateBuffer* _tmp10_;
				_tmp12_ = NULL;
				_tmp10_ = NULL;
				g_string_append (_result_, _tmp12_ = g_markup_escape_text (gtk_text_buffer_get_slice ((GtkTextBuffer*) (_tmp10_ = gtk_mate_exporter_buffer (self)), &position, (_tmp11_ = gtk_mate_scope_start_iter (child), &_tmp11_), TRUE), -1));
				_tmp12_ = (g_free (_tmp12_), NULL);
				(_tmp10_ == NULL) ? NULL : (_tmp10_ = (g_object_unref (_tmp10_), NULL));
				position = gtk_mate_scope_start_iter (child);
			}
			if (gtk_mate_exporter_scope_has_inner (self, scope)) {
				gboolean _tmp13_;
				GtkTextIter _tmp14_ = {0};
				_tmp13_ = FALSE;
				if (gtk_text_iter_compare (&position, (_tmp14_ = gtk_mate_scope_inner_end_iter (scope), &_tmp14_)) >= 0) {
					_tmp13_ = !closed_inner;
				} else {
					_tmp13_ = FALSE;
				}
				if (_tmp13_) {
					g_string_append (_result_, "</span>");
					closed_inner = TRUE;
				}
			}
			gtk_mate_exporter_scope_to_html (self, _result_, child);
			position = gtk_mate_scope_end_iter (child);
			iter = g_sequence_iter_next (iter);
		}
		_tmp15_ = FALSE;
		if (child != NULL) {
			GtkTextIter _tmp17_ = {0};
			GtkTextIter _tmp16_ = {0};
			_tmp15_ = gtk_text_iter_compare ((_tmp16_ = gtk_mate_scope_end_iter (child), &_tmp16_), (_tmp17_ = gtk_mate_scope_end_iter (scope), &_tmp17_)) < 0;
		} else {
			_tmp15_ = FALSE;
		}
		if (_tmp15_) {
			char* _tmp21_;
			GtkTextIter _tmp20_ = {0};
			GtkTextIter _tmp19_ = {0};
			GtkMateBuffer* _tmp18_;
			_tmp21_ = NULL;
			_tmp18_ = NULL;
			g_string_append (_result_, _tmp21_ = g_markup_escape_text (gtk_text_buffer_get_slice ((GtkTextBuffer*) (_tmp18_ = gtk_mate_exporter_buffer (self)), (_tmp19_ = gtk_mate_scope_end_iter (child), &_tmp19_), (_tmp20_ = gtk_mate_scope_end_iter (scope), &_tmp20_), TRUE), -1));
			_tmp21_ = (g_free (_tmp21_), NULL);
			(_tmp18_ == NULL) ? NULL : (_tmp18_ = (g_object_unref (_tmp18_), NULL));
		}
		(child == NULL) ? NULL : (child = (g_object_unref (child), NULL));
	} else {
		char* _tmp25_;
		GtkTextIter _tmp24_ = {0};
		GtkTextIter _tmp23_ = {0};
		GtkMateBuffer* _tmp22_;
		_tmp25_ = NULL;
		_tmp22_ = NULL;
		g_string_append (_result_, _tmp25_ = g_markup_escape_text (gtk_text_buffer_get_slice ((GtkTextBuffer*) (_tmp22_ = gtk_mate_exporter_buffer (self)), (_tmp23_ = gtk_mate_scope_start_iter (scope), &_tmp23_), (_tmp24_ = gtk_mate_scope_end_iter (scope), &_tmp24_), TRUE), -1));
		_tmp25_ = (g_free (_tmp25_), NULL);
		(_tmp22_ == NULL) ? NULL : (_tmp22_ = (g_object_unref (_tmp22_), NULL));
	}
	_tmp26_ = FALSE;
	if (_vala_strcmp0 (names, "") != 0) {
		_tmp26_ = names != NULL;
	} else {
		_tmp26_ = FALSE;
	}
	if (_tmp26_) {
		g_string_append (_result_, "</span>");
	}
	names = (g_free (names), NULL);
	return;
}


static GtkMateBuffer* gtk_mate_exporter_buffer (GtkMateExporter* self) {
	GtkMateBuffer* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = NULL;
	return (_tmp0_ = GTK_MATE_BUFFER (gtk_text_view_get_buffer ((GtkTextView*) self->view)), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
}


static char* gtk_mate_exporter_theme_name (GtkMateExporter* self) {
	const char* _tmp1_;
	GtkMateBuffer* _tmp0_;
	char* _tmp2_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	return (_tmp2_ = (_tmp1_ = gtk_mate_colourer_get_theme (gtk_mate_parser_get_colourer ((_tmp0_ = gtk_mate_exporter_buffer (self))->parser))->name, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), (_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_object_unref (_tmp0_), NULL)), _tmp2_);
}


static char* gtk_mate_exporter_theme_name_css (GtkMateExporter* self) {
	char* _tmp1_;
	GtkMateBuffer* _tmp0_;
	char* _tmp2_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	return (_tmp2_ = string_helper_gsub (_tmp1_ = g_utf8_strdown (gtk_mate_colourer_get_theme (gtk_mate_parser_get_colourer ((_tmp0_ = gtk_mate_exporter_buffer (self))->parser))->name, -1), " ", "_"), _tmp1_ = (g_free (_tmp1_), NULL), (_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_object_unref (_tmp0_), NULL)), _tmp2_);
}


static char* gtk_mate_exporter_html_header (GtkMateExporter* self, const char* title) {
	char* _tmp1_;
	char* _tmp0_;
	char* _tmp2_;
	char* header;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (title != NULL, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	header = (_tmp2_ = g_strconcat (_tmp1_ = g_strconcat (_tmp0_ = g_strconcat ("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\">\n" "<head>\n" "\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n" "\t<title>", title, NULL), "</title>\n", NULL), "\t<style type=\"text/css\">\n", NULL), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp2_);
	return header;
}


static char* gtk_mate_exporter_body_start (GtkMateExporter* self) {
	char* html;
	g_return_val_if_fail (self != NULL, NULL);
	html = g_strdup ("\t</style>\n</head>\n\n<body>\n");
	return html;
}


static char* gtk_mate_exporter_body_end (GtkMateExporter* self) {
	char* html;
	g_return_val_if_fail (self != NULL, NULL);
	html = g_strdup ("</body>\n</html>\n");
	return html;
}


static glong string_get_length (const char* self) {
	g_return_val_if_fail (self != NULL, 0L);
	return g_utf8_strlen (self, -1);
}


static char* gtk_mate_exporter_colour (GtkMateExporter* self, const char* colour) {
	GString* _result_;
	const char* _tmp9_;
	char* _tmp10_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (colour != NULL, NULL);
	_result_ = g_string_new ("");
	if (string_get_length (colour) == 9) {
		char* _tmp1_;
		char* _tmp0_;
		char* _tmp3_;
		char* _tmp2_;
		char* _tmp5_;
		char* _tmp4_;
		char* _tmp6_;
		g_string_append (_result_, "\tbackground-color: rgba(");
		_tmp1_ = NULL;
		_tmp0_ = NULL;
		g_string_append (_result_, _tmp1_ = g_strconcat (_tmp0_ = g_strdup_printf ("%d", gtk_mate_colourer_hex_to_int (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 1)), g_utf8_get_char (g_utf8_offset_to_pointer (colour, 2)))), ", ", NULL));
		_tmp1_ = (g_free (_tmp1_), NULL);
		_tmp0_ = (g_free (_tmp0_), NULL);
		_tmp3_ = NULL;
		_tmp2_ = NULL;
		g_string_append (_result_, _tmp3_ = g_strconcat (_tmp2_ = g_strdup_printf ("%d", gtk_mate_colourer_hex_to_int (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 3)), g_utf8_get_char (g_utf8_offset_to_pointer (colour, 4)))), ", ", NULL));
		_tmp3_ = (g_free (_tmp3_), NULL);
		_tmp2_ = (g_free (_tmp2_), NULL);
		_tmp5_ = NULL;
		_tmp4_ = NULL;
		g_string_append (_result_, _tmp5_ = g_strconcat (_tmp4_ = g_strdup_printf ("%d", gtk_mate_colourer_hex_to_int (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 5)), g_utf8_get_char (g_utf8_offset_to_pointer (colour, 6)))), ", ", NULL));
		_tmp5_ = (g_free (_tmp5_), NULL);
		_tmp4_ = (g_free (_tmp4_), NULL);
		_tmp6_ = NULL;
		g_string_append (_result_, _tmp6_ = g_strdup_printf ("%0.2f", ((double) gtk_mate_colourer_hex_to_int (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 7)), g_utf8_get_char (g_utf8_offset_to_pointer (colour, 8)))) / 256.0));
		_tmp6_ = (g_free (_tmp6_), NULL);
		g_string_append (_result_, ");\n");
	} else {
		if (string_get_length (colour) == 7) {
			char* _tmp8_;
			char* _tmp7_;
			_tmp8_ = NULL;
			_tmp7_ = NULL;
			g_string_append (_result_, _tmp8_ = g_strconcat (_tmp7_ = g_strconcat ("\tbackground-color: ", colour, NULL), ";\n", NULL));
			_tmp8_ = (g_free (_tmp8_), NULL);
			_tmp7_ = (g_free (_tmp7_), NULL);
		}
	}
	_tmp9_ = NULL;
	_tmp10_ = NULL;
	return (_tmp10_ = (_tmp9_ = _result_->str, (_tmp9_ == NULL) ? NULL : g_strdup (_tmp9_)), (_result_ == NULL) ? NULL : (_result_ = (g_string_free (_result_, TRUE), NULL)), _tmp10_);
}


static char* gtk_mate_exporter_css (GtkMateExporter* self) {
	GtkMateColourer* _tmp0_;
	GtkMateColourer* colourer;
	GString* _result_;
	char* _tmp3_;
	char* _tmp2_;
	char* _tmp1_;
	char* _tmp13_;
	char* _tmp12_;
	char* _tmp11_;
	char* _tmp10_;
	char* _tmp9_;
	char* _tmp8_;
	char* _tmp7_;
	char* _tmp6_;
	char* _tmp5_;
	char* _tmp4_;
	char* _tmp16_;
	char* _tmp15_;
	char* _tmp14_;
	char* selection_colour;
	gboolean _tmp17_;
	const char* _tmp44_;
	char* _tmp45_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = NULL;
	colourer = (_tmp0_ = gtk_mate_parser_get_colourer (GTK_MATE_BUFFER (gtk_text_view_get_buffer ((GtkTextView*) self->view))->parser), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	_result_ = g_string_new ("");
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	g_string_append (_result_, _tmp3_ = g_strconcat (_tmp2_ = g_strconcat ("/* Stylesheet generated from theme: ", _tmp1_ = gtk_mate_exporter_theme_name (self), NULL), " */\n\n", NULL));
	_tmp3_ = (g_free (_tmp3_), NULL);
	_tmp2_ = (g_free (_tmp2_), NULL);
	_tmp1_ = (g_free (_tmp1_), NULL);
	g_string_append (_result_, "body {\n\tmargin: 0;\n\tpadding: 0;\n}\n\n");
	g_string_append (_result_, "pre.textmate-source {\n\tmargin: 0;\n\tpadding: 0 0 0 2px;\n\tfont-family: Monaco, monospace;\n" "\tfont-size: 11px;\n\tline-height: 1.3em;\n\tword-wrap: break-word;\n\twhite-space: pre;\n" "\twhite-space: pre-wrap;\n\twhite-space: -moz-pre-wrap;\n\twhite-space: -o-pre-wrap;\n}\n\n");
	_tmp13_ = NULL;
	_tmp12_ = NULL;
	_tmp11_ = NULL;
	_tmp10_ = NULL;
	_tmp9_ = NULL;
	_tmp8_ = NULL;
	_tmp7_ = NULL;
	_tmp6_ = NULL;
	_tmp5_ = NULL;
	_tmp4_ = NULL;
	g_string_append (_result_, _tmp13_ = g_strconcat (_tmp12_ = g_strconcat (_tmp10_ = g_strconcat (_tmp9_ = g_strconcat (_tmp7_ = g_strconcat (_tmp6_ = g_strconcat (_tmp5_ = g_strconcat ("pre.textmate-source.", _tmp4_ = gtk_mate_exporter_theme_name_css (self), NULL), " {\n", NULL), "\tcolor: ", NULL), _tmp8_ = gtk_mate_colourer_global_foreground_colour (colourer), NULL), ";\n\tbackground-color: ", NULL), _tmp11_ = gtk_mate_colourer_global_background_colour (colourer), NULL), ";\n}\n\n", NULL));
	_tmp13_ = (g_free (_tmp13_), NULL);
	_tmp12_ = (g_free (_tmp12_), NULL);
	_tmp11_ = (g_free (_tmp11_), NULL);
	_tmp10_ = (g_free (_tmp10_), NULL);
	_tmp9_ = (g_free (_tmp9_), NULL);
	_tmp8_ = (g_free (_tmp8_), NULL);
	_tmp7_ = (g_free (_tmp7_), NULL);
	_tmp6_ = (g_free (_tmp6_), NULL);
	_tmp5_ = (g_free (_tmp5_), NULL);
	_tmp4_ = (g_free (_tmp4_), NULL);
	g_string_append (_result_, "pre.textmate-source .linenum {\n");
	g_string_append (_result_, "\twidth: 75px;\n");
	g_string_append (_result_, "\tpadding: 0.1em 1em 0.2em 0;\n");
	g_string_append (_result_, "\tcolor: #888;\n");
	g_string_append (_result_, "\tbackground-color: #eee;\n");
	g_string_append (_result_, "}\n\n");
	_tmp16_ = NULL;
	_tmp15_ = NULL;
	_tmp14_ = NULL;
	g_string_append (_result_, _tmp16_ = g_strconcat (_tmp15_ = g_strconcat ("pre.textmate-source.", _tmp14_ = gtk_mate_exporter_theme_name_css (self), NULL), " span {\n", NULL));
	_tmp16_ = (g_free (_tmp16_), NULL);
	_tmp15_ = (g_free (_tmp15_), NULL);
	_tmp14_ = (g_free (_tmp14_), NULL);
	g_string_append (_result_, "\tpadding-top: 0.2em;\n");
	g_string_append (_result_, "\tpadding-bottom: 0.1em;\n");
	g_string_append (_result_, "}\n\n");
	selection_colour = (char*) gee_map_get ((GeeMap*) gtk_mate_colourer_get_theme (colourer)->global_settings, "selection");
	_tmp17_ = FALSE;
	if (selection_colour != NULL) {
		_tmp17_ = _vala_strcmp0 (selection_colour, "") != 0;
	} else {
		_tmp17_ = FALSE;
	}
	if (_tmp17_) {
		char* _tmp20_;
		char* _tmp19_;
		char* _tmp18_;
		char* _tmp21_;
		_tmp20_ = NULL;
		_tmp19_ = NULL;
		_tmp18_ = NULL;
		g_string_append (_result_, _tmp20_ = g_strconcat (_tmp19_ = g_strconcat ("pre.textmate-source.", _tmp18_ = gtk_mate_exporter_theme_name_css (self), NULL), " ::selection {\n", NULL));
		_tmp20_ = (g_free (_tmp20_), NULL);
		_tmp19_ = (g_free (_tmp19_), NULL);
		_tmp18_ = (g_free (_tmp18_), NULL);
		_tmp21_ = NULL;
		g_string_append (_result_, _tmp21_ = gtk_mate_exporter_colour (self, selection_colour));
		_tmp21_ = (g_free (_tmp21_), NULL);
		g_string_append (_result_, "}\n\n");
	}
	{
		GeeIterator* _setting_it;
		_setting_it = gee_iterable_iterator ((GeeIterable*) gtk_mate_colourer_get_theme (colourer)->settings);
		while (gee_iterator_next (_setting_it)) {
			GtkMateThemeSetting* setting;
			char* _tmp23_;
			char* _tmp22_;
			char* _tmp34_;
			char* _tmp33_;
			char* _tmp32_;
			char* _tmp31_;
			char* _tmp30_;
			char* _tmp29_;
			char* _tmp28_;
			char* _tmp27_;
			char* _tmp26_;
			char* _tmp25_;
			char* _tmp24_;
			char* _tmp35_;
			gboolean _tmp36_;
			char* font_style;
			gboolean _tmp40_;
			gboolean _tmp41_;
			gboolean _tmp42_;
			char* bg_colour;
			setting = (GtkMateThemeSetting*) gee_iterator_get (_setting_it);
			_tmp23_ = NULL;
			_tmp22_ = NULL;
			g_string_append (_result_, _tmp23_ = g_strconcat (_tmp22_ = g_strconcat ("/* ", setting->name, NULL), " */\n", NULL));
			_tmp23_ = (g_free (_tmp23_), NULL);
			_tmp22_ = (g_free (_tmp22_), NULL);
			_tmp34_ = NULL;
			_tmp33_ = NULL;
			_tmp32_ = NULL;
			_tmp31_ = NULL;
			_tmp30_ = NULL;
			_tmp29_ = NULL;
			_tmp28_ = NULL;
			_tmp27_ = NULL;
			_tmp26_ = NULL;
			_tmp25_ = NULL;
			_tmp24_ = NULL;
			g_string_append (_result_, _tmp34_ = g_strconcat (_tmp33_ = g_strconcat (_tmp26_ = g_strconcat (_tmp25_ = g_strconcat ("pre.textmate-source.", _tmp24_ = gtk_mate_exporter_theme_name_css (self), NULL), " .", NULL), _tmp32_ = string_helper_gsub (_tmp28_ = string_helper_gsub (_tmp27_ = string_helper_gsub (setting->selector, ".", "_"), " ", " ."), ", ", _tmp31_ = g_strconcat (_tmp30_ = g_strconcat (", pre.textmate-source.", _tmp29_ = gtk_mate_exporter_theme_name_css (self), NULL), " ", NULL)), NULL), " {\n", NULL));
			_tmp34_ = (g_free (_tmp34_), NULL);
			_tmp33_ = (g_free (_tmp33_), NULL);
			_tmp32_ = (g_free (_tmp32_), NULL);
			_tmp31_ = (g_free (_tmp31_), NULL);
			_tmp30_ = (g_free (_tmp30_), NULL);
			_tmp29_ = (g_free (_tmp29_), NULL);
			_tmp28_ = (g_free (_tmp28_), NULL);
			_tmp27_ = (g_free (_tmp27_), NULL);
			_tmp26_ = (g_free (_tmp26_), NULL);
			_tmp25_ = (g_free (_tmp25_), NULL);
			_tmp24_ = (g_free (_tmp24_), NULL);
			_tmp35_ = NULL;
			if ((_tmp36_ = (_tmp35_ = (char*) gee_map_get ((GeeMap*) setting->settings, "foreground")) != NULL, _tmp35_ = (g_free (_tmp35_), NULL), _tmp36_)) {
				char* _tmp39_;
				char* _tmp38_;
				char* _tmp37_;
				_tmp39_ = NULL;
				_tmp38_ = NULL;
				_tmp37_ = NULL;
				g_string_append (_result_, _tmp39_ = g_strconcat (_tmp38_ = g_strconcat ("\tcolor: ", _tmp37_ = (char*) gee_map_get ((GeeMap*) setting->settings, "foreground"), NULL), ";\n", NULL));
				_tmp39_ = (g_free (_tmp39_), NULL);
				_tmp38_ = (g_free (_tmp38_), NULL);
				_tmp37_ = (g_free (_tmp37_), NULL);
			}
			font_style = (char*) gee_map_get ((GeeMap*) setting->settings, "fontStyle");
			_tmp40_ = FALSE;
			if (font_style != NULL) {
				_tmp40_ = strstr (font_style, "italic") != NULL;
			} else {
				_tmp40_ = FALSE;
			}
			if (_tmp40_) {
				g_string_append (_result_, "\tfont-style: italic;\n");
			}
			_tmp41_ = FALSE;
			if (font_style != NULL) {
				_tmp41_ = strstr (font_style, "underline") != NULL;
			} else {
				_tmp41_ = FALSE;
			}
			if (_tmp41_) {
				g_string_append (_result_, "\ttext-decoration: underline;\n");
			}
			_tmp42_ = FALSE;
			if (font_style != NULL) {
				_tmp42_ = strstr (font_style, "bold") != NULL;
			} else {
				_tmp42_ = FALSE;
			}
			if (_tmp42_) {
				g_string_append (_result_, "\tfont-weight: bold;\n");
			}
			bg_colour = (char*) gee_map_get ((GeeMap*) setting->settings, "background");
			if (bg_colour != NULL) {
				char* _tmp43_;
				_tmp43_ = NULL;
				g_string_append (_result_, _tmp43_ = gtk_mate_exporter_colour (self, bg_colour));
				_tmp43_ = (g_free (_tmp43_), NULL);
			}
			g_string_append (_result_, "}\n\n");
			(setting == NULL) ? NULL : (setting = (g_object_unref (setting), NULL));
			font_style = (g_free (font_style), NULL);
			bg_colour = (g_free (bg_colour), NULL);
		}
		(_setting_it == NULL) ? NULL : (_setting_it = (g_object_unref (_setting_it), NULL));
	}
	_tmp44_ = NULL;
	_tmp45_ = NULL;
	return (_tmp45_ = (_tmp44_ = _result_->str, (_tmp44_ == NULL) ? NULL : g_strdup (_tmp44_)), (colourer == NULL) ? NULL : (colourer = (g_object_unref (colourer), NULL)), (_result_ == NULL) ? NULL : (_result_ = (g_string_free (_result_, TRUE), NULL)), selection_colour = (g_free (selection_colour), NULL), _tmp45_);
}


static char* gtk_mate_exporter_html (GtkMateExporter* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return g_strdup ("");
}


static void gtk_mate_exporter_class_init (GtkMateExporterClass * klass) {
	gtk_mate_exporter_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_exporter_finalize;
}


static void gtk_mate_exporter_instance_init (GtkMateExporter * self) {
}


static void gtk_mate_exporter_finalize (GObject* obj) {
	GtkMateExporter * self;
	self = GTK_MATE_EXPORTER (obj);
	(self->view == NULL) ? NULL : (self->view = (g_object_unref (self->view), NULL));
	G_OBJECT_CLASS (gtk_mate_exporter_parent_class)->finalize (obj);
}


GType gtk_mate_exporter_get_type (void) {
	static GType gtk_mate_exporter_type_id = 0;
	if (gtk_mate_exporter_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateExporterClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_exporter_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateExporter), 0, (GInstanceInitFunc) gtk_mate_exporter_instance_init, NULL };
		gtk_mate_exporter_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateExporter", &g_define_type_info, 0);
	}
	return gtk_mate_exporter_type_id;
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




