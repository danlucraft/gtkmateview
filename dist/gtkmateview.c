
#include "gtkmateview.h"
#include <gee/collection.h>
#include <glib/gstdio.h>
#include <stdio.h>
#include "buffer.h"
#include "bundle.h"
#include "theme.h"
#include "grammar.h"
#include "plist.h"




static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static int _vala_strcmp0 (const char * str1, const char * str2);



/* Loads bundles (in particular, grammars) from 
 /usr/share/textmate/Bundles*/
gint gtk_mate_load_bundles (void) {
	GError * inner_error;
	GeeArrayList* _tmp1;
	GeeArrayList* _tmp2;
	char* syntax_dir;
	char* name;
	GtkMateBundle* bundle;
	GtkMateGrammar* grammar;
	PListDict* plist;
	gint _tmp17;
	inner_error = NULL;
	if (gtk_mate_buffer_bundles != NULL) {
		return 1;
	}
	_tmp1 = NULL;
	gtk_mate_buffer_bundles = (_tmp1 = gee_array_list_new (GTK_MATE_TYPE_BUNDLE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal), (gtk_mate_buffer_bundles == NULL ? NULL : (gtk_mate_buffer_bundles = (g_object_unref (gtk_mate_buffer_bundles), NULL))), _tmp1);
	_tmp2 = NULL;
	gtk_mate_buffer_themes = (_tmp2 = gee_array_list_new (GTK_MATE_TYPE_THEME, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal), (gtk_mate_buffer_themes == NULL ? NULL : (gtk_mate_buffer_themes = (g_object_unref (gtk_mate_buffer_themes), NULL))), _tmp2);
	syntax_dir = NULL;
	name = NULL;
	bundle = NULL;
	grammar = NULL;
	plist = NULL;
	{
		GeeArrayList* bundle_dir_collection;
		int bundle_dir_it;
		bundle_dir_collection = gtk_mate_bundle_dirs ();
		for (bundle_dir_it = 0; bundle_dir_it < gee_collection_get_size (GEE_COLLECTION (bundle_dir_collection)); bundle_dir_it = bundle_dir_it + 1) {
			char* bundle_dir;
			bundle_dir = ((char*) (gee_list_get (GEE_LIST (bundle_dir_collection), bundle_dir_it)));
			{
				GtkMateBundle* _tmp4;
				gint _tmp3_length1;
				char** _tmp3;
				char* _tmp8;
				char* _tmp7;
				char* _tmp6;
				char* _tmp5;
				_tmp4 = NULL;
				_tmp3 = NULL;
				bundle = (_tmp4 = g_object_ref_sink (gtk_mate_bundle_new (((_tmp3 = g_strsplit (bundle_dir, ".", 0)), _tmp3_length1 = -1, _tmp3)[0])), (bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL))), _tmp4);
				_tmp3 = (_vala_array_free (_tmp3, _tmp3_length1, ((GDestroyNotify) (g_free))), NULL);
				gee_collection_add (((GeeCollection*) (gtk_mate_buffer_bundles)), bundle);
				_tmp8 = NULL;
				_tmp7 = NULL;
				_tmp6 = NULL;
				_tmp5 = NULL;
				syntax_dir = (_tmp8 = g_strconcat ((_tmp7 = g_strconcat ((_tmp6 = g_strconcat ((_tmp5 = gtk_mate_textmate_share_dir ()), "/Bundles/", NULL)), bundle_dir, NULL)), "/Syntaxes", NULL), (syntax_dir = (g_free (syntax_dir), NULL)), _tmp8);
				_tmp7 = (g_free (_tmp7), NULL);
				_tmp6 = (g_free (_tmp6), NULL);
				_tmp5 = (g_free (_tmp5), NULL);
				if (g_file_test (syntax_dir, G_FILE_TEST_EXISTS)) {
					{
						GDir* d;
						char* _tmp10;
						const char* _tmp9;
						d = g_dir_open (syntax_dir, 0, &inner_error);
						if (inner_error != NULL) {
							if (inner_error->domain == G_FILE_ERROR) {
								goto __catch2_g_file_error;
							}
							g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
							g_clear_error (&inner_error);
						}
						_tmp10 = NULL;
						_tmp9 = NULL;
						while ((name = (_tmp10 = (_tmp9 = g_dir_read_name (d), (_tmp9 == NULL ? NULL : g_strdup (_tmp9))), (name = (g_free (name), NULL)), _tmp10)) != NULL) {
							if (_vala_strcmp0 (name, ".svn") != 0 && (g_str_has_suffix (name, ".tmLanguage") || g_str_has_suffix (name, ".plist"))) {
								{
									PListDict* _tmp13;
									char* _tmp12;
									char* _tmp11;
									_tmp13 = NULL;
									_tmp12 = NULL;
									_tmp11 = NULL;
									plist = (_tmp13 = plist_parse ((_tmp12 = g_strconcat ((_tmp11 = g_strconcat (syntax_dir, "/", NULL)), name, NULL)), &inner_error), (plist == NULL ? NULL : (plist = (g_object_unref (plist), NULL))), _tmp13);
									if (inner_error != NULL) {
										if (inner_error->domain == XML_ERROR) {
											goto __catch3_xml_error;
										}
										g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
										g_clear_error (&inner_error);
									}
									_tmp12 = (g_free (_tmp12), NULL);
									_tmp11 = (g_free (_tmp11), NULL);
								}
								goto __finally3;
								__catch3_xml_error:
								{
									GError * e;
									e = inner_error;
									inner_error = NULL;
									{
										char* _tmp15;
										char* _tmp14;
										_tmp15 = NULL;
										_tmp14 = NULL;
										fprintf (stdout, "error opening %s\n", (_tmp15 = g_strconcat ((_tmp14 = g_strconcat (syntax_dir, "/", NULL)), name, NULL)));
										_tmp15 = (g_free (_tmp15), NULL);
										_tmp14 = (g_free (_tmp14), NULL);
										(e == NULL ? NULL : (e = (g_error_free (e), NULL)));
									}
								}
								__finally3:
								;
								if (plist != NULL) {
									GtkMateGrammar* _tmp16;
									_tmp16 = NULL;
									grammar = (_tmp16 = g_object_ref_sink (gtk_mate_grammar_new (plist)), (grammar == NULL ? NULL : (grammar = (g_object_unref (grammar), NULL))), _tmp16);
									gee_collection_add (((GeeCollection*) (bundle->grammars)), grammar);
								}
							}
						}
						(d == NULL ? NULL : (d = (g_dir_close (d), NULL)));
					}
					goto __finally2;
					__catch2_g_file_error:
					{
						GError * e;
						e = inner_error;
						inner_error = NULL;
						{
							fprintf (stdout, "error opening %s\n", syntax_dir);
							(e == NULL ? NULL : (e = (g_error_free (e), NULL)));
						}
					}
					__finally2:
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
		b_collection = gtk_mate_buffer_bundles;
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
	return (_tmp17 = -1, (syntax_dir = (g_free (syntax_dir), NULL)), (name = (g_free (name), NULL)), (bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL))), (grammar == NULL ? NULL : (grammar = (g_object_unref (grammar), NULL))), (plist == NULL ? NULL : (plist = (g_object_unref (plist), NULL))), _tmp17);
}


/* Loads themes from /usr/share/textmate/Themes/. */
void gtk_mate_load_themes (void) {
	GError * inner_error;
	GeeArrayList* _tmp0;
	inner_error = NULL;
	if (gtk_mate_theme_themes != NULL) {
		return;
	}
	_tmp0 = NULL;
	gtk_mate_theme_themes = (_tmp0 = gee_array_list_new (GTK_MATE_TYPE_THEME, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal), (gtk_mate_theme_themes == NULL ? NULL : (gtk_mate_theme_themes = (g_object_unref (gtk_mate_theme_themes), NULL))), _tmp0);
	{
		GeeArrayList* fn_collection;
		int fn_it;
		fn_collection = gtk_mate_theme_theme_filenames ();
		for (fn_it = 0; fn_it < gee_collection_get_size (GEE_COLLECTION (fn_collection)); fn_it = fn_it + 1) {
			char* fn;
			fn = ((char*) (gee_list_get (GEE_LIST (fn_collection), fn_it)));
			{
				{
					PListDict* plist;
					GtkMateTheme* theme;
					plist = plist_parse (fn, &inner_error);
					if (inner_error != NULL) {
						if (inner_error->domain == XML_ERROR) {
							goto __catch4_xml_error;
						}
						g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
						g_clear_error (&inner_error);
					}
					theme = gtk_mate_theme_create_from_plist (PLIST_DICT (plist));
					if (theme != NULL) {
						gee_collection_add (((GeeCollection*) (gtk_mate_theme_themes)), theme);
					}
					(plist == NULL ? NULL : (plist = (g_object_unref (plist), NULL)));
					(theme == NULL ? NULL : (theme = (g_object_unref (theme), NULL)));
				}
				goto __finally4;
				__catch4_xml_error:
				{
					GError * e;
					e = inner_error;
					inner_error = NULL;
					{
						fprintf (stdout, "error opening %s\n", fn);
						(e == NULL ? NULL : (e = (g_error_free (e), NULL)));
					}
				}
				__finally4:
				;
				fn = (g_free (fn), NULL);
			}
		}
		(fn_collection == NULL ? NULL : (fn_collection = (g_object_unref (fn_collection), NULL)));
	}
}


/* Return a list of bundle names like "Ruby.tmbundle"*/
GeeArrayList* gtk_mate_bundle_dirs (void) {
	GError * inner_error;
	char* name;
	char* share_dir;
	GeeArrayList* names;
	GeeArrayList* _tmp6;
	inner_error = NULL;
	name = NULL;
	share_dir = gtk_mate_textmate_share_dir ();
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
				goto __catch5_g_file_error;
			}
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
			g_clear_error (&inner_error);
		}
		_tmp3 = NULL;
		_tmp2 = NULL;
		while ((name = (_tmp3 = (_tmp2 = g_dir_read_name (d), (_tmp2 == NULL ? NULL : g_strdup (_tmp2))), (name = (g_free (name), NULL)), _tmp3)) != NULL) {
			if (g_str_has_suffix (name, ".tmbundle")) {
				gee_collection_add (((GeeCollection*) (names)), name);
			}
		}
		_tmp4 = NULL;
		return (_tmp4 = names, (d == NULL ? NULL : (d = (g_dir_close (d), NULL))), (name = (g_free (name), NULL)), (share_dir = (g_free (share_dir), NULL)), _tmp4);
	}
	goto __finally5;
	__catch5_g_file_error:
	{
		GError * e;
		e = inner_error;
		inner_error = NULL;
		{
			char* _tmp5;
			_tmp5 = NULL;
			fprintf (stdout, "couldn't open: %s\n", (_tmp5 = g_strconcat (share_dir, "/Bundles", NULL)));
			_tmp5 = (g_free (_tmp5), NULL);
			(e == NULL ? NULL : (e = (g_error_free (e), NULL)));
		}
	}
	__finally5:
	;
	_tmp6 = NULL;
	return (_tmp6 = NULL, (name = (g_free (name), NULL)), (share_dir = (g_free (share_dir), NULL)), (names == NULL ? NULL : (names = (g_object_unref (names), NULL))), _tmp6);
}


/* Return the textmate assets directory path,
 e.g. /usr/share/textmate*/
char* gtk_mate_textmate_share_dir (void) {
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




