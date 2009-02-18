
#ifndef __PATTERN_H__
#define __PATTERN_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>
#include <gee/hashmap.h>
#include "plist.h"
#include "onig_wrap.h"
#include "grammar.h"

G_BEGIN_DECLS


#define GTK_MATE_TYPE_PATTERN (gtk_mate_pattern_get_type ())
#define GTK_MATE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_PATTERN, GtkMatePattern))
#define GTK_MATE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_PATTERN, GtkMatePatternClass))
#define GTK_MATE_IS_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_PATTERN))
#define GTK_MATE_IS_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_PATTERN))
#define GTK_MATE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_PATTERN, GtkMatePatternClass))

typedef struct _GtkMatePattern GtkMatePattern;
typedef struct _GtkMatePatternClass GtkMatePatternClass;
typedef struct _GtkMatePatternPrivate GtkMatePatternPrivate;

#define GTK_MATE_TYPE_SINGLE_PATTERN (gtk_mate_single_pattern_get_type ())
#define GTK_MATE_SINGLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePattern))
#define GTK_MATE_SINGLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePatternClass))
#define GTK_MATE_IS_SINGLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SINGLE_PATTERN))
#define GTK_MATE_IS_SINGLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SINGLE_PATTERN))
#define GTK_MATE_SINGLE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePatternClass))

typedef struct _GtkMateSinglePattern GtkMateSinglePattern;
typedef struct _GtkMateSinglePatternClass GtkMateSinglePatternClass;
typedef struct _GtkMateSinglePatternPrivate GtkMateSinglePatternPrivate;

#define GTK_MATE_TYPE_DOUBLE_PATTERN (gtk_mate_double_pattern_get_type ())
#define GTK_MATE_DOUBLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePattern))
#define GTK_MATE_DOUBLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePatternClass))
#define GTK_MATE_IS_DOUBLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN))
#define GTK_MATE_IS_DOUBLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_DOUBLE_PATTERN))
#define GTK_MATE_DOUBLE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePatternClass))

typedef struct _GtkMateDoublePattern GtkMateDoublePattern;
typedef struct _GtkMateDoublePatternClass GtkMateDoublePatternClass;
typedef struct _GtkMateDoublePatternPrivate GtkMateDoublePatternPrivate;

#define GTK_MATE_TYPE_INCLUDE_PATTERN (gtk_mate_include_pattern_get_type ())
#define GTK_MATE_INCLUDE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_INCLUDE_PATTERN, GtkMateIncludePattern))
#define GTK_MATE_INCLUDE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_INCLUDE_PATTERN, GtkMateIncludePatternClass))
#define GTK_MATE_IS_INCLUDE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_INCLUDE_PATTERN))
#define GTK_MATE_IS_INCLUDE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_INCLUDE_PATTERN))
#define GTK_MATE_INCLUDE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_INCLUDE_PATTERN, GtkMateIncludePatternClass))

typedef struct _GtkMateIncludePattern GtkMateIncludePattern;
typedef struct _GtkMateIncludePatternClass GtkMateIncludePatternClass;
typedef struct _GtkMateIncludePatternPrivate GtkMateIncludePatternPrivate;

struct _GtkMatePattern {
	GtkObject parent_instance;
	GtkMatePatternPrivate * priv;
	char* name;
	char* comment;
	gboolean disabled;
};

struct _GtkMatePatternClass {
	GtkObjectClass parent_class;
};

struct _GtkMateSinglePattern {
	GtkMatePattern parent_instance;
	GtkMateSinglePatternPrivate * priv;
	OnigRx* match;
	GeeHashMap* captures;
};

struct _GtkMateSinglePatternClass {
	GtkMatePatternClass parent_class;
};

struct _GtkMateDoublePattern {
	GtkMatePattern parent_instance;
	GtkMateDoublePatternPrivate * priv;
	char* content_name;
	OnigRx* begin;
	OnigRx* end;
	char* end_string;
	char* begin_string;
	GeeHashMap* begin_captures;
	GeeHashMap* end_captures;
	GeeHashMap* both_captures;
	GeeArrayList* patterns;
};

struct _GtkMateDoublePatternClass {
	GtkMatePatternClass parent_class;
};

struct _GtkMateIncludePattern {
	GtkMatePattern parent_instance;
	GtkMateIncludePatternPrivate * priv;
};

struct _GtkMateIncludePatternClass {
	GtkMatePatternClass parent_class;
};


extern GeeArrayList* gtk_mate_pattern_all_patterns;
GtkMatePattern* gtk_mate_pattern_create_from_plist (GeeArrayList* all_patterns, PListDict* pd);
GeeHashMap* gtk_mate_pattern_make_captures_from_plist (PListDict* pd);
void gtk_mate_pattern_replace_include_patterns (GeeArrayList* patlist, GtkMateGrammar* g);
void gtk_mate_pattern_replace_repository_includes (GeeArrayList* patlist, GtkMateGrammar* g);
void gtk_mate_pattern_replace_base_and_self_includes (GeeArrayList* patlist, GtkMateGrammar* g);
GtkMatePattern* gtk_mate_pattern_construct (GType object_type);
GtkMatePattern* gtk_mate_pattern_new (void);
GtkMateGrammar* gtk_mate_pattern_get_grammar (GtkMatePattern* self);
void gtk_mate_pattern_set_grammar (GtkMatePattern* self, GtkMateGrammar* value);
GType gtk_mate_pattern_get_type (void);
GtkMateSinglePattern* gtk_mate_single_pattern_create_from_plist (GeeArrayList* all_patterns, PListDict* pd);
GtkMateSinglePattern* gtk_mate_single_pattern_construct (GType object_type);
GtkMateSinglePattern* gtk_mate_single_pattern_new (void);
GType gtk_mate_single_pattern_get_type (void);
GtkMateDoublePattern* gtk_mate_double_pattern_create_from_plist (GeeArrayList* all_patterns, PListDict* pd);
GtkMateDoublePattern* gtk_mate_double_pattern_construct (GType object_type);
GtkMateDoublePattern* gtk_mate_double_pattern_new (void);
GType gtk_mate_double_pattern_get_type (void);
GtkMateIncludePattern* gtk_mate_include_pattern_create_from_plist (PListDict* pd);
GtkMateIncludePattern* gtk_mate_include_pattern_construct (GType object_type);
GtkMateIncludePattern* gtk_mate_include_pattern_new (void);
GType gtk_mate_include_pattern_get_type (void);


G_END_DECLS

#endif
