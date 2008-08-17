
#ifndef __PARSER_H__
#define __PARSER_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "scope.h"
#include "range_set.h"
#include "onig_wrap.h"
#include "grammar.h"

G_BEGIN_DECLS


#define GTK_MATE_TYPE_PARSER (gtk_mate_parser_get_type ())
#define GTK_MATE_PARSER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_PARSER, GtkMateParser))
#define GTK_MATE_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_PARSER, GtkMateParserClass))
#define GTK_MATE_IS_PARSER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_PARSER))
#define GTK_MATE_IS_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_PARSER))
#define GTK_MATE_PARSER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_PARSER, GtkMateParserClass))

typedef struct _GtkMateParserPrivate GtkMateParserPrivate;

struct _GtkMateTextLoc {
	gint line;
	gint line_offset;
};

struct _GtkMateParser {
	GtkObject parent_instance;
	GtkMateParserPrivate * priv;
	GtkMateScope* root;
	RangeSet* changes;
	gint deactivation_level;
};

struct _GtkMateParserClass {
	GtkObjectClass parent_class;
};


GtkMateTextLoc gtk_mate_text_loc_make (gint l, gint lo);
extern GtkMateParser* gtk_mate_parser_current;
void gtk_mate_parser_make_root (GtkMateParser* self);
void gtk_mate_parser_stop_parsing (GtkMateParser* self);
void gtk_mate_parser_start_parsing (GtkMateParser* self);
gboolean gtk_mate_parser_is_parsing (GtkMateParser* self);
void gtk_mate_parser_close_scope (GtkMateParser* self, GtkMateScanner* scanner, gint line_ix, GtkMateMarker* m);
void gtk_mate_parser_open_scope (GtkMateParser* self, GtkMateScanner* scanner, gint line_ix, gint length, GtkMateMarker* m);
void gtk_mate_parser_single_scope (GtkMateParser* self, GtkMateScanner* scanner, gint line_ix, gint length, GtkMateMarker* m);
void gtk_mate_parser_handle_captures (GtkMateParser* self, gint line_ix, GtkMateScope* scope, GtkMateMarker* m);
OnigurumaRegex* gtk_mate_parser_make_closing_regex (GtkMateParser* self, GtkMateScope* scope, GtkMateMarker* m);
void gtk_mate_parser_collect_child_captures (GtkMateParser* self, gint line_ix, GtkMateScope* scope, GtkMateMarker* m);
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
