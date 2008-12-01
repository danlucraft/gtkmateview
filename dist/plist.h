
#ifndef __PLIST_H__
#define __PLIST_H__

#include <glib.h>
#include <glib-object.h>
#include <libxml/tree.h>
#include <stdlib.h>
#include <string.h>
#include <gee/hashmap.h>
#include <gee/arraylist.h>

G_BEGIN_DECLS


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

#define PLIST_TYPE_ARRAY (plist_array_get_type ())
#define PLIST_ARRAY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PLIST_TYPE_ARRAY, PListArray))
#define PLIST_ARRAY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PLIST_TYPE_ARRAY, PListArrayClass))
#define PLIST_IS_ARRAY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PLIST_TYPE_ARRAY))
#define PLIST_IS_ARRAY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PLIST_TYPE_ARRAY))
#define PLIST_ARRAY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PLIST_TYPE_ARRAY, PListArrayClass))

typedef struct _PListArray PListArray;
typedef struct _PListArrayClass PListArrayClass;
typedef struct _PListArrayPrivate PListArrayPrivate;

#define PLIST_TYPE_DICT (plist_dict_get_type ())
#define PLIST_DICT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PLIST_TYPE_DICT, PListDict))
#define PLIST_DICT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PLIST_TYPE_DICT, PListDictClass))
#define PLIST_IS_DICT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PLIST_TYPE_DICT))
#define PLIST_IS_DICT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PLIST_TYPE_DICT))
#define PLIST_DICT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PLIST_TYPE_DICT, PListDictClass))

typedef struct _PListDict PListDict;
typedef struct _PListDictClass PListDictClass;
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
PListNode* plist_node_parse_xml_node (xmlNode* node);
PListNode* plist_node_construct (GType object_type);
PListNode* plist_node_new (void);
GType plist_node_get_type (void);
PListString* plist_string_construct (GType object_type);
PListString* plist_string_new (void);
GType plist_string_get_type (void);
PListInteger* plist_integer_construct (GType object_type);
PListInteger* plist_integer_new (void);
GType plist_integer_get_type (void);
PListNode* plist_array_get (PListArray* self, gint ix);
PListArray* plist_array_parse_array (xmlNode* node);
PListArray* plist_array_construct (GType object_type);
PListArray* plist_array_new (void);
GType plist_array_get_type (void);
PListNode* plist_dict_get (PListDict* self, const char* key);
char** plist_dict_keys (PListDict* self, int* result_length1);
void plist_dict_print_keys (PListDict* self);
PListDict* plist_dict_parse_dict (xmlNode* node);
PListDict* plist_dict_construct (GType object_type);
PListDict* plist_dict_new (void);
GType plist_dict_get_type (void);
PListDict* plist_parse (const char* filename, GError** error);
void plist_print_plist (gint indent, PListNode* node);


G_END_DECLS

#endif
