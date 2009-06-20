
#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>
#include <gee/hashmap.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>
#include <gee/map.h>


#define GTK_MATE_TYPE_GRAMMAR (gtk_mate_grammar_get_type ())
#define GTK_MATE_GRAMMAR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammar))
#define GTK_MATE_GRAMMAR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammarClass))
#define GTK_MATE_IS_GRAMMAR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_GRAMMAR))
#define GTK_MATE_IS_GRAMMAR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_GRAMMAR))
#define GTK_MATE_GRAMMAR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammarClass))

typedef struct _GtkMateGrammar GtkMateGrammar;
typedef struct _GtkMateGrammarClass GtkMateGrammarClass;
typedef struct _GtkMateGrammarPrivate GtkMateGrammarPrivate;

#define ONIG_TYPE_RX (onig_rx_get_type ())
#define ONIG_RX(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIG_TYPE_RX, OnigRx))
#define ONIG_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIG_TYPE_RX, OnigRxClass))
#define ONIG_IS_RX(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIG_TYPE_RX))
#define ONIG_IS_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIG_TYPE_RX))
#define ONIG_RX_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIG_TYPE_RX, OnigRxClass))

typedef struct _OnigRx OnigRx;
typedef struct _OnigRxClass OnigRxClass;

#define GTK_MATE_TYPE_PATTERN (gtk_mate_pattern_get_type ())
#define GTK_MATE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_PATTERN, GtkMatePattern))
#define GTK_MATE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_PATTERN, GtkMatePatternClass))
#define GTK_MATE_IS_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_PATTERN))
#define GTK_MATE_IS_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_PATTERN))
#define GTK_MATE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_PATTERN, GtkMatePatternClass))

typedef struct _GtkMatePattern GtkMatePattern;
typedef struct _GtkMatePatternClass GtkMatePatternClass;

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

#define GTK_MATE_TYPE_BUNDLE (gtk_mate_bundle_get_type ())
#define GTK_MATE_BUNDLE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_BUNDLE, GtkMateBundle))
#define GTK_MATE_BUNDLE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_BUNDLE, GtkMateBundleClass))
#define GTK_MATE_IS_BUNDLE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_BUNDLE))
#define GTK_MATE_IS_BUNDLE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_BUNDLE))
#define GTK_MATE_BUNDLE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_BUNDLE, GtkMateBundleClass))

typedef struct _GtkMateBundle GtkMateBundle;
typedef struct _GtkMateBundleClass GtkMateBundleClass;
typedef struct _GtkMateBundlePrivate GtkMateBundlePrivate;
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

#define GTK_MATE_TYPE_DOUBLE_PATTERN (gtk_mate_double_pattern_get_type ())
#define GTK_MATE_DOUBLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePattern))
#define GTK_MATE_DOUBLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePatternClass))
#define GTK_MATE_IS_DOUBLE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN))
#define GTK_MATE_IS_DOUBLE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_DOUBLE_PATTERN))
#define GTK_MATE_DOUBLE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_DOUBLE_PATTERN, GtkMateDoublePatternClass))

typedef struct _GtkMateDoublePattern GtkMateDoublePattern;
typedef struct _GtkMateDoublePatternClass GtkMateDoublePatternClass;
typedef struct _GtkMatePatternPrivate GtkMatePatternPrivate;
typedef struct _GtkMateDoublePatternPrivate GtkMateDoublePatternPrivate;

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

struct _GtkMateGrammarPrivate {
	char* _name;
	PListDict* _plist;
	char* _filename;
};

struct _GtkMateBundle {
	GtkObject parent_instance;
	GtkMateBundlePrivate * priv;
	GeeArrayList* grammars;
};

struct _GtkMateBundleClass {
	GtkObjectClass parent_class;
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



GType gtk_mate_grammar_get_type (void);
GType onig_rx_get_type (void);
GType gtk_mate_pattern_get_type (void);
GType plist_node_get_type (void);
GType plist_dict_get_type (void);
#define GTK_MATE_GRAMMAR_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammarPrivate))
enum  {
	GTK_MATE_GRAMMAR_DUMMY_PROPERTY,
	GTK_MATE_GRAMMAR_NAME,
	GTK_MATE_GRAMMAR_PLIST,
	GTK_MATE_GRAMMAR_FILENAME
};
static void gtk_mate_grammar_set_plist (GtkMateGrammar* self, PListDict* value);
GtkMateGrammar* gtk_mate_grammar_new (PListDict* plist);
GtkMateGrammar* gtk_mate_grammar_construct (GType object_type, PListDict* plist);
GtkMateGrammar* gtk_mate_grammar_new (PListDict* plist);
extern GeeArrayList* gtk_mate_buffer_bundles;
GType gtk_mate_bundle_get_type (void);
GtkMateGrammar* gtk_mate_grammar_find_by_scope_name (const char* scope);
PListDict* gtk_mate_grammar_get_plist (GtkMateGrammar* self);
PListNode* plist_dict_get (PListDict* self, const char* key);
GType plist_string_get_type (void);
static void gtk_mate_grammar_set_name (GtkMateGrammar* self, const char* value);
OnigRx* onig_rx_make1 (const char* pattern);
GType plist_array_get_type (void);
void gtk_mate_grammar_init_for_reference (GtkMateGrammar* self);
GtkMatePattern* gtk_mate_pattern_create_from_plist (GeeArrayList* all_patterns, PListDict* pd);
void gtk_mate_pattern_set_grammar (GtkMatePattern* self, GtkMateGrammar* value);
GType gtk_mate_double_pattern_get_type (void);
void gtk_mate_pattern_replace_include_patterns (GeeArrayList* patlist, GtkMateGrammar* g);
void gtk_mate_grammar_init_for_use (GtkMateGrammar* self);
const char* gtk_mate_grammar_get_name (GtkMateGrammar* self);
const char* gtk_mate_grammar_get_filename (GtkMateGrammar* self);
void gtk_mate_grammar_set_filename (GtkMateGrammar* self, const char* value);
static gpointer gtk_mate_grammar_parent_class = NULL;
static void gtk_mate_grammar_finalize (GObject* obj);
static void gtk_mate_grammar_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void gtk_mate_grammar_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static int _vala_strcmp0 (const char * str1, const char * str2);



GtkMateGrammar* gtk_mate_grammar_construct (GType object_type, PListDict* plist) {
	GtkMateGrammar * self;
	g_return_val_if_fail (plist != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	gtk_mate_grammar_set_plist (self, plist);
	return self;
}


GtkMateGrammar* gtk_mate_grammar_new (PListDict* plist) {
	return gtk_mate_grammar_construct (GTK_MATE_TYPE_GRAMMAR, plist);
}


GtkMateGrammar* gtk_mate_grammar_find_by_scope_name (const char* scope) {
	g_return_val_if_fail (scope != NULL, NULL);
	{
		GeeIterator* _bundle_it;
		_bundle_it = gee_iterable_iterator ((GeeIterable*) gtk_mate_buffer_bundles);
		while (gee_iterator_next (_bundle_it)) {
			GtkMateBundle* bundle;
			bundle = (GtkMateBundle*) gee_iterator_get (_bundle_it);
			{
				GeeIterator* _gr_it;
				_gr_it = gee_iterable_iterator ((GeeIterable*) bundle->grammars);
				while (gee_iterator_next (_gr_it)) {
					GtkMateGrammar* gr;
					gr = (GtkMateGrammar*) gee_iterator_get (_gr_it);
					if (_vala_strcmp0 (gr->scope_name, scope) == 0) {
						GtkMateGrammar* _tmp0_;
						_tmp0_ = NULL;
						return (_tmp0_ = gr, (_gr_it == NULL) ? NULL : (_gr_it = (g_object_unref (_gr_it), NULL)), (bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL)), (_bundle_it == NULL) ? NULL : (_bundle_it = (g_object_unref (_bundle_it), NULL)), _tmp0_);
					}
					(gr == NULL) ? NULL : (gr = (g_object_unref (gr), NULL));
				}
				(_gr_it == NULL) ? NULL : (_gr_it = (g_object_unref (_gr_it), NULL));
			}
			(bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL));
		}
		(_bundle_it == NULL) ? NULL : (_bundle_it = (g_object_unref (_bundle_it), NULL));
	}
	return NULL;
}


/* Loads the properties that are needed whether or not 
 the grammar ever used.*/
void gtk_mate_grammar_init_for_reference (GtkMateGrammar* self) {
	PListNode* nm;
	PListNode* flm;
	PListNode* ke;
	PListNode* sn;
	PListNode* cm;
	PListNode* filetypes;
	g_return_if_fail (self != NULL);
	nm = plist_dict_get (self->priv->_plist, "name");
	if (nm != NULL) {
		gtk_mate_grammar_set_name (self, PLIST_STRING (nm)->str);
	}
	flm = plist_dict_get (self->priv->_plist, "firstLineMatch");
	if (flm != NULL) {
		OnigRx* _tmp0_;
		_tmp0_ = NULL;
		self->first_line_match = (_tmp0_ = onig_rx_make1 (PLIST_STRING (flm)->str), (self->first_line_match == NULL) ? NULL : (self->first_line_match = (g_object_unref (self->first_line_match), NULL)), _tmp0_);
	}
	ke = plist_dict_get (self->priv->_plist, "keyEquivalent");
	if (ke != NULL) {
		char* _tmp2_;
		const char* _tmp1_;
		_tmp2_ = NULL;
		_tmp1_ = NULL;
		self->key_equivalent = (_tmp2_ = (_tmp1_ = PLIST_STRING (ke)->str, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), self->key_equivalent = (g_free (self->key_equivalent), NULL), _tmp2_);
	}
	sn = plist_dict_get (self->priv->_plist, "scopeName");
	if (sn != NULL) {
		char* _tmp4_;
		const char* _tmp3_;
		_tmp4_ = NULL;
		_tmp3_ = NULL;
		self->scope_name = (_tmp4_ = (_tmp3_ = PLIST_STRING (sn)->str, (_tmp3_ == NULL) ? NULL : g_strdup (_tmp3_)), self->scope_name = (g_free (self->scope_name), NULL), _tmp4_);
	}
	cm = plist_dict_get (self->priv->_plist, "comment");
	if (cm != NULL) {
		char* _tmp6_;
		const char* _tmp5_;
		_tmp6_ = NULL;
		_tmp5_ = NULL;
		self->comment = (_tmp6_ = (_tmp5_ = PLIST_STRING (cm)->str, (_tmp5_ == NULL) ? NULL : g_strdup (_tmp5_)), self->comment = (g_free (self->comment), NULL), _tmp6_);
	}
	filetypes = plist_dict_get (self->priv->_plist, "fileTypes");
	if (filetypes != NULL) {
		PListArray* _tmp7_;
		PListArray* fts;
		char** _tmp9_;
		gint _tmp8_;
		gint i;
		_tmp7_ = NULL;
		fts = (_tmp7_ = PLIST_ARRAY (filetypes), (_tmp7_ == NULL) ? NULL : g_object_ref (_tmp7_));
		_tmp9_ = NULL;
		self->file_types = (_tmp9_ = g_new0 (char*, (_tmp8_ = gee_collection_get_size ((GeeCollection*) fts->array)) + 1), self->file_types = (_vala_array_free (self->file_types, self->file_types_length1, (GDestroyNotify) g_free), NULL), self->file_types_length1 = _tmp8_, _tmp9_);
		i = 0;
		{
			GeeIterator* _n_it;
			_n_it = gee_iterable_iterator ((GeeIterable*) fts->array);
			while (gee_iterator_next (_n_it)) {
				PListNode* n;
				char* _tmp12_;
				char* *_tmp11_;
				const char* _tmp10_;
				n = (PListNode*) gee_iterator_get (_n_it);
				_tmp12_ = NULL;
				_tmp10_ = NULL;
				_tmp11_ = &self->file_types[i++];
				(*_tmp11_) = (_tmp12_ = (_tmp10_ = PLIST_STRING (n)->str, (_tmp10_ == NULL) ? NULL : g_strdup (_tmp10_)), (*_tmp11_) = (g_free ((*_tmp11_)), NULL), _tmp12_);
				(n == NULL) ? NULL : (n = (g_object_unref (n), NULL));
			}
			(_n_it == NULL) ? NULL : (_n_it = (g_object_unref (_n_it), NULL));
		}
		(fts == NULL) ? NULL : (fts = (g_object_unref (fts), NULL));
	}
	(nm == NULL) ? NULL : (nm = (g_object_unref (nm), NULL));
	(flm == NULL) ? NULL : (flm = (g_object_unref (flm), NULL));
	(ke == NULL) ? NULL : (ke = (g_object_unref (ke), NULL));
	(sn == NULL) ? NULL : (sn = (g_object_unref (sn), NULL));
	(cm == NULL) ? NULL : (cm = (g_object_unref (cm), NULL));
	(filetypes == NULL) ? NULL : (filetypes = (g_object_unref (filetypes), NULL));
}


/* Loads the properties of the grammar that are required
 for parsing. Loads patterns into memory, and sets
 up possible patterns.*/
void gtk_mate_grammar_init_for_use (GtkMateGrammar* self) {
	PListNode* fsm;
	PListNode* ftm;
	GeeArrayList* _tmp2_;
	GeeArrayList* _tmp3_;
	PListNode* ps;
	GtkMatePattern* pattern;
	GeeHashMap* _tmp5_;
	PListDict* pd;
	PListDict* pd1;
	PListNode* pa1;
	g_return_if_fail (self != NULL);
	if (self->loaded) {
		return;
	}
	self->loaded = TRUE;
	/*stdout.printf("initializing grammar for use: %s\n", name);*/
	fsm = plist_dict_get (self->priv->_plist, "foldingStartMarker");
	if (fsm != NULL) {
		OnigRx* _tmp0_;
		_tmp0_ = NULL;
		self->folding_start_marker = (_tmp0_ = onig_rx_make1 (PLIST_STRING (fsm)->str), (self->folding_start_marker == NULL) ? NULL : (self->folding_start_marker = (g_object_unref (self->folding_start_marker), NULL)), _tmp0_);
	}
	ftm = plist_dict_get (self->priv->_plist, "foldingStopMarker");
	if (ftm != NULL) {
		OnigRx* _tmp1_;
		_tmp1_ = NULL;
		self->folding_stop_marker = (_tmp1_ = onig_rx_make1 (PLIST_STRING (ftm)->str), (self->folding_stop_marker == NULL) ? NULL : (self->folding_stop_marker = (g_object_unref (self->folding_stop_marker), NULL)), _tmp1_);
	}
	_tmp2_ = NULL;
	self->all_patterns = (_tmp2_ = gee_array_list_new (GTK_MATE_TYPE_PATTERN, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->all_patterns == NULL) ? NULL : (self->all_patterns = (g_object_unref (self->all_patterns), NULL)), _tmp2_);
	/* stdout.printf("getting patterns\n");*/
	_tmp3_ = NULL;
	self->patterns = (_tmp3_ = gee_array_list_new (GTK_MATE_TYPE_PATTERN, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->patterns == NULL) ? NULL : (self->patterns = (g_object_unref (self->patterns), NULL)), _tmp3_);
	ps = plist_dict_get (self->priv->_plist, "patterns");
	pattern = NULL;
	if (ps != NULL) {
		{
			GeeIterator* _p_it;
			_p_it = gee_iterable_iterator ((GeeIterable*) PLIST_ARRAY (ps)->array);
			while (gee_iterator_next (_p_it)) {
				PListNode* p;
				GtkMatePattern* _tmp4_;
				p = (PListNode*) gee_iterator_get (_p_it);
				_tmp4_ = NULL;
				pattern = (_tmp4_ = gtk_mate_pattern_create_from_plist (self->all_patterns, PLIST_DICT (p)), (pattern == NULL) ? NULL : (pattern = (g_object_unref (pattern), NULL)), _tmp4_);
				gtk_mate_pattern_set_grammar (pattern, self);
				if (pattern != NULL) {
					gee_collection_add ((GeeCollection*) self->patterns, pattern);
				}
				(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
			}
			(_p_it == NULL) ? NULL : (_p_it = (g_object_unref (_p_it), NULL));
		}
	}
	/* stdout.printf("getting repository\n");*/
	_tmp5_ = NULL;
	self->repository = (_tmp5_ = gee_hash_map_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, GEE_TYPE_ARRAY_LIST, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_str_hash, g_str_equal, g_direct_equal), (self->repository == NULL) ? NULL : (self->repository = (g_object_unref (self->repository), NULL)), _tmp5_);
	pd = PLIST_DICT (plist_dict_get (self->priv->_plist, "repository"));
	pd1 = NULL;
	pa1 = NULL;
	if (pd != NULL) {
		{
			GeeSet* _tmp6_;
			GeeIterator* _tmp7_;
			GeeIterator* _key_it;
			_tmp6_ = NULL;
			_tmp7_ = NULL;
			_key_it = (_tmp7_ = gee_iterable_iterator ((GeeIterable*) (_tmp6_ = gee_map_get_keys ((GeeMap*) pd->map))), (_tmp6_ == NULL) ? NULL : (_tmp6_ = (g_object_unref (_tmp6_), NULL)), _tmp7_);
			while (gee_iterator_next (_key_it)) {
				char* key;
				GeeArrayList* repo_array;
				PListDict* _tmp8_;
				gboolean _tmp9_;
				PListNode* _tmp10_;
				gboolean _tmp11_;
				key = (char*) gee_iterator_get (_key_it);
				/* stdout.printf("convert repo name: %s\n", key);*/
				repo_array = gee_array_list_new (GTK_MATE_TYPE_PATTERN, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
				_tmp8_ = NULL;
				pd1 = (_tmp8_ = PLIST_DICT (plist_dict_get (pd, key)), (pd1 == NULL) ? NULL : (pd1 = (g_object_unref (pd1), NULL)), _tmp8_);
				_tmp9_ = FALSE;
				_tmp10_ = NULL;
				if ((_tmp11_ = (_tmp10_ = plist_dict_get (pd1, "begin")) != NULL, (_tmp10_ == NULL) ? NULL : (_tmp10_ = (g_object_unref (_tmp10_), NULL)), _tmp11_)) {
					_tmp9_ = TRUE;
				} else {
					PListNode* _tmp12_;
					_tmp12_ = NULL;
					_tmp9_ = (_tmp12_ = plist_dict_get (pd1, "match")) != NULL;
					(_tmp12_ == NULL) ? NULL : (_tmp12_ = (g_object_unref (_tmp12_), NULL));
				}
				/* repository name can go straight to a pattern*/
				if (_tmp9_) {
					GtkMatePattern* _tmp13_;
					_tmp13_ = NULL;
					pattern = (_tmp13_ = gtk_mate_pattern_create_from_plist (self->all_patterns, PLIST_DICT (pd1)), (pattern == NULL) ? NULL : (pattern = (g_object_unref (pattern), NULL)), _tmp13_);
					gtk_mate_pattern_set_grammar (pattern, self);
					if (pattern != NULL) {
						gee_collection_add ((GeeCollection*) repo_array, pattern);
					}
				} else {
					PListNode* _tmp14_;
					_tmp14_ = NULL;
					if ((pa1 = (_tmp14_ = plist_dict_get (pd1, "patterns"), (pa1 == NULL) ? NULL : (pa1 = (g_object_unref (pa1), NULL)), _tmp14_)) != NULL) {
						{
							GeeIterator* _ps1_it;
							_ps1_it = gee_iterable_iterator ((GeeIterable*) PLIST_ARRAY (pa1)->array);
							while (gee_iterator_next (_ps1_it)) {
								PListNode* ps1;
								GtkMatePattern* _tmp15_;
								ps1 = (PListNode*) gee_iterator_get (_ps1_it);
								_tmp15_ = NULL;
								pattern = (_tmp15_ = gtk_mate_pattern_create_from_plist (self->all_patterns, PLIST_DICT (ps1)), (pattern == NULL) ? NULL : (pattern = (g_object_unref (pattern), NULL)), _tmp15_);
								gtk_mate_pattern_set_grammar (pattern, self);
								if (pattern != NULL) {
									gee_collection_add ((GeeCollection*) repo_array, pattern);
								}
								(ps1 == NULL) ? NULL : (ps1 = (g_object_unref (ps1), NULL));
							}
							(_ps1_it == NULL) ? NULL : (_ps1_it = (g_object_unref (_ps1_it), NULL));
						}
					}
				}
				gee_map_set ((GeeMap*) self->repository, key, repo_array);
				key = (g_free (key), NULL);
				(repo_array == NULL) ? NULL : (repo_array = (g_object_unref (repo_array), NULL));
			}
			(_key_it == NULL) ? NULL : (_key_it = (g_object_unref (_key_it), NULL));
		}
	}
	/* stdout.printf("all_patterns: %d\n", all_patterns.size);*/
	{
		GeeIterator* _p_it;
		/* stdout.printf("all_patterns: %d\n", all_patterns.size);*/
		_p_it = gee_iterable_iterator ((GeeIterable*) self->all_patterns);
		/* stdout.printf("all_patterns: %d\n", all_patterns.size);*/
		while (gee_iterator_next (_p_it)) {
			GtkMatePattern* p;
			/* stdout.printf("all_patterns: %d\n", all_patterns.size);*/
			p = (GtkMatePattern*) gee_iterator_get (_p_it);
			if (GTK_MATE_IS_DOUBLE_PATTERN (p)) {
				gtk_mate_pattern_replace_include_patterns (GTK_MATE_DOUBLE_PATTERN (p)->patterns, self);
			}
			(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
		}
		(_p_it == NULL) ? NULL : (_p_it = (g_object_unref (_p_it), NULL));
	}
	gtk_mate_pattern_replace_include_patterns (self->patterns, self);
	(fsm == NULL) ? NULL : (fsm = (g_object_unref (fsm), NULL));
	(ftm == NULL) ? NULL : (ftm = (g_object_unref (ftm), NULL));
	(ps == NULL) ? NULL : (ps = (g_object_unref (ps), NULL));
	(pattern == NULL) ? NULL : (pattern = (g_object_unref (pattern), NULL));
	(pd == NULL) ? NULL : (pd = (g_object_unref (pd), NULL));
	(pd1 == NULL) ? NULL : (pd1 = (g_object_unref (pd1), NULL));
	(pa1 == NULL) ? NULL : (pa1 = (g_object_unref (pa1), NULL));
}


const char* gtk_mate_grammar_get_name (GtkMateGrammar* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_name;
}


static void gtk_mate_grammar_set_name (GtkMateGrammar* self, const char* value) {
	char* _tmp2_;
	const char* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_name = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), self->priv->_name = (g_free (self->priv->_name), NULL), _tmp2_);
	g_object_notify ((GObject *) self, "name");
}


PListDict* gtk_mate_grammar_get_plist (GtkMateGrammar* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_plist;
}


static void gtk_mate_grammar_set_plist (GtkMateGrammar* self, PListDict* value) {
	PListDict* _tmp2_;
	PListDict* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_plist = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->priv->_plist == NULL) ? NULL : (self->priv->_plist = (g_object_unref (self->priv->_plist), NULL)), _tmp2_);
	g_object_notify ((GObject *) self, "plist");
}


const char* gtk_mate_grammar_get_filename (GtkMateGrammar* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_filename;
}


void gtk_mate_grammar_set_filename (GtkMateGrammar* self, const char* value) {
	char* _tmp2_;
	const char* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_filename = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), self->priv->_filename = (g_free (self->priv->_filename), NULL), _tmp2_);
	g_object_notify ((GObject *) self, "filename");
}


static void gtk_mate_grammar_class_init (GtkMateGrammarClass * klass) {
	gtk_mate_grammar_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GtkMateGrammarPrivate));
	G_OBJECT_CLASS (klass)->get_property = gtk_mate_grammar_get_property;
	G_OBJECT_CLASS (klass)->set_property = gtk_mate_grammar_set_property;
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_grammar_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_GRAMMAR_NAME, g_param_spec_string ("name", "name", "name", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_GRAMMAR_PLIST, g_param_spec_object ("plist", "plist", "plist", PLIST_TYPE_DICT, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_GRAMMAR_FILENAME, g_param_spec_string ("filename", "filename", "filename", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void gtk_mate_grammar_instance_init (GtkMateGrammar * self) {
	self->priv = GTK_MATE_GRAMMAR_GET_PRIVATE (self);
}


static void gtk_mate_grammar_finalize (GObject* obj) {
	GtkMateGrammar * self;
	self = GTK_MATE_GRAMMAR (obj);
	self->priv->_name = (g_free (self->priv->_name), NULL);
	(self->priv->_plist == NULL) ? NULL : (self->priv->_plist = (g_object_unref (self->priv->_plist), NULL));
	self->file_types = (_vala_array_free (self->file_types, self->file_types_length1, (GDestroyNotify) g_free), NULL);
	(self->first_line_match == NULL) ? NULL : (self->first_line_match = (g_object_unref (self->first_line_match), NULL));
	self->key_equivalent = (g_free (self->key_equivalent), NULL);
	self->scope_name = (g_free (self->scope_name), NULL);
	self->comment = (g_free (self->comment), NULL);
	(self->all_patterns == NULL) ? NULL : (self->all_patterns = (g_object_unref (self->all_patterns), NULL));
	self->priv->_filename = (g_free (self->priv->_filename), NULL);
	(self->folding_start_marker == NULL) ? NULL : (self->folding_start_marker = (g_object_unref (self->folding_start_marker), NULL));
	(self->folding_stop_marker == NULL) ? NULL : (self->folding_stop_marker = (g_object_unref (self->folding_stop_marker), NULL));
	(self->patterns == NULL) ? NULL : (self->patterns = (g_object_unref (self->patterns), NULL));
	(self->repository == NULL) ? NULL : (self->repository = (g_object_unref (self->repository), NULL));
	G_OBJECT_CLASS (gtk_mate_grammar_parent_class)->finalize (obj);
}


GType gtk_mate_grammar_get_type (void) {
	static GType gtk_mate_grammar_type_id = 0;
	if (gtk_mate_grammar_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateGrammarClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_grammar_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateGrammar), 0, (GInstanceInitFunc) gtk_mate_grammar_instance_init, NULL };
		gtk_mate_grammar_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateGrammar", &g_define_type_info, 0);
	}
	return gtk_mate_grammar_type_id;
}


static void gtk_mate_grammar_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateGrammar * self;
	gpointer boxed;
	self = GTK_MATE_GRAMMAR (object);
	switch (property_id) {
		case GTK_MATE_GRAMMAR_NAME:
		g_value_set_string (value, gtk_mate_grammar_get_name (self));
		break;
		case GTK_MATE_GRAMMAR_PLIST:
		g_value_set_object (value, gtk_mate_grammar_get_plist (self));
		break;
		case GTK_MATE_GRAMMAR_FILENAME:
		g_value_set_string (value, gtk_mate_grammar_get_filename (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_grammar_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GtkMateGrammar * self;
	self = GTK_MATE_GRAMMAR (object);
	switch (property_id) {
		case GTK_MATE_GRAMMAR_NAME:
		gtk_mate_grammar_set_name (self, g_value_get_string (value));
		break;
		case GTK_MATE_GRAMMAR_PLIST:
		gtk_mate_grammar_set_plist (self, g_value_get_object (value));
		break;
		case GTK_MATE_GRAMMAR_FILENAME:
		gtk_mate_grammar_set_filename (self, g_value_get_string (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
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




