
#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>
#include <gee/hashmap.h>
#include <gee/map.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>
#include <stdio.h>


#define GTK_MATE_TYPE_PATTERN (gtk_mate_pattern_get_type ())
#define GTK_MATE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_PATTERN, GtkMatePattern))
#define GTK_MATE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_PATTERN, GtkMatePatternClass))
#define GTK_MATE_IS_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_PATTERN))
#define GTK_MATE_IS_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_PATTERN))
#define GTK_MATE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_PATTERN, GtkMatePatternClass))

typedef struct _GtkMatePattern GtkMatePattern;
typedef struct _GtkMatePatternClass GtkMatePatternClass;
typedef struct _GtkMatePatternPrivate GtkMatePatternPrivate;

#define GTK_MATE_TYPE_GRAMMAR (gtk_mate_grammar_get_type ())
#define GTK_MATE_GRAMMAR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammar))
#define GTK_MATE_GRAMMAR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammarClass))
#define GTK_MATE_IS_GRAMMAR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_GRAMMAR))
#define GTK_MATE_IS_GRAMMAR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_GRAMMAR))
#define GTK_MATE_GRAMMAR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammarClass))

typedef struct _GtkMateGrammar GtkMateGrammar;
typedef struct _GtkMateGrammarClass GtkMateGrammarClass;

#define PLIST_TYPE_NODE (plist_node_get_type ())
#define PLIST_NODE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PLIST_TYPE_NODE, PListNode))
#define PLIST_NODE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PLIST_TYPE_NODE, PListNodeClass))
#define PLIST_IS_NODE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PLIST_TYPE_NODE))
#define PLIST_IS_NODE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PLIST_TYPE_NODE))
#define PLIST_NODE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PLIST_TYPE_NODE, PListNodeClass))

typedef struct _PListNode PListNode;
typedef struct _PListNodeClass PListNodeClass;

#define PLIST_TYPE_DICT (plist_dict_get_type ())
#define PLIST_DICT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PLIST_TYPE_DICT, PListDict))
#define PLIST_DICT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PLIST_TYPE_DICT, PListDictClass))
#define PLIST_IS_DICT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PLIST_TYPE_DICT))
#define PLIST_IS_DICT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PLIST_TYPE_DICT))
#define PLIST_DICT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PLIST_TYPE_DICT, PListDictClass))

typedef struct _PListDict PListDict;
typedef struct _PListDictClass PListDictClass;

#define GTK_MATE_TYPE_SINGLE_PATTERN (gtk_mate_single_pattern_get_type ())
#define GTK_MATE_SINGLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePattern))
#define GTK_MATE_SINGLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePatternClass))
#define GTK_MATE_IS_SINGLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SINGLE_PATTERN))
#define GTK_MATE_IS_SINGLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SINGLE_PATTERN))
#define GTK_MATE_SINGLE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SINGLE_PATTERN, GtkMateSinglePatternClass))

typedef struct _GtkMateSinglePattern GtkMateSinglePattern;
typedef struct _GtkMateSinglePatternClass GtkMateSinglePatternClass;

#define GTK_MATE_TYPE_INCLUDE_PATTERN (gtk_mate_include_pattern_get_type ())
#define GTK_MATE_INCLUDE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_INCLUDE_PATTERN, GtkMateIncludePattern))
#define GTK_MATE_INCLUDE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_INCLUDE_PATTERN, GtkMateIncludePatternClass))
#define GTK_MATE_IS_INCLUDE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_INCLUDE_PATTERN))
#define GTK_MATE_IS_INCLUDE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_INCLUDE_PATTERN))
#define GTK_MATE_INCLUDE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_INCLUDE_PATTERN, GtkMateIncludePatternClass))

typedef struct _GtkMateIncludePattern GtkMateIncludePattern;
typedef struct _GtkMateIncludePatternClass GtkMateIncludePatternClass;

#define GTK_MATE_TYPE_DOUBLE_PATTERN (gtk_mate_double_pattern_get_type ())
#define GTK_MATE_DOUBLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePattern))
#define GTK_MATE_DOUBLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePatternClass))
#define GTK_MATE_IS_DOUBLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN))
#define GTK_MATE_IS_DOUBLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_DOUBLE_PATTERN))
#define GTK_MATE_DOUBLE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePatternClass))

typedef struct _GtkMateDoublePattern GtkMateDoublePattern;
typedef struct _GtkMateDoublePatternClass GtkMateDoublePatternClass;

#define PLIST_TYPE_STRING (plist_string_get_type ())
#define PLIST_STRING(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PLIST_TYPE_STRING, PListString))
#define PLIST_STRING_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PLIST_TYPE_STRING, PListStringClass))
#define PLIST_IS_STRING(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PLIST_TYPE_STRING))
#define PLIST_IS_STRING_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PLIST_TYPE_STRING))
#define PLIST_STRING_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PLIST_TYPE_STRING, PListStringClass))

typedef struct _PListString PListString;
typedef struct _PListStringClass PListStringClass;
typedef struct _PListNodePrivate PListNodePrivate;
typedef struct _PListStringPrivate PListStringPrivate;
typedef struct _GtkMateGrammarPrivate GtkMateGrammarPrivate;

#define ONIG_TYPE_RX (onig_rx_get_type ())
#define ONIG_RX(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIG_TYPE_RX, OnigRx))
#define ONIG_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIG_TYPE_RX, OnigRxClass))
#define ONIG_IS_RX(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIG_TYPE_RX))
#define ONIG_IS_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIG_TYPE_RX))
#define ONIG_RX_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIG_TYPE_RX, OnigRxClass))

typedef struct _OnigRx OnigRx;
typedef struct _OnigRxClass OnigRxClass;
typedef struct _GtkMateSinglePatternPrivate GtkMateSinglePatternPrivate;

#define PLIST_TYPE_INTEGER (plist_integer_get_type ())
#define PLIST_INTEGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PLIST_TYPE_INTEGER, PListInteger))
#define PLIST_INTEGER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PLIST_TYPE_INTEGER, PListIntegerClass))
#define PLIST_IS_INTEGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PLIST_TYPE_INTEGER))
#define PLIST_IS_INTEGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PLIST_TYPE_INTEGER))
#define PLIST_INTEGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PLIST_TYPE_INTEGER, PListIntegerClass))

typedef struct _PListInteger PListInteger;
typedef struct _PListIntegerClass PListIntegerClass;
typedef struct _PListIntegerPrivate PListIntegerPrivate;
typedef struct _GtkMateDoublePatternPrivate GtkMateDoublePatternPrivate;

#define PLIST_TYPE_ARRAY (plist_array_get_type ())
#define PLIST_ARRAY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PLIST_TYPE_ARRAY, PListArray))
#define PLIST_ARRAY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PLIST_TYPE_ARRAY, PListArrayClass))
#define PLIST_IS_ARRAY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PLIST_TYPE_ARRAY))
#define PLIST_IS_ARRAY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PLIST_TYPE_ARRAY))
#define PLIST_ARRAY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PLIST_TYPE_ARRAY, PListArrayClass))

typedef struct _PListArray PListArray;
typedef struct _PListArrayClass PListArrayClass;
typedef struct _PListArrayPrivate PListArrayPrivate;
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

struct _GtkMatePatternPrivate {
	GtkMateGrammar* _grammar;
};

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

struct _GtkMateGrammar {
	GtkObject parent_instance;
	GtkMateGrammarPrivate * priv;
	char** file_types;
	gint file_types_length1;
	OnigRx* first_line_match;
	char* key_equivalent;
	char* scope_name;
	char* comment;
	GeeArrayList* all_patterns;
	OnigRx* folding_start_marker;
	OnigRx* folding_stop_marker;
	GeeArrayList* patterns;
	GeeHashMap* repository;
	gboolean loaded;
};

struct _GtkMateGrammarClass {
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

struct _PListInteger {
	PListNode parent_instance;
	PListIntegerPrivate * priv;
	gint value;
};

struct _PListIntegerClass {
	PListNodeClass parent_class;
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

struct _PListArray {
	PListNode parent_instance;
	PListArrayPrivate * priv;
	GeeArrayList* array;
};

struct _PListArrayClass {
	PListNodeClass parent_class;
};

struct _GtkMateIncludePattern {
	GtkMatePattern parent_instance;
	GtkMateIncludePatternPrivate * priv;
};

struct _GtkMateIncludePatternClass {
	GtkMatePatternClass parent_class;
};



GType gtk_mate_pattern_get_type (void);
GType gtk_mate_grammar_get_type (void);
#define GTK_MATE_PATTERN_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_TYPE_PATTERN, GtkMatePatternPrivate))
enum  {
	GTK_MATE_PATTERN_DUMMY_PROPERTY,
	GTK_MATE_PATTERN_GRAMMAR
};
extern GeeArrayList* gtk_mate_pattern_all_patterns;
GeeArrayList* gtk_mate_pattern_all_patterns = NULL;
GType plist_node_get_type (void);
GType plist_dict_get_type (void);
PListNode* plist_dict_get (PListDict* self, const char* key);
GType gtk_mate_single_pattern_get_type (void);
GtkMateSinglePattern* gtk_mate_single_pattern_create_from_plist (GeeArrayList* all_patterns, PListDict* pd);
GType gtk_mate_include_pattern_get_type (void);
GtkMateIncludePattern* gtk_mate_include_pattern_create_from_plist (PListDict* pd);
GType gtk_mate_double_pattern_get_type (void);
GtkMateDoublePattern* gtk_mate_double_pattern_create_from_plist (GeeArrayList* all_patterns, PListDict* pd);
GtkMatePattern* gtk_mate_pattern_create_from_plist (GeeArrayList* all_patterns, PListDict* pd);
GType plist_string_get_type (void);
char** plist_dict_keys (PListDict* self, int* result_length1);
GeeHashMap* gtk_mate_pattern_make_captures_from_plist (PListDict* pd);
void gtk_mate_pattern_replace_repository_includes (GeeArrayList* patlist, GtkMateGrammar* g);
void gtk_mate_pattern_replace_base_and_self_includes (GeeArrayList* patlist, GtkMateGrammar* g);
void gtk_mate_pattern_replace_include_patterns (GeeArrayList* patlist, GtkMateGrammar* g);
GType onig_rx_get_type (void);
const char* gtk_mate_grammar_get_name (GtkMateGrammar* self);
static void gtk_mate_pattern_remove_patterns (GeeArrayList* patlist, GeeArrayList* ps);
static void gtk_mate_pattern_add_patterns (GeeArrayList* patlist, GeeArrayList* ps);
GtkMateGrammar* gtk_mate_grammar_find_by_scope_name (const char* scope);
void gtk_mate_grammar_init_for_use (GtkMateGrammar* self);
GtkMatePattern* gtk_mate_pattern_new (void);
GtkMatePattern* gtk_mate_pattern_construct (GType object_type);
GtkMatePattern* gtk_mate_pattern_new (void);
GtkMateGrammar* gtk_mate_pattern_get_grammar (GtkMatePattern* self);
void gtk_mate_pattern_set_grammar (GtkMatePattern* self, GtkMateGrammar* value);
static gpointer gtk_mate_pattern_parent_class = NULL;
static void gtk_mate_pattern_finalize (GObject* obj);
static void gtk_mate_pattern_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void gtk_mate_pattern_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
enum  {
	GTK_MATE_SINGLE_PATTERN_DUMMY_PROPERTY
};
GtkMateSinglePattern* gtk_mate_single_pattern_new (void);
GtkMateSinglePattern* gtk_mate_single_pattern_construct (GType object_type);
OnigRx* onig_rx_make1 (const char* pattern);
GType plist_integer_get_type (void);
GtkMateSinglePattern* gtk_mate_single_pattern_new (void);
static gpointer gtk_mate_single_pattern_parent_class = NULL;
static void gtk_mate_single_pattern_finalize (GObject* obj);
enum  {
	GTK_MATE_DOUBLE_PATTERN_DUMMY_PROPERTY
};
GtkMateDoublePattern* gtk_mate_double_pattern_new (void);
GtkMateDoublePattern* gtk_mate_double_pattern_construct (GType object_type);
GType plist_array_get_type (void);
GtkMateDoublePattern* gtk_mate_double_pattern_new (void);
static gpointer gtk_mate_double_pattern_parent_class = NULL;
static void gtk_mate_double_pattern_finalize (GObject* obj);
enum  {
	GTK_MATE_INCLUDE_PATTERN_DUMMY_PROPERTY
};
GtkMateIncludePattern* gtk_mate_include_pattern_new (void);
GtkMateIncludePattern* gtk_mate_include_pattern_construct (GType object_type);
GtkMateIncludePattern* gtk_mate_include_pattern_new (void);
static gpointer gtk_mate_include_pattern_parent_class = NULL;
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static int _vala_strcmp0 (const char * str1, const char * str2);



GtkMatePattern* gtk_mate_pattern_create_from_plist (GeeArrayList* all_patterns, PListDict* pd) {
	GtkMatePattern* p;
	PListNode* _tmp0_;
	gboolean _tmp1_;
	g_return_val_if_fail (all_patterns != NULL, NULL);
	g_return_val_if_fail (pd != NULL, NULL);
	p = NULL;
	_tmp0_ = NULL;
	if ((_tmp1_ = (_tmp0_ = plist_dict_get (pd, "match")) != NULL, (_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_object_unref (_tmp0_), NULL)), _tmp1_)) {
		GtkMatePattern* _tmp2_;
		_tmp2_ = NULL;
		p = (_tmp2_ = (GtkMatePattern*) gtk_mate_single_pattern_create_from_plist (all_patterns, pd), (p == NULL) ? NULL : (p = (g_object_unref (p), NULL)), _tmp2_);
	} else {
		PListNode* _tmp3_;
		gboolean _tmp4_;
		_tmp3_ = NULL;
		if ((_tmp4_ = (_tmp3_ = plist_dict_get (pd, "include")) != NULL, (_tmp3_ == NULL) ? NULL : (_tmp3_ = (g_object_unref (_tmp3_), NULL)), _tmp4_)) {
			GtkMatePattern* _tmp5_;
			_tmp5_ = NULL;
			p = (_tmp5_ = (GtkMatePattern*) gtk_mate_include_pattern_create_from_plist (pd), (p == NULL) ? NULL : (p = (g_object_unref (p), NULL)), _tmp5_);
		} else {
			PListNode* _tmp6_;
			gboolean _tmp7_;
			_tmp6_ = NULL;
			if ((_tmp7_ = (_tmp6_ = plist_dict_get (pd, "begin")) != NULL, (_tmp6_ == NULL) ? NULL : (_tmp6_ = (g_object_unref (_tmp6_), NULL)), _tmp7_)) {
				GtkMatePattern* _tmp8_;
				_tmp8_ = NULL;
				p = (_tmp8_ = (GtkMatePattern*) gtk_mate_double_pattern_create_from_plist (all_patterns, pd), (p == NULL) ? NULL : (p = (g_object_unref (p), NULL)), _tmp8_);
			}
		}
	}
	return p;
}


GeeHashMap* gtk_mate_pattern_make_captures_from_plist (PListDict* pd) {
	PListDict* pcd;
	PListString* ns;
	GeeHashMap* captures;
	GeeHashMap* _tmp5_;
	if (pd == NULL) {
		return gee_hash_map_new (G_TYPE_INT, NULL, NULL, G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, g_direct_hash, g_direct_equal, g_direct_equal);
	}
	pcd = NULL;
	ns = NULL;
	captures = gee_hash_map_new (G_TYPE_INT, NULL, NULL, G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, g_direct_hash, g_direct_equal, g_direct_equal);
	{
		gint _tmp1_;
		char** s_capnum_collection;
		int s_capnum_collection_length1;
		int s_capnum_it;
		s_capnum_collection = plist_dict_keys (pd, &_tmp1_);
		s_capnum_collection_length1 = _tmp1_;
		for (s_capnum_it = 0; s_capnum_it < _tmp1_; s_capnum_it = s_capnum_it + 1) {
			const char* _tmp4_;
			char* s_capnum;
			_tmp4_ = NULL;
			s_capnum = (_tmp4_ = s_capnum_collection[s_capnum_it], (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_));
			{
				gint capnum;
				PListDict* _tmp2_;
				PListString* _tmp3_;
				capnum = atoi (s_capnum);
				_tmp2_ = NULL;
				pcd = (_tmp2_ = PLIST_DICT (plist_dict_get (pd, s_capnum)), (pcd == NULL) ? NULL : (pcd = (g_object_unref (pcd), NULL)), _tmp2_);
				_tmp3_ = NULL;
				ns = (_tmp3_ = PLIST_STRING (plist_dict_get (pcd, "name")), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp3_);
				/* stdout.printf("capture: %d, %s\n", capnum, ns.str);*/
				gee_map_set ((GeeMap*) captures, GINT_TO_POINTER (capnum), ns->str);
				s_capnum = (g_free (s_capnum), NULL);
			}
		}
		s_capnum_collection = (_vala_array_free (s_capnum_collection, s_capnum_collection_length1, (GDestroyNotify) g_free), NULL);
	}
	_tmp5_ = NULL;
	return (_tmp5_ = captures, (pcd == NULL) ? NULL : (pcd = (g_object_unref (pcd), NULL)), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp5_);
}


void gtk_mate_pattern_replace_include_patterns (GeeArrayList* patlist, GtkMateGrammar* g) {
	g_return_if_fail (patlist != NULL);
	g_return_if_fail (g != NULL);
	/* first replace repository, as repository can include $self*/
	gtk_mate_pattern_replace_repository_includes (patlist, g);
	gtk_mate_pattern_replace_base_and_self_includes (patlist, g);
}


static char* string_substring (const char* self, glong offset, glong len) {
	glong string_length;
	const char* start;
	g_return_val_if_fail (self != NULL, NULL);
	string_length = g_utf8_strlen (self, -1);
	if (offset < 0) {
		offset = string_length + offset;
		g_return_val_if_fail (offset >= 0, NULL);
	} else {
		g_return_val_if_fail (offset <= string_length, NULL);
	}
	if (len < 0) {
		len = string_length - offset;
	}
	g_return_val_if_fail ((offset + len) <= string_length, NULL);
	start = g_utf8_offset_to_pointer (self, offset);
	return g_strndup (start, ((gchar*) g_utf8_offset_to_pointer (start, len)) - ((gchar*) start));
}


void gtk_mate_pattern_replace_repository_includes (GeeArrayList* patlist, GtkMateGrammar* g) {
	GeeArrayList* include_patterns;
	GeeArrayList* patterns_to_include;
	gboolean any_included;
	g_return_if_fail (patlist != NULL);
	g_return_if_fail (g != NULL);
	include_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	patterns_to_include = gee_array_list_new (GTK_MATE_TYPE_PATTERN, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	any_included = TRUE;
	while (any_included) {
		/* stdout.printf("repo replacement pass\n");*/
		any_included = FALSE;
		{
			GeeIterator* _p_it;
			_p_it = gee_iterable_iterator ((GeeIterable*) patlist);
			while (gee_iterator_next (_p_it)) {
				GtkMatePattern* p;
				gboolean _tmp0_;
				p = (GtkMatePattern*) gee_iterator_get (_p_it);
				_tmp0_ = FALSE;
				if (GTK_MATE_IS_INCLUDE_PATTERN (p)) {
					_tmp0_ = g_str_has_prefix (p->name, "#");
				} else {
					_tmp0_ = FALSE;
				}
				if (_tmp0_) {
					char* reponame;
					GeeArrayList* ps;
					gee_collection_add ((GeeCollection*) include_patterns, p);
					reponame = string_substring (p->name, (glong) 1, (glong) (((gint) strlen (p->name)) - 1));
					ps = (GeeArrayList*) gee_map_get ((GeeMap*) g->repository, reponame);
					/* stdout.printf("(%s) getting reponame: %s (%d)\n", this.name, reponame, ps.size);*/
					if (ps != NULL) {
						{
							GeeIterator* _p1_it;
							_p1_it = gee_iterable_iterator ((GeeIterable*) ps);
							while (gee_iterator_next (_p1_it)) {
								GtkMatePattern* p1;
								p1 = (GtkMatePattern*) gee_iterator_get (_p1_it);
								any_included = TRUE;
								gee_collection_add ((GeeCollection*) patterns_to_include, p1);
								(p1 == NULL) ? NULL : (p1 = (g_object_unref (p1), NULL));
							}
							(_p1_it == NULL) ? NULL : (_p1_it = (g_object_unref (_p1_it), NULL));
						}
					} else {
						fprintf (stdout, "warning: couldn't find repository key '%s' in grammar '%s'\n", reponame, gtk_mate_grammar_get_name (g));
					}
					reponame = (g_free (reponame), NULL);
					(ps == NULL) ? NULL : (ps = (g_object_unref (ps), NULL));
				}
				(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
			}
			(_p_it == NULL) ? NULL : (_p_it = (g_object_unref (_p_it), NULL));
		}
		gtk_mate_pattern_remove_patterns (patlist, include_patterns);
		gtk_mate_pattern_add_patterns (patlist, patterns_to_include);
		gee_collection_clear ((GeeCollection*) include_patterns);
		gee_collection_clear ((GeeCollection*) patterns_to_include);
	}
	(include_patterns == NULL) ? NULL : (include_patterns = (g_object_unref (include_patterns), NULL));
	(patterns_to_include == NULL) ? NULL : (patterns_to_include = (g_object_unref (patterns_to_include), NULL));
}


void gtk_mate_pattern_replace_base_and_self_includes (GeeArrayList* patlist, GtkMateGrammar* g) {
	GeeArrayList* include_patterns;
	GeeArrayList* patterns_to_include;
	gboolean already_self;
	GtkMateGrammar* ng;
	g_return_if_fail (patlist != NULL);
	g_return_if_fail (g != NULL);
	include_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	patterns_to_include = gee_array_list_new (GTK_MATE_TYPE_PATTERN, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	already_self = FALSE;
	/* some patterns have $self twice*/
	ng = NULL;
	{
		GeeIterator* _p_it;
		_p_it = gee_iterable_iterator ((GeeIterable*) patlist);
		while (gee_iterator_next (_p_it)) {
			GtkMatePattern* p;
			p = (GtkMatePattern*) gee_iterator_get (_p_it);
			if (GTK_MATE_IS_INCLUDE_PATTERN (p)) {
				if (g_str_has_prefix (p->name, "$")) {
					gboolean _tmp0_;
					gboolean _tmp1_;
					gee_collection_add ((GeeCollection*) include_patterns, p);
					_tmp0_ = FALSE;
					_tmp1_ = FALSE;
					if (_vala_strcmp0 (p->name, "$self") == 0) {
						_tmp1_ = TRUE;
					} else {
						_tmp1_ = _vala_strcmp0 (p->name, "$base") == 0;
					}
					if (_tmp1_) {
						_tmp0_ = !already_self;
					} else {
						_tmp0_ = FALSE;
					}
					if (_tmp0_) {
						already_self = TRUE;
						{
							GeeIterator* _pat_it;
							_pat_it = gee_iterable_iterator ((GeeIterable*) g->patterns);
							while (gee_iterator_next (_pat_it)) {
								GtkMatePattern* pat;
								pat = (GtkMatePattern*) gee_iterator_get (_pat_it);
								gee_collection_add ((GeeCollection*) patterns_to_include, pat);
								(pat == NULL) ? NULL : (pat = (g_object_unref (pat), NULL));
							}
							(_pat_it == NULL) ? NULL : (_pat_it = (g_object_unref (_pat_it), NULL));
						}
					}
				} else {
					GtkMateGrammar* _tmp2_;
					_tmp2_ = NULL;
					if ((ng = (_tmp2_ = gtk_mate_grammar_find_by_scope_name (p->name), (ng == NULL) ? NULL : (ng = (g_object_unref (ng), NULL)), _tmp2_)) != NULL) {
						gtk_mate_grammar_init_for_use (ng);
						gee_collection_add ((GeeCollection*) include_patterns, p);
						{
							GeeIterator* _pat_it;
							_pat_it = gee_iterable_iterator ((GeeIterable*) ng->patterns);
							while (gee_iterator_next (_pat_it)) {
								GtkMatePattern* pat;
								pat = (GtkMatePattern*) gee_iterator_get (_pat_it);
								gee_collection_add ((GeeCollection*) patterns_to_include, pat);
								(pat == NULL) ? NULL : (pat = (g_object_unref (pat), NULL));
							}
							(_pat_it == NULL) ? NULL : (_pat_it = (g_object_unref (_pat_it), NULL));
						}
					} else {
					}
				}
			}
			(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
		}
		(_p_it == NULL) ? NULL : (_p_it = (g_object_unref (_p_it), NULL));
	}
	/*stdout.printf("unknown include pattern: %s\n", p.name);*/
	gtk_mate_pattern_remove_patterns (patlist, include_patterns);
	gtk_mate_pattern_add_patterns (patlist, patterns_to_include);
	(include_patterns == NULL) ? NULL : (include_patterns = (g_object_unref (include_patterns), NULL));
	(patterns_to_include == NULL) ? NULL : (patterns_to_include = (g_object_unref (patterns_to_include), NULL));
	(ng == NULL) ? NULL : (ng = (g_object_unref (ng), NULL));
}


static void gtk_mate_pattern_remove_patterns (GeeArrayList* patlist, GeeArrayList* ps) {
	g_return_if_fail (patlist != NULL);
	g_return_if_fail (ps != NULL);
	{
		GeeIterator* _p_it;
		_p_it = gee_iterable_iterator ((GeeIterable*) ps);
		while (gee_iterator_next (_p_it)) {
			GtkMatePattern* p;
			p = (GtkMatePattern*) gee_iterator_get (_p_it);
			gee_collection_remove ((GeeCollection*) patlist, p);
			(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
		}
		(_p_it == NULL) ? NULL : (_p_it = (g_object_unref (_p_it), NULL));
	}
}


static void gtk_mate_pattern_add_patterns (GeeArrayList* patlist, GeeArrayList* ps) {
	g_return_if_fail (patlist != NULL);
	g_return_if_fail (ps != NULL);
	{
		GeeIterator* _p_it;
		_p_it = gee_iterable_iterator ((GeeIterable*) ps);
		while (gee_iterator_next (_p_it)) {
			GtkMatePattern* p;
			p = (GtkMatePattern*) gee_iterator_get (_p_it);
			gee_collection_add ((GeeCollection*) patlist, p);
			(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
		}
		(_p_it == NULL) ? NULL : (_p_it = (g_object_unref (_p_it), NULL));
	}
}


GtkMatePattern* gtk_mate_pattern_construct (GType object_type) {
	GtkMatePattern * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


GtkMatePattern* gtk_mate_pattern_new (void) {
	return gtk_mate_pattern_construct (GTK_MATE_TYPE_PATTERN);
}


GtkMateGrammar* gtk_mate_pattern_get_grammar (GtkMatePattern* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_grammar;
}


void gtk_mate_pattern_set_grammar (GtkMatePattern* self, GtkMateGrammar* value) {
	GtkMateGrammar* _tmp2_;
	GtkMateGrammar* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_grammar = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->priv->_grammar == NULL) ? NULL : (self->priv->_grammar = (g_object_unref (self->priv->_grammar), NULL)), _tmp2_);
	g_object_notify ((GObject *) self, "grammar");
}


static void gtk_mate_pattern_class_init (GtkMatePatternClass * klass) {
	gtk_mate_pattern_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GtkMatePatternPrivate));
	G_OBJECT_CLASS (klass)->get_property = gtk_mate_pattern_get_property;
	G_OBJECT_CLASS (klass)->set_property = gtk_mate_pattern_set_property;
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_pattern_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_PATTERN_GRAMMAR, g_param_spec_object ("grammar", "grammar", "grammar", GTK_MATE_TYPE_GRAMMAR, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void gtk_mate_pattern_instance_init (GtkMatePattern * self) {
	self->priv = GTK_MATE_PATTERN_GET_PRIVATE (self);
}


static void gtk_mate_pattern_finalize (GObject* obj) {
	GtkMatePattern * self;
	self = GTK_MATE_PATTERN (obj);
	self->name = (g_free (self->name), NULL);
	self->comment = (g_free (self->comment), NULL);
	(self->priv->_grammar == NULL) ? NULL : (self->priv->_grammar = (g_object_unref (self->priv->_grammar), NULL));
	G_OBJECT_CLASS (gtk_mate_pattern_parent_class)->finalize (obj);
}


GType gtk_mate_pattern_get_type (void) {
	static GType gtk_mate_pattern_type_id = 0;
	if (gtk_mate_pattern_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMatePatternClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_pattern_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMatePattern), 0, (GInstanceInitFunc) gtk_mate_pattern_instance_init, NULL };
		gtk_mate_pattern_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMatePattern", &g_define_type_info, 0);
	}
	return gtk_mate_pattern_type_id;
}


static void gtk_mate_pattern_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMatePattern * self;
	gpointer boxed;
	self = GTK_MATE_PATTERN (object);
	switch (property_id) {
		case GTK_MATE_PATTERN_GRAMMAR:
		g_value_set_object (value, gtk_mate_pattern_get_grammar (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_pattern_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GtkMatePattern * self;
	self = GTK_MATE_PATTERN (object);
	switch (property_id) {
		case GTK_MATE_PATTERN_GRAMMAR:
		gtk_mate_pattern_set_grammar (self, g_value_get_object (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


GtkMateSinglePattern* gtk_mate_single_pattern_create_from_plist (GeeArrayList* all_patterns, PListDict* pd) {
	PListString* ns;
	GtkMateSinglePattern* pattern;
	PListString* _tmp0_;
	PListString* _tmp3_;
	OnigRx* _tmp4_;
	PListNode* n;
	GeeHashMap* _tmp5_;
	PListNode* _tmp6_;
	gboolean _tmp7_;
	gboolean _tmp8_;
	GtkMateSinglePattern* _tmp11_;
	g_return_val_if_fail (all_patterns != NULL, NULL);
	g_return_val_if_fail (pd != NULL, NULL);
	ns = NULL;
	pattern = g_object_ref_sink (gtk_mate_single_pattern_new ());
	_tmp0_ = NULL;
	ns = (_tmp0_ = PLIST_STRING (plist_dict_get (pd, "name")), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp0_);
	if (ns != NULL) {
		char* _tmp2_;
		const char* _tmp1_;
		_tmp2_ = NULL;
		_tmp1_ = NULL;
		((GtkMatePattern*) pattern)->name = (_tmp2_ = (_tmp1_ = ns->str, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), ((GtkMatePattern*) pattern)->name = (g_free (((GtkMatePattern*) pattern)->name), NULL), _tmp2_);
	}
	/*stdout.printf("sp: %s\n", ((PList.String) pd.get("name")).str);
	else
	stdout.printf("sp: no name\n");*/
	_tmp3_ = NULL;
	ns = (_tmp3_ = PLIST_STRING (plist_dict_get (pd, "match")), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp3_);
	_tmp4_ = NULL;
	pattern->match = (_tmp4_ = onig_rx_make1 (ns->str), (pattern->match == NULL) ? NULL : (pattern->match = (g_object_unref (pattern->match), NULL)), _tmp4_);
	n = plist_dict_get (pd, "captures");
	_tmp5_ = NULL;
	pattern->captures = (_tmp5_ = gtk_mate_pattern_make_captures_from_plist (PLIST_DICT (n)), (pattern->captures == NULL) ? NULL : (pattern->captures = (g_object_unref (pattern->captures), NULL)), _tmp5_);
	_tmp6_ = NULL;
	n = (_tmp6_ = plist_dict_get (pd, "disabled"), (n == NULL) ? NULL : (n = (g_object_unref (n), NULL)), _tmp6_);
	_tmp7_ = FALSE;
	_tmp8_ = FALSE;
	if (n != NULL) {
		_tmp8_ = PLIST_IS_INTEGER (n);
	} else {
		_tmp8_ = FALSE;
	}
	if (_tmp8_) {
		_tmp7_ = PLIST_INTEGER (n)->value == 1;
	} else {
		_tmp7_ = FALSE;
	}
	if (_tmp7_) {
		((GtkMatePattern*) pattern)->disabled = TRUE;
	} else {
		gboolean _tmp9_;
		gboolean _tmp10_;
		_tmp9_ = FALSE;
		_tmp10_ = FALSE;
		if (n != NULL) {
			_tmp10_ = PLIST_IS_STRING (n);
		} else {
			_tmp10_ = FALSE;
		}
		if (_tmp10_) {
			_tmp9_ = _vala_strcmp0 (PLIST_STRING (n)->str, "1") == 0;
		} else {
			_tmp9_ = FALSE;
		}
		if (_tmp9_) {
			((GtkMatePattern*) pattern)->disabled = TRUE;
		} else {
			((GtkMatePattern*) pattern)->disabled = FALSE;
		}
	}
	gee_collection_add ((GeeCollection*) all_patterns, (GtkMatePattern*) pattern);
	_tmp11_ = NULL;
	return (_tmp11_ = pattern, (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), (n == NULL) ? NULL : (n = (g_object_unref (n), NULL)), _tmp11_);
}


GtkMateSinglePattern* gtk_mate_single_pattern_construct (GType object_type) {
	GtkMateSinglePattern * self;
	self = (GtkMateSinglePattern*) gtk_mate_pattern_construct (object_type);
	return self;
}


GtkMateSinglePattern* gtk_mate_single_pattern_new (void) {
	return gtk_mate_single_pattern_construct (GTK_MATE_TYPE_SINGLE_PATTERN);
}


static void gtk_mate_single_pattern_class_init (GtkMateSinglePatternClass * klass) {
	gtk_mate_single_pattern_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_single_pattern_finalize;
}


static void gtk_mate_single_pattern_instance_init (GtkMateSinglePattern * self) {
}


static void gtk_mate_single_pattern_finalize (GObject* obj) {
	GtkMateSinglePattern * self;
	self = GTK_MATE_SINGLE_PATTERN (obj);
	(self->match == NULL) ? NULL : (self->match = (g_object_unref (self->match), NULL));
	(self->captures == NULL) ? NULL : (self->captures = (g_object_unref (self->captures), NULL));
	G_OBJECT_CLASS (gtk_mate_single_pattern_parent_class)->finalize (obj);
}


GType gtk_mate_single_pattern_get_type (void) {
	static GType gtk_mate_single_pattern_type_id = 0;
	if (gtk_mate_single_pattern_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateSinglePatternClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_single_pattern_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateSinglePattern), 0, (GInstanceInitFunc) gtk_mate_single_pattern_instance_init, NULL };
		gtk_mate_single_pattern_type_id = g_type_register_static (GTK_MATE_TYPE_PATTERN, "GtkMateSinglePattern", &g_define_type_info, 0);
	}
	return gtk_mate_single_pattern_type_id;
}


GtkMateDoublePattern* gtk_mate_double_pattern_create_from_plist (GeeArrayList* all_patterns, PListDict* pd) {
	PListString* ns;
	GtkMateDoublePattern* pattern;
	PListString* _tmp0_;
	PListString* _tmp3_;
	char* _tmp5_;
	const char* _tmp4_;
	OnigRx* _tmp6_;
	PListString* _tmp7_;
	char* _tmp9_;
	const char* _tmp8_;
	PListString* _tmp10_;
	PListNode* n;
	PListNode* _tmp14_;
	PListNode* _tmp16_;
	GeeHashMap* _tmp17_;
	GeeArrayList* _tmp18_;
	PListNode* ps;
	GtkMatePattern* subpattern;
	PListNode* _tmp20_;
	gboolean _tmp21_;
	gboolean _tmp22_;
	GtkMateDoublePattern* _tmp25_;
	g_return_val_if_fail (all_patterns != NULL, NULL);
	g_return_val_if_fail (pd != NULL, NULL);
	ns = NULL;
	pattern = g_object_ref_sink (gtk_mate_double_pattern_new ());
	_tmp0_ = NULL;
	ns = (_tmp0_ = PLIST_STRING (plist_dict_get (pd, "name")), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp0_);
	if (ns != NULL) {
		char* _tmp2_;
		const char* _tmp1_;
		_tmp2_ = NULL;
		_tmp1_ = NULL;
		((GtkMatePattern*) pattern)->name = (_tmp2_ = (_tmp1_ = ns->str, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), ((GtkMatePattern*) pattern)->name = (g_free (((GtkMatePattern*) pattern)->name), NULL), _tmp2_);
	}
	_tmp3_ = NULL;
	ns = (_tmp3_ = PLIST_STRING (plist_dict_get (pd, "begin")), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp3_);
	_tmp5_ = NULL;
	_tmp4_ = NULL;
	pattern->begin_string = (_tmp5_ = (_tmp4_ = ns->str, (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_)), pattern->begin_string = (g_free (pattern->begin_string), NULL), _tmp5_);
	_tmp6_ = NULL;
	pattern->begin = (_tmp6_ = onig_rx_make1 (ns->str), (pattern->begin == NULL) ? NULL : (pattern->begin = (g_object_unref (pattern->begin), NULL)), _tmp6_);
	_tmp7_ = NULL;
	ns = (_tmp7_ = PLIST_STRING (plist_dict_get (pd, "end")), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp7_);
	_tmp9_ = NULL;
	_tmp8_ = NULL;
	pattern->end_string = (_tmp9_ = (_tmp8_ = ns->str, (_tmp8_ == NULL) ? NULL : g_strdup (_tmp8_)), pattern->end_string = (g_free (pattern->end_string), NULL), _tmp9_);
	_tmp10_ = NULL;
	ns = (_tmp10_ = PLIST_STRING (plist_dict_get (pd, "contentName")), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp10_);
	if (ns != NULL) {
		char* _tmp12_;
		const char* _tmp11_;
		_tmp12_ = NULL;
		_tmp11_ = NULL;
		pattern->content_name = (_tmp12_ = (_tmp11_ = ns->str, (_tmp11_ == NULL) ? NULL : g_strdup (_tmp11_)), pattern->content_name = (g_free (pattern->content_name), NULL), _tmp12_);
	}
	n = plist_dict_get (pd, "beginCaptures");
	if (n != NULL) {
		GeeHashMap* _tmp13_;
		_tmp13_ = NULL;
		pattern->begin_captures = (_tmp13_ = gtk_mate_pattern_make_captures_from_plist (PLIST_DICT (n)), (pattern->begin_captures == NULL) ? NULL : (pattern->begin_captures = (g_object_unref (pattern->begin_captures), NULL)), _tmp13_);
	}
	_tmp14_ = NULL;
	n = (_tmp14_ = plist_dict_get (pd, "captures"), (n == NULL) ? NULL : (n = (g_object_unref (n), NULL)), _tmp14_);
	if (n != NULL) {
		GeeHashMap* _tmp15_;
		_tmp15_ = NULL;
		pattern->both_captures = (_tmp15_ = gtk_mate_pattern_make_captures_from_plist (PLIST_DICT (n)), (pattern->both_captures == NULL) ? NULL : (pattern->both_captures = (g_object_unref (pattern->both_captures), NULL)), _tmp15_);
	}
	_tmp16_ = NULL;
	n = (_tmp16_ = plist_dict_get (pd, "endCaptures"), (n == NULL) ? NULL : (n = (g_object_unref (n), NULL)), _tmp16_);
	_tmp17_ = NULL;
	pattern->end_captures = (_tmp17_ = gtk_mate_pattern_make_captures_from_plist (PLIST_DICT (n)), (pattern->end_captures == NULL) ? NULL : (pattern->end_captures = (g_object_unref (pattern->end_captures), NULL)), _tmp17_);
	_tmp18_ = NULL;
	pattern->patterns = (_tmp18_ = gee_array_list_new (GTK_MATE_TYPE_PATTERN, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (pattern->patterns == NULL) ? NULL : (pattern->patterns = (g_object_unref (pattern->patterns), NULL)), _tmp18_);
	ps = plist_dict_get (pd, "patterns");
	subpattern = NULL;
	if (ps != NULL) {
		{
			GeeIterator* _p_it;
			_p_it = gee_iterable_iterator ((GeeIterable*) PLIST_ARRAY (ps)->array);
			while (gee_iterator_next (_p_it)) {
				PListNode* p;
				GtkMatePattern* _tmp19_;
				p = (PListNode*) gee_iterator_get (_p_it);
				_tmp19_ = NULL;
				subpattern = (_tmp19_ = gtk_mate_pattern_create_from_plist (all_patterns, PLIST_DICT (p)), (subpattern == NULL) ? NULL : (subpattern = (g_object_unref (subpattern), NULL)), _tmp19_);
				if (subpattern != NULL) {
					gee_collection_add ((GeeCollection*) pattern->patterns, subpattern);
				}
				(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
			}
			(_p_it == NULL) ? NULL : (_p_it = (g_object_unref (_p_it), NULL));
		}
	}
	_tmp20_ = NULL;
	n = (_tmp20_ = plist_dict_get (pd, "disabled"), (n == NULL) ? NULL : (n = (g_object_unref (n), NULL)), _tmp20_);
	_tmp21_ = FALSE;
	_tmp22_ = FALSE;
	if (n != NULL) {
		_tmp22_ = PLIST_IS_INTEGER (n);
	} else {
		_tmp22_ = FALSE;
	}
	if (_tmp22_) {
		_tmp21_ = PLIST_INTEGER (n)->value == 1;
	} else {
		_tmp21_ = FALSE;
	}
	if (_tmp21_) {
		((GtkMatePattern*) pattern)->disabled = TRUE;
	} else {
		gboolean _tmp23_;
		gboolean _tmp24_;
		_tmp23_ = FALSE;
		_tmp24_ = FALSE;
		if (n != NULL) {
			_tmp24_ = PLIST_IS_STRING (n);
		} else {
			_tmp24_ = FALSE;
		}
		if (_tmp24_) {
			_tmp23_ = _vala_strcmp0 (PLIST_STRING (n)->str, "1") == 0;
		} else {
			_tmp23_ = FALSE;
		}
		if (_tmp23_) {
			((GtkMatePattern*) pattern)->disabled = TRUE;
		} else {
			((GtkMatePattern*) pattern)->disabled = FALSE;
		}
	}
	gee_collection_add ((GeeCollection*) all_patterns, (GtkMatePattern*) pattern);
	_tmp25_ = NULL;
	return (_tmp25_ = pattern, (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), (n == NULL) ? NULL : (n = (g_object_unref (n), NULL)), (ps == NULL) ? NULL : (ps = (g_object_unref (ps), NULL)), (subpattern == NULL) ? NULL : (subpattern = (g_object_unref (subpattern), NULL)), _tmp25_);
}


GtkMateDoublePattern* gtk_mate_double_pattern_construct (GType object_type) {
	GtkMateDoublePattern * self;
	self = (GtkMateDoublePattern*) gtk_mate_pattern_construct (object_type);
	return self;
}


GtkMateDoublePattern* gtk_mate_double_pattern_new (void) {
	return gtk_mate_double_pattern_construct (GTK_MATE_TYPE_DOUBLE_PATTERN);
}


static void gtk_mate_double_pattern_class_init (GtkMateDoublePatternClass * klass) {
	gtk_mate_double_pattern_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_double_pattern_finalize;
}


static void gtk_mate_double_pattern_instance_init (GtkMateDoublePattern * self) {
}


static void gtk_mate_double_pattern_finalize (GObject* obj) {
	GtkMateDoublePattern * self;
	self = GTK_MATE_DOUBLE_PATTERN (obj);
	self->content_name = (g_free (self->content_name), NULL);
	(self->begin == NULL) ? NULL : (self->begin = (g_object_unref (self->begin), NULL));
	(self->end == NULL) ? NULL : (self->end = (g_object_unref (self->end), NULL));
	self->end_string = (g_free (self->end_string), NULL);
	self->begin_string = (g_free (self->begin_string), NULL);
	(self->begin_captures == NULL) ? NULL : (self->begin_captures = (g_object_unref (self->begin_captures), NULL));
	(self->end_captures == NULL) ? NULL : (self->end_captures = (g_object_unref (self->end_captures), NULL));
	(self->both_captures == NULL) ? NULL : (self->both_captures = (g_object_unref (self->both_captures), NULL));
	(self->patterns == NULL) ? NULL : (self->patterns = (g_object_unref (self->patterns), NULL));
	G_OBJECT_CLASS (gtk_mate_double_pattern_parent_class)->finalize (obj);
}


GType gtk_mate_double_pattern_get_type (void) {
	static GType gtk_mate_double_pattern_type_id = 0;
	if (gtk_mate_double_pattern_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateDoublePatternClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_double_pattern_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateDoublePattern), 0, (GInstanceInitFunc) gtk_mate_double_pattern_instance_init, NULL };
		gtk_mate_double_pattern_type_id = g_type_register_static (GTK_MATE_TYPE_PATTERN, "GtkMateDoublePattern", &g_define_type_info, 0);
	}
	return gtk_mate_double_pattern_type_id;
}


GtkMateIncludePattern* gtk_mate_include_pattern_create_from_plist (PListDict* pd) {
	PListString* ns;
	GtkMateIncludePattern* pattern;
	PListString* _tmp0_;
	char* _tmp2_;
	const char* _tmp1_;
	GtkMateIncludePattern* _tmp3_;
	g_return_val_if_fail (pd != NULL, NULL);
	ns = NULL;
	pattern = g_object_ref_sink (gtk_mate_include_pattern_new ());
	_tmp0_ = NULL;
	ns = (_tmp0_ = PLIST_STRING (plist_dict_get (pd, "include")), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp0_);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	((GtkMatePattern*) pattern)->name = (_tmp2_ = (_tmp1_ = ns->str, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), ((GtkMatePattern*) pattern)->name = (g_free (((GtkMatePattern*) pattern)->name), NULL), _tmp2_);
	/* stdout.printf("ip: %s\n", ns.str);*/
	_tmp3_ = NULL;
	return (_tmp3_ = pattern, (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp3_);
}


GtkMateIncludePattern* gtk_mate_include_pattern_construct (GType object_type) {
	GtkMateIncludePattern * self;
	self = (GtkMateIncludePattern*) gtk_mate_pattern_construct (object_type);
	return self;
}


GtkMateIncludePattern* gtk_mate_include_pattern_new (void) {
	return gtk_mate_include_pattern_construct (GTK_MATE_TYPE_INCLUDE_PATTERN);
}


static void gtk_mate_include_pattern_class_init (GtkMateIncludePatternClass * klass) {
	gtk_mate_include_pattern_parent_class = g_type_class_peek_parent (klass);
}


static void gtk_mate_include_pattern_instance_init (GtkMateIncludePattern * self) {
}


GType gtk_mate_include_pattern_get_type (void) {
	static GType gtk_mate_include_pattern_type_id = 0;
	if (gtk_mate_include_pattern_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateIncludePatternClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_include_pattern_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateIncludePattern), 0, (GInstanceInitFunc) gtk_mate_include_pattern_instance_init, NULL };
		gtk_mate_include_pattern_type_id = g_type_register_static (GTK_MATE_TYPE_PATTERN, "GtkMateIncludePattern", &g_define_type_info, 0);
	}
	return gtk_mate_include_pattern_type_id;
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




