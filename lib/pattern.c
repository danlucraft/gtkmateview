
#include "pattern.h"
#include <gee/collection.h>




enum  {
	GTK_MATE_PATTERN_DUMMY_PROPERTY
};
GeeArrayList* gtk_mate_pattern_all_patterns = NULL;
static gpointer gtk_mate_pattern_parent_class = NULL;
static void gtk_mate_pattern_dispose (GObject * obj);
enum  {
	GTK_MATE_SINGLE_PATTERN_DUMMY_PROPERTY
};
static gpointer gtk_mate_single_pattern_parent_class = NULL;
static void gtk_mate_single_pattern_dispose (GObject * obj);
enum  {
	GTK_MATE_DOUBLE_PATTERN_DUMMY_PROPERTY
};
static gpointer gtk_mate_double_pattern_parent_class = NULL;
static void gtk_mate_double_pattern_dispose (GObject * obj);
enum  {
	GTK_MATE_INCLUDE_PATTERN_DUMMY_PROPERTY
};
static gpointer gtk_mate_include_pattern_parent_class = NULL;



GtkMatePattern* gtk_mate_pattern_create_from_plist (PListDict* pd) {
	PListString* ns;
	GtkMatePattern* p;
	PListNode* _tmp0;
	gboolean _tmp1;
	GtkMatePattern* _tmp9;
	g_return_val_if_fail (PLIST_IS_DICT (pd), NULL);
	ns = NULL;
	p = NULL;
	_tmp0 = NULL;
	if ((_tmp1 = (_tmp0 = plist_dict_get (pd, "match")) != NULL, (_tmp0 == NULL ? NULL : (_tmp0 = (g_object_unref (_tmp0), NULL))), _tmp1)) {
		GtkMatePattern* _tmp2;
		_tmp2 = NULL;
		p = (_tmp2 = GTK_MATE_PATTERN (gtk_mate_single_pattern_create_from_plist (pd)), (p == NULL ? NULL : (p = (g_object_unref (p), NULL))), _tmp2);
	} else {
		PListNode* _tmp3;
		gboolean _tmp4;
		_tmp3 = NULL;
		if ((_tmp4 = (_tmp3 = plist_dict_get (pd, "include")) != NULL, (_tmp3 == NULL ? NULL : (_tmp3 = (g_object_unref (_tmp3), NULL))), _tmp4)) {
			GtkMatePattern* _tmp5;
			_tmp5 = NULL;
			p = (_tmp5 = GTK_MATE_PATTERN (gtk_mate_include_pattern_create_from_plist (pd)), (p == NULL ? NULL : (p = (g_object_unref (p), NULL))), _tmp5);
		} else {
			PListNode* _tmp6;
			gboolean _tmp7;
			_tmp6 = NULL;
			if ((_tmp7 = (_tmp6 = plist_dict_get (pd, "begin")) != NULL, (_tmp6 == NULL ? NULL : (_tmp6 = (g_object_unref (_tmp6), NULL))), _tmp7)) {
				GtkMatePattern* _tmp8;
				_tmp8 = NULL;
				p = (_tmp8 = GTK_MATE_PATTERN (gtk_mate_double_pattern_create_from_plist (pd)), (p == NULL ? NULL : (p = (g_object_unref (p), NULL))), _tmp8);
			}
		}
	}
	_tmp9 = NULL;
	return (_tmp9 = p, (ns == NULL ? NULL : (ns = (g_object_unref (ns), NULL))), _tmp9);
}


GtkMatePattern* gtk_mate_pattern_new (void) {
	GtkMatePattern * self;
	self = g_object_newv (GTK_MATE_TYPE_PATTERN, 0, NULL);
	return self;
}


static void gtk_mate_pattern_class_init (GtkMatePatternClass * klass) {
	gtk_mate_pattern_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->dispose = gtk_mate_pattern_dispose;
}


static void gtk_mate_pattern_instance_init (GtkMatePattern * self) {
}


static void gtk_mate_pattern_dispose (GObject * obj) {
	GtkMatePattern * self;
	self = GTK_MATE_PATTERN (obj);
	self->name = (g_free (self->name), NULL);
	self->comment = (g_free (self->comment), NULL);
	G_OBJECT_CLASS (gtk_mate_pattern_parent_class)->dispose (obj);
}


GType gtk_mate_pattern_get_type (void) {
	static GType gtk_mate_pattern_type_id = 0;
	if (G_UNLIKELY (gtk_mate_pattern_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMatePatternClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_pattern_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMatePattern), 0, (GInstanceInitFunc) gtk_mate_pattern_instance_init };
		gtk_mate_pattern_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMatePattern", &g_define_type_info, 0);
	}
	return gtk_mate_pattern_type_id;
}


GtkMateSinglePattern* gtk_mate_single_pattern_create_from_plist (PListDict* pd) {
	PListString* ns;
	GtkMateSinglePattern* pattern;
	PListString* _tmp0;
	PListString* _tmp3;
	OnigurumaRegex* _tmp4;
	GtkMateSinglePattern* _tmp5;
	g_return_val_if_fail (PLIST_IS_DICT (pd), NULL);
	ns = NULL;
	pattern = g_object_ref_sink (gtk_mate_single_pattern_new ());
	_tmp0 = NULL;
	ns = (_tmp0 = PLIST_STRING (plist_dict_get (pd, "name")), (ns == NULL ? NULL : (ns = (g_object_unref (ns), NULL))), _tmp0);
	if (ns != NULL) {
		char* _tmp2;
		const char* _tmp1;
		_tmp2 = NULL;
		_tmp1 = NULL;
		GTK_MATE_PATTERN (pattern)->name = (_tmp2 = (_tmp1 = ns->str, (_tmp1 == NULL ? NULL : g_strdup (_tmp1))), (GTK_MATE_PATTERN (pattern)->name = (g_free (GTK_MATE_PATTERN (pattern)->name), NULL)), _tmp2);
	}
	/*stdout.printf("sp: %s\n", ((PList.String) pd.get("name")).str);
	else
	stdout.printf("sp: no name\n");*/
	_tmp3 = NULL;
	ns = (_tmp3 = PLIST_STRING (plist_dict_get (pd, "match")), (ns == NULL ? NULL : (ns = (g_object_unref (ns), NULL))), _tmp3);
	_tmp4 = NULL;
	pattern->match = (_tmp4 = oniguruma_regex_make1 (ns->str), (pattern->match == NULL ? NULL : (pattern->match = (g_object_unref (pattern->match), NULL))), _tmp4);
	_tmp5 = NULL;
	return (_tmp5 = pattern, (ns == NULL ? NULL : (ns = (g_object_unref (ns), NULL))), _tmp5);
}


GtkMateSinglePattern* gtk_mate_single_pattern_new (void) {
	GtkMateSinglePattern * self;
	self = g_object_newv (GTK_MATE_TYPE_SINGLE_PATTERN, 0, NULL);
	return self;
}


static void gtk_mate_single_pattern_class_init (GtkMateSinglePatternClass * klass) {
	gtk_mate_single_pattern_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->dispose = gtk_mate_single_pattern_dispose;
}


static void gtk_mate_single_pattern_instance_init (GtkMateSinglePattern * self) {
}


static void gtk_mate_single_pattern_dispose (GObject * obj) {
	GtkMateSinglePattern * self;
	self = GTK_MATE_SINGLE_PATTERN (obj);
	(self->match == NULL ? NULL : (self->match = (g_object_unref (self->match), NULL)));
	(self->captures == NULL ? NULL : (self->captures = (g_object_unref (self->captures), NULL)));
	G_OBJECT_CLASS (gtk_mate_single_pattern_parent_class)->dispose (obj);
}


GType gtk_mate_single_pattern_get_type (void) {
	static GType gtk_mate_single_pattern_type_id = 0;
	if (G_UNLIKELY (gtk_mate_single_pattern_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateSinglePatternClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_single_pattern_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateSinglePattern), 0, (GInstanceInitFunc) gtk_mate_single_pattern_instance_init };
		gtk_mate_single_pattern_type_id = g_type_register_static (GTK_MATE_TYPE_PATTERN, "GtkMateSinglePattern", &g_define_type_info, 0);
	}
	return gtk_mate_single_pattern_type_id;
}


GtkMateDoublePattern* gtk_mate_double_pattern_create_from_plist (PListDict* pd) {
	PListString* ns;
	GtkMateDoublePattern* pattern;
	PListString* _tmp0;
	PListString* _tmp3;
	OnigurumaRegex* _tmp4;
	PListString* _tmp5;
	OnigurumaRegex* _tmp6;
	GeeArrayList* _tmp7;
	PListNode* ps;
	GtkMatePattern* subpattern;
	GtkMateDoublePattern* _tmp9;
	g_return_val_if_fail (PLIST_IS_DICT (pd), NULL);
	ns = NULL;
	pattern = g_object_ref_sink (gtk_mate_double_pattern_new ());
	_tmp0 = NULL;
	ns = (_tmp0 = PLIST_STRING (plist_dict_get (pd, "name")), (ns == NULL ? NULL : (ns = (g_object_unref (ns), NULL))), _tmp0);
	if (ns != NULL) {
		char* _tmp2;
		const char* _tmp1;
		_tmp2 = NULL;
		_tmp1 = NULL;
		GTK_MATE_PATTERN (pattern)->name = (_tmp2 = (_tmp1 = ns->str, (_tmp1 == NULL ? NULL : g_strdup (_tmp1))), (GTK_MATE_PATTERN (pattern)->name = (g_free (GTK_MATE_PATTERN (pattern)->name), NULL)), _tmp2);
	}
	/*stdout.printf("dp: %s\n", ((PList.String) pd.get("name")).str);
	 else
	 stdout.printf("dp: no name\n");*/
	_tmp3 = NULL;
	ns = (_tmp3 = PLIST_STRING (plist_dict_get (pd, "begin")), (ns == NULL ? NULL : (ns = (g_object_unref (ns), NULL))), _tmp3);
	_tmp4 = NULL;
	pattern->begin = (_tmp4 = oniguruma_regex_make1 (ns->str), (pattern->begin == NULL ? NULL : (pattern->begin = (g_object_unref (pattern->begin), NULL))), _tmp4);
	_tmp5 = NULL;
	ns = (_tmp5 = PLIST_STRING (plist_dict_get (pd, "end")), (ns == NULL ? NULL : (ns = (g_object_unref (ns), NULL))), _tmp5);
	_tmp6 = NULL;
	pattern->end = (_tmp6 = oniguruma_regex_make1 (ns->str), (pattern->end == NULL ? NULL : (pattern->end = (g_object_unref (pattern->end), NULL))), _tmp6);
	_tmp7 = NULL;
	pattern->patterns = (_tmp7 = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal), (pattern->patterns == NULL ? NULL : (pattern->patterns = (g_object_unref (pattern->patterns), NULL))), _tmp7);
	ps = plist_dict_get (pd, "patterns");
	subpattern = NULL;
	if (ps != NULL) {
		{
			GeeArrayList* p_collection;
			int p_it;
			p_collection = (PLIST_ARRAY (ps))->array;
			for (p_it = 0; p_it < gee_collection_get_size (GEE_COLLECTION (p_collection)); p_it = p_it + 1) {
				PListNode* p;
				p = ((PListNode*) (gee_list_get (GEE_LIST (p_collection), p_it)));
				{
					GtkMatePattern* _tmp8;
					_tmp8 = NULL;
					subpattern = (_tmp8 = gtk_mate_pattern_create_from_plist (PLIST_DICT (p)), (subpattern == NULL ? NULL : (subpattern = (g_object_unref (subpattern), NULL))), _tmp8);
					if (subpattern != NULL) {
						gee_collection_add (GEE_COLLECTION (pattern->patterns), subpattern);
					}
					(p == NULL ? NULL : (p = (g_object_unref (p), NULL)));
				}
			}
		}
	}
	_tmp9 = NULL;
	return (_tmp9 = pattern, (ns == NULL ? NULL : (ns = (g_object_unref (ns), NULL))), (ps == NULL ? NULL : (ps = (g_object_unref (ps), NULL))), (subpattern == NULL ? NULL : (subpattern = (g_object_unref (subpattern), NULL))), _tmp9);
}


GtkMateDoublePattern* gtk_mate_double_pattern_new (void) {
	GtkMateDoublePattern * self;
	self = g_object_newv (GTK_MATE_TYPE_DOUBLE_PATTERN, 0, NULL);
	return self;
}


static void gtk_mate_double_pattern_class_init (GtkMateDoublePatternClass * klass) {
	gtk_mate_double_pattern_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->dispose = gtk_mate_double_pattern_dispose;
}


static void gtk_mate_double_pattern_instance_init (GtkMateDoublePattern * self) {
}


static void gtk_mate_double_pattern_dispose (GObject * obj) {
	GtkMateDoublePattern * self;
	self = GTK_MATE_DOUBLE_PATTERN (obj);
	(self->begin == NULL ? NULL : (self->begin = (g_object_unref (self->begin), NULL)));
	(self->end == NULL ? NULL : (self->end = (g_object_unref (self->end), NULL)));
	(self->begin_captures == NULL ? NULL : (self->begin_captures = (g_object_unref (self->begin_captures), NULL)));
	(self->end_captures == NULL ? NULL : (self->end_captures = (g_object_unref (self->end_captures), NULL)));
	(self->patterns == NULL ? NULL : (self->patterns = (g_object_unref (self->patterns), NULL)));
	G_OBJECT_CLASS (gtk_mate_double_pattern_parent_class)->dispose (obj);
}


GType gtk_mate_double_pattern_get_type (void) {
	static GType gtk_mate_double_pattern_type_id = 0;
	if (G_UNLIKELY (gtk_mate_double_pattern_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateDoublePatternClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_double_pattern_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateDoublePattern), 0, (GInstanceInitFunc) gtk_mate_double_pattern_instance_init };
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
	g_return_val_if_fail (PLIST_IS_DICT (pd), NULL);
	ns = NULL;
	pattern = g_object_ref_sink (gtk_mate_include_pattern_new ());
	_tmp0 = NULL;
	ns = (_tmp0 = PLIST_STRING (plist_dict_get (pd, "include")), (ns == NULL ? NULL : (ns = (g_object_unref (ns), NULL))), _tmp0);
	_tmp2 = NULL;
	_tmp1 = NULL;
	GTK_MATE_PATTERN (pattern)->name = (_tmp2 = (_tmp1 = ns->str, (_tmp1 == NULL ? NULL : g_strdup (_tmp1))), (GTK_MATE_PATTERN (pattern)->name = (g_free (GTK_MATE_PATTERN (pattern)->name), NULL)), _tmp2);
	/* stdout.printf("ip: %s\n", ns.str);*/
	_tmp3 = NULL;
	return (_tmp3 = pattern, (ns == NULL ? NULL : (ns = (g_object_unref (ns), NULL))), _tmp3);
}


GtkMateIncludePattern* gtk_mate_include_pattern_new (void) {
	GtkMateIncludePattern * self;
	self = g_object_newv (GTK_MATE_TYPE_INCLUDE_PATTERN, 0, NULL);
	return self;
}


static void gtk_mate_include_pattern_class_init (GtkMateIncludePatternClass * klass) {
	gtk_mate_include_pattern_parent_class = g_type_class_peek_parent (klass);
}


static void gtk_mate_include_pattern_instance_init (GtkMateIncludePattern * self) {
}


GType gtk_mate_include_pattern_get_type (void) {
	static GType gtk_mate_include_pattern_type_id = 0;
	if (G_UNLIKELY (gtk_mate_include_pattern_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateIncludePatternClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_include_pattern_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateIncludePattern), 0, (GInstanceInitFunc) gtk_mate_include_pattern_instance_init };
		gtk_mate_include_pattern_type_id = g_type_register_static (GTK_MATE_TYPE_PATTERN, "GtkMateIncludePattern", &g_define_type_info, 0);
	}
	return gtk_mate_include_pattern_type_id;
}




