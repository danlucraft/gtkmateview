
#ifndef __BUNDLE_H__
#define __BUNDLE_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <gee/arraylist.h>
#include <stdlib.h>
#include <string.h>

G_BEGIN_DECLS


#define GTK_MATE_TYPE_BUNDLE (gtk_mate_bundle_get_type ())
#define GTK_MATE_BUNDLE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_BUNDLE, GtkMateBundle))
#define GTK_MATE_BUNDLE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_BUNDLE, GtkMateBundleClass))
#define GTK_MATE_IS_BUNDLE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_BUNDLE))
#define GTK_MATE_IS_BUNDLE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_BUNDLE))
#define GTK_MATE_BUNDLE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_BUNDLE, GtkMateBundleClass))

typedef struct _GtkMateBundle GtkMateBundle;
typedef struct _GtkMateBundleClass GtkMateBundleClass;
typedef struct _GtkMateBundlePrivate GtkMateBundlePrivate;

struct _GtkMateBundle {
	GtkObject parent_instance;
	GtkMateBundlePrivate * priv;
	GeeArrayList* grammars;
};

struct _GtkMateBundleClass {
	GtkObjectClass parent_class;
};


GeeArrayList* gtk_mate_bundle_all_grammars (GtkMateBundle* self);
GtkMateBundle* gtk_mate_bundle_new (const char* name);
const char* gtk_mate_bundle_get_name (GtkMateBundle* self);
GType gtk_mate_bundle_get_type (void);


G_END_DECLS

#endif
