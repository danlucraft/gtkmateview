
#ifndef __COLOURER_H__
#define __COLOURER_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <gee/arraylist.h>
#include "theme.h"

G_BEGIN_DECLS


#define GTK_MATE_TYPE_COLOURER (gtk_mate_colourer_get_type ())
#define GTK_MATE_COLOURER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_COLOURER, GtkMateColourer))
#define GTK_MATE_COLOURER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_COLOURER, GtkMateColourerClass))
#define GTK_MATE_IS_COLOURER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_COLOURER))
#define GTK_MATE_IS_COLOURER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_COLOURER))
#define GTK_MATE_COLOURER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_COLOURER, GtkMateColourerClass))

typedef struct _GtkMateColourerPrivate GtkMateColourerPrivate;

struct _GtkMateColourer {
	GtkObject parent_instance;
	GtkMateColourerPrivate * priv;
};

struct _GtkMateColourerClass {
	GtkObjectClass parent_class;
};


GtkMateColourer* gtk_mate_colourer_new (GtkMateBuffer* buffer);
void gtk_mate_colourer_colour_line_with_scopes (GtkMateColourer* self, GeeArrayList* scopes);
void gtk_mate_colourer_colour_scope (GtkMateColourer* self, GtkMateScope* scope, gboolean colour_inner);
GtkMateBuffer* gtk_mate_colourer_get_buffer (GtkMateColourer* self);
void gtk_mate_colourer_set_buffer (GtkMateColourer* self, GtkMateBuffer* value);
GtkMateTheme* gtk_mate_colourer_get_theme (GtkMateColourer* self);
void gtk_mate_colourer_set_theme (GtkMateColourer* self, GtkMateTheme* value);
GType gtk_mate_colourer_get_type (void);


G_END_DECLS

#endif
