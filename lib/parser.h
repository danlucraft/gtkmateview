
#ifndef __PARSER_H__
#define __PARSER_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <scope.h>
#include <grammar.h>

G_BEGIN_DECLS

typedef struct _GtkMateTextLoc GtkMateTextLoc;
typedef struct _GtkMateChange GtkMateChange;
typedef struct _GtkMateParser GtkMateParser;
typedef struct _GtkMateParserClass GtkMateParserClass;
typedef struct _GtkMateBuffer GtkMateBuffer;
typedef struct _GtkMateBufferClass GtkMateBufferClass;

#define GTK_MATE_TYPE_CHANGE_TYPE (gtk_mate_change_type_get_type ())

#define GTK_MATE_TYPE_PARSER (gtk_mate_parser_get_type ())
#define GTK_MATE_PARSER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_PARSER, GtkMateParser))
#define GTK_MATE_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_PARSER, GtkMateParserClass))
#define GTK_MATE_IS_PARSER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_PARSER))
#define GTK_MATE_IS_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_PARSER))
#define GTK_MATE_PARSER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_PARSER, GtkMateParserClass))

typedef struct _GtkMateParserPrivate GtkMateParserPrivate;

typedef enum  {
	GTK_MATE_CHANGE_TYPE_INSERTION,
	GTK_MATE_CHANGE_TYPE_DELETION
} GtkMateChangeType;

struct _GtkMateTextLoc {
	gint line;
	gint line_offset;
};

struct _GtkMateChange {
	GtkMateChangeType type;
	gint line;
	gint num_lines;
};

struct _GtkMateParser {
	GtkObject parent_instance;
	GtkMateParserPrivate * priv;
	GtkMateScope* root;
	GQueue* changes;
	gint deactivation_level;
};

struct _GtkMateParserClass {
	GtkObjectClass parent_class;
};


GType gtk_mate_change_type_get_type (void);
GtkMateTextLoc gtk_mate_text_loc_make (gint l, gint lo);
extern GtkMateParser* gtk_mate_parser_current;
void gtk_mate_parser_make_root (GtkMateParser* self);
void gtk_mate_parser_stop_parsing (GtkMateParser* self);
void gtk_mate_parser_start_parsing (GtkMateParser* self);
gboolean gtk_mate_parser_is_parsing (GtkMateParser* self);
void gtk_mate_parser_connect_buffer_signals (GtkMateParser* self);
void gtk_mate_parser_insert_text_handler (GtkMateParser* self, GtkMateBuffer* bf, GtkTextIter* pos, const char* text, gint length);
void gtk_mate_parser_delete_range_handler (GtkMateParser* self, GtkMateBuffer* bf, GtkTextIter* pos, GtkTextIter* pos2);
void gtk_mate_parser_insert_text_after_handler (GtkMateParser* self, GtkMateBuffer* bf, GtkTextIter* pos, const char* text, gint length);
void gtk_mate_parser_delete_range_after_handler (GtkMateParser* self, GtkMateBuffer* bf, GtkTextIter* pos, GtkTextIter* pos2);
void gtk_mate_parser_static_insert_text_after_handler (GtkMateBuffer* bf, GtkTextIter* pos, const char* text, gint length);
void gtk_mate_parser_static_delete_range_after_handler (GtkMateBuffer* bf, GtkTextIter* pos, GtkTextIter* pos2);
GtkMateParser* gtk_mate_parser_create (GtkMateGrammar* grammar, GtkMateBuffer* buffer);
GtkMateParser* gtk_mate_parser_new (void);
GtkMateGrammar* gtk_mate_parser_get_grammar (GtkMateParser* self);
void gtk_mate_parser_set_grammar (GtkMateParser* self, GtkMateGrammar* value);
GtkMateBuffer* gtk_mate_parser_get_buffer (GtkMateParser* self);
void gtk_mate_parser_set_buffer (GtkMateParser* self, GtkMateBuffer* value);
GType gtk_mate_parser_get_type (void);


G_END_DECLS

#endif
