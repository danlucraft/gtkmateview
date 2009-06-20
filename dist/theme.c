
#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gee/hashmap.h>
#include <gee/arraylist.h>
#include <gee/map.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>
#include <stdio.h>


#define GTK_MATE_TYPE_THEME_SETTING (gtk_mate_theme_setting_get_type ())
#define GTK_MATE_THEME_SETTING(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSetting))
#define GTK_MATE_THEME_SETTING_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSettingClass))
#define GTK_MATE_IS_THEME_SETTING(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_THEME_SETTING))
#define GTK_MATE_IS_THEME_SETTING_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_THEME_SETTING))
#define GTK_MATE_THEME_SETTING_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSettingClass))

typedef struct _GtkMateThemeSetting GtkMateThemeSetting;
typedef struct _GtkMateThemeSettingClass GtkMateThemeSettingClass;
typedef struct _GtkMateThemeSettingPrivate GtkMateThemeSettingPrivate;

#define GTK_MATE_TYPE_MATCHER (gtk_mate_matcher_get_type ())
#define GTK_MATE_MATCHER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_MATCHER, GtkMateMatcher))
#define GTK_MATE_MATCHER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_MATCHER, GtkMateMatcherClass))
#define GTK_MATE_IS_MATCHER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_MATCHER))
#define GTK_MATE_IS_MATCHER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_MATCHER))
#define GTK_MATE_MATCHER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_MATCHER, GtkMateMatcherClass))

typedef struct _GtkMateMatcher GtkMateMatcher;
typedef struct _GtkMateMatcherClass GtkMateMatcherClass;

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
typedef struct _PListNodePrivate PListNodePrivate;

#define PLIST_TYPE_STRING (plist_string_get_type ())
#define PLIST_STRING(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PLIST_TYPE_STRING, PListString))
#define PLIST_STRING_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PLIST_TYPE_STRING, PListStringClass))
#define PLIST_IS_STRING(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PLIST_TYPE_STRING))
#define PLIST_IS_STRING_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PLIST_TYPE_STRING))
#define PLIST_STRING_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PLIST_TYPE_STRING, PListStringClass))

typedef struct _PListString PListString;
typedef struct _PListStringClass PListStringClass;
typedef struct _PListStringPrivate PListStringPrivate;
typedef struct _PListDictPrivate PListDictPrivate;

#define ONIG_TYPE_RX (onig_rx_get_type ())
#define ONIG_RX(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIG_TYPE_RX, OnigRx))
#define ONIG_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIG_TYPE_RX, OnigRxClass))
#define ONIG_IS_RX(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIG_TYPE_RX))
#define ONIG_IS_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIG_TYPE_RX))
#define ONIG_RX_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIG_TYPE_RX, OnigRxClass))

typedef struct _OnigRx OnigRx;
typedef struct _OnigRxClass OnigRxClass;

#define ONIG_TYPE_MATCH (onig_match_get_type ())
#define ONIG_MATCH(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIG_TYPE_MATCH, OnigMatch))
#define ONIG_MATCH_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIG_TYPE_MATCH, OnigMatchClass))
#define ONIG_IS_MATCH(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIG_TYPE_MATCH))
#define ONIG_IS_MATCH_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIG_TYPE_MATCH))
#define ONIG_MATCH_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIG_TYPE_MATCH, OnigMatchClass))

typedef struct _OnigMatch OnigMatch;
typedef struct _OnigMatchClass OnigMatchClass;
typedef struct _GtkMateMatcherPrivate GtkMateMatcherPrivate;

#define GTK_MATE_TYPE_THEME (gtk_mate_theme_get_type ())
#define GTK_MATE_THEME(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_THEME, GtkMateTheme))
#define GTK_MATE_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_THEME, GtkMateThemeClass))
#define GTK_MATE_IS_THEME(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_THEME))
#define GTK_MATE_IS_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_THEME))
#define GTK_MATE_THEME_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_THEME, GtkMateThemeClass))

typedef struct _GtkMateTheme GtkMateTheme;
typedef struct _GtkMateThemeClass GtkMateThemeClass;
typedef struct _GtkMateThemePrivate GtkMateThemePrivate;

#define PLIST_TYPE_ARRAY (plist_array_get_type ())
#define PLIST_ARRAY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PLIST_TYPE_ARRAY, PListArray))
#define PLIST_ARRAY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PLIST_TYPE_ARRAY, PListArrayClass))
#define PLIST_IS_ARRAY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PLIST_TYPE_ARRAY))
#define PLIST_IS_ARRAY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PLIST_TYPE_ARRAY))
#define PLIST_ARRAY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PLIST_TYPE_ARRAY, PListArrayClass))

typedef struct _PListArray PListArray;
typedef struct _PListArrayClass PListArrayClass;
typedef struct _PListArrayPrivate PListArrayPrivate;

#define GTK_MATE_TYPE_SCOPE (gtk_mate_scope_get_type ())
#define GTK_MATE_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SCOPE, GtkMateScope))
#define GTK_MATE_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SCOPE, GtkMateScopeClass))
#define GTK_MATE_IS_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SCOPE))
#define GTK_MATE_IS_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SCOPE))
#define GTK_MATE_SCOPE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SCOPE, GtkMateScopeClass))

typedef struct _GtkMateScope GtkMateScope;
typedef struct _GtkMateScopeClass GtkMateScopeClass;

struct _GtkMateThemeSetting {
	GtkObject parent_instance;
	GtkMateThemeSettingPrivate * priv;
	char* name;
	char* selector;
	GeeHashMap* settings;
	GeeArrayList* matchers;
};

struct _GtkMateThemeSettingClass {
	GtkObjectClass parent_class;
};

struct _PListNode {
	GObject parent_instance;
	PListNodePrivate * priv;
};

struct _PListNodeClass {
	GObjectClass parent_class;
};

struct _PListString {
	PListNode parent_instance;
	PListStringPrivate * priv;
	char* str;
};

struct _PListStringClass {
	PListNodeClass parent_class;
};

struct _PListDict {
	PListNode parent_instance;
	PListDictPrivate * priv;
	GeeHashMap* map;
};

struct _PListDictClass {
	PListNodeClass parent_class;
};

struct _GtkMateMatcher {
	GtkObject parent_instance;
	GtkMateMatcherPrivate * priv;
	OnigRx* pos_rx;
	GeeArrayList* neg_rxs;
};

struct _GtkMateMatcherClass {
	GtkObjectClass parent_class;
};

struct _GtkMateTheme {
	GtkObject parent_instance;
	GtkMateThemePrivate * priv;
	char* author;
	char* name;
	GeeHashMap* global_settings;
	GeeArrayList* settings;
	gboolean is_initialized;
	GeeHashMap* cached_setting_for_scopes;
};

struct _GtkMateThemeClass {
	GtkObjectClass parent_class;
};

struct _PListArray {
	PListNode parent_instance;
	PListArrayPrivate * priv;
	GeeArrayList* array;
};

struct _PListArrayClass {
	PListNodeClass parent_class;
};



GType gtk_mate_theme_setting_get_type (void);
GType gtk_mate_matcher_get_type (void);
enum  {
	GTK_MATE_THEME_SETTING_DUMMY_PROPERTY
};
GtkMateThemeSetting* gtk_mate_theme_setting_new (void);
GtkMateThemeSetting* gtk_mate_theme_setting_construct (GType object_type);
GType plist_node_get_type (void);
GType plist_dict_get_type (void);
PListNode* plist_dict_get (PListDict* self, const char* key);
GType plist_string_get_type (void);
GtkMateThemeSetting* gtk_mate_theme_setting_create_from_plist (PListDict* dict);
GeeArrayList* gtk_mate_matcher_compile (const char* selector_string);
void gtk_mate_theme_setting_compile_scope_matchers (GtkMateThemeSetting* self);
GType onig_rx_get_type (void);
GType onig_match_get_type (void);
gboolean gtk_mate_matcher_test_match_re (OnigRx* positive_selector_regex, GeeArrayList* negative_selector_regex, const char* scope_string, OnigMatch** match);
gboolean gtk_mate_theme_setting_match (GtkMateThemeSetting* self, const char* scope, OnigMatch** match);
GtkMateThemeSetting* gtk_mate_theme_setting_new (void);
static gpointer gtk_mate_theme_setting_parent_class = NULL;
static void gtk_mate_theme_setting_finalize (GObject* obj);
GType gtk_mate_theme_get_type (void);
enum  {
	GTK_MATE_THEME_DUMMY_PROPERTY
};
extern GeeArrayList* gtk_mate_theme__themes;
GeeArrayList* gtk_mate_theme__themes = NULL;
void gtk_mate_load_themes (void);
GeeArrayList* gtk_mate_theme_themes (void);
GtkMateTheme* gtk_mate_theme_new (void);
GtkMateTheme* gtk_mate_theme_construct (GType object_type);
GType plist_array_get_type (void);
char** plist_dict_keys (PListDict* self, int* result_length1);
GtkMateTheme* gtk_mate_theme_create_from_plist (PListDict* dict);
void gtk_mate_theme_init_for_use (GtkMateTheme* self);
char* gtk_mate_textmate_share_dir (void);
GeeArrayList* gtk_mate_theme_theme_filenames (void);
GType gtk_mate_scope_get_type (void);
char* gtk_mate_scope_hierarchy_names (GtkMateScope* self, gboolean inner);
gint gtk_mate_matcher_compare_match (const char* scope_string, OnigMatch* m1, OnigMatch* m2);
GtkMateThemeSetting* gtk_mate_theme_settings_for_scope (GtkMateTheme* self, GtkMateScope* scope, gboolean inner, GtkMateThemeSetting* exclude_setting);
GtkMateTheme* gtk_mate_theme_new (void);
static gpointer gtk_mate_theme_parent_class = NULL;
static void gtk_mate_theme_finalize (GObject* obj);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);



GtkMateThemeSetting* gtk_mate_theme_setting_create_from_plist (PListDict* dict) {
	GtkMateThemeSetting* tsetting;
	PListNode* nm;
	PListNode* _tmp2_;
	GeeHashMap* _tmp5_;
	PListDict* pd;
	GtkMateThemeSetting* _tmp9_;
	g_return_val_if_fail (dict != NULL, NULL);
	tsetting = g_object_ref_sink (gtk_mate_theme_setting_new ());
	nm = plist_dict_get (dict, "name");
	if (nm != NULL) {
		char* _tmp1_;
		const char* _tmp0_;
		_tmp1_ = NULL;
		_tmp0_ = NULL;
		tsetting->name = (_tmp1_ = (_tmp0_ = PLIST_STRING (nm)->str, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), tsetting->name = (g_free (tsetting->name), NULL), _tmp1_);
	}
	_tmp2_ = NULL;
	nm = (_tmp2_ = plist_dict_get (dict, "scope"), (nm == NULL) ? NULL : (nm = (g_object_unref (nm), NULL)), _tmp2_);
	if (nm != NULL) {
		char* _tmp4_;
		const char* _tmp3_;
		_tmp4_ = NULL;
		_tmp3_ = NULL;
		tsetting->selector = (_tmp4_ = (_tmp3_ = PLIST_STRING (nm)->str, (_tmp3_ == NULL) ? NULL : g_strdup (_tmp3_)), tsetting->selector = (g_free (tsetting->selector), NULL), _tmp4_);
	}
	_tmp5_ = NULL;
	tsetting->settings = (_tmp5_ = gee_hash_map_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, g_str_hash, g_str_equal, g_direct_equal), (tsetting->settings == NULL) ? NULL : (tsetting->settings = (g_object_unref (tsetting->settings), NULL)), _tmp5_);
	pd = PLIST_DICT (plist_dict_get (dict, "settings"));
	{
		GeeSet* _tmp6_;
		GeeIterator* _tmp7_;
		GeeIterator* _key_it;
		_tmp6_ = NULL;
		_tmp7_ = NULL;
		_key_it = (_tmp7_ = gee_iterable_iterator ((GeeIterable*) (_tmp6_ = gee_map_get_keys ((GeeMap*) pd->map))), (_tmp6_ == NULL) ? NULL : (_tmp6_ = (g_object_unref (_tmp6_), NULL)), _tmp7_);
		while (gee_iterator_next (_key_it)) {
			char* key;
			PListString* _tmp8_;
			key = (char*) gee_iterator_get (_key_it);
			_tmp8_ = NULL;
			gee_map_set ((GeeMap*) tsetting->settings, key, (_tmp8_ = PLIST_STRING ((PListNode*) gee_map_get ((GeeMap*) pd->map, key)))->str);
			(_tmp8_ == NULL) ? NULL : (_tmp8_ = (g_object_unref (_tmp8_), NULL));
			key = (g_free (key), NULL);
		}
		(_key_it == NULL) ? NULL : (_key_it = (g_object_unref (_key_it), NULL));
	}
	_tmp9_ = NULL;
	return (_tmp9_ = tsetting, (nm == NULL) ? NULL : (nm = (g_object_unref (nm), NULL)), (pd == NULL) ? NULL : (pd = (g_object_unref (pd), NULL)), _tmp9_);
}


void gtk_mate_theme_setting_compile_scope_matchers (GtkMateThemeSetting* self) {
	GeeArrayList* _tmp0_;
	g_return_if_fail (self != NULL);
	/*stdout.printf("  compiling '%s'\n", selector);*/
	_tmp0_ = NULL;
	self->matchers = (_tmp0_ = gtk_mate_matcher_compile (self->selector), (self->matchers == NULL) ? NULL : (self->matchers = (g_object_unref (self->matchers), NULL)), _tmp0_);
}


gboolean gtk_mate_theme_setting_match (GtkMateThemeSetting* self, const char* scope, OnigMatch** match) {
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (scope != NULL, FALSE);
	*match = NULL;
	if (self->matchers == NULL) {
		gtk_mate_theme_setting_compile_scope_matchers (self);
	}
	{
		GeeIterator* _matcher_it;
		_matcher_it = gee_iterable_iterator ((GeeIterable*) self->matchers);
		while (gee_iterator_next (_matcher_it)) {
			GtkMateMatcher* matcher;
			OnigMatch* _tmp2_;
			gboolean _tmp1_;
			OnigMatch* _tmp0_;
			matcher = (GtkMateMatcher*) gee_iterator_get (_matcher_it);
			_tmp2_ = NULL;
			_tmp0_ = NULL;
			if ((_tmp1_ = gtk_mate_matcher_test_match_re (matcher->pos_rx, matcher->neg_rxs, scope, &_tmp0_), (*match) = (_tmp2_ = _tmp0_, ((*match) == NULL) ? NULL : ((*match) = (g_object_unref ((*match)), NULL)), _tmp2_), _tmp1_)) {
				gboolean _tmp3_;
				return (_tmp3_ = TRUE, (matcher == NULL) ? NULL : (matcher = (g_object_unref (matcher), NULL)), (_matcher_it == NULL) ? NULL : (_matcher_it = (g_object_unref (_matcher_it), NULL)), _tmp3_);
			}
			(matcher == NULL) ? NULL : (matcher = (g_object_unref (matcher), NULL));
		}
		(_matcher_it == NULL) ? NULL : (_matcher_it = (g_object_unref (_matcher_it), NULL));
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


GeeArrayList* gtk_mate_theme_themes (void) {
	GeeArrayList* _tmp0_;
	if (gtk_mate_theme__themes == NULL) {
		gtk_mate_load_themes ();
	}
	_tmp0_ = NULL;
	return (_tmp0_ = gtk_mate_theme__themes, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
}


GtkMateTheme* gtk_mate_theme_create_from_plist (PListDict* dict) {
	GtkMateTheme* theme;
	PListNode* nm;
	PListNode* _tmp2_;
	GeeHashMap* _tmp5_;
	GeeArrayList* _tmp6_;
	PListArray* na;
	GtkMateTheme* _tmp14_;
	g_return_val_if_fail (dict != NULL, NULL);
	theme = g_object_ref_sink (gtk_mate_theme_new ());
	theme->is_initialized = FALSE;
	nm = plist_dict_get (dict, "name");
	if (nm != NULL) {
		char* _tmp1_;
		const char* _tmp0_;
		_tmp1_ = NULL;
		_tmp0_ = NULL;
		theme->name = (_tmp1_ = (_tmp0_ = PLIST_STRING (nm)->str, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), theme->name = (g_free (theme->name), NULL), _tmp1_);
	}
	_tmp2_ = NULL;
	nm = (_tmp2_ = plist_dict_get (dict, "author"), (nm == NULL) ? NULL : (nm = (g_object_unref (nm), NULL)), _tmp2_);
	if (nm != NULL) {
		char* _tmp4_;
		const char* _tmp3_;
		_tmp4_ = NULL;
		_tmp3_ = NULL;
		theme->author = (_tmp4_ = (_tmp3_ = PLIST_STRING (nm)->str, (_tmp3_ == NULL) ? NULL : g_strdup (_tmp3_)), theme->author = (g_free (theme->author), NULL), _tmp4_);
	}
	_tmp5_ = NULL;
	theme->global_settings = (_tmp5_ = gee_hash_map_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, g_str_hash, g_str_equal, g_direct_equal), (theme->global_settings == NULL) ? NULL : (theme->global_settings = (g_object_unref (theme->global_settings), NULL)), _tmp5_);
	_tmp6_ = NULL;
	theme->settings = (_tmp6_ = gee_array_list_new (GTK_MATE_TYPE_THEME_SETTING, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (theme->settings == NULL) ? NULL : (theme->settings = (g_object_unref (theme->settings), NULL)), _tmp6_);
	na = PLIST_ARRAY (plist_dict_get (dict, "settings"));
	{
		GeeIterator* _nn_it;
		_nn_it = gee_iterable_iterator ((GeeIterable*) na->array);
		while (gee_iterator_next (_nn_it)) {
			PListNode* nn;
			PListDict* _tmp7_;
			PListDict* nd;
			PListNode* _tmp8_;
			gboolean _tmp9_;
			nn = (PListNode*) gee_iterator_get (_nn_it);
			_tmp7_ = NULL;
			nd = (_tmp7_ = PLIST_DICT (nn), (_tmp7_ == NULL) ? NULL : g_object_ref (_tmp7_));
			_tmp8_ = NULL;
			if ((_tmp9_ = (_tmp8_ = plist_dict_get (nd, "scope")) == NULL, (_tmp8_ == NULL) ? NULL : (_tmp8_ = (g_object_unref (_tmp8_), NULL)), _tmp9_)) {
				PListDict* gsd;
				gsd = PLIST_DICT (plist_dict_get (nd, "settings"));
				{
					gint _tmp10_;
					char** key_collection;
					int key_collection_length1;
					int key_it;
					key_collection = plist_dict_keys (gsd, &_tmp10_);
					key_collection_length1 = _tmp10_;
					for (key_it = 0; key_it < _tmp10_; key_it = key_it + 1) {
						const char* _tmp12_;
						char* key;
						_tmp12_ = NULL;
						key = (_tmp12_ = key_collection[key_it], (_tmp12_ == NULL) ? NULL : g_strdup (_tmp12_));
						{
							PListString* _tmp11_;
							_tmp11_ = NULL;
							gee_map_set ((GeeMap*) theme->global_settings, key, (_tmp11_ = PLIST_STRING (plist_dict_get (gsd, key)))->str);
							(_tmp11_ == NULL) ? NULL : (_tmp11_ = (g_object_unref (_tmp11_), NULL));
							key = (g_free (key), NULL);
						}
					}
					key_collection = (_vala_array_free (key_collection, key_collection_length1, (GDestroyNotify) g_free), NULL);
				}
				(gsd == NULL) ? NULL : (gsd = (g_object_unref (gsd), NULL));
			} else {
				GtkMateThemeSetting* _tmp13_;
				_tmp13_ = NULL;
				gee_collection_add ((GeeCollection*) theme->settings, _tmp13_ = gtk_mate_theme_setting_create_from_plist (nd));
				(_tmp13_ == NULL) ? NULL : (_tmp13_ = (g_object_unref (_tmp13_), NULL));
			}
			(nn == NULL) ? NULL : (nn = (g_object_unref (nn), NULL));
			(nd == NULL) ? NULL : (nd = (g_object_unref (nd), NULL));
		}
		(_nn_it == NULL) ? NULL : (_nn_it = (g_object_unref (_nn_it), NULL));
	}
	_tmp14_ = NULL;
	return (_tmp14_ = theme, (nm == NULL) ? NULL : (nm = (g_object_unref (nm), NULL)), (na == NULL) ? NULL : (na = (g_object_unref (na), NULL)), _tmp14_);
}


void gtk_mate_theme_init_for_use (GtkMateTheme* self) {
	GeeHashMap* _tmp0_;
	g_return_if_fail (self != NULL);
	if (self->is_initialized) {
		return;
	}
	self->is_initialized = TRUE;
	/* stdout.printf("initializing theme for use: %s\n", name);*/
	_tmp0_ = NULL;
	self->cached_setting_for_scopes = (_tmp0_ = gee_hash_map_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, GTK_MATE_TYPE_THEME_SETTING, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_str_hash, g_str_equal, g_direct_equal), (self->cached_setting_for_scopes == NULL) ? NULL : (self->cached_setting_for_scopes = (g_object_unref (self->cached_setting_for_scopes), NULL)), _tmp0_);
	{
		GeeIterator* _setting_it;
		_setting_it = gee_iterable_iterator ((GeeIterable*) self->settings);
		while (gee_iterator_next (_setting_it)) {
			GtkMateThemeSetting* setting;
			setting = (GtkMateThemeSetting*) gee_iterator_get (_setting_it);
			gtk_mate_theme_setting_compile_scope_matchers (setting);
			(setting == NULL) ? NULL : (setting = (g_object_unref (setting), NULL));
		}
		(_setting_it == NULL) ? NULL : (_setting_it = (g_object_unref (_setting_it), NULL));
	}
}


GeeArrayList* gtk_mate_theme_theme_filenames (void) {
	GError * _inner_error_;
	GeeArrayList* names;
	char* share_dir;
	char* name;
	GeeArrayList* _tmp8_;
	_inner_error_ = NULL;
	names = gee_array_list_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, g_direct_equal);
	share_dir = gtk_mate_textmate_share_dir ();
	name = NULL;
	{
		char* _tmp0_;
		GDir* _tmp1_;
		GDir* d;
		char* _tmp3_;
		const char* _tmp2_;
		GeeArrayList* _tmp6_;
		_tmp0_ = NULL;
		_tmp1_ = NULL;
		d = (_tmp1_ = g_dir_open (_tmp0_ = g_strconcat (share_dir, "/Themes", NULL), 0, &_inner_error_), _tmp0_ = (g_free (_tmp0_), NULL), _tmp1_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_FILE_ERROR) {
				goto __catch6_g_file_error;
			}
			goto __finally6;
		}
		_tmp3_ = NULL;
		_tmp2_ = NULL;
		while ((name = (_tmp3_ = (_tmp2_ = g_dir_read_name (d), (_tmp2_ == NULL) ? NULL : g_strdup (_tmp2_)), name = (g_free (name), NULL), _tmp3_)) != NULL) {
			if (g_str_has_suffix (name, ".tmTheme")) {
				char* _tmp5_;
				char* _tmp4_;
				_tmp5_ = NULL;
				_tmp4_ = NULL;
				gee_collection_add ((GeeCollection*) names, _tmp5_ = g_strconcat (_tmp4_ = g_strconcat (share_dir, "/Themes/", NULL), name, NULL));
				_tmp5_ = (g_free (_tmp5_), NULL);
				_tmp4_ = (g_free (_tmp4_), NULL);
			}
		}
		_tmp6_ = NULL;
		return (_tmp6_ = names, (d == NULL) ? NULL : (d = (g_dir_close (d), NULL)), share_dir = (g_free (share_dir), NULL), name = (g_free (name), NULL), _tmp6_);
	}
	goto __finally6;
	__catch6_g_file_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			char* _tmp7_;
			_tmp7_ = NULL;
			fprintf (stdout, "couldn't open: %s\n", _tmp7_ = g_strconcat (share_dir, "/Bundles", NULL));
			_tmp7_ = (g_free (_tmp7_), NULL);
			(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
		}
	}
	__finally6:
	if (_inner_error_ != NULL) {
		(names == NULL) ? NULL : (names = (g_object_unref (names), NULL));
		share_dir = (g_free (share_dir), NULL);
		name = (g_free (name), NULL);
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	_tmp8_ = NULL;
	return (_tmp8_ = NULL, (names == NULL) ? NULL : (names = (g_object_unref (names), NULL)), share_dir = (g_free (share_dir), NULL), name = (g_free (name), NULL), _tmp8_);
}


/* TODO make this return multiple themes if they are identical
 (see 13.5 of Textmate manual)*/
GtkMateThemeSetting* gtk_mate_theme_settings_for_scope (GtkMateTheme* self, GtkMateScope* scope, gboolean inner, GtkMateThemeSetting* exclude_setting) {
	char* scope_name;
	GtkMateThemeSetting* cached;
	OnigMatch* current_m;
	OnigMatch* m;
	GtkMateThemeSetting* current;
	GtkMateThemeSetting* _tmp14_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (scope != NULL, NULL);
	scope_name = gtk_mate_scope_hierarchy_names (scope, inner);
	/*stdout.printf("  finding settings for '%s'\n", scope_name);*/
	cached = NULL;
	if (gee_map_contains ((GeeMap*) self->cached_setting_for_scopes, scope_name)) {
		GtkMateThemeSetting* _tmp0_;
		GtkMateThemeSetting* _tmp1_;
		_tmp0_ = NULL;
		cached = (_tmp0_ = (GtkMateThemeSetting*) gee_map_get ((GeeMap*) self->cached_setting_for_scopes, scope_name), (cached == NULL) ? NULL : (cached = (g_object_unref (cached), NULL)), _tmp0_);
		_tmp1_ = NULL;
		return (_tmp1_ = cached, scope_name = (g_free (scope_name), NULL), _tmp1_);
	}
	current_m = NULL;
	m = NULL;
	current = NULL;
	{
		GeeIterator* _setting_it;
		_setting_it = gee_iterable_iterator ((GeeIterable*) self->settings);
		while (gee_iterator_next (_setting_it)) {
			GtkMateThemeSetting* setting;
			gboolean _tmp2_;
			setting = (GtkMateThemeSetting*) gee_iterator_get (_setting_it);
			_tmp2_ = FALSE;
			if (setting == exclude_setting) {
				_tmp2_ = exclude_setting != NULL;
			} else {
				_tmp2_ = FALSE;
			}
			if (_tmp2_) {
			} else {
				OnigMatch* _tmp5_;
				gboolean _tmp4_;
				OnigMatch* _tmp3_;
				/*stdout.printf("    setting '%s' excluded due to parent\n", exclude_setting.name);*/
				_tmp5_ = NULL;
				_tmp3_ = NULL;
				if ((_tmp4_ = gtk_mate_theme_setting_match (setting, scope_name, &_tmp3_), m = (_tmp5_ = _tmp3_, (m == NULL) ? NULL : (m = (g_object_unref (m), NULL)), _tmp5_), _tmp4_)) {
					/*stdout.printf("    setting '%s' matches selector '%s'\n", setting.name, setting.selector); */
					if (current == NULL) {
						GtkMateThemeSetting* _tmp7_;
						GtkMateThemeSetting* _tmp6_;
						OnigMatch* _tmp9_;
						OnigMatch* _tmp8_;
						_tmp7_ = NULL;
						_tmp6_ = NULL;
						current = (_tmp7_ = (_tmp6_ = setting, (_tmp6_ == NULL) ? NULL : g_object_ref (_tmp6_)), (current == NULL) ? NULL : (current = (g_object_unref (current), NULL)), _tmp7_);
						_tmp9_ = NULL;
						_tmp8_ = NULL;
						current_m = (_tmp9_ = (_tmp8_ = m, (_tmp8_ == NULL) ? NULL : g_object_ref (_tmp8_)), (current_m == NULL) ? NULL : (current_m = (g_object_unref (current_m), NULL)), _tmp9_);
					} else {
						if (gtk_mate_matcher_compare_match (scope_name, current_m, m) < 0) {
							GtkMateThemeSetting* _tmp11_;
							GtkMateThemeSetting* _tmp10_;
							OnigMatch* _tmp13_;
							OnigMatch* _tmp12_;
							_tmp11_ = NULL;
							_tmp10_ = NULL;
							current = (_tmp11_ = (_tmp10_ = setting, (_tmp10_ == NULL) ? NULL : g_object_ref (_tmp10_)), (current == NULL) ? NULL : (current = (g_object_unref (current), NULL)), _tmp11_);
							_tmp13_ = NULL;
							_tmp12_ = NULL;
							current_m = (_tmp13_ = (_tmp12_ = m, (_tmp12_ == NULL) ? NULL : g_object_ref (_tmp12_)), (current_m == NULL) ? NULL : (current_m = (g_object_unref (current_m), NULL)), _tmp13_);
						}
					}
				}
			}
			(setting == NULL) ? NULL : (setting = (g_object_unref (setting), NULL));
		}
		(_setting_it == NULL) ? NULL : (_setting_it = (g_object_unref (_setting_it), NULL));
	}
	/*if (current == null) {
	stdout.printf("none match\n");
	}
	else {
	stdout.printf("    best: '%s'\n", current.name);
	}*/
	gee_map_set ((GeeMap*) self->cached_setting_for_scopes, scope_name, current);
	_tmp14_ = NULL;
	return (_tmp14_ = current, scope_name = (g_free (scope_name), NULL), (cached == NULL) ? NULL : (cached = (g_object_unref (cached), NULL)), (current_m == NULL) ? NULL : (current_m = (g_object_unref (current_m), NULL)), (m == NULL) ? NULL : (m = (g_object_unref (m), NULL)), _tmp14_);
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




