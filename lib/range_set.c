
#include "range_set.h"
#include <gee/collection.h>
#include <gee/list.h>




enum  {
	RANGE_SET_DUMMY_PROPERTY
};
static GType range_set_real_get_element_type (GeeIterable* base);
static GeeIterator* range_set_real_iterator (GeeIterable* base);
static GObject * range_set_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
enum  {
	RANGE_SET_RANGE_DUMMY_PROPERTY
};
static gpointer range_set_range_parent_class = NULL;
static void range_set_range_dispose (GObject * obj);
static gpointer range_set_parent_class = NULL;
static GeeIterableIface* range_set_gee_iterable_parent_iface = NULL;
static void range_set_dispose (GObject * obj);



gint range_set_length (RangeSet* self) {
	g_return_val_if_fail (IS_RANGE_SET (self), 0);
	return ((gint) (gee_collection_get_size (GEE_COLLECTION (self->ranges))));
}


gint range_set_size (RangeSet* self) {
	gint sizec;
	g_return_val_if_fail (IS_RANGE_SET (self), 0);
	sizec = 0;
	{
		GeeArrayList* p_collection;
		int p_it;
		p_collection = self->ranges;
		for (p_it = 0; p_it < gee_collection_get_size (GEE_COLLECTION (p_collection)); p_it = p_it + 1) {
			RangeSetRange* p;
			p = ((RangeSetRange*) (gee_list_get (GEE_LIST (p_collection), p_it)));
			{
				sizec = sizec + (p->b - p->a + 1);
				(p == NULL ? NULL : (p = (g_object_unref (p), NULL)));
			}
		}
	}
	return sizec;
}


gboolean range_set_is_empty (RangeSet* self) {
	g_return_val_if_fail (IS_RANGE_SET (self), FALSE);
	return (gee_collection_get_size (GEE_COLLECTION (self->ranges)) == 0);
}


void range_set_add (RangeSet* self, gint a, gint b) {
	gboolean merged;
	gint insert_ix;
	RangeSetRange* n;
	RangeSetRange* p;
	RangeSetRange* p2;
	g_return_if_fail (IS_RANGE_SET (self));
	merged = FALSE;
	insert_ix = 0;
	n = range_set_range_new ();
	n->a = a;
	n->b = b;
	p = NULL;
	p2 = NULL;
	{
		GeeArrayList* p_collection;
		int p_it;
		p_collection = self->ranges;
		for (p_it = 0; p_it < gee_collection_get_size (GEE_COLLECTION (p_collection)); p_it = p_it + 1) {
			RangeSetRange* p;
			p = ((RangeSetRange*) (gee_list_get (GEE_LIST (p_collection), p_it)));
			{
				if (p->a < n->a) {
					insert_ix++;
				}
				(p == NULL ? NULL : (p = (g_object_unref (p), NULL)));
			}
		}
	}
	gee_list_insert (GEE_LIST (self->ranges), insert_ix, n);
	range_set_merge (self, insert_ix);
	(n == NULL ? NULL : (n = (g_object_unref (n), NULL)));
	(p == NULL ? NULL : (p = (g_object_unref (p), NULL)));
	(p2 == NULL ? NULL : (p2 = (g_object_unref (p2), NULL)));
}


void range_set_merge (RangeSet* self, gint ix) {
	RangeSetRange* n;
	g_return_if_fail (IS_RANGE_SET (self));
	n = ((RangeSetRange*) (gee_list_get (((GeeList*) (self->ranges)), ix)));
	/* stdout.printf("merge(%d, %d..%d)\n", ix, n.a, n.b);*/
	if (ix > 0) {
		RangeSetRange* x;
		/* stdout.printf("ix > 0\n");*/
		x = ((RangeSetRange*) (gee_list_get (((GeeList*) (self->ranges)), ix - 1)));
		/* stdout.printf("x: %d..%d, n: %d..%d\n", x.a, x.b, n.a, n.b);*/
		if (n->a <= x->b + 1) {
			RangeSetRange* _tmp0;
			gee_list_remove_at (GEE_LIST (self->ranges), ix);
			x->b = range_set_max (self, x->b, n->b);
			gee_list_set (((GeeList*) (self->ranges)), ix - 1, x);
			ix--;
			_tmp0 = NULL;
			n = (_tmp0 = ((RangeSetRange*) (gee_list_get (((GeeList*) (self->ranges)), ix))), (n == NULL ? NULL : (n = (g_object_unref (n), NULL))), _tmp0);
		}
		(x == NULL ? NULL : (x = (g_object_unref (x), NULL)));
	}
	if (ix < gee_collection_get_size (GEE_COLLECTION (self->ranges)) - 1) {
		RangeSetRange* y;
		/* stdout.printf("ix < %d\n", ranges.size-1);*/
		y = ((RangeSetRange*) (gee_list_get (((GeeList*) (self->ranges)), ix + 1)));
		while (ix < gee_collection_get_size (GEE_COLLECTION (self->ranges)) - 1 && n->b >= y->a - 1) {
			/* stdout.printf("n: %d..%d, y: %d..%d\n", n.a, n.b, y.a, y.b);*/
			y->a = range_set_min (self, n->a, y->a);
			if (n->b > y->b) {
				y->b = n->b;
			}
			gee_list_set (((GeeList*) (self->ranges)), ix + 1, y);
			gee_list_remove_at (GEE_LIST (self->ranges), ix);
			if (ix < gee_collection_get_size (GEE_COLLECTION (self->ranges)) - 1) {
				RangeSetRange* _tmp1;
				_tmp1 = NULL;
				y = (_tmp1 = ((RangeSetRange*) (gee_list_get (((GeeList*) (self->ranges)), ix + 1))), (y == NULL ? NULL : (y = (g_object_unref (y), NULL))), _tmp1);
			}
		}
		(y == NULL ? NULL : (y = (g_object_unref (y), NULL)));
	}
	(n == NULL ? NULL : (n = (g_object_unref (n), NULL)));
}


char* range_set_present (RangeSet* self) {
	GString* sb;
	const char* _tmp3;
	char* _tmp4;
	g_return_val_if_fail (IS_RANGE_SET (self), NULL);
	sb = g_string_new ("");
	{
		GeeArrayList* p_collection;
		int p_it;
		p_collection = self->ranges;
		for (p_it = 0; p_it < gee_collection_get_size (GEE_COLLECTION (p_collection)); p_it = p_it + 1) {
			RangeSetRange* p;
			p = ((RangeSetRange*) (gee_list_get (GEE_LIST (p_collection), p_it)));
			{
				if (p->b - p->a == 0) {
					char* _tmp0;
					_tmp0 = NULL;
					g_string_append (sb, (_tmp0 = g_strdup_printf ("%i", p->a)));
					_tmp0 = (g_free (_tmp0), NULL);
					g_string_append (sb, ", ");
				} else {
					char* _tmp1;
					char* _tmp2;
					_tmp1 = NULL;
					g_string_append (sb, (_tmp1 = g_strdup_printf ("%i", p->a)));
					_tmp1 = (g_free (_tmp1), NULL);
					g_string_append (sb, "..");
					_tmp2 = NULL;
					g_string_append (sb, (_tmp2 = g_strdup_printf ("%i", p->b)));
					_tmp2 = (g_free (_tmp2), NULL);
					g_string_append (sb, ", ");
				}
				(p == NULL ? NULL : (p = (g_object_unref (p), NULL)));
			}
		}
	}
	_tmp3 = NULL;
	_tmp4 = NULL;
	return (_tmp4 = (_tmp3 = sb->str, (_tmp3 == NULL ? NULL : g_strdup (_tmp3))), (sb == NULL ? NULL : (sb = (g_string_free (sb, TRUE), NULL))), _tmp4);
}


gint range_set_max (RangeSet* self, gint a, gint b) {
	g_return_val_if_fail (IS_RANGE_SET (self), 0);
	if (a > b) {
		return a;
	} else {
		return b;
	}
}


gint range_set_min (RangeSet* self, gint a, gint b) {
	g_return_val_if_fail (IS_RANGE_SET (self), 0);
	if (a < b) {
		return a;
	} else {
		return b;
	}
}


RangeSet* range_set_new (void) {
	RangeSet * self;
	self = g_object_newv (TYPE_RANGE_SET, 0, NULL);
	return self;
}


static GType range_set_real_get_element_type (GeeIterable* base) {
	RangeSet * self;
	self = RANGE_SET (base);
	return RANGE_SET_TYPE_RANGE;
}


static GeeIterator* range_set_real_iterator (GeeIterable* base) {
	RangeSet * self;
	self = RANGE_SET (base);
	return gee_iterable_iterator (GEE_ITERABLE (self->ranges));
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
		GeeArrayList* _tmp0;
		_tmp0 = NULL;
		self->ranges = (_tmp0 = gee_array_list_new (RANGE_SET_TYPE_RANGE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal), (self->ranges == NULL ? NULL : (self->ranges = (g_object_unref (self->ranges), NULL))), _tmp0);
	}
	return obj;
}


RangeSetRange* range_set_range_new (void) {
	RangeSetRange * self;
	self = g_object_newv (RANGE_SET_TYPE_RANGE, 0, NULL);
	return self;
}


static void range_set_range_class_init (RangeSetRangeClass * klass) {
	range_set_range_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->dispose = range_set_range_dispose;
}


static void range_set_range_instance_init (RangeSetRange * self) {
}


static void range_set_range_dispose (GObject * obj) {
	RangeSetRange * self;
	self = RANGE_SET_RANGE (obj);
	G_OBJECT_CLASS (range_set_range_parent_class)->dispose (obj);
}


GType range_set_range_get_type (void) {
	static GType range_set_range_type_id = 0;
	if (G_UNLIKELY (range_set_range_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (RangeSetRangeClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) range_set_range_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RangeSetRange), 0, (GInstanceInitFunc) range_set_range_instance_init };
		range_set_range_type_id = g_type_register_static (G_TYPE_OBJECT, "RangeSetRange", &g_define_type_info, 0);
	}
	return range_set_range_type_id;
}


static void range_set_class_init (RangeSetClass * klass) {
	range_set_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = range_set_constructor;
	G_OBJECT_CLASS (klass)->dispose = range_set_dispose;
}


static void range_set_gee_iterable_interface_init (GeeIterableIface * iface) {
	range_set_gee_iterable_parent_iface = g_type_interface_peek_parent (iface);
	iface->get_element_type = range_set_real_get_element_type;
	iface->iterator = range_set_real_iterator;
}


static void range_set_instance_init (RangeSet * self) {
}


static void range_set_dispose (GObject * obj) {
	RangeSet * self;
	self = RANGE_SET (obj);
	(self->ranges == NULL ? NULL : (self->ranges = (g_object_unref (self->ranges), NULL)));
	G_OBJECT_CLASS (range_set_parent_class)->dispose (obj);
}


GType range_set_get_type (void) {
	static GType range_set_type_id = 0;
	if (G_UNLIKELY (range_set_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (RangeSetClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) range_set_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RangeSet), 0, (GInstanceInitFunc) range_set_instance_init };
		static const GInterfaceInfo gee_iterable_info = { (GInterfaceInitFunc) range_set_gee_iterable_interface_init, (GInterfaceFinalizeFunc) NULL, NULL};
		range_set_type_id = g_type_register_static (G_TYPE_OBJECT, "RangeSet", &g_define_type_info, 0);
		g_type_add_interface_static (range_set_type_id, GEE_TYPE_ITERABLE, &gee_iterable_info);
	}
	return range_set_type_id;
}




