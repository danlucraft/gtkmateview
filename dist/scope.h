
#ifndef __SCOPE_H__
#define __SCOPE_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>
#include "view.h"
#include "onig_wrap.h"
#include "pattern.h"

G_BEGIN_DECLS


#define GTK_MATE_TYPE_SCOPE (gtk_mate_scope_get_type ())
#define GTK_MATE_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SCOPE, GtkMateScope))
#define GTK_MATE_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SCOPE, GtkMateScopeClass))
#define GTK_MATE_IS_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SCOPE))
#define GTK_MATE_IS_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SCOPE))
#define GTK_MATE_SCOPE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SCOPE, GtkMateScopeClass))

typedef struct _GtkMateScopePrivate GtkMateScopePrivate;

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


extern gint gtk_mate_scope_scope_count;
GtkMateScope* gtk_mate_scope_construct (GType object_type, GtkMateBuffer* buf, const char* name);
GtkMateScope* gtk_mate_scope_new (GtkMateBuffer* buf, const char* name);
gboolean gtk_mate_scope_is_root (GtkMateScope* self);
gint gtk_mate_scope_compare (GtkMateScope* a, GtkMateScope* b, void* data);
gint gtk_mate_scope_compare_by_loc (GtkMateScope* a, GtkMateScope* b, void* data);
gboolean gtk_mate_scope_surface_identical_to_modulo_ending (GtkMateScope* self, GtkMateScope* other);
gboolean gtk_mate_scope_surface_identical_to (GtkMateScope* self, GtkMateScope* other);
GtkMateScope* gtk_mate_scope_scope_at (GtkMateScope* self, gint line, gint line_offset);
GtkMateScope* gtk_mate_scope_containing_double_scope (GtkMateScope* self);
GtkMateScope* gtk_mate_scope_first_child_after (GtkMateScope* self, GtkMateTextLoc* loc);
gboolean gtk_mate_scope_contains_loc (GtkMateScope* self, GtkMateTextLoc* loc);
gboolean gtk_mate_scope_overlaps_with (GtkMateScope* self, GtkMateScope* other);
void gtk_mate_scope_add_child (GtkMateScope* self, GtkMateScope* s);
void gtk_mate_scope_delete_child (GtkMateScope* self, GtkMateScope* s);
GeeArrayList* gtk_mate_scope_delete_any_on_line_not_in (GtkMateScope* self, gint line_ix, GeeArrayList* scopes);
void gtk_mate_scope_clear_after (GtkMateScope* self, gint line_ix, gint line_offset);
char* gtk_mate_scope_pretty (GtkMateScope* self, gint indent);
void gtk_mate_scope_start_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity);
void gtk_mate_scope_inner_start_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity);
void gtk_mate_scope_inner_end_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity);
void gtk_mate_scope_end_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity);
GtkTextIter gtk_mate_scope_start_iter (GtkMateScope* self);
GtkTextIter gtk_mate_scope_inner_start_iter (GtkMateScope* self);
GtkTextIter gtk_mate_scope_inner_end_iter (GtkMateScope* self);
GtkTextIter gtk_mate_scope_end_iter (GtkMateScope* self);
gint gtk_mate_scope_start_offset (GtkMateScope* self);
gint gtk_mate_scope_inner_start_offset (GtkMateScope* self);
gint gtk_mate_scope_inner_end_offset (GtkMateScope* self);
gint gtk_mate_scope_end_offset (GtkMateScope* self);
gint gtk_mate_scope_start_line (GtkMateScope* self);
gint gtk_mate_scope_inner_start_line (GtkMateScope* self);
gint gtk_mate_scope_inner_end_line (GtkMateScope* self);
gint gtk_mate_scope_end_line (GtkMateScope* self);
gint gtk_mate_scope_start_line_offset (GtkMateScope* self);
gint gtk_mate_scope_inner_start_line_offset (GtkMateScope* self);
gint gtk_mate_scope_inner_end_line_offset (GtkMateScope* self);
gint gtk_mate_scope_end_line_offset (GtkMateScope* self);
GtkMateTextLoc* gtk_mate_scope_start_loc (GtkMateScope* self);
GtkMateTextLoc* gtk_mate_scope_inner_start_loc (GtkMateScope* self);
GtkMateTextLoc* gtk_mate_scope_inner_end_loc (GtkMateScope* self);
GtkMateTextLoc* gtk_mate_scope_end_loc (GtkMateScope* self);
GtkMateScope* gtk_mate_scope_root (GtkMateScope* self);
gint gtk_mate_scope_priority (GtkMateScope* self, gboolean inner);
char* gtk_mate_scope_hierarchy_names (GtkMateScope* self, gboolean inner);
char* gtk_mate_scope_nearest_background_colour (GtkMateScope* self);
char* gtk_mate_scope_nearest_background_colour1 (GtkMateScope* self);
char* gtk_mate_scope_nearest_foreground_colour (GtkMateScope* self);
char* gtk_mate_scope_nearest_foreground_colour1 (GtkMateScope* self);
const char* gtk_mate_scope_get_name (GtkMateScope* self);
void gtk_mate_scope_set_name (GtkMateScope* self, const char* value);
GtkMateBuffer* gtk_mate_scope_get_buffer (GtkMateScope* self);
void gtk_mate_scope_set_buffer (GtkMateScope* self, GtkMateBuffer* value);
GSequence* gtk_mate_scope_get_children (GtkMateScope* self);
gboolean gtk_mate_scope_get_is_coloured (GtkMateScope* self);
void gtk_mate_scope_set_is_coloured (GtkMateScope* self, gboolean value);
GType gtk_mate_scope_get_type (void);


G_END_DECLS

#endif
