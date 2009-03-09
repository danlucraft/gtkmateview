
#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <glib.h>
#include <glib-object.h>
#include <gtksourceview/gtksourceview.h>
#include <gee/arraylist.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

G_BEGIN_DECLS

typedef struct _GtkMateBuffer GtkMateBuffer;
typedef struct _GtkMateBufferClass GtkMateBufferClass;
typedef struct _GtkMateTextLoc GtkMateTextLoc;
typedef struct _GtkMateTextLocClass GtkMateTextLocClass;
typedef struct _GtkMateParser GtkMateParser;
typedef struct _GtkMateParserClass GtkMateParserClass;
typedef struct _GtkMateThemeSetting GtkMateThemeSetting;
typedef struct _GtkMateThemeSettingClass GtkMateThemeSettingClass;
typedef struct _GtkMateTheme GtkMateTheme;
typedef struct _GtkMateThemeClass GtkMateThemeClass;
typedef struct _GtkMateScope GtkMateScope;
typedef struct _GtkMateScopeClass GtkMateScopeClass;
typedef struct _GtkMateColourer GtkMateColourer;
typedef struct _GtkMateColourerClass GtkMateColourerClass;
typedef struct _GtkMateView GtkMateView;
typedef struct _GtkMateViewClass GtkMateViewClass;

#define GTK_MATE_TYPE_BUFFER (gtk_mate_buffer_get_type ())
#define GTK_MATE_BUFFER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_BUFFER, GtkMateBuffer))
#define GTK_MATE_BUFFER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_BUFFER, GtkMateBufferClass))
#define GTK_MATE_IS_BUFFER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_BUFFER))
#define GTK_MATE_IS_BUFFER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_BUFFER))
#define GTK_MATE_BUFFER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_BUFFER, GtkMateBufferClass))

typedef struct _GtkMateBufferPrivate GtkMateBufferPrivate;

struct _GtkMateBuffer {
	GtkSourceBuffer parent_instance;
	GtkMateBufferPrivate * priv;
	GtkMateParser* parser;
};

struct _GtkMateBufferClass {
	GtkSourceBufferClass parent_class;
};


extern GeeArrayList* gtk_mate_buffer_bundles;
extern GeeArrayList* gtk_mate_buffer_themes;
gboolean gtk_mate_buffer_set_grammar_by_name (GtkMateBuffer* self, const char* name);
char* gtk_mate_buffer_set_grammar_by_filename (GtkMateBuffer* self, const char* filename);
char* gtk_mate_buffer_set_grammar_by_first_line (GtkMateBuffer* self, const char* first_line);
GtkTextIter gtk_mate_buffer_iter_ (GtkMateBuffer* self, gint offset);
GtkTextIter gtk_mate_buffer_start_iter (GtkMateBuffer* self);
GtkTextIter gtk_mate_buffer_end_iter (GtkMateBuffer* self);
GtkTextIter gtk_mate_buffer_cursor_iter (GtkMateBuffer* self);
GtkTextIter gtk_mate_buffer_iter_from_mark (GtkMateBuffer* self, GtkTextMark* mark);
GtkTextIter gtk_mate_buffer_iter_at_line_offset (GtkMateBuffer* self, gint line, gint line_offset);
GtkTextIter gtk_mate_buffer_iter_at_line_index (GtkMateBuffer* self, gint line, gint line_offset);
GtkTextIter gtk_mate_buffer_line_start_iter (GtkMateBuffer* self, gint line);
GtkTextIter gtk_mate_buffer_line_end_iter (GtkMateBuffer* self, gint line);
GtkTextIter gtk_mate_buffer_line_end_iter1 (GtkMateBuffer* self, gint line);
GtkTextMark* gtk_mate_buffer_start_mark (GtkMateBuffer* self);
GtkTextMark* gtk_mate_buffer_end_mark (GtkMateBuffer* self);
GtkTextMark* gtk_mate_buffer_cursor_mark (GtkMateBuffer* self);
GtkTextMark* gtk_mate_buffer_selection_mark (GtkMateBuffer* self);
char* gtk_mate_buffer_get_line (GtkMateBuffer* self, gint line);
char* gtk_mate_buffer_get_line1 (GtkMateBuffer* self, gint line_ix);
gint gtk_mate_buffer_get_line_length (GtkMateBuffer* self, gint line);
gint gtk_mate_buffer_cursor_line (GtkMateBuffer* self);
gint gtk_mate_buffer_cursor_line_offset (GtkMateBuffer* self);
gint gtk_mate_buffer_cursor_offset (GtkMateBuffer* self);
void gtk_mate_buffer_select_current_scope (GtkMateBuffer* self);
GeeArrayList* gtk_mate_buffer_current_scope_range (GtkMateBuffer* self);
GtkMateBuffer* gtk_mate_buffer_construct (GType object_type);
GtkMateBuffer* gtk_mate_buffer_new (void);
GType gtk_mate_buffer_get_type (void);


G_END_DECLS

#endif
