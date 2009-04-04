
#ifndef __GTKMATEVIEW_H__
#define __GTKMATEVIEW_H__

#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>

G_BEGIN_DECLS



extern char* gtk_mate_textmate_dir;
gint gtk_mate_load_bundles (void);
void gtk_mate_load_themes (void);
GeeArrayList* gtk_mate_bundle_dirs (void);
char* gtk_mate_textmate_share_dir (void);


G_END_DECLS

#endif
