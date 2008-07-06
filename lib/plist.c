
#include "plist.h"
#include <gee/list.h>
#include <gee/collection.h>
#include <gee/map.h>
#include <stdio.h>
#include <libxml/parser.h>




enum  {
	PLIST_NODE_DUMMY_PROPERTY
};
static gpointer plist_node_parent_class = NULL;
enum  {
	PLIST_STRING_DUMMY_PROPERTY
};
static gpointer plist_string_parent_class = NULL;
static void plist_string_dispose (GObject * obj);
enum  {
	PLIST_ARRAY_DUMMY_PROPERTY
};
static GObject * plist_array_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer plist_array_parent_class = NULL;
static void plist_array_dispose (GObject * obj);
enum  {
	PLIST_DICT_DUMMY_PROPERTY
};
static GObject * plist_dict_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer plist_dict_parent_class = NULL;
static void plist_dict_dispose (GObject * obj);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static int _vala_strcmp0 (const char * str1, const char * str2);



GQuark xml_error_quark (void) {
	return g_quark_from_static_string ("xml_error-quark");
}


PListNode* plist_node_parse_xml_node (xmlNode* node) {
	if (_vala_strcmp0 (node->name, "string") == 0) {
		PListString* string_node;
		char* _tmp0;
		string_node = plist_string_new ();
		_tmp0 = NULL;
		string_node->str = (_tmp0 = xmlNodeGetContent (node), (string_node->str = (g_free (string_node->str), NULL)), _tmp0);
		return PLIST_NODE (string_node);
	}
	if (_vala_strcmp0 (node->name, "dict") == 0) {
		return PLIST_NODE (plist_dict_parse_dict (node));
	}
	if (_vala_strcmp0 (node->name, "array") == 0) {
		return PLIST_NODE (plist_array_parse_array (node));
	}
	return NULL;
}


PListNode* plist_node_new (void) {
	PListNode * self;
	self = g_object_newv (PLIST_TYPE_NODE, 0, NULL);
	return self;
}


static void plist_node_class_init (PListNodeClass * klass) {
	plist_node_parent_class = g_type_class_peek_parent (klass);
}


static void plist_node_instance_init (PListNode * self) {
}


GType plist_node_get_type (void) {
	static GType plist_node_type_id = 0;
	if (G_UNLIKELY (plist_node_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (PListNodeClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) plist_node_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (PListNode), 0, (GInstanceInitFunc) plist_node_instance_init };
		plist_node_type_id = g_type_register_static (G_TYPE_OBJECT, "PListNode", &g_define_type_info, 0);
	}
	return plist_node_type_id;
}


PListString* plist_string_new (void) {
	PListString * self;
	self = g_object_newv (PLIST_TYPE_STRING, 0, NULL);
	return self;
}


static void plist_string_class_init (PListStringClass * klass) {
	plist_string_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->dispose = plist_string_dispose;
}


static void plist_string_instance_init (PListString * self) {
}


static void plist_string_dispose (GObject * obj) {
	PListString * self;
	self = PLIST_STRING (obj);
	self->str = (g_free (self->str), NULL);
	G_OBJECT_CLASS (plist_string_parent_class)->dispose (obj);
}


GType plist_string_get_type (void) {
	static GType plist_string_type_id = 0;
	if (G_UNLIKELY (plist_string_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (PListStringClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) plist_string_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (PListString), 0, (GInstanceInitFunc) plist_string_instance_init };
		plist_string_type_id = g_type_register_static (PLIST_TYPE_NODE, "PListString", &g_define_type_info, 0);
	}
	return plist_string_type_id;
}


PListNode* plist_array_get (PListArray* self, gint ix) {
	g_return_val_if_fail (PLIST_IS_ARRAY (self), NULL);
	return ((PListNode*) (gee_list_get (GEE_LIST (self->array), ix)));
}


PListArray* plist_array_parse_array (xmlNode* node) {
	PListArray* array;
	PListString* string_node;
	PListArray* _tmp1;
	array = plist_array_new ();
	string_node = NULL;
	{
		xmlNode* iter;
		iter = node->children;
		for (; iter != NULL; iter = iter->next) {
			PListNode* _tmp0;
			if (iter->type != XML_ELEMENT_NODE) {
				continue;
			}
			_tmp0 = NULL;
			gee_collection_add (GEE_COLLECTION (array->array), (_tmp0 = plist_node_parse_xml_node (iter)));
			(_tmp0 == NULL ? NULL : (_tmp0 = (g_object_unref (_tmp0), NULL)));
		}
	}
	_tmp1 = NULL;
	return (_tmp1 = array, (string_node == NULL ? NULL : (string_node = (g_object_unref (string_node), NULL))), _tmp1);
}


PListArray* plist_array_new (void) {
	PListArray * self;
	self = g_object_newv (PLIST_TYPE_ARRAY, 0, NULL);
	return self;
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
		GeeArrayList* _tmp0;
		_tmp0 = NULL;
		self->array = (_tmp0 = gee_array_list_new (PLIST_TYPE_NODE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal), (self->array == NULL ? NULL : (self->array = (g_object_unref (self->array), NULL))), _tmp0);
	}
	return obj;
}


static void plist_array_class_init (PListArrayClass * klass) {
	plist_array_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = plist_array_constructor;
	G_OBJECT_CLASS (klass)->dispose = plist_array_dispose;
}


static void plist_array_instance_init (PListArray * self) {
}


static void plist_array_dispose (GObject * obj) {
	PListArray * self;
	self = PLIST_ARRAY (obj);
	(self->array == NULL ? NULL : (self->array = (g_object_unref (self->array), NULL)));
	G_OBJECT_CLASS (plist_array_parent_class)->dispose (obj);
}


GType plist_array_get_type (void) {
	static GType plist_array_type_id = 0;
	if (G_UNLIKELY (plist_array_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (PListArrayClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) plist_array_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (PListArray), 0, (GInstanceInitFunc) plist_array_instance_init };
		plist_array_type_id = g_type_register_static (PLIST_TYPE_NODE, "PListArray", &g_define_type_info, 0);
	}
	return plist_array_type_id;
}


PListNode* plist_dict_get (PListDict* self, const char* key) {
	g_return_val_if_fail (PLIST_IS_DICT (self), NULL);
	g_return_val_if_fail (key != NULL, NULL);
	return ((PListNode*) (gee_map_get (GEE_MAP (self->map), key)));
}


char** plist_dict_keys (PListDict* self, int* result_length1) {
	char** _tmp3;
	gint ks_length1;
	gint _tmp1;
	GeeSet* _tmp0;
	char** _tmp2;
	char** ks;
	gint i;
	char** _tmp6;
	g_return_val_if_fail (PLIST_IS_DICT (self), NULL);
	_tmp3 = NULL;
	_tmp0 = NULL;
	_tmp2 = NULL;
	ks = (_tmp3 = (_tmp2 = g_new0 (char*, (_tmp1 = gee_collection_get_size (GEE_COLLECTION ((_tmp0 = gee_map_get_keys (GEE_MAP (self->map)))))) + 1), (_tmp0 == NULL ? NULL : (_tmp0 = (g_object_unref (_tmp0), NULL))), _tmp2), ks_length1 = _tmp1, _tmp3);
	i = 0;
	{
		GeeSet* s_collection;
		GeeIterator* s_it;
		s_collection = gee_map_get_keys (GEE_MAP (self->map));
		s_it = gee_iterable_iterator (GEE_ITERABLE (s_collection));
		while (gee_iterator_next (s_it)) {
			char* s;
			s = ((char*) (gee_iterator_get (s_it)));
			{
				char* _tmp5;
				const char* _tmp4;
				_tmp5 = NULL;
				_tmp4 = NULL;
				ks[i] = (_tmp5 = (_tmp4 = s, (_tmp4 == NULL ? NULL : g_strdup (_tmp4))), (ks[i] = (g_free (ks[i]), NULL)), _tmp5);
				i = i + (1);
				s = (g_free (s), NULL);
			}
		}
		(s_it == NULL ? NULL : (s_it = (g_object_unref (s_it), NULL)));
		(s_collection == NULL ? NULL : (s_collection = (g_object_unref (s_collection), NULL)));
	}
	_tmp6 = NULL;
	return (_tmp6 = ks, (*result_length1) = ks_length1, _tmp6);
}


void plist_dict_print_keys (PListDict* self) {
	g_return_if_fail (PLIST_IS_DICT (self));
	{
		gint _tmp0;
		char** s_collection;
		int s_collection_length1;
		int s_it;
		s_collection = plist_dict_keys (self, &_tmp0);
		s_collection_length1 = _tmp0;
		for (s_it = 0; (_tmp0 != -1 && s_it < _tmp0) || (_tmp0 == -1 && s_collection[s_it] != NULL); s_it = s_it + 1) {
			const char* _tmp1;
			char* s;
			_tmp1 = NULL;
			s = (_tmp1 = s_collection[s_it], (_tmp1 == NULL ? NULL : g_strdup (_tmp1)));
			{
				fprintf (stdout, "key: %s\n", s);
				s = (g_free (s), NULL);
			}
		}
		s_collection = (_vala_array_free (s_collection, s_collection_length1, ((GDestroyNotify) (g_free))), NULL);
	}
}


PListDict* plist_dict_parse_dict (xmlNode* node) {
	PListDict* dict;
	char* key;
	PListString* string_node;
	PListDict* _tmp3;
	dict = plist_dict_new ();
	key = NULL;
	string_node = NULL;
	{
		xmlNode* iter;
		iter = node->children;
		for (; iter != NULL; iter = iter->next) {
			if (iter->type != XML_ELEMENT_NODE) {
				continue;
			}
			if (key == NULL) {
				char* _tmp0;
				_tmp0 = NULL;
				key = (_tmp0 = xmlNodeGetContent (iter), (key = (g_free (key), NULL)), _tmp0);
			} else {
				PListNode* _tmp1;
				char* _tmp2;
				_tmp1 = NULL;
				gee_map_set (GEE_MAP (dict->map), key, (_tmp1 = plist_node_parse_xml_node (iter)));
				(_tmp1 == NULL ? NULL : (_tmp1 = (g_object_unref (_tmp1), NULL)));
				_tmp2 = NULL;
				key = (_tmp2 = NULL, (key = (g_free (key), NULL)), _tmp2);
			}
		}
	}
	_tmp3 = NULL;
	return (_tmp3 = dict, (key = (g_free (key), NULL)), (string_node == NULL ? NULL : (string_node = (g_object_unref (string_node), NULL))), _tmp3);
}


PListDict* plist_dict_new (void) {
	PListDict * self;
	self = g_object_newv (PLIST_TYPE_DICT, 0, NULL);
	return self;
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
		GeeHashMap* _tmp1;
		_tmp1 = NULL;
		self->map = (_tmp1 = gee_hash_map_new (G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, PLIST_TYPE_NODE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_str_hash, g_str_equal, g_direct_equal), (self->map == NULL ? NULL : (self->map = (g_object_unref (self->map), NULL))), _tmp1);
	}
	return obj;
}


static void plist_dict_class_init (PListDictClass * klass) {
	plist_dict_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = plist_dict_constructor;
	G_OBJECT_CLASS (klass)->dispose = plist_dict_dispose;
}


static void plist_dict_instance_init (PListDict * self) {
}


static void plist_dict_dispose (GObject * obj) {
	PListDict * self;
	self = PLIST_DICT (obj);
	(self->map == NULL ? NULL : (self->map = (g_object_unref (self->map), NULL)));
	G_OBJECT_CLASS (plist_dict_parent_class)->dispose (obj);
}


GType plist_dict_get_type (void) {
	static GType plist_dict_type_id = 0;
	if (G_UNLIKELY (plist_dict_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (PListDictClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) plist_dict_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (PListDict), 0, (GInstanceInitFunc) plist_dict_instance_init };
		plist_dict_type_id = g_type_register_static (PLIST_TYPE_NODE, "PListDict", &g_define_type_info, 0);
	}
	return plist_dict_type_id;
}


PListDict* plist_parse (const char* filename, GError** error) {
	GError * inner_error;
	xmlDoc* xml_doc;
	xmlNode* root_node;
	xmlNode* top_node;
	PListDict* dict;
	g_return_val_if_fail (filename != NULL, NULL);
	inner_error = NULL;
	xml_doc = xmlParseFile (filename);
	if (xml_doc == NULL) {
		char* _tmp1;
		char* _tmp0;
		GError* _tmp2;
		_tmp1 = NULL;
		_tmp0 = NULL;
		_tmp2 = NULL;
		inner_error = (_tmp2 = g_error_new (XML_ERROR, XML_ERROR_FILE_NOT_FOUND, (_tmp1 = g_strconcat ((_tmp0 = g_strconcat ("file ", filename, NULL)), " not found or permissions missing", NULL))), (_tmp1 = (g_free (_tmp1), NULL)), (_tmp0 = (g_free (_tmp0), NULL)), _tmp2);
		if (inner_error != NULL) {
			g_propagate_error (error, inner_error);
			return NULL;
		}
	}
	root_node = xmlDocGetRootElement (xml_doc);
	if (root_node == NULL) {
		char* _tmp4;
		char* _tmp3;
		GError* _tmp5;
		/*free the document manually before throwing because the garbage collector can't work on pointers*/
		xmlFreeDoc (xml_doc);
		_tmp4 = NULL;
		_tmp3 = NULL;
		_tmp5 = NULL;
		inner_error = (_tmp5 = g_error_new (XML_ERROR, XML_ERROR_XML_DOCUMENT_EMPTY, (_tmp4 = g_strconcat ((_tmp3 = g_strconcat ("the xml'", filename, NULL)), "' is empty", NULL))), (_tmp4 = (g_free (_tmp4), NULL)), (_tmp3 = (g_free (_tmp3), NULL)), _tmp5);
		if (inner_error != NULL) {
			g_propagate_error (error, inner_error);
			return NULL;
		}
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
	return dict;
}


void plist_print_plist (gint indent, PListNode* node) {
	char* str_indent;
	g_return_if_fail (PLIST_IS_NODE (node));
	str_indent = g_strnfill (((gulong) (indent * 2)), ' ');
	if (PLIST_IS_STRING (node)) {
		fprintf (stdout, "%s%s,\n", str_indent, (PLIST_STRING (node))->str);
	}
	if (PLIST_IS_DICT (node)) {
		char* _tmp0;
		char* _tmp1;
		fprintf (stdout, "%s{\n", str_indent);
		_tmp0 = NULL;
		str_indent = (_tmp0 = g_strnfill (((gulong) ((indent + 1) * 2)), ' '), (str_indent = (g_free (str_indent), NULL)), _tmp0);
		{
			GeeSet* key_collection;
			GeeIterator* key_it;
			key_collection = gee_map_get_keys (GEE_MAP ((PLIST_DICT (node))->map));
			key_it = gee_iterable_iterator (GEE_ITERABLE (key_collection));
			while (gee_iterator_next (key_it)) {
				char* key;
				key = ((char*) (gee_iterator_get (key_it)));
				{
					PListNode* value;
					fprintf (stdout, "%s%s => ", str_indent, key);
					value = ((PListNode*) (gee_map_get (GEE_MAP ((PLIST_DICT (node))->map), key)));
					if (PLIST_IS_STRING (value)) {
						fprintf (stdout, "\"%s\",\n", (PLIST_STRING (value))->str);
					} else {
						fprintf (stdout, "\n");
						plist_print_plist (indent + 1, value);
					}
					key = (g_free (key), NULL);
					(value == NULL ? NULL : (value = (g_object_unref (value), NULL)));
				}
			}
			(key_it == NULL ? NULL : (key_it = (g_object_unref (key_it), NULL)));
			(key_collection == NULL ? NULL : (key_collection = (g_object_unref (key_collection), NULL)));
		}
		_tmp1 = NULL;
		str_indent = (_tmp1 = g_strnfill (((gulong) (indent * 2)), ' '), (str_indent = (g_free (str_indent), NULL)), _tmp1);
		fprintf (stdout, "%s},\n", str_indent);
	}
	if (PLIST_IS_ARRAY (node)) {
		char* _tmp2;
		char* _tmp3;
		fprintf (stdout, "%s[\n", str_indent);
		_tmp2 = NULL;
		str_indent = (_tmp2 = g_strnfill (((gulong) ((indent + 1) * 2)), ' '), (str_indent = (g_free (str_indent), NULL)), _tmp2);
		{
			GeeArrayList* sub_node_collection;
			int sub_node_it;
			sub_node_collection = (PLIST_ARRAY (node))->array;
			for (sub_node_it = 0; sub_node_it < gee_collection_get_size (GEE_COLLECTION (sub_node_collection)); sub_node_it = sub_node_it + 1) {
				PListNode* sub_node;
				sub_node = ((PListNode*) (gee_list_get (GEE_LIST (sub_node_collection), sub_node_it)));
				{
					plist_print_plist (indent + 1, sub_node);
					(sub_node == NULL ? NULL : (sub_node = (g_object_unref (sub_node), NULL)));
				}
			}
		}
		_tmp3 = NULL;
		str_indent = (_tmp3 = g_strnfill (((gulong) (indent * 2)), ' '), (str_indent = (g_free (str_indent), NULL)), _tmp3);
		fprintf (stdout, "%s],\n", str_indent);
	}
	str_indent = (g_free (str_indent), NULL);
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if (array != NULL && destroy_func != NULL) {
		int i;
		if (array_length >= 0)
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) (array))[i] != NULL)
			destroy_func (((gpointer*) (array))[i]);
		}
		else
		for (i = 0; ((gpointer*) (array))[i] != NULL; i = i + 1) {
			destroy_func (((gpointer*) (array))[i]);
		}
	}
	g_free (array);
}


static int _vala_strcmp0 (const char * str1, const char * str2) {
	if (str1 == NULL) {
		return -(str1 != str2);
	}
	if (str2 == NULL) {
		return (str1 != str2);
	}
	return strcmp (str1, str2);
}




