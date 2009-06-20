
#include <glib.h>
#include <glib-object.h>
#include <libxml/tree.h>
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>
#include <gee/list.h>
#include <gee/collection.h>
#include <gee/hashmap.h>
#include <gee/map.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <stdio.h>
#include <glib/gstdio.h>
#include <libxml/parser.h>


#define PLIST_TYPE_NODE (plist_node_get_type ())
#define PLIST_NODE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PLIST_TYPE_NODE, PListNode))
#define PLIST_NODE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PLIST_TYPE_NODE, PListNodeClass))
#define PLIST_IS_NODE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PLIST_TYPE_NODE))
#define PLIST_IS_NODE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PLIST_TYPE_NODE))
#define PLIST_NODE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PLIST_TYPE_NODE, PListNodeClass))

typedef struct _PListNode PListNode;
typedef struct _PListNodeClass PListNodeClass;
typedef struct _PListNodePrivate PListNodePrivate;

#define PLIST_TYPE_STRING (plist_string_get_type ())
#define PLIST_STRING(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PLIST_TYPE_STRING, PListString))
#define PLIST_STRING_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PLIST_TYPE_STRING, PListStringClass))
#define PLIST_IS_STRING(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PLIST_TYPE_STRING))
#define PLIST_IS_STRING_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PLIST_TYPE_STRING))
#define PLIST_STRING_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PLIST_TYPE_STRING, PListStringClass))

typedef struct _PListString PListString;
typedef struct _PListStringClass PListStringClass;
typedef struct _PListStringPrivate PListStringPrivate;

#define PLIST_TYPE_INTEGER (plist_integer_get_type ())
#define PLIST_INTEGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PLIST_TYPE_INTEGER, PListInteger))
#define PLIST_INTEGER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PLIST_TYPE_INTEGER, PListIntegerClass))
#define PLIST_IS_INTEGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PLIST_TYPE_INTEGER))
#define PLIST_IS_INTEGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PLIST_TYPE_INTEGER))
#define PLIST_INTEGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PLIST_TYPE_INTEGER, PListIntegerClass))

typedef struct _PListInteger PListInteger;
typedef struct _PListIntegerClass PListIntegerClass;
typedef struct _PListIntegerPrivate PListIntegerPrivate;

#define PLIST_TYPE_DICT (plist_dict_get_type ())
#define PLIST_DICT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PLIST_TYPE_DICT, PListDict))
#define PLIST_DICT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PLIST_TYPE_DICT, PListDictClass))
#define PLIST_IS_DICT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PLIST_TYPE_DICT))
#define PLIST_IS_DICT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PLIST_TYPE_DICT))
#define PLIST_DICT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PLIST_TYPE_DICT, PListDictClass))

typedef struct _PListDict PListDict;
typedef struct _PListDictClass PListDictClass;

#define PLIST_TYPE_ARRAY (plist_array_get_type ())
#define PLIST_ARRAY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PLIST_TYPE_ARRAY, PListArray))
#define PLIST_ARRAY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PLIST_TYPE_ARRAY, PListArrayClass))
#define PLIST_IS_ARRAY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PLIST_TYPE_ARRAY))
#define PLIST_IS_ARRAY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PLIST_TYPE_ARRAY))
#define PLIST_ARRAY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PLIST_TYPE_ARRAY, PListArrayClass))

typedef struct _PListArray PListArray;
typedef struct _PListArrayClass PListArrayClass;
typedef struct _PListArrayPrivate PListArrayPrivate;
typedef struct _PListDictPrivate PListDictPrivate;

/* PList reader in Vala
 valac -o plist --pkg libxml-2.0 --pkg gee-1.0 plist.vala*/
typedef enum  {
	XML_ERROR_FILE_NOT_FOUND,
	XML_ERROR_XML_DOCUMENT_EMPTY
} XmlError;
#define XML_ERROR xml_error_quark ()
struct _PListNode {
	GObject parent_instance;
	PListNodePrivate * priv;
};

struct _PListNodeClass {
	GObjectClass parent_class;
};

struct _PListString {
	PListNode parent_instance;
	PListStringPrivate * priv;
	char* str;
};

struct _PListStringClass {
	PListNodeClass parent_class;
};

struct _PListInteger {
	PListNode parent_instance;
	PListIntegerPrivate * priv;
	gint value;
};

struct _PListIntegerClass {
	PListNodeClass parent_class;
};

struct _PListArray {
	PListNode parent_instance;
	PListArrayPrivate * priv;
	GeeArrayList* array;
};

struct _PListArrayClass {
	PListNodeClass parent_class;
};

struct _PListDict {
	PListNode parent_instance;
	PListDictPrivate * priv;
	GeeHashMap* map;
};

struct _PListDictClass {
	PListNodeClass parent_class;
};



GQuark xml_error_quark (void);
GType plist_node_get_type (void);
enum  {
	PLIST_NODE_DUMMY_PROPERTY
};
PListString* plist_string_new (void);
PListString* plist_string_construct (GType object_type);
GType plist_string_get_type (void);
PListInteger* plist_integer_new (void);
PListInteger* plist_integer_construct (GType object_type);
GType plist_integer_get_type (void);
GType plist_dict_get_type (void);
PListDict* plist_dict_parse_dict (xmlNode* node);
GType plist_array_get_type (void);
PListArray* plist_array_parse_array (xmlNode* node);
PListNode* plist_node_parse_xml_node (xmlNode* node);
PListNode* plist_node_new (void);
PListNode* plist_node_construct (GType object_type);
PListNode* plist_node_new (void);
static gpointer plist_node_parent_class = NULL;
enum  {
	PLIST_STRING_DUMMY_PROPERTY
};
PListString* plist_string_new (void);
static gpointer plist_string_parent_class = NULL;
static void plist_string_finalize (GObject* obj);
enum  {
	PLIST_INTEGER_DUMMY_PROPERTY
};
PListInteger* plist_integer_new (void);
static gpointer plist_integer_parent_class = NULL;
static void plist_integer_finalize (GObject* obj);
enum  {
	PLIST_ARRAY_DUMMY_PROPERTY
};
PListNode* plist_array_get (PListArray* self, gint ix);
PListArray* plist_array_new (void);
PListArray* plist_array_construct (GType object_type);
PListArray* plist_array_new (void);
static GObject * plist_array_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer plist_array_parent_class = NULL;
static void plist_array_finalize (GObject* obj);
enum  {
	PLIST_DICT_DUMMY_PROPERTY
};
PListNode* plist_dict_get (PListDict* self, const char* key);
char** plist_dict_keys (PListDict* self, int* result_length1);
void plist_dict_print_keys (PListDict* self);
PListDict* plist_dict_new (void);
PListDict* plist_dict_construct (GType object_type);
PListDict* plist_dict_new (void);
static GObject * plist_dict_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer plist_dict_parent_class = NULL;
static void plist_dict_finalize (GObject* obj);
char* string_helper_gsub (const char* start_string, const char* match_string, const char* replacement_string);
PListDict* plist_parse (const char* filename, GError** error);
void plist_print_plist (gint indent, PListNode* node);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static int _vala_strcmp0 (const char * str1, const char * str2);



GQuark xml_error_quark (void) {
	return g_quark_from_static_string ("xml_error-quark");
}


PListNode* plist_node_parse_xml_node (xmlNode* node) {
	if (_vala_strcmp0 (node->name, "string") == 0) {
		PListString* string_node;
		char* _tmp0_;
		string_node = plist_string_new ();
		_tmp0_ = NULL;
		string_node->str = (_tmp0_ = xmlNodeGetContent (node), string_node->str = (g_free (string_node->str), NULL), _tmp0_);
		return (PListNode*) string_node;
	}
	if (_vala_strcmp0 (node->name, "integer") == 0) {
		PListInteger* int_node;
		char* _tmp2_;
		int_node = plist_integer_new ();
		_tmp2_ = NULL;
		int_node->value = atoi (_tmp2_ = xmlNodeGetContent (node));
		_tmp2_ = (g_free (_tmp2_), NULL);
		return (PListNode*) int_node;
	}
	if (_vala_strcmp0 (node->name, "dict") == 0) {
		return (PListNode*) plist_dict_parse_dict (node);
	}
	if (_vala_strcmp0 (node->name, "array") == 0) {
		return (PListNode*) plist_array_parse_array (node);
	}
	return NULL;
}


PListNode* plist_node_construct (GType object_type) {
	PListNode * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


PListNode* plist_node_new (void) {
	return plist_node_construct (PLIST_TYPE_NODE);
}


static void plist_node_class_init (PListNodeClass * klass) {
	plist_node_parent_class = g_type_class_peek_parent (klass);
}


static void plist_node_instance_init (PListNode * self) {
}


GType plist_node_get_type (void) {
	static GType plist_node_type_id = 0;
	if (plist_node_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (PListNodeClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) plist_node_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (PListNode), 0, (GInstanceInitFunc) plist_node_instance_init, NULL };
		plist_node_type_id = g_type_register_static (G_TYPE_OBJECT, "PListNode", &g_define_type_info, 0);
	}
	return plist_node_type_id;
}


PListString* plist_string_construct (GType object_type) {
	PListString * self;
	self = (PListString*) plist_node_construct (object_type);
	return self;
}


PListString* plist_string_new (void) {
	return plist_string_construct (PLIST_TYPE_STRING);
}


static void plist_string_class_init (PListStringClass * klass) {
	plist_string_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = plist_string_finalize;
}


static void plist_string_instance_init (PListString * self) {
}


static void plist_string_finalize (GObject* obj) {
	PListString * self;
	self = PLIST_STRING (obj);
	self->str = (g_free (self->str), NULL);
	G_OBJECT_CLASS (plist_string_parent_class)->finalize (obj);
}


GType plist_string_get_type (void) {
	static GType plist_string_type_id = 0;
	if (plist_string_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (PListStringClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) plist_string_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (PListString), 0, (GInstanceInitFunc) plist_string_instance_init, NULL };
		plist_string_type_id = g_type_register_static (PLIST_TYPE_NODE, "PListString", &g_define_type_info, 0);
	}
	return plist_string_type_id;
}


PListInteger* plist_integer_construct (GType object_type) {
	PListInteger * self;
	self = (PListInteger*) plist_node_construct (object_type);
	return self;
}


PListInteger* plist_integer_new (void) {
	return plist_integer_construct (PLIST_TYPE_INTEGER);
}


static void plist_integer_class_init (PListIntegerClass * klass) {
	plist_integer_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = plist_integer_finalize;
}


static void plist_integer_instance_init (PListInteger * self) {
}


static void plist_integer_finalize (GObject* obj) {
	PListInteger * self;
	self = PLIST_INTEGER (obj);
	G_OBJECT_CLASS (plist_integer_parent_class)->finalize (obj);
}


GType plist_integer_get_type (void) {
	static GType plist_integer_type_id = 0;
	if (plist_integer_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (PListIntegerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) plist_integer_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (PListInteger), 0, (GInstanceInitFunc) plist_integer_instance_init, NULL };
		plist_integer_type_id = g_type_register_static (PLIST_TYPE_NODE, "PListInteger", &g_define_type_info, 0);
	}
	return plist_integer_type_id;
}


PListNode* plist_array_get (PListArray* self, gint ix) {
	g_return_val_if_fail (self != NULL, NULL);
	return (PListNode*) gee_list_get ((GeeList*) self->array, ix);
}


PListArray* plist_array_parse_array (xmlNode* node) {
	PListArray* array;
	array = plist_array_new ();
	{
		xmlNode* iter;
		iter = node->children;
		for (; iter != NULL; iter = iter->next) {
			PListNode* _tmp0_;
			if (iter->type != XML_ELEMENT_NODE) {
				continue;
			}
			_tmp0_ = NULL;
			gee_collection_add ((GeeCollection*) array->array, _tmp0_ = plist_node_parse_xml_node (iter));
			(_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_object_unref (_tmp0_), NULL));
		}
	}
	return array;
}


PListArray* plist_array_construct (GType object_type) {
	PListArray * self;
	self = (PListArray*) plist_node_construct (object_type);
	return self;
}


PListArray* plist_array_new (void) {
	return plist_array_construct (PLIST_TYPE_ARRAY);
}


static GObject * plist_array_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	PListArrayClass * klass;
	GObjectClass * parent_class;
	PListArray * self;
	klass = PLIST_ARRAY_CLASS (g_type_class_peek (PLIST_TYPE_ARRAY));
	parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = PLIST_ARRAY (obj);
	{
		GeeArrayList* _tmp0_;
		_tmp0_ = NULL;
		self->array = (_tmp0_ = gee_array_list_new (PLIST_TYPE_NODE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->array == NULL) ? NULL : (self->array = (g_object_unref (self->array), NULL)), _tmp0_);
	}
	return obj;
}


static void plist_array_class_init (PListArrayClass * klass) {
	plist_array_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = plist_array_constructor;
	G_OBJECT_CLASS (klass)->finalize = plist_array_finalize;
}


static void plist_array_instance_init (PListArray * self) {
}


static void plist_array_finalize (GObject* obj) {
	PListArray * self;
	self = PLIST_ARRAY (obj);
	(self->array == NULL) ? NULL : (self->array = (g_object_unref (self->array), NULL));
	G_OBJECT_CLASS (plist_array_parent_class)->finalize (obj);
}


GType plist_array_get_type (void) {
	static GType plist_array_type_id = 0;
	if (plist_array_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (PListArrayClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) plist_array_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (PListArray), 0, (GInstanceInitFunc) plist_array_instance_init, NULL };
		plist_array_type_id = g_type_register_static (PLIST_TYPE_NODE, "PListArray", &g_define_type_info, 0);
	}
	return plist_array_type_id;
}


PListNode* plist_dict_get (PListDict* self, const char* key) {
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (key != NULL, NULL);
	return (PListNode*) gee_map_get ((GeeMap*) self->map, key);
}


char** plist_dict_keys (PListDict* self, int* result_length1) {
	char** _tmp3_;
	gint ks_size;
	gint ks_length1;
	gint _tmp1_;
	GeeSet* _tmp0_;
	char** _tmp2_;
	char** ks;
	gint i;
	char** _tmp8_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp3_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	ks = (_tmp3_ = (_tmp2_ = g_new0 (char*, (_tmp1_ = gee_collection_get_size ((GeeCollection*) (_tmp0_ = gee_map_get_keys ((GeeMap*) self->map)))) + 1), (_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_object_unref (_tmp0_), NULL)), _tmp2_), ks_length1 = _tmp1_, ks_size = ks_length1, _tmp3_);
	i = 0;
	{
		GeeSet* _tmp4_;
		GeeIterator* _tmp5_;
		GeeIterator* _s_it;
		_tmp4_ = NULL;
		_tmp5_ = NULL;
		_s_it = (_tmp5_ = gee_iterable_iterator ((GeeIterable*) (_tmp4_ = gee_map_get_keys ((GeeMap*) self->map))), (_tmp4_ == NULL) ? NULL : (_tmp4_ = (g_object_unref (_tmp4_), NULL)), _tmp5_);
		while (gee_iterator_next (_s_it)) {
			char* s;
			char* _tmp7_;
			const char* _tmp6_;
			s = (char*) gee_iterator_get (_s_it);
			_tmp7_ = NULL;
			_tmp6_ = NULL;
			ks[i] = (_tmp7_ = (_tmp6_ = s, (_tmp6_ == NULL) ? NULL : g_strdup (_tmp6_)), ks[i] = (g_free (ks[i]), NULL), _tmp7_);
			i = i + 1;
			s = (g_free (s), NULL);
		}
		(_s_it == NULL) ? NULL : (_s_it = (g_object_unref (_s_it), NULL));
	}
	_tmp8_ = NULL;
	return (_tmp8_ = ks, *result_length1 = ks_length1, _tmp8_);
}


void plist_dict_print_keys (PListDict* self) {
	g_return_if_fail (self != NULL);
	{
		gint _tmp0_;
		char** s_collection;
		int s_collection_length1;
		int s_it;
		s_collection = plist_dict_keys (self, &_tmp0_);
		s_collection_length1 = _tmp0_;
		for (s_it = 0; s_it < _tmp0_; s_it = s_it + 1) {
			const char* _tmp1_;
			char* s;
			_tmp1_ = NULL;
			s = (_tmp1_ = s_collection[s_it], (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_));
			{
				fprintf (stdout, "key: %s\n", s);
				s = (g_free (s), NULL);
			}
		}
		s_collection = (_vala_array_free (s_collection, s_collection_length1, (GDestroyNotify) g_free), NULL);
	}
}


PListDict* plist_dict_parse_dict (xmlNode* node) {
	PListDict* dict;
	char* key;
	PListDict* _tmp3_;
	dict = plist_dict_new ();
	key = NULL;
	{
		xmlNode* iter;
		iter = node->children;
		for (; iter != NULL; iter = iter->next) {
			if (iter->type != XML_ELEMENT_NODE) {
				continue;
			}
			if (key == NULL) {
				char* _tmp0_;
				_tmp0_ = NULL;
				key = (_tmp0_ = xmlNodeGetContent (iter), key = (g_free (key), NULL), _tmp0_);
			} else {
				PListNode* _tmp1_;
				char* _tmp2_;
				_tmp1_ = NULL;
				gee_map_set ((GeeMap*) dict->map, key, _tmp1_ = plist_node_parse_xml_node (iter));
				(_tmp1_ == NULL) ? NULL : (_tmp1_ = (g_object_unref (_tmp1_), NULL));
				_tmp2_ = NULL;
				key = (_tmp2_ = NULL, key = (g_free (key), NULL), _tmp2_);
			}
		}
	}
	_tmp3_ = NULL;
	return (_tmp3_ = dict, key = (g_free (key), NULL), _tmp3_);
}


PListDict* plist_dict_construct (GType object_type) {
	PListDict * self;
	self = (PListDict*) plist_node_construct (object_type);
	return self;
}


PListDict* plist_dict_new (void) {
	return plist_dict_construct (PLIST_TYPE_DICT);
}


static GObject * plist_dict_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	PListDictClass * klass;
	GObjectClass * parent_class;
	PListDict * self;
	klass = PLIST_DICT_CLASS (g_type_class_peek (PLIST_TYPE_DICT));
	parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = PLIST_DICT (obj);
	{
		GeeHashMap* _tmp1_;
		_tmp1_ = NULL;
		self->map = (_tmp1_ = gee_hash_map_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, PLIST_TYPE_NODE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_str_hash, g_str_equal, g_direct_equal), (self->map == NULL) ? NULL : (self->map = (g_object_unref (self->map), NULL)), _tmp1_);
	}
	return obj;
}


static void plist_dict_class_init (PListDictClass * klass) {
	plist_dict_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = plist_dict_constructor;
	G_OBJECT_CLASS (klass)->finalize = plist_dict_finalize;
}


static void plist_dict_instance_init (PListDict * self) {
}


static void plist_dict_finalize (GObject* obj) {
	PListDict * self;
	self = PLIST_DICT (obj);
	(self->map == NULL) ? NULL : (self->map = (g_object_unref (self->map), NULL));
	G_OBJECT_CLASS (plist_dict_parent_class)->finalize (obj);
}


GType plist_dict_get_type (void) {
	static GType plist_dict_type_id = 0;
	if (plist_dict_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (PListDictClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) plist_dict_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (PListDict), 0, (GInstanceInitFunc) plist_dict_instance_init, NULL };
		plist_dict_type_id = g_type_register_static (PLIST_TYPE_NODE, "PListDict", &g_define_type_info, 0);
	}
	return plist_dict_type_id;
}


PListDict* plist_parse (const char* filename, GError** error) {
	GError * _inner_error_;
	char* file_contents;
	gulong len;
	char* _tmp2_;
	gboolean _tmp1_;
	char* _tmp0_;
	char* _tmp3_;
	xmlDoc* xml_doc;
	xmlNode* root_node;
	xmlNode* top_node;
	PListDict* dict;
	PListDict* _tmp7_;
	g_return_val_if_fail (filename != NULL, NULL);
	_inner_error_ = NULL;
	file_contents = NULL;
	len = 0UL;
	_tmp2_ = NULL;
	_tmp0_ = NULL;
	_tmp1_ = g_file_get_contents (filename, &_tmp0_, &len, &_inner_error_);
	file_contents = (_tmp2_ = _tmp0_, file_contents = (g_free (file_contents), NULL), _tmp2_);
	_tmp1_;
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == G_FILE_ERROR) {
			g_propagate_error (error, _inner_error_);
			file_contents = (g_free (file_contents), NULL);
			return NULL;
		} else {
			file_contents = (g_free (file_contents), NULL);
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	/* libxml doesn't like vertical tabs */
	_tmp3_ = NULL;
	file_contents = (_tmp3_ = string_helper_gsub (file_contents, "\v", ""), file_contents = (g_free (file_contents), NULL), _tmp3_);
	if (!g_utf8_validate (file_contents, -1, NULL)) {
		PListDict* _tmp4_;
		fprintf (stdout, "%s contents not UTF-8\n", filename);
		_tmp4_ = NULL;
		return (_tmp4_ = NULL, file_contents = (g_free (file_contents), NULL), _tmp4_);
	}
	xml_doc = xmlParseMemory (file_contents, (gint) len);
	if (xml_doc == NULL) {
		PListDict* _tmp5_;
		/*throw new XmlError.FILE_NOT_FOUND ("file "+ filename + " not found or permissions missing");*/
		_tmp5_ = NULL;
		return (_tmp5_ = NULL, file_contents = (g_free (file_contents), NULL), _tmp5_);
	}
	root_node = xmlDocGetRootElement (xml_doc);
	if (root_node == NULL) {
		PListDict* _tmp6_;
		/* free the document manually before throwing because the garbage collector can't work on pointers*/
		xmlFreeDoc (xml_doc);
		fprintf (stdout, "XML document is empty when opening %s\n", filename);
		_tmp6_ = NULL;
		return (_tmp6_ = NULL, file_contents = (g_free (file_contents), NULL), _tmp6_);
	}
	top_node = NULL;
	{
		xmlNode* iter;
		iter = root_node->children;
		for (; iter != NULL; iter = iter->next) {
			if (iter->type != XML_ELEMENT_NODE) {
				continue;
			}
			top_node = iter;
		}
	}
	if (_vala_strcmp0 (top_node->name, "dict") != 0) {
		fprintf (stdout, "error top node is not a dict");
	}
	dict = plist_dict_parse_dict (top_node);
	/*free the document*/
	xmlFreeDoc (xml_doc);
	_tmp7_ = NULL;
	return (_tmp7_ = dict, file_contents = (g_free (file_contents), NULL), _tmp7_);
}


void plist_print_plist (gint indent, PListNode* node) {
	char* str_indent;
	g_return_if_fail (node != NULL);
	str_indent = g_strnfill ((gulong) (indent * 2), ' ');
	if (PLIST_IS_STRING (node)) {
		fprintf (stdout, "%s%s,\n", str_indent, PLIST_STRING (node)->str);
	}
	if (PLIST_IS_DICT (node)) {
		char* _tmp0_;
		char* _tmp3_;
		fprintf (stdout, "%s{\n", str_indent);
		_tmp0_ = NULL;
		str_indent = (_tmp0_ = g_strnfill ((gulong) ((indent + 1) * 2), ' '), str_indent = (g_free (str_indent), NULL), _tmp0_);
		{
			GeeSet* _tmp1_;
			GeeIterator* _tmp2_;
			GeeIterator* _key_it;
			_tmp1_ = NULL;
			_tmp2_ = NULL;
			_key_it = (_tmp2_ = gee_iterable_iterator ((GeeIterable*) (_tmp1_ = gee_map_get_keys ((GeeMap*) PLIST_DICT (node)->map))), (_tmp1_ == NULL) ? NULL : (_tmp1_ = (g_object_unref (_tmp1_), NULL)), _tmp2_);
			while (gee_iterator_next (_key_it)) {
				char* key;
				PListNode* value;
				key = (char*) gee_iterator_get (_key_it);
				fprintf (stdout, "%s%s => ", str_indent, key);
				value = (PListNode*) gee_map_get ((GeeMap*) PLIST_DICT (node)->map, key);
				if (PLIST_IS_STRING (value)) {
					fprintf (stdout, "\"%s\",\n", PLIST_STRING (value)->str);
				} else {
					fprintf (stdout, "\n");
					plist_print_plist (indent + 1, value);
				}
				key = (g_free (key), NULL);
				(value == NULL) ? NULL : (value = (g_object_unref (value), NULL));
			}
			(_key_it == NULL) ? NULL : (_key_it = (g_object_unref (_key_it), NULL));
		}
		_tmp3_ = NULL;
		str_indent = (_tmp3_ = g_strnfill ((gulong) (indent * 2), ' '), str_indent = (g_free (str_indent), NULL), _tmp3_);
		fprintf (stdout, "%s},\n", str_indent);
	}
	if (PLIST_IS_ARRAY (node)) {
		char* _tmp4_;
		char* _tmp5_;
		fprintf (stdout, "%s[\n", str_indent);
		_tmp4_ = NULL;
		str_indent = (_tmp4_ = g_strnfill ((gulong) ((indent + 1) * 2), ' '), str_indent = (g_free (str_indent), NULL), _tmp4_);
		{
			GeeIterator* _sub_node_it;
			_sub_node_it = gee_iterable_iterator ((GeeIterable*) PLIST_ARRAY (node)->array);
			while (gee_iterator_next (_sub_node_it)) {
				PListNode* sub_node;
				sub_node = (PListNode*) gee_iterator_get (_sub_node_it);
				plist_print_plist (indent + 1, sub_node);
				(sub_node == NULL) ? NULL : (sub_node = (g_object_unref (sub_node), NULL));
			}
			(_sub_node_it == NULL) ? NULL : (_sub_node_it = (g_object_unref (_sub_node_it), NULL));
		}
		_tmp5_ = NULL;
		str_indent = (_tmp5_ = g_strnfill ((gulong) (indent * 2), ' '), str_indent = (g_free (str_indent), NULL), _tmp5_);
		fprintf (stdout, "%s],\n", str_indent);
	}
	str_indent = (g_free (str_indent), NULL);
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
}


static int _vala_strcmp0 (const char * str1, const char * str2) {
	if (str1 == NULL) {
		return -(str1 != str2);
	}
	if (str2 == NULL) {
		return str1 != str2;
	}
	return strcmp (str1, str2);
}




