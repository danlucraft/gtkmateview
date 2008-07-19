
#ifndef __GTKMATEVIEW_H__
#define __GTKMATEVIEW_H__

#include <glib.h>
#include <glib-object.h>
#include <gee/arraylist.h>
#include <stdlib.h>
#include <string.h>

G_BEGIN_DECLS


typedef enum  {
	GTK_MATE_MATE_ERROR_INIT_ERROR
} GtkMateMateError;
#define GTK_MATE_MATE_ERROR gtk_mate_mate_error_quark ()

gint gtk_mate_load_bundles (void);
void gtk_mate_load_themes (void);
GeeArrayList* gtk_mate_bundle_dirs (void);
char* gtk_mate_textmate_share_dir (void);
GQuark gtk_mate_mate_error_quark (void);


G_END_DECLS

#endif
