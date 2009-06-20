
#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gtksourceview/gtksourceview.h>
#include <gee/arraylist.h>
#include <gee/collection.h>
#include <gee/hashmap.h>


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

#define GTK_MATE_TYPE_THEME_SETTING (gtk_mate_theme_setting_get_type ())
#define GTK_MATE_THEME_SETTING(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSetting))
#define GTK_MATE_THEME_SETTING_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSettingClass))
#define GTK_MATE_IS_THEME_SETTING(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_THEME_SETTING))
#define GTK_MATE_IS_THEME_SETTING_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_THEME_SETTING))
#define GTK_MATE_THEME_SETTING_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSettingClass))

typedef struct _GtkMateThemeSetting GtkMateThemeSetting;
typedef struct _GtkMateThemeSettingClass GtkMateThemeSettingClass;

#define GTK_MATE_TYPE_BUFFER (gtk_mate_buffer_get_type ())
#define GTK_MATE_BUFFER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_BUFFER, GtkMateBuffer))
#define GTK_MATE_BUFFER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_BUFFER, GtkMateBufferClass))
#define GTK_MATE_IS_BUFFER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_BUFFER))
#define GTK_MATE_IS_BUFFER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_BUFFER))
#define GTK_MATE_BUFFER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_BUFFER, GtkMateBufferClass))

typedef struct _GtkMateBuffer GtkMateBuffer;
typedef struct _GtkMateBufferClass GtkMateBufferClass;

#define GTK_MATE_TYPE_SINGLE_PATTERN (gtk_mate_single_pattern_get_type ())
#define GTK_MATE_SINGLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePattern))
#define GTK_MATE_SINGLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePatternClass))
#define GTK_MATE_IS_SINGLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SINGLE_PATTERN))
#define GTK_MATE_IS_SINGLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SINGLE_PATTERN))
#define GTK_MATE_SINGLE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePatternClass))

typedef struct _GtkMateSinglePattern GtkMateSinglePattern;
typedef struct _GtkMateSinglePatternClass GtkMateSinglePatternClass;

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

struct _GtkMateScopePrivate {
	char* _name;
	GtkMateBuffer* _buffer;
	GSequence* _children;
	gboolean _is_coloured;
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



GType gtk_mate_scope_get_type (void);
GType gtk_mate_pattern_get_type (void);
GType onig_match_get_type (void);
GType onig_rx_get_type (void);
GType gtk_mate_text_loc_get_type (void);
GType gtk_mate_theme_setting_get_type (void);
GType gtk_mate_buffer_get_type (void);
#define GTK_MATE_SCOPE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_TYPE_SCOPE, GtkMateScopePrivate))
enum  {
	GTK_MATE_SCOPE_DUMMY_PROPERTY,
	GTK_MATE_SCOPE_NAME,
	GTK_MATE_SCOPE_BUFFER,
	GTK_MATE_SCOPE_CHILDREN,
	GTK_MATE_SCOPE_IS_COLOURED
};
extern gint gtk_mate_scope_scope_count;
gint gtk_mate_scope_scope_count = 0;
void gtk_mate_scope_set_name (GtkMateScope* self, const char* value);
void gtk_mate_scope_set_buffer (GtkMateScope* self, GtkMateBuffer* value);
void gtk_mate_scope_set_is_coloured (GtkMateScope* self, gboolean value);
GtkMateScope* gtk_mate_scope_new (GtkMateBuffer* buf, const char* name);
GtkMateScope* gtk_mate_scope_construct (GType object_type, GtkMateBuffer* buf, const char* name);
GtkMateScope* gtk_mate_scope_new (GtkMateBuffer* buf, const char* name);
gboolean gtk_mate_scope_is_root (GtkMateScope* self);
GtkTextIter gtk_mate_scope_start_iter (GtkMateScope* self);
gint gtk_mate_scope_compare (GtkMateScope* a, GtkMateScope* b, void* data);
GtkMateTextLoc* gtk_mate_scope_start_loc (GtkMateScope* self);
gboolean gtk_mate_text_loc_lt (GtkMateTextLoc* t1, GtkMateTextLoc* t2);
gboolean gtk_mate_text_loc_equal (GtkMateTextLoc* t1, GtkMateTextLoc* t2);
gint gtk_mate_scope_compare_by_loc (GtkMateScope* a, GtkMateScope* b, void* data);
const char* gtk_mate_scope_get_name (GtkMateScope* self);
GtkMateTextLoc* gtk_mate_scope_inner_start_loc (GtkMateScope* self);
gboolean gtk_mate_scope_surface_identical_to_modulo_ending (GtkMateScope* self, GtkMateScope* other);
GtkMateTextLoc* gtk_mate_scope_end_loc (GtkMateScope* self);
GtkMateTextLoc* gtk_mate_scope_inner_end_loc (GtkMateScope* self);
gboolean gtk_mate_scope_surface_identical_to (GtkMateScope* self, GtkMateScope* other);
GtkMateTextLoc* gtk_mate_text_loc_make (gint l, gint lo);
gboolean gtk_mate_text_loc_lte (GtkMateTextLoc* t1, GtkMateTextLoc* t2);
gboolean gtk_mate_text_loc_gte (GtkMateTextLoc* t1, GtkMateTextLoc* t2);
GSequence* gtk_mate_scope_get_children (GtkMateScope* self);
GtkMateBuffer* gtk_mate_scope_get_buffer (GtkMateScope* self);
gboolean gtk_mate_scope_contains_loc (GtkMateScope* self, GtkMateTextLoc* loc);
GtkMateScope* gtk_mate_scope_scope_at (GtkMateScope* self, gint line, gint line_offset);
GType gtk_mate_single_pattern_get_type (void);
gint gtk_mate_scope_start_line (GtkMateScope* self);
gint gtk_mate_scope_start_line_offset (GtkMateScope* self);
GtkMateScope* gtk_mate_scope_containing_double_scope (GtkMateScope* self, gint line_ix);
GtkMateScope* gtk_mate_scope_first_child_after (GtkMateScope* self, GtkMateTextLoc* loc);
gboolean gtk_mate_text_loc_gt (GtkMateTextLoc* t1, GtkMateTextLoc* t2);
GtkTextIter gtk_mate_scope_end_iter (GtkMateScope* self);
gboolean gtk_mate_scope_overlaps_with (GtkMateScope* self, GtkMateScope* other);
void gtk_mate_scope_add_child (GtkMateScope* self, GtkMateScope* s);
void gtk_mate_scope_delete_child (GtkMateScope* self, GtkMateScope* s);
GeeArrayList* gtk_mate_scope_delete_any_on_line_not_in (GtkMateScope* self, gint line_ix, GeeArrayList* scopes);
void gtk_mate_scope_clear_after (GtkMateScope* self, gint line_ix, gint line_offset);
GType gtk_mate_double_pattern_get_type (void);
GtkTextIter gtk_mate_buffer_iter_from_mark (GtkMateBuffer* self, GtkTextMark* mark);
char* gtk_mate_scope_pretty (GtkMateScope* self, gint indent);
GtkTextIter gtk_mate_buffer_iter_at_line_index (GtkMateBuffer* self, gint line, gint line_offset);
void gtk_mate_scope_start_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity);
void gtk_mate_scope_inner_start_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity);
void gtk_mate_scope_inner_end_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity);
void gtk_mate_scope_end_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity);
GtkTextIter gtk_mate_scope_inner_start_iter (GtkMateScope* self);
GtkTextIter gtk_mate_scope_inner_end_iter (GtkMateScope* self);
GtkTextIter gtk_mate_buffer_iter_ (GtkMateBuffer* self, gint offset);
gint gtk_mate_scope_start_offset (GtkMateScope* self);
gint gtk_mate_scope_inner_start_offset (GtkMateScope* self);
gint gtk_mate_scope_inner_end_offset (GtkMateScope* self);
gint gtk_mate_scope_end_offset (GtkMateScope* self);
gint gtk_mate_scope_inner_start_line (GtkMateScope* self);
gint gtk_mate_scope_inner_end_line (GtkMateScope* self);
gint gtk_mate_scope_end_line (GtkMateScope* self);
gint gtk_mate_scope_inner_start_line_offset (GtkMateScope* self);
gint gtk_mate_scope_inner_end_line_offset (GtkMateScope* self);
gint gtk_mate_scope_end_line_offset (GtkMateScope* self);
GtkMateScope* gtk_mate_scope_root (GtkMateScope* self);
gint gtk_mate_scope_priority (GtkMateScope* self, gboolean inner);
char* gtk_mate_scope_hierarchy_names (GtkMateScope* self, gboolean inner);
char* gtk_mate_scope_nearest_background_colour1 (GtkMateScope* self);
char* gtk_mate_scope_nearest_background_colour (GtkMateScope* self);
char* gtk_mate_scope_nearest_foreground_colour1 (GtkMateScope* self);
char* gtk_mate_scope_nearest_foreground_colour (GtkMateScope* self);
gboolean gtk_mate_scope_get_is_coloured (GtkMateScope* self);
static GObject * gtk_mate_scope_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer gtk_mate_scope_parent_class = NULL;
static void gtk_mate_scope_finalize (GObject* obj);
static void gtk_mate_scope_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void gtk_mate_scope_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
static int _vala_strcmp0 (const char * str1, const char * str2);



GtkMateScope* gtk_mate_scope_construct (GType object_type, GtkMateBuffer* buf, const char* name) {
	GtkMateScope * self;
	g_return_val_if_fail (buf != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	gtk_mate_scope_set_name (self, name);
	gtk_mate_scope_set_buffer (self, buf);
	gtk_mate_scope_set_is_coloured (self, FALSE);
	return self;
}


GtkMateScope* gtk_mate_scope_new (GtkMateBuffer* buf, const char* name) {
	return gtk_mate_scope_construct (GTK_MATE_TYPE_SCOPE, buf, name);
}


gboolean gtk_mate_scope_is_root (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, FALSE);
	if (self->parent == NULL) {
		return TRUE;
	}
	return FALSE;
}


/* compare two Scope's. Returns 1 if a is later than b,
 -1 if a is before b and 0 if b is overlapping with a*/
gint gtk_mate_scope_compare (GtkMateScope* a, GtkMateScope* b, void* data) {
	GtkTextIter _tmp1_ = {0};
	GtkTextIter _tmp0_ = {0};
	g_return_val_if_fail (a != NULL, 0);
	g_return_val_if_fail (b != NULL, 0);
	return gtk_text_iter_compare ((_tmp0_ = gtk_mate_scope_start_iter (a), &_tmp0_), (_tmp1_ = gtk_mate_scope_start_iter (b), &_tmp1_));
}


gint gtk_mate_scope_compare_by_loc (GtkMateScope* a, GtkMateScope* b, void* data) {
	GtkMateTextLoc* a_start;
	GtkMateTextLoc* b_start;
	g_return_val_if_fail (a != NULL, 0);
	g_return_val_if_fail (b != NULL, 0);
	a_start = gtk_mate_scope_start_loc (a);
	b_start = gtk_mate_scope_start_loc (b);
	/*stdout.printf("comparing: %s (%d, %d) to %s (%d, %d)\n", a.name, a_start.line, a_start.line_offset,
	b.name, b_start.line, b_start.line_offset);*/
	if (gtk_mate_text_loc_lt (a_start, b_start)) {
		gint _tmp0_;
		/*stdout.printf("  -1\n");*/
		return (_tmp0_ = -1, (a_start == NULL) ? NULL : (a_start = (g_object_unref (a_start), NULL)), (b_start == NULL) ? NULL : (b_start = (g_object_unref (b_start), NULL)), _tmp0_);
	} else {
		if (gtk_mate_text_loc_equal (a_start, b_start)) {
			gint _tmp1_;
			/*stdout.printf("  0\n");*/
			return (_tmp1_ = 0, (a_start == NULL) ? NULL : (a_start = (g_object_unref (a_start), NULL)), (b_start == NULL) ? NULL : (b_start = (g_object_unref (b_start), NULL)), _tmp1_);
		} else {
			gint _tmp2_;
			/*stdout.printf("  1\n");*/
			return (_tmp2_ = 1, (a_start == NULL) ? NULL : (a_start = (g_object_unref (a_start), NULL)), (b_start == NULL) ? NULL : (b_start = (g_object_unref (b_start), NULL)), _tmp2_);
		}
	}
	(a_start == NULL) ? NULL : (a_start = (g_object_unref (a_start), NULL));
	(b_start == NULL) ? NULL : (b_start = (g_object_unref (b_start), NULL));
}


gboolean gtk_mate_scope_surface_identical_to_modulo_ending (GtkMateScope* self, GtkMateScope* other) {
	gboolean _tmp0_;
	gboolean _tmp1_;
	gboolean _tmp2_;
	gboolean _tmp3_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (other != NULL, FALSE);
	_tmp0_ = FALSE;
	_tmp1_ = FALSE;
	_tmp2_ = FALSE;
	_tmp3_ = FALSE;
	if (_vala_strcmp0 (self->priv->_name, other->priv->_name) == 0) {
		_tmp3_ = self->pattern == other->pattern;
	} else {
		_tmp3_ = FALSE;
	}
	if (_tmp3_) {
		GtkMateTextLoc* _tmp5_;
		GtkMateTextLoc* _tmp4_;
		_tmp5_ = NULL;
		_tmp4_ = NULL;
		_tmp2_ = gtk_mate_text_loc_equal (_tmp4_ = gtk_mate_scope_start_loc (self), _tmp5_ = gtk_mate_scope_start_loc (other));
		(_tmp5_ == NULL) ? NULL : (_tmp5_ = (g_object_unref (_tmp5_), NULL));
		(_tmp4_ == NULL) ? NULL : (_tmp4_ = (g_object_unref (_tmp4_), NULL));
	} else {
		_tmp2_ = FALSE;
	}
	if (_tmp2_) {
		GtkMateTextLoc* _tmp7_;
		GtkMateTextLoc* _tmp6_;
		_tmp7_ = NULL;
		_tmp6_ = NULL;
		_tmp1_ = gtk_mate_text_loc_equal (_tmp6_ = gtk_mate_scope_inner_start_loc (self), _tmp7_ = gtk_mate_scope_inner_start_loc (other));
		(_tmp7_ == NULL) ? NULL : (_tmp7_ = (g_object_unref (_tmp7_), NULL));
		(_tmp6_ == NULL) ? NULL : (_tmp6_ = (g_object_unref (_tmp6_), NULL));
	} else {
		_tmp1_ = FALSE;
	}
	if (_tmp1_) {
		_tmp0_ = _vala_strcmp0 (self->begin_match_string, other->begin_match_string) == 0;
	} else {
		_tmp0_ = FALSE;
	}
	/* stdout.printf("%s == %s and %s == %s and %s == %s and %s == %s and %s == %s",
	   name, other.name, pattern.name, other.pattern.name, start_loc().to_s(),
	   other.start_loc().to_s(), inner_start_loc().to_s(), other.inner_start_loc().to_s(),
	   begin_match_string, other.begin_match_string);*/
	if (_tmp0_) {
		return TRUE;
	}
	return FALSE;
}


gboolean gtk_mate_scope_surface_identical_to (GtkMateScope* self, GtkMateScope* other) {
	gboolean _tmp0_;
	gboolean _tmp1_;
	gboolean _tmp2_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (other != NULL, FALSE);
	_tmp0_ = FALSE;
	_tmp1_ = FALSE;
	_tmp2_ = FALSE;
	if (gtk_mate_scope_surface_identical_to_modulo_ending (self, other)) {
		GtkMateTextLoc* _tmp4_;
		GtkMateTextLoc* _tmp3_;
		_tmp4_ = NULL;
		_tmp3_ = NULL;
		_tmp2_ = gtk_mate_text_loc_equal (_tmp3_ = gtk_mate_scope_end_loc (self), _tmp4_ = gtk_mate_scope_end_loc (other));
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
		_tmp1_ = gtk_mate_text_loc_equal (_tmp5_ = gtk_mate_scope_inner_end_loc (self), _tmp6_ = gtk_mate_scope_inner_end_loc (other));
		(_tmp6_ == NULL) ? NULL : (_tmp6_ = (g_object_unref (_tmp6_), NULL));
		(_tmp5_ == NULL) ? NULL : (_tmp5_ = (g_object_unref (_tmp5_), NULL));
	} else {
		_tmp1_ = FALSE;
	}
	if (_tmp1_) {
		_tmp0_ = _vala_strcmp0 (self->begin_match_string, other->begin_match_string) == 0;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		return TRUE;
	}
	return FALSE;
}


GtkMateScope* gtk_mate_scope_scope_at (GtkMateScope* self, gint line, gint line_offset) {
	GtkMateTextLoc* loc;
	GtkMateTextLoc* start;
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	loc = gtk_mate_text_loc_make (line, line_offset);
	start = gtk_mate_scope_start_loc (self);
	_tmp0_ = FALSE;
	if (gtk_mate_text_loc_lte (start, loc)) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = self->parent == NULL;
	}
	if (_tmp0_) {
		GtkMateTextLoc* _tmp1_;
		gboolean _tmp2_;
		_tmp1_ = NULL;
		if ((_tmp2_ = gtk_mate_text_loc_gte (_tmp1_ = gtk_mate_scope_end_loc (self), loc), (_tmp1_ == NULL) ? NULL : (_tmp1_ = (g_object_unref (_tmp1_), NULL)), _tmp2_)) {
			GtkMateScope* s;
			GtkMateTextLoc* _tmp6_;
			GtkMateTextLoc* _tmp5_;
			GtkMateTextLoc* _tmp8_;
			GtkMateTextLoc* _tmp7_;
			GSequenceIter* iter;
			GtkMateScope* _tmp13_;
			GtkMateScope* _tmp14_;
			if (g_sequence_get_length (gtk_mate_scope_get_children (self)) == 0) {
				GtkMateScope* _tmp3_;
				GtkMateScope* _tmp4_;
				_tmp3_ = NULL;
				_tmp4_ = NULL;
				return (_tmp4_ = (_tmp3_ = self, (_tmp3_ == NULL) ? NULL : g_object_ref (_tmp3_)), (loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL)), (start == NULL) ? NULL : (start = (g_object_unref (start), NULL)), _tmp4_);
			}
			s = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, ""));
			_tmp6_ = NULL;
			_tmp5_ = NULL;
			s->dummy_start_loc = (_tmp6_ = (_tmp5_ = loc, (_tmp5_ == NULL) ? NULL : g_object_ref (_tmp5_)), (s->dummy_start_loc == NULL) ? NULL : (s->dummy_start_loc = (g_object_unref (s->dummy_start_loc), NULL)), _tmp6_);
			_tmp8_ = NULL;
			_tmp7_ = NULL;
			s->dummy_end_loc = (_tmp8_ = (_tmp7_ = loc, (_tmp7_ == NULL) ? NULL : g_object_ref (_tmp7_)), (s->dummy_end_loc == NULL) ? NULL : (s->dummy_end_loc = (g_object_unref (s->dummy_end_loc), NULL)), _tmp8_);
			iter = g_sequence_search (gtk_mate_scope_get_children (self), s, (GCompareDataFunc) gtk_mate_scope_compare_by_loc, NULL);
			if (!g_sequence_iter_is_begin (iter)) {
				GtkMateScope* _tmp9_;
				GtkMateScope* prev_scope;
				_tmp9_ = NULL;
				prev_scope = (_tmp9_ = (GtkMateScope*) g_sequence_get (g_sequence_iter_prev (iter)), (_tmp9_ == NULL) ? NULL : g_object_ref (_tmp9_));
				if (gtk_mate_scope_contains_loc (prev_scope, loc)) {
					GtkMateScope* _tmp10_;
					_tmp10_ = NULL;
					return (_tmp10_ = gtk_mate_scope_scope_at (prev_scope, line, line_offset), (prev_scope == NULL) ? NULL : (prev_scope = (g_object_unref (prev_scope), NULL)), (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), (loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL)), (start == NULL) ? NULL : (start = (g_object_unref (start), NULL)), _tmp10_);
				}
				(prev_scope == NULL) ? NULL : (prev_scope = (g_object_unref (prev_scope), NULL));
			}
			if (!g_sequence_iter_is_end (iter)) {
				GtkMateScope* _tmp11_;
				GtkMateScope* next_scope;
				_tmp11_ = NULL;
				next_scope = (_tmp11_ = (GtkMateScope*) g_sequence_get (iter), (_tmp11_ == NULL) ? NULL : g_object_ref (_tmp11_));
				/* .next());*/
				if (gtk_mate_scope_contains_loc (next_scope, loc)) {
					GtkMateScope* _tmp12_;
					_tmp12_ = NULL;
					return (_tmp12_ = gtk_mate_scope_scope_at (next_scope, line, line_offset), (next_scope == NULL) ? NULL : (next_scope = (g_object_unref (next_scope), NULL)), (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), (loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL)), (start == NULL) ? NULL : (start = (g_object_unref (start), NULL)), _tmp12_);
				}
				(next_scope == NULL) ? NULL : (next_scope = (g_object_unref (next_scope), NULL));
			}
			_tmp13_ = NULL;
			_tmp14_ = NULL;
			return (_tmp14_ = (_tmp13_ = self, (_tmp13_ == NULL) ? NULL : g_object_ref (_tmp13_)), (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), (loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL)), (start == NULL) ? NULL : (start = (g_object_unref (start), NULL)), _tmp14_);
		} else {
			GtkMateScope* _tmp15_;
			_tmp15_ = NULL;
			return (_tmp15_ = NULL, (loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL)), (start == NULL) ? NULL : (start = (g_object_unref (start), NULL)), _tmp15_);
		}
	} else {
		GtkMateScope* _tmp16_;
		_tmp16_ = NULL;
		return (_tmp16_ = NULL, (loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL)), (start == NULL) ? NULL : (start = (g_object_unref (start), NULL)), _tmp16_);
	}
	(loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL));
	(start == NULL) ? NULL : (start = (g_object_unref (start), NULL));
}


GtkMateScope* gtk_mate_scope_containing_double_scope (GtkMateScope* self, gint line_ix) {
	GtkMateScope* _tmp0_;
	GtkMateScope* scope;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = NULL;
	scope = (_tmp0_ = self, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	while (TRUE) {
		gboolean _tmp1_;
		gboolean _tmp2_;
		gboolean _tmp3_;
		GtkMateScope* _tmp6_;
		GtkMateScope* _tmp5_;
		_tmp1_ = FALSE;
		_tmp2_ = FALSE;
		_tmp3_ = FALSE;
		if (GTK_MATE_IS_SINGLE_PATTERN (scope->pattern)) {
			_tmp3_ = TRUE;
		} else {
			_tmp3_ = scope->is_capture;
		}
		if (_tmp3_) {
			_tmp2_ = TRUE;
		} else {
			gboolean _tmp4_;
			_tmp4_ = FALSE;
			if (gtk_mate_scope_start_line (scope) == line_ix) {
				_tmp4_ = gtk_mate_scope_start_line_offset (scope) == 0;
			} else {
				_tmp4_ = FALSE;
			}
			_tmp2_ = _tmp4_;
		}
		if (_tmp2_) {
			_tmp1_ = scope->parent != NULL;
		} else {
			_tmp1_ = FALSE;
		}
		if (!_tmp1_) {
			break;
		}
		_tmp6_ = NULL;
		_tmp5_ = NULL;
		scope = (_tmp6_ = (_tmp5_ = scope->parent, (_tmp5_ == NULL) ? NULL : g_object_ref (_tmp5_)), (scope == NULL) ? NULL : (scope = (g_object_unref (scope), NULL)), _tmp6_);
	}
	return scope;
}


GtkMateScope* gtk_mate_scope_first_child_after (GtkMateScope* self, GtkMateTextLoc* loc) {
	GtkMateScope* s;
	GtkMateTextLoc* _tmp2_;
	GtkMateTextLoc* _tmp1_;
	GtkMateTextLoc* _tmp4_;
	GtkMateTextLoc* _tmp3_;
	GSequenceIter* iter;
	GtkMateScope* _tmp9_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (loc != NULL, NULL);
	/*stdout.printf("\"%s\".first_child_after(%d, %d)\n", name, loc.line, loc.line_offset);*/
	if (g_sequence_get_length (gtk_mate_scope_get_children (self)) == 0) {
		return NULL;
	}
	s = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, ""));
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	s->dummy_start_loc = (_tmp2_ = (_tmp1_ = loc, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (s->dummy_start_loc == NULL) ? NULL : (s->dummy_start_loc = (g_object_unref (s->dummy_start_loc), NULL)), _tmp2_);
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	s->dummy_end_loc = (_tmp4_ = (_tmp3_ = loc, (_tmp3_ == NULL) ? NULL : g_object_ref (_tmp3_)), (s->dummy_end_loc == NULL) ? NULL : (s->dummy_end_loc = (g_object_unref (s->dummy_end_loc), NULL)), _tmp4_);
	iter = g_sequence_search (gtk_mate_scope_get_children (self), s, (GCompareDataFunc) gtk_mate_scope_compare_by_loc, NULL);
	if (!g_sequence_iter_is_begin (iter)) {
		GtkMateScope* _tmp5_;
		GtkMateScope* prev_scope;
		_tmp5_ = NULL;
		prev_scope = (_tmp5_ = (GtkMateScope*) g_sequence_get (g_sequence_iter_prev (iter)), (_tmp5_ == NULL) ? NULL : g_object_ref (_tmp5_));
		if (gtk_mate_scope_compare_by_loc (prev_scope, s, NULL) == 0) {
			GtkMateScope* _tmp6_;
			_tmp6_ = NULL;
			return (_tmp6_ = prev_scope, (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), _tmp6_);
		}
		(prev_scope == NULL) ? NULL : (prev_scope = (g_object_unref (prev_scope), NULL));
	}
	if (!g_sequence_iter_is_end (iter)) {
		GtkMateScope* _tmp7_;
		GtkMateScope* _tmp8_;
		_tmp7_ = NULL;
		_tmp8_ = NULL;
		return (_tmp8_ = (_tmp7_ = (GtkMateScope*) g_sequence_get (iter), (_tmp7_ == NULL) ? NULL : g_object_ref (_tmp7_)), (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), _tmp8_);
	}
	_tmp9_ = NULL;
	return (_tmp9_ = NULL, (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), _tmp9_);
}


gboolean gtk_mate_scope_contains_loc (GtkMateScope* self, GtkMateTextLoc* loc) {
	gboolean _tmp0_;
	GtkMateTextLoc* _tmp1_;
	gboolean _tmp2_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (loc != NULL, FALSE);
	_tmp0_ = FALSE;
	_tmp1_ = NULL;
	if ((_tmp2_ = gtk_mate_text_loc_lte (_tmp1_ = gtk_mate_scope_start_loc (self), loc), (_tmp1_ == NULL) ? NULL : (_tmp1_ = (g_object_unref (_tmp1_), NULL)), _tmp2_)) {
		GtkMateTextLoc* _tmp3_;
		_tmp3_ = NULL;
		_tmp0_ = gtk_mate_text_loc_gt (_tmp3_ = gtk_mate_scope_end_loc (self), loc);
		(_tmp3_ == NULL) ? NULL : (_tmp3_ = (g_object_unref (_tmp3_), NULL));
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		return TRUE;
	} else {
		return FALSE;
	}
}


gboolean gtk_mate_scope_overlaps_with (GtkMateScope* self, GtkMateScope* other) {
	GtkTextIter _tmp1_ = {0};
	GtkTextIter _tmp0_ = {0};
	GtkTextIter _tmp7_ = {0};
	GtkTextIter _tmp6_ = {0};
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (other != NULL, FALSE);
	/* sd1    +---
	 sd2  +---*/
	if (gtk_text_iter_compare ((_tmp0_ = gtk_mate_scope_start_iter (self), &_tmp0_), (_tmp1_ = gtk_mate_scope_start_iter (other), &_tmp1_)) >= 0) {
		GtkTextIter _tmp3_ = {0};
		GtkTextIter _tmp2_ = {0};
		if (gtk_text_iter_compare ((_tmp2_ = gtk_mate_scope_start_iter (self), &_tmp2_), (_tmp3_ = gtk_mate_scope_end_iter (other), &_tmp3_)) < 0) {
			return TRUE;
		}
		return FALSE;
	}
	/* sd1 +---
	 sd2   +---*/
	if (gtk_text_iter_compare ((_tmp6_ = gtk_mate_scope_end_iter (self), &_tmp6_), (_tmp7_ = gtk_mate_scope_start_iter (other), &_tmp7_)) > 0) {
		return TRUE;
	}
	return FALSE;
}


void gtk_mate_scope_add_child (GtkMateScope* self, GtkMateScope* s) {
	GtkMateScope* _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (s != NULL);
	_tmp0_ = NULL;
	g_sequence_insert_sorted (gtk_mate_scope_get_children (self), (_tmp0_ = s, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (GCompareDataFunc) gtk_mate_scope_compare, NULL);
}


void gtk_mate_scope_delete_child (GtkMateScope* self, GtkMateScope* s) {
	GSequenceIter* iter;
	g_return_if_fail (self != NULL);
	g_return_if_fail (s != NULL);
	iter = g_sequence_search (gtk_mate_scope_get_children (self), s, (GCompareDataFunc) gtk_mate_scope_compare, NULL);
	/* The gsequence docs don't say whether iter will now be pointing to
	 the equal element, so we have to look on the left and on the right.*/
	if (!g_sequence_iter_is_begin (iter)) {
		GtkMateScope* _tmp0_;
		GtkMateScope* prev_scope;
		_tmp0_ = NULL;
		prev_scope = (_tmp0_ = (GtkMateScope*) g_sequence_get (g_sequence_iter_prev (iter)), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
		if (prev_scope == s) {
			/* stdout.printf("leftremove\n");*/
			g_sequence_remove (g_sequence_iter_prev (iter));
			(prev_scope == NULL) ? NULL : (prev_scope = (g_object_unref (prev_scope), NULL));
			return;
		}
		(prev_scope == NULL) ? NULL : (prev_scope = (g_object_unref (prev_scope), NULL));
	}
	if (!g_sequence_iter_is_end (iter)) {
		GtkMateScope* _tmp1_;
		GtkMateScope* next_scope;
		_tmp1_ = NULL;
		next_scope = (_tmp1_ = (GtkMateScope*) g_sequence_get (iter), (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_));
		if (next_scope == s) {
			/* stdout.printf("rightremove\n");*/
			g_sequence_remove (iter);
			(next_scope == NULL) ? NULL : (next_scope = (g_object_unref (next_scope), NULL));
			return;
		}
		(next_scope == NULL) ? NULL : (next_scope = (g_object_unref (next_scope), NULL));
	}
}


GeeArrayList* gtk_mate_scope_delete_any_on_line_not_in (GtkMateScope* self, gint line_ix, GeeArrayList* scopes) {
	GeeArrayList* removed_scopes;
	gboolean removed;
	GtkMateScope* s;
	GtkMateTextLoc* loc;
	GtkMateTextLoc* _tmp1_;
	GtkMateTextLoc* _tmp0_;
	GtkMateTextLoc* _tmp3_;
	GtkMateTextLoc* _tmp2_;
	GSequenceIter* iter;
	GeeArrayList* _tmp6_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (scopes != NULL, NULL);
	/*var start_scope = scope_at(line_ix, -1);*/
	removed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	/*var iter = children.get_begin_iter();*/
	removed = FALSE;
	s = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, ""));
	loc = gtk_mate_text_loc_make (line_ix, -1);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	s->dummy_start_loc = (_tmp1_ = (_tmp0_ = loc, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (s->dummy_start_loc == NULL) ? NULL : (s->dummy_start_loc = (g_object_unref (s->dummy_start_loc), NULL)), _tmp1_);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	s->dummy_end_loc = (_tmp3_ = (_tmp2_ = loc, (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (s->dummy_end_loc == NULL) ? NULL : (s->dummy_end_loc = (g_object_unref (s->dummy_end_loc), NULL)), _tmp3_);
	iter = g_sequence_search (gtk_mate_scope_get_children (self), s, (GCompareDataFunc) gtk_mate_scope_compare_by_loc, NULL);
	while (!g_sequence_iter_is_end (iter)) {
		GtkMateScope* _tmp4_;
		GtkMateScope* child;
		removed = FALSE;
		_tmp4_ = NULL;
		child = (_tmp4_ = (GtkMateScope*) g_sequence_get (iter), (_tmp4_ == NULL) ? NULL : g_object_ref (_tmp4_));
		if (gtk_mate_scope_start_line (child) > line_ix) {
			GeeArrayList* _tmp5_;
			_tmp5_ = NULL;
			return (_tmp5_ = removed_scopes, (child == NULL) ? NULL : (child = (g_object_unref (child), NULL)), (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), (loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL)), _tmp5_);
		}
		if (gtk_mate_scope_start_line (child) == line_ix) {
			if (!gee_collection_contains ((GeeCollection*) scopes, child)) {
				gee_collection_add ((GeeCollection*) removed_scopes, child);
				iter = g_sequence_iter_next (iter);
				g_sequence_remove (g_sequence_iter_prev (iter));
				removed = TRUE;
			}
		}
		if (!removed) {
			iter = g_sequence_iter_next (iter);
		}
		(child == NULL) ? NULL : (child = (g_object_unref (child), NULL));
	}
	_tmp6_ = NULL;
	return (_tmp6_ = removed_scopes, (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), (loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL)), _tmp6_);
}


void gtk_mate_scope_clear_after (GtkMateScope* self, gint line_ix, gint line_offset) {
	GtkMateTextLoc* loc;
	GtkMateScope* s;
	GtkMateTextLoc* _tmp1_;
	GtkMateTextLoc* _tmp0_;
	GtkMateTextLoc* _tmp3_;
	GtkMateTextLoc* _tmp2_;
	GSequenceIter* iter;
	GSequenceIter* prev_iter;
	GSequenceIter* end_iter;
	g_return_if_fail (self != NULL);
	loc = gtk_mate_text_loc_make (line_ix, line_offset);
	s = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, ""));
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	s->dummy_start_loc = (_tmp1_ = (_tmp0_ = loc, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (s->dummy_start_loc == NULL) ? NULL : (s->dummy_start_loc = (g_object_unref (s->dummy_start_loc), NULL)), _tmp1_);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	s->dummy_end_loc = (_tmp3_ = (_tmp2_ = loc, (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (s->dummy_end_loc == NULL) ? NULL : (s->dummy_end_loc = (g_object_unref (s->dummy_end_loc), NULL)), _tmp3_);
	iter = g_sequence_search (gtk_mate_scope_get_children (self), s, (GCompareDataFunc) gtk_mate_scope_compare_by_loc, NULL);
	prev_iter = g_sequence_iter_prev (iter);
	if (!g_sequence_iter_is_end (prev_iter)) {
		GtkMateScope* _tmp4_;
		GtkMateScope* prev_child;
		GtkMateTextLoc* _tmp5_;
		gboolean _tmp6_;
		_tmp4_ = NULL;
		prev_child = (_tmp4_ = (GtkMateScope*) g_sequence_get (g_sequence_iter_prev (iter)), (_tmp4_ == NULL) ? NULL : g_object_ref (_tmp4_));
		_tmp5_ = NULL;
		if ((_tmp6_ = gtk_mate_text_loc_gt (_tmp5_ = gtk_mate_scope_end_loc (prev_child), loc), (_tmp5_ == NULL) ? NULL : (_tmp5_ = (g_object_unref (_tmp5_), NULL)), _tmp6_)) {
			gtk_mate_scope_clear_after (prev_child, line_ix, line_offset);
		}
		(prev_child == NULL) ? NULL : (prev_child = (g_object_unref (prev_child), NULL));
	}
	end_iter = g_sequence_get_end_iter (gtk_mate_scope_get_children (self));
	g_sequence_remove_range (iter, end_iter);
	(loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL));
	(s == NULL) ? NULL : (s = (g_object_unref (s), NULL));
}


char* gtk_mate_scope_pretty (GtkMateScope* self, gint indent) {
	GString* _tmp0_;
	char* _tmp1_;
	gboolean _tmp2_;
	gboolean _tmp3_;
	const char* _tmp11_;
	GSequenceIter* iter;
	const char* _tmp13_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = NULL;
	self->pretty_string = (_tmp0_ = g_string_new (""), (self->pretty_string == NULL) ? NULL : (self->pretty_string = (g_string_free (self->pretty_string, TRUE), NULL)), _tmp0_);
	self->indent = indent;
	{
		gint i;
		i = 0;
		for (; i < self->indent; i++) {
			g_string_append (self->pretty_string, "  ");
		}
	}
	if (self->is_capture) {
		g_string_append (self->pretty_string, "c");
	} else {
		g_string_append (self->pretty_string, "+");
	}
	_tmp1_ = NULL;
	g_string_append (self->pretty_string, _tmp1_ = g_strconcat (" ", self->priv->_name, NULL));
	_tmp1_ = (g_free (_tmp1_), NULL);
	_tmp2_ = FALSE;
	_tmp3_ = FALSE;
	if (GTK_MATE_IS_DOUBLE_PATTERN (self->pattern)) {
		_tmp3_ = self->is_capture == FALSE;
	} else {
		_tmp3_ = FALSE;
	}
	if (_tmp3_) {
		_tmp2_ = GTK_MATE_DOUBLE_PATTERN (self->pattern)->content_name != NULL;
	} else {
		_tmp2_ = FALSE;
	}
	if (_tmp2_) {
		char* _tmp4_;
		_tmp4_ = NULL;
		g_string_append (self->pretty_string, _tmp4_ = g_strconcat (" ", GTK_MATE_DOUBLE_PATTERN (self->pattern)->content_name, NULL));
		_tmp4_ = (g_free (_tmp4_), NULL);
	}
	g_string_append (self->pretty_string, " (");
	if (self->start_mark == NULL) {
		g_string_append (self->pretty_string, "inf");
	} else {
		char* _tmp7_;
		GtkTextIter _tmp6_ = {0};
		GtkTextIter _tmp5_ = {0};
		_tmp7_ = NULL;
		g_string_append (self->pretty_string, _tmp7_ = g_strdup_printf ("%d,%d", gtk_text_iter_get_line ((_tmp5_ = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark), &_tmp5_)), gtk_text_iter_get_line_offset ((_tmp6_ = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark), &_tmp6_))));
		_tmp7_ = (g_free (_tmp7_), NULL);
	}
	g_string_append (self->pretty_string, ")-(");
	if (self->end_mark == NULL) {
		g_string_append (self->pretty_string, "inf");
	} else {
		char* _tmp10_;
		GtkTextIter _tmp9_ = {0};
		GtkTextIter _tmp8_ = {0};
		_tmp10_ = NULL;
		g_string_append (self->pretty_string, _tmp10_ = g_strdup_printf ("%d,%d", gtk_text_iter_get_line ((_tmp8_ = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark), &_tmp8_)), gtk_text_iter_get_line_offset ((_tmp9_ = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark), &_tmp9_))));
		_tmp10_ = (g_free (_tmp10_), NULL);
	}
	g_string_append (self->pretty_string, ")");
	_tmp11_ = NULL;
	if (self->is_open) {
		_tmp11_ = " open";
	} else {
		_tmp11_ = " closed";
	}
	g_string_append (self->pretty_string, _tmp11_);
	g_string_append (self->pretty_string, "\n");
	self->indent = self->indent + 1;
	iter = g_sequence_get_begin_iter (gtk_mate_scope_get_children (self));
	while (!g_sequence_iter_is_end (iter)) {
		char* _tmp12_;
		_tmp12_ = NULL;
		g_string_append (self->pretty_string, _tmp12_ = gtk_mate_scope_pretty ((GtkMateScope*) g_sequence_get (iter), self->indent));
		_tmp12_ = (g_free (_tmp12_), NULL);
		iter = g_sequence_iter_next (iter);
	}
	self->indent = self->indent - 1;
	_tmp13_ = NULL;
	return (_tmp13_ = self->pretty_string->str, (_tmp13_ == NULL) ? NULL : g_strdup (_tmp13_));
}


void gtk_mate_scope_start_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity) {
	GtkTextMark* _tmp2_;
	GtkTextMark* _tmp1_;
	GtkTextIter _tmp0_ = {0};
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->start_mark = (_tmp2_ = (_tmp1_ = gtk_text_buffer_create_mark ((GtkTextBuffer*) self->priv->_buffer, NULL, (_tmp0_ = gtk_mate_buffer_iter_at_line_index (self->priv->_buffer, line, line_offset), &_tmp0_), has_left_gravity), (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->start_mark == NULL) ? NULL : (self->start_mark = (g_object_unref (self->start_mark), NULL)), _tmp2_);
}


void gtk_mate_scope_inner_start_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity) {
	GtkTextMark* _tmp2_;
	GtkTextMark* _tmp1_;
	GtkTextIter _tmp0_ = {0};
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->inner_start_mark = (_tmp2_ = (_tmp1_ = gtk_text_buffer_create_mark ((GtkTextBuffer*) self->priv->_buffer, NULL, (_tmp0_ = gtk_mate_buffer_iter_at_line_index (self->priv->_buffer, line, line_offset), &_tmp0_), has_left_gravity), (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->inner_start_mark == NULL) ? NULL : (self->inner_start_mark = (g_object_unref (self->inner_start_mark), NULL)), _tmp2_);
}


void gtk_mate_scope_inner_end_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity) {
	GtkTextMark* _tmp2_;
	GtkTextMark* _tmp1_;
	GtkTextIter _tmp0_ = {0};
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->inner_end_mark = (_tmp2_ = (_tmp1_ = gtk_text_buffer_create_mark ((GtkTextBuffer*) self->priv->_buffer, NULL, (_tmp0_ = gtk_mate_buffer_iter_at_line_index (self->priv->_buffer, line, line_offset), &_tmp0_), has_left_gravity), (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->inner_end_mark == NULL) ? NULL : (self->inner_end_mark = (g_object_unref (self->inner_end_mark), NULL)), _tmp2_);
}


void gtk_mate_scope_end_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity) {
	GtkTextMark* _tmp2_;
	GtkTextMark* _tmp1_;
	GtkTextIter _tmp0_ = {0};
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->end_mark = (_tmp2_ = (_tmp1_ = gtk_text_buffer_create_mark ((GtkTextBuffer*) self->priv->_buffer, NULL, (_tmp0_ = gtk_mate_buffer_iter_at_line_index (self->priv->_buffer, line, line_offset), &_tmp0_), has_left_gravity), (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->end_mark == NULL) ? NULL : (self->end_mark = (g_object_unref (self->end_mark), NULL)), _tmp2_);
}


GtkTextIter gtk_mate_scope_start_iter (GtkMateScope* self) {
	return gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark);
}


GtkTextIter gtk_mate_scope_inner_start_iter (GtkMateScope* self) {
	return gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->inner_start_mark);
}


GtkTextIter gtk_mate_scope_inner_end_iter (GtkMateScope* self) {
	if (self->inner_end_mark != NULL) {
		return gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->inner_end_mark);
	} else {
		return gtk_mate_scope_end_iter (self);
	}
}


GtkTextIter gtk_mate_scope_end_iter (GtkMateScope* self) {
	if (self->end_mark != NULL) {
		return gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark);
	} else {
		return gtk_mate_buffer_iter_ (self->priv->_buffer, gtk_text_buffer_get_char_count ((GtkTextBuffer*) self->priv->_buffer));
	}
}


gint gtk_mate_scope_start_offset (GtkMateScope* self) {
	GtkTextIter _tmp0_ = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_offset ((_tmp0_ = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark), &_tmp0_));
}


gint gtk_mate_scope_inner_start_offset (GtkMateScope* self) {
	GtkTextIter _tmp0_ = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_offset ((_tmp0_ = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->inner_start_mark), &_tmp0_));
}


gint gtk_mate_scope_inner_end_offset (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, 0);
	if (self->inner_end_mark != NULL) {
		GtkTextIter _tmp0_ = {0};
		return gtk_text_iter_get_offset ((_tmp0_ = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->inner_end_mark), &_tmp0_));
	} else {
		return G_MAXINT;
	}
}


gint gtk_mate_scope_end_offset (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, 0);
	if (self->end_mark != NULL) {
		GtkTextIter _tmp0_ = {0};
		return gtk_text_iter_get_offset ((_tmp0_ = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark), &_tmp0_));
	} else {
		return G_MAXINT;
	}
}


gint gtk_mate_scope_start_line (GtkMateScope* self) {
	GtkTextIter _tmp0_ = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_line ((_tmp0_ = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark), &_tmp0_));
}


gint gtk_mate_scope_inner_start_line (GtkMateScope* self) {
	GtkTextIter _tmp0_ = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_line ((_tmp0_ = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->inner_start_mark), &_tmp0_));
}


gint gtk_mate_scope_inner_end_line (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, 0);
	if (self->inner_end_mark != NULL) {
		GtkTextIter _tmp0_ = {0};
		return gtk_text_iter_get_line ((_tmp0_ = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->inner_end_mark), &_tmp0_));
	} else {
		return G_MAXINT;
	}
}


gint gtk_mate_scope_end_line (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, 0);
	if (self->end_mark != NULL) {
		GtkTextIter _tmp0_ = {0};
		return gtk_text_iter_get_line ((_tmp0_ = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark), &_tmp0_));
	} else {
		return G_MAXINT;
	}
}


gint gtk_mate_scope_start_line_offset (GtkMateScope* self) {
	GtkTextIter _tmp0_ = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_line_offset ((_tmp0_ = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark), &_tmp0_));
}


gint gtk_mate_scope_inner_start_line_offset (GtkMateScope* self) {
	GtkTextIter _tmp0_ = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_line_offset ((_tmp0_ = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->inner_start_mark), &_tmp0_));
}


gint gtk_mate_scope_inner_end_line_offset (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, 0);
	if (self->inner_end_mark != NULL) {
		GtkTextIter _tmp0_ = {0};
		return gtk_text_iter_get_line_offset ((_tmp0_ = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->inner_end_mark), &_tmp0_));
	} else {
		return G_MAXINT;
	}
}


gint gtk_mate_scope_end_line_offset (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, 0);
	if (self->end_mark != NULL) {
		GtkTextIter _tmp0_ = {0};
		return gtk_text_iter_get_line_offset ((_tmp0_ = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark), &_tmp0_));
	} else {
		return G_MAXINT;
	}
}


GtkMateTextLoc* gtk_mate_scope_start_loc (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->dummy_start_loc != NULL) {
		GtkMateTextLoc* _tmp0_;
		_tmp0_ = NULL;
		return (_tmp0_ = self->dummy_start_loc, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	} else {
		GtkTextIter s_iter;
		s_iter = gtk_mate_scope_start_iter (self);
		return gtk_mate_text_loc_make (gtk_text_iter_get_line (&s_iter), gtk_text_iter_get_line_offset (&s_iter));
	}
}


GtkMateTextLoc* gtk_mate_scope_inner_start_loc (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->inner_start_mark != NULL) {
		GtkTextIter is_iter;
		is_iter = gtk_mate_scope_inner_start_iter (self);
		return gtk_mate_text_loc_make (gtk_text_iter_get_line (&is_iter), gtk_text_iter_get_line_offset (&is_iter));
	} else {
		return gtk_mate_scope_start_loc (self);
	}
}


GtkMateTextLoc* gtk_mate_scope_inner_end_loc (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->inner_end_mark != NULL) {
		GtkTextIter ie_iter;
		ie_iter = gtk_mate_scope_inner_end_iter (self);
		return gtk_mate_text_loc_make (gtk_text_iter_get_line (&ie_iter), gtk_text_iter_get_line_offset (&ie_iter));
	} else {
		return gtk_mate_scope_end_loc (self);
	}
}


GtkMateTextLoc* gtk_mate_scope_end_loc (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->dummy_end_loc != NULL) {
		GtkMateTextLoc* _tmp0_;
		_tmp0_ = NULL;
		return (_tmp0_ = self->dummy_end_loc, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	} else {
		GtkTextIter e_iter;
		e_iter = gtk_mate_scope_end_iter (self);
		return gtk_mate_text_loc_make (gtk_text_iter_get_line (&e_iter), gtk_text_iter_get_line_offset (&e_iter));
	}
}


GtkMateScope* gtk_mate_scope_root (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->parent == NULL) {
		GtkMateScope* _tmp0_;
		_tmp0_ = NULL;
		return (_tmp0_ = self, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	} else {
		return gtk_mate_scope_root (self->parent);
	}
}


gint gtk_mate_scope_priority (GtkMateScope* self, gboolean inner) {
	g_return_val_if_fail (self != NULL, 0);
	if (self->parent == NULL) {
		if (inner) {
			return 2;
		} else {
			return 1;
		}
	} else {
		if (inner) {
			return gtk_mate_scope_priority (self->parent, TRUE) + 2;
		} else {
			return gtk_mate_scope_priority (self->parent, TRUE) + 1;
		}
	}
}


char* gtk_mate_scope_hierarchy_names (GtkMateScope* self, gboolean inner) {
	char* self_name;
	gboolean _tmp0_;
	gboolean _tmp1_;
	g_return_val_if_fail (self != NULL, NULL);
	self_name = NULL;
	_tmp0_ = FALSE;
	_tmp1_ = FALSE;
	if (GTK_MATE_IS_DOUBLE_PATTERN (self->pattern)) {
		_tmp1_ = GTK_MATE_DOUBLE_PATTERN (self->pattern)->content_name != NULL;
	} else {
		_tmp1_ = FALSE;
	}
	if (_tmp1_) {
		_tmp0_ = inner;
	} else {
		_tmp0_ = FALSE;
	}
	/* stdout.printf("'%s'.hierarchy_names(%s)\n", name, inner ? "true" : "false");*/
	if (_tmp0_) {
		char* _tmp3_;
		char* _tmp2_;
		_tmp3_ = NULL;
		_tmp2_ = NULL;
		self_name = (_tmp3_ = g_strconcat (_tmp2_ = g_strconcat (self->priv->_name, " ", NULL), GTK_MATE_DOUBLE_PATTERN (self->pattern)->content_name, NULL), self_name = (g_free (self_name), NULL), _tmp3_);
		_tmp2_ = (g_free (_tmp2_), NULL);
	} else {
		char* _tmp5_;
		const char* _tmp4_;
		_tmp5_ = NULL;
		_tmp4_ = NULL;
		self_name = (_tmp5_ = (_tmp4_ = self->priv->_name, (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_)), self_name = (g_free (self_name), NULL), _tmp5_);
	}
	if (self->parent != NULL) {
		gboolean next_inner;
		char* _tmp7_;
		char* _tmp6_;
		char* _tmp8_;
		char* _tmp9_;
		next_inner = FALSE;
		if (self->is_capture) {
			next_inner = FALSE;
		} else {
			next_inner = TRUE;
		}
		_tmp7_ = NULL;
		_tmp6_ = NULL;
		_tmp8_ = NULL;
		_tmp9_ = NULL;
		return (_tmp9_ = (_tmp8_ = g_strconcat (_tmp7_ = g_strconcat (_tmp6_ = gtk_mate_scope_hierarchy_names (self->parent, next_inner), " ", NULL), self_name, NULL), _tmp7_ = (g_free (_tmp7_), NULL), _tmp6_ = (g_free (_tmp6_), NULL), _tmp8_), self_name = (g_free (self_name), NULL), _tmp9_);
	} else {
		return self_name;
	}
	self_name = (g_free (self_name), NULL);
}


/* public int scope_id() {
 if (id == null) {
 Scope.id_count++;
 id = Scope.id_count;
 }
 return id;
 }*/
char* gtk_mate_scope_nearest_background_colour (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->parent != NULL) {
		return gtk_mate_scope_nearest_background_colour1 (self->parent);
	}
	return NULL;
}


char* gtk_mate_scope_nearest_background_colour1 (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->bg_colour != NULL) {
		const char* _tmp0_;
		_tmp0_ = NULL;
		return (_tmp0_ = self->bg_colour, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
	}
	if (self->parent != NULL) {
		return gtk_mate_scope_nearest_background_colour1 (self->parent);
	}
	return NULL;
}


char* gtk_mate_scope_nearest_foreground_colour (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->parent != NULL) {
		return gtk_mate_scope_nearest_foreground_colour1 (self->parent);
	}
	return NULL;
}


char* gtk_mate_scope_nearest_foreground_colour1 (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->fg_colour != NULL) {
		const char* _tmp0_;
		_tmp0_ = NULL;
		return (_tmp0_ = self->fg_colour, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
	}
	if (self->parent != NULL) {
		return gtk_mate_scope_nearest_foreground_colour1 (self->parent);
	}
	return NULL;
}


const char* gtk_mate_scope_get_name (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_name;
}


void gtk_mate_scope_set_name (GtkMateScope* self, const char* value) {
	char* _tmp2_;
	const char* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_name = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), self->priv->_name = (g_free (self->priv->_name), NULL), _tmp2_);
	g_object_notify ((GObject *) self, "name");
}


GtkMateBuffer* gtk_mate_scope_get_buffer (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_buffer;
}


void gtk_mate_scope_set_buffer (GtkMateScope* self, GtkMateBuffer* value) {
	GtkMateBuffer* _tmp2_;
	GtkMateBuffer* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_buffer = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->priv->_buffer == NULL) ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL)), _tmp2_);
	g_object_notify ((GObject *) self, "buffer");
}


GSequence* gtk_mate_scope_get_children (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->priv->_children == NULL) {
		GSequence* _tmp0_;
		_tmp0_ = NULL;
		self->priv->_children = (_tmp0_ = g_sequence_new (NULL), (self->priv->_children == NULL) ? NULL : (self->priv->_children = (g_sequence_free (self->priv->_children), NULL)), _tmp0_);
	}
	return self->priv->_children;
}


gboolean gtk_mate_scope_get_is_coloured (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, FALSE);
	return self->priv->_is_coloured;
}


void gtk_mate_scope_set_is_coloured (GtkMateScope* self, gboolean value) {
	g_return_if_fail (self != NULL);
	self->priv->_is_coloured = value;
	g_object_notify ((GObject *) self, "is-coloured");
}


static GObject * gtk_mate_scope_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GtkMateScopeClass * klass;
	GObjectClass * parent_class;
	GtkMateScope * self;
	klass = GTK_MATE_SCOPE_CLASS (g_type_class_peek (GTK_MATE_TYPE_SCOPE));
	parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = GTK_MATE_SCOPE (obj);
	{
		gtk_mate_scope_scope_count++;
	}
	return obj;
}


static void gtk_mate_scope_class_init (GtkMateScopeClass * klass) {
	gtk_mate_scope_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GtkMateScopePrivate));
	G_OBJECT_CLASS (klass)->get_property = gtk_mate_scope_get_property;
	G_OBJECT_CLASS (klass)->set_property = gtk_mate_scope_set_property;
	G_OBJECT_CLASS (klass)->constructor = gtk_mate_scope_constructor;
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_scope_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCOPE_NAME, g_param_spec_string ("name", "name", "name", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCOPE_BUFFER, g_param_spec_object ("buffer", "buffer", "buffer", GTK_MATE_TYPE_BUFFER, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCOPE_CHILDREN, g_param_spec_pointer ("children", "children", "children", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCOPE_IS_COLOURED, g_param_spec_boolean ("is-coloured", "is-coloured", "is-coloured", FALSE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void gtk_mate_scope_instance_init (GtkMateScope * self) {
	self->priv = GTK_MATE_SCOPE_GET_PRIVATE (self);
}


static void gtk_mate_scope_finalize (GObject* obj) {
	GtkMateScope * self;
	self = GTK_MATE_SCOPE (obj);
	(self->pattern == NULL) ? NULL : (self->pattern = (g_object_unref (self->pattern), NULL));
	self->priv->_name = (g_free (self->priv->_name), NULL);
	(self->priv->_buffer == NULL) ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL));
	(self->open_match == NULL) ? NULL : (self->open_match = (g_object_unref (self->open_match), NULL));
	(self->close_match == NULL) ? NULL : (self->close_match = (g_object_unref (self->close_match), NULL));
	(self->closing_regex == NULL) ? NULL : (self->closing_regex = (g_object_unref (self->closing_regex), NULL));
	(self->start_mark == NULL) ? NULL : (self->start_mark = (g_object_unref (self->start_mark), NULL));
	(self->inner_start_mark == NULL) ? NULL : (self->inner_start_mark = (g_object_unref (self->inner_start_mark), NULL));
	(self->inner_end_mark == NULL) ? NULL : (self->inner_end_mark = (g_object_unref (self->inner_end_mark), NULL));
	(self->end_mark == NULL) ? NULL : (self->end_mark = (g_object_unref (self->end_mark), NULL));
	(self->tag == NULL) ? NULL : (self->tag = (g_object_unref (self->tag), NULL));
	(self->inner_tag == NULL) ? NULL : (self->inner_tag = (g_object_unref (self->inner_tag), NULL));
	self->bg_colour = (g_free (self->bg_colour), NULL);
	self->fg_colour = (g_free (self->fg_colour), NULL);
	(self->dummy_start_loc == NULL) ? NULL : (self->dummy_start_loc = (g_object_unref (self->dummy_start_loc), NULL));
	(self->dummy_end_loc == NULL) ? NULL : (self->dummy_end_loc = (g_object_unref (self->dummy_end_loc), NULL));
	self->begin_match_string = (g_free (self->begin_match_string), NULL);
	self->end_match_string = (g_free (self->end_match_string), NULL);
	(self->priv->_children == NULL) ? NULL : (self->priv->_children = (g_sequence_free (self->priv->_children), NULL));
	(self->parent == NULL) ? NULL : (self->parent = (g_object_unref (self->parent), NULL));
	(self->pretty_string == NULL) ? NULL : (self->pretty_string = (g_string_free (self->pretty_string, TRUE), NULL));
	(self->theme_setting == NULL) ? NULL : (self->theme_setting = (g_object_unref (self->theme_setting), NULL));
	G_OBJECT_CLASS (gtk_mate_scope_parent_class)->finalize (obj);
}


GType gtk_mate_scope_get_type (void) {
	static GType gtk_mate_scope_type_id = 0;
	if (gtk_mate_scope_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateScopeClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_scope_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateScope), 0, (GInstanceInitFunc) gtk_mate_scope_instance_init, NULL };
		gtk_mate_scope_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateScope", &g_define_type_info, 0);
	}
	return gtk_mate_scope_type_id;
}


static void gtk_mate_scope_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateScope * self;
	gpointer boxed;
	self = GTK_MATE_SCOPE (object);
	switch (property_id) {
		case GTK_MATE_SCOPE_NAME:
		g_value_set_string (value, gtk_mate_scope_get_name (self));
		break;
		case GTK_MATE_SCOPE_BUFFER:
		g_value_set_object (value, gtk_mate_scope_get_buffer (self));
		break;
		case GTK_MATE_SCOPE_CHILDREN:
		g_value_set_pointer (value, gtk_mate_scope_get_children (self));
		break;
		case GTK_MATE_SCOPE_IS_COLOURED:
		g_value_set_boolean (value, gtk_mate_scope_get_is_coloured (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_scope_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GtkMateScope * self;
	self = GTK_MATE_SCOPE (object);
	switch (property_id) {
		case GTK_MATE_SCOPE_NAME:
		gtk_mate_scope_set_name (self, g_value_get_string (value));
		break;
		case GTK_MATE_SCOPE_BUFFER:
		gtk_mate_scope_set_buffer (self, g_value_get_object (value));
		break;
		case GTK_MATE_SCOPE_IS_COLOURED:
		gtk_mate_scope_set_is_coloured (self, g_value_get_boolean (value));
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




