
#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <gtksourceview/gtksourceview.h>
#include <stdlib.h>
#include <string.h>
#include <gee/hashmap.h>
#include <gee/arraylist.h>
#include <gee/map.h>
#include <gdk/gdk.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <pango/pango.h>


#define GTK_MATE_TYPE_COLOURER (gtk_mate_colourer_get_type ())
#define GTK_MATE_COLOURER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_COLOURER, GtkMateColourer))
#define GTK_MATE_COLOURER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_COLOURER, GtkMateColourerClass))
#define GTK_MATE_IS_COLOURER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_COLOURER))
#define GTK_MATE_IS_COLOURER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_COLOURER))
#define GTK_MATE_COLOURER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_COLOURER, GtkMateColourerClass))

typedef struct _GtkMateColourer GtkMateColourer;
typedef struct _GtkMateColourerClass GtkMateColourerClass;
typedef struct _GtkMateColourerPrivate GtkMateColourerPrivate;

#define GTK_MATE_TYPE_BUFFER (gtk_mate_buffer_get_type ())
#define GTK_MATE_BUFFER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_BUFFER, GtkMateBuffer))
#define GTK_MATE_BUFFER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_BUFFER, GtkMateBufferClass))
#define GTK_MATE_IS_BUFFER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_BUFFER))
#define GTK_MATE_IS_BUFFER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_BUFFER))
#define GTK_MATE_BUFFER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_BUFFER, GtkMateBufferClass))

typedef struct _GtkMateBuffer GtkMateBuffer;
typedef struct _GtkMateBufferClass GtkMateBufferClass;

#define GTK_MATE_TYPE_THEME (gtk_mate_theme_get_type ())
#define GTK_MATE_THEME(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_THEME, GtkMateTheme))
#define GTK_MATE_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_THEME, GtkMateThemeClass))
#define GTK_MATE_IS_THEME(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_THEME))
#define GTK_MATE_IS_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_THEME))
#define GTK_MATE_THEME_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_THEME, GtkMateThemeClass))

typedef struct _GtkMateTheme GtkMateTheme;
typedef struct _GtkMateThemeClass GtkMateThemeClass;
typedef struct _GtkMateThemePrivate GtkMateThemePrivate;

#define GTK_MATE_TYPE_THEME_SETTING (gtk_mate_theme_setting_get_type ())
#define GTK_MATE_THEME_SETTING(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSetting))
#define GTK_MATE_THEME_SETTING_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSettingClass))
#define GTK_MATE_IS_THEME_SETTING(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_THEME_SETTING))
#define GTK_MATE_IS_THEME_SETTING_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_THEME_SETTING))
#define GTK_MATE_THEME_SETTING_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSettingClass))

typedef struct _GtkMateThemeSetting GtkMateThemeSetting;
typedef struct _GtkMateThemeSettingClass GtkMateThemeSettingClass;

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

#define GTK_MATE_TYPE_SINGLE_PATTERN (gtk_mate_single_pattern_get_type ())
#define GTK_MATE_SINGLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePattern))
#define GTK_MATE_SINGLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePatternClass))
#define GTK_MATE_IS_SINGLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SINGLE_PATTERN))
#define GTK_MATE_IS_SINGLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SINGLE_PATTERN))
#define GTK_MATE_SINGLE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePatternClass))

typedef struct _GtkMateSinglePattern GtkMateSinglePattern;
typedef struct _GtkMateSinglePatternClass GtkMateSinglePatternClass;
typedef struct _GtkMatePatternPrivate GtkMatePatternPrivate;

#define GTK_MATE_TYPE_DOUBLE_PATTERN (gtk_mate_double_pattern_get_type ())
#define GTK_MATE_DOUBLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePattern))
#define GTK_MATE_DOUBLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePatternClass))
#define GTK_MATE_IS_DOUBLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN))
#define GTK_MATE_IS_DOUBLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_DOUBLE_PATTERN))
#define GTK_MATE_DOUBLE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePatternClass))

typedef struct _GtkMateDoublePattern GtkMateDoublePattern;
typedef struct _GtkMateDoublePatternClass GtkMateDoublePatternClass;
typedef struct _GtkMateDoublePatternPrivate GtkMateDoublePatternPrivate;
typedef struct _GtkMateBufferPrivate GtkMateBufferPrivate;

#define GTK_MATE_TYPE_PARSER (gtk_mate_parser_get_type ())
#define GTK_MATE_PARSER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_PARSER, GtkMateParser))
#define GTK_MATE_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_PARSER, GtkMateParserClass))
#define GTK_MATE_IS_PARSER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_PARSER))
#define GTK_MATE_IS_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_PARSER))
#define GTK_MATE_PARSER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_PARSER, GtkMateParserClass))

typedef struct _GtkMateParser GtkMateParser;
typedef struct _GtkMateParserClass GtkMateParserClass;
typedef struct _GtkMateThemeSettingPrivate GtkMateThemeSettingPrivate;

#define GTK_MATE_TYPE_MATCHER (gtk_mate_matcher_get_type ())
#define GTK_MATE_MATCHER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_MATCHER, GtkMateMatcher))
#define GTK_MATE_MATCHER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_MATCHER, GtkMateMatcherClass))
#define GTK_MATE_IS_MATCHER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_MATCHER))
#define GTK_MATE_IS_MATCHER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_MATCHER))
#define GTK_MATE_MATCHER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_MATCHER, GtkMateMatcherClass))

typedef struct _GtkMateMatcher GtkMateMatcher;
typedef struct _GtkMateMatcherClass GtkMateMatcherClass;

struct _GtkMateColourer {
	GtkObject parent_instance;
	GtkMateColourerPrivate * priv;
};

struct _GtkMateColourerClass {
	GtkObjectClass parent_class;
};

struct _GtkMateColourerPrivate {
	GtkMateBuffer* _buffer;
	GtkMateTheme* _theme;
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

struct _GtkMateBuffer {
	GtkSourceBuffer parent_instance;
	GtkMateBufferPrivate * priv;
	GtkMateParser* parser;
};

struct _GtkMateBufferClass {
	GtkSourceBufferClass parent_class;
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



GType gtk_mate_colourer_get_type (void);
GType gtk_mate_buffer_get_type (void);
GType gtk_mate_theme_get_type (void);
#define GTK_MATE_COLOURER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_TYPE_COLOURER, GtkMateColourerPrivate))
enum  {
	GTK_MATE_COLOURER_DUMMY_PROPERTY,
	GTK_MATE_COLOURER_BUFFER,
	GTK_MATE_COLOURER_THEME
};
GtkMateTheme* gtk_mate_colourer_get_theme (GtkMateColourer* self);
GType gtk_mate_theme_setting_get_type (void);
char* gtk_mate_colourer_merge_colour (const char* parent_colour, const char* colour);
char* gtk_mate_colourer_global_background_colour (GtkMateColourer* self);
char* gtk_mate_colourer_global_foreground_colour (GtkMateColourer* self);
GdkColor gtk_mate_colourer_parse_colour (GtkMateColourer* self, const char* colour);
GType gtk_mate_view_get_type (void);
void gtk_mate_colourer_set_global_settings (GtkMateColourer* self, GtkMateView* view);
void gtk_mate_colourer_set_buffer (GtkMateColourer* self, GtkMateBuffer* value);
GtkMateColourer* gtk_mate_colourer_new (GtkMateBuffer* buffer);
GtkMateColourer* gtk_mate_colourer_construct (GType object_type, GtkMateBuffer* buffer);
GtkMateColourer* gtk_mate_colourer_new (GtkMateBuffer* buffer);
GType gtk_mate_scope_get_type (void);
GType gtk_mate_pattern_get_type (void);
GType onig_match_get_type (void);
GType onig_rx_get_type (void);
GType gtk_mate_text_loc_get_type (void);
const char* gtk_mate_scope_get_name (GtkMateScope* self);
GType gtk_mate_single_pattern_get_type (void);
GType gtk_mate_double_pattern_get_type (void);
void gtk_mate_colourer_colour_scope (GtkMateColourer* self, GtkMateScope* scope, gboolean inner, gboolean force);
void gtk_mate_colourer_colour_line_with_scopes (GtkMateColourer* self, GeeArrayList* scopes);
gint gtk_mate_scope_priority (GtkMateScope* self, gboolean inner);
void gtk_mate_scope_set_is_coloured (GtkMateScope* self, gboolean value);
GtkTextIter gtk_mate_scope_inner_start_iter (GtkMateScope* self);
GtkTextIter gtk_mate_scope_inner_end_iter (GtkMateScope* self);
GtkTextIter gtk_mate_scope_start_iter (GtkMateScope* self);
GtkTextIter gtk_mate_scope_end_iter (GtkMateScope* self);
GtkMateThemeSetting* gtk_mate_theme_settings_for_scope (GtkMateTheme* self, GtkMateScope* scope, gboolean inner, GtkMateThemeSetting* exclude_setting);
GtkMateBuffer* gtk_mate_colourer_get_buffer (GtkMateColourer* self);
void gtk_mate_colourer_set_tag_properties (GtkMateColourer* self, GtkMateScope* scope, GtkTextTag* tag, GtkMateThemeSetting* setting);
GType gtk_mate_parser_get_type (void);
void gtk_mate_parser_added_tag (GtkMateParser* self, GtkTextTag* tag);
GType gtk_mate_matcher_get_type (void);
char* gtk_mate_scope_nearest_foreground_colour (GtkMateScope* self);
gint gtk_mate_colourer_char_to_hex (gunichar ch);
gint gtk_mate_colourer_hex_to_int (gunichar ch1, gunichar ch2);
void gtk_mate_colourer_uncolour_scope (GtkMateColourer* self, GtkMateScope* scope, gboolean recurse);
void gtk_mate_colourer_uncolour_scopes (GtkMateColourer* self, GeeArrayList* scopes);
GSequence* gtk_mate_scope_get_children (GtkMateScope* self);
void gtk_mate_colourer_set_theme (GtkMateColourer* self, GtkMateTheme* value);
static gpointer gtk_mate_colourer_parent_class = NULL;
static void gtk_mate_colourer_finalize (GObject* obj);
static void gtk_mate_colourer_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void gtk_mate_colourer_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
static int _vala_strcmp0 (const char * str1, const char * str2);



char* gtk_mate_colourer_global_background_colour (GtkMateColourer* self) {
	char* bg_colour;
	gboolean _tmp0_;
	char* _tmp3_;
	g_return_val_if_fail (self != NULL, NULL);
	bg_colour = (char*) gee_map_get ((GeeMap*) self->priv->_theme->global_settings, "background");
	_tmp0_ = FALSE;
	if (bg_colour != NULL) {
		_tmp0_ = _vala_strcmp0 (bg_colour, "") != 0;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		char* _tmp1_;
		_tmp1_ = NULL;
		bg_colour = (_tmp1_ = gtk_mate_colourer_merge_colour ("#FFFFFF", bg_colour), bg_colour = (g_free (bg_colour), NULL), _tmp1_);
		return bg_colour;
	}
	_tmp3_ = NULL;
	return (_tmp3_ = NULL, bg_colour = (g_free (bg_colour), NULL), _tmp3_);
}


char* gtk_mate_colourer_global_foreground_colour (GtkMateColourer* self) {
	char* fg_colour;
	gboolean _tmp0_;
	char* _tmp3_;
	g_return_val_if_fail (self != NULL, NULL);
	fg_colour = (char*) gee_map_get ((GeeMap*) self->priv->_theme->global_settings, "foreground");
	_tmp0_ = FALSE;
	if (fg_colour != NULL) {
		_tmp0_ = _vala_strcmp0 (fg_colour, "") != 0;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		char* _tmp1_;
		_tmp1_ = NULL;
		fg_colour = (_tmp1_ = gtk_mate_colourer_merge_colour ("#FFFFFF", fg_colour), fg_colour = (g_free (fg_colour), NULL), _tmp1_);
		return fg_colour;
	}
	_tmp3_ = NULL;
	return (_tmp3_ = NULL, fg_colour = (g_free (fg_colour), NULL), _tmp3_);
}


void gtk_mate_colourer_set_global_settings (GtkMateColourer* self, GtkMateView* view) {
	char* bg_colour;
	char* fg_colour;
	g_return_if_fail (self != NULL);
	g_return_if_fail (view != NULL);
	bg_colour = gtk_mate_colourer_global_background_colour (self);
	if (bg_colour != NULL) {
		GdkColor _tmp0_ = {0};
		gtk_widget_modify_base (GTK_WIDGET (view), GTK_STATE_NORMAL, (_tmp0_ = gtk_mate_colourer_parse_colour (self, bg_colour), &_tmp0_));
	}
	fg_colour = gtk_mate_colourer_global_foreground_colour (self);
	if (fg_colour != NULL) {
		GdkColor _tmp1_ = {0};
		gtk_widget_modify_text (GTK_WIDGET (view), GTK_STATE_NORMAL, (_tmp1_ = gtk_mate_colourer_parse_colour (self, fg_colour), &_tmp1_));
	}
	bg_colour = (g_free (bg_colour), NULL);
	fg_colour = (g_free (fg_colour), NULL);
}


GtkMateColourer* gtk_mate_colourer_construct (GType object_type, GtkMateBuffer* buffer) {
	GtkMateColourer * self;
	g_return_val_if_fail (buffer != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	gtk_mate_colourer_set_buffer (self, buffer);
	return self;
}


GtkMateColourer* gtk_mate_colourer_new (GtkMateBuffer* buffer) {
	return gtk_mate_colourer_construct (GTK_MATE_TYPE_COLOURER, buffer);
}


GdkColor gtk_mate_colourer_parse_colour (GtkMateColourer* self, const char* colour) {
	GdkColor c = {0};
	gdk_color_parse (colour, &c);
	return c;
}


void gtk_mate_colourer_colour_line_with_scopes (GtkMateColourer* self, GeeArrayList* scopes) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (scopes != NULL);
	if (self->priv->_theme == NULL) {
		return;
	}
	{
		GeeIterator* _scope_it;
		_scope_it = gee_iterable_iterator ((GeeIterable*) scopes);
		while (gee_iterator_next (_scope_it)) {
			GtkMateScope* scope;
			gboolean _tmp0_;
			gboolean _tmp1_;
			gboolean _tmp3_;
			gboolean _tmp4_;
			scope = (GtkMateScope*) gee_iterator_get (_scope_it);
			if (scope->parent == NULL) {
				(scope == NULL) ? NULL : (scope = (g_object_unref (scope), NULL));
				continue;
			}
			_tmp0_ = FALSE;
			_tmp1_ = FALSE;
			if (gtk_mate_scope_get_name (scope) == NULL) {
				_tmp1_ = scope->pattern != NULL;
			} else {
				_tmp1_ = FALSE;
			}
			if (_tmp1_) {
				gboolean _tmp2_;
				_tmp2_ = FALSE;
				if (GTK_MATE_IS_SINGLE_PATTERN (scope->pattern)) {
					_tmp2_ = TRUE;
				} else {
					_tmp2_ = GTK_MATE_DOUBLE_PATTERN (scope->pattern)->content_name == NULL;
				}
				_tmp0_ = _tmp2_;
			} else {
				_tmp0_ = FALSE;
			}
			if (_tmp0_) {
				/*stdout.printf("  no pattern name\n");*/
				(scope == NULL) ? NULL : (scope = (g_object_unref (scope), NULL));
				continue;
			}
			/* if (scope.is_coloured) {
			 //stdout.printf("  already coloured\n");
			 continue;
			 }*/
			gtk_mate_colourer_colour_scope (self, scope, FALSE, TRUE);
			_tmp3_ = FALSE;
			_tmp4_ = FALSE;
			if (GTK_MATE_IS_DOUBLE_PATTERN (scope->pattern)) {
				_tmp4_ = GTK_MATE_DOUBLE_PATTERN (scope->pattern)->content_name != NULL;
			} else {
				_tmp4_ = FALSE;
			}
			if (_tmp4_) {
				_tmp3_ = scope->is_capture == FALSE;
			} else {
				_tmp3_ = FALSE;
			}
			if (_tmp3_) {
				gtk_mate_colourer_colour_scope (self, scope, TRUE, TRUE);
			}
			(scope == NULL) ? NULL : (scope = (g_object_unref (scope), NULL));
		}
		(_scope_it == NULL) ? NULL : (_scope_it = (g_object_unref (_scope_it), NULL));
	}
}


void gtk_mate_colourer_colour_scope (GtkMateColourer* self, GtkMateScope* scope, gboolean inner, gboolean force) {
	gint priority;
	GtkTextTag* tag;
	GtkTextIter start_iter = {0};
	GtkTextIter end_iter = {0};
	GtkMateThemeSetting* setting;
	GtkMateThemeSetting* exclude_setting;
	char* tag_name;
	gboolean _tmp6_;
	GtkTextTagTable* _tmp12_;
	GtkTextTagTable* tag_table;
	gboolean new_tag;
	gboolean _tmp13_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	/*stdout.printf("colour_scope: %s (%s) [%d - %d]\n", scope.name, inner ? "true" : "false",
	   scope.start_offset(), scope.end_offset());*/
	priority = gtk_mate_scope_priority (scope, inner);
	tag = NULL;
	/*stdout.printf("  priority: %d\n", priority);*/
	gtk_mate_scope_set_is_coloured (scope, TRUE);
	if (inner) {
		start_iter = gtk_mate_scope_inner_start_iter (scope);
		end_iter = gtk_mate_scope_inner_end_iter (scope);
		if (scope->inner_tag != NULL) {
			GtkTextTag* _tmp1_;
			GtkTextTag* _tmp0_;
			_tmp1_ = NULL;
			_tmp0_ = NULL;
			tag = (_tmp1_ = (_tmp0_ = scope->inner_tag, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (tag == NULL) ? NULL : (tag = (g_object_unref (tag), NULL)), _tmp1_);
		}
	} else {
		start_iter = gtk_mate_scope_start_iter (scope);
		end_iter = gtk_mate_scope_end_iter (scope);
		if (scope->tag != NULL) {
			GtkTextTag* _tmp3_;
			GtkTextTag* _tmp2_;
			_tmp3_ = NULL;
			_tmp2_ = NULL;
			tag = (_tmp3_ = (_tmp2_ = scope->tag, (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (tag == NULL) ? NULL : (tag = (g_object_unref (tag), NULL)), _tmp3_);
		}
	}
	/* TODO: allow for multiple settings that set different 
	 parts of the style.*/
	setting = NULL;
	exclude_setting = NULL;
	if (scope->parent != NULL) {
		GtkMateThemeSetting* _tmp5_;
		GtkMateThemeSetting* _tmp4_;
		_tmp5_ = NULL;
		_tmp4_ = NULL;
		exclude_setting = (_tmp5_ = (_tmp4_ = scope->parent->theme_setting, (_tmp4_ == NULL) ? NULL : g_object_ref (_tmp4_)), (exclude_setting == NULL) ? NULL : (exclude_setting = (g_object_unref (exclude_setting), NULL)), _tmp5_);
	}
	tag_name = NULL;
	_tmp6_ = FALSE;
	if (tag == NULL) {
		_tmp6_ = TRUE;
	} else {
		_tmp6_ = force;
	}
	if (_tmp6_) {
		GtkMateThemeSetting* _tmp7_;
		_tmp7_ = NULL;
		setting = (_tmp7_ = gtk_mate_theme_settings_for_scope (self->priv->_theme, scope, inner, NULL), (setting == NULL) ? NULL : (setting = (g_object_unref (setting), NULL)), _tmp7_);
		/*exclude_setting);*/
		if (setting == NULL) {
			char* _tmp8_;
			_tmp8_ = NULL;
			tag_name = (_tmp8_ = g_strdup_printf ("gmv(%d):default", priority - 1), tag_name = (g_free (tag_name), NULL), _tmp8_);
		} else {
			GtkMateThemeSetting* _tmp10_;
			GtkMateThemeSetting* _tmp9_;
			char* _tmp11_;
			_tmp10_ = NULL;
			_tmp9_ = NULL;
			scope->theme_setting = (_tmp10_ = (_tmp9_ = setting, (_tmp9_ == NULL) ? NULL : g_object_ref (_tmp9_)), (scope->theme_setting == NULL) ? NULL : (scope->theme_setting = (g_object_unref (scope->theme_setting), NULL)), _tmp10_);
			_tmp11_ = NULL;
			tag_name = (_tmp11_ = g_strdup_printf ("gmv(%d):%s", priority - 1, gtk_mate_scope_get_name (scope)), tag_name = (g_free (tag_name), NULL), _tmp11_);
		}
	}
	_tmp12_ = NULL;
	tag_table = (_tmp12_ = gtk_text_buffer_get_tag_table ((GtkTextBuffer*) self->priv->_buffer), (_tmp12_ == NULL) ? NULL : g_object_ref (_tmp12_));
	new_tag = FALSE;
	_tmp13_ = FALSE;
	if (tag == NULL) {
		_tmp13_ = TRUE;
	} else {
		_tmp13_ = force;
	}
	if (_tmp13_) {
		GtkTextTag* _tmp15_;
		GtkTextTag* _tmp14_;
		_tmp15_ = NULL;
		_tmp14_ = NULL;
		tag = (_tmp15_ = (_tmp14_ = gtk_text_tag_table_lookup (tag_table, tag_name), (_tmp14_ == NULL) ? NULL : g_object_ref (_tmp14_)), (tag == NULL) ? NULL : (tag = (g_object_unref (tag), NULL)), _tmp15_);
		if (tag == NULL) {
			GtkTextTag* _tmp17_;
			GtkTextTag* _tmp16_;
			/* stdout.printf("create_tag\n");*/
			_tmp17_ = NULL;
			_tmp16_ = NULL;
			tag = (_tmp17_ = (_tmp16_ = gtk_text_buffer_create_tag ((GtkTextBuffer*) self->priv->_buffer, tag_name, NULL), (_tmp16_ == NULL) ? NULL : g_object_ref (_tmp16_)), (tag == NULL) ? NULL : (tag = (g_object_unref (tag), NULL)), _tmp17_);
			new_tag = TRUE;
		}
	}
	/* stdout.printf("      tag: '%s'\n", tag_name);*/
	if (setting != NULL) {
		gtk_mate_colourer_set_tag_properties (self, scope, tag, setting);
	}
	if (inner) {
		GtkTextTag* _tmp19_;
		GtkTextTag* _tmp18_;
		_tmp19_ = NULL;
		_tmp18_ = NULL;
		scope->inner_tag = (_tmp19_ = (_tmp18_ = tag, (_tmp18_ == NULL) ? NULL : g_object_ref (_tmp18_)), (scope->inner_tag == NULL) ? NULL : (scope->inner_tag = (g_object_unref (scope->inner_tag), NULL)), _tmp19_);
	} else {
		GtkTextTag* _tmp21_;
		GtkTextTag* _tmp20_;
		_tmp21_ = NULL;
		_tmp20_ = NULL;
		scope->tag = (_tmp21_ = (_tmp20_ = tag, (_tmp20_ == NULL) ? NULL : g_object_ref (_tmp20_)), (scope->tag == NULL) ? NULL : (scope->tag = (g_object_unref (scope->tag), NULL)), _tmp21_);
	}
	gtk_text_buffer_apply_tag ((GtkTextBuffer*) self->priv->_buffer, tag, &start_iter, &end_iter);
	if (new_tag) {
		gtk_mate_parser_added_tag (self->priv->_buffer->parser, tag);
	}
	(tag == NULL) ? NULL : (tag = (g_object_unref (tag), NULL));
	(setting == NULL) ? NULL : (setting = (g_object_unref (setting), NULL));
	(exclude_setting == NULL) ? NULL : (exclude_setting = (g_object_unref (exclude_setting), NULL));
	tag_name = (g_free (tag_name), NULL);
	(tag_table == NULL) ? NULL : (tag_table = (g_object_unref (tag_table), NULL));
}


void gtk_mate_colourer_set_tag_properties (GtkMateColourer* self, GtkMateScope* scope, GtkTextTag* tag, GtkMateThemeSetting* setting) {
	char* font_style;
	char* background;
	char* merged_bg_colour;
	char* parent_bg;
	gboolean _tmp2_;
	char* foreground;
	char* parent_fg;
	gboolean _tmp9_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	g_return_if_fail (tag != NULL);
	g_return_if_fail (setting != NULL);
	font_style = (char*) gee_map_get ((GeeMap*) setting->settings, "fontStyle");
	if (_vala_strcmp0 (font_style, "italic") == 0) {
		PangoStyle _tmp0_;
		g_object_set (tag, "style", PANGO_STYLE_ITALIC | (g_object_get (tag, "style", &_tmp0_, NULL), _tmp0_), NULL);
	} else {
		PangoStyle _tmp1_;
		g_object_set (tag, "style", PANGO_STYLE_NORMAL | (g_object_get (tag, "style", &_tmp1_, NULL), _tmp1_), NULL);
	}
	if (_vala_strcmp0 (font_style, "underline") == 0) {
		g_object_set (tag, "underline", PANGO_UNDERLINE_SINGLE, NULL);
	} else {
		g_object_set (tag, "underline", PANGO_UNDERLINE_NONE, NULL);
	}
	background = (char*) gee_map_get ((GeeMap*) setting->settings, "background");
	/*stdout.printf("        scope background:        %s\n", background);*/
	merged_bg_colour = NULL;
	parent_bg = (char*) gee_map_get ((GeeMap*) self->priv->_theme->global_settings, "background");
	_tmp2_ = FALSE;
	if (background != NULL) {
		_tmp2_ = _vala_strcmp0 (background, "") != 0;
	} else {
		_tmp2_ = FALSE;
	}
	/*stdout.printf("        global background: %s\n", parent_bg);
	 TODO: wasn't this a better way of creating the background colours?
	var parent_bg = scope.nearest_background_colour();
	if (parent_bg == null) {
	}
	else {
	stdout.printf("        parent background: %s\n", parent_bg);
	}*/
	if (_tmp2_) {
		char* _tmp3_;
		/*if (parent_bg != null) {
		merged_bg_colour = parent_bg;
		}
		else {*/
		_tmp3_ = NULL;
		merged_bg_colour = (_tmp3_ = gtk_mate_colourer_merge_colour (parent_bg, background), merged_bg_colour = (g_free (merged_bg_colour), NULL), _tmp3_);
		/*}*/
		if (merged_bg_colour != NULL) {
			char* _tmp5_;
			const char* _tmp4_;
			_tmp5_ = NULL;
			_tmp4_ = NULL;
			scope->bg_colour = (_tmp5_ = (_tmp4_ = merged_bg_colour, (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_)), scope->bg_colour = (g_free (scope->bg_colour), NULL), _tmp5_);
			g_object_set (tag, "background", merged_bg_colour, NULL);
		}
	} else {
		char* _tmp7_;
		const char* _tmp6_;
		/*stdout.printf("       tag.background = %s\n", merged_bg_colour);*/
		_tmp7_ = NULL;
		_tmp6_ = NULL;
		merged_bg_colour = (_tmp7_ = (_tmp6_ = parent_bg, (_tmp6_ == NULL) ? NULL : g_strdup (_tmp6_)), merged_bg_colour = (g_free (merged_bg_colour), NULL), _tmp7_);
	}
	/*stdout.printf("        merged_bg_colour:  %s\n", merged_bg_colour);*/
	foreground = (char*) gee_map_get ((GeeMap*) setting->settings, "foreground");
	/*stdout.printf("        scope foreground:        %s\n", foreground);*/
	parent_fg = gtk_mate_scope_nearest_foreground_colour (scope);
	if (parent_fg == NULL) {
		char* _tmp8_;
		_tmp8_ = NULL;
		parent_fg = (_tmp8_ = (char*) gee_map_get ((GeeMap*) self->priv->_theme->global_settings, "foreground"), parent_fg = (g_free (parent_fg), NULL), _tmp8_);
	}
	_tmp9_ = FALSE;
	if (foreground != NULL) {
		_tmp9_ = _vala_strcmp0 (foreground, "") != 0;
	} else {
		_tmp9_ = FALSE;
	}
	/*stdout.printf("        global foreground:        %s\n", parent_fg);*/
	if (_tmp9_) {
		char* merged_fg_colour;
		gboolean _tmp10_;
		merged_fg_colour = NULL;
		_tmp10_ = FALSE;
		if (parent_fg != NULL) {
			_tmp10_ = !scope->is_capture;
		} else {
			_tmp10_ = FALSE;
		}
		if (_tmp10_) {
			char* _tmp11_;
			_tmp11_ = NULL;
			merged_fg_colour = (_tmp11_ = gtk_mate_colourer_merge_colour (parent_fg, foreground), merged_fg_colour = (g_free (merged_fg_colour), NULL), _tmp11_);
		} else {
			char* _tmp13_;
			const char* _tmp12_;
			_tmp13_ = NULL;
			_tmp12_ = NULL;
			merged_fg_colour = (_tmp13_ = (_tmp12_ = foreground, (_tmp12_ == NULL) ? NULL : g_strdup (_tmp12_)), merged_fg_colour = (g_free (merged_fg_colour), NULL), _tmp13_);
		}
		if (merged_fg_colour != NULL) {
			char* _tmp15_;
			const char* _tmp14_;
			_tmp15_ = NULL;
			_tmp14_ = NULL;
			scope->fg_colour = (_tmp15_ = (_tmp14_ = merged_fg_colour, (_tmp14_ == NULL) ? NULL : g_strdup (_tmp14_)), scope->fg_colour = (g_free (scope->fg_colour), NULL), _tmp15_);
			g_object_set (tag, "foreground", merged_fg_colour, NULL);
		}
		merged_fg_colour = (g_free (merged_fg_colour), NULL);
	}
	font_style = (g_free (font_style), NULL);
	background = (g_free (background), NULL);
	merged_bg_colour = (g_free (merged_bg_colour), NULL);
	parent_bg = (g_free (parent_bg), NULL);
	foreground = (g_free (foreground), NULL);
	parent_fg = (g_free (parent_fg), NULL);
}


/*stdout.printf("       merged_fg_colour: %s\n", merged_fg_colour);
stdout.printf("\n");*/
gint gtk_mate_colourer_char_to_hex (gunichar ch) {
	if (g_unichar_isxdigit (ch)) {
		return g_unichar_xdigit_value (ch);
	}
	return 0;
}


gint gtk_mate_colourer_hex_to_int (gunichar ch1, gunichar ch2) {
	return (gtk_mate_colourer_char_to_hex (ch1) * 16) + gtk_mate_colourer_char_to_hex (ch2);
}


static glong string_get_length (const char* self) {
	g_return_val_if_fail (self != NULL, 0L);
	return g_utf8_strlen (self, -1);
}


/* Here parent_colour is like '#FFFFFF' and
 colour is like '#000000DD'.*/
char* gtk_mate_colourer_merge_colour (const char* parent_colour, const char* colour) {
	gint pre_r;
	gint pre_g;
	gint pre_b;
	gint post_r;
	gint post_g;
	gint post_b;
	gint opacity;
	gint new_r;
	gint new_g;
	gint new_b;
	char* new_colour;
	char* _tmp5_;
	g_return_val_if_fail (colour != NULL, NULL);
	pre_r = 0;
	pre_g = 0;
	pre_b = 0;
	post_r = 0;
	post_g = 0;
	post_b = 0;
	opacity = 0;
	new_r = 0;
	new_g = 0;
	new_b = 0;
	new_colour = NULL;
	if (parent_colour == NULL) {
		char* _tmp0_;
		_tmp0_ = NULL;
		return (_tmp0_ = NULL, new_colour = (g_free (new_colour), NULL), _tmp0_);
	}
	if (string_get_length (colour) == 7) {
		const char* _tmp1_;
		char* _tmp2_;
		_tmp1_ = NULL;
		_tmp2_ = NULL;
		return (_tmp2_ = (_tmp1_ = colour, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), new_colour = (g_free (new_colour), NULL), _tmp2_);
	}
	if (string_get_length (colour) == 9) {
		char* _tmp3_;
		pre_r = gtk_mate_colourer_hex_to_int (g_utf8_get_char (g_utf8_offset_to_pointer (parent_colour, 1)), g_utf8_get_char (g_utf8_offset_to_pointer (parent_colour, 2)));
		pre_g = gtk_mate_colourer_hex_to_int (g_utf8_get_char (g_utf8_offset_to_pointer (parent_colour, 3)), g_utf8_get_char (g_utf8_offset_to_pointer (parent_colour, 4)));
		pre_b = gtk_mate_colourer_hex_to_int (g_utf8_get_char (g_utf8_offset_to_pointer (parent_colour, 5)), g_utf8_get_char (g_utf8_offset_to_pointer (parent_colour, 6)));
		post_r = gtk_mate_colourer_hex_to_int (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 1)), g_utf8_get_char (g_utf8_offset_to_pointer (colour, 2)));
		post_g = gtk_mate_colourer_hex_to_int (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 3)), g_utf8_get_char (g_utf8_offset_to_pointer (colour, 4)));
		post_b = gtk_mate_colourer_hex_to_int (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 5)), g_utf8_get_char (g_utf8_offset_to_pointer (colour, 6)));
		opacity = gtk_mate_colourer_hex_to_int (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 7)), g_utf8_get_char (g_utf8_offset_to_pointer (colour, 8)));
		new_r = ((pre_r * (255 - opacity)) + (post_r * opacity)) / 255;
		new_g = ((pre_g * (255 - opacity)) + (post_g * opacity)) / 255;
		new_b = ((pre_b * (255 - opacity)) + (post_b * opacity)) / 255;
		_tmp3_ = NULL;
		new_colour = (_tmp3_ = g_strdup_printf ("#%.2x%.2x%.2x", (guint) new_r, (guint) new_g, (guint) new_b), new_colour = (g_free (new_colour), NULL), _tmp3_);
		/* stdout.printf("%s/%s/%s - %d,%d,%d\n", parent_colour, colour, new_colour, new_r, new_g, new_b);*/
		return new_colour;
	}
	_tmp5_ = NULL;
	return (_tmp5_ = g_strdup ("#000000"), new_colour = (g_free (new_colour), NULL), _tmp5_);
}


void gtk_mate_colourer_uncolour_scopes (GtkMateColourer* self, GeeArrayList* scopes) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (scopes != NULL);
	{
		GeeIterator* _scope_it;
		_scope_it = gee_iterable_iterator ((GeeIterable*) scopes);
		while (gee_iterator_next (_scope_it)) {
			GtkMateScope* scope;
			scope = (GtkMateScope*) gee_iterator_get (_scope_it);
			gtk_mate_colourer_uncolour_scope (self, scope, TRUE);
			(scope == NULL) ? NULL : (scope = (g_object_unref (scope), NULL));
		}
		(_scope_it == NULL) ? NULL : (_scope_it = (g_object_unref (_scope_it), NULL));
	}
}


void gtk_mate_colourer_uncolour_scope (GtkMateColourer* self, GtkMateScope* scope, gboolean recurse) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	/* stdout.printf("uncolour scope: %s\n", scope.name);*/
	if (scope->inner_tag != NULL) {
		GtkTextIter _tmp1_ = {0};
		GtkTextIter _tmp0_ = {0};
		gtk_text_buffer_remove_tag ((GtkTextBuffer*) self->priv->_buffer, scope->inner_tag, (_tmp0_ = gtk_mate_scope_inner_start_iter (scope), &_tmp0_), (_tmp1_ = gtk_mate_scope_inner_end_iter (scope), &_tmp1_));
	}
	if (scope->tag != NULL) {
		GtkTextIter _tmp3_ = {0};
		GtkTextIter _tmp2_ = {0};
		gtk_text_buffer_remove_tag ((GtkTextBuffer*) self->priv->_buffer, scope->tag, (_tmp2_ = gtk_mate_scope_start_iter (scope), &_tmp2_), (_tmp3_ = gtk_mate_scope_end_iter (scope), &_tmp3_));
	}
	gtk_mate_scope_set_is_coloured (scope, FALSE);
	if (recurse) {
		GSequenceIter* iter;
		iter = g_sequence_get_begin_iter (gtk_mate_scope_get_children (scope));
		while (!g_sequence_iter_is_end (iter)) {
			gtk_mate_colourer_uncolour_scope (self, (GtkMateScope*) g_sequence_get (iter), recurse);
			iter = g_sequence_iter_next (iter);
		}
	}
}


GtkMateBuffer* gtk_mate_colourer_get_buffer (GtkMateColourer* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_buffer;
}


void gtk_mate_colourer_set_buffer (GtkMateColourer* self, GtkMateBuffer* value) {
	GtkMateBuffer* _tmp2_;
	GtkMateBuffer* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_buffer = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->priv->_buffer == NULL) ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL)), _tmp2_);
	g_object_notify ((GObject *) self, "buffer");
}


GtkMateTheme* gtk_mate_colourer_get_theme (GtkMateColourer* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_theme;
}


void gtk_mate_colourer_set_theme (GtkMateColourer* self, GtkMateTheme* value) {
	GtkMateTheme* _tmp2_;
	GtkMateTheme* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_theme = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->priv->_theme == NULL) ? NULL : (self->priv->_theme = (g_object_unref (self->priv->_theme), NULL)), _tmp2_);
	g_object_notify ((GObject *) self, "theme");
}


static void gtk_mate_colourer_class_init (GtkMateColourerClass * klass) {
	gtk_mate_colourer_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GtkMateColourerPrivate));
	G_OBJECT_CLASS (klass)->get_property = gtk_mate_colourer_get_property;
	G_OBJECT_CLASS (klass)->set_property = gtk_mate_colourer_set_property;
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_colourer_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_COLOURER_BUFFER, g_param_spec_object ("buffer", "buffer", "buffer", GTK_MATE_TYPE_BUFFER, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_COLOURER_THEME, g_param_spec_object ("theme", "theme", "theme", GTK_MATE_TYPE_THEME, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void gtk_mate_colourer_instance_init (GtkMateColourer * self) {
	self->priv = GTK_MATE_COLOURER_GET_PRIVATE (self);
}


static void gtk_mate_colourer_finalize (GObject* obj) {
	GtkMateColourer * self;
	self = GTK_MATE_COLOURER (obj);
	(self->priv->_buffer == NULL) ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL));
	(self->priv->_theme == NULL) ? NULL : (self->priv->_theme = (g_object_unref (self->priv->_theme), NULL));
	G_OBJECT_CLASS (gtk_mate_colourer_parent_class)->finalize (obj);
}


GType gtk_mate_colourer_get_type (void) {
	static GType gtk_mate_colourer_type_id = 0;
	if (gtk_mate_colourer_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateColourerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_colourer_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateColourer), 0, (GInstanceInitFunc) gtk_mate_colourer_instance_init, NULL };
		gtk_mate_colourer_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateColourer", &g_define_type_info, 0);
	}
	return gtk_mate_colourer_type_id;
}


static void gtk_mate_colourer_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateColourer * self;
	gpointer boxed;
	self = GTK_MATE_COLOURER (object);
	switch (property_id) {
		case GTK_MATE_COLOURER_BUFFER:
		g_value_set_object (value, gtk_mate_colourer_get_buffer (self));
		break;
		case GTK_MATE_COLOURER_THEME:
		g_value_set_object (value, gtk_mate_colourer_get_theme (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_colourer_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GtkMateColourer * self;
	self = GTK_MATE_COLOURER (object);
	switch (property_id) {
		case GTK_MATE_COLOURER_BUFFER:
		gtk_mate_colourer_set_buffer (self, g_value_get_object (value));
		break;
		case GTK_MATE_COLOURER_THEME:
		gtk_mate_colourer_set_theme (self, g_value_get_object (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
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




