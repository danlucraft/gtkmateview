
#ifndef __RANGE_SET_H__
#define __RANGE_SET_H__

#include <glib.h>
#include <glib-object.h>
#include <gee/iterable.h>
#include <gee/arraylist.h>
#include <stdlib.h>
#include <string.h>
#include <gee/iterator.h>

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

#define RANGE_SET_TYPE_RANGE (range_set_range_get_type ())
#define RANGE_SET_RANGE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RANGE_SET_TYPE_RANGE, RangeSetRange))
#define RANGE_SET_RANGE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RANGE_SET_TYPE_RANGE, RangeSetRangeClass))
#define RANGE_SET_IS_RANGE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RANGE_SET_TYPE_RANGE))
#define RANGE_SET_IS_RANGE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RANGE_SET_TYPE_RANGE))
#define RANGE_SET_RANGE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RANGE_SET_TYPE_RANGE, RangeSetRangeClass))

typedef struct _RangeSetRange RangeSetRange;
typedef struct _RangeSetRangeClass RangeSetRangeClass;
typedef struct _RangeSetRangePrivate RangeSetRangePrivate;

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

struct _RangeSetRange {
	GObject parent_instance;
	RangeSetRangePrivate * priv;
	gint a;
	gint b;
};

struct _RangeSetRangeClass {
	GObjectClass parent_class;
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
RangeSetRange* range_set_range_new (void);
GType range_set_range_get_type (void);
GType range_set_get_type (void);


G_END_DECLS

#endif
