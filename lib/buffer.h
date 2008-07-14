
#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <glib.h>
#include <glib-object.h>
#include <gtksourceview/gtksourceview.h>
#include <gee/arraylist.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <grammar.h>

G_BEGIN_DECLS


#define GTK_MATE_TYPE_BUFFER (gtk_mate_buffer_get_type ())
#define GTK_MATE_BUFFER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_BUFFER, GtkMateBuffer))
#define GTK_MATE_BUFFER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_BUFFER, GtkMateBufferClass))
#define GTK_MATE_IS_BUFFER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_BUFFER))
#define GTK_MATE_IS_BUFFER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_BUFFER))
#define GTK_MATE_BUFFER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_BUFFER, GtkMateBufferClass))

typedef struct _GtkMateBuffer GtkMateBuffer;
typedef struct _GtkMateBufferClass GtkMateBufferClass;
typedef struct _GtkMateBufferPrivate GtkMateBufferPrivate;

struct _GtkMateBuffer {
	GtkSourceBuffer parent_instance;
	GtkMateBufferPrivate * priv;
};

struct _GtkMateBufferClass {
	GtkSourceBufferClass parent_class;
};


extern GeeArrayList* gtk_mate_buffer_bundles;
extern GeeArrayList* gtk_mate_buffer_themes;
GeeArrayList* gtk_mate_buffer_all_bundles (GtkMateBuffer* self);
GeeArrayList* gtk_mate_buffer_all_themes (GtkMateBuffer* self);
char* gtk_mate_buffer_set_grammar_by_extension (GtkMateBuffer* self, const char* extension);
GtkTextIter gtk_mate_buffer_iter_ (GtkMateBuffer* self, gint offset);
GtkTextIter gtk_mate_buffer_iter_line_start (GtkMateBuffer* self, gint line);
GtkMateBuffer* gtk_mate_buffer_new (void);
GtkMateGrammar* gtk_mate_buffer_get_grammar (GtkMateBuffer* self);
void gtk_mate_buffer_set_grammar (GtkMateBuffer* self, GtkMateGrammar* value);
GType gtk_mate_buffer_get_type (void);


G_END_DECLS

#endif
