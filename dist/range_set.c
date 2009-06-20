
#include <glib.h>
#include <glib-object.h>
#include <gee/iterable.h>
#include <gee/arraylist.h>
#include <gee/collection.h>
#include <gee/iterator.h>
#include <gee/list.h>
#include <stdlib.h>
#include <string.h>


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



GType range_set_get_type (void);
GType range_set_range_get_type (void);
enum  {
	RANGE_SET_DUMMY_PROPERTY
};
gint range_set_length (RangeSet* self);
gint range_set_size (RangeSet* self);
gboolean range_set_is_empty (RangeSet* self);
RangeSetRange* range_set_range_new (void);
RangeSetRange* range_set_range_construct (GType object_type);
void range_set_merge (RangeSet* self, gint ix);
void range_set_add (RangeSet* self, gint a, gint b);
gint range_set_max (RangeSet* self, gint a, gint b);
gint range_set_min (RangeSet* self, gint a, gint b);
char* range_set_present (RangeSet* self);
RangeSet* range_set_new (void);
RangeSet* range_set_construct (GType object_type);
RangeSet* range_set_new (void);
static GType range_set_real_get_element_type (GeeIterable* base);
static GeeIterator* range_set_real_iterator (GeeIterable* base);
static GObject * range_set_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
enum  {
	RANGE_SET_RANGE_DUMMY_PROPERTY
};
RangeSetRange* range_set_range_new (void);
static gpointer range_set_range_parent_class = NULL;
static void range_set_range_finalize (GObject* obj);
static gpointer range_set_parent_class = NULL;
static GeeIterableIface* range_set_gee_iterable_parent_iface = NULL;
static void range_set_finalize (GObject* obj);



gint range_set_length (RangeSet* self) {
	g_return_val_if_fail (self != NULL, 0);
	return (gint) gee_collection_get_size ((GeeCollection*) self->ranges);
}


gint range_set_size (RangeSet* self) {
	gint sizec;
	g_return_val_if_fail (self != NULL, 0);
	sizec = 0;
	{
		GeeIterator* _p_it;
		_p_it = gee_iterable_iterator ((GeeIterable*) self->ranges);
		while (gee_iterator_next (_p_it)) {
			RangeSetRange* p;
			p = (RangeSetRange*) gee_iterator_get (_p_it);
			sizec = sizec + ((p->b - p->a) + 1);
			(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
		}
		(_p_it == NULL) ? NULL : (_p_it = (g_object_unref (_p_it), NULL));
	}
	return sizec;
}


gboolean range_set_is_empty (RangeSet* self) {
	g_return_val_if_fail (self != NULL, FALSE);
	return gee_collection_get_size ((GeeCollection*) self->ranges) == 0;
}


void range_set_add (RangeSet* self, gint a, gint b) {
	gint insert_ix;
	RangeSetRange* n;
	g_return_if_fail (self != NULL);
	insert_ix = 0;
	n = range_set_range_new ();
	n->a = a;
	n->b = b;
	{
		GeeIterator* _p_it;
		_p_it = gee_iterable_iterator ((GeeIterable*) self->ranges);
		while (gee_iterator_next (_p_it)) {
			RangeSetRange* p;
			p = (RangeSetRange*) gee_iterator_get (_p_it);
			if (p->a < n->a) {
				insert_ix++;
			}
			(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
		}
		(_p_it == NULL) ? NULL : (_p_it = (g_object_unref (_p_it), NULL));
	}
	gee_list_insert ((GeeList*) self->ranges, insert_ix, n);
	range_set_merge (self, insert_ix);
	(n == NULL) ? NULL : (n = (g_object_unref (n), NULL));
}


void range_set_merge (RangeSet* self, gint ix) {
	RangeSetRange* n;
	g_return_if_fail (self != NULL);
	n = (RangeSetRange*) gee_list_get ((GeeList*) self->ranges, ix);
	/* stdout.printf("merge(%d, %d..%d)\n", ix, n.a, n.b);*/
	if (ix > 0) {
		RangeSetRange* x;
		/* stdout.printf("ix > 0\n");*/
		x = (RangeSetRange*) gee_list_get ((GeeList*) self->ranges, ix - 1);
		/* stdout.printf("x: %d..%d, n: %d..%d\n", x.a, x.b, n.a, n.b);*/
		if (n->a <= (x->b + 1)) {
			RangeSetRange* _tmp0_;
			gee_list_remove_at ((GeeList*) self->ranges, ix);
			x->b = range_set_max (self, x->b, n->b);
			gee_list_set ((GeeList*) self->ranges, ix - 1, x);
			ix--;
			_tmp0_ = NULL;
			n = (_tmp0_ = (RangeSetRange*) gee_list_get ((GeeList*) self->ranges, ix), (n == NULL) ? NULL : (n = (g_object_unref (n), NULL)), _tmp0_);
		}
		(x == NULL) ? NULL : (x = (g_object_unref (x), NULL));
	}
	if (ix < (gee_collection_get_size ((GeeCollection*) self->ranges) - 1)) {
		RangeSetRange* y;
		/* stdout.printf("ix < %d\n", ranges.size-1);*/
		y = (RangeSetRange*) gee_list_get ((GeeList*) self->ranges, ix + 1);
		while (TRUE) {
			gboolean _tmp1_;
			_tmp1_ = FALSE;
			if (ix < (gee_collection_get_size ((GeeCollection*) self->ranges) - 1)) {
				_tmp1_ = n->b >= (y->a - 1);
			} else {
				_tmp1_ = FALSE;
			}
			if (!_tmp1_) {
				break;
			}
			/* stdout.printf("n: %d..%d, y: %d..%d\n", n.a, n.b, y.a, y.b);*/
			y->a = range_set_min (self, n->a, y->a);
			if (n->b > y->b) {
				y->b = n->b;
			}
			gee_list_set ((GeeList*) self->ranges, ix + 1, y);
			gee_list_remove_at ((GeeList*) self->ranges, ix);
			if (ix < (gee_collection_get_size ((GeeCollection*) self->ranges) - 1)) {
				RangeSetRange* _tmp2_;
				_tmp2_ = NULL;
				y = (_tmp2_ = (RangeSetRange*) gee_list_get ((GeeList*) self->ranges, ix + 1), (y == NULL) ? NULL : (y = (g_object_unref (y), NULL)), _tmp2_);
			}
		}
		(y == NULL) ? NULL : (y = (g_object_unref (y), NULL));
	}
	(n == NULL) ? NULL : (n = (g_object_unref (n), NULL));
}


char* range_set_present (RangeSet* self) {
	GString* sb;
	const char* _tmp3_;
	char* _tmp4_;
	g_return_val_if_fail (self != NULL, NULL);
	sb = g_string_new ("");
	{
		GeeIterator* _p_it;
		_p_it = gee_iterable_iterator ((GeeIterable*) self->ranges);
		while (gee_iterator_next (_p_it)) {
			RangeSetRange* p;
			p = (RangeSetRange*) gee_iterator_get (_p_it);
			if ((p->b - p->a) == 0) {
				char* _tmp0_;
				_tmp0_ = NULL;
				g_string_append (sb, _tmp0_ = g_strdup_printf ("%i", p->a));
				_tmp0_ = (g_free (_tmp0_), NULL);
				g_string_append (sb, ", ");
			} else {
				char* _tmp1_;
				char* _tmp2_;
				_tmp1_ = NULL;
				g_string_append (sb, _tmp1_ = g_strdup_printf ("%i", p->a));
				_tmp1_ = (g_free (_tmp1_), NULL);
				g_string_append (sb, "..");
				_tmp2_ = NULL;
				g_string_append (sb, _tmp2_ = g_strdup_printf ("%i", p->b));
				_tmp2_ = (g_free (_tmp2_), NULL);
				g_string_append (sb, ", ");
			}
			(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
		}
		(_p_it == NULL) ? NULL : (_p_it = (g_object_unref (_p_it), NULL));
	}
	_tmp3_ = NULL;
	_tmp4_ = NULL;
	return (_tmp4_ = (_tmp3_ = sb->str, (_tmp3_ == NULL) ? NULL : g_strdup (_tmp3_)), (sb == NULL) ? NULL : (sb = (g_string_free (sb, TRUE), NULL)), _tmp4_);
}


gint range_set_max (RangeSet* self, gint a, gint b) {
	g_return_val_if_fail (self != NULL, 0);
	if (a > b) {
		return a;
	} else {
		return b;
	}
}


gint range_set_min (RangeSet* self, gint a, gint b) {
	g_return_val_if_fail (self != NULL, 0);
	if (a < b) {
		return a;
	} else {
		return b;
	}
}


RangeSet* range_set_construct (GType object_type) {
	RangeSet * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


RangeSet* range_set_new (void) {
	return range_set_construct (TYPE_RANGE_SET);
}


static GType range_set_real_get_element_type (GeeIterable* base) {
	RangeSet * self;
	self = (RangeSet*) base;
	return RANGE_SET_TYPE_RANGE;
}


static GeeIterator* range_set_real_iterator (GeeIterable* base) {
	RangeSet * self;
	self = (RangeSet*) base;
	return gee_iterable_iterator ((GeeIterable*) self->ranges);
}


static GObject * range_set_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	RangeSetClass * klass;
	GObjectClass * parent_class;
	RangeSet * self;
	klass = RANGE_SET_CLASS (g_type_class_peek (TYPE_RANGE_SET));
	parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = RANGE_SET (obj);
	{
		GeeArrayList* _tmp0_;
		_tmp0_ = NULL;
		self->ranges = (_tmp0_ = gee_array_list_new (RANGE_SET_TYPE_RANGE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->ranges == NULL) ? NULL : (self->ranges = (g_object_unref (self->ranges), NULL)), _tmp0_);
	}
	return obj;
}


RangeSetRange* range_set_range_construct (GType object_type) {
	RangeSetRange * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


RangeSetRange* range_set_range_new (void) {
	return range_set_range_construct (RANGE_SET_TYPE_RANGE);
}


static void range_set_range_class_init (RangeSetRangeClass * klass) {
	range_set_range_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = range_set_range_finalize;
}


static void range_set_range_instance_init (RangeSetRange * self) {
}


static void range_set_range_finalize (GObject* obj) {
	RangeSetRange * self;
	self = RANGE_SET_RANGE (obj);
	G_OBJECT_CLASS (range_set_range_parent_class)->finalize (obj);
}


GType range_set_range_get_type (void) {
	static GType range_set_range_type_id = 0;
	if (range_set_range_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RangeSetRangeClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) range_set_range_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RangeSetRange), 0, (GInstanceInitFunc) range_set_range_instance_init, NULL };
		range_set_range_type_id = g_type_register_static (G_TYPE_OBJECT, "RangeSetRange", &g_define_type_info, 0);
	}
	return range_set_range_type_id;
}


static void range_set_class_init (RangeSetClass * klass) {
	range_set_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = range_set_constructor;
	G_OBJECT_CLASS (klass)->finalize = range_set_finalize;
}


static void range_set_gee_iterable_interface_init (GeeIterableIface * iface) {
	range_set_gee_iterable_parent_iface = g_type_interface_peek_parent (iface);
	iface->get_element_type = range_set_real_get_element_type;
	iface->iterator = range_set_real_iterator;
}


static void range_set_instance_init (RangeSet * self) {
}


static void range_set_finalize (GObject* obj) {
	RangeSet * self;
	self = RANGE_SET (obj);
	(self->ranges == NULL) ? NULL : (self->ranges = (g_object_unref (self->ranges), NULL));
	G_OBJECT_CLASS (range_set_parent_class)->finalize (obj);
}


GType range_set_get_type (void) {
	static GType range_set_type_id = 0;
	if (range_set_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RangeSetClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) range_set_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RangeSet), 0, (GInstanceInitFunc) range_set_instance_init, NULL };
		static const GInterfaceInfo gee_iterable_info = { (GInterfaceInitFunc) range_set_gee_iterable_interface_init, (GInterfaceFinalizeFunc) NULL, NULL};
		range_set_type_id = g_type_register_static (G_TYPE_OBJECT, "RangeSet", &g_define_type_info, 0);
		g_type_add_interface_static (range_set_type_id, GEE_TYPE_ITERABLE, &gee_iterable_info);
	}
	return range_set_type_id;
}




