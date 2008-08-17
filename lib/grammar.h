
#ifndef __GRAMMAR_H__
#define __GRAMMAR_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>
#include <gee/hashmap.h>
#include "onig_wrap.h"
#include "plist.h"

G_BEGIN_DECLS


#define GTK_MATE_TYPE_GRAMMAR (gtk_mate_grammar_get_type ())
#define GTK_MATE_GRAMMAR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammar))
#define GTK_MATE_GRAMMAR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammarClass))
#define GTK_MATE_IS_GRAMMAR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_GRAMMAR))
#define GTK_MATE_IS_GRAMMAR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_GRAMMAR))
#define GTK_MATE_GRAMMAR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammarClass))

typedef struct _GtkMateGrammar GtkMateGrammar;
typedef struct _GtkMateGrammarClass GtkMateGrammarClass;
typedef struct _GtkMateGrammarPrivate GtkMateGrammarPrivate;

struct _GtkMateGrammar {
	GtkObject parent_instance;
	GtkMateGrammarPrivate * priv;
	char** file_types;
	gint file_types_length1;
	OnigurumaRegex* first_line_match;
	char* key_equivalent;
	char* scope_name;
	char* comment;
	GeeArrayList* all_patterns;
	OnigurumaRegex* folding_start_marker;
	OnigurumaRegex* folding_stop_marker;
	GeeArrayList* patterns;
	GeeHashMap* repository;
	gboolean loaded;
};

struct _GtkMateGrammarClass {
	GtkObjectClass parent_class;
};


GtkMateGrammar* gtk_mate_grammar_new (PListDict* plist);
GtkMateGrammar* gtk_mate_grammar_find_by_scope_name (const char* scope);
void gtk_mate_grammar_init_for_reference (GtkMateGrammar* self);
void gtk_mate_grammar_init_for_use (GtkMateGrammar* self);
const char* gtk_mate_grammar_get_name (GtkMateGrammar* self);
PListDict* gtk_mate_grammar_get_plist (GtkMateGrammar* self);
GType gtk_mate_grammar_get_type (void);


G_END_DECLS

#endif
