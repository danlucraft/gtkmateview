
#ifndef __PARSER_H__
#define __PARSER_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <scope.h>
#include <buffer.h>
#include <grammar.h>

G_BEGIN_DECLS


#define GTK_MATE_TYPE_PARSER (gtk_mate_parser_get_type ())
#define GTK_MATE_PARSER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_PARSER, GtkMateParser))
#define GTK_MATE_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_PARSER, GtkMateParserClass))
#define GTK_MATE_IS_PARSER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_PARSER))
#define GTK_MATE_IS_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_PARSER))
#define GTK_MATE_PARSER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_PARSER, GtkMateParserClass))

typedef struct _GtkMateParserPrivate GtkMateParserPrivate;

struct _GtkMateParser {
	GtkObject parent_instance;
	GtkMateParserPrivate * priv;
	GtkMateScope* root;
};

struct _GtkMateParserClass {
	GtkObjectClass parent_class;
};


void gtk_mate_parser_make_root (GtkMateParser* self);
GtkMateParser* gtk_mate_parser_new (void);
GtkMateParser* gtk_mate_parser_create (GtkMateGrammar* grammar, GtkMateBuffer* buffer);
GtkMateGrammar* gtk_mate_parser_get_grammar (GtkMateParser* self);
void gtk_mate_parser_set_grammar (GtkMateParser* self, GtkMateGrammar* value);
GtkMateBuffer* gtk_mate_parser_get_buffer (GtkMateParser* self);
void gtk_mate_parser_set_buffer (GtkMateParser* self, GtkMateBuffer* value);
GType gtk_mate_parser_get_type (void);


G_END_DECLS

#endif
