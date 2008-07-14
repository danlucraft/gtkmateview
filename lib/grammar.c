
#include "grammar.h"
#include <gee/collection.h>
#include <stdio.h>
#include <gee/map.h>




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
static void gtk_mate_grammar_dispose (GObject * obj);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static int _vala_strcmp0 (const char * str1, const char * str2);



GtkMateGrammar* gtk_mate_grammar_new (PListDict* plist) {
	GtkMateGrammar * self;
	g_return_val_if_fail (PLIST_IS_DICT (plist), NULL);
	self = g_object_newv (GTK_MATE_TYPE_GRAMMAR, 0, NULL);
	gtk_mate_grammar_set_plist (self, plist);
	return self;
}


void gtk_mate_grammar_init_for_reference (GtkMateGrammar* self) {
	PListNode* nm;
	PListNode* flm;
	PListNode* ke;
	PListNode* sn;
	PListNode* cm;
	PListNode* filetypes;
	g_return_if_fail (GTK_MATE_IS_GRAMMAR (self));
	nm = plist_dict_get (self->priv->_plist, "name");
	if (nm != NULL) {
		gtk_mate_grammar_set_name (self, (PLIST_STRING (nm))->str);
	}
	flm = plist_dict_get (self->priv->_plist, "firstLineMatch");
	if (flm != NULL) {
		OnigurumaRegex* _tmp0;
		_tmp0 = NULL;
		self->first_line_match = (_tmp0 = oniguruma_regex_make1 ((PLIST_STRING (flm))->str), (self->first_line_match == NULL ? NULL : (self->first_line_match = (g_object_unref (self->first_line_match), NULL))), _tmp0);
	}
	ke = plist_dict_get (self->priv->_plist, "keyEquivalent");
	if (ke != NULL) {
		char* _tmp2;
		const char* _tmp1;
		_tmp2 = NULL;
		_tmp1 = NULL;
		self->key_equivalent = (_tmp2 = (_tmp1 = (PLIST_STRING (ke))->str, (_tmp1 == NULL ? NULL : g_strdup (_tmp1))), (self->key_equivalent = (g_free (self->key_equivalent), NULL)), _tmp2);
	}
	sn = plist_dict_get (self->priv->_plist, "scopeName");
	if (sn != NULL) {
		char* _tmp4;
		const char* _tmp3;
		_tmp4 = NULL;
		_tmp3 = NULL;
		self->scope_name = (_tmp4 = (_tmp3 = (PLIST_STRING (sn))->str, (_tmp3 == NULL ? NULL : g_strdup (_tmp3))), (self->scope_name = (g_free (self->scope_name), NULL)), _tmp4);
	}
	cm = plist_dict_get (self->priv->_plist, "comment");
	if (cm != NULL) {
		char* _tmp6;
		const char* _tmp5;
		_tmp6 = NULL;
		_tmp5 = NULL;
		self->comment = (_tmp6 = (_tmp5 = (PLIST_STRING (cm))->str, (_tmp5 == NULL ? NULL : g_strdup (_tmp5))), (self->comment = (g_free (self->comment), NULL)), _tmp6);
	}
	filetypes = plist_dict_get (self->priv->_plist, "fileTypes");
	if (filetypes != NULL) {
		PListArray* _tmp7;
		PListArray* fts;
		char** _tmp9;
		gint _tmp8;
		gint i;
		_tmp7 = NULL;
		fts = (_tmp7 = PLIST_ARRAY (filetypes), (_tmp7 == NULL ? NULL : g_object_ref (_tmp7)));
		_tmp9 = NULL;
		self->file_types = (_tmp9 = g_new0 (char*, (_tmp8 = gee_collection_get_size (GEE_COLLECTION (fts->array))) + 1), (self->file_types = (_vala_array_free (self->file_types, self->file_types_length1, ((GDestroyNotify) (g_free))), NULL)), self->file_types_length1 = _tmp8, _tmp9);
		i = 0;
		{
			GeeArrayList* n_collection;
			int n_it;
			n_collection = fts->array;
			for (n_it = 0; n_it < gee_collection_get_size (GEE_COLLECTION (n_collection)); n_it = n_it + 1) {
				PListNode* n;
				n = ((PListNode*) (gee_list_get (GEE_LIST (n_collection), n_it)));
				{
					gint _tmp12;
					char* _tmp11;
					const char* _tmp10;
					_tmp11 = NULL;
					_tmp10 = NULL;
					_tmp12 = i++;
					self->file_types[_tmp12] = (_tmp11 = (_tmp10 = (PLIST_STRING (n))->str, (_tmp10 == NULL ? NULL : g_strdup (_tmp10))), (self->file_types[_tmp12] = (g_free (self->file_types[_tmp12]), NULL)), _tmp11);
					(n == NULL ? NULL : (n = (g_object_unref (n), NULL)));
				}
			}
		}
		(fts == NULL ? NULL : (fts = (g_object_unref (fts), NULL)));
	}
	(nm == NULL ? NULL : (nm = (g_object_unref (nm), NULL)));
	(flm == NULL ? NULL : (flm = (g_object_unref (flm), NULL)));
	(ke == NULL ? NULL : (ke = (g_object_unref (ke), NULL)));
	(sn == NULL ? NULL : (sn = (g_object_unref (sn), NULL)));
	(cm == NULL ? NULL : (cm = (g_object_unref (cm), NULL)));
	(filetypes == NULL ? NULL : (filetypes = (g_object_unref (filetypes), NULL)));
}


GeeArrayList* gtk_mate_grammar_all_patterns (GtkMateGrammar* self) {
	GeeArrayList* _tmp0;
	g_return_val_if_fail (GTK_MATE_IS_GRAMMAR (self), NULL);
	_tmp0 = NULL;
	return (_tmp0 = self->patterns, (_tmp0 == NULL ? NULL : g_object_ref (_tmp0)));
}


void gtk_mate_grammar_init_for_use (GtkMateGrammar* self) {
	PListNode* fsm;
	PListNode* ftm;
	GeeArrayList* _tmp2;
	PListNode* ps;
	GtkMatePattern* pattern;
	GeeHashMap* _tmp4;
	PListDict* pd;
	PListDict* pd1;
	PListNode* pa1;
	GeeArrayList* repo_array;
	g_return_if_fail (GTK_MATE_IS_GRAMMAR (self));
	if (self->loaded) {
		return;
	}
	fprintf (stdout, "initializing grammar for use: %s\n", self->priv->_name);
	fsm = plist_dict_get (self->priv->_plist, "foldingStartMarker");
	if (fsm != NULL) {
		OnigurumaRegex* _tmp0;
		_tmp0 = NULL;
		self->folding_start_marker = (_tmp0 = oniguruma_regex_make1 ((PLIST_STRING (fsm))->str), (self->folding_start_marker == NULL ? NULL : (self->folding_start_marker = (g_object_unref (self->folding_start_marker), NULL))), _tmp0);
	}
	ftm = plist_dict_get (self->priv->_plist, "foldingStopMarker");
	if (ftm != NULL) {
		OnigurumaRegex* _tmp1;
		_tmp1 = NULL;
		self->folding_stop_marker = (_tmp1 = oniguruma_regex_make1 ((PLIST_STRING (ftm))->str), (self->folding_stop_marker == NULL ? NULL : (self->folding_stop_marker = (g_object_unref (self->folding_stop_marker), NULL))), _tmp1);
	}
	_tmp2 = NULL;
	self->patterns = (_tmp2 = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal), (self->patterns == NULL ? NULL : (self->patterns = (g_object_unref (self->patterns), NULL))), _tmp2);
	ps = plist_dict_get (self->priv->_plist, "patterns");
	pattern = NULL;
	if (ps != NULL) {
		{
			GeeArrayList* p_collection;
			int p_it;
			p_collection = (PLIST_ARRAY (ps))->array;
			for (p_it = 0; p_it < gee_collection_get_size (GEE_COLLECTION (p_collection)); p_it = p_it + 1) {
				PListNode* p;
				p = ((PListNode*) (gee_list_get (GEE_LIST (p_collection), p_it)));
				{
					GtkMatePattern* _tmp3;
					_tmp3 = NULL;
					pattern = (_tmp3 = gtk_mate_pattern_create_from_plist (PLIST_DICT (p)), (pattern == NULL ? NULL : (pattern = (g_object_unref (pattern), NULL))), _tmp3);
					if (pattern != NULL) {
						gee_collection_add (GEE_COLLECTION (self->patterns), pattern);
					}
					(p == NULL ? NULL : (p = (g_object_unref (p), NULL)));
				}
			}
		}
	}
	_tmp4 = NULL;
	self->repository = (_tmp4 = gee_hash_map_new (G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, GEE_TYPE_ARRAY_LIST, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_str_hash, g_str_equal, g_direct_equal), (self->repository == NULL ? NULL : (self->repository = (g_object_unref (self->repository), NULL))), _tmp4);
	pd = PLIST_DICT (plist_dict_get (self->priv->_plist, "repository"));
	pd1 = NULL;
	pa1 = NULL;
	repo_array = NULL;
	if (pd != NULL) {
		{
			GeeSet* key_collection;
			GeeIterator* key_it;
			key_collection = gee_map_get_keys (GEE_MAP (pd->map));
			key_it = gee_iterable_iterator (GEE_ITERABLE (key_collection));
			while (gee_iterator_next (key_it)) {
				char* key;
				key = ((char*) (gee_iterator_get (key_it)));
				{
					GeeArrayList* repo_array;
					PListDict* _tmp5;
					PListNode* _tmp7;
					PListNode* _tmp6;
					gboolean _tmp8;
					fprintf (stdout, "convert repo name: %s\n", key);
					repo_array = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
					_tmp5 = NULL;
					pd1 = (_tmp5 = PLIST_DICT (plist_dict_get (pd, key)), (pd1 == NULL ? NULL : (pd1 = (g_object_unref (pd1), NULL))), _tmp5);
					/* repository name can go straight to a pattern*/
					_tmp7 = NULL;
					_tmp6 = NULL;
					if ((_tmp8 = (_tmp6 = plist_dict_get (pd1, "begin")) != NULL || (_tmp7 = plist_dict_get (pd1, "match")) != NULL, (_tmp7 == NULL ? NULL : (_tmp7 = (g_object_unref (_tmp7), NULL))), (_tmp6 == NULL ? NULL : (_tmp6 = (g_object_unref (_tmp6), NULL))), _tmp8)) {
						GtkMatePattern* _tmp9;
						_tmp9 = NULL;
						pattern = (_tmp9 = gtk_mate_pattern_create_from_plist (PLIST_DICT (pd1)), (pattern == NULL ? NULL : (pattern = (g_object_unref (pattern), NULL))), _tmp9);
						if (pattern != NULL) {
							gee_collection_add (GEE_COLLECTION (repo_array), pattern);
						}
					} else {
						PListNode* _tmp10;
						/* or it can go to an array of patterns*/
						_tmp10 = NULL;
						pa1 = (_tmp10 = plist_dict_get (pd1, "patterns"), (pa1 == NULL ? NULL : (pa1 = (g_object_unref (pa1), NULL))), _tmp10);
						{
							GeeArrayList* ps1_collection;
							int ps1_it;
							ps1_collection = (PLIST_ARRAY (pa1))->array;
							for (ps1_it = 0; ps1_it < gee_collection_get_size (GEE_COLLECTION (ps1_collection)); ps1_it = ps1_it + 1) {
								PListNode* ps1;
								ps1 = ((PListNode*) (gee_list_get (GEE_LIST (ps1_collection), ps1_it)));
								{
									GtkMatePattern* _tmp11;
									_tmp11 = NULL;
									pattern = (_tmp11 = gtk_mate_pattern_create_from_plist (PLIST_DICT (ps1)), (pattern == NULL ? NULL : (pattern = (g_object_unref (pattern), NULL))), _tmp11);
									if (pattern != NULL) {
										gee_collection_add (GEE_COLLECTION (repo_array), pattern);
									}
									(ps1 == NULL ? NULL : (ps1 = (g_object_unref (ps1), NULL)));
								}
							}
						}
					}
					gee_map_set (GEE_MAP (self->repository), key, repo_array);
					key = (g_free (key), NULL);
					(repo_array == NULL ? NULL : (repo_array = (g_object_unref (repo_array), NULL)));
				}
			}
			(key_it == NULL ? NULL : (key_it = (g_object_unref (key_it), NULL)));
			(key_collection == NULL ? NULL : (key_collection = (g_object_unref (key_collection), NULL)));
		}
	}
	fprintf (stdout, "replaceing repository %d\n", gee_map_get_size (GEE_MAP (self->repository)));
	{
		GeeSet* key_collection;
		GeeIterator* key_it;
		key_collection = gee_map_get_keys (GEE_MAP (self->repository));
		key_it = gee_iterable_iterator (GEE_ITERABLE (key_collection));
		while (gee_iterator_next (key_it)) {
			char* key;
			key = ((char*) (gee_iterator_get (key_it)));
			{
				GeeArrayList* al;
				GeeArrayList* _tmp12;
				al = ((GeeArrayList*) (gee_map_get (GEE_MAP (self->repository), key)));
				fprintf (stdout, "key: %s, %d\n", key, gee_collection_get_size (GEE_COLLECTION (al)));
				_tmp12 = NULL;
				gtk_mate_grammar_replace_include_patterns (self, NULL, (_tmp12 = ((GeeArrayList*) (gee_map_get (GEE_MAP (self->repository), key)))));
				(_tmp12 == NULL ? NULL : (_tmp12 = (g_object_unref (_tmp12), NULL)));
				if (al == NULL) {
					fprintf (stdout, "key null: %s\n", key);
				}
				{
					GeeArrayList* pt_collection;
					int pt_it;
					pt_collection = ((GeeArrayList*) (gee_map_get (GEE_MAP (self->repository), key)));
					for (pt_it = 0; pt_it < gee_collection_get_size (GEE_COLLECTION (pt_collection)); pt_it = pt_it + 1) {
						GtkMatePattern* pt;
						pt = ((GtkMatePattern*) (gee_list_get (GEE_LIST (pt_collection), pt_it)));
						{
							if (GTK_MATE_IS_DOUBLE_PATTERN (pt)) {
								gtk_mate_grammar_replace_include_patterns (self, GTK_MATE_DOUBLE_PATTERN (pt), (GTK_MATE_DOUBLE_PATTERN (pt))->patterns);
							}
							(pt == NULL ? NULL : (pt = (g_object_unref (pt), NULL)));
						}
					}
					(pt_collection == NULL ? NULL : (pt_collection = (g_object_unref (pt_collection), NULL)));
				}
				key = (g_free (key), NULL);
				(al == NULL ? NULL : (al = (g_object_unref (al), NULL)));
			}
		}
		(key_it == NULL ? NULL : (key_it = (g_object_unref (key_it), NULL)));
		(key_collection == NULL ? NULL : (key_collection = (g_object_unref (key_collection), NULL)));
	}
	fprintf (stdout, "replaceing patterns %d\n", gee_collection_get_size (GEE_COLLECTION (self->patterns)));
	{
		GeeArrayList* pt_collection;
		int pt_it;
		pt_collection = self->patterns;
		for (pt_it = 0; pt_it < gee_collection_get_size (GEE_COLLECTION (pt_collection)); pt_it = pt_it + 1) {
			GtkMatePattern* pt;
			pt = ((GtkMatePattern*) (gee_list_get (GEE_LIST (pt_collection), pt_it)));
			{
				if (pt != NULL && GTK_MATE_IS_DOUBLE_PATTERN (pt)) {
					/*stdout.printf("null!\n");
					else*/
					gtk_mate_grammar_replace_include_patterns (self, GTK_MATE_DOUBLE_PATTERN (pt), (GTK_MATE_DOUBLE_PATTERN (pt))->patterns);
				}
				(pt == NULL ? NULL : (pt = (g_object_unref (pt), NULL)));
			}
		}
	}
	/* repository = null;*/
	self->loaded = TRUE;
	(fsm == NULL ? NULL : (fsm = (g_object_unref (fsm), NULL)));
	(ftm == NULL ? NULL : (ftm = (g_object_unref (ftm), NULL)));
	(ps == NULL ? NULL : (ps = (g_object_unref (ps), NULL)));
	(pattern == NULL ? NULL : (pattern = (g_object_unref (pattern), NULL)));
	(pd == NULL ? NULL : (pd = (g_object_unref (pd), NULL)));
	(pd1 == NULL ? NULL : (pd1 = (g_object_unref (pd1), NULL)));
	(pa1 == NULL ? NULL : (pa1 = (g_object_unref (pa1), NULL)));
	(repo_array == NULL ? NULL : (repo_array = (g_object_unref (repo_array), NULL)));
}


void gtk_mate_grammar_replace_include_patterns (GtkMateGrammar* self, GtkMateDoublePattern* pattern, GeeArrayList* ps) {
	GeeArrayList* include_patterns;
	GeeArrayList* patterns_to_include;
	g_return_if_fail (GTK_MATE_IS_GRAMMAR (self));
	g_return_if_fail (pattern == NULL || GTK_MATE_IS_DOUBLE_PATTERN (pattern));
	g_return_if_fail (GEE_IS_ARRAY_LIST (ps));
	if (pattern == NULL) {
		fprintf (stdout, "replace include patterns for null\n");
	} else {
		fprintf (stdout, "replace include patterns for %s\n", GTK_MATE_PATTERN (pattern)->name);
	}
	include_patterns = gee_array_list_new (GTK_MATE_TYPE_INCLUDE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
	patterns_to_include = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
	/* find include patterns (and deal with subpatterns)*/
	{
		GeeArrayList* p_collection;
		int p_it;
		p_collection = ps;
		for (p_it = 0; p_it < gee_collection_get_size (GEE_COLLECTION (p_collection)); p_it = p_it + 1) {
			GtkMatePattern* p;
			p = ((GtkMatePattern*) (gee_list_get (GEE_LIST (p_collection), p_it)));
			{
				if (GTK_MATE_IS_INCLUDE_PATTERN (p)) {
					gee_collection_add (GEE_COLLECTION (include_patterns), GTK_MATE_INCLUDE_PATTERN (p));
				} else {
					if (GTK_MATE_IS_DOUBLE_PATTERN (p)) {
						gtk_mate_grammar_replace_include_patterns (self, GTK_MATE_DOUBLE_PATTERN (p), (GTK_MATE_DOUBLE_PATTERN (p))->patterns);
					}
				}
				(p == NULL ? NULL : (p = (g_object_unref (p), NULL)));
			}
		}
	}
	/* remove include patterns*/
	{
		GeeArrayList* ip_collection;
		int ip_it;
		ip_collection = include_patterns;
		for (ip_it = 0; ip_it < gee_collection_get_size (GEE_COLLECTION (ip_collection)); ip_it = ip_it + 1) {
			GtkMatePattern* ip;
			ip = ((GtkMatePattern*) (GTK_MATE_PATTERN (gee_list_get (GEE_LIST (ip_collection), ip_it))));
			{
				gee_collection_remove (GEE_COLLECTION (ps), ip);
				(ip == NULL ? NULL : (ip = (g_object_unref (ip), NULL)));
			}
		}
	}
	/* add referenced patterns*/
	{
		GeeArrayList* ip_collection;
		int ip_it;
		ip_collection = include_patterns;
		for (ip_it = 0; ip_it < gee_collection_get_size (GEE_COLLECTION (ip_collection)); ip_it = ip_it + 1) {
			GtkMatePattern* ip;
			ip = ((GtkMatePattern*) (GTK_MATE_PATTERN (gee_list_get (GEE_LIST (ip_collection), ip_it))));
			{
				fprintf (stdout, "includename: %s\n", ip->name);
				if (_vala_strcmp0 (ip->name, "$self") == 0) {
					{
						GeeArrayList* p_collection;
						int p_it;
						p_collection = ps;
						for (p_it = 0; p_it < gee_collection_get_size (GEE_COLLECTION (p_collection)); p_it = p_it + 1) {
							GtkMatePattern* p;
							p = ((GtkMatePattern*) (gee_list_get (GEE_LIST (p_collection), p_it)));
							{
								gee_collection_add (GEE_COLLECTION (patterns_to_include), p);
								(p == NULL ? NULL : (p = (g_object_unref (p), NULL)));
							}
						}
					}
				} else {
					if (_vala_strcmp0 (ip->name, "$base") == 0) {
						{
							GeeArrayList* p_collection;
							int p_it;
							p_collection = self->patterns;
							for (p_it = 0; p_it < gee_collection_get_size (GEE_COLLECTION (p_collection)); p_it = p_it + 1) {
								GtkMatePattern* p;
								p = ((GtkMatePattern*) (gee_list_get (GEE_LIST (p_collection), p_it)));
								{
									gee_collection_add (GEE_COLLECTION (patterns_to_include), p);
									(p == NULL ? NULL : (p = (g_object_unref (p), NULL)));
								}
							}
						}
					} else {
						if (g_str_has_prefix (ip->name, "#")) {
						} else {
						}
					}
				}
				(ip == NULL ? NULL : (ip = (g_object_unref (ip), NULL)));
			}
		}
	}
	(include_patterns == NULL ? NULL : (include_patterns = (g_object_unref (include_patterns), NULL)));
	(patterns_to_include == NULL ? NULL : (patterns_to_include = (g_object_unref (patterns_to_include), NULL)));
}


const char* gtk_mate_grammar_get_name (GtkMateGrammar* self) {
	g_return_val_if_fail (GTK_MATE_IS_GRAMMAR (self), NULL);
	return self->priv->_name;
}


static void gtk_mate_grammar_set_name (GtkMateGrammar* self, const char* value) {
	char* _tmp2;
	const char* _tmp1;
	g_return_if_fail (GTK_MATE_IS_GRAMMAR (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_name = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_strdup (_tmp1))), (self->priv->_name = (g_free (self->priv->_name), NULL)), _tmp2);
}


PListDict* gtk_mate_grammar_get_plist (GtkMateGrammar* self) {
	g_return_val_if_fail (GTK_MATE_IS_GRAMMAR (self), NULL);
	return self->priv->_plist;
}


static void gtk_mate_grammar_set_plist (GtkMateGrammar* self, PListDict* value) {
	PListDict* _tmp2;
	PListDict* _tmp1;
	g_return_if_fail (GTK_MATE_IS_GRAMMAR (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_plist = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (self->priv->_plist == NULL ? NULL : (self->priv->_plist = (g_object_unref (self->priv->_plist), NULL))), _tmp2);
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
	G_OBJECT_CLASS (klass)->dispose = gtk_mate_grammar_dispose;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_GRAMMAR_NAME, g_param_spec_string ("name", "name", "name", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_GRAMMAR_PLIST, g_param_spec_object ("plist", "plist", "plist", PLIST_TYPE_DICT, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void gtk_mate_grammar_instance_init (GtkMateGrammar * self) {
	self->priv = GTK_MATE_GRAMMAR_GET_PRIVATE (self);
}


static void gtk_mate_grammar_dispose (GObject * obj) {
	GtkMateGrammar * self;
	self = GTK_MATE_GRAMMAR (obj);
	self->priv->_name = (g_free (self->priv->_name), NULL);
	(self->priv->_plist == NULL ? NULL : (self->priv->_plist = (g_object_unref (self->priv->_plist), NULL)));
	self->file_types = (_vala_array_free (self->file_types, self->file_types_length1, ((GDestroyNotify) (g_free))), NULL);
	(self->first_line_match == NULL ? NULL : (self->first_line_match = (g_object_unref (self->first_line_match), NULL)));
	self->key_equivalent = (g_free (self->key_equivalent), NULL);
	self->scope_name = (g_free (self->scope_name), NULL);
	self->comment = (g_free (self->comment), NULL);
	(self->folding_start_marker == NULL ? NULL : (self->folding_start_marker = (g_object_unref (self->folding_start_marker), NULL)));
	(self->folding_stop_marker == NULL ? NULL : (self->folding_stop_marker = (g_object_unref (self->folding_stop_marker), NULL)));
	(self->patterns == NULL ? NULL : (self->patterns = (g_object_unref (self->patterns), NULL)));
	(self->repository == NULL ? NULL : (self->repository = (g_object_unref (self->repository), NULL)));
	G_OBJECT_CLASS (gtk_mate_grammar_parent_class)->dispose (obj);
}


GType gtk_mate_grammar_get_type (void) {
	static GType gtk_mate_grammar_type_id = 0;
	if (G_UNLIKELY (gtk_mate_grammar_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateGrammarClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_grammar_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateGrammar), 0, (GInstanceInitFunc) gtk_mate_grammar_instance_init };
		gtk_mate_grammar_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateGrammar", &g_define_type_info, 0);
	}
	return gtk_mate_grammar_type_id;
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




