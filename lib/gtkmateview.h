
#ifndef __GTKMATEVIEW_H__
#define __GTKMATEVIEW_H__

#include <glib.h>
#include <glib-object.h>
#include <gee/arraylist.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS


#define GTK_MATE_TYPE_THEME (gtk_mate_theme_get_type ())
#define GTK_MATE_THEME(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_THEME, GtkMateTheme))
#define GTK_MATE_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_THEME, GtkMateThemeClass))
#define GTK_MATE_IS_THEME(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_THEME))
#define GTK_MATE_IS_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_THEME))
#define GTK_MATE_THEME_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_THEME, GtkMateThemeClass))

typedef struct _GtkMateTheme GtkMateTheme;
typedef struct _GtkMateThemeClass GtkMateThemeClass;
typedef struct _GtkMateThemePrivate GtkMateThemePrivate;

typedef enum  {
	GTK_MATE_MATE_ERROR_INIT_ERROR
} GtkMateMateError;
#define GTK_MATE_MATE_ERROR gtk_mate_mate_error_quark ()
struct _GtkMateTheme {
	GtkObject parent_instance;
	GtkMateThemePrivate * priv;
};

struct _GtkMateThemeClass {
	GtkObjectClass parent_class;
};


gint gtk_mate_load_bundles (void);
GeeArrayList* gtk_mate_bundle_dirs (void);
char* gtk_mate_textmate_share_dir (void);
char** gtk_mate_bundle_dirs_rb (int* result_length1);
GQuark gtk_mate_mate_error_quark (void);
GtkMateTheme* gtk_mate_theme_new (void);
GType gtk_mate_theme_get_type (void);


G_END_DECLS

#endif
