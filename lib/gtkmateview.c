
#include <gtkmateview.h>
#include <stdio.h>
#include <gee/collection.h>
#include <glib/gstdio.h>




enum  {
	GTK_MATE_VIEW_DUMMY_PROPERTY
};
static char** gtk_mate_view_get_string_array (GeeArrayList* al, int* result_length1);
static gpointer gtk_mate_view_parent_class = NULL;
enum  {
	GTK_MATE_GRAMMAR_DUMMY_PROPERTY
};
static gpointer gtk_mate_grammar_parent_class = NULL;
enum  {
	GTK_MATE_PATTERN_DUMMY_PROPERTY
};
static gpointer gtk_mate_pattern_parent_class = NULL;
enum  {
	GTK_MATE_THEME_DUMMY_PROPERTY
};
static gpointer gtk_mate_theme_parent_class = NULL;
enum  {
	GTK_MATE_SINGLE_PATTERN_DUMMY_PROPERTY
};
static gpointer gtk_mate_single_pattern_parent_class = NULL;
enum  {
	GTK_MATE_DOUBLE_PATTERN_DUMMY_PROPERTY
};
static gpointer gtk_mate_double_pattern_parent_class = NULL;
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);



gint gtk_mate_view_load_grammars (void) {
	{
		GeeArrayList* bundle_dir_collection;
		int bundle_dir_it;
		bundle_dir_collection = gtk_mate_view_bundle_dirs ();
		for (bundle_dir_it = 0; bundle_dir_it < gee_collection_get_size (GEE_COLLECTION (bundle_dir_collection)); bundle_dir_it = bundle_dir_it + 1) {
			char* bundle_dir;
			bundle_dir = ((char*) (gee_list_get (GEE_LIST (bundle_dir_collection), bundle_dir_it)));
			{
				char* _tmp2;
				char* _tmp1;
				char* _tmp0;
				_tmp2 = NULL;
				_tmp1 = NULL;
				_tmp0 = NULL;
				fprintf (stdout, "%s\n", (_tmp2 = g_strconcat ((_tmp1 = g_strconcat ((_tmp0 = gtk_mate_view_textmate_share_dir ()), "/Bundles/", NULL)), bundle_dir, NULL)));
				_tmp2 = (g_free (_tmp2), NULL);
				_tmp1 = (g_free (_tmp1), NULL);
				_tmp0 = (g_free (_tmp0), NULL);
				bundle_dir = (g_free (bundle_dir), NULL);
			}
		}
		(bundle_dir_collection == NULL ? NULL : (bundle_dir_collection = (g_object_unref (bundle_dir_collection), NULL)));
	}
	return 1;
}


GeeArrayList* gtk_mate_view_bundle_dirs (void) {
	GError * inner_error;
	char* name;
	char* share_dir;
	GeeArrayList* names;
	GeeArrayList* _tmp6;
	inner_error = NULL;
	name = NULL;
	share_dir = gtk_mate_view_textmate_share_dir ();
	names = gee_array_list_new (G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, g_direct_equal);
	{
		char* _tmp0;
		GDir* _tmp1;
		GDir* d;
		char* _tmp3;
		const char* _tmp2;
		GeeArrayList* _tmp4;
		_tmp0 = NULL;
		_tmp1 = NULL;
		d = (_tmp1 = g_dir_open ((_tmp0 = g_strconcat (share_dir, "/Bundles", NULL)), 0, &inner_error), (_tmp0 = (g_free (_tmp0), NULL)), _tmp1);
		if (inner_error != NULL) {
			if (inner_error->domain == G_FILE_ERROR) {
				goto __catch0_g_file_error;
			}
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
			g_clear_error (&inner_error);
		}
		_tmp3 = NULL;
		_tmp2 = NULL;
		while ((name = (_tmp3 = (_tmp2 = g_dir_read_name (d), (_tmp2 == NULL ? NULL : g_strdup (_tmp2))), (name = (g_free (name), NULL)), _tmp3)) != NULL && g_str_has_suffix (name, ".tmbundle")) {
			gee_collection_add (GEE_COLLECTION (names), name);
		}
		_tmp4 = NULL;
		return (_tmp4 = names, (d == NULL ? NULL : (d = (g_dir_close (d), NULL))), (name = (g_free (name), NULL)), (share_dir = (g_free (share_dir), NULL)), _tmp4);
	}
	goto __finally0;
	__catch0_g_file_error:
	{
		GError * e;
		e = inner_error;
		inner_error = NULL;
		{
			char* _tmp5;
			_tmp5 = NULL;
			fprintf (stdout, "couldn't open: %s\n", (_tmp5 = g_strconcat (share_dir, "/Bundles", NULL)));
			_tmp5 = (g_free (_tmp5), NULL);
		}
	}
	__finally0:
	;
	_tmp6 = NULL;
	return (_tmp6 = NULL, (name = (g_free (name), NULL)), (share_dir = (g_free (share_dir), NULL)), (names == NULL ? NULL : (names = (g_object_unref (names), NULL))), _tmp6);
}


char* gtk_mate_view_textmate_share_dir (void) {
	char* share_dir;
	char* _tmp1;
	char* _tmp3;
	share_dir = g_strdup ("/usr/local/share/textmate");
	if (g_file_test (share_dir, G_FILE_TEST_EXISTS)) {
		return share_dir;
	}
	_tmp1 = NULL;
	share_dir = (_tmp1 = g_strdup ("/usr/share/textmate"), (share_dir = (g_free (share_dir), NULL)), _tmp1);
	if (g_file_test (share_dir, G_FILE_TEST_EXISTS)) {
		return share_dir;
	}
	fprintf (stdout, "couldn't find /usr/share/textmate or /usr/local/share/textmate\n");
	_tmp3 = NULL;
	return (_tmp3 = NULL, (share_dir = (g_free (share_dir), NULL)), _tmp3);
}


char** gtk_mate_view_bundle_dirs_rb (int* result_length1) {
	gint arr_names_length1;
	char** arr_names;
	GeeArrayList* names;
	arr_names = (arr_names_length1 = 0, NULL);
	names = gtk_mate_view_bundle_dirs ();
	if (names != NULL) {
		char** _tmp1;
		gint _tmp0;
		char** _tmp2;
		char** _tmp3;
		_tmp1 = NULL;
		arr_names = (_tmp1 = gtk_mate_view_get_string_array (names, &_tmp0), (arr_names = (_vala_array_free (arr_names, arr_names_length1, ((GDestroyNotify) (g_free))), NULL)), arr_names_length1 = _tmp0, _tmp1);
		_tmp2 = NULL;
		_tmp3 = NULL;
		return (_tmp3 = (_tmp2 = arr_names, (*result_length1) = arr_names_length1, _tmp2), (names == NULL ? NULL : (names = (g_object_unref (names), NULL))), _tmp3);
	} else {
		gpointer _tmp4;
		char** _tmp5;
		_tmp5 = NULL;
		return (_tmp5 = (_tmp4 = NULL, (*result_length1) = 0, _tmp4), (arr_names = (_vala_array_free (arr_names, arr_names_length1, ((GDestroyNotify) (g_free))), NULL)), (names == NULL ? NULL : (names = (g_object_unref (names), NULL))), _tmp5);
	}
	arr_names = (_vala_array_free (arr_names, arr_names_length1, ((GDestroyNotify) (g_free))), NULL);
	(names == NULL ? NULL : (names = (g_object_unref (names), NULL)));
}


static char** gtk_mate_view_get_string_array (GeeArrayList* al, int* result_length1) {
	char** _tmp1;
	gint arr_length1;
	gint _tmp0;
	char** arr;
	gint i;
	char** _tmp4;
	g_return_val_if_fail (GEE_IS_ARRAY_LIST (al), NULL);
	_tmp1 = NULL;
	arr = (_tmp1 = g_new0 (char*, (_tmp0 = gee_collection_get_size (GEE_COLLECTION (al))) + 1), arr_length1 = _tmp0, _tmp1);
	i = 0;
	{
		GeeArrayList* n_collection;
		int n_it;
		n_collection = al;
		for (n_it = 0; n_it < gee_collection_get_size (GEE_COLLECTION (n_collection)); n_it = n_it + 1) {
			char* n;
			n = ((char*) (gee_list_get (GEE_LIST (n_collection), n_it)));
			{
				char* _tmp3;
				const char* _tmp2;
				_tmp3 = NULL;
				_tmp2 = NULL;
				arr[i] = (_tmp3 = (_tmp2 = n, (_tmp2 == NULL ? NULL : g_strdup (_tmp2))), (arr[i] = (g_free (arr[i]), NULL)), _tmp3);
				i++;
				n = (g_free (n), NULL);
			}
		}
	}
	_tmp4 = NULL;
	return (_tmp4 = arr, (*result_length1) = arr_length1, _tmp4);
}


GtkMateView* gtk_mate_view_new (void) {
	GtkMateView * self;
	self = g_object_newv (GTK_TYPE_MATE_VIEW, 0, NULL);
	return self;
}


static void gtk_mate_view_class_init (GtkMateViewClass * klass) {
	gtk_mate_view_parent_class = g_type_class_peek_parent (klass);
}


static void gtk_mate_view_instance_init (GtkMateView * self) {
}


GType gtk_mate_view_get_type (void) {
	static GType gtk_mate_view_type_id = 0;
	if (G_UNLIKELY (gtk_mate_view_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateViewClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_view_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateView), 0, (GInstanceInitFunc) gtk_mate_view_instance_init };
		gtk_mate_view_type_id = g_type_register_static (GTK_TYPE_SOURCE_VIEW, "GtkMateView", &g_define_type_info, 0);
	}
	return gtk_mate_view_type_id;
}


GQuark gtk_mate_mate_error_quark (void) {
	return g_quark_from_static_string ("gtk_mate_mate_error-quark");
}


GtkMateGrammar* gtk_mate_grammar_new (void) {
	GtkMateGrammar * self;
	self = g_object_newv (GTK_MATE_TYPE_GRAMMAR, 0, NULL);
	return self;
}


static void gtk_mate_grammar_class_init (GtkMateGrammarClass * klass) {
	gtk_mate_grammar_parent_class = g_type_class_peek_parent (klass);
}


static void gtk_mate_grammar_instance_init (GtkMateGrammar * self) {
}


GType gtk_mate_grammar_get_type (void) {
	static GType gtk_mate_grammar_type_id = 0;
	if (G_UNLIKELY (gtk_mate_grammar_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateGrammarClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_grammar_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateGrammar), 0, (GInstanceInitFunc) gtk_mate_grammar_instance_init };
		gtk_mate_grammar_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateGrammar", &g_define_type_info, 0);
	}
	return gtk_mate_grammar_type_id;
}


GtkMatePattern* gtk_mate_pattern_new (void) {
	GtkMatePattern * self;
	self = g_object_newv (GTK_MATE_TYPE_PATTERN, 0, NULL);
	return self;
}


static void gtk_mate_pattern_class_init (GtkMatePatternClass * klass) {
	gtk_mate_pattern_parent_class = g_type_class_peek_parent (klass);
}


static void gtk_mate_pattern_instance_init (GtkMatePattern * self) {
}


GType gtk_mate_pattern_get_type (void) {
	static GType gtk_mate_pattern_type_id = 0;
	if (G_UNLIKELY (gtk_mate_pattern_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMatePatternClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_pattern_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMatePattern), 0, (GInstanceInitFunc) gtk_mate_pattern_instance_init };
		gtk_mate_pattern_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMatePattern", &g_define_type_info, 0);
	}
	return gtk_mate_pattern_type_id;
}


GtkMateTheme* gtk_mate_theme_new (void) {
	GtkMateTheme * self;
	self = g_object_newv (GTK_MATE_TYPE_THEME, 0, NULL);
	return self;
}


static void gtk_mate_theme_class_init (GtkMateThemeClass * klass) {
	gtk_mate_theme_parent_class = g_type_class_peek_parent (klass);
}


static void gtk_mate_theme_instance_init (GtkMateTheme * self) {
}


GType gtk_mate_theme_get_type (void) {
	static GType gtk_mate_theme_type_id = 0;
	if (G_UNLIKELY (gtk_mate_theme_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateThemeClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_theme_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateTheme), 0, (GInstanceInitFunc) gtk_mate_theme_instance_init };
		gtk_mate_theme_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateTheme", &g_define_type_info, 0);
	}
	return gtk_mate_theme_type_id;
}


GtkMateSinglePattern* gtk_mate_single_pattern_new (void) {
	GtkMateSinglePattern * self;
	self = g_object_newv (GTK_MATE_TYPE_SINGLE_PATTERN, 0, NULL);
	return self;
}


static void gtk_mate_single_pattern_class_init (GtkMateSinglePatternClass * klass) {
	gtk_mate_single_pattern_parent_class = g_type_class_peek_parent (klass);
}


static void gtk_mate_single_pattern_instance_init (GtkMateSinglePattern * self) {
}


GType gtk_mate_single_pattern_get_type (void) {
	static GType gtk_mate_single_pattern_type_id = 0;
	if (G_UNLIKELY (gtk_mate_single_pattern_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateSinglePatternClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_single_pattern_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateSinglePattern), 0, (GInstanceInitFunc) gtk_mate_single_pattern_instance_init };
		gtk_mate_single_pattern_type_id = g_type_register_static (GTK_MATE_TYPE_PATTERN, "GtkMateSinglePattern", &g_define_type_info, 0);
	}
	return gtk_mate_single_pattern_type_id;
}


GtkMateDoublePattern* gtk_mate_double_pattern_new (void) {
	GtkMateDoublePattern * self;
	self = g_object_newv (GTK_MATE_TYPE_DOUBLE_PATTERN, 0, NULL);
	return self;
}


static void gtk_mate_double_pattern_class_init (GtkMateDoublePatternClass * klass) {
	gtk_mate_double_pattern_parent_class = g_type_class_peek_parent (klass);
}


static void gtk_mate_double_pattern_instance_init (GtkMateDoublePattern * self) {
}


GType gtk_mate_double_pattern_get_type (void) {
	static GType gtk_mate_double_pattern_type_id = 0;
	if (G_UNLIKELY (gtk_mate_double_pattern_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateDoublePatternClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_double_pattern_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateDoublePattern), 0, (GInstanceInitFunc) gtk_mate_double_pattern_instance_init };
		gtk_mate_double_pattern_type_id = g_type_register_static (GTK_MATE_TYPE_PATTERN, "GtkMateDoublePattern", &g_define_type_info, 0);
	}
	return gtk_mate_double_pattern_type_id;
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




