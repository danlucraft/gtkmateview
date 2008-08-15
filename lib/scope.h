
#ifndef __SCOPE_H__
#define __SCOPE_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <gtksourceview/gtksourceview.h>
#include <stdlib.h>
#include <string.h>
#include <pattern.h>
#include <onig_wrap.h>

G_BEGIN_DECLS


#define GTK_MATE_TYPE_SCOPE (gtk_mate_scope_get_type ())
#define GTK_MATE_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SCOPE, GtkMateScope))
#define GTK_MATE_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SCOPE, GtkMateScopeClass))
#define GTK_MATE_IS_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SCOPE))
#define GTK_MATE_IS_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SCOPE))
#define GTK_MATE_SCOPE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SCOPE, GtkMateScopeClass))

typedef struct _GtkMateScope GtkMateScope;
typedef struct _GtkMateScopeClass GtkMateScopeClass;
typedef struct _GtkMateScopePrivate GtkMateScopePrivate;

struct _GtkMateScope {
	GtkObject parent_instance;
	GtkMateScopePrivate * priv;
	GtkMatePattern* pattern;
	OnigurumaMatch* open_match;
	OnigurumaMatch* close_match;
	OnigurumaRegex* closing_regex;
	GtkSourceMark* start_mark;
	GtkSourceMark* inner_start_mark;
	GtkSourceMark* inner_end_mark;
	GtkSourceMark* end_mark;
	GtkTextTag* tag;
	GtkTextTag* inner_tag;
	char* bg_color;
	gboolean is_capture;
	GtkMateScope* parent;
	GString* pretty_string;
	gint indent;
};

struct _GtkMateScopeClass {
	GtkObjectClass parent_class;
};


GtkMateScope* gtk_mate_scope_new (const char* name);
gboolean gtk_mate_scope_is_root (GtkMateScope* self);
gint gtk_mate_scope_compare (GtkMateScope* a, GtkMateScope* b);
char* gtk_mate_scope_pretty (GtkMateScope* self, gint indent);
void gtk_mate_scope_append_pretty (GtkMateScope* self, GtkMateScope* child);
const char* gtk_mate_scope_get_name (GtkMateScope* self);
void gtk_mate_scope_set_name (GtkMateScope* self, const char* value);
GSequence* gtk_mate_scope_get_children (GtkMateScope* self);
GType gtk_mate_scope_get_type (void);


G_END_DECLS

#endif
