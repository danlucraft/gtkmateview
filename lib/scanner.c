
#include "scanner.h"
#include <stdio.h>
#include <gee/collection.h>




enum  {
	GTK_MATE_MARKER_DUMMY_PROPERTY
};
static gpointer gtk_mate_marker_parent_class = NULL;
static void gtk_mate_marker_dispose (GObject * obj);
struct _GtkMateScannerPrivate {
	GtkMateScope* _current_scope;
	char* _line;
	gint _line_length;
};

#define GTK_MATE_SCANNER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_TYPE_SCANNER, GtkMateScannerPrivate))
enum  {
	GTK_MATE_SCANNER_DUMMY_PROPERTY,
	GTK_MATE_SCANNER_CURRENT_SCOPE,
	GTK_MATE_SCANNER_LINE,
	GTK_MATE_SCANNER_LINE_LENGTH
};
static GType gtk_mate_scanner_real_get_element_type (GeeIterable* base);
static GeeIterator* gtk_mate_scanner_real_iterator (GeeIterable* base);
static void gtk_mate_scanner_updated_current_scope (GtkMateScanner* self);
static GObject * gtk_mate_scanner_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
struct _GtkMateScannerIteratorPrivate {
	GtkMateScanner* _scanner;
	GType marker_type;
	GBoxedCopyFunc marker_dup_func;
	GDestroyNotify marker_destroy_func;
};

#define GTK_MATE_SCANNER_ITERATOR_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_SCANNER_TYPE_ITERATOR, GtkMateScannerIteratorPrivate))
enum  {
	GTK_MATE_SCANNER_ITERATOR_DUMMY_PROPERTY,
	GTK_MATE_SCANNER_ITERATOR_SCANNER,
	GTK_MATE_SCANNER_ITERATOR_MARKER_TYPE,
	GTK_MATE_SCANNER_ITERATOR_MARKER_DUP_FUNC,
	GTK_MATE_SCANNER_ITERATOR_MARKER_DESTROY_FUNC
};
static gboolean gtk_mate_scanner_iterator_real_next (GeeIterator* base);
static gpointer gtk_mate_scanner_iterator_real_get (GeeIterator* base);
static GObject * gtk_mate_scanner_iterator_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer gtk_mate_scanner_iterator_parent_class = NULL;
static GeeIteratorIface* gtk_mate_scanner_iterator_gee_iterator_parent_iface = NULL;
static void gtk_mate_scanner_iterator_dispose (GObject * obj);
static gpointer gtk_mate_scanner_parent_class = NULL;
static GeeIterableIface* gtk_mate_scanner_gee_iterable_parent_iface = NULL;
static void gtk_mate_scanner_dispose (GObject * obj);



/* The Scanner returns these to indicate successful pattern matches in a line.*/
GtkMateMarker* gtk_mate_marker_new (void) {
	GtkMateMarker * self;
	self = g_object_newv (GTK_MATE_TYPE_MARKER, 0, NULL);
	return self;
}


static void gtk_mate_marker_class_init (GtkMateMarkerClass * klass) {
	gtk_mate_marker_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->dispose = gtk_mate_marker_dispose;
}


static void gtk_mate_marker_instance_init (GtkMateMarker * self) {
}


static void gtk_mate_marker_dispose (GObject * obj) {
	GtkMateMarker * self;
	self = GTK_MATE_MARKER (obj);
	(self->pattern == NULL ? NULL : (self->pattern = (g_object_unref (self->pattern), NULL)));
	(self->match == NULL ? NULL : (self->match = (g_object_unref (self->match), NULL)));
	G_OBJECT_CLASS (gtk_mate_marker_parent_class)->dispose (obj);
}


GType gtk_mate_marker_get_type (void) {
	static volatile gsize gtk_mate_marker_type_id = 0;
	if (g_once_init_enter (&gtk_mate_marker_type_id)) {
		GType gtk_mate_marker_type_id_temp;
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateMarkerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_marker_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateMarker), 0, (GInstanceInitFunc) gtk_mate_marker_instance_init };
		gtk_mate_marker_type_id_temp = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateMarker", &g_define_type_info, 0);
		g_once_init_leave (&gtk_mate_marker_type_id, gtk_mate_marker_type_id_temp);
	}
	return gtk_mate_marker_type_id;
}


GtkMateScanner* gtk_mate_scanner_new (GtkMateScope* s, const char* line, gint line_length) {
	GtkMateScanner * self;
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (s), NULL);
	g_return_val_if_fail (line != NULL, NULL);
	self = g_object_newv (GTK_MATE_TYPE_SCANNER, 0, NULL);
	gtk_mate_scanner_set_current_scope (self, s);
	gtk_mate_scanner_set_line (self, line);
	gtk_mate_scanner_set_line_length (self, line_length);
	return self;
}


static GType gtk_mate_scanner_real_get_element_type (GeeIterable* base) {
	GtkMateScanner * self;
	self = GTK_MATE_SCANNER (base);
	return GTK_MATE_TYPE_MARKER;
}


static GeeIterator* gtk_mate_scanner_real_iterator (GeeIterable* base) {
	GtkMateScanner * self;
	self = GTK_MATE_SCANNER (base);
	return GEE_ITERATOR (g_object_ref_sink (gtk_mate_scanner_iterator_new (GTK_MATE_TYPE_MARKER, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, self)));
}


/* if we have already scanned this line for this scope then
 simply return the next cached marker*/
GtkMateMarker* gtk_mate_scanner_get_cached_marker (GtkMateScanner* self) {
	GtkMateMarker* m;
	g_return_val_if_fail (GTK_MATE_IS_SCANNER (self), NULL);
	m = NULL;
	{
		GeeArrayList* m1_collection;
		int m1_it;
		m1_collection = self->cached_markers;
		for (m1_it = 0; m1_it < gee_collection_get_size (GEE_COLLECTION (m1_collection)); m1_it = m1_it + 1) {
			GtkMateMarker* m1;
			m1 = ((GtkMateMarker*) (gee_list_get (GEE_LIST (m1_collection), m1_it)));
			{
				if (m == NULL || m->from > m1->from) {
					GtkMateMarker* _tmp1;
					GtkMateMarker* _tmp0;
					_tmp1 = NULL;
					_tmp0 = NULL;
					m = (_tmp1 = (_tmp0 = m1, (_tmp0 == NULL ? NULL : g_object_ref (_tmp0))), (m == NULL ? NULL : (m = (g_object_unref (m), NULL))), _tmp1);
				}
				(m1 == NULL ? NULL : (m1 = (g_object_unref (m1), NULL)));
			}
		}
	}
	return m;
}


OnigurumaMatch* gtk_mate_scanner_scan_for_match (GtkMateScanner* self, gint from, GtkMatePattern* p) {
	OnigurumaMatch* match;
	g_return_val_if_fail (GTK_MATE_IS_SCANNER (self), NULL);
	g_return_val_if_fail (GTK_MATE_IS_PATTERN (p), NULL);
	match = NULL;
	if (GTK_MATE_IS_SINGLE_PATTERN (p)) {
		OnigurumaMatch* _tmp0;
		_tmp0 = NULL;
		match = (_tmp0 = oniguruma_regex_search ((GTK_MATE_SINGLE_PATTERN (p))->match, self->priv->_line, from, self->priv->_line_length), (match == NULL ? NULL : (match = (g_object_unref (match), NULL))), _tmp0);
	} else {
		if (GTK_MATE_IS_DOUBLE_PATTERN (p)) {
			OnigurumaMatch* _tmp1;
			_tmp1 = NULL;
			match = (_tmp1 = oniguruma_regex_search ((GTK_MATE_DOUBLE_PATTERN (p))->begin, self->priv->_line, from, self->priv->_line_length), (match == NULL ? NULL : (match = (g_object_unref (match), NULL))), _tmp1);
		}
	}
	return match;
}


GtkMateMarker* gtk_mate_scanner_find_next_marker (GtkMateScanner* self) {
	GtkMateMarker* m;
	GtkMateMarker* _tmp0;
	g_return_val_if_fail (GTK_MATE_IS_SCANNER (self), NULL);
	m = NULL;
	_tmp0 = NULL;
	if ((m = (_tmp0 = gtk_mate_scanner_get_cached_marker (self), (m == NULL ? NULL : (m = (g_object_unref (m), NULL))), _tmp0)) != NULL) {
		fprintf (stdout, "got cached marker\n");
		gee_collection_remove (GEE_COLLECTION (self->cached_markers), m);
		return m;
	}
	fprintf (stdout, "no cached marker\n");
	g_assert (gee_collection_get_size (GEE_COLLECTION (self->cached_markers)) == 0);
	{
		GeeArrayList* p_collection;
		int p_it;
		p_collection = (GTK_MATE_DOUBLE_PATTERN (gtk_mate_scanner_get_current_scope (self)->pattern))->patterns;
		for (p_it = 0; p_it < gee_collection_get_size (GEE_COLLECTION (p_collection)); p_it = p_it + 1) {
			GtkMatePattern* p;
			p = ((GtkMatePattern*) (gee_list_get (GEE_LIST (p_collection), p_it)));
			{
				gint position_now;
				OnigurumaMatch* match;
				OnigurumaMatch* _tmp2;
				position_now = self->position;
				match = NULL;
				_tmp2 = NULL;
				while ((match = (_tmp2 = gtk_mate_scanner_scan_for_match (self, position_now, p), (match == NULL ? NULL : (match = (g_object_unref (match), NULL))), _tmp2)) != NULL) {
					GtkMateMarker* nm;
					GtkMatePattern* _tmp4;
					GtkMatePattern* _tmp3;
					OnigurumaMatch* _tmp6;
					OnigurumaMatch* _tmp5;
					fprintf (stdout, "matched: %s\n", p->name);
					nm = g_object_ref_sink (gtk_mate_marker_new ());
					_tmp4 = NULL;
					_tmp3 = NULL;
					nm->pattern = (_tmp4 = (_tmp3 = p, (_tmp3 == NULL ? NULL : g_object_ref (_tmp3))), (nm->pattern == NULL ? NULL : (nm->pattern = (g_object_unref (nm->pattern), NULL))), _tmp4);
					_tmp6 = NULL;
					_tmp5 = NULL;
					nm->match = (_tmp6 = (_tmp5 = match, (_tmp5 == NULL ? NULL : g_object_ref (_tmp5))), (nm->match == NULL ? NULL : (nm->match = (g_object_unref (nm->match), NULL))), _tmp6);
					nm->from = oniguruma_match_begin (match, 0);
					gee_collection_add (GEE_COLLECTION (self->cached_markers), nm);
					if (m == NULL || nm->from < m->from) {
						GtkMateMarker* _tmp8;
						GtkMateMarker* _tmp7;
						/*stdout.printf("(current first)\n");*/
						_tmp8 = NULL;
						_tmp7 = NULL;
						m = (_tmp8 = (_tmp7 = nm, (_tmp7 == NULL ? NULL : g_object_ref (_tmp7))), (m == NULL ? NULL : (m = (g_object_unref (m), NULL))), _tmp8);
					}
					position_now = oniguruma_match_end (match, 0);
					(nm == NULL ? NULL : (nm = (g_object_unref (nm), NULL)));
				}
				(p == NULL ? NULL : (p = (g_object_unref (p), NULL)));
				(match == NULL ? NULL : (match = (g_object_unref (match), NULL)));
			}
		}
	}
	if (m != NULL) {
		gee_collection_remove (GEE_COLLECTION (self->cached_markers), m);
	}
	return m;
}


/* called when the current_scope property is set.*/
static void gtk_mate_scanner_updated_current_scope (GtkMateScanner* self) {
	g_return_if_fail (GTK_MATE_IS_SCANNER (self));
	/* clear markers cached for this scope: 
	 (optimization potential? keep them for each scope in a hashmap)*/
	gee_collection_clear (GEE_COLLECTION (self->cached_markers));
}


GtkMateScope* gtk_mate_scanner_get_current_scope (GtkMateScanner* self) {
	g_return_val_if_fail (GTK_MATE_IS_SCANNER (self), NULL);
	return self->priv->_current_scope;
}


void gtk_mate_scanner_set_current_scope (GtkMateScanner* self, GtkMateScope* value) {
	GtkMateScope* _tmp2;
	GtkMateScope* _tmp1;
	g_return_if_fail (GTK_MATE_IS_SCANNER (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_current_scope = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (self->priv->_current_scope == NULL ? NULL : (self->priv->_current_scope = (g_object_unref (self->priv->_current_scope), NULL))), _tmp2);
	gtk_mate_scanner_updated_current_scope (self);
	g_object_notify (((GObject *) (self)), "current-scope");
}


const char* gtk_mate_scanner_get_line (GtkMateScanner* self) {
	g_return_val_if_fail (GTK_MATE_IS_SCANNER (self), NULL);
	return self->priv->_line;
}


void gtk_mate_scanner_set_line (GtkMateScanner* self, const char* value) {
	char* _tmp2;
	const char* _tmp1;
	g_return_if_fail (GTK_MATE_IS_SCANNER (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_line = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_strdup (_tmp1))), (self->priv->_line = (g_free (self->priv->_line), NULL)), _tmp2);
	g_object_notify (((GObject *) (self)), "line");
}


gint gtk_mate_scanner_get_line_length (GtkMateScanner* self) {
	g_return_val_if_fail (GTK_MATE_IS_SCANNER (self), 0);
	return self->priv->_line_length;
}


void gtk_mate_scanner_set_line_length (GtkMateScanner* self, gint value) {
	g_return_if_fail (GTK_MATE_IS_SCANNER (self));
	self->priv->_line_length = value;
	g_object_notify (((GObject *) (self)), "line-length");
}


static GObject * gtk_mate_scanner_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GtkMateScannerClass * klass;
	GObjectClass * parent_class;
	GtkMateScanner * self;
	klass = GTK_MATE_SCANNER_CLASS (g_type_class_peek (GTK_MATE_TYPE_SCANNER));
	parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = GTK_MATE_SCANNER (obj);
	{
		GeeArrayList* _tmp0;
		self->position = 0;
		_tmp0 = NULL;
		self->cached_markers = (_tmp0 = gee_array_list_new (GTK_MATE_TYPE_MARKER, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal), (self->cached_markers == NULL ? NULL : (self->cached_markers = (g_object_unref (self->cached_markers), NULL))), _tmp0);
	}
	return obj;
}


GtkMateScannerIterator* gtk_mate_scanner_iterator_new (GType marker_type, GBoxedCopyFunc marker_dup_func, GDestroyNotify marker_destroy_func, GtkMateScanner* s) {
	GParameter * __params;
	GParameter * __params_it;
	GtkMateScannerIterator * self;
	g_return_val_if_fail (GTK_MATE_IS_SCANNER (s), NULL);
	__params = g_new0 (GParameter, 4);
	__params_it = __params;
	__params_it->name = "marker-type";
	g_value_init (&__params_it->value, G_TYPE_GTYPE);
	g_value_set_gtype (&__params_it->value, marker_type);
	__params_it++;
	__params_it->name = "marker-dup-func";
	g_value_init (&__params_it->value, G_TYPE_POINTER);
	g_value_set_pointer (&__params_it->value, marker_dup_func);
	__params_it++;
	__params_it->name = "marker-destroy-func";
	g_value_init (&__params_it->value, G_TYPE_POINTER);
	g_value_set_pointer (&__params_it->value, marker_destroy_func);
	__params_it++;
	__params_it->name = "scanner";
	g_value_init (&__params_it->value, GTK_MATE_TYPE_SCANNER);
	g_value_set_object (&__params_it->value, s);
	__params_it++;
	self = g_object_newv (GTK_MATE_SCANNER_TYPE_ITERATOR, __params_it - __params, __params);
	while (__params_it > __params) {
		--__params_it;
		g_value_unset (&__params_it->value);
	}
	g_free (__params);
	return self;
}


static gboolean gtk_mate_scanner_iterator_real_next (GeeIterator* base) {
	GtkMateScannerIterator * self;
	gpointer _tmp0;
	self = GTK_MATE_SCANNER_ITERATOR (base);
	_tmp0 = NULL;
	self->next_marker = (_tmp0 = gtk_mate_scanner_find_next_marker (self->priv->_scanner), (self->next_marker == NULL || self->priv->marker_destroy_func == NULL ? NULL : (self->next_marker = (self->priv->marker_destroy_func (self->next_marker), NULL))), _tmp0);
	return (self->next_marker != NULL);
}


static gpointer gtk_mate_scanner_iterator_real_get (GeeIterator* base) {
	GtkMateScannerIterator * self;
	gconstpointer _tmp0;
	self = GTK_MATE_SCANNER_ITERATOR (base);
	_tmp0 = NULL;
	return (_tmp0 = self->next_marker, (_tmp0 == NULL || self->priv->marker_dup_func == NULL ? ((gpointer) (_tmp0)) : self->priv->marker_dup_func (((gpointer) (_tmp0)))));
}


GtkMateScanner* gtk_mate_scanner_iterator_get_scanner (GtkMateScannerIterator* self) {
	g_return_val_if_fail (GTK_MATE_SCANNER_IS_ITERATOR (self), NULL);
	return self->priv->_scanner;
}


void gtk_mate_scanner_iterator_set_scanner (GtkMateScannerIterator* self, GtkMateScanner* value) {
	GtkMateScanner* _tmp2;
	GtkMateScanner* _tmp1;
	g_return_if_fail (GTK_MATE_SCANNER_IS_ITERATOR (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_scanner = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (self->priv->_scanner == NULL ? NULL : (self->priv->_scanner = (g_object_unref (self->priv->_scanner), NULL))), _tmp2);
	g_object_notify (((GObject *) (self)), "scanner");
}


static GObject * gtk_mate_scanner_iterator_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GtkMateScannerIteratorClass * klass;
	GObjectClass * parent_class;
	GtkMateScannerIterator * self;
	klass = GTK_MATE_SCANNER_ITERATOR_CLASS (g_type_class_peek (GTK_MATE_SCANNER_TYPE_ITERATOR));
	parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = GTK_MATE_SCANNER_ITERATOR (obj);
	{
	}
	return obj;
}


static void gtk_mate_scanner_iterator_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateScannerIterator * self;
	self = GTK_MATE_SCANNER_ITERATOR (object);
	switch (property_id) {
		case GTK_MATE_SCANNER_ITERATOR_SCANNER:
		g_value_set_object (value, gtk_mate_scanner_iterator_get_scanner (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_scanner_iterator_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GtkMateScannerIterator * self;
	self = GTK_MATE_SCANNER_ITERATOR (object);
	switch (property_id) {
		case GTK_MATE_SCANNER_ITERATOR_SCANNER:
		gtk_mate_scanner_iterator_set_scanner (self, g_value_get_object (value));
		break;
		case GTK_MATE_SCANNER_ITERATOR_MARKER_TYPE:
		self->priv->marker_type = g_value_get_gtype (value);
		break;
		case GTK_MATE_SCANNER_ITERATOR_MARKER_DUP_FUNC:
		self->priv->marker_dup_func = g_value_get_pointer (value);
		break;
		case GTK_MATE_SCANNER_ITERATOR_MARKER_DESTROY_FUNC:
		self->priv->marker_destroy_func = g_value_get_pointer (value);
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_scanner_iterator_class_init (GtkMateScannerIteratorClass * klass) {
	gtk_mate_scanner_iterator_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GtkMateScannerIteratorPrivate));
	G_OBJECT_CLASS (klass)->get_property = gtk_mate_scanner_iterator_get_property;
	G_OBJECT_CLASS (klass)->set_property = gtk_mate_scanner_iterator_set_property;
	G_OBJECT_CLASS (klass)->constructor = gtk_mate_scanner_iterator_constructor;
	G_OBJECT_CLASS (klass)->dispose = gtk_mate_scanner_iterator_dispose;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCANNER_ITERATOR_MARKER_TYPE, g_param_spec_gtype ("marker-type", "type", "type", G_TYPE_NONE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCANNER_ITERATOR_MARKER_DUP_FUNC, g_param_spec_pointer ("marker-dup-func", "dup func", "dup func", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCANNER_ITERATOR_MARKER_DESTROY_FUNC, g_param_spec_pointer ("marker-destroy-func", "destroy func", "destroy func", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCANNER_ITERATOR_SCANNER, g_param_spec_object ("scanner", "scanner", "scanner", GTK_MATE_TYPE_SCANNER, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT));
}


static void gtk_mate_scanner_iterator_gee_iterator_interface_init (GeeIteratorIface * iface) {
	gtk_mate_scanner_iterator_gee_iterator_parent_iface = g_type_interface_peek_parent (iface);
	iface->next = gtk_mate_scanner_iterator_real_next;
	iface->get = gtk_mate_scanner_iterator_real_get;
}


static void gtk_mate_scanner_iterator_instance_init (GtkMateScannerIterator * self) {
	self->priv = GTK_MATE_SCANNER_ITERATOR_GET_PRIVATE (self);
}


static void gtk_mate_scanner_iterator_dispose (GObject * obj) {
	GtkMateScannerIterator * self;
	self = GTK_MATE_SCANNER_ITERATOR (obj);
	(self->priv->_scanner == NULL ? NULL : (self->priv->_scanner = (g_object_unref (self->priv->_scanner), NULL)));
	(self->next_marker == NULL || self->priv->marker_destroy_func == NULL ? NULL : (self->next_marker = (self->priv->marker_destroy_func (self->next_marker), NULL)));
	G_OBJECT_CLASS (gtk_mate_scanner_iterator_parent_class)->dispose (obj);
}


GType gtk_mate_scanner_iterator_get_type (void) {
	static volatile gsize gtk_mate_scanner_iterator_type_id = 0;
	if (g_once_init_enter (&gtk_mate_scanner_iterator_type_id)) {
		GType gtk_mate_scanner_iterator_type_id_temp;
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateScannerIteratorClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_scanner_iterator_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateScannerIterator), 0, (GInstanceInitFunc) gtk_mate_scanner_iterator_instance_init };
		static const GInterfaceInfo gee_iterator_info = { (GInterfaceInitFunc) gtk_mate_scanner_iterator_gee_iterator_interface_init, (GInterfaceFinalizeFunc) NULL, NULL};
		gtk_mate_scanner_iterator_type_id_temp = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateScannerIterator", &g_define_type_info, 0);
		g_type_add_interface_static (gtk_mate_scanner_iterator_type_id_temp, GEE_TYPE_ITERATOR, &gee_iterator_info);
		g_once_init_leave (&gtk_mate_scanner_iterator_type_id, gtk_mate_scanner_iterator_type_id_temp);
	}
	return gtk_mate_scanner_iterator_type_id;
}


static void gtk_mate_scanner_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateScanner * self;
	self = GTK_MATE_SCANNER (object);
	switch (property_id) {
		case GTK_MATE_SCANNER_CURRENT_SCOPE:
		g_value_set_object (value, gtk_mate_scanner_get_current_scope (self));
		break;
		case GTK_MATE_SCANNER_LINE:
		g_value_set_string (value, gtk_mate_scanner_get_line (self));
		break;
		case GTK_MATE_SCANNER_LINE_LENGTH:
		g_value_set_int (value, gtk_mate_scanner_get_line_length (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_scanner_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GtkMateScanner * self;
	self = GTK_MATE_SCANNER (object);
	switch (property_id) {
		case GTK_MATE_SCANNER_CURRENT_SCOPE:
		gtk_mate_scanner_set_current_scope (self, g_value_get_object (value));
		break;
		case GTK_MATE_SCANNER_LINE:
		gtk_mate_scanner_set_line (self, g_value_get_string (value));
		break;
		case GTK_MATE_SCANNER_LINE_LENGTH:
		gtk_mate_scanner_set_line_length (self, g_value_get_int (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_scanner_class_init (GtkMateScannerClass * klass) {
	gtk_mate_scanner_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GtkMateScannerPrivate));
	G_OBJECT_CLASS (klass)->get_property = gtk_mate_scanner_get_property;
	G_OBJECT_CLASS (klass)->set_property = gtk_mate_scanner_set_property;
	G_OBJECT_CLASS (klass)->constructor = gtk_mate_scanner_constructor;
	G_OBJECT_CLASS (klass)->dispose = gtk_mate_scanner_dispose;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCANNER_CURRENT_SCOPE, g_param_spec_object ("current-scope", "current-scope", "current-scope", GTK_MATE_TYPE_SCOPE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCANNER_LINE, g_param_spec_string ("line", "line", "line", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCANNER_LINE_LENGTH, g_param_spec_int ("line-length", "line-length", "line-length", G_MININT, G_MAXINT, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void gtk_mate_scanner_gee_iterable_interface_init (GeeIterableIface * iface) {
	gtk_mate_scanner_gee_iterable_parent_iface = g_type_interface_peek_parent (iface);
	iface->get_element_type = gtk_mate_scanner_real_get_element_type;
	iface->iterator = gtk_mate_scanner_real_iterator;
}


static void gtk_mate_scanner_instance_init (GtkMateScanner * self) {
	self->priv = GTK_MATE_SCANNER_GET_PRIVATE (self);
}


static void gtk_mate_scanner_dispose (GObject * obj) {
	GtkMateScanner * self;
	self = GTK_MATE_SCANNER (obj);
	(self->priv->_current_scope == NULL ? NULL : (self->priv->_current_scope = (g_object_unref (self->priv->_current_scope), NULL)));
	self->priv->_line = (g_free (self->priv->_line), NULL);
	(self->cached_markers == NULL ? NULL : (self->cached_markers = (g_object_unref (self->cached_markers), NULL)));
	G_OBJECT_CLASS (gtk_mate_scanner_parent_class)->dispose (obj);
}


GType gtk_mate_scanner_get_type (void) {
	static volatile gsize gtk_mate_scanner_type_id = 0;
	if (g_once_init_enter (&gtk_mate_scanner_type_id)) {
		GType gtk_mate_scanner_type_id_temp;
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateScannerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_scanner_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateScanner), 0, (GInstanceInitFunc) gtk_mate_scanner_instance_init };
		static const GInterfaceInfo gee_iterable_info = { (GInterfaceInitFunc) gtk_mate_scanner_gee_iterable_interface_init, (GInterfaceFinalizeFunc) NULL, NULL};
		gtk_mate_scanner_type_id_temp = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateScanner", &g_define_type_info, 0);
		g_type_add_interface_static (gtk_mate_scanner_type_id_temp, GEE_TYPE_ITERABLE, &gee_iterable_info);
		g_once_init_leave (&gtk_mate_scanner_type_id, gtk_mate_scanner_type_id_temp);
	}
	return gtk_mate_scanner_type_id;
}




