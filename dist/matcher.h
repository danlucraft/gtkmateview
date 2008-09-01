
#ifndef __MATCHER_H__
#define __MATCHER_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <gee/arraylist.h>
#include <stdlib.h>
#include <string.h>
#include "onig_wrap.h"

G_BEGIN_DECLS


#define GTK_MATE_TYPE_MATCHER (gtk_mate_matcher_get_type ())
#define GTK_MATE_MATCHER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_MATCHER, GtkMateMatcher))
#define GTK_MATE_MATCHER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_MATCHER, GtkMateMatcherClass))
#define GTK_MATE_IS_MATCHER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_MATCHER))
#define GTK_MATE_IS_MATCHER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_MATCHER))
#define GTK_MATE_MATCHER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_MATCHER, GtkMateMatcherClass))

typedef struct _GtkMateMatcher GtkMateMatcher;
typedef struct _GtkMateMatcherClass GtkMateMatcherClass;
typedef struct _GtkMateMatcherPrivate GtkMateMatcherPrivate;

struct _GtkMateMatcher {
	GtkObject parent_instance;
	GtkMateMatcherPrivate * priv;
	OnigurumaRegex* pos_rx;
	GeeArrayList* neg_rxs;
};

struct _GtkMateMatcherClass {
	GtkObjectClass parent_class;
};


gint gtk_mate_matcher_compare_match (const char* scope_string, OnigurumaMatch* m1, OnigurumaMatch* m2);
char* gtk_mate_matcher_test_rank (const char* selector_a, const char* selector_b, const char* scope_string);
gboolean gtk_mate_matcher_test_match (const char* selector_string, const char* scope_string);
gboolean gtk_mate_matcher_match (const char* selector_string, const char* scope_string, OnigurumaMatch** match);
GeeArrayList* gtk_mate_matcher_compile (const char* selector_string);
gboolean gtk_mate_matcher_test_match_re (OnigurumaRegex* positive_selector_regex, GeeArrayList* negative_selector_regex, const char* scope_string, OnigurumaMatch** match);
GtkMateMatcher* gtk_mate_matcher_new (void);
GType gtk_mate_matcher_get_type (void);


G_END_DECLS

#endif
