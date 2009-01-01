
#include "gtkmateview.h"
#include <glib/gstdio.h>
#include <stdio.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>
#include "theme.h"
#include "plist.h"
#include "buffer.h"
#include "bundle.h"
#include "grammar.h"




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
	gint _tmp23;
	inner_error = NULL;
	if (gtk_mate_buffer_bundles != NULL) {
		return 1;
	}
	_tmp1 = NULL;
	gtk_mate_buffer_bundles = (_tmp1 = gee_array_list_new (GTK_MATE_TYPE_BUNDLE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (gtk_mate_buffer_bundles == NULL) ? NULL : (gtk_mate_buffer_bundles = (g_object_unref (gtk_mate_buffer_bundles), NULL)), _tmp1);
	_tmp2 = NULL;
	gtk_mate_buffer_themes = (_tmp2 = gee_array_list_new (GTK_MATE_TYPE_THEME, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (gtk_mate_buffer_themes == NULL) ? NULL : (gtk_mate_buffer_themes = (g_object_unref (gtk_mate_buffer_themes), NULL)), _tmp2);
	syntax_dir = NULL;
	name = NULL;
	bundle = NULL;
	grammar = NULL;
	plist = NULL;
	{
		GeeArrayList* _tmp3;
		GeeIterator* _tmp4;
		GeeIterator* bundle_dir_it;
		_tmp3 = NULL;
		_tmp4 = NULL;
		bundle_dir_it = (_tmp4 = gee_iterable_iterator ((GeeIterable*) (_tmp3 = gtk_mate_bundle_dirs ())), (_tmp3 == NULL) ? NULL : (_tmp3 = (g_object_unref (_tmp3), NULL)), _tmp4);
		while (gee_iterator_next (bundle_dir_it)) {
			char* bundle_dir;
			GtkMateBundle* _tmp6;
			gint _tmp5_length1;
			char** _tmp5;
			char* _tmp10;
			char* _tmp9;
			char* _tmp8;
			char* _tmp7;
			bundle_dir = (char*) gee_iterator_get (bundle_dir_it);
			_tmp6 = NULL;
			_tmp5 = NULL;
			bundle = (_tmp6 = g_object_ref_sink (gtk_mate_bundle_new ((_tmp5 = g_strsplit (bundle_dir, ".", 0), _tmp5_length1 = -1, _tmp5)[0])), (bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL)), _tmp6);
			_tmp5 = (_vala_array_free (_tmp5, _tmp5_length1, (GDestroyNotify) g_free), NULL);
			gee_collection_add ((GeeCollection*) gtk_mate_buffer_bundles, bundle);
			_tmp10 = NULL;
			_tmp9 = NULL;
			_tmp8 = NULL;
			_tmp7 = NULL;
			syntax_dir = (_tmp10 = g_strconcat (_tmp9 = g_strconcat (_tmp8 = g_strconcat (_tmp7 = gtk_mate_textmate_share_dir (), "/Bundles/", NULL), bundle_dir, NULL), "/Syntaxes", NULL), syntax_dir = (g_free (syntax_dir), NULL), _tmp10);
			_tmp9 = (g_free (_tmp9), NULL);
			_tmp8 = (g_free (_tmp8), NULL);
			_tmp7 = (g_free (_tmp7), NULL);
			if (g_file_test (syntax_dir, G_FILE_TEST_EXISTS)) {
				{
					GDir* d;
					char* _tmp12;
					const char* _tmp11;
					d = g_dir_open (syntax_dir, 0, &inner_error);
					if (inner_error != NULL) {
						if (inner_error->domain == G_FILE_ERROR) {
							goto __catch2_g_file_error;
						}
						g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
						g_clear_error (&inner_error);
					}
					_tmp12 = NULL;
					_tmp11 = NULL;
					while ((name = (_tmp12 = (_tmp11 = g_dir_read_name (d), (_tmp11 == NULL) ? NULL : g_strdup (_tmp11)), name = (g_free (name), NULL), _tmp12)) != NULL) {
						gboolean _tmp13;
						_tmp13 = FALSE;
						if (_vala_strcmp0 (name, ".svn") != 0) {
							gboolean _tmp14;
							_tmp14 = FALSE;
							if (g_str_has_suffix (name, ".tmLanguage")) {
								_tmp14 = TRUE;
							} else {
								_tmp14 = g_str_has_suffix (name, ".plist");
							}
							_tmp13 = (_tmp14);
						} else {
							_tmp13 = FALSE;
						}
						if (_tmp13) {
							{
								char* _tmp16;
								char* _tmp15;
								PListDict* _tmp17;
								PListDict* _tmp18;
								PListDict* _tmp19;
								_tmp16 = NULL;
								_tmp15 = NULL;
								_tmp17 = NULL;
								_tmp18 = (_tmp17 = plist_parse (_tmp16 = g_strconcat (_tmp15 = g_strconcat (syntax_dir, "/", NULL), name, NULL), &inner_error), _tmp16 = (g_free (_tmp16), NULL), _tmp15 = (g_free (_tmp15), NULL), _tmp17);
								if (inner_error != NULL) {
									if (inner_error->domain == XML_ERROR) {
										goto __catch3_xml_error;
									}
									g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
									g_clear_error (&inner_error);
								}
								_tmp19 = NULL;
								plist = (_tmp19 = _tmp18, (plist == NULL) ? NULL : (plist = (g_object_unref (plist), NULL)), _tmp19);
							}
							goto __finally3;
							__catch3_xml_error:
							{
								GError * e;
								e = inner_error;
								inner_error = NULL;
								{
									char* _tmp21;
									char* _tmp20;
									_tmp21 = NULL;
									_tmp20 = NULL;
									fprintf (stdout, "error opening %s\n", _tmp21 = g_strconcat (_tmp20 = g_strconcat (syntax_dir, "/", NULL), name, NULL));
									_tmp21 = (g_free (_tmp21), NULL);
									_tmp20 = (g_free (_tmp20), NULL);
									(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
								}
							}
							__finally3:
							;
							if (plist != NULL) {
								GtkMateGrammar* _tmp22;
								_tmp22 = NULL;
								grammar = (_tmp22 = g_object_ref_sink (gtk_mate_grammar_new (plist)), (grammar == NULL) ? NULL : (grammar = (g_object_unref (grammar), NULL)), _tmp22);
								gtk_mate_grammar_set_filename (grammar, name);
								gee_collection_add ((GeeCollection*) bundle->grammars, grammar);
							}
						}
					}
					(d == NULL) ? NULL : (d = (g_dir_close (d), NULL));
				}
				goto __finally2;
				__catch2_g_file_error:
				{
					GError * e;
					e = inner_error;
					inner_error = NULL;
					{
						fprintf (stdout, "error opening %s\n", syntax_dir);
						(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
					}
				}
				__finally2:
				;
			}
			bundle_dir = (g_free (bundle_dir), NULL);
		}
		(bundle_dir_it == NULL) ? NULL : (bundle_dir_it = (g_object_unref (bundle_dir_it), NULL));
	}
	{
		GeeIterator* b_it;
		b_it = gee_iterable_iterator ((GeeIterable*) gtk_mate_buffer_bundles);
		while (gee_iterator_next (b_it)) {
			GtkMateBundle* b;
			b = (GtkMateBundle*) gee_iterator_get (b_it);
			{
				GeeIterator* g_it;
				g_it = gee_iterable_iterator ((GeeIterable*) b->grammars);
				while (gee_iterator_next (g_it)) {
					GtkMateGrammar* g;
					g = (GtkMateGrammar*) gee_iterator_get (g_it);
					gtk_mate_grammar_init_for_reference (g);
					(g == NULL) ? NULL : (g = (g_object_unref (g), NULL));
				}
				(g_it == NULL) ? NULL : (g_it = (g_object_unref (g_it), NULL));
			}
			(b == NULL) ? NULL : (b = (g_object_unref (b), NULL));
		}
		(b_it == NULL) ? NULL : (b_it = (g_object_unref (b_it), NULL));
	}
	return (_tmp23 = -1, syntax_dir = (g_free (syntax_dir), NULL), name = (g_free (name), NULL), (bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL)), (grammar == NULL) ? NULL : (grammar = (g_object_unref (grammar), NULL)), (plist == NULL) ? NULL : (plist = (g_object_unref (plist), NULL)), _tmp23);
}


/* Loads themes from /usr/share/textmate/Themes/. */
void gtk_mate_load_themes (void) {
	GError * inner_error;
	GeeArrayList* _tmp0;
	inner_error = NULL;
	if (gtk_mate_theme__themes != NULL) {
		return;
	}
	_tmp0 = NULL;
	gtk_mate_theme__themes = (_tmp0 = gee_array_list_new (GTK_MATE_TYPE_THEME, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (gtk_mate_theme__themes == NULL) ? NULL : (gtk_mate_theme__themes = (g_object_unref (gtk_mate_theme__themes), NULL)), _tmp0);
	{
		GeeArrayList* _tmp1;
		GeeIterator* _tmp2;
		GeeIterator* fn_it;
		_tmp1 = NULL;
		_tmp2 = NULL;
		fn_it = (_tmp2 = gee_iterable_iterator ((GeeIterable*) (_tmp1 = gtk_mate_theme_theme_filenames ())), (_tmp1 == NULL) ? NULL : (_tmp1 = (g_object_unref (_tmp1), NULL)), _tmp2);
		while (gee_iterator_next (fn_it)) {
			char* fn;
			fn = (char*) gee_iterator_get (fn_it);
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
					gee_collection_add ((GeeCollection*) gtk_mate_theme__themes, theme);
				}
				(plist == NULL) ? NULL : (plist = (g_object_unref (plist), NULL));
				(theme == NULL) ? NULL : (theme = (g_object_unref (theme), NULL));
			}
			goto __finally4;
			__catch4_xml_error:
			{
				GError * e;
				e = inner_error;
				inner_error = NULL;
				{
					fprintf (stdout, "error opening %s\n", fn);
					(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
				}
			}
			__finally4:
			;
			fn = (g_free (fn), NULL);
		}
		(fn_it == NULL) ? NULL : (fn_it = (g_object_unref (fn_it), NULL));
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
	names = gee_array_list_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, g_direct_equal);
	{
		char* _tmp0;
		GDir* _tmp1;
		GDir* d;
		char* _tmp3;
		const char* _tmp2;
		GeeArrayList* _tmp4;
		_tmp0 = NULL;
		_tmp1 = NULL;
		d = (_tmp1 = g_dir_open (_tmp0 = g_strconcat (share_dir, "/Bundles", NULL), 0, &inner_error), _tmp0 = (g_free (_tmp0), NULL), _tmp1);
		if (inner_error != NULL) {
			if (inner_error->domain == G_FILE_ERROR) {
				goto __catch5_g_file_error;
			}
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
			g_clear_error (&inner_error);
		}
		_tmp3 = NULL;
		_tmp2 = NULL;
		while ((name = (_tmp3 = (_tmp2 = g_dir_read_name (d), (_tmp2 == NULL) ? NULL : g_strdup (_tmp2)), name = (g_free (name), NULL), _tmp3)) != NULL) {
			if (g_str_has_suffix (name, ".tmbundle")) {
				gee_collection_add ((GeeCollection*) names, name);
			}
		}
		_tmp4 = NULL;
		return (_tmp4 = names, (d == NULL) ? NULL : (d = (g_dir_close (d), NULL)), name = (g_free (name), NULL), share_dir = (g_free (share_dir), NULL), _tmp4);
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
			fprintf (stdout, "couldn't open: %s\n", _tmp5 = g_strconcat (share_dir, "/Bundles", NULL));
			_tmp5 = (g_free (_tmp5), NULL);
			(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
		}
	}
	__finally5:
	;
	_tmp6 = NULL;
	return (_tmp6 = NULL, name = (g_free (name), NULL), share_dir = (g_free (share_dir), NULL), (names == NULL) ? NULL : (names = (g_object_unref (names), NULL)), _tmp6);
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
	share_dir = (_tmp1 = g_strdup ("/usr/share/textmate"), share_dir = (g_free (share_dir), NULL), _tmp1);
	if (g_file_test (share_dir, G_FILE_TEST_EXISTS)) {
		return share_dir;
	}
	fprintf (stdout, "couldn't find /usr/share/textmate or /usr/local/share/textmate\n");
	_tmp3 = NULL;
	return (_tmp3 = NULL, share_dir = (g_free (share_dir), NULL), _tmp3);
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




