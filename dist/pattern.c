
#include "pattern.h"
#include <gee/map.h>
#include <gee/collection.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <stdio.h>




enum  {
	GTK_MATE_PATTERN_DUMMY_PROPERTY
};
GeeArrayList* gtk_mate_pattern_all_patterns = NULL;
static void gtk_mate_pattern_remove_patterns (GeeArrayList* patlist, GeeArrayList* ps);
static void gtk_mate_pattern_add_patterns (GeeArrayList* patlist, GeeArrayList* ps);
static gpointer gtk_mate_pattern_parent_class = NULL;
static void gtk_mate_pattern_finalize (GObject* obj);
enum  {
	GTK_MATE_SINGLE_PATTERN_DUMMY_PROPERTY
};
static gpointer gtk_mate_single_pattern_parent_class = NULL;
static void gtk_mate_single_pattern_finalize (GObject* obj);
enum  {
	GTK_MATE_DOUBLE_PATTERN_DUMMY_PROPERTY
};
static gpointer gtk_mate_double_pattern_parent_class = NULL;
static void gtk_mate_double_pattern_finalize (GObject* obj);
enum  {
	GTK_MATE_INCLUDE_PATTERN_DUMMY_PROPERTY
};
static gpointer gtk_mate_include_pattern_parent_class = NULL;
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static int _vala_strcmp0 (const char * str1, const char * str2);



GtkMatePattern* gtk_mate_pattern_create_from_plist (GeeArrayList* all_patterns, PListDict* pd) {
	GtkMatePattern* p;
	PListNode* _tmp0;
	gboolean _tmp1;
	g_return_val_if_fail (all_patterns != NULL, NULL);
	g_return_val_if_fail (pd != NULL, NULL);
	p = NULL;
	_tmp0 = NULL;
	if ((_tmp1 = (_tmp0 = plist_dict_get (pd, "match")) != NULL, (_tmp0 == NULL) ? NULL : (_tmp0 = (g_object_unref (_tmp0), NULL)), _tmp1)) {
		GtkMatePattern* _tmp2;
		_tmp2 = NULL;
		p = (_tmp2 = (GtkMatePattern*) gtk_mate_single_pattern_create_from_plist (all_patterns, pd), (p == NULL) ? NULL : (p = (g_object_unref (p), NULL)), _tmp2);
	} else {
		PListNode* _tmp3;
		gboolean _tmp4;
		_tmp3 = NULL;
		if ((_tmp4 = (_tmp3 = plist_dict_get (pd, "include")) != NULL, (_tmp3 == NULL) ? NULL : (_tmp3 = (g_object_unref (_tmp3), NULL)), _tmp4)) {
			GtkMatePattern* _tmp5;
			_tmp5 = NULL;
			p = (_tmp5 = (GtkMatePattern*) gtk_mate_include_pattern_create_from_plist (pd), (p == NULL) ? NULL : (p = (g_object_unref (p), NULL)), _tmp5);
		} else {
			PListNode* _tmp6;
			gboolean _tmp7;
			_tmp6 = NULL;
			if ((_tmp7 = (_tmp6 = plist_dict_get (pd, "begin")) != NULL, (_tmp6 == NULL) ? NULL : (_tmp6 = (g_object_unref (_tmp6), NULL)), _tmp7)) {
				GtkMatePattern* _tmp8;
				_tmp8 = NULL;
				p = (_tmp8 = (GtkMatePattern*) gtk_mate_double_pattern_create_from_plist (all_patterns, pd), (p == NULL) ? NULL : (p = (g_object_unref (p), NULL)), _tmp8);
			}
		}
	}
	return p;
}


GeeHashMap* gtk_mate_pattern_make_captures_from_plist (PListDict* pd) {
	PListDict* pcd;
	PListString* ns;
	GeeHashMap* captures;
	GeeHashMap* _tmp5;
	if (pd == NULL) {
		return gee_hash_map_new (G_TYPE_INT, NULL, NULL, G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, g_direct_hash, g_direct_equal, g_direct_equal);
	}
	pcd = NULL;
	ns = NULL;
	captures = gee_hash_map_new (G_TYPE_INT, NULL, NULL, G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, g_direct_hash, g_direct_equal, g_direct_equal);
	{
		gint _tmp1;
		char** s_capnum_collection;
		int s_capnum_collection_length1;
		int s_capnum_it;
		s_capnum_collection = plist_dict_keys (pd, &_tmp1);
		s_capnum_collection_length1 = _tmp1;
		for (s_capnum_it = 0; ((_tmp1 != -1) && (s_capnum_it < _tmp1)) || ((_tmp1 == -1) && (s_capnum_collection[s_capnum_it] != NULL)); s_capnum_it = s_capnum_it + 1) {
			const char* _tmp4;
			char* s_capnum;
			_tmp4 = NULL;
			s_capnum = (_tmp4 = s_capnum_collection[s_capnum_it], (_tmp4 == NULL) ? NULL : g_strdup (_tmp4));
			{
				gint capnum;
				PListDict* _tmp2;
				PListString* _tmp3;
				capnum = atoi (s_capnum);
				_tmp2 = NULL;
				pcd = (_tmp2 = PLIST_DICT (plist_dict_get (pd, s_capnum)), (pcd == NULL) ? NULL : (pcd = (g_object_unref (pcd), NULL)), _tmp2);
				_tmp3 = NULL;
				ns = (_tmp3 = PLIST_STRING (plist_dict_get (pcd, "name")), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp3);
				/* stdout.printf("capture: %d, %s\n", capnum, ns.str);*/
				gee_map_set ((GeeMap*) captures, GINT_TO_POINTER (capnum), ns->str);
				s_capnum = (g_free (s_capnum), NULL);
			}
		}
		s_capnum_collection = (_vala_array_free (s_capnum_collection, s_capnum_collection_length1, (GDestroyNotify) g_free), NULL);
	}
	_tmp5 = NULL;
	return (_tmp5 = captures, (pcd == NULL) ? NULL : (pcd = (g_object_unref (pcd), NULL)), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp5);
}


void gtk_mate_pattern_replace_include_patterns (GeeArrayList* patlist, GtkMateGrammar* g) {
	g_return_if_fail (patlist != NULL);
	g_return_if_fail (g != NULL);
	/* first replace repository, as repository can include $self*/
	gtk_mate_pattern_replace_repository_includes (patlist, g);
	gtk_mate_pattern_replace_base_and_self_includes (patlist, g);
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
			GeeIterator* p_it;
			p_it = gee_iterable_iterator ((GeeIterable*) patlist);
			while (gee_iterator_next (p_it)) {
				GtkMatePattern* p;
				gboolean _tmp0;
				p = (GtkMatePattern*) gee_iterator_get (p_it);
				_tmp0 = FALSE;
				if (GTK_MATE_IS_INCLUDE_PATTERN (p)) {
					_tmp0 = g_str_has_prefix (p->name, "#");
				} else {
					_tmp0 = FALSE;
				}
				if (_tmp0) {
					char* _tmp1;
					char* reponame;
					GeeArrayList* ps;
					gee_collection_add ((GeeCollection*) include_patterns, p);
					_tmp1 = NULL;
					reponame = (_tmp1 = g_utf8_offset_to_pointer (p->name, (glong) 1), g_strndup (_tmp1, g_utf8_offset_to_pointer (_tmp1, (glong) (((gint) strlen (p->name)) - 1)) - _tmp1));
					ps = (GeeArrayList*) gee_map_get ((GeeMap*) g->repository, reponame);
					/* stdout.printf("(%s) getting reponame: %s (%d)\n", this.name, reponame, ps.size);*/
					{
						GeeIterator* p1_it;
						/* stdout.printf("(%s) getting reponame: %s (%d)\n", this.name, reponame, ps.size);*/
						p1_it = gee_iterable_iterator ((GeeIterable*) ps);
						/* stdout.printf("(%s) getting reponame: %s (%d)\n", this.name, reponame, ps.size);*/
						while (gee_iterator_next (p1_it)) {
							GtkMatePattern* p1;
							/* stdout.printf("(%s) getting reponame: %s (%d)\n", this.name, reponame, ps.size);*/
							p1 = (GtkMatePattern*) gee_iterator_get (p1_it);
							any_included = TRUE;
							gee_collection_add ((GeeCollection*) patterns_to_include, p1);
							(p1 == NULL) ? NULL : (p1 = (g_object_unref (p1), NULL));
						}
						(p1_it == NULL) ? NULL : (p1_it = (g_object_unref (p1_it), NULL));
					}
					reponame = (g_free (reponame), NULL);
					(ps == NULL) ? NULL : (ps = (g_object_unref (ps), NULL));
				}
				(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
			}
			(p_it == NULL) ? NULL : (p_it = (g_object_unref (p_it), NULL));
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
		GeeIterator* p_it;
		p_it = gee_iterable_iterator ((GeeIterable*) patlist);
		while (gee_iterator_next (p_it)) {
			GtkMatePattern* p;
			p = (GtkMatePattern*) gee_iterator_get (p_it);
			if (GTK_MATE_IS_INCLUDE_PATTERN (p)) {
				if (g_str_has_prefix (p->name, "$")) {
					gboolean _tmp0;
					gboolean _tmp1;
					gee_collection_add ((GeeCollection*) include_patterns, p);
					_tmp0 = FALSE;
					_tmp1 = FALSE;
					if (_vala_strcmp0 (p->name, "$self") == 0) {
						_tmp1 = TRUE;
					} else {
						_tmp1 = _vala_strcmp0 (p->name, "$base") == 0;
					}
					if ((_tmp1)) {
						_tmp0 = !already_self;
					} else {
						_tmp0 = FALSE;
					}
					if (_tmp0) {
						already_self = TRUE;
						{
							GeeIterator* p_it;
							p_it = gee_iterable_iterator ((GeeIterable*) g->patterns);
							while (gee_iterator_next (p_it)) {
								GtkMatePattern* p;
								p = (GtkMatePattern*) gee_iterator_get (p_it);
								gee_collection_add ((GeeCollection*) patterns_to_include, p);
								(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
							}
							(p_it == NULL) ? NULL : (p_it = (g_object_unref (p_it), NULL));
						}
					}
				} else {
					GtkMateGrammar* _tmp2;
					_tmp2 = NULL;
					if ((ng = (_tmp2 = gtk_mate_grammar_find_by_scope_name (p->name), (ng == NULL) ? NULL : (ng = (g_object_unref (ng), NULL)), _tmp2)) != NULL) {
						gtk_mate_grammar_init_for_use (ng);
						gee_collection_add ((GeeCollection*) include_patterns, p);
						{
							GeeIterator* p_it;
							p_it = gee_iterable_iterator ((GeeIterable*) ng->patterns);
							while (gee_iterator_next (p_it)) {
								GtkMatePattern* p;
								p = (GtkMatePattern*) gee_iterator_get (p_it);
								gee_collection_add ((GeeCollection*) patterns_to_include, p);
								(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
							}
							(p_it == NULL) ? NULL : (p_it = (g_object_unref (p_it), NULL));
						}
					} else {
						fprintf (stdout, "unknown include pattern: %s\n", p->name);
					}
				}
			}
			(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
		}
		(p_it == NULL) ? NULL : (p_it = (g_object_unref (p_it), NULL));
	}
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
		GeeIterator* p_it;
		p_it = gee_iterable_iterator ((GeeIterable*) ps);
		while (gee_iterator_next (p_it)) {
			GtkMatePattern* p;
			p = (GtkMatePattern*) gee_iterator_get (p_it);
			gee_collection_remove ((GeeCollection*) patlist, p);
			(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
		}
		(p_it == NULL) ? NULL : (p_it = (g_object_unref (p_it), NULL));
	}
}


static void gtk_mate_pattern_add_patterns (GeeArrayList* patlist, GeeArrayList* ps) {
	g_return_if_fail (patlist != NULL);
	g_return_if_fail (ps != NULL);
	{
		GeeIterator* p_it;
		p_it = gee_iterable_iterator ((GeeIterable*) ps);
		while (gee_iterator_next (p_it)) {
			GtkMatePattern* p;
			p = (GtkMatePattern*) gee_iterator_get (p_it);
			gee_collection_add ((GeeCollection*) patlist, p);
			(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
		}
		(p_it == NULL) ? NULL : (p_it = (g_object_unref (p_it), NULL));
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


static void gtk_mate_pattern_class_init (GtkMatePatternClass * klass) {
	gtk_mate_pattern_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_pattern_finalize;
}


static void gtk_mate_pattern_instance_init (GtkMatePattern * self) {
}


static void gtk_mate_pattern_finalize (GObject* obj) {
	GtkMatePattern * self;
	self = GTK_MATE_PATTERN (obj);
	self->name = (g_free (self->name), NULL);
	self->comment = (g_free (self->comment), NULL);
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


GtkMateSinglePattern* gtk_mate_single_pattern_create_from_plist (GeeArrayList* all_patterns, PListDict* pd) {
	PListString* ns;
	GtkMateSinglePattern* pattern;
	PListString* _tmp0;
	PListString* _tmp3;
	OnigRx* _tmp4;
	PListNode* n;
	GeeHashMap* _tmp5;
	PListNode* _tmp6;
	gboolean _tmp7;
	GtkMateSinglePattern* _tmp8;
	g_return_val_if_fail (all_patterns != NULL, NULL);
	g_return_val_if_fail (pd != NULL, NULL);
	ns = NULL;
	pattern = g_object_ref_sink (gtk_mate_single_pattern_new ());
	_tmp0 = NULL;
	ns = (_tmp0 = PLIST_STRING (plist_dict_get (pd, "name")), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp0);
	if (ns != NULL) {
		char* _tmp2;
		const char* _tmp1;
		_tmp2 = NULL;
		_tmp1 = NULL;
		((GtkMatePattern*) pattern)->name = (_tmp2 = (_tmp1 = ns->str, (_tmp1 == NULL) ? NULL : g_strdup (_tmp1)), ((GtkMatePattern*) pattern)->name = (g_free (((GtkMatePattern*) pattern)->name), NULL), _tmp2);
	}
	/*stdout.printf("sp: %s\n", ((PList.String) pd.get("name")).str);
	else
	stdout.printf("sp: no name\n");*/
	_tmp3 = NULL;
	ns = (_tmp3 = PLIST_STRING (plist_dict_get (pd, "match")), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp3);
	_tmp4 = NULL;
	pattern->match = (_tmp4 = onig_rx_make1 (ns->str), (pattern->match == NULL) ? NULL : (pattern->match = (g_object_unref (pattern->match), NULL)), _tmp4);
	n = plist_dict_get (pd, "captures");
	_tmp5 = NULL;
	pattern->captures = (_tmp5 = gtk_mate_pattern_make_captures_from_plist (PLIST_DICT (n)), (pattern->captures == NULL) ? NULL : (pattern->captures = (g_object_unref (pattern->captures), NULL)), _tmp5);
	_tmp6 = NULL;
	n = (_tmp6 = plist_dict_get (pd, "disabled"), (n == NULL) ? NULL : (n = (g_object_unref (n), NULL)), _tmp6);
	_tmp7 = FALSE;
	if (n != NULL) {
		_tmp7 = (PLIST_INTEGER (n))->value == 1;
	} else {
		_tmp7 = FALSE;
	}
	if (_tmp7) {
		((GtkMatePattern*) pattern)->disabled = TRUE;
	} else {
		((GtkMatePattern*) pattern)->disabled = FALSE;
	}
	gee_collection_add ((GeeCollection*) all_patterns, (GtkMatePattern*) pattern);
	_tmp8 = NULL;
	return (_tmp8 = pattern, (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), (n == NULL) ? NULL : (n = (g_object_unref (n), NULL)), _tmp8);
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
	PListString* _tmp0;
	PListString* _tmp3;
	char* _tmp5;
	const char* _tmp4;
	OnigRx* _tmp6;
	PListString* _tmp7;
	char* _tmp9;
	const char* _tmp8;
	PListString* _tmp10;
	PListNode* n;
	PListNode* _tmp14;
	PListNode* _tmp16;
	GeeHashMap* _tmp17;
	GeeArrayList* _tmp18;
	PListNode* ps;
	GtkMatePattern* subpattern;
	PListNode* _tmp20;
	gboolean _tmp21;
	GtkMateDoublePattern* _tmp22;
	g_return_val_if_fail (all_patterns != NULL, NULL);
	g_return_val_if_fail (pd != NULL, NULL);
	ns = NULL;
	pattern = g_object_ref_sink (gtk_mate_double_pattern_new ());
	_tmp0 = NULL;
	ns = (_tmp0 = PLIST_STRING (plist_dict_get (pd, "name")), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp0);
	if (ns != NULL) {
		char* _tmp2;
		const char* _tmp1;
		_tmp2 = NULL;
		_tmp1 = NULL;
		((GtkMatePattern*) pattern)->name = (_tmp2 = (_tmp1 = ns->str, (_tmp1 == NULL) ? NULL : g_strdup (_tmp1)), ((GtkMatePattern*) pattern)->name = (g_free (((GtkMatePattern*) pattern)->name), NULL), _tmp2);
	}
	_tmp3 = NULL;
	ns = (_tmp3 = PLIST_STRING (plist_dict_get (pd, "begin")), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp3);
	_tmp5 = NULL;
	_tmp4 = NULL;
	pattern->begin_string = (_tmp5 = (_tmp4 = ns->str, (_tmp4 == NULL) ? NULL : g_strdup (_tmp4)), pattern->begin_string = (g_free (pattern->begin_string), NULL), _tmp5);
	_tmp6 = NULL;
	pattern->begin = (_tmp6 = onig_rx_make1 (ns->str), (pattern->begin == NULL) ? NULL : (pattern->begin = (g_object_unref (pattern->begin), NULL)), _tmp6);
	_tmp7 = NULL;
	ns = (_tmp7 = PLIST_STRING (plist_dict_get (pd, "end")), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp7);
	_tmp9 = NULL;
	_tmp8 = NULL;
	pattern->end_string = (_tmp9 = (_tmp8 = ns->str, (_tmp8 == NULL) ? NULL : g_strdup (_tmp8)), pattern->end_string = (g_free (pattern->end_string), NULL), _tmp9);
	_tmp10 = NULL;
	ns = (_tmp10 = PLIST_STRING (plist_dict_get (pd, "contentName")), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp10);
	if (ns != NULL) {
		char* _tmp12;
		const char* _tmp11;
		_tmp12 = NULL;
		_tmp11 = NULL;
		pattern->content_name = (_tmp12 = (_tmp11 = ns->str, (_tmp11 == NULL) ? NULL : g_strdup (_tmp11)), pattern->content_name = (g_free (pattern->content_name), NULL), _tmp12);
	}
	n = plist_dict_get (pd, "beginCaptures");
	if (n != NULL) {
		GeeHashMap* _tmp13;
		_tmp13 = NULL;
		pattern->begin_captures = (_tmp13 = gtk_mate_pattern_make_captures_from_plist (PLIST_DICT (n)), (pattern->begin_captures == NULL) ? NULL : (pattern->begin_captures = (g_object_unref (pattern->begin_captures), NULL)), _tmp13);
	}
	_tmp14 = NULL;
	n = (_tmp14 = plist_dict_get (pd, "captures"), (n == NULL) ? NULL : (n = (g_object_unref (n), NULL)), _tmp14);
	if (n != NULL) {
		GeeHashMap* _tmp15;
		_tmp15 = NULL;
		pattern->both_captures = (_tmp15 = gtk_mate_pattern_make_captures_from_plist (PLIST_DICT (n)), (pattern->both_captures == NULL) ? NULL : (pattern->both_captures = (g_object_unref (pattern->both_captures), NULL)), _tmp15);
	}
	_tmp16 = NULL;
	n = (_tmp16 = plist_dict_get (pd, "endCaptures"), (n == NULL) ? NULL : (n = (g_object_unref (n), NULL)), _tmp16);
	_tmp17 = NULL;
	pattern->end_captures = (_tmp17 = gtk_mate_pattern_make_captures_from_plist (PLIST_DICT (n)), (pattern->end_captures == NULL) ? NULL : (pattern->end_captures = (g_object_unref (pattern->end_captures), NULL)), _tmp17);
	_tmp18 = NULL;
	pattern->patterns = (_tmp18 = gee_array_list_new (GTK_MATE_TYPE_PATTERN, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (pattern->patterns == NULL) ? NULL : (pattern->patterns = (g_object_unref (pattern->patterns), NULL)), _tmp18);
	ps = plist_dict_get (pd, "patterns");
	subpattern = NULL;
	if (ps != NULL) {
		{
			GeeIterator* p_it;
			p_it = gee_iterable_iterator ((GeeIterable*) (PLIST_ARRAY (ps))->array);
			while (gee_iterator_next (p_it)) {
				PListNode* p;
				GtkMatePattern* _tmp19;
				p = (PListNode*) gee_iterator_get (p_it);
				_tmp19 = NULL;
				subpattern = (_tmp19 = gtk_mate_pattern_create_from_plist (all_patterns, PLIST_DICT (p)), (subpattern == NULL) ? NULL : (subpattern = (g_object_unref (subpattern), NULL)), _tmp19);
				if (subpattern != NULL) {
					gee_collection_add ((GeeCollection*) pattern->patterns, subpattern);
				}
				(p == NULL) ? NULL : (p = (g_object_unref (p), NULL));
			}
			(p_it == NULL) ? NULL : (p_it = (g_object_unref (p_it), NULL));
		}
	}
	_tmp20 = NULL;
	n = (_tmp20 = plist_dict_get (pd, "disabled"), (n == NULL) ? NULL : (n = (g_object_unref (n), NULL)), _tmp20);
	_tmp21 = FALSE;
	if (n != NULL) {
		_tmp21 = (PLIST_INTEGER (n))->value == 1;
	} else {
		_tmp21 = FALSE;
	}
	if (_tmp21) {
		((GtkMatePattern*) pattern)->disabled = TRUE;
	} else {
		((GtkMatePattern*) pattern)->disabled = FALSE;
	}
	gee_collection_add ((GeeCollection*) all_patterns, (GtkMatePattern*) pattern);
	_tmp22 = NULL;
	return (_tmp22 = pattern, (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), (n == NULL) ? NULL : (n = (g_object_unref (n), NULL)), (ps == NULL) ? NULL : (ps = (g_object_unref (ps), NULL)), (subpattern == NULL) ? NULL : (subpattern = (g_object_unref (subpattern), NULL)), _tmp22);
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
	PListString* _tmp0;
	char* _tmp2;
	const char* _tmp1;
	GtkMateIncludePattern* _tmp3;
	g_return_val_if_fail (pd != NULL, NULL);
	ns = NULL;
	pattern = g_object_ref_sink (gtk_mate_include_pattern_new ());
	_tmp0 = NULL;
	ns = (_tmp0 = PLIST_STRING (plist_dict_get (pd, "include")), (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp0);
	_tmp2 = NULL;
	_tmp1 = NULL;
	((GtkMatePattern*) pattern)->name = (_tmp2 = (_tmp1 = ns->str, (_tmp1 == NULL) ? NULL : g_strdup (_tmp1)), ((GtkMatePattern*) pattern)->name = (g_free (((GtkMatePattern*) pattern)->name), NULL), _tmp2);
	/* stdout.printf("ip: %s\n", ns.str);*/
	_tmp3 = NULL;
	return (_tmp3 = pattern, (ns == NULL) ? NULL : (ns = (g_object_unref (ns), NULL)), _tmp3);
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




