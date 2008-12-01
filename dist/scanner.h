
#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <gee/iterable.h>
#include <gee/arraylist.h>
#include <stdlib.h>
#include <string.h>
#include <gee/iterator.h>
#include "scope.h"
#include "pattern.h"
#include "onig_wrap.h"

G_BEGIN_DECLS


#define GTK_MATE_TYPE_MARKER (gtk_mate_marker_get_type ())
#define GTK_MATE_MARKER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_MARKER, GtkMateMarker))
#define GTK_MATE_MARKER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_MARKER, GtkMateMarkerClass))
#define GTK_MATE_IS_MARKER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_MARKER))
#define GTK_MATE_IS_MARKER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_MARKER))
#define GTK_MATE_MARKER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_MARKER, GtkMateMarkerClass))

typedef struct _GtkMateMarker GtkMateMarker;
typedef struct _GtkMateMarkerClass GtkMateMarkerClass;
typedef struct _GtkMateMarkerPrivate GtkMateMarkerPrivate;

#define GTK_MATE_TYPE_SCANNER (gtk_mate_scanner_get_type ())
#define GTK_MATE_SCANNER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SCANNER, GtkMateScanner))
#define GTK_MATE_SCANNER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SCANNER, GtkMateScannerClass))
#define GTK_MATE_IS_SCANNER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SCANNER))
#define GTK_MATE_IS_SCANNER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SCANNER))
#define GTK_MATE_SCANNER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SCANNER, GtkMateScannerClass))

typedef struct _GtkMateScanner GtkMateScanner;
typedef struct _GtkMateScannerClass GtkMateScannerClass;
typedef struct _GtkMateScannerPrivate GtkMateScannerPrivate;

#define GTK_MATE_SCANNER_TYPE_ITERATOR (gtk_mate_scanner_iterator_get_type ())
#define GTK_MATE_SCANNER_ITERATOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_SCANNER_TYPE_ITERATOR, GtkMateScannerIterator))
#define GTK_MATE_SCANNER_ITERATOR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_SCANNER_TYPE_ITERATOR, GtkMateScannerIteratorClass))
#define GTK_MATE_SCANNER_IS_ITERATOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_SCANNER_TYPE_ITERATOR))
#define GTK_MATE_SCANNER_IS_ITERATOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_SCANNER_TYPE_ITERATOR))
#define GTK_MATE_SCANNER_ITERATOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_SCANNER_TYPE_ITERATOR, GtkMateScannerIteratorClass))

typedef struct _GtkMateScannerIterator GtkMateScannerIterator;
typedef struct _GtkMateScannerIteratorClass GtkMateScannerIteratorClass;
typedef struct _GtkMateScannerIteratorPrivate GtkMateScannerIteratorPrivate;

/* The Scanner returns these to indicate successful pattern matches in a line.*/
struct _GtkMateMarker {
	GtkObject parent_instance;
	GtkMateMarkerPrivate * priv;
	gint from;
	gint hint;
	gboolean is_close_scope;
	GtkMatePattern* pattern;
	OnigMatch* match;
};

struct _GtkMateMarkerClass {
	GtkObjectClass parent_class;
};

/* the matchdata of the successful match
 Scans lines for patterns. Handles caching of what has already been seen etc.*/
struct _GtkMateScanner {
	GtkObject parent_instance;
	GtkMateScannerPrivate * priv;
	gint position;
	GeeArrayList* cached_markers;
};

struct _GtkMateScannerClass {
	GtkObjectClass parent_class;
};

struct _GtkMateScannerIterator {
	GtkObject parent_instance;
	GtkMateScannerIteratorPrivate * priv;
	gpointer next_marker;
};

struct _GtkMateScannerIteratorClass {
	GtkObjectClass parent_class;
};


GtkMateMarker* gtk_mate_marker_construct (GType object_type);
GtkMateMarker* gtk_mate_marker_new (void);
GType gtk_mate_marker_get_type (void);
GtkMateScanner* gtk_mate_scanner_construct (GType object_type, GtkMateScope* s, const char* line, gint line_length);
GtkMateScanner* gtk_mate_scanner_new (GtkMateScope* s, const char* line, gint line_length);
GtkMateMarker* gtk_mate_scanner_get_cached_marker (GtkMateScanner* self);
void gtk_mate_scanner_remove_preceding_cached_markers (GtkMateScanner* self, GtkMateMarker* m);
OnigMatch* gtk_mate_scanner_scan_for_match (GtkMateScanner* self, gint from, GtkMatePattern* p);
GtkMateMarker* gtk_mate_scanner_find_next_marker (GtkMateScanner* self);
GtkMateScope* gtk_mate_scanner_get_current_scope (GtkMateScanner* self);
void gtk_mate_scanner_set_current_scope (GtkMateScanner* self, GtkMateScope* value);
const char* gtk_mate_scanner_get_line (GtkMateScanner* self);
void gtk_mate_scanner_set_line (GtkMateScanner* self, const char* value);
gint gtk_mate_scanner_get_line_length (GtkMateScanner* self);
void gtk_mate_scanner_set_line_length (GtkMateScanner* self, gint value);
GtkMateScannerIterator* gtk_mate_scanner_iterator_construct (GType object_type, GType marker_type, GBoxedCopyFunc marker_dup_func, GDestroyNotify marker_destroy_func, GtkMateScanner* s);
GtkMateScannerIterator* gtk_mate_scanner_iterator_new (GType marker_type, GBoxedCopyFunc marker_dup_func, GDestroyNotify marker_destroy_func, GtkMateScanner* s);
GtkMateScanner* gtk_mate_scanner_iterator_get_scanner (GtkMateScannerIterator* self);
void gtk_mate_scanner_iterator_set_scanner (GtkMateScannerIterator* self, GtkMateScanner* value);
GType gtk_mate_scanner_iterator_get_type (void);
GType gtk_mate_scanner_get_type (void);


G_END_DECLS

#endif
