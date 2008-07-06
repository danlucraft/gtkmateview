
#ifndef __GTKMATEVIEW_H__
#define __GTKMATEVIEW_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS


#define GTK_TYPE_MATE_VIEW (gtk_mate_view_get_type ())
#define GTK_MATE_VIEW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_MATE_VIEW, GtkMateView))
#define GTK_MATE_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_MATE_VIEW, GtkMateViewClass))
#define GTK_IS_MATE_VIEW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_MATE_VIEW))
#define GTK_IS_MATE_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_MATE_VIEW))
#define GTK_MATE_VIEW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_MATE_VIEW, GtkMateViewClass))

typedef struct _GtkMateView GtkMateView;
typedef struct _GtkMateViewClass GtkMateViewClass;
typedef struct _GtkMateViewPrivate GtkMateViewPrivate;

struct _GtkMateView {
	GtkTextView parent_instance;
	GtkMateViewPrivate * priv;
};

struct _GtkMateViewClass {
	GtkTextViewClass parent_class;
};


void gtk_mate_view_test_regex (char** args, int args_length1);
GtkMateView* gtk_mate_view_new (void);
GType gtk_mate_view_get_type (void);


G_END_DECLS

#endif
