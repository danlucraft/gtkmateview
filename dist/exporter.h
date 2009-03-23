
#ifndef __EXPORTER_H__
#define __EXPORTER_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "view.h"

G_BEGIN_DECLS


#define GTK_MATE_TYPE_EXPORTER (gtk_mate_exporter_get_type ())
#define GTK_MATE_EXPORTER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_EXPORTER, GtkMateExporter))
#define GTK_MATE_EXPORTER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_EXPORTER, GtkMateExporterClass))
#define GTK_MATE_IS_EXPORTER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_EXPORTER))
#define GTK_MATE_IS_EXPORTER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_EXPORTER))
#define GTK_MATE_EXPORTER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_EXPORTER, GtkMateExporterClass))

typedef struct _GtkMateExporter GtkMateExporter;
typedef struct _GtkMateExporterClass GtkMateExporterClass;
typedef struct _GtkMateExporterPrivate GtkMateExporterPrivate;

struct _GtkMateExporter {
	GtkObject parent_instance;
	GtkMateExporterPrivate * priv;
	GtkMateView* view;
};

struct _GtkMateExporterClass {
	GtkObjectClass parent_class;
};


GtkMateExporter* gtk_mate_exporter_construct (GType object_type, GtkMateView* v);
GtkMateExporter* gtk_mate_exporter_new (GtkMateView* v);
char* gtk_mate_exporter_to_html (GtkMateExporter* self, const char* title);
GType gtk_mate_exporter_get_type (void);


G_END_DECLS

#endif
