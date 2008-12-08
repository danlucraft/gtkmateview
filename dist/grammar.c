
#include "grammar.h"
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>
#include <gee/map.h>
#include "pattern.h"
#include "buffer.h"
#include "bundle.h"




struct _GtkMateGrammarPrivate {
	char* _name;
	PListDict* _plist;
};

#define GTK_MATE_GRAMMAR_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammarPrivate))
enum  {
	GTK_MATE_GRAMMAR_DUMMY_PROPERTY,
	GTK_MATE_GRAMMAR_NAME,
	GTK_MATE_GRAMMAR_PLIST
};
static void gtk_mate_grammar_set_name (GtkMateGrammar* self, const char* value);
static void gtk_mate_grammar_set_plist (GtkMateGrammar* self, PListDict* value);
static gpointer gtk_mate_grammar_parent_class = NULL;
static void gtk_mate_grammar_finalize (GObject* obj);
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
		GeeIterator* bundle_it;
		bundle_it = gee_iterable_iterator ((GeeIterable*) gtk_mate_buffer_bundles);
		while (gee_iterator_next (bundle_it)) {
			GtkMateBundle* bundle;
			bundle = (GtkMateBundle*) gee_iterator_get (bundle_it);
			{
				GeeIterator* gr_it;
				gr_it = gee_iterable_iterator ((GeeIterable*) bundle->grammars);
				while (gee_iterator_next (gr_it)) {
					GtkMateGrammar* gr;
					gr = (GtkMateGrammar*) gee_iterator_get (gr_it);
					if (_vala_strcmp0 (gr->scope_name, scope) == 0) {
						GtkMateGrammar* _tmp0;
						_tmp0 = NULL;
						return (_tmp0 = gr, (gr_it == NULL) ? NULL : (gr_it = (g_object_unref (gr_it), NULL)), (bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL)), (bundle_it == NULL) ? NULL : (bundle_it = (g_object_unref (bundle_it), NULL)), _tmp0);
					}
					(gr == NULL) ? NULL : (gr = (g_object_unref (gr), NULL));
				}
				(gr_it == NULL) ? NULL : (gr_it = (g_object_unref (gr_it), NULL));
			}
			(bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL));
		}
		(bundle_it == NULL) ? NULL : (bundle_it = (g_object_unref (bundle_it), NULL));
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
		gtk_mate_grammar_set_name (self, (PLIST_STRING (nm))->str);
	}
	flm = plist_dict_get (self->priv->_plist, "firstLineMatch");
	if (flm != NULL) {
		OnigRx* _tmp0;
		_tmp0 = NULL;
		self->first_line_match = (_tmp0 = onig_rx_make1 ((PLIST_STRING (flm))->str), (self->first_line_match == NULL) ? NULL : (self->first_line_match = (g_object_unref (self->first_line_match), NULL)), _tmp0);
	}
	ke = plist_dict_get (self->priv->_plist, "keyEquivalent");
	if (ke != NULL) {
		char* _tmp2;
		const char* _tmp1;
		_tmp2 = NULL;
		_tmp1 = NULL;
		self->key_equivalent = (_tmp2 = (_tmp1 = (PLIST_STRING (ke))->str, (_tmp1 == NULL) ? NULL : g_strdup (_tmp1)), self->key_equivalent = (g_free (self->key_equivalent), NULL), _tmp2);
	}
	sn = plist_dict_get (self->priv->_plist, "scopeName");
	if (sn != NULL) {
		char* _tmp4;
		const char* _tmp3;
		_tmp4 = NULL;
		_tmp3 = NULL;
		self->scope_name = (_tmp4 = (_tmp3 = (PLIST_STRING (sn))->str, (_tmp3 == NULL) ? NULL : g_strdup (_tmp3)), self->scope_name = (g_free (self->scope_name), NULL), _tmp4);
	}
	cm = plist_dict_get (self->priv->_plist, "comment");
	if (cm != NULL) {
		char* _tmp6;
		const char* _tmp5;
		_tmp6 = NULL;
		_tmp5 = NULL;
		self->comment = (_tmp6 = (_tmp5 = (PLIST_STRING (cm))->str, (_tmp5 == NULL) ? NULL : g_strdup (_tmp5)), self->comment = (g_free (self->comment), NULL), _tmp6);
	}
	filetypes = plist_dict_get (self->priv->_plist, "fileTypes");
	if (filetypes != NULL) {
		PListArray* _tmp7;
		PListArray* fts;
		char** _tmp9;
		gint _tmp8;
		gint i;
		_tmp7 = NULL;
		fts = (_tmp7 = PLIST_ARRAY (filetypes), (_tmp7 == NULL) ? NULL : g_object_ref (_tmp7));
		_tmp9 = NULL;
		self->file_types = (_tmp9 = g_new0 (char*, (_tmp8 = gee_collection_get_size ((GeeCollection*) fts->array)) + 1), self->file_types = (_vala_array_free (self->file_types, self->file_types_length1, (GDestroyNotify) g_free), NULL), self->file_types_length1 = _tmp8, _tmp9);
		i = 0;
		{
			GeeIterator* n_it;
			n_it = gee_iterable_iterator ((GeeIterable*) fts->array);
			while (gee_iterator_next (n_it)) {
				PListNode* n;
				gint _tmp12;
				char* _tmp11;
				const char* _tmp10;
				n = (PListNode*) gee_iterator_get (n_it);
				_tmp11 = NULL;
				_tmp10 = NULL;
				_tmp12 = i++;
				self->file_types[_tmp12] = (_tmp11 = (_tmp10 = (PLIST_STRING (n))->str, (_tmp10 == NULL) ? NULL : g_strdup (_tmp10)), self->file_types[_tmp12] = (g_free (self->file_types[_tmp12]), NULL), _tmp11);
				(n == NULL) ? NULL : (n = (g_object_unref (n), NULL));
			}
			(n_it == NULL) ? NULL : (n_it = (g_object_unref (n_it), NULL));
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
	GeeArrayList* _tmp2;
	GeeArrayList* _tmp3;
	PListNode* ps;
	GtkMatePattern* pattern;
	GeeHashMap* _tmp5;
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
		OnigRx* _tmp0;
		_tmp0 = NULL;
		self->folding_start_marker = (_tmp0 = onig_rx_make1 ((PLIST_STRING (fsm))->str), (self->folding_start_marker == NULL) ? NULL : (self->folding_start_marker = (g_object_unref (self->folding_start_marker), NULL)), _tmp0);
	}
	ftm = plist_dict_get (self->priv->_plist, "foldingStopMarker");
	if (ftm != NULL) {
		OnigRx* _tmp1;
		_tmp1 = NULL;
		self->folding_stop_marker = (_tmp1 = onig_rx_make1 ((PLIST_STRING (ftm))->str), (self->folding_stop_marker == NULL) ? NULL : (self->folding_stop_marker = (g_object_unref (self->folding_stop_marker), NULL)), _tmp1);
	}
	_tmp2 = NULL;
	self->all_patterns = (_tmp2 = gee_array_list_new (GTK_MATE_TYPE_PATTERN, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->all_patterns == NULL) ? NULL : (self->all_patterns = (g_object_unref (self->all_patterns), NULL)), _tmp2);
	/* stdout.printf("getting patterns\n");*/
	_tmp3 = NULL;
	self->patterns = (_tmp3 = gee_array_list_new (GTK_MATE_TYPE_PATTERN, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->patterns == NULL) ? NULL : (self->patterns = (g_object_unref (self->patterns), NULL)), _tmp3);
	ps = plist_dict_get (self->priv->_plist, "patterns");
	pattern = NULL;
	if (ps != NULL) {
		{
			GeeIterator* p_it;
			p_it = gee_iterable_iterator ((GeeIterable*) (PLIST_ARRAY (ps))->array);
			while (gee_iterator_next (p_it)) {
				PListNode* p;
				GtkMatePattern* _tmp4;
				p = (PListNode*) gee_iterator_get (p_it);
				_tmp4 = NULL;
				pattern = (_tmp4 = gtk_mate_pattern_create_from_plist (self->all_patterns, PLIST_DICT (p)), (pattern == NULL) ? NULL : (pattern = (g_object_unref (pattern), NULL)), _tmp4);
				if (pattern != NULL) {
					gee_collection_add ((GeeCollection*) self->patterns, pattern);
				}
				(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
			}
			(p_it == NULL) ? NULL : (p_it = (g_object_unref (p_it), NULL));
		}
	}
	/* stdout.printf("getting repository\n");*/
	_tmp5 = NULL;
	self->repository = (_tmp5 = gee_hash_map_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, GEE_TYPE_ARRAY_LIST, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_str_hash, g_str_equal, g_direct_equal), (self->repository == NULL) ? NULL : (self->repository = (g_object_unref (self->repository), NULL)), _tmp5);
	pd = PLIST_DICT (plist_dict_get (self->priv->_plist, "repository"));
	pd1 = NULL;
	pa1 = NULL;
	if (pd != NULL) {
		{
			GeeSet* _tmp6;
			GeeIterator* _tmp7;
			GeeIterator* key_it;
			_tmp6 = NULL;
			_tmp7 = NULL;
			key_it = (_tmp7 = gee_iterable_iterator ((GeeIterable*) (_tmp6 = gee_map_get_keys ((GeeMap*) pd->map))), (_tmp6 == NULL) ? NULL : (_tmp6 = (g_object_unref (_tmp6), NULL)), _tmp7);
			while (gee_iterator_next (key_it)) {
				char* key;
				GeeArrayList* repo_array;
				PListDict* _tmp8;
				gboolean _tmp9;
				PListNode* _tmp10;
				gboolean _tmp11;
				key = (char*) gee_iterator_get (key_it);
				/* stdout.printf("convert repo name: %s\n", key);*/
				repo_array = gee_array_list_new (GTK_MATE_TYPE_PATTERN, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
				_tmp8 = NULL;
				pd1 = (_tmp8 = PLIST_DICT (plist_dict_get (pd, key)), (pd1 == NULL) ? NULL : (pd1 = (g_object_unref (pd1), NULL)), _tmp8);
				_tmp9 = FALSE;
				_tmp10 = NULL;
				if ((_tmp11 = (_tmp10 = plist_dict_get (pd1, "begin")) != NULL, (_tmp10 == NULL) ? NULL : (_tmp10 = (g_object_unref (_tmp10), NULL)), _tmp11)) {
					_tmp9 = TRUE;
				} else {
					PListNode* _tmp12;
					_tmp12 = NULL;
					_tmp9 = (_tmp12 = plist_dict_get (pd1, "match")) != NULL;
					(_tmp12 == NULL) ? NULL : (_tmp12 = (g_object_unref (_tmp12), NULL));
				}
				/* repository name can go straight to a pattern*/
				if (_tmp9) {
					GtkMatePattern* _tmp13;
					_tmp13 = NULL;
					pattern = (_tmp13 = gtk_mate_pattern_create_from_plist (self->all_patterns, PLIST_DICT (pd1)), (pattern == NULL) ? NULL : (pattern = (g_object_unref (pattern), NULL)), _tmp13);
					if (pattern != NULL) {
						gee_collection_add ((GeeCollection*) repo_array, pattern);
					}
				} else {
					PListNode* _tmp14;
					/* or it can go to an array of patterns*/
					_tmp14 = NULL;
					pa1 = (_tmp14 = plist_dict_get (pd1, "patterns"), (pa1 == NULL) ? NULL : (pa1 = (g_object_unref (pa1), NULL)), _tmp14);
					{
						GeeIterator* ps1_it;
						ps1_it = gee_iterable_iterator ((GeeIterable*) (PLIST_ARRAY (pa1))->array);
						while (gee_iterator_next (ps1_it)) {
							PListNode* ps1;
							GtkMatePattern* _tmp15;
							ps1 = (PListNode*) gee_iterator_get (ps1_it);
							_tmp15 = NULL;
							pattern = (_tmp15 = gtk_mate_pattern_create_from_plist (self->all_patterns, PLIST_DICT (ps1)), (pattern == NULL) ? NULL : (pattern = (g_object_unref (pattern), NULL)), _tmp15);
							if (pattern != NULL) {
								gee_collection_add ((GeeCollection*) repo_array, pattern);
							}
							(ps1 == NULL) ? NULL : (ps1 = (g_object_unref (ps1), NULL));
						}
						(ps1_it == NULL) ? NULL : (ps1_it = (g_object_unref (ps1_it), NULL));
					}
				}
				gee_map_set ((GeeMap*) self->repository, key, repo_array);
				key = (g_free (key), NULL);
				(repo_array == NULL) ? NULL : (repo_array = (g_object_unref (repo_array), NULL));
			}
			(key_it == NULL) ? NULL : (key_it = (g_object_unref (key_it), NULL));
		}
	}
	/* stdout.printf("all_patterns: %d\n", all_patterns.size);*/
	{
		GeeIterator* p_it;
		/* stdout.printf("all_patterns: %d\n", all_patterns.size);*/
		p_it = gee_iterable_iterator ((GeeIterable*) self->all_patterns);
		/* stdout.printf("all_patterns: %d\n", all_patterns.size);*/
		while (gee_iterator_next (p_it)) {
			GtkMatePattern* p;
			/* stdout.printf("all_patterns: %d\n", all_patterns.size);*/
			p = (GtkMatePattern*) gee_iterator_get (p_it);
			if (GTK_MATE_IS_DOUBLE_PATTERN (p)) {
				gtk_mate_pattern_replace_include_patterns ((GTK_MATE_DOUBLE_PATTERN (p))->patterns, self);
			}
			(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
		}
		(p_it == NULL) ? NULL : (p_it = (g_object_unref (p_it), NULL));
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
	char* _tmp2;
	const char* _tmp1;
	g_return_if_fail (self != NULL);
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_name = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL) ? NULL : g_strdup (_tmp1)), self->priv->_name = (g_free (self->priv->_name), NULL), _tmp2);
	g_object_notify ((GObject *) self, "name");
}


PListDict* gtk_mate_grammar_get_plist (GtkMateGrammar* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_plist;
}


static void gtk_mate_grammar_set_plist (GtkMateGrammar* self, PListDict* value) {
	PListDict* _tmp2;
	PListDict* _tmp1;
	g_return_if_fail (self != NULL);
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_plist = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL) ? NULL : g_object_ref (_tmp1)), (self->priv->_plist == NULL) ? NULL : (self->priv->_plist = (g_object_unref (self->priv->_plist), NULL)), _tmp2);
	g_object_notify ((GObject *) self, "plist");
}


static void gtk_mate_grammar_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateGrammar * self;
	self = GTK_MATE_GRAMMAR (object);
	switch (property_id) {
		case GTK_MATE_GRAMMAR_NAME:
		g_value_set_string (value, gtk_mate_grammar_get_name (self));
		break;
		case GTK_MATE_GRAMMAR_PLIST:
		g_value_set_object (value, gtk_mate_grammar_get_plist (self));
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
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_grammar_class_init (GtkMateGrammarClass * klass) {
	gtk_mate_grammar_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GtkMateGrammarPrivate));
	G_OBJECT_CLASS (klass)->get_property = gtk_mate_grammar_get_property;
	G_OBJECT_CLASS (klass)->set_property = gtk_mate_grammar_set_property;
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_grammar_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_GRAMMAR_NAME, g_param_spec_string ("name", "name", "name", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_GRAMMAR_PLIST, g_param_spec_object ("plist", "plist", "plist", PLIST_TYPE_DICT, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
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


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		if (array_length >= 0)
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL)
			destroy_func (((gpointer*) array)[i]);
		}
		else
		for (i = 0; ((gpointer*) array)[i] != NULL; i = i + 1) {
			destroy_func (((gpointer*) array)[i]);
		}
	}
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




