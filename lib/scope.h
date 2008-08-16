
#ifndef __SCOPE_H__
#define __SCOPE_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "pattern.h"
#include "onig_wrap.h"

G_BEGIN_DECLS

typedef struct _GtkMateScope GtkMateScope;
typedef struct _GtkMateScopeClass GtkMateScopeClass;
typedef struct _GtkMateBuffer GtkMateBuffer;
typedef struct _GtkMateBufferClass GtkMateBufferClass;
typedef struct _GtkMateTextLoc GtkMateTextLoc;
typedef struct _GtkMateParser GtkMateParser;
typedef struct _GtkMateParserClass GtkMateParserClass;
typedef struct _GtkMateMarker GtkMateMarker;
typedef struct _GtkMateMarkerClass GtkMateMarkerClass;
typedef struct _GtkMateScanner GtkMateScanner;
typedef struct _GtkMateScannerClass GtkMateScannerClass;
typedef struct _GtkMateScannerIterator GtkMateScannerIterator;
typedef struct _GtkMateScannerIteratorClass GtkMateScannerIteratorClass;

#define GTK_MATE_TYPE_SCOPE (gtk_mate_scope_get_type ())
#define GTK_MATE_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SCOPE, GtkMateScope))
#define GTK_MATE_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SCOPE, GtkMateScopeClass))
#define GTK_MATE_IS_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SCOPE))
#define GTK_MATE_IS_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SCOPE))
#define GTK_MATE_SCOPE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SCOPE, GtkMateScopeClass))

typedef struct _GtkMateScopePrivate GtkMateScopePrivate;

struct _GtkMateScope {
	GtkObject parent_instance;
	GtkMateScopePrivate * priv;
	GtkMatePattern* pattern;
	OnigurumaMatch* open_match;
	OnigurumaMatch* close_match;
	OnigurumaRegex* closing_regex;
	GtkTextMark* start_mark;
	GtkTextMark* inner_start_mark;
	GtkTextMark* inner_end_mark;
	GtkTextMark* end_mark;
	GtkTextTag* tag;
	GtkTextTag* inner_tag;
	gboolean is_open;
	char* bg_color;
	gboolean is_capture;
	GtkMateScope* parent;
	GString* pretty_string;
	gint indent;
};

struct _GtkMateScopeClass {
	GtkObjectClass parent_class;
};


GtkMateScope* gtk_mate_scope_new (GtkMateBuffer* buf, const char* name);
gboolean gtk_mate_scope_is_root (GtkMateScope* self);
gint gtk_mate_scope_compare (GtkMateScope* a, GtkMateScope* b);
char* gtk_mate_scope_pretty (GtkMateScope* self, gint indent);
void gtk_mate_scope_start_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity);
void gtk_mate_scope_inner_start_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity);
void gtk_mate_scope_inner_end_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity);
void gtk_mate_scope_end_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity);
gint gtk_mate_scope_start_offset (GtkMateScope* self);
gint gtk_mate_scope_end_offset (GtkMateScope* self);
const char* gtk_mate_scope_get_name (GtkMateScope* self);
void gtk_mate_scope_set_name (GtkMateScope* self, const char* value);
GtkMateBuffer* gtk_mate_scope_get_buffer (GtkMateScope* self);
void gtk_mate_scope_set_buffer (GtkMateScope* self, GtkMateBuffer* value);
GSequence* gtk_mate_scope_get_children (GtkMateScope* self);
GType gtk_mate_scope_get_type (void);


G_END_DECLS

#endif
