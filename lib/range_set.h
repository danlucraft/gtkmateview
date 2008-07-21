
#ifndef __RANGE_SET_H__
#define __RANGE_SET_H__

#include <glib.h>
#include <glib-object.h>
#include <gee/arraylist.h>
#include <stdlib.h>
#include <string.h>

G_BEGIN_DECLS


#define TYPE_RANGE_SET (range_set_get_type ())
#define RANGE_SET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_RANGE_SET, RangeSet))
#define RANGE_SET_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_RANGE_SET, RangeSetClass))
#define IS_RANGE_SET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_RANGE_SET))
#define IS_RANGE_SET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_RANGE_SET))
#define RANGE_SET_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_RANGE_SET, RangeSetClass))

typedef struct _RangeSet RangeSet;
typedef struct _RangeSetClass RangeSetClass;
typedef struct _RangeSetPrivate RangeSetPrivate;
typedef struct _RangeSetIntPair RangeSetIntPair;

/* This data structure stores sets of ranges 
 like 1, 4-8, 10, 12, 15-20*/
struct _RangeSet {
	GObject parent_instance;
	RangeSetPrivate * priv;
	GeeArrayList* ranges;
};

struct _RangeSetClass {
	GObjectClass parent_class;
};

struct _RangeSetIntPair {
	gint a;
	gint b;
};


gint range_set_length (RangeSet* self);
gint range_set_size (RangeSet* self);
gboolean range_set_is_empty (RangeSet* self);
void range_set_add (RangeSet* self, gint a, gint b);
void range_set_merge (RangeSet* self, gint ix);
char* range_set_present (RangeSet* self);
gint range_set_max (RangeSet* self, gint a, gint b);
gint range_set_min (RangeSet* self, gint a, gint b);
RangeSet* range_set_new (void);
void range_set_int_pair_init (RangeSetIntPair *self, gint x, gint y);
GType range_set_get_type (void);


G_END_DECLS

#endif
