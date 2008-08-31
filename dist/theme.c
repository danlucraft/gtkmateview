
#include "theme.h"
#include <gee/map.h>
#include <gee/collection.h>
#include <stdio.h>
#include "gtkmateview.h"
#include "scope.h"
#include "matcher.h"




enum  {
	GTK_MATE_THEME_SETTING_DUMMY_PROPERTY
};
static gpointer gtk_mate_theme_setting_parent_class = NULL;
static void gtk_mate_theme_setting_finalize (GObject * obj);
enum  {
	GTK_MATE_THEME_DUMMY_PROPERTY
};
GeeArrayList* gtk_mate_theme_themes = NULL;
static gpointer gtk_mate_theme_parent_class = NULL;
static void gtk_mate_theme_finalize (GObject * obj);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);



GtkMateThemeSetting* gtk_mate_theme_setting_create_from_plist (PListDict* dict) {
	GtkMateThemeSetting* tsetting;
	PListNode* nm;
	PListNode* _tmp2;
	GeeHashMap* _tmp5;
	PListDict* pd;
	GtkMateThemeSetting* _tmp7;
	g_return_val_if_fail (PLIST_IS_DICT (dict), NULL);
	tsetting = g_object_ref_sink (gtk_mate_theme_setting_new ());
	nm = plist_dict_get (dict, "name");
	if (nm != NULL) {
		char* _tmp1;
		const char* _tmp0;
		_tmp1 = NULL;
		_tmp0 = NULL;
		tsetting->name = (_tmp1 = (_tmp0 = (PLIST_STRING (nm))->str, (_tmp0 == NULL ? NULL : g_strdup (_tmp0))), (tsetting->name = (g_free (tsetting->name), NULL)), _tmp1);
	}
	_tmp2 = NULL;
	nm = (_tmp2 = plist_dict_get (dict, "scope"), (nm == NULL ? NULL : (nm = (g_object_unref (nm), NULL))), _tmp2);
	if (nm != NULL) {
		char* _tmp4;
		const char* _tmp3;
		_tmp4 = NULL;
		_tmp3 = NULL;
		tsetting->selector = (_tmp4 = (_tmp3 = (PLIST_STRING (nm))->str, (_tmp3 == NULL ? NULL : g_strdup (_tmp3))), (tsetting->selector = (g_free (tsetting->selector), NULL)), _tmp4);
	}
	_tmp5 = NULL;
	tsetting->settings = (_tmp5 = gee_hash_map_new (G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, g_str_hash, g_str_equal, g_direct_equal), (tsetting->settings == NULL ? NULL : (tsetting->settings = (g_object_unref (tsetting->settings), NULL))), _tmp5);
	pd = PLIST_DICT (plist_dict_get (dict, "settings"));
	{
		GeeSet* key_collection;
		GeeIterator* key_it;
		key_collection = gee_map_get_keys (GEE_MAP (pd->map));
		key_it = gee_iterable_iterator (GEE_ITERABLE (key_collection));
		while (gee_iterator_next (key_it)) {
			char* key;
			key = ((char*) (gee_iterator_get (key_it)));
			{
				PListString* _tmp6;
				_tmp6 = NULL;
				gee_map_set (GEE_MAP (tsetting->settings), key, (_tmp6 = (PLIST_STRING (((PListNode*) (gee_map_get (GEE_MAP (pd->map), key))))))->str);
				(_tmp6 == NULL ? NULL : (_tmp6 = (g_object_unref (_tmp6), NULL)));
				key = (g_free (key), NULL);
			}
		}
		(key_it == NULL ? NULL : (key_it = (g_object_unref (key_it), NULL)));
		(key_collection == NULL ? NULL : (key_collection = (g_object_unref (key_collection), NULL)));
	}
	_tmp7 = NULL;
	return (_tmp7 = tsetting, (nm == NULL ? NULL : (nm = (g_object_unref (nm), NULL))), (pd == NULL ? NULL : (pd = (g_object_unref (pd), NULL))), _tmp7);
}


void gtk_mate_theme_setting_compile_scope_matchers (GtkMateThemeSetting* self) {
	g_return_if_fail (GTK_MATE_IS_THEME_SETTING (self));
}


GtkMateThemeSetting* gtk_mate_theme_setting_new (void) {
	GtkMateThemeSetting * self;
	self = g_object_newv (GTK_MATE_TYPE_THEME_SETTING, 0, NULL);
	return self;
}


static void gtk_mate_theme_setting_class_init (GtkMateThemeSettingClass * klass) {
	gtk_mate_theme_setting_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_theme_setting_finalize;
}


static void gtk_mate_theme_setting_instance_init (GtkMateThemeSetting * self) {
}


static void gtk_mate_theme_setting_finalize (GObject * obj) {
	GtkMateThemeSetting * self;
	self = GTK_MATE_THEME_SETTING (obj);
	self->name = (g_free (self->name), NULL);
	self->selector = (g_free (self->selector), NULL);
	(self->settings == NULL ? NULL : (self->settings = (g_object_unref (self->settings), NULL)));
	(self->positive_rx == NULL ? NULL : (self->positive_rx = (g_object_unref (self->positive_rx), NULL)));
	(self->negative_rx == NULL ? NULL : (self->negative_rx = (g_object_unref (self->negative_rx), NULL)));
	G_OBJECT_CLASS (gtk_mate_theme_setting_parent_class)->finalize (obj);
}


GType gtk_mate_theme_setting_get_type (void) {
	static GType gtk_mate_theme_setting_type_id = 0;
	if (gtk_mate_theme_setting_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateThemeSettingClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_theme_setting_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateThemeSetting), 0, (GInstanceInitFunc) gtk_mate_theme_setting_instance_init };
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
	g_return_val_if_fail (PLIST_IS_DICT (dict), NULL);
	theme = g_object_ref_sink (gtk_mate_theme_new ());
	theme->is_initialized = FALSE;
	nm = plist_dict_get (dict, "name");
	if (nm != NULL) {
		char* _tmp1;
		const char* _tmp0;
		_tmp1 = NULL;
		_tmp0 = NULL;
		theme->name = (_tmp1 = (_tmp0 = (PLIST_STRING (nm))->str, (_tmp0 == NULL ? NULL : g_strdup (_tmp0))), (theme->name = (g_free (theme->name), NULL)), _tmp1);
	}
	_tmp2 = NULL;
	nm = (_tmp2 = plist_dict_get (dict, "author"), (nm == NULL ? NULL : (nm = (g_object_unref (nm), NULL))), _tmp2);
	if (nm != NULL) {
		char* _tmp4;
		const char* _tmp3;
		_tmp4 = NULL;
		_tmp3 = NULL;
		theme->author = (_tmp4 = (_tmp3 = (PLIST_STRING (nm))->str, (_tmp3 == NULL ? NULL : g_strdup (_tmp3))), (theme->author = (g_free (theme->author), NULL)), _tmp4);
	}
	_tmp5 = NULL;
	theme->global_settings = (_tmp5 = gee_hash_map_new (G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, g_str_hash, g_str_equal, g_direct_equal), (theme->global_settings == NULL ? NULL : (theme->global_settings = (g_object_unref (theme->global_settings), NULL))), _tmp5);
	_tmp6 = NULL;
	theme->settings = (_tmp6 = gee_array_list_new (GTK_MATE_TYPE_THEME_SETTING, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal), (theme->settings == NULL ? NULL : (theme->settings = (g_object_unref (theme->settings), NULL))), _tmp6);
	na = PLIST_ARRAY (plist_dict_get (dict, "settings"));
	{
		GeeArrayList* nn_collection;
		int nn_it;
		nn_collection = na->array;
		for (nn_it = 0; nn_it < gee_collection_get_size (GEE_COLLECTION (nn_collection)); nn_it = nn_it + 1) {
			PListNode* nn;
			nn = ((PListNode*) (gee_list_get (GEE_LIST (nn_collection), nn_it)));
			{
				PListDict* _tmp7;
				PListDict* nd;
				PListNode* _tmp8;
				gboolean _tmp9;
				_tmp7 = NULL;
				nd = (_tmp7 = PLIST_DICT (nn), (_tmp7 == NULL ? NULL : g_object_ref (_tmp7)));
				_tmp8 = NULL;
				if ((_tmp9 = (_tmp8 = plist_dict_get (nd, "scope")) == NULL, (_tmp8 == NULL ? NULL : (_tmp8 = (g_object_unref (_tmp8), NULL))), _tmp9)) {
					PListDict* gsd;
					gsd = (PLIST_DICT (plist_dict_get (nd, "settings")));
					{
						gint _tmp10;
						char** key_collection;
						int key_collection_length1;
						int key_it;
						key_collection = plist_dict_keys (gsd, &_tmp10);
						key_collection_length1 = _tmp10;
						for (key_it = 0; (_tmp10 != -1 && key_it < _tmp10) || (_tmp10 == -1 && key_collection[key_it] != NULL); key_it = key_it + 1) {
							const char* _tmp12;
							char* key;
							_tmp12 = NULL;
							key = (_tmp12 = key_collection[key_it], (_tmp12 == NULL ? NULL : g_strdup (_tmp12)));
							{
								PListString* _tmp11;
								_tmp11 = NULL;
								gee_map_set (GEE_MAP (theme->global_settings), key, (_tmp11 = (PLIST_STRING (plist_dict_get (gsd, key))))->str);
								(_tmp11 == NULL ? NULL : (_tmp11 = (g_object_unref (_tmp11), NULL)));
								key = (g_free (key), NULL);
							}
						}
						key_collection = (_vala_array_free (key_collection, key_collection_length1, ((GDestroyNotify) (g_free))), NULL);
					}
					(gsd == NULL ? NULL : (gsd = (g_object_unref (gsd), NULL)));
				} else {
					GtkMateThemeSetting* _tmp13;
					_tmp13 = NULL;
					gee_collection_add (GEE_COLLECTION (theme->settings), (_tmp13 = gtk_mate_theme_setting_create_from_plist (nd)));
					(_tmp13 == NULL ? NULL : (_tmp13 = (g_object_unref (_tmp13), NULL)));
				}
				(nn == NULL ? NULL : (nn = (g_object_unref (nn), NULL)));
				(nd == NULL ? NULL : (nd = (g_object_unref (nd), NULL)));
			}
		}
	}
	_tmp14 = NULL;
	return (_tmp14 = theme, (nm == NULL ? NULL : (nm = (g_object_unref (nm), NULL))), (na == NULL ? NULL : (na = (g_object_unref (na), NULL))), _tmp14);
}


void gtk_mate_theme_init_for_use (GtkMateTheme* self) {
	g_return_if_fail (GTK_MATE_IS_THEME (self));
	if (self->is_initialized) {
		return;
	}
	self->is_initialized = TRUE;
	fprintf (stdout, "initializing theme for use: %s\n", self->name);
	{
		GeeArrayList* setting_collection;
		int setting_it;
		setting_collection = self->settings;
		for (setting_it = 0; setting_it < gee_collection_get_size (GEE_COLLECTION (setting_collection)); setting_it = setting_it + 1) {
			GtkMateThemeSetting* setting;
			setting = ((GtkMateThemeSetting*) (gee_list_get (GEE_LIST (setting_collection), setting_it)));
			{
				gtk_mate_theme_setting_compile_scope_matchers (setting);
				(setting == NULL ? NULL : (setting = (g_object_unref (setting), NULL)));
			}
		}
	}
}


GeeArrayList* gtk_mate_theme_theme_filenames (void) {
	GError * inner_error;
	GeeArrayList* names;
	char* share_dir;
	char* name;
	GeeArrayList* _tmp8;
	inner_error = NULL;
	names = gee_array_list_new (G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, g_direct_equal);
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
		d = (_tmp1 = g_dir_open ((_tmp0 = g_strconcat (share_dir, "/Themes", NULL)), 0, &inner_error), (_tmp0 = (g_free (_tmp0), NULL)), _tmp1);
		if (inner_error != NULL) {
			if (inner_error->domain == G_FILE_ERROR) {
				goto __catch0_g_file_error;
			}
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
			g_clear_error (&inner_error);
		}
		_tmp3 = NULL;
		_tmp2 = NULL;
		while ((name = (_tmp3 = (_tmp2 = g_dir_read_name (d), (_tmp2 == NULL ? NULL : g_strdup (_tmp2))), (name = (g_free (name), NULL)), _tmp3)) != NULL) {
			if (g_str_has_suffix (name, ".tmTheme")) {
				char* _tmp5;
				char* _tmp4;
				_tmp5 = NULL;
				_tmp4 = NULL;
				gee_collection_add (GEE_COLLECTION (names), (_tmp5 = g_strconcat ((_tmp4 = g_strconcat (share_dir, "/Themes/", NULL)), name, NULL)));
				_tmp5 = (g_free (_tmp5), NULL);
				_tmp4 = (g_free (_tmp4), NULL);
			}
		}
		_tmp6 = NULL;
		return (_tmp6 = names, (d == NULL ? NULL : (d = (g_dir_close (d), NULL))), (share_dir = (g_free (share_dir), NULL)), (name = (g_free (name), NULL)), _tmp6);
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
			fprintf (stdout, "couldn't open: %s\n", (_tmp7 = g_strconcat (share_dir, "/Bundles", NULL)));
			_tmp7 = (g_free (_tmp7), NULL);
			(e == NULL ? NULL : (e = (g_error_free (e), NULL)));
		}
	}
	__finally0:
	;
	_tmp8 = NULL;
	return (_tmp8 = NULL, (names == NULL ? NULL : (names = (g_object_unref (names), NULL))), (share_dir = (g_free (share_dir), NULL)), (name = (g_free (name), NULL)), _tmp8);
}


/* TODO make this return multiple themes if they are identical
 (see 13.5 of Textmate manual)*/
GtkMateThemeSetting* gtk_mate_theme_settings_for_scope (GtkMateTheme* self, GtkMateScope* scope, gboolean inner) {
	char* scope_name;
	OnigurumaMatch* current_m;
	OnigurumaMatch* m;
	GtkMateThemeSetting* current;
	GtkMateThemeSetting* _tmp11;
	g_return_val_if_fail (GTK_MATE_IS_THEME (self), NULL);
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (scope), NULL);
	scope_name = gtk_mate_scope_hierarchy_names (scope, inner);
	fprintf (stdout, "  finding settings for '%s'\n", scope_name);
	current_m = NULL;
	m = NULL;
	current = NULL;
	{
		GeeArrayList* setting_collection;
		int setting_it;
		setting_collection = self->settings;
		for (setting_it = 0; setting_it < gee_collection_get_size (GEE_COLLECTION (setting_collection)); setting_it = setting_it + 1) {
			GtkMateThemeSetting* setting;
			setting = ((GtkMateThemeSetting*) (gee_list_get (GEE_LIST (setting_collection), setting_it)));
			{
				OnigurumaMatch* _tmp2;
				gboolean _tmp1;
				OnigurumaMatch* _tmp0;
				_tmp2 = NULL;
				_tmp0 = NULL;
				if ((_tmp1 = gtk_mate_matcher_match (setting->selector, scope_name, &_tmp0), m = (_tmp2 = _tmp0, (m == NULL ? NULL : (m = (g_object_unref (m), NULL))), _tmp2), _tmp1)) {
					fprintf (stdout, "    setting '%s' with selector '%s'\n", setting->name, setting->selector);
					if (current == NULL) {
						GtkMateThemeSetting* _tmp4;
						GtkMateThemeSetting* _tmp3;
						OnigurumaMatch* _tmp6;
						OnigurumaMatch* _tmp5;
						_tmp4 = NULL;
						_tmp3 = NULL;
						current = (_tmp4 = (_tmp3 = setting, (_tmp3 == NULL ? NULL : g_object_ref (_tmp3))), (current == NULL ? NULL : (current = (g_object_unref (current), NULL))), _tmp4);
						_tmp6 = NULL;
						_tmp5 = NULL;
						current_m = (_tmp6 = (_tmp5 = m, (_tmp5 == NULL ? NULL : g_object_ref (_tmp5))), (current_m == NULL ? NULL : (current_m = (g_object_unref (current_m), NULL))), _tmp6);
					} else {
						if (gtk_mate_matcher_compare_match (scope_name, current_m, m) < 0) {
							GtkMateThemeSetting* _tmp8;
							GtkMateThemeSetting* _tmp7;
							OnigurumaMatch* _tmp10;
							OnigurumaMatch* _tmp9;
							_tmp8 = NULL;
							_tmp7 = NULL;
							current = (_tmp8 = (_tmp7 = setting, (_tmp7 == NULL ? NULL : g_object_ref (_tmp7))), (current == NULL ? NULL : (current = (g_object_unref (current), NULL))), _tmp8);
							_tmp10 = NULL;
							_tmp9 = NULL;
							current_m = (_tmp10 = (_tmp9 = m, (_tmp9 == NULL ? NULL : g_object_ref (_tmp9))), (current_m == NULL ? NULL : (current_m = (g_object_unref (current_m), NULL))), _tmp10);
						}
					}
				}
				(setting == NULL ? NULL : (setting = (g_object_unref (setting), NULL)));
			}
		}
	}
	if (current == NULL) {
	} else {
		/* stdout.printf("none match\n");*/
		fprintf (stdout, "    best: '%s'\n", current->name);
	}
	_tmp11 = NULL;
	return (_tmp11 = current, (scope_name = (g_free (scope_name), NULL)), (current_m == NULL ? NULL : (current_m = (g_object_unref (current_m), NULL))), (m == NULL ? NULL : (m = (g_object_unref (m), NULL))), _tmp11);
}


/* stdout.printf("compiling '%s'\n", selector);*/
GtkMateTheme* gtk_mate_theme_new (void) {
	GtkMateTheme * self;
	self = g_object_newv (GTK_MATE_TYPE_THEME, 0, NULL);
	return self;
}


static void gtk_mate_theme_class_init (GtkMateThemeClass * klass) {
	gtk_mate_theme_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_theme_finalize;
}


static void gtk_mate_theme_instance_init (GtkMateTheme * self) {
}


static void gtk_mate_theme_finalize (GObject * obj) {
	GtkMateTheme * self;
	self = GTK_MATE_THEME (obj);
	self->author = (g_free (self->author), NULL);
	self->name = (g_free (self->name), NULL);
	(self->global_settings == NULL ? NULL : (self->global_settings = (g_object_unref (self->global_settings), NULL)));
	(self->settings == NULL ? NULL : (self->settings = (g_object_unref (self->settings), NULL)));
	G_OBJECT_CLASS (gtk_mate_theme_parent_class)->finalize (obj);
}


GType gtk_mate_theme_get_type (void) {
	static GType gtk_mate_theme_type_id = 0;
	if (gtk_mate_theme_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateThemeClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_theme_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateTheme), 0, (GInstanceInitFunc) gtk_mate_theme_instance_init };
		gtk_mate_theme_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateTheme", &g_define_type_info, 0);
	}
	return gtk_mate_theme_type_id;
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




