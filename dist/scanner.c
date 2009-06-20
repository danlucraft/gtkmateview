
#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <gee/iterable.h>
#include <gee/arraylist.h>
#include <stdlib.h>
#include <string.h>
#include <gee/iterator.h>
#include <gee/collection.h>
#include <gee/list.h>
#include <gee/hashmap.h>


#define GTK_MATE_TYPE_MARKER (gtk_mate_marker_get_type ())
#define GTK_MATE_MARKER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_MARKER, GtkMateMarker))
#define GTK_MATE_MARKER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_MARKER, GtkMateMarkerClass))
#define GTK_MATE_IS_MARKER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_MARKER))
#define GTK_MATE_IS_MARKER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_MARKER))
#define GTK_MATE_MARKER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_MARKER, GtkMateMarkerClass))

typedef struct _GtkMateMarker GtkMateMarker;
typedef struct _GtkMateMarkerClass GtkMateMarkerClass;
typedef struct _GtkMateMarkerPrivate GtkMateMarkerPrivate;

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

#define GTK_MATE_TYPE_SCANNER (gtk_mate_scanner_get_type ())
#define GTK_MATE_SCANNER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SCANNER, GtkMateScanner))
#define GTK_MATE_SCANNER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SCANNER, GtkMateScannerClass))
#define GTK_MATE_IS_SCANNER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SCANNER))
#define GTK_MATE_IS_SCANNER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SCANNER))
#define GTK_MATE_SCANNER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SCANNER, GtkMateScannerClass))

typedef struct _GtkMateScanner GtkMateScanner;
typedef struct _GtkMateScannerClass GtkMateScannerClass;
typedef struct _GtkMateScannerPrivate GtkMateScannerPrivate;

#define GTK_MATE_TYPE_SCOPE (gtk_mate_scope_get_type ())
#define GTK_MATE_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SCOPE, GtkMateScope))
#define GTK_MATE_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SCOPE, GtkMateScopeClass))
#define GTK_MATE_IS_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SCOPE))
#define GTK_MATE_IS_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SCOPE))
#define GTK_MATE_SCOPE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SCOPE, GtkMateScopeClass))

typedef struct _GtkMateScope GtkMateScope;
typedef struct _GtkMateScopeClass GtkMateScopeClass;

#define GTK_MATE_SCANNER_TYPE_ITERATOR (gtk_mate_scanner_iterator_get_type ())
#define GTK_MATE_SCANNER_ITERATOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_SCANNER_TYPE_ITERATOR, GtkMateScannerIterator))
#define GTK_MATE_SCANNER_ITERATOR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_SCANNER_TYPE_ITERATOR, GtkMateScannerIteratorClass))
#define GTK_MATE_SCANNER_IS_ITERATOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_SCANNER_TYPE_ITERATOR))
#define GTK_MATE_SCANNER_IS_ITERATOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_SCANNER_TYPE_ITERATOR))
#define GTK_MATE_SCANNER_ITERATOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_SCANNER_TYPE_ITERATOR, GtkMateScannerIteratorClass))

typedef struct _GtkMateScannerIterator GtkMateScannerIterator;
typedef struct _GtkMateScannerIteratorClass GtkMateScannerIteratorClass;

#define GTK_MATE_TYPE_SINGLE_PATTERN (gtk_mate_single_pattern_get_type ())
#define GTK_MATE_SINGLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePattern))
#define GTK_MATE_SINGLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePatternClass))
#define GTK_MATE_IS_SINGLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SINGLE_PATTERN))
#define GTK_MATE_IS_SINGLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SINGLE_PATTERN))
#define GTK_MATE_SINGLE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePatternClass))

typedef struct _GtkMateSinglePattern GtkMateSinglePattern;
typedef struct _GtkMateSinglePatternClass GtkMateSinglePatternClass;
typedef struct _GtkMatePatternPrivate GtkMatePatternPrivate;
typedef struct _GtkMateSinglePatternPrivate GtkMateSinglePatternPrivate;

#define ONIG_TYPE_RX (onig_rx_get_type ())
#define ONIG_RX(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIG_TYPE_RX, OnigRx))
#define ONIG_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIG_TYPE_RX, OnigRxClass))
#define ONIG_IS_RX(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIG_TYPE_RX))
#define ONIG_IS_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIG_TYPE_RX))
#define ONIG_RX_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIG_TYPE_RX, OnigRxClass))

typedef struct _OnigRx OnigRx;
typedef struct _OnigRxClass OnigRxClass;

#define GTK_MATE_TYPE_DOUBLE_PATTERN (gtk_mate_double_pattern_get_type ())
#define GTK_MATE_DOUBLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePattern))
#define GTK_MATE_DOUBLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePatternClass))
#define GTK_MATE_IS_DOUBLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN))
#define GTK_MATE_IS_DOUBLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_DOUBLE_PATTERN))
#define GTK_MATE_DOUBLE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePatternClass))

typedef struct _GtkMateDoublePattern GtkMateDoublePattern;
typedef struct _GtkMateDoublePatternClass GtkMateDoublePatternClass;
typedef struct _GtkMateDoublePatternPrivate GtkMateDoublePatternPrivate;
typedef struct _GtkMateScopePrivate GtkMateScopePrivate;

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
typedef struct _GtkMateScannerIteratorPrivate GtkMateScannerIteratorPrivate;

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

struct _GtkMateScannerPrivate {
	GtkMateScope* _current_scope;
	char* _line;
	gint _line_length;
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

struct _GtkMateSinglePattern {
	GtkMatePattern parent_instance;
	GtkMateSinglePatternPrivate * priv;
	OnigRx* match;
	GeeHashMap* captures;
};

struct _GtkMateSinglePatternClass {
	GtkMatePatternClass parent_class;
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

struct _GtkMateScannerIterator {
	GtkObject parent_instance;
	GtkMateScannerIteratorPrivate * priv;
	gpointer next_marker;
};

struct _GtkMateScannerIteratorClass {
	GtkObjectClass parent_class;
};

struct _GtkMateScannerIteratorPrivate {
	GType marker_type;
	GBoxedCopyFunc marker_dup_func;
	GDestroyNotify marker_destroy_func;
	GtkMateScanner* _scanner;
};



GType gtk_mate_marker_get_type (void);
GType gtk_mate_pattern_get_type (void);
GType onig_match_get_type (void);
enum  {
	GTK_MATE_MARKER_DUMMY_PROPERTY
};
GtkMateMarker* gtk_mate_marker_new (void);
GtkMateMarker* gtk_mate_marker_construct (GType object_type);
GtkMateMarker* gtk_mate_marker_new (void);
static gpointer gtk_mate_marker_parent_class = NULL;
static void gtk_mate_marker_finalize (GObject* obj);
GType gtk_mate_scanner_get_type (void);
GType gtk_mate_scope_get_type (void);
#define GTK_MATE_SCANNER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_TYPE_SCANNER, GtkMateScannerPrivate))
enum  {
	GTK_MATE_SCANNER_DUMMY_PROPERTY,
	GTK_MATE_SCANNER_CURRENT_SCOPE,
	GTK_MATE_SCANNER_LINE,
	GTK_MATE_SCANNER_LINE_LENGTH
};
void gtk_mate_scanner_set_current_scope (GtkMateScanner* self, GtkMateScope* value);
void gtk_mate_scanner_set_line (GtkMateScanner* self, const char* value);
void gtk_mate_scanner_set_line_length (GtkMateScanner* self, gint value);
GtkMateScanner* gtk_mate_scanner_new (GtkMateScope* s, const char* line, gint line_length);
GtkMateScanner* gtk_mate_scanner_construct (GType object_type, GtkMateScope* s, const char* line, gint line_length);
GtkMateScanner* gtk_mate_scanner_new (GtkMateScope* s, const char* line, gint line_length);
static GType gtk_mate_scanner_real_get_element_type (GeeIterable* base);
GtkMateScannerIterator* gtk_mate_scanner_iterator_new (GType marker_type, GBoxedCopyFunc marker_dup_func, GDestroyNotify marker_destroy_func, GtkMateScanner* s);
GtkMateScannerIterator* gtk_mate_scanner_iterator_construct (GType object_type, GType marker_type, GBoxedCopyFunc marker_dup_func, GDestroyNotify marker_destroy_func, GtkMateScanner* s);
GType gtk_mate_scanner_iterator_get_type (void);
static GeeIterator* gtk_mate_scanner_real_iterator (GeeIterable* base);
gint onig_match_end (OnigMatch* self, gint capture);
GtkMateMarker* gtk_mate_scanner_get_cached_marker (GtkMateScanner* self);
void gtk_mate_scanner_remove_preceding_cached_markers (GtkMateScanner* self, GtkMateMarker* m);
GType gtk_mate_single_pattern_get_type (void);
GType onig_rx_get_type (void);
OnigMatch* onig_rx_search (OnigRx* self, const char* target, gint start, gint end);
const char* gtk_mate_scanner_get_line (GtkMateScanner* self);
gint gtk_mate_scanner_get_line_length (GtkMateScanner* self);
GType gtk_mate_double_pattern_get_type (void);
OnigMatch* gtk_mate_scanner_scan_for_match (GtkMateScanner* self, gint from, GtkMatePattern* p);
GtkMateScope* gtk_mate_scanner_get_current_scope (GtkMateScanner* self);
GType gtk_mate_text_loc_get_type (void);
GType gtk_mate_theme_setting_get_type (void);
gint onig_match_begin (OnigMatch* self, gint capture);
GtkMateMarker* gtk_mate_scanner_find_next_marker (GtkMateScanner* self);
static void gtk_mate_scanner_updated_current_scope (GtkMateScanner* self);
static GObject * gtk_mate_scanner_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
#define GTK_MATE_SCANNER_ITERATOR_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_SCANNER_TYPE_ITERATOR, GtkMateScannerIteratorPrivate))
enum  {
	GTK_MATE_SCANNER_ITERATOR_DUMMY_PROPERTY,
	GTK_MATE_SCANNER_ITERATOR_SCANNER,
	GTK_MATE_SCANNER_ITERATOR_MARKER_TYPE,
	GTK_MATE_SCANNER_ITERATOR_MARKER_DUP_FUNC,
	GTK_MATE_SCANNER_ITERATOR_MARKER_DESTROY_FUNC
};
void gtk_mate_scanner_iterator_set_scanner (GtkMateScannerIterator* self, GtkMateScanner* value);
GtkMateScannerIterator* gtk_mate_scanner_iterator_new (GType marker_type, GBoxedCopyFunc marker_dup_func, GDestroyNotify marker_destroy_func, GtkMateScanner* s);
GtkMateScanner* gtk_mate_scanner_iterator_get_scanner (GtkMateScannerIterator* self);
static gboolean gtk_mate_scanner_iterator_real_next (GeeIterator* base);
static gpointer gtk_mate_scanner_iterator_real_get (GeeIterator* base);
static GObject * gtk_mate_scanner_iterator_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer gtk_mate_scanner_iterator_parent_class = NULL;
static GeeIteratorIface* gtk_mate_scanner_iterator_gee_iterator_parent_iface = NULL;
static void gtk_mate_scanner_iterator_finalize (GObject* obj);
static void gtk_mate_scanner_iterator_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void gtk_mate_scanner_iterator_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
static gpointer gtk_mate_scanner_parent_class = NULL;
static GeeIterableIface* gtk_mate_scanner_gee_iterable_parent_iface = NULL;
static void gtk_mate_scanner_finalize (GObject* obj);
static void gtk_mate_scanner_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void gtk_mate_scanner_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);



/* The Scanner returns these to indicate successful pattern matches in a line.*/
GtkMateMarker* gtk_mate_marker_construct (GType object_type) {
	GtkMateMarker * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


GtkMateMarker* gtk_mate_marker_new (void) {
	return gtk_mate_marker_construct (GTK_MATE_TYPE_MARKER);
}


static void gtk_mate_marker_class_init (GtkMateMarkerClass * klass) {
	gtk_mate_marker_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_marker_finalize;
}


static void gtk_mate_marker_instance_init (GtkMateMarker * self) {
}


static void gtk_mate_marker_finalize (GObject* obj) {
	GtkMateMarker * self;
	self = GTK_MATE_MARKER (obj);
	(self->pattern == NULL) ? NULL : (self->pattern = (g_object_unref (self->pattern), NULL));
	(self->match == NULL) ? NULL : (self->match = (g_object_unref (self->match), NULL));
	G_OBJECT_CLASS (gtk_mate_marker_parent_class)->finalize (obj);
}


GType gtk_mate_marker_get_type (void) {
	static GType gtk_mate_marker_type_id = 0;
	if (gtk_mate_marker_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateMarkerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_marker_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateMarker), 0, (GInstanceInitFunc) gtk_mate_marker_instance_init, NULL };
		gtk_mate_marker_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateMarker", &g_define_type_info, 0);
	}
	return gtk_mate_marker_type_id;
}


GtkMateScanner* gtk_mate_scanner_construct (GType object_type, GtkMateScope* s, const char* line, gint line_length) {
	GtkMateScanner * self;
	g_return_val_if_fail (s != NULL, NULL);
	g_return_val_if_fail (line != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	gtk_mate_scanner_set_current_scope (self, s);
	gtk_mate_scanner_set_line (self, line);
	gtk_mate_scanner_set_line_length (self, line_length);
	return self;
}


GtkMateScanner* gtk_mate_scanner_new (GtkMateScope* s, const char* line, gint line_length) {
	return gtk_mate_scanner_construct (GTK_MATE_TYPE_SCANNER, s, line, line_length);
}


static GType gtk_mate_scanner_real_get_element_type (GeeIterable* base) {
	GtkMateScanner * self;
	self = (GtkMateScanner*) base;
	return GTK_MATE_TYPE_MARKER;
}


static GeeIterator* gtk_mate_scanner_real_iterator (GeeIterable* base) {
	GtkMateScanner * self;
	self = (GtkMateScanner*) base;
	return (GeeIterator*) g_object_ref_sink (gtk_mate_scanner_iterator_new (GTK_MATE_TYPE_MARKER, (GBoxedCopyFunc) g_object_ref, g_object_unref, self));
}


/* if we have already scanned this line for this scope then
 simply return the next cached marker (choosing the longest
 match in case of a tie).*/
GtkMateMarker* gtk_mate_scanner_get_cached_marker (GtkMateScanner* self) {
	GtkMateMarker* m;
	gint best_length;
	gint new_length;
	g_return_val_if_fail (self != NULL, NULL);
	m = NULL;
	best_length = 0;
	new_length = 0;
	{
		GeeIterator* _m1_it;
		_m1_it = gee_iterable_iterator ((GeeIterable*) self->cached_markers);
		while (gee_iterator_next (_m1_it)) {
			GtkMateMarker* m1;
			gboolean _tmp0_;
			gboolean _tmp1_;
			gboolean _tmp2_;
			m1 = (GtkMateMarker*) gee_iterator_get (_m1_it);
			new_length = onig_match_end (m1->match, 0) - m1->from;
			_tmp0_ = FALSE;
			_tmp1_ = FALSE;
			_tmp2_ = FALSE;
			if (m == NULL) {
				_tmp2_ = TRUE;
			} else {
				_tmp2_ = m1->from < m->from;
			}
			if (_tmp2_) {
				_tmp1_ = TRUE;
			} else {
				gboolean _tmp3_;
				_tmp3_ = FALSE;
				if (m1->from == m->from) {
					_tmp3_ = new_length > best_length;
				} else {
					_tmp3_ = FALSE;
				}
				_tmp1_ = _tmp3_;
			}
			if (_tmp1_) {
				_tmp0_ = TRUE;
			} else {
				gboolean _tmp4_;
				gboolean _tmp5_;
				_tmp4_ = FALSE;
				_tmp5_ = FALSE;
				if (m1->from == m->from) {
					_tmp5_ = new_length == best_length;
				} else {
					_tmp5_ = FALSE;
				}
				if (_tmp5_) {
					_tmp4_ = m1->is_close_scope;
				} else {
					_tmp4_ = FALSE;
				}
				_tmp0_ = _tmp4_;
			}
			if (_tmp0_) {
				GtkMateMarker* _tmp7_;
				GtkMateMarker* _tmp6_;
				_tmp7_ = NULL;
				_tmp6_ = NULL;
				m = (_tmp7_ = (_tmp6_ = m1, (_tmp6_ == NULL) ? NULL : g_object_ref (_tmp6_)), (m == NULL) ? NULL : (m = (g_object_unref (m), NULL)), _tmp7_);
				best_length = new_length;
			}
			(m1 == NULL) ? NULL : (m1 = (g_object_unref (m1), NULL));
		}
		(_m1_it == NULL) ? NULL : (_m1_it = (g_object_unref (_m1_it), NULL));
	}
	return m;
}


/* if we have gone beyond the marker, toss it out.*/
void gtk_mate_scanner_remove_preceding_cached_markers (GtkMateScanner* self, GtkMateMarker* m) {
	gint ix;
	gint len;
	g_return_if_fail (self != NULL);
	g_return_if_fail (m != NULL);
	ix = 0;
	len = gee_collection_get_size ((GeeCollection*) self->cached_markers);
	{
		gint i;
		/*stdout.printf("num cached: %d\n", len);*/
		i = 0;
		for (; i < len; i++, ix++) {
			GtkMateMarker* _tmp0_;
			gboolean _tmp1_;
			_tmp0_ = NULL;
			if ((_tmp1_ = (_tmp0_ = (GtkMateMarker*) gee_list_get ((GeeList*) self->cached_markers, ix))->from < onig_match_end (m->match, 0), (_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_object_unref (_tmp0_), NULL)), _tmp1_)) {
				gee_list_remove_at ((GeeList*) self->cached_markers, ix);
				ix--;
			}
		}
	}
}


/*stdout.printf("num cached after removals: %d\n", cached_markers.size);*/
OnigMatch* gtk_mate_scanner_scan_for_match (GtkMateScanner* self, gint from, GtkMatePattern* p) {
	OnigMatch* match;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (p != NULL, NULL);
	match = NULL;
	if (GTK_MATE_IS_SINGLE_PATTERN (p)) {
		GtkMateSinglePattern* _tmp0_;
		GtkMateSinglePattern* sp;
		OnigMatch* _tmp1_;
		_tmp0_ = NULL;
		sp = (_tmp0_ = GTK_MATE_SINGLE_PATTERN (p), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
		_tmp1_ = NULL;
		match = (_tmp1_ = onig_rx_search (sp->match, self->priv->_line, from, self->priv->_line_length), (match == NULL) ? NULL : (match = (g_object_unref (match), NULL)), _tmp1_);
		(sp == NULL) ? NULL : (sp = (g_object_unref (sp), NULL));
	} else {
		if (GTK_MATE_IS_DOUBLE_PATTERN (p)) {
			OnigMatch* _tmp2_;
			_tmp2_ = NULL;
			match = (_tmp2_ = onig_rx_search (GTK_MATE_DOUBLE_PATTERN (p)->begin, self->priv->_line, from, self->priv->_line_length), (match == NULL) ? NULL : (match = (g_object_unref (match), NULL)), _tmp2_);
		}
	}
	return match;
}


GtkMateMarker* gtk_mate_scanner_find_next_marker (GtkMateScanner* self) {
	GtkMateMarker* m;
	gint best_length;
	gint new_length;
	gboolean is_close_match;
	GtkMateMarker* _tmp0_;
	OnigRx* _tmp2_;
	OnigRx* closing_regex;
	GtkMateMarker* _tmp21_;
	g_return_val_if_fail (self != NULL, NULL);
	/* stdout.printf("find_next_marker (current_scope is %s)\n", current_scope.name);
	 stdout.printf("scanning: '%s' from %d to %d\n", line, position, line_length);*/
	m = NULL;
	best_length = 0;
	new_length = 0;
	is_close_match = FALSE;
	_tmp0_ = NULL;
	if ((m = (_tmp0_ = gtk_mate_scanner_get_cached_marker (self), (m == NULL) ? NULL : (m = (g_object_unref (m), NULL)), _tmp0_)) != NULL) {
		/*stdout.printf("got cached marker\n");*/
		gee_collection_remove ((GeeCollection*) self->cached_markers, m);
		gtk_mate_scanner_remove_preceding_cached_markers (self, m);
		return m;
	}
	/*stdout.printf("no cached marker\n");*/
	g_assert (gee_collection_get_size ((GeeCollection*) self->cached_markers) == 0);
	_tmp2_ = NULL;
	closing_regex = (_tmp2_ = gtk_mate_scanner_get_current_scope (self)->closing_regex, (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_));
	if (closing_regex != NULL) {
		OnigMatch* match;
		match = onig_rx_search (closing_regex, self->priv->_line, self->position, self->priv->_line_length);
		if (match != NULL) {
			GtkMateMarker* nm;
			GtkMatePattern* _tmp4_;
			GtkMatePattern* _tmp3_;
			OnigMatch* _tmp6_;
			OnigMatch* _tmp5_;
			GtkMateMarker* _tmp8_;
			GtkMateMarker* _tmp7_;
			/* stdout.printf("closing match: %s (%d-%d)\n", current_scope.name, match.begin(0), match.end(0));*/
			nm = g_object_ref_sink (gtk_mate_marker_new ());
			_tmp4_ = NULL;
			_tmp3_ = NULL;
			nm->pattern = (_tmp4_ = (_tmp3_ = gtk_mate_scanner_get_current_scope (self)->pattern, (_tmp3_ == NULL) ? NULL : g_object_ref (_tmp3_)), (nm->pattern == NULL) ? NULL : (nm->pattern = (g_object_unref (nm->pattern), NULL)), _tmp4_);
			_tmp6_ = NULL;
			_tmp5_ = NULL;
			nm->match = (_tmp6_ = (_tmp5_ = match, (_tmp5_ == NULL) ? NULL : g_object_ref (_tmp5_)), (nm->match == NULL) ? NULL : (nm->match = (g_object_unref (nm->match), NULL)), _tmp6_);
			nm->from = onig_match_begin (match, 0);
			nm->is_close_scope = TRUE;
			gee_collection_add ((GeeCollection*) self->cached_markers, nm);
			_tmp8_ = NULL;
			_tmp7_ = NULL;
			m = (_tmp8_ = (_tmp7_ = nm, (_tmp7_ == NULL) ? NULL : g_object_ref (_tmp7_)), (m == NULL) ? NULL : (m = (g_object_unref (m), NULL)), _tmp8_);
			best_length = onig_match_end (nm->match, 0) - nm->from;
			is_close_match = TRUE;
			(nm == NULL) ? NULL : (nm = (g_object_unref (nm), NULL));
		}
		(match == NULL) ? NULL : (match = (g_object_unref (match), NULL));
	}
	{
		GeeIterator* _p_it;
		_p_it = gee_iterable_iterator ((GeeIterable*) GTK_MATE_DOUBLE_PATTERN (gtk_mate_scanner_get_current_scope (self)->pattern)->patterns);
		while (gee_iterator_next (_p_it)) {
			GtkMatePattern* p;
			gint position_now;
			gint position_prev;
			OnigMatch* match;
			p = (GtkMatePattern*) gee_iterator_get (_p_it);
			if (p->disabled) {
				(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
				continue;
			}
			position_now = self->position;
			position_prev = self->position - 1;
			match = NULL;
			while (TRUE) {
				gboolean _tmp9_;
				OnigMatch* _tmp10_;
				GtkMateMarker* nm;
				GtkMatePattern* _tmp12_;
				GtkMatePattern* _tmp11_;
				OnigMatch* _tmp14_;
				OnigMatch* _tmp13_;
				gboolean _tmp15_;
				gboolean _tmp16_;
				_tmp9_ = FALSE;
				_tmp10_ = NULL;
				if ((match = (_tmp10_ = gtk_mate_scanner_scan_for_match (self, position_now, p), (match == NULL) ? NULL : (match = (g_object_unref (match), NULL)), _tmp10_)) != NULL) {
					_tmp9_ = position_now != position_prev;
				} else {
					_tmp9_ = FALSE;
				}
				if (!_tmp9_) {
					break;
				}
				/* some regex's have zero width (meta.selector.css)*/
				position_prev = position_now;
				/* stdout.printf("matched: %s (%d-%d)\n", p.name, match.begin(0), match.end(0));*/
				nm = g_object_ref_sink (gtk_mate_marker_new ());
				_tmp12_ = NULL;
				_tmp11_ = NULL;
				nm->pattern = (_tmp12_ = (_tmp11_ = p, (_tmp11_ == NULL) ? NULL : g_object_ref (_tmp11_)), (nm->pattern == NULL) ? NULL : (nm->pattern = (g_object_unref (nm->pattern), NULL)), _tmp12_);
				_tmp14_ = NULL;
				_tmp13_ = NULL;
				nm->match = (_tmp14_ = (_tmp13_ = match, (_tmp13_ == NULL) ? NULL : g_object_ref (_tmp13_)), (nm->match == NULL) ? NULL : (nm->match = (g_object_unref (nm->match), NULL)), _tmp14_);
				nm->from = onig_match_begin (match, 0);
				nm->is_close_scope = FALSE;
				gee_collection_add ((GeeCollection*) self->cached_markers, nm);
				new_length = onig_match_end (nm->match, 0) - nm->from;
				_tmp15_ = FALSE;
				_tmp16_ = FALSE;
				if (m == NULL) {
					_tmp16_ = TRUE;
				} else {
					_tmp16_ = nm->from < m->from;
				}
				if (_tmp16_) {
					_tmp15_ = TRUE;
				} else {
					gboolean _tmp17_;
					gboolean _tmp18_;
					_tmp17_ = FALSE;
					_tmp18_ = FALSE;
					if (nm->from == m->from) {
						_tmp18_ = new_length > best_length;
					} else {
						_tmp18_ = FALSE;
					}
					if (_tmp18_) {
						_tmp17_ = !is_close_match;
					} else {
						_tmp17_ = FALSE;
					}
					_tmp15_ = _tmp17_;
				}
				if (_tmp15_) {
					GtkMateMarker* _tmp20_;
					GtkMateMarker* _tmp19_;
					_tmp20_ = NULL;
					_tmp19_ = NULL;
					m = (_tmp20_ = (_tmp19_ = nm, (_tmp19_ == NULL) ? NULL : g_object_ref (_tmp19_)), (m == NULL) ? NULL : (m = (g_object_unref (m), NULL)), _tmp20_);
					best_length = new_length;
				}
				position_now = onig_match_end (match, 0);
				(nm == NULL) ? NULL : (nm = (g_object_unref (nm), NULL));
			}
			(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
			(match == NULL) ? NULL : (match = (g_object_unref (match), NULL));
		}
		(_p_it == NULL) ? NULL : (_p_it = (g_object_unref (_p_it), NULL));
	}
	/* stdout.printf("  new position: %d\n", position_now);*/
	if (m != NULL) {
		gee_collection_remove ((GeeCollection*) self->cached_markers, m);
		gtk_mate_scanner_remove_preceding_cached_markers (self, m);
	}
	_tmp21_ = NULL;
	return (_tmp21_ = m, (closing_regex == NULL) ? NULL : (closing_regex = (g_object_unref (closing_regex), NULL)), _tmp21_);
}


/* called when the current_scope property is set.*/
static void gtk_mate_scanner_updated_current_scope (GtkMateScanner* self) {
	g_return_if_fail (self != NULL);
	/* clear markers cached for this scope: 
	 (optimization potential: keep them for each scope in a hashmap)
	 (optimization potential: be aware of when a subscope can contain
	  all the parents scopes, so we don't need to clear.)*/
	gee_collection_clear ((GeeCollection*) self->cached_markers);
}


GtkMateScope* gtk_mate_scanner_get_current_scope (GtkMateScanner* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_current_scope;
}


void gtk_mate_scanner_set_current_scope (GtkMateScanner* self, GtkMateScope* value) {
	GtkMateScope* _tmp2_;
	GtkMateScope* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_current_scope = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->priv->_current_scope == NULL) ? NULL : (self->priv->_current_scope = (g_object_unref (self->priv->_current_scope), NULL)), _tmp2_);
	gtk_mate_scanner_updated_current_scope (self);
	g_object_notify ((GObject *) self, "current-scope");
}


const char* gtk_mate_scanner_get_line (GtkMateScanner* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_line;
}


void gtk_mate_scanner_set_line (GtkMateScanner* self, const char* value) {
	char* _tmp2_;
	const char* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_line = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), self->priv->_line = (g_free (self->priv->_line), NULL), _tmp2_);
	g_object_notify ((GObject *) self, "line");
}


gint gtk_mate_scanner_get_line_length (GtkMateScanner* self) {
	g_return_val_if_fail (self != NULL, 0);
	return self->priv->_line_length;
}


void gtk_mate_scanner_set_line_length (GtkMateScanner* self, gint value) {
	g_return_if_fail (self != NULL);
	self->priv->_line_length = value;
	g_object_notify ((GObject *) self, "line-length");
}


static GObject * gtk_mate_scanner_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GtkMateScannerClass * klass;
	GObjectClass * parent_class;
	GtkMateScanner * self;
	klass = GTK_MATE_SCANNER_CLASS (g_type_class_peek (GTK_MATE_TYPE_SCANNER));
	parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = GTK_MATE_SCANNER (obj);
	{
		GeeArrayList* _tmp0_;
		self->position = 0;
		_tmp0_ = NULL;
		self->cached_markers = (_tmp0_ = gee_array_list_new (GTK_MATE_TYPE_MARKER, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->cached_markers == NULL) ? NULL : (self->cached_markers = (g_object_unref (self->cached_markers), NULL)), _tmp0_);
	}
	return obj;
}


GtkMateScannerIterator* gtk_mate_scanner_iterator_construct (GType object_type, GType marker_type, GBoxedCopyFunc marker_dup_func, GDestroyNotify marker_destroy_func, GtkMateScanner* s) {
	GParameter * __params;
	GParameter * __params_it;
	GtkMateScannerIterator * self;
	g_return_val_if_fail (s != NULL, NULL);
	__params = g_new0 (GParameter, 4);
	__params_it = __params;
	__params_it->name = "marker-type";
	g_value_init (&__params_it->value, G_TYPE_GTYPE);
	g_value_set_gtype (&__params_it->value, marker_type);
	__params_it++;
	__params_it->name = "marker-dup-func";
	g_value_init (&__params_it->value, G_TYPE_POINTER);
	g_value_set_pointer (&__params_it->value, marker_dup_func);
	__params_it++;
	__params_it->name = "marker-destroy-func";
	g_value_init (&__params_it->value, G_TYPE_POINTER);
	g_value_set_pointer (&__params_it->value, marker_destroy_func);
	__params_it++;
	__params_it->name = "scanner";
	g_value_init (&__params_it->value, GTK_MATE_TYPE_SCANNER);
	g_value_set_object (&__params_it->value, s);
	__params_it++;
	self = g_object_newv (object_type, __params_it - __params, __params);
	while (__params_it > __params) {
		--__params_it;
		g_value_unset (&__params_it->value);
	}
	g_free (__params);
	return self;
}


GtkMateScannerIterator* gtk_mate_scanner_iterator_new (GType marker_type, GBoxedCopyFunc marker_dup_func, GDestroyNotify marker_destroy_func, GtkMateScanner* s) {
	return gtk_mate_scanner_iterator_construct (GTK_MATE_SCANNER_TYPE_ITERATOR, marker_type, marker_dup_func, marker_destroy_func, s);
}


static gboolean gtk_mate_scanner_iterator_real_next (GeeIterator* base) {
	GtkMateScannerIterator * self;
	gpointer _tmp0_;
	self = (GtkMateScannerIterator*) base;
	_tmp0_ = NULL;
	self->next_marker = (_tmp0_ = gtk_mate_scanner_find_next_marker (self->priv->_scanner), ((self->next_marker == NULL) || (self->priv->marker_destroy_func == NULL)) ? NULL : (self->next_marker = (self->priv->marker_destroy_func (self->next_marker), NULL)), _tmp0_);
	return self->next_marker != NULL;
}


static gpointer gtk_mate_scanner_iterator_real_get (GeeIterator* base) {
	GtkMateScannerIterator * self;
	gconstpointer _tmp0_;
	self = (GtkMateScannerIterator*) base;
	_tmp0_ = NULL;
	return (_tmp0_ = self->next_marker, ((_tmp0_ == NULL) || (self->priv->marker_dup_func == NULL)) ? ((gpointer) _tmp0_) : self->priv->marker_dup_func ((gpointer) _tmp0_));
}


GtkMateScanner* gtk_mate_scanner_iterator_get_scanner (GtkMateScannerIterator* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_scanner;
}


void gtk_mate_scanner_iterator_set_scanner (GtkMateScannerIterator* self, GtkMateScanner* value) {
	GtkMateScanner* _tmp2_;
	GtkMateScanner* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_scanner = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->priv->_scanner == NULL) ? NULL : (self->priv->_scanner = (g_object_unref (self->priv->_scanner), NULL)), _tmp2_);
	g_object_notify ((GObject *) self, "scanner");
}


static GObject * gtk_mate_scanner_iterator_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GtkMateScannerIteratorClass * klass;
	GObjectClass * parent_class;
	GtkMateScannerIterator * self;
	klass = GTK_MATE_SCANNER_ITERATOR_CLASS (g_type_class_peek (GTK_MATE_SCANNER_TYPE_ITERATOR));
	parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = GTK_MATE_SCANNER_ITERATOR (obj);
	{
	}
	return obj;
}


static void gtk_mate_scanner_iterator_class_init (GtkMateScannerIteratorClass * klass) {
	gtk_mate_scanner_iterator_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GtkMateScannerIteratorPrivate));
	G_OBJECT_CLASS (klass)->get_property = gtk_mate_scanner_iterator_get_property;
	G_OBJECT_CLASS (klass)->set_property = gtk_mate_scanner_iterator_set_property;
	G_OBJECT_CLASS (klass)->constructor = gtk_mate_scanner_iterator_constructor;
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_scanner_iterator_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCANNER_ITERATOR_MARKER_TYPE, g_param_spec_gtype ("marker-type", "type", "type", G_TYPE_NONE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCANNER_ITERATOR_MARKER_DUP_FUNC, g_param_spec_pointer ("marker-dup-func", "dup func", "dup func", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCANNER_ITERATOR_MARKER_DESTROY_FUNC, g_param_spec_pointer ("marker-destroy-func", "destroy func", "destroy func", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCANNER_ITERATOR_SCANNER, g_param_spec_object ("scanner", "scanner", "scanner", GTK_MATE_TYPE_SCANNER, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT));
}


static void gtk_mate_scanner_iterator_gee_iterator_interface_init (GeeIteratorIface * iface) {
	gtk_mate_scanner_iterator_gee_iterator_parent_iface = g_type_interface_peek_parent (iface);
	iface->next = gtk_mate_scanner_iterator_real_next;
	iface->get = gtk_mate_scanner_iterator_real_get;
}


static void gtk_mate_scanner_iterator_instance_init (GtkMateScannerIterator * self) {
	self->priv = GTK_MATE_SCANNER_ITERATOR_GET_PRIVATE (self);
}


static void gtk_mate_scanner_iterator_finalize (GObject* obj) {
	GtkMateScannerIterator * self;
	self = GTK_MATE_SCANNER_ITERATOR (obj);
	(self->priv->_scanner == NULL) ? NULL : (self->priv->_scanner = (g_object_unref (self->priv->_scanner), NULL));
	((self->next_marker == NULL) || (self->priv->marker_destroy_func == NULL)) ? NULL : (self->next_marker = (self->priv->marker_destroy_func (self->next_marker), NULL));
	G_OBJECT_CLASS (gtk_mate_scanner_iterator_parent_class)->finalize (obj);
}


GType gtk_mate_scanner_iterator_get_type (void) {
	static GType gtk_mate_scanner_iterator_type_id = 0;
	if (gtk_mate_scanner_iterator_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateScannerIteratorClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_scanner_iterator_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateScannerIterator), 0, (GInstanceInitFunc) gtk_mate_scanner_iterator_instance_init, NULL };
		static const GInterfaceInfo gee_iterator_info = { (GInterfaceInitFunc) gtk_mate_scanner_iterator_gee_iterator_interface_init, (GInterfaceFinalizeFunc) NULL, NULL};
		gtk_mate_scanner_iterator_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateScannerIterator", &g_define_type_info, 0);
		g_type_add_interface_static (gtk_mate_scanner_iterator_type_id, GEE_TYPE_ITERATOR, &gee_iterator_info);
	}
	return gtk_mate_scanner_iterator_type_id;
}


static void gtk_mate_scanner_iterator_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateScannerIterator * self;
	gpointer boxed;
	self = GTK_MATE_SCANNER_ITERATOR (object);
	switch (property_id) {
		case GTK_MATE_SCANNER_ITERATOR_SCANNER:
		g_value_set_object (value, gtk_mate_scanner_iterator_get_scanner (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_scanner_iterator_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GtkMateScannerIterator * self;
	self = GTK_MATE_SCANNER_ITERATOR (object);
	switch (property_id) {
		case GTK_MATE_SCANNER_ITERATOR_SCANNER:
		gtk_mate_scanner_iterator_set_scanner (self, g_value_get_object (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
		case GTK_MATE_SCANNER_ITERATOR_MARKER_TYPE:
		self->priv->marker_type = g_value_get_gtype (value);
		break;
		case GTK_MATE_SCANNER_ITERATOR_MARKER_DUP_FUNC:
		self->priv->marker_dup_func = g_value_get_pointer (value);
		break;
		case GTK_MATE_SCANNER_ITERATOR_MARKER_DESTROY_FUNC:
		self->priv->marker_destroy_func = g_value_get_pointer (value);
		break;
	}
}


static void gtk_mate_scanner_class_init (GtkMateScannerClass * klass) {
	gtk_mate_scanner_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GtkMateScannerPrivate));
	G_OBJECT_CLASS (klass)->get_property = gtk_mate_scanner_get_property;
	G_OBJECT_CLASS (klass)->set_property = gtk_mate_scanner_set_property;
	G_OBJECT_CLASS (klass)->constructor = gtk_mate_scanner_constructor;
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_scanner_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCANNER_CURRENT_SCOPE, g_param_spec_object ("current-scope", "current-scope", "current-scope", GTK_MATE_TYPE_SCOPE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCANNER_LINE, g_param_spec_string ("line", "line", "line", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCANNER_LINE_LENGTH, g_param_spec_int ("line-length", "line-length", "line-length", G_MININT, G_MAXINT, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void gtk_mate_scanner_gee_iterable_interface_init (GeeIterableIface * iface) {
	gtk_mate_scanner_gee_iterable_parent_iface = g_type_interface_peek_parent (iface);
	iface->get_element_type = gtk_mate_scanner_real_get_element_type;
	iface->iterator = gtk_mate_scanner_real_iterator;
}


static void gtk_mate_scanner_instance_init (GtkMateScanner * self) {
	self->priv = GTK_MATE_SCANNER_GET_PRIVATE (self);
}


static void gtk_mate_scanner_finalize (GObject* obj) {
	GtkMateScanner * self;
	self = GTK_MATE_SCANNER (obj);
	(self->priv->_current_scope == NULL) ? NULL : (self->priv->_current_scope = (g_object_unref (self->priv->_current_scope), NULL));
	self->priv->_line = (g_free (self->priv->_line), NULL);
	(self->cached_markers == NULL) ? NULL : (self->cached_markers = (g_object_unref (self->cached_markers), NULL));
	G_OBJECT_CLASS (gtk_mate_scanner_parent_class)->finalize (obj);
}


GType gtk_mate_scanner_get_type (void) {
	static GType gtk_mate_scanner_type_id = 0;
	if (gtk_mate_scanner_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateScannerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_scanner_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateScanner), 0, (GInstanceInitFunc) gtk_mate_scanner_instance_init, NULL };
		static const GInterfaceInfo gee_iterable_info = { (GInterfaceInitFunc) gtk_mate_scanner_gee_iterable_interface_init, (GInterfaceFinalizeFunc) NULL, NULL};
		gtk_mate_scanner_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateScanner", &g_define_type_info, 0);
		g_type_add_interface_static (gtk_mate_scanner_type_id, GEE_TYPE_ITERABLE, &gee_iterable_info);
	}
	return gtk_mate_scanner_type_id;
}


static void gtk_mate_scanner_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateScanner * self;
	gpointer boxed;
	self = GTK_MATE_SCANNER (object);
	switch (property_id) {
		case GTK_MATE_SCANNER_CURRENT_SCOPE:
		g_value_set_object (value, gtk_mate_scanner_get_current_scope (self));
		break;
		case GTK_MATE_SCANNER_LINE:
		g_value_set_string (value, gtk_mate_scanner_get_line (self));
		break;
		case GTK_MATE_SCANNER_LINE_LENGTH:
		g_value_set_int (value, gtk_mate_scanner_get_line_length (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_scanner_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GtkMateScanner * self;
	self = GTK_MATE_SCANNER (object);
	switch (property_id) {
		case GTK_MATE_SCANNER_CURRENT_SCOPE:
		gtk_mate_scanner_set_current_scope (self, g_value_get_object (value));
		break;
		case GTK_MATE_SCANNER_LINE:
		gtk_mate_scanner_set_line (self, g_value_get_string (value));
		break;
		case GTK_MATE_SCANNER_LINE_LENGTH:
		gtk_mate_scanner_set_line_length (self, g_value_get_int (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}




