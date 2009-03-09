
#ifndef __VIEW_H__
#define __VIEW_H__

#include <glib.h>
#include <glib-object.h>
#include <gtksourceview/gtksourceview.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"

G_BEGIN_DECLS


#define GTK_MATE_TYPE_VIEW (gtk_mate_view_get_type ())
#define GTK_MATE_VIEW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_VIEW, GtkMateView))
#define GTK_MATE_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_VIEW, GtkMateViewClass))
#define GTK_MATE_IS_VIEW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_VIEW))
#define GTK_MATE_IS_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_VIEW))
#define GTK_MATE_VIEW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_VIEW, GtkMateViewClass))

typedef struct _GtkMateViewPrivate GtkMateViewPrivate;

struct _GtkMateView {
	GtkSourceView parent_instance;
	GtkMateViewPrivate * priv;
};

struct _GtkMateViewClass {
	GtkSourceViewClass parent_class;
};


gboolean gtk_mate_view_set_theme_by_name (GtkMateView* self, const char* name);
void gtk_mate_view_set_global_theme_settings (GtkMateView* self);
void gtk_mate_view_value_changed_handler (GtkMateView* self);
GtkMateParser* gtk_mate_view_get_parser (GtkMateView* self);
gint gtk_mate_view_first_visible_line (GtkMateView* self);
gint gtk_mate_view_last_visible_line (GtkMateView* self);
GtkMateView* gtk_mate_view_construct (GType object_type);
GtkMateView* gtk_mate_view_new (void);
GType gtk_mate_view_get_type (void);


G_END_DECLS

#endif
