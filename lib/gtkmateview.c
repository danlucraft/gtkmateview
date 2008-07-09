
#include "gtkmateview.h"
#include <gee/collection.h>
#include <glib/gstdio.h>
#include <stdio.h>
#include <bundle.h>
#include <onig_wrap.h>
#include <plist.h>




enum  {
	GTK_MATE_VIEW_DUMMY_PROPERTY,
	GTK_MATE_VIEW_GRAMMAR
};
GeeArrayList* gtk_mate_view_bundles = NULL;
GeeArrayList* gtk_mate_view_themes = NULL;
static GtkMateGrammar* gtk_mate_view__grammar;
static char** gtk_mate_view_get_string_array (GeeArrayList* al, int* result_length1);
static gpointer gtk_mate_view_parent_class = NULL;
static void gtk_mate_view_dispose (GObject * obj);
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
static int _vala_strcmp0 (const char * str1, const char * str2);



/* Sets the grammar with the file extension, then checks the
 first line for matches as a fallback. If unable to find
 a grammar, sets the grammar to null. Returns the grammar
 name or null.*/
char* gtk_mate_view_set_grammar_by_extension (GtkMateView* self, const char* extension) {
	OnigurumaRegex* re;
	GtkSourceBuffer* _tmp3;
	GtkSourceBuffer* buf;
	const char* _tmp6;
	GtkTextIter _tmp5 = {0};
	GtkTextIter _tmp4 = {0};
	char* first_line;
	char* _tmp13;
	g_return_val_if_fail (GTK_IS_MATE_VIEW (self), NULL);
	g_return_val_if_fail (extension != NULL, NULL);
	{
		GeeArrayList* bundle_collection;
		int bundle_it;
		bundle_collection = gtk_mate_view_bundles;
		for (bundle_it = 0; bundle_it < gee_collection_get_size (GEE_COLLECTION (bundle_collection)); bundle_it = bundle_it + 1) {
			GtkMateBundle* bundle;
			bundle = ((GtkMateBundle*) (gee_list_get (GEE_LIST (bundle_collection), bundle_it)));
			{
				{
					GeeArrayList* gr_collection;
					int gr_it;
					gr_collection = bundle->grammars;
					for (gr_it = 0; gr_it < gee_collection_get_size (GEE_COLLECTION (gr_collection)); gr_it = gr_it + 1) {
						GtkMateGrammar* gr;
						gr = ((GtkMateGrammar*) (gee_list_get (GEE_LIST (gr_collection), gr_it)));
						{
							{
								char** ext_collection;
								int ext_collection_length1;
								int ext_it;
								ext_collection = gr->file_types;
								ext_collection_length1 = gr->file_types_length1;
								for (ext_it = 0; (gr->file_types_length1 != -1 && ext_it < gr->file_types_length1) || (gr->file_types_length1 == -1 && ext_collection[ext_it] != NULL); ext_it = ext_it + 1) {
									const char* _tmp2;
									char* ext;
									_tmp2 = NULL;
									ext = (_tmp2 = ext_collection[ext_it], (_tmp2 == NULL ? NULL : g_strdup (_tmp2)));
									{
										if (_vala_strcmp0 (ext, extension) == 0) {
											const char* _tmp0;
											char* _tmp1;
											gtk_mate_view_set_grammar (self, gr);
											_tmp0 = NULL;
											_tmp1 = NULL;
											return (_tmp1 = (_tmp0 = gtk_mate_grammar_get_name (gr), (_tmp0 == NULL ? NULL : g_strdup (_tmp0))), (ext = (g_free (ext), NULL)), (gr == NULL ? NULL : (gr = (g_object_unref (gr), NULL))), (bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL))), _tmp1);
										}
										ext = (g_free (ext), NULL);
									}
								}
							}
							(gr == NULL ? NULL : (gr = (g_object_unref (gr), NULL)));
						}
					}
				}
				(bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL)));
			}
		}
	}
	re = NULL;
	_tmp3 = NULL;
	buf = (_tmp3 = GTK_SOURCE_BUFFER (gtk_text_view_get_buffer (GTK_TEXT_VIEW (self))), (_tmp3 == NULL ? NULL : g_object_ref (_tmp3)));
	_tmp6 = NULL;
	first_line = (_tmp6 = gtk_text_buffer_get_text (GTK_TEXT_BUFFER (buf), (_tmp4 = gtk_mate_view_iter_ (self, 0), &_tmp4), (_tmp5 = gtk_mate_view_iter_line_start (self, 1), &_tmp5), FALSE), (_tmp6 == NULL ? NULL : g_strdup (_tmp6)));
	{
		GeeArrayList* bundle_collection;
		int bundle_it;
		bundle_collection = gtk_mate_view_bundles;
		for (bundle_it = 0; bundle_it < gee_collection_get_size (GEE_COLLECTION (bundle_collection)); bundle_it = bundle_it + 1) {
			GtkMateBundle* bundle;
			bundle = ((GtkMateBundle*) (gee_list_get (GEE_LIST (bundle_collection), bundle_it)));
			{
				{
					GeeArrayList* gr_collection;
					int gr_it;
					gr_collection = bundle->grammars;
					for (gr_it = 0; gr_it < gee_collection_get_size (GEE_COLLECTION (gr_collection)); gr_it = gr_it + 1) {
						GtkMateGrammar* gr;
						gr = ((GtkMateGrammar*) (gee_list_get (GEE_LIST (gr_collection), gr_it)));
						{
							OnigurumaRegex* _tmp8;
							OnigurumaRegex* _tmp7;
							_tmp8 = NULL;
							_tmp7 = NULL;
							if ((re = (_tmp8 = (_tmp7 = gr->first_line_match, (_tmp7 == NULL ? NULL : g_object_ref (_tmp7))), (re == NULL ? NULL : (re = (g_object_unref (re), NULL))), _tmp8)) != NULL) {
								OnigurumaMatch* _tmp9;
								gboolean _tmp10;
								_tmp9 = NULL;
								if ((_tmp10 = (_tmp9 = oniguruma_regex_search (re, first_line, 0, ((gint) (strlen (first_line))))) != NULL, (_tmp9 == NULL ? NULL : (_tmp9 = (g_object_unref (_tmp9), NULL))), _tmp10)) {
									const char* _tmp11;
									char* _tmp12;
									gtk_mate_view_set_grammar (self, gr);
									_tmp11 = NULL;
									_tmp12 = NULL;
									return (_tmp12 = (_tmp11 = gtk_mate_grammar_get_name (gr), (_tmp11 == NULL ? NULL : g_strdup (_tmp11))), (gr == NULL ? NULL : (gr = (g_object_unref (gr), NULL))), (bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL))), (re == NULL ? NULL : (re = (g_object_unref (re), NULL))), (buf == NULL ? NULL : (buf = (g_object_unref (buf), NULL))), (first_line = (g_free (first_line), NULL)), _tmp12);
								}
							}
							(gr == NULL ? NULL : (gr = (g_object_unref (gr), NULL)));
						}
					}
				}
				(bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL)));
			}
		}
	}
	gtk_mate_view_set_grammar (self, NULL);
	_tmp13 = NULL;
	return (_tmp13 = NULL, (re == NULL ? NULL : (re = (g_object_unref (re), NULL))), (buf == NULL ? NULL : (buf = (g_object_unref (buf), NULL))), (first_line = (g_free (first_line), NULL)), _tmp13);
}


GtkTextIter gtk_mate_view_iter_ (GtkMateView* self, gint offset) {
	GtkTextIter i = {0};
	0;
	gtk_text_buffer_get_iter_at_offset (gtk_text_view_get_buffer (GTK_TEXT_VIEW (self)), &i, offset);
	return i;
}


GtkTextIter gtk_mate_view_iter_line_start (GtkMateView* self, gint line) {
	GtkTextIter i = {0};
	0;
	gtk_text_buffer_get_iter_at_line (gtk_text_view_get_buffer (GTK_TEXT_VIEW (self)), &i, line);
	return i;
}


gint gtk_mate_view_load_bundles (void) {
	GError * inner_error;
	char* syntax_dir;
	char* name;
	GtkMateBundle* bundle;
	GtkMateGrammar* grammar;
	PListDict* plist;
	gint _tmp14;
	inner_error = NULL;
	syntax_dir = NULL;
	name = NULL;
	bundle = NULL;
	grammar = NULL;
	plist = NULL;
	{
		GeeArrayList* bundle_dir_collection;
		int bundle_dir_it;
		bundle_dir_collection = gtk_mate_view_bundle_dirs ();
		for (bundle_dir_it = 0; bundle_dir_it < gee_collection_get_size (GEE_COLLECTION (bundle_dir_collection)); bundle_dir_it = bundle_dir_it + 1) {
			char* bundle_dir;
			bundle_dir = ((char*) (gee_list_get (GEE_LIST (bundle_dir_collection), bundle_dir_it)));
			{
				GtkMateBundle* _tmp1;
				gint _tmp0_length1;
				char** _tmp0;
				char* _tmp5;
				char* _tmp4;
				char* _tmp3;
				char* _tmp2;
				_tmp1 = NULL;
				_tmp0 = NULL;
				bundle = (_tmp1 = g_object_ref_sink (gtk_mate_bundle_new (((_tmp0 = g_strsplit (bundle_dir, ".", 0)), _tmp0_length1 = -1, _tmp0)[0])), (bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL))), _tmp1);
				_tmp0 = (_vala_array_free (_tmp0, _tmp0_length1, ((GDestroyNotify) (g_free))), NULL);
				gee_collection_add (GEE_COLLECTION (gtk_mate_view_bundles), bundle);
				_tmp5 = NULL;
				_tmp4 = NULL;
				_tmp3 = NULL;
				_tmp2 = NULL;
				syntax_dir = (_tmp5 = g_strconcat ((_tmp4 = g_strconcat ((_tmp3 = g_strconcat ((_tmp2 = gtk_mate_view_textmate_share_dir ()), "/Bundles/", NULL)), bundle_dir, NULL)), "/Syntaxes", NULL), (syntax_dir = (g_free (syntax_dir), NULL)), _tmp5);
				_tmp4 = (g_free (_tmp4), NULL);
				_tmp3 = (g_free (_tmp3), NULL);
				_tmp2 = (g_free (_tmp2), NULL);
				if (g_file_test (syntax_dir, G_FILE_TEST_EXISTS)) {
					{
						GDir* d;
						char* _tmp7;
						const char* _tmp6;
						d = g_dir_open (syntax_dir, 0, &inner_error);
						if (inner_error != NULL) {
							if (inner_error->domain == G_FILE_ERROR) {
								goto __catch0_g_file_error;
							}
							g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
							g_clear_error (&inner_error);
						}
						_tmp7 = NULL;
						_tmp6 = NULL;
						while ((name = (_tmp7 = (_tmp6 = g_dir_read_name (d), (_tmp6 == NULL ? NULL : g_strdup (_tmp6))), (name = (g_free (name), NULL)), _tmp7)) != NULL) {
							if (_vala_strcmp0 (name, ".svn") != 0 && (g_str_has_suffix (name, ".tmLanguage") || g_str_has_suffix (name, ".plist"))) {
								{
									PListDict* _tmp10;
									char* _tmp9;
									char* _tmp8;
									_tmp10 = NULL;
									_tmp9 = NULL;
									_tmp8 = NULL;
									plist = (_tmp10 = plist_parse ((_tmp9 = g_strconcat ((_tmp8 = g_strconcat (syntax_dir, "/", NULL)), name, NULL)), &inner_error), (plist == NULL ? NULL : (plist = (g_object_unref (plist), NULL))), _tmp10);
									if (inner_error != NULL) {
										if (inner_error->domain == XML_ERROR) {
											goto __catch1_xml_error;
										}
										g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
										g_clear_error (&inner_error);
									}
									_tmp9 = (g_free (_tmp9), NULL);
									_tmp8 = (g_free (_tmp8), NULL);
								}
								goto __finally1;
								__catch1_xml_error:
								{
									GError * e;
									e = inner_error;
									inner_error = NULL;
									{
										char* _tmp12;
										char* _tmp11;
										_tmp12 = NULL;
										_tmp11 = NULL;
										fprintf (stdout, "error opening %s\n", (_tmp12 = g_strconcat ((_tmp11 = g_strconcat (syntax_dir, "/", NULL)), name, NULL)));
										_tmp12 = (g_free (_tmp12), NULL);
										_tmp11 = (g_free (_tmp11), NULL);
									}
								}
								__finally1:
								;
								if (plist != NULL) {
									GtkMateGrammar* _tmp13;
									_tmp13 = NULL;
									grammar = (_tmp13 = g_object_ref_sink (gtk_mate_grammar_new (plist)), (grammar == NULL ? NULL : (grammar = (g_object_unref (grammar), NULL))), _tmp13);
									gee_collection_add (GEE_COLLECTION (bundle->grammars), grammar);
								}
							}
						}
						(d == NULL ? NULL : (d = (g_dir_close (d), NULL)));
					}
					goto __finally0;
					__catch0_g_file_error:
					{
						GError * e;
						e = inner_error;
						inner_error = NULL;
						{
							fprintf (stdout, "error opening %s\n", syntax_dir);
						}
					}
					__finally0:
					;
				}
				bundle_dir = (g_free (bundle_dir), NULL);
			}
		}
		(bundle_dir_collection == NULL ? NULL : (bundle_dir_collection = (g_object_unref (bundle_dir_collection), NULL)));
	}
	{
		GeeArrayList* b_collection;
		int b_it;
		b_collection = gtk_mate_view_bundles;
		for (b_it = 0; b_it < gee_collection_get_size (GEE_COLLECTION (b_collection)); b_it = b_it + 1) {
			GtkMateBundle* b;
			b = ((GtkMateBundle*) (gee_list_get (GEE_LIST (b_collection), b_it)));
			{
				{
					GeeArrayList* g_collection;
					int g_it;
					g_collection = b->grammars;
					for (g_it = 0; g_it < gee_collection_get_size (GEE_COLLECTION (g_collection)); g_it = g_it + 1) {
						GtkMateGrammar* g;
						g = ((GtkMateGrammar*) (gee_list_get (GEE_LIST (g_collection), g_it)));
						{
							gtk_mate_grammar_init_for_reference (g);
							(g == NULL ? NULL : (g = (g_object_unref (g), NULL)));
						}
					}
				}
				(b == NULL ? NULL : (b = (g_object_unref (b), NULL)));
			}
		}
	}
	return (_tmp14 = -1, (syntax_dir = (g_free (syntax_dir), NULL)), (name = (g_free (name), NULL)), (bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL))), (grammar == NULL ? NULL : (grammar = (g_object_unref (grammar), NULL))), (plist == NULL ? NULL : (plist = (g_object_unref (plist), NULL))), _tmp14);
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
				goto __catch2_g_file_error;
			}
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
			g_clear_error (&inner_error);
		}
		_tmp3 = NULL;
		_tmp2 = NULL;
		while ((name = (_tmp3 = (_tmp2 = g_dir_read_name (d), (_tmp2 == NULL ? NULL : g_strdup (_tmp2))), (name = (g_free (name), NULL)), _tmp3)) != NULL) {
			if (g_str_has_suffix (name, ".tmbundle")) {
				gee_collection_add (GEE_COLLECTION (names), name);
			}
		}
		_tmp4 = NULL;
		return (_tmp4 = names, (d == NULL ? NULL : (d = (g_dir_close (d), NULL))), (name = (g_free (name), NULL)), (share_dir = (g_free (share_dir), NULL)), _tmp4);
	}
	goto __finally2;
	__catch2_g_file_error:
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
	__finally2:
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


GtkMateGrammar* gtk_mate_view_get_grammar (GtkMateView* self) {
	g_return_val_if_fail (GTK_IS_MATE_VIEW (self), NULL);
	return gtk_mate_view__grammar;
}


void gtk_mate_view_set_grammar (GtkMateView* self, GtkMateGrammar* value) {
	GtkMateGrammar* _tmp2;
	GtkMateGrammar* _tmp1;
	g_return_if_fail (GTK_IS_MATE_VIEW (self));
	gtk_mate_grammar_init_for_use (value);
	_tmp2 = NULL;
	_tmp1 = NULL;
	gtk_mate_view__grammar = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (gtk_mate_view__grammar == NULL ? NULL : (gtk_mate_view__grammar = (g_object_unref (gtk_mate_view__grammar), NULL))), _tmp2);
}


static void gtk_mate_view_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateView * self;
	self = GTK_MATE_VIEW (object);
	switch (property_id) {
		case GTK_MATE_VIEW_GRAMMAR:
		g_value_set_object (value, gtk_mate_view_get_grammar (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_view_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GtkMateView * self;
	self = GTK_MATE_VIEW (object);
	switch (property_id) {
		case GTK_MATE_VIEW_GRAMMAR:
		gtk_mate_view_set_grammar (self, g_value_get_object (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_view_class_init (GtkMateViewClass * klass) {
	gtk_mate_view_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->get_property = gtk_mate_view_get_property;
	G_OBJECT_CLASS (klass)->set_property = gtk_mate_view_set_property;
	G_OBJECT_CLASS (klass)->dispose = gtk_mate_view_dispose;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_VIEW_GRAMMAR, g_param_spec_object ("grammar", "grammar", "grammar", GTK_MATE_TYPE_GRAMMAR, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	{
		GeeArrayList* _tmp0;
		GeeArrayList* _tmp1;
		_tmp0 = NULL;
		gtk_mate_view_bundles = (_tmp0 = gee_array_list_new (GTK_MATE_TYPE_BUNDLE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal), (gtk_mate_view_bundles == NULL ? NULL : (gtk_mate_view_bundles = (g_object_unref (gtk_mate_view_bundles), NULL))), _tmp0);
		_tmp1 = NULL;
		gtk_mate_view_themes = (_tmp1 = gee_array_list_new (GTK_MATE_TYPE_THEME, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal), (gtk_mate_view_themes == NULL ? NULL : (gtk_mate_view_themes = (g_object_unref (gtk_mate_view_themes), NULL))), _tmp1);
	}
}


static void gtk_mate_view_instance_init (GtkMateView * self) {
}


static void gtk_mate_view_dispose (GObject * obj) {
	GtkMateView * self;
	self = GTK_MATE_VIEW (obj);
	G_OBJECT_CLASS (gtk_mate_view_parent_class)->dispose (obj);
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


static int _vala_strcmp0 (const char * str1, const char * str2) {
	if (str1 == NULL) {
		return -(str1 != str2);
	}
	if (str2 == NULL) {
		return (str1 != str2);
	}
	return strcmp (str1, str2);
}




