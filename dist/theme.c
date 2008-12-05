
#include "theme.h"
#include <gee/map.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>
#include <stdio.h>
#include "matcher.h"
#include "gtkmateview.h"
#include "scope.h"




enum  {
	GTK_MATE_THEME_SETTING_DUMMY_PROPERTY
};
static gpointer gtk_mate_theme_setting_parent_class = NULL;
static void gtk_mate_theme_setting_finalize (GObject* obj);
enum  {
	GTK_MATE_THEME_DUMMY_PROPERTY
};
GeeArrayList* gtk_mate_theme_themes = NULL;
static gpointer gtk_mate_theme_parent_class = NULL;
static void gtk_mate_theme_finalize (GObject* obj);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);



GtkMateThemeSetting* gtk_mate_theme_setting_create_from_plist (PListDict* dict) {
	GtkMateThemeSetting* tsetting;
	PListNode* nm;
	PListNode* _tmp2;
	GeeHashMap* _tmp5;
	PListDict* pd;
	GtkMateThemeSetting* _tmp9;
	g_return_val_if_fail (dict != NULL, NULL);
	tsetting = g_object_ref_sink (gtk_mate_theme_setting_new ());
	nm = plist_dict_get (dict, "name");
	if (nm != NULL) {
		char* _tmp1;
		const char* _tmp0;
		_tmp1 = NULL;
		_tmp0 = NULL;
		tsetting->name = (_tmp1 = (_tmp0 = (PLIST_STRING (nm))->str, (_tmp0 == NULL) ? NULL : g_strdup (_tmp0)), tsetting->name = (g_free (tsetting->name), NULL), _tmp1);
	}
	_tmp2 = NULL;
	nm = (_tmp2 = plist_dict_get (dict, "scope"), (nm == NULL) ? NULL : (nm = (g_object_unref (nm), NULL)), _tmp2);
	if (nm != NULL) {
		char* _tmp4;
		const char* _tmp3;
		_tmp4 = NULL;
		_tmp3 = NULL;
		tsetting->selector = (_tmp4 = (_tmp3 = (PLIST_STRING (nm))->str, (_tmp3 == NULL) ? NULL : g_strdup (_tmp3)), tsetting->selector = (g_free (tsetting->selector), NULL), _tmp4);
	}
	_tmp5 = NULL;
	tsetting->settings = (_tmp5 = gee_hash_map_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, g_str_hash, g_str_equal, g_direct_equal), (tsetting->settings == NULL) ? NULL : (tsetting->settings = (g_object_unref (tsetting->settings), NULL)), _tmp5);
	pd = PLIST_DICT (plist_dict_get (dict, "settings"));
	{
		GeeSet* _tmp6;
		GeeIterator* _tmp7;
		GeeIterator* key_it;
		_tmp6 = NULL;
		_tmp7 = NULL;
		key_it = (_tmp7 = gee_iterable_iterator ((GeeIterable*) (_tmp6 = gee_map_get_keys ((GeeMap*) pd->map))), (_tmp6 == NULL) ? NULL : (_tmp6 = (g_object_unref (_tmp6), NULL)), _tmp7);
		while (gee_iterator_next (key_it)) {
			char* key;
			PListString* _tmp8;
			key = (char*) gee_iterator_get (key_it);
			_tmp8 = NULL;
			gee_map_set ((GeeMap*) tsetting->settings, key, (_tmp8 = (PLIST_STRING ((PListNode*) gee_map_get ((GeeMap*) pd->map, key))))->str);
			(_tmp8 == NULL) ? NULL : (_tmp8 = (g_object_unref (_tmp8), NULL));
			key = (g_free (key), NULL);
		}
		(key_it == NULL) ? NULL : (key_it = (g_object_unref (key_it), NULL));
	}
	_tmp9 = NULL;
	return (_tmp9 = tsetting, (nm == NULL) ? NULL : (nm = (g_object_unref (nm), NULL)), (pd == NULL) ? NULL : (pd = (g_object_unref (pd), NULL)), _tmp9);
}


void gtk_mate_theme_setting_compile_scope_matchers (GtkMateThemeSetting* self) {
	GeeArrayList* _tmp0;
	g_return_if_fail (self != NULL);
	/*stdout.printf("  compiling '%s'\n", selector);*/
	_tmp0 = NULL;
	self->matchers = (_tmp0 = gtk_mate_matcher_compile (self->selector), (self->matchers == NULL) ? NULL : (self->matchers = (g_object_unref (self->matchers), NULL)), _tmp0);
}


gboolean gtk_mate_theme_setting_match (GtkMateThemeSetting* self, const char* scope, OnigMatch** match) {
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (scope != NULL, FALSE);
	*match = NULL;
	if (self->matchers == NULL) {
		gtk_mate_theme_setting_compile_scope_matchers (self);
	}
	{
		GeeIterator* matcher_it;
		matcher_it = gee_iterable_iterator ((GeeIterable*) self->matchers);
		while (gee_iterator_next (matcher_it)) {
			GtkMateMatcher* matcher;
			OnigMatch* _tmp2;
			gboolean _tmp1;
			OnigMatch* _tmp0;
			matcher = (GtkMateMatcher*) gee_iterator_get (matcher_it);
			_tmp2 = NULL;
			_tmp0 = NULL;
			if ((_tmp1 = gtk_mate_matcher_test_match_re (matcher->pos_rx, matcher->neg_rxs, scope, &_tmp0), (*match) = (_tmp2 = _tmp0, ((*match) == NULL) ? NULL : ((*match) = (g_object_unref ((*match)), NULL)), _tmp2), _tmp1)) {
				gboolean _tmp3;
				return (_tmp3 = TRUE, (matcher == NULL) ? NULL : (matcher = (g_object_unref (matcher), NULL)), (matcher_it == NULL) ? NULL : (matcher_it = (g_object_unref (matcher_it), NULL)), _tmp3);
			}
			(matcher == NULL) ? NULL : (matcher = (g_object_unref (matcher), NULL));
		}
		(matcher_it == NULL) ? NULL : (matcher_it = (g_object_unref (matcher_it), NULL));
	}
	return FALSE;
}


GtkMateThemeSetting* gtk_mate_theme_setting_construct (GType object_type) {
	GtkMateThemeSetting * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


GtkMateThemeSetting* gtk_mate_theme_setting_new (void) {
	return gtk_mate_theme_setting_construct (GTK_MATE_TYPE_THEME_SETTING);
}


static void gtk_mate_theme_setting_class_init (GtkMateThemeSettingClass * klass) {
	gtk_mate_theme_setting_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_theme_setting_finalize;
}


static void gtk_mate_theme_setting_instance_init (GtkMateThemeSetting * self) {
}


static void gtk_mate_theme_setting_finalize (GObject* obj) {
	GtkMateThemeSetting * self;
	self = GTK_MATE_THEME_SETTING (obj);
	self->name = (g_free (self->name), NULL);
	self->selector = (g_free (self->selector), NULL);
	(self->settings == NULL) ? NULL : (self->settings = (g_object_unref (self->settings), NULL));
	(self->matchers == NULL) ? NULL : (self->matchers = (g_object_unref (self->matchers), NULL));
	G_OBJECT_CLASS (gtk_mate_theme_setting_parent_class)->finalize (obj);
}


GType gtk_mate_theme_setting_get_type (void) {
	static GType gtk_mate_theme_setting_type_id = 0;
	if (gtk_mate_theme_setting_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateThemeSettingClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_theme_setting_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateThemeSetting), 0, (GInstanceInitFunc) gtk_mate_theme_setting_instance_init, NULL };
		gtk_mate_theme_setting_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateThemeSetting", &g_define_type_info, 0);
	}
	return gtk_mate_theme_setting_type_id;
}


GtkMateTheme* gtk_mate_theme_create_from_plist (PListDict* dict) {
	GtkMateTheme* theme;
	PListNode* nm;
	PListNode* _tmp2;
	GeeHashMap* _tmp5;
	GeeArrayList* _tmp6;
	PListArray* na;
	GtkMateTheme* _tmp14;
	g_return_val_if_fail (dict != NULL, NULL);
	theme = g_object_ref_sink (gtk_mate_theme_new ());
	theme->is_initialized = FALSE;
	nm = plist_dict_get (dict, "name");
	if (nm != NULL) {
		char* _tmp1;
		const char* _tmp0;
		_tmp1 = NULL;
		_tmp0 = NULL;
		theme->name = (_tmp1 = (_tmp0 = (PLIST_STRING (nm))->str, (_tmp0 == NULL) ? NULL : g_strdup (_tmp0)), theme->name = (g_free (theme->name), NULL), _tmp1);
	}
	_tmp2 = NULL;
	nm = (_tmp2 = plist_dict_get (dict, "author"), (nm == NULL) ? NULL : (nm = (g_object_unref (nm), NULL)), _tmp2);
	if (nm != NULL) {
		char* _tmp4;
		const char* _tmp3;
		_tmp4 = NULL;
		_tmp3 = NULL;
		theme->author = (_tmp4 = (_tmp3 = (PLIST_STRING (nm))->str, (_tmp3 == NULL) ? NULL : g_strdup (_tmp3)), theme->author = (g_free (theme->author), NULL), _tmp4);
	}
	_tmp5 = NULL;
	theme->global_settings = (_tmp5 = gee_hash_map_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, g_str_hash, g_str_equal, g_direct_equal), (theme->global_settings == NULL) ? NULL : (theme->global_settings = (g_object_unref (theme->global_settings), NULL)), _tmp5);
	_tmp6 = NULL;
	theme->settings = (_tmp6 = gee_array_list_new (GTK_MATE_TYPE_THEME_SETTING, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (theme->settings == NULL) ? NULL : (theme->settings = (g_object_unref (theme->settings), NULL)), _tmp6);
	na = PLIST_ARRAY (plist_dict_get (dict, "settings"));
	{
		GeeIterator* nn_it;
		nn_it = gee_iterable_iterator ((GeeIterable*) na->array);
		while (gee_iterator_next (nn_it)) {
			PListNode* nn;
			PListDict* _tmp7;
			PListDict* nd;
			PListNode* _tmp8;
			gboolean _tmp9;
			nn = (PListNode*) gee_iterator_get (nn_it);
			_tmp7 = NULL;
			nd = (_tmp7 = PLIST_DICT (nn), (_tmp7 == NULL) ? NULL : g_object_ref (_tmp7));
			_tmp8 = NULL;
			if ((_tmp9 = (_tmp8 = plist_dict_get (nd, "scope")) == NULL, (_tmp8 == NULL) ? NULL : (_tmp8 = (g_object_unref (_tmp8), NULL)), _tmp9)) {
				PListDict* gsd;
				gsd = (PLIST_DICT (plist_dict_get (nd, "settings")));
				{
					gint _tmp10;
					char** key_collection;
					int key_collection_length1;
					int key_it;
					key_collection = plist_dict_keys (gsd, &_tmp10);
					key_collection_length1 = _tmp10;
					for (key_it = 0; ((_tmp10 != -1) && (key_it < _tmp10)) || ((_tmp10 == -1) && (key_collection[key_it] != NULL)); key_it = key_it + 1) {
						const char* _tmp12;
						char* key;
						_tmp12 = NULL;
						key = (_tmp12 = key_collection[key_it], (_tmp12 == NULL) ? NULL : g_strdup (_tmp12));
						{
							PListString* _tmp11;
							_tmp11 = NULL;
							gee_map_set ((GeeMap*) theme->global_settings, key, (_tmp11 = (PLIST_STRING (plist_dict_get (gsd, key))))->str);
							(_tmp11 == NULL) ? NULL : (_tmp11 = (g_object_unref (_tmp11), NULL));
							key = (g_free (key), NULL);
						}
					}
					key_collection = (_vala_array_free (key_collection, key_collection_length1, (GDestroyNotify) g_free), NULL);
				}
				(gsd == NULL) ? NULL : (gsd = (g_object_unref (gsd), NULL));
			} else {
				GtkMateThemeSetting* _tmp13;
				_tmp13 = NULL;
				gee_collection_add ((GeeCollection*) theme->settings, _tmp13 = gtk_mate_theme_setting_create_from_plist (nd));
				(_tmp13 == NULL) ? NULL : (_tmp13 = (g_object_unref (_tmp13), NULL));
			}
			(nn == NULL) ? NULL : (nn = (g_object_unref (nn), NULL));
			(nd == NULL) ? NULL : (nd = (g_object_unref (nd), NULL));
		}
		(nn_it == NULL) ? NULL : (nn_it = (g_object_unref (nn_it), NULL));
	}
	_tmp14 = NULL;
	return (_tmp14 = theme, (nm == NULL) ? NULL : (nm = (g_object_unref (nm), NULL)), (na == NULL) ? NULL : (na = (g_object_unref (na), NULL)), _tmp14);
}


void gtk_mate_theme_init_for_use (GtkMateTheme* self) {
	GeeHashMap* _tmp0;
	g_return_if_fail (self != NULL);
	if (self->is_initialized) {
		return;
	}
	self->is_initialized = TRUE;
	fprintf (stdout, "initializing theme for use: %s\n", self->name);
	_tmp0 = NULL;
	self->cached_setting_for_scopes = (_tmp0 = gee_hash_map_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, GTK_MATE_TYPE_THEME_SETTING, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_str_hash, g_str_equal, g_direct_equal), (self->cached_setting_for_scopes == NULL) ? NULL : (self->cached_setting_for_scopes = (g_object_unref (self->cached_setting_for_scopes), NULL)), _tmp0);
	{
		GeeIterator* setting_it;
		setting_it = gee_iterable_iterator ((GeeIterable*) self->settings);
		while (gee_iterator_next (setting_it)) {
			GtkMateThemeSetting* setting;
			setting = (GtkMateThemeSetting*) gee_iterator_get (setting_it);
			gtk_mate_theme_setting_compile_scope_matchers (setting);
			(setting == NULL) ? NULL : (setting = (g_object_unref (setting), NULL));
		}
		(setting_it == NULL) ? NULL : (setting_it = (g_object_unref (setting_it), NULL));
	}
}


GeeArrayList* gtk_mate_theme_theme_filenames (void) {
	GError * inner_error;
	GeeArrayList* names;
	char* share_dir;
	char* name;
	GeeArrayList* _tmp8;
	inner_error = NULL;
	names = gee_array_list_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, g_direct_equal);
	share_dir = gtk_mate_textmate_share_dir ();
	name = NULL;
	{
		char* _tmp0;
		GDir* _tmp1;
		GDir* d;
		char* _tmp3;
		const char* _tmp2;
		GeeArrayList* _tmp6;
		_tmp0 = NULL;
		_tmp1 = NULL;
		d = (_tmp1 = g_dir_open (_tmp0 = g_strconcat (share_dir, "/Themes", NULL), 0, &inner_error), _tmp0 = (g_free (_tmp0), NULL), _tmp1);
		if (inner_error != NULL) {
			if (inner_error->domain == G_FILE_ERROR) {
				goto __catch0_g_file_error;
			}
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
			g_clear_error (&inner_error);
		}
		_tmp3 = NULL;
		_tmp2 = NULL;
		while ((name = (_tmp3 = (_tmp2 = g_dir_read_name (d), (_tmp2 == NULL) ? NULL : g_strdup (_tmp2)), name = (g_free (name), NULL), _tmp3)) != NULL) {
			if (g_str_has_suffix (name, ".tmTheme")) {
				char* _tmp5;
				char* _tmp4;
				_tmp5 = NULL;
				_tmp4 = NULL;
				gee_collection_add ((GeeCollection*) names, _tmp5 = g_strconcat (_tmp4 = g_strconcat (share_dir, "/Themes/", NULL), name, NULL));
				_tmp5 = (g_free (_tmp5), NULL);
				_tmp4 = (g_free (_tmp4), NULL);
			}
		}
		_tmp6 = NULL;
		return (_tmp6 = names, (d == NULL) ? NULL : (d = (g_dir_close (d), NULL)), share_dir = (g_free (share_dir), NULL), name = (g_free (name), NULL), _tmp6);
	}
	goto __finally0;
	__catch0_g_file_error:
	{
		GError * e;
		e = inner_error;
		inner_error = NULL;
		{
			char* _tmp7;
			_tmp7 = NULL;
			fprintf (stdout, "couldn't open: %s\n", _tmp7 = g_strconcat (share_dir, "/Bundles", NULL));
			_tmp7 = (g_free (_tmp7), NULL);
			(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
		}
	}
	__finally0:
	;
	_tmp8 = NULL;
	return (_tmp8 = NULL, (names == NULL) ? NULL : (names = (g_object_unref (names), NULL)), share_dir = (g_free (share_dir), NULL), name = (g_free (name), NULL), _tmp8);
}


/* TODO make this return multiple themes if they are identical
 (see 13.5 of Textmate manual)*/
GtkMateThemeSetting* gtk_mate_theme_settings_for_scope (GtkMateTheme* self, GtkMateScope* scope, gboolean inner) {
	char* scope_name;
	GtkMateThemeSetting* cached;
	OnigMatch* current_m;
	OnigMatch* m;
	GtkMateThemeSetting* current;
	GtkMateThemeSetting* _tmp13;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (scope != NULL, NULL);
	scope_name = gtk_mate_scope_hierarchy_names (scope, inner);
	/*stdout.printf("  finding settings for '%s'\n", scope_name);*/
	cached = NULL;
	if (gee_map_contains ((GeeMap*) self->cached_setting_for_scopes, scope_name)) {
		GtkMateThemeSetting* _tmp0;
		GtkMateThemeSetting* _tmp1;
		_tmp0 = NULL;
		cached = (_tmp0 = (GtkMateThemeSetting*) gee_map_get ((GeeMap*) self->cached_setting_for_scopes, scope_name), (cached == NULL) ? NULL : (cached = (g_object_unref (cached), NULL)), _tmp0);
		_tmp1 = NULL;
		return (_tmp1 = cached, scope_name = (g_free (scope_name), NULL), _tmp1);
	}
	current_m = NULL;
	m = NULL;
	current = NULL;
	{
		GeeIterator* setting_it;
		setting_it = gee_iterable_iterator ((GeeIterable*) self->settings);
		while (gee_iterator_next (setting_it)) {
			GtkMateThemeSetting* setting;
			OnigMatch* _tmp4;
			gboolean _tmp3;
			OnigMatch* _tmp2;
			setting = (GtkMateThemeSetting*) gee_iterator_get (setting_it);
			_tmp4 = NULL;
			_tmp2 = NULL;
			if ((_tmp3 = gtk_mate_theme_setting_match (setting, scope_name, &_tmp2), m = (_tmp4 = _tmp2, (m == NULL) ? NULL : (m = (g_object_unref (m), NULL)), _tmp4), _tmp3)) {
				fprintf (stdout, "    setting '%s' with selector '%s'\n", setting->name, setting->selector);
				if (current == NULL) {
					GtkMateThemeSetting* _tmp6;
					GtkMateThemeSetting* _tmp5;
					OnigMatch* _tmp8;
					OnigMatch* _tmp7;
					_tmp6 = NULL;
					_tmp5 = NULL;
					current = (_tmp6 = (_tmp5 = setting, (_tmp5 == NULL) ? NULL : g_object_ref (_tmp5)), (current == NULL) ? NULL : (current = (g_object_unref (current), NULL)), _tmp6);
					_tmp8 = NULL;
					_tmp7 = NULL;
					current_m = (_tmp8 = (_tmp7 = m, (_tmp7 == NULL) ? NULL : g_object_ref (_tmp7)), (current_m == NULL) ? NULL : (current_m = (g_object_unref (current_m), NULL)), _tmp8);
				} else {
					if (gtk_mate_matcher_compare_match (scope_name, current_m, m) < 0) {
						GtkMateThemeSetting* _tmp10;
						GtkMateThemeSetting* _tmp9;
						OnigMatch* _tmp12;
						OnigMatch* _tmp11;
						_tmp10 = NULL;
						_tmp9 = NULL;
						current = (_tmp10 = (_tmp9 = setting, (_tmp9 == NULL) ? NULL : g_object_ref (_tmp9)), (current == NULL) ? NULL : (current = (g_object_unref (current), NULL)), _tmp10);
						_tmp12 = NULL;
						_tmp11 = NULL;
						current_m = (_tmp12 = (_tmp11 = m, (_tmp11 == NULL) ? NULL : g_object_ref (_tmp11)), (current_m == NULL) ? NULL : (current_m = (g_object_unref (current_m), NULL)), _tmp12);
					}
				}
			}
			(setting == NULL) ? NULL : (setting = (g_object_unref (setting), NULL));
		}
		(setting_it == NULL) ? NULL : (setting_it = (g_object_unref (setting_it), NULL));
	}
	if (current == NULL) {
		fprintf (stdout, "none match\n");
	} else {
		fprintf (stdout, "    best: '%s'\n", current->name);
	}
	gee_map_set ((GeeMap*) self->cached_setting_for_scopes, scope_name, current);
	_tmp13 = NULL;
	return (_tmp13 = current, scope_name = (g_free (scope_name), NULL), (cached == NULL) ? NULL : (cached = (g_object_unref (cached), NULL)), (current_m == NULL) ? NULL : (current_m = (g_object_unref (current_m), NULL)), (m == NULL) ? NULL : (m = (g_object_unref (m), NULL)), _tmp13);
}


GtkMateTheme* gtk_mate_theme_construct (GType object_type) {
	GtkMateTheme * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


GtkMateTheme* gtk_mate_theme_new (void) {
	return gtk_mate_theme_construct (GTK_MATE_TYPE_THEME);
}


static void gtk_mate_theme_class_init (GtkMateThemeClass * klass) {
	gtk_mate_theme_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_theme_finalize;
}


static void gtk_mate_theme_instance_init (GtkMateTheme * self) {
}


static void gtk_mate_theme_finalize (GObject* obj) {
	GtkMateTheme * self;
	self = GTK_MATE_THEME (obj);
	self->author = (g_free (self->author), NULL);
	self->name = (g_free (self->name), NULL);
	(self->global_settings == NULL) ? NULL : (self->global_settings = (g_object_unref (self->global_settings), NULL));
	(self->settings == NULL) ? NULL : (self->settings = (g_object_unref (self->settings), NULL));
	(self->cached_setting_for_scopes == NULL) ? NULL : (self->cached_setting_for_scopes = (g_object_unref (self->cached_setting_for_scopes), NULL));
	G_OBJECT_CLASS (gtk_mate_theme_parent_class)->finalize (obj);
}


GType gtk_mate_theme_get_type (void) {
	static GType gtk_mate_theme_type_id = 0;
	if (gtk_mate_theme_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateThemeClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_theme_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateTheme), 0, (GInstanceInitFunc) gtk_mate_theme_instance_init, NULL };
		gtk_mate_theme_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateTheme", &g_define_type_info, 0);
	}
	return gtk_mate_theme_type_id;
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




