
#include <glib.h>
#include <glib-object.h>
#include <gee/arraylist.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>
#include <glib/gstdio.h>
#include <stdio.h>


#define GTK_MATE_TYPE_BUNDLE (gtk_mate_bundle_get_type ())
#define GTK_MATE_BUNDLE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_BUNDLE, GtkMateBundle))
#define GTK_MATE_BUNDLE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_BUNDLE, GtkMateBundleClass))
#define GTK_MATE_IS_BUNDLE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_BUNDLE))
#define GTK_MATE_IS_BUNDLE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_BUNDLE))
#define GTK_MATE_BUNDLE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_BUNDLE, GtkMateBundleClass))

typedef struct _GtkMateBundle GtkMateBundle;
typedef struct _GtkMateBundleClass GtkMateBundleClass;

#define GTK_MATE_TYPE_THEME (gtk_mate_theme_get_type ())
#define GTK_MATE_THEME(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_THEME, GtkMateTheme))
#define GTK_MATE_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_THEME, GtkMateThemeClass))
#define GTK_MATE_IS_THEME(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_THEME))
#define GTK_MATE_IS_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_THEME))
#define GTK_MATE_THEME_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_THEME, GtkMateThemeClass))

typedef struct _GtkMateTheme GtkMateTheme;
typedef struct _GtkMateThemeClass GtkMateThemeClass;

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
typedef struct _GtkMateBundlePrivate GtkMateBundlePrivate;

/* PList reader in Vala
 valac -o plist --pkg libxml-2.0 --pkg gee-1.0 plist.vala*/
typedef enum  {
	XML_ERROR_FILE_NOT_FOUND,
	XML_ERROR_XML_DOCUMENT_EMPTY
} XmlError;
#define XML_ERROR xml_error_quark ()
struct _GtkMateBundle {
	GtkObject parent_instance;
	GtkMateBundlePrivate * priv;
	GeeArrayList* grammars;
};

struct _GtkMateBundleClass {
	GtkObjectClass parent_class;
};



extern char* gtk_mate_textmate_dir;
char* gtk_mate_textmate_dir = NULL;
extern GeeArrayList* gtk_mate_buffer_bundles;
GType gtk_mate_bundle_get_type (void);
GType gtk_mate_theme_get_type (void);
extern GeeArrayList* gtk_mate_buffer_themes;
GType gtk_mate_grammar_get_type (void);
GType plist_node_get_type (void);
GType plist_dict_get_type (void);
GeeArrayList* gtk_mate_bundle_dirs (void);
GtkMateBundle* gtk_mate_bundle_new (const char* name);
GtkMateBundle* gtk_mate_bundle_construct (GType object_type, const char* name);
char* gtk_mate_textmate_share_dir (void);
PListDict* plist_parse (const char* filename, GError** error);
GQuark xml_error_quark (void);
GtkMateGrammar* gtk_mate_grammar_new (PListDict* plist);
GtkMateGrammar* gtk_mate_grammar_construct (GType object_type, PListDict* plist);
void gtk_mate_grammar_set_filename (GtkMateGrammar* self, const char* value);
void gtk_mate_grammar_init_for_reference (GtkMateGrammar* self);
gint gtk_mate_load_bundles (void);
extern GeeArrayList* gtk_mate_theme__themes;
GeeArrayList* gtk_mate_theme_theme_filenames (void);
GtkMateTheme* gtk_mate_theme_create_from_plist (PListDict* dict);
void gtk_mate_load_themes (void);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static gint _vala_array_length (gpointer array);
static int _vala_strcmp0 (const char * str1, const char * str2);



/* Loads bundles (in particular, grammars) from 
 /usr/share/textmate/Bundles or from the location in
 textmate_dir*/
gint gtk_mate_load_bundles (void) {
	GError * _inner_error_;
	GeeArrayList* _tmp1_;
	GeeArrayList* _tmp2_;
	char* syntax_dir;
	char* name;
	GtkMateBundle* bundle;
	GtkMateGrammar* grammar;
	PListDict* plist;
	gint _tmp24_;
	_inner_error_ = NULL;
	if (gtk_mate_buffer_bundles != NULL) {
		return 1;
	}
	_tmp1_ = NULL;
	gtk_mate_buffer_bundles = (_tmp1_ = gee_array_list_new (GTK_MATE_TYPE_BUNDLE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (gtk_mate_buffer_bundles == NULL) ? NULL : (gtk_mate_buffer_bundles = (g_object_unref (gtk_mate_buffer_bundles), NULL)), _tmp1_);
	_tmp2_ = NULL;
	gtk_mate_buffer_themes = (_tmp2_ = gee_array_list_new (GTK_MATE_TYPE_THEME, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (gtk_mate_buffer_themes == NULL) ? NULL : (gtk_mate_buffer_themes = (g_object_unref (gtk_mate_buffer_themes), NULL)), _tmp2_);
	syntax_dir = NULL;
	name = NULL;
	bundle = NULL;
	grammar = NULL;
	plist = NULL;
	{
		GeeArrayList* _tmp3_;
		GeeIterator* _tmp4_;
		GeeIterator* _bundle_dir_it;
		_tmp3_ = NULL;
		_tmp4_ = NULL;
		_bundle_dir_it = (_tmp4_ = gee_iterable_iterator ((GeeIterable*) (_tmp3_ = gtk_mate_bundle_dirs ())), (_tmp3_ == NULL) ? NULL : (_tmp3_ = (g_object_unref (_tmp3_), NULL)), _tmp4_);
		while (gee_iterator_next (_bundle_dir_it)) {
			char* bundle_dir;
			GtkMateBundle* _tmp7_;
			gint _tmp6__length1;
			char** _tmp6_;
			char** _tmp5_;
			char* _tmp11_;
			char* _tmp10_;
			char* _tmp9_;
			char* _tmp8_;
			bundle_dir = (char*) gee_iterator_get (_bundle_dir_it);
			_tmp7_ = NULL;
			_tmp6_ = NULL;
			_tmp5_ = NULL;
			bundle = (_tmp7_ = g_object_ref_sink (gtk_mate_bundle_new ((_tmp6_ = _tmp5_ = g_strsplit (bundle_dir, ".", 0), _tmp6__length1 = _vala_array_length (_tmp5_), _tmp6_)[0])), (bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL)), _tmp7_);
			_tmp6_ = (_vala_array_free (_tmp6_, _tmp6__length1, (GDestroyNotify) g_free), NULL);
			gee_collection_add ((GeeCollection*) gtk_mate_buffer_bundles, bundle);
			_tmp11_ = NULL;
			_tmp10_ = NULL;
			_tmp9_ = NULL;
			_tmp8_ = NULL;
			syntax_dir = (_tmp11_ = g_strconcat (_tmp10_ = g_strconcat (_tmp9_ = g_strconcat (_tmp8_ = gtk_mate_textmate_share_dir (), "/Bundles/", NULL), bundle_dir, NULL), "/Syntaxes", NULL), syntax_dir = (g_free (syntax_dir), NULL), _tmp11_);
			_tmp10_ = (g_free (_tmp10_), NULL);
			_tmp9_ = (g_free (_tmp9_), NULL);
			_tmp8_ = (g_free (_tmp8_), NULL);
			if (g_file_test (syntax_dir, G_FILE_TEST_EXISTS)) {
				{
					GDir* d;
					char* _tmp13_;
					const char* _tmp12_;
					d = g_dir_open (syntax_dir, 0, &_inner_error_);
					if (_inner_error_ != NULL) {
						if (_inner_error_->domain == G_FILE_ERROR) {
							goto __catch0_g_file_error;
						}
						goto __finally0;
					}
					_tmp13_ = NULL;
					_tmp12_ = NULL;
					while ((name = (_tmp13_ = (_tmp12_ = g_dir_read_name (d), (_tmp12_ == NULL) ? NULL : g_strdup (_tmp12_)), name = (g_free (name), NULL), _tmp13_)) != NULL) {
						gboolean _tmp14_;
						_tmp14_ = FALSE;
						if (_vala_strcmp0 (name, ".svn") != 0) {
							gboolean _tmp15_;
							_tmp15_ = FALSE;
							if (g_str_has_suffix (name, ".tmLanguage")) {
								_tmp15_ = TRUE;
							} else {
								_tmp15_ = g_str_has_suffix (name, ".plist");
							}
							_tmp14_ = _tmp15_;
						} else {
							_tmp14_ = FALSE;
						}
						if (_tmp14_) {
							{
								char* _tmp17_;
								char* _tmp16_;
								PListDict* _tmp18_;
								PListDict* _tmp19_;
								PListDict* _tmp20_;
								_tmp17_ = NULL;
								_tmp16_ = NULL;
								_tmp18_ = NULL;
								_tmp19_ = (_tmp18_ = plist_parse (_tmp17_ = g_strconcat (_tmp16_ = g_strconcat (syntax_dir, "/", NULL), name, NULL), &_inner_error_), _tmp17_ = (g_free (_tmp17_), NULL), _tmp16_ = (g_free (_tmp16_), NULL), _tmp18_);
								if (_inner_error_ != NULL) {
									if (_inner_error_->domain == XML_ERROR) {
										goto __catch1_xml_error;
									}
									goto __finally1;
								}
								_tmp20_ = NULL;
								plist = (_tmp20_ = _tmp19_, (plist == NULL) ? NULL : (plist = (g_object_unref (plist), NULL)), _tmp20_);
							}
							goto __finally1;
							__catch1_xml_error:
							{
								GError * e;
								e = _inner_error_;
								_inner_error_ = NULL;
								{
									char* _tmp22_;
									char* _tmp21_;
									_tmp22_ = NULL;
									_tmp21_ = NULL;
									fprintf (stdout, "error opening %s\n", _tmp22_ = g_strconcat (_tmp21_ = g_strconcat (syntax_dir, "/", NULL), name, NULL));
									_tmp22_ = (g_free (_tmp22_), NULL);
									_tmp21_ = (g_free (_tmp21_), NULL);
									(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
								}
							}
							__finally1:
							if (_inner_error_ != NULL) {
								(d == NULL) ? NULL : (d = (g_dir_close (d), NULL));
								if (_inner_error_->domain == G_FILE_ERROR) {
									goto __catch0_g_file_error;
								}
								goto __finally0;
							}
							if (plist != NULL) {
								GtkMateGrammar* _tmp23_;
								_tmp23_ = NULL;
								grammar = (_tmp23_ = g_object_ref_sink (gtk_mate_grammar_new (plist)), (grammar == NULL) ? NULL : (grammar = (g_object_unref (grammar), NULL)), _tmp23_);
								gtk_mate_grammar_set_filename (grammar, name);
								gee_collection_add ((GeeCollection*) bundle->grammars, grammar);
							}
						}
					}
					(d == NULL) ? NULL : (d = (g_dir_close (d), NULL));
				}
				goto __finally0;
				__catch0_g_file_error:
				{
					GError * e;
					e = _inner_error_;
					_inner_error_ = NULL;
					{
						fprintf (stdout, "error opening %s\n", syntax_dir);
						(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
					}
				}
				__finally0:
				if (_inner_error_ != NULL) {
					bundle_dir = (g_free (bundle_dir), NULL);
					(_bundle_dir_it == NULL) ? NULL : (_bundle_dir_it = (g_object_unref (_bundle_dir_it), NULL));
					syntax_dir = (g_free (syntax_dir), NULL);
					name = (g_free (name), NULL);
					(bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL));
					(grammar == NULL) ? NULL : (grammar = (g_object_unref (grammar), NULL));
					(plist == NULL) ? NULL : (plist = (g_object_unref (plist), NULL));
					g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
					g_clear_error (&_inner_error_);
					return 0;
				}
			}
			bundle_dir = (g_free (bundle_dir), NULL);
		}
		(_bundle_dir_it == NULL) ? NULL : (_bundle_dir_it = (g_object_unref (_bundle_dir_it), NULL));
	}
	{
		GeeIterator* _b_it;
		_b_it = gee_iterable_iterator ((GeeIterable*) gtk_mate_buffer_bundles);
		while (gee_iterator_next (_b_it)) {
			GtkMateBundle* b;
			b = (GtkMateBundle*) gee_iterator_get (_b_it);
			{
				GeeIterator* _g_it;
				_g_it = gee_iterable_iterator ((GeeIterable*) b->grammars);
				while (gee_iterator_next (_g_it)) {
					GtkMateGrammar* g;
					g = (GtkMateGrammar*) gee_iterator_get (_g_it);
					gtk_mate_grammar_init_for_reference (g);
					(g == NULL) ? NULL : (g = (g_object_unref (g), NULL));
				}
				(_g_it == NULL) ? NULL : (_g_it = (g_object_unref (_g_it), NULL));
			}
			(b == NULL) ? NULL : (b = (g_object_unref (b), NULL));
		}
		(_b_it == NULL) ? NULL : (_b_it = (g_object_unref (_b_it), NULL));
	}
	return (_tmp24_ = -1, syntax_dir = (g_free (syntax_dir), NULL), name = (g_free (name), NULL), (bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL)), (grammar == NULL) ? NULL : (grammar = (g_object_unref (grammar), NULL)), (plist == NULL) ? NULL : (plist = (g_object_unref (plist), NULL)), _tmp24_);
}


/* Loads themes from /usr/share/textmate/Themes/. */
void gtk_mate_load_themes (void) {
	GError * _inner_error_;
	GeeArrayList* _tmp0_;
	_inner_error_ = NULL;
	if (gtk_mate_theme__themes != NULL) {
		return;
	}
	_tmp0_ = NULL;
	gtk_mate_theme__themes = (_tmp0_ = gee_array_list_new (GTK_MATE_TYPE_THEME, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (gtk_mate_theme__themes == NULL) ? NULL : (gtk_mate_theme__themes = (g_object_unref (gtk_mate_theme__themes), NULL)), _tmp0_);
	{
		GeeArrayList* _tmp1_;
		GeeIterator* _tmp2_;
		GeeIterator* _fn_it;
		_tmp1_ = NULL;
		_tmp2_ = NULL;
		_fn_it = (_tmp2_ = gee_iterable_iterator ((GeeIterable*) (_tmp1_ = gtk_mate_theme_theme_filenames ())), (_tmp1_ == NULL) ? NULL : (_tmp1_ = (g_object_unref (_tmp1_), NULL)), _tmp2_);
		while (gee_iterator_next (_fn_it)) {
			char* fn;
			fn = (char*) gee_iterator_get (_fn_it);
			{
				PListDict* plist;
				GtkMateTheme* theme;
				plist = plist_parse (fn, &_inner_error_);
				if (_inner_error_ != NULL) {
					if (_inner_error_->domain == XML_ERROR) {
						goto __catch2_xml_error;
					}
					goto __finally2;
				}
				theme = gtk_mate_theme_create_from_plist (PLIST_DICT (plist));
				if (theme != NULL) {
					gee_collection_add ((GeeCollection*) gtk_mate_theme__themes, theme);
				}
				(plist == NULL) ? NULL : (plist = (g_object_unref (plist), NULL));
				(theme == NULL) ? NULL : (theme = (g_object_unref (theme), NULL));
			}
			goto __finally2;
			__catch2_xml_error:
			{
				GError * e;
				e = _inner_error_;
				_inner_error_ = NULL;
				{
					fprintf (stdout, "error opening %s\n", fn);
					(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
				}
			}
			__finally2:
			if (_inner_error_ != NULL) {
				fn = (g_free (fn), NULL);
				(_fn_it == NULL) ? NULL : (_fn_it = (g_object_unref (_fn_it), NULL));
				g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
				g_clear_error (&_inner_error_);
				return;
			}
			fn = (g_free (fn), NULL);
		}
		(_fn_it == NULL) ? NULL : (_fn_it = (g_object_unref (_fn_it), NULL));
	}
}


/* Return a list of bundle names like "Ruby.tmbundle"*/
GeeArrayList* gtk_mate_bundle_dirs (void) {
	GError * _inner_error_;
	char* name;
	char* share_dir;
	GeeArrayList* names;
	GeeArrayList* _tmp6_;
	_inner_error_ = NULL;
	name = NULL;
	share_dir = gtk_mate_textmate_share_dir ();
	names = gee_array_list_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, g_direct_equal);
	{
		char* _tmp0_;
		GDir* _tmp1_;
		GDir* d;
		char* _tmp3_;
		const char* _tmp2_;
		GeeArrayList* _tmp4_;
		_tmp0_ = NULL;
		_tmp1_ = NULL;
		d = (_tmp1_ = g_dir_open (_tmp0_ = g_strconcat (share_dir, "/Bundles", NULL), 0, &_inner_error_), _tmp0_ = (g_free (_tmp0_), NULL), _tmp1_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_FILE_ERROR) {
				goto __catch3_g_file_error;
			}
			goto __finally3;
		}
		_tmp3_ = NULL;
		_tmp2_ = NULL;
		while ((name = (_tmp3_ = (_tmp2_ = g_dir_read_name (d), (_tmp2_ == NULL) ? NULL : g_strdup (_tmp2_)), name = (g_free (name), NULL), _tmp3_)) != NULL) {
			if (g_str_has_suffix (name, ".tmbundle")) {
				gee_collection_add ((GeeCollection*) names, name);
			}
		}
		_tmp4_ = NULL;
		return (_tmp4_ = names, (d == NULL) ? NULL : (d = (g_dir_close (d), NULL)), name = (g_free (name), NULL), share_dir = (g_free (share_dir), NULL), _tmp4_);
	}
	goto __finally3;
	__catch3_g_file_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			char* _tmp5_;
			_tmp5_ = NULL;
			fprintf (stdout, "couldn't open: %s\n", _tmp5_ = g_strconcat (share_dir, "/Bundles", NULL));
			_tmp5_ = (g_free (_tmp5_), NULL);
			(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
		}
	}
	__finally3:
	if (_inner_error_ != NULL) {
		name = (g_free (name), NULL);
		share_dir = (g_free (share_dir), NULL);
		(names == NULL) ? NULL : (names = (g_object_unref (names), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	_tmp6_ = NULL;
	return (_tmp6_ = NULL, name = (g_free (name), NULL), share_dir = (g_free (share_dir), NULL), (names == NULL) ? NULL : (names = (g_object_unref (names), NULL)), _tmp6_);
}


/* Return the textmate assets directory path,
 e.g. /usr/share/textmate*/
char* gtk_mate_textmate_share_dir (void) {
	char* share_dir;
	char* _tmp3_;
	char* _tmp5_;
	if (gtk_mate_textmate_dir != NULL) {
		const char* _tmp0_;
		_tmp0_ = NULL;
		return (_tmp0_ = gtk_mate_textmate_dir, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
	}
	share_dir = g_strdup ("/usr/local/share/textmate");
	if (g_file_test (share_dir, G_FILE_TEST_EXISTS)) {
		return share_dir;
	}
	_tmp3_ = NULL;
	share_dir = (_tmp3_ = g_strdup ("/usr/share/textmate"), share_dir = (g_free (share_dir), NULL), _tmp3_);
	if (g_file_test (share_dir, G_FILE_TEST_EXISTS)) {
		return share_dir;
	}
	fprintf (stdout, "couldn't find /usr/share/textmate or /usr/local/share/textmate\n");
	_tmp5_ = NULL;
	return (_tmp5_ = NULL, share_dir = (g_free (share_dir), NULL), _tmp5_);
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


static gint _vala_array_length (gpointer array) {
	int length;
	length = 0;
	if (array) {
		while (((gpointer*) array)[length]) {
			length++;
		}
	}
	return length;
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




