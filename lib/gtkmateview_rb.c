#include "ruby.h"
#include "rbgtk.h"
#include "parser.h"
#include "theme.h"
#include "pattern.h"
#include "scope.h"
#include "grammar.h"
#include "view.h"
#include "buffer.h"
#include "bundle.h"
#include "gtkmateview.h"
#include "onig_wrap.h"
#include "plist.h"
static VALUE rb_vala_error, rbc_gtk;

/****  Gtk wrapper *****/

#define _GTK_SELF(s) GTK(RVAL2GOBJ(s))
static VALUE rbc_gtk;

/****  Gtk.Mate wrapper *****/

#define _GTK_MATE_SELF(s) GTK_MATE(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate;

/****  Gtk.Mate.ThemeSetting wrapper *****/

#define _GTK_MATE_THEME_SETTING_SELF(s) GTK_MATE_THEME_SETTING(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_theme_setting;

/****  Gtk.Mate.Theme wrapper *****/

#define _GTK_MATE_THEME_SELF(s) GTK_MATE_THEME(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_theme;
GeeArrayList* gtk_mate_theme_themes;

/****  Gtk.Mate.Pattern wrapper *****/

#define _GTK_MATE_PATTERN_SELF(s) GTK_MATE_PATTERN(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_pattern;
GeeArrayList* gtk_mate_pattern_all_patterns;

/****  Gtk.Mate.SinglePattern wrapper *****/

#define _GTK_MATE_SINGLE_PATTERN_SELF(s) GTK_MATE_SINGLE_PATTERN(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_single_pattern;

/****  Gtk.Mate.DoublePattern wrapper *****/

#define _GTK_MATE_DOUBLE_PATTERN_SELF(s) GTK_MATE_DOUBLE_PATTERN(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_double_pattern;

/****  Gtk.Mate.IncludePattern wrapper *****/

#define _GTK_MATE_INCLUDE_PATTERN_SELF(s) GTK_MATE_INCLUDE_PATTERN(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_include_pattern;

/****  Gtk.Mate.Scope wrapper *****/

#define _GTK_MATE_SCOPE_SELF(s) GTK_MATE_SCOPE(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_scope;

/****  Gtk.Mate.Grammar wrapper *****/

#define _GTK_MATE_GRAMMAR_SELF(s) GTK_MATE_GRAMMAR(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_grammar;

/****  Gtk.Mate.View wrapper *****/

#define _GTK_MATE_VIEW_SELF(s) GTK_MATE_VIEW(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_view;

/****  Gtk.Mate.Buffer wrapper *****/

#define _GTK_MATE_BUFFER_SELF(s) GTK_MATE_BUFFER(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_buffer;
GeeArrayList* gtk_mate_buffer_bundles;
GeeArrayList* gtk_mate_buffer_themes;

/****  Gtk.Mate.Parser wrapper *****/

#define _GTK_MATE_PARSER_SELF(s) GTK_MATE_PARSER(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_parser;
GtkMateParser* gtk_mate_parser_current;

/****  Gtk.Mate.Bundle wrapper *****/

#define _GTK_MATE_BUNDLE_SELF(s) GTK_MATE_BUNDLE(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_bundle;

/****  Oniguruma wrapper *****/

#define _ONIGURUMA_SELF(s) ONIGURUMA(RVAL2GOBJ(s))
static VALUE rbc_oniguruma;

/****  Oniguruma.OnigError wrapper *****/

#define _ONIGURUMA_ONIG_ERROR_SELF(s) ONIGURUMA_ONIG_ERROR(RVAL2GOBJ(s))
static VALUE rbc_oniguruma_onig_error;

/****  Oniguruma.Match wrapper *****/

#define _ONIGURUMA_MATCH_SELF(s) ONIGURUMA_MATCH(RVAL2GOBJ(s))
static VALUE rbc_oniguruma_match;

/****  Oniguruma.Regex wrapper *****/

#define _ONIGURUMA_REGEX_SELF(s) ONIGURUMA_REGEX(RVAL2GOBJ(s))
static VALUE rbc_oniguruma_regex;

/****  PList wrapper *****/

#define _PLIST_SELF(s) PLIST(RVAL2GOBJ(s))
static VALUE rbc_plist;

/****  PList.Node wrapper *****/

#define _PLIST_NODE_SELF(s) PLIST_NODE(RVAL2GOBJ(s))
static VALUE rbc_plist_node;

/****  PList.String wrapper *****/

#define _PLIST_STRING_SELF(s) PLIST_STRING(RVAL2GOBJ(s))
static VALUE rbc_plist_string;

/****  PList.Array wrapper *****/

#define _PLIST_ARRAY_SELF(s) PLIST_ARRAY(RVAL2GOBJ(s))
static VALUE rbc_plist_array;

/****  PList.Dict wrapper *****/

#define _PLIST_DICT_SELF(s) PLIST_DICT(RVAL2GOBJ(s))
static VALUE rbc_plist_dict;

/****  Gtk methods *****/


/****  Gtk.Mate methods *****/

static VALUE rb_gtk_mate_load_bundles(VALUE self) {
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_load_bundles();
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_load_themes(VALUE self) {
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gtk_mate_load_themes();
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_bundle_dirs(VALUE self) {
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    GeeArrayList* _c_return;
    _c_return = gtk_mate_bundle_dirs();
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val1;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val1 = 0; it_val1 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val1 = it_val1 + 1) {
            char * i_val2;
            i_val2 = (char *) (gee_list_get (GEE_LIST (_c_return), it_val1));
            VALUE rb_ival2;
                  if (i_val2 == NULL) {
        rb_ival2 = Qnil;
      }
      else {
        rb_ival2 = rb_str_new2(i_val2);
      }

            rb_ary_store (_rb_return, it_val1, rb_ival2);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_textmate_share_dir(VALUE self) {
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    char * _c_return;
    _c_return = gtk_mate_textmate_share_dir();
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
              if (_c_return == NULL) {
        _rb_return = Qnil;
      }
      else {
        _rb_return = rb_str_new2(_c_return);
      }

    }
    return _rb_return;
}


/****  Gtk.Mate.ThemeSetting methods *****/


static VALUE gtk_mate_theme_setting_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_theme_setting_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_theme_setting_get_name(VALUE self) {
    GtkMateThemeSetting* gtk_mate_theme_setting = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_theme_setting->name; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == NULL) {
        _rb_return = Qnil;
      }
      else {
        _rb_return = rb_str_new2(_c_return);
      }

    return _rb_return;
}

static VALUE rb_gtk_mate_theme_setting_set_name(VALUE self, VALUE name) {
    GtkMateThemeSetting* gtk_mate_theme_setting = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(name) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_name;
    _c_name = g_strdup(STR2CSTR(name));
    // ValaMemberSet#body
    gtk_mate_theme_setting->name = _c_name;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_theme_setting_get_scope(VALUE self) {
    GtkMateThemeSetting* gtk_mate_theme_setting = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_theme_setting->scope; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == NULL) {
        _rb_return = Qnil;
      }
      else {
        _rb_return = rb_str_new2(_c_return);
      }

    return _rb_return;
}

static VALUE rb_gtk_mate_theme_setting_set_scope(VALUE self, VALUE scope) {
    GtkMateThemeSetting* gtk_mate_theme_setting = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(scope) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_scope;
    _c_scope = g_strdup(STR2CSTR(scope));
    // ValaMemberSet#body
    gtk_mate_theme_setting->scope = _c_scope;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_theme_setting_get_settings(VALUE self) {
    GtkMateThemeSetting* gtk_mate_theme_setting = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeHashMap* _c_return = gtk_mate_theme_setting->settings; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // HashMap#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        _rb_return = rb_hash_new();
        GeeSet* s_collection;
        GeeIterator* s_it;
        s_collection = gee_map_get_keys (GEE_MAP (_c_return));
        s_it = gee_iterable_iterator (GEE_ITERABLE (s_collection));
        while (gee_iterator_next (s_it)) {
            char * s;
            s = ((char *) (gee_iterator_get (s_it)));
            {
                char * v;
                v = (char *) ((char *) (gee_map_get (GEE_MAP (_c_return), s)));
                VALUE rb_s;
                      if (s == NULL) {
        rb_s = Qnil;
      }
      else {
        rb_s = rb_str_new2(s);
      }

                VALUE rb_v;
                      if (v == NULL) {
        rb_v = Qnil;
      }
      else {
        rb_v = rb_str_new2(v);
      }

                rb_hash_aset(_rb_return, rb_s, rb_v);
//                s = (g_free (s), NULL);
            }
        }
        (s_it == NULL ? NULL : (s_it = (g_object_unref (s_it), NULL)));
        (s_collection == NULL ? NULL : (s_collection = (g_object_unref (s_collection), NULL)));
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_theme_setting_set_settings(VALUE self, VALUE settings) {
    GtkMateThemeSetting* gtk_mate_theme_setting = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(settings) != T_HASH) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a hash");
    }
    // Method#argument_type_conversions
    GeeHashMap* _c_settings;
        // HashMap#ruby_to_c(:before, "settings", "_c_settings")
    _c_settings = gee_hash_map_new (G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, g_str_hash, g_str_equal, g_direct_equal);
    VALUE rb_keys = rb_funcall(settings, rb_intern("keys"), 0);
    int len_val3 = RARRAY_LEN(rb_keys);
    {
        gint i;
        i = 0;
        for (; i < len_val3; i++) {
            VALUE _rb_key = rb_ary_entry(rb_keys, (long) i);
            VALUE _rb_value = rb_hash_aref(settings, _rb_key);
            char * _c__rb_key;
            _c__rb_key = g_strdup(STR2CSTR(_rb_key));
            char * _c__rb_value;
            _c__rb_value = g_strdup(STR2CSTR(_rb_value));
            gee_map_set (GEE_MAP (_c_settings), _c__rb_key,  (_c__rb_value));
        }
    }

    // ValaMemberSet#body
    gtk_mate_theme_setting->settings = _c_settings;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_theme_setting_create_from_plist(VALUE self, VALUE dict) {
    // Method#type_checks
    // Method#argument_type_conversions
    PListDict* _c_dict;
    _c_dict = _PLIST_DICT_SELF(dict);
    // Method#body
    
    GtkMateThemeSetting* _c_return;
    _c_return = gtk_mate_theme_setting_create_from_plist(_c_dict);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}


/****  Gtk.Mate.Theme methods *****/


static VALUE gtk_mate_theme_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_theme_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_theme_get_themes(VALUE self) {
    // Method#type_checks
    // Method#argument_type_conversions
    // StaticMemberGet#body
    GeeArrayList* _c_return = gtk_mate_theme_themes;
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val4;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val4 = 0; it_val4 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val4 = it_val4 + 1) {
            GtkMateTheme* i_val5;
            i_val5 =  (gee_list_get (GEE_LIST (_c_return), it_val4));
            VALUE rb_ival5;
            rb_ival5 = GOBJ2RVAL(i_val5);
            rb_ary_store (_rb_return, it_val4, rb_ival5);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_theme_set_themes(VALUE self, VALUE themes) {
    // Method#type_checks
    if (TYPE(themes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_themes;
        // ArrayListType#ruby_to_c(:before, "themes", "_c_themes")
    int len_val6 = RARRAY_LEN(themes);
    _c_themes = gee_array_list_new (GTK_MATE_TYPE_THEME, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val6; i++) {
            VALUE _rb_el = rb_ary_entry(themes, (long) i);
            GtkMateTheme* _c_el = _GTK_MATE_THEME_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_themes), (_c_el));
        }
    }

    // StaticMemberSet#body
    gtk_mate_theme_themes = _c_themes; 
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_theme_get_author(VALUE self) {
    GtkMateTheme* gtk_mate_theme = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_theme->author; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == NULL) {
        _rb_return = Qnil;
      }
      else {
        _rb_return = rb_str_new2(_c_return);
      }

    return _rb_return;
}

static VALUE rb_gtk_mate_theme_set_author(VALUE self, VALUE author) {
    GtkMateTheme* gtk_mate_theme = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(author) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_author;
    _c_author = g_strdup(STR2CSTR(author));
    // ValaMemberSet#body
    gtk_mate_theme->author = _c_author;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_theme_get_name(VALUE self) {
    GtkMateTheme* gtk_mate_theme = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_theme->name; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == NULL) {
        _rb_return = Qnil;
      }
      else {
        _rb_return = rb_str_new2(_c_return);
      }

    return _rb_return;
}

static VALUE rb_gtk_mate_theme_set_name(VALUE self, VALUE name) {
    GtkMateTheme* gtk_mate_theme = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(name) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_name;
    _c_name = g_strdup(STR2CSTR(name));
    // ValaMemberSet#body
    gtk_mate_theme->name = _c_name;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_theme_get_global_settings(VALUE self) {
    GtkMateTheme* gtk_mate_theme = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeHashMap* _c_return = gtk_mate_theme->global_settings; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // HashMap#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        _rb_return = rb_hash_new();
        GeeSet* s_collection;
        GeeIterator* s_it;
        s_collection = gee_map_get_keys (GEE_MAP (_c_return));
        s_it = gee_iterable_iterator (GEE_ITERABLE (s_collection));
        while (gee_iterator_next (s_it)) {
            char * s;
            s = ((char *) (gee_iterator_get (s_it)));
            {
                char * v;
                v = (char *) ((char *) (gee_map_get (GEE_MAP (_c_return), s)));
                VALUE rb_s;
                      if (s == NULL) {
        rb_s = Qnil;
      }
      else {
        rb_s = rb_str_new2(s);
      }

                VALUE rb_v;
                      if (v == NULL) {
        rb_v = Qnil;
      }
      else {
        rb_v = rb_str_new2(v);
      }

                rb_hash_aset(_rb_return, rb_s, rb_v);
//                s = (g_free (s), NULL);
            }
        }
        (s_it == NULL ? NULL : (s_it = (g_object_unref (s_it), NULL)));
        (s_collection == NULL ? NULL : (s_collection = (g_object_unref (s_collection), NULL)));
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_theme_set_global_settings(VALUE self, VALUE global_settings) {
    GtkMateTheme* gtk_mate_theme = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(global_settings) != T_HASH) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a hash");
    }
    // Method#argument_type_conversions
    GeeHashMap* _c_global_settings;
        // HashMap#ruby_to_c(:before, "global_settings", "_c_global_settings")
    _c_global_settings = gee_hash_map_new (G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, g_str_hash, g_str_equal, g_direct_equal);
    VALUE rb_keys = rb_funcall(global_settings, rb_intern("keys"), 0);
    int len_val7 = RARRAY_LEN(rb_keys);
    {
        gint i;
        i = 0;
        for (; i < len_val7; i++) {
            VALUE _rb_key = rb_ary_entry(rb_keys, (long) i);
            VALUE _rb_value = rb_hash_aref(global_settings, _rb_key);
            char * _c__rb_key;
            _c__rb_key = g_strdup(STR2CSTR(_rb_key));
            char * _c__rb_value;
            _c__rb_value = g_strdup(STR2CSTR(_rb_value));
            gee_map_set (GEE_MAP (_c_global_settings), _c__rb_key,  (_c__rb_value));
        }
    }

    // ValaMemberSet#body
    gtk_mate_theme->global_settings = _c_global_settings;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_theme_get_settings(VALUE self) {
    GtkMateTheme* gtk_mate_theme = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeArrayList* _c_return = gtk_mate_theme->settings; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val8;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val8 = 0; it_val8 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val8 = it_val8 + 1) {
            GtkMateThemeSetting* i_val9;
            i_val9 =  (gee_list_get (GEE_LIST (_c_return), it_val8));
            VALUE rb_ival9;
            rb_ival9 = GOBJ2RVAL(i_val9);
            rb_ary_store (_rb_return, it_val8, rb_ival9);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_theme_set_settings(VALUE self, VALUE settings) {
    GtkMateTheme* gtk_mate_theme = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(settings) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_settings;
        // ArrayListType#ruby_to_c(:before, "settings", "_c_settings")
    int len_val10 = RARRAY_LEN(settings);
    _c_settings = gee_array_list_new (GTK_MATE_TYPE_THEME_SETTING, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val10; i++) {
            VALUE _rb_el = rb_ary_entry(settings, (long) i);
            GtkMateThemeSetting* _c_el = _GTK_MATE_THEME_SETTING_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_settings), (_c_el));
        }
    }

    // ValaMemberSet#body
    gtk_mate_theme->settings = _c_settings;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_theme_create_from_plist(VALUE self, VALUE dict) {
    // Method#type_checks
    // Method#argument_type_conversions
    PListDict* _c_dict;
    _c_dict = _PLIST_DICT_SELF(dict);
    // Method#body
    
    GtkMateTheme* _c_return;
    _c_return = gtk_mate_theme_create_from_plist(_c_dict);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_theme_theme_filenames(VALUE self) {
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    GeeArrayList* _c_return;
    _c_return = gtk_mate_theme_theme_filenames();
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val11;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val11 = 0; it_val11 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val11 = it_val11 + 1) {
            char * i_val12;
            i_val12 = (char *) (gee_list_get (GEE_LIST (_c_return), it_val11));
            VALUE rb_ival12;
                  if (i_val12 == NULL) {
        rb_ival12 = Qnil;
      }
      else {
        rb_ival12 = rb_str_new2(i_val12);
      }

            rb_ary_store (_rb_return, it_val11, rb_ival12);
        }
    }

    return _rb_return;
}


/****  Gtk.Mate.Pattern methods *****/


static VALUE gtk_mate_pattern_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_pattern_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_pattern_get_name(VALUE self) {
    GtkMatePattern* gtk_mate_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_pattern->name; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == NULL) {
        _rb_return = Qnil;
      }
      else {
        _rb_return = rb_str_new2(_c_return);
      }

    return _rb_return;
}

static VALUE rb_gtk_mate_pattern_set_name(VALUE self, VALUE name) {
    GtkMatePattern* gtk_mate_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(name) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_name;
    _c_name = g_strdup(STR2CSTR(name));
    // ValaMemberSet#body
    gtk_mate_pattern->name = _c_name;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_pattern_get_comment(VALUE self) {
    GtkMatePattern* gtk_mate_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_pattern->comment; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == NULL) {
        _rb_return = Qnil;
      }
      else {
        _rb_return = rb_str_new2(_c_return);
      }

    return _rb_return;
}

static VALUE rb_gtk_mate_pattern_set_comment(VALUE self, VALUE comment) {
    GtkMatePattern* gtk_mate_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(comment) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_comment;
    _c_comment = g_strdup(STR2CSTR(comment));
    // ValaMemberSet#body
    gtk_mate_pattern->comment = _c_comment;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_pattern_get_all_patterns(VALUE self) {
    // Method#type_checks
    // Method#argument_type_conversions
    // StaticMemberGet#body
    GeeArrayList* _c_return = gtk_mate_pattern_all_patterns;
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val13;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val13 = 0; it_val13 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val13 = it_val13 + 1) {
            GtkMatePattern* i_val14;
            i_val14 =  (gee_list_get (GEE_LIST (_c_return), it_val13));
            VALUE rb_ival14;
            rb_ival14 = GOBJ2RVAL(i_val14);
            rb_ary_store (_rb_return, it_val13, rb_ival14);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_pattern_set_all_patterns(VALUE self, VALUE all_patterns) {
    // Method#type_checks
    if (TYPE(all_patterns) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_all_patterns;
        // ArrayListType#ruby_to_c(:before, "all_patterns", "_c_all_patterns")
    int len_val15 = RARRAY_LEN(all_patterns);
    _c_all_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val15; i++) {
            VALUE _rb_el = rb_ary_entry(all_patterns, (long) i);
            GtkMatePattern* _c_el = _GTK_MATE_PATTERN_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_all_patterns), (_c_el));
        }
    }

    // StaticMemberSet#body
    gtk_mate_pattern_all_patterns = _c_all_patterns; 
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_pattern_create_from_plist(VALUE self, VALUE all_patterns, VALUE pd) {
    // Method#type_checks
    if (TYPE(all_patterns) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_all_patterns;
        // ArrayListType#ruby_to_c(:before, "all_patterns", "_c_all_patterns")
    int len_val16 = RARRAY_LEN(all_patterns);
    _c_all_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val16; i++) {
            VALUE _rb_el = rb_ary_entry(all_patterns, (long) i);
            GtkMatePattern* _c_el = _GTK_MATE_PATTERN_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_all_patterns), (_c_el));
        }
    }

    PListDict* _c_pd;
    _c_pd = _PLIST_DICT_SELF(pd);
    // Method#body
    
    GtkMatePattern* _c_return;
    _c_return = gtk_mate_pattern_create_from_plist(_c_all_patterns, _c_pd);
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}

static VALUE rb_gtk_mate_pattern_make_captures_from_plist(VALUE self, VALUE pd) {
    // Method#type_checks
    // Method#argument_type_conversions
    PListDict* _c_pd;
    _c_pd = _PLIST_DICT_SELF(pd);
    // Method#body
    
    GeeHashMap* _c_return;
    _c_return = gtk_mate_pattern_make_captures_from_plist(_c_pd);
    // Method#return_type_conversion
    VALUE _rb_return; 
        // HashMap#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        _rb_return = rb_hash_new();
        GeeSet* s_collection;
        GeeIterator* s_it;
        s_collection = gee_map_get_keys (GEE_MAP (_c_return));
        s_it = gee_iterable_iterator (GEE_ITERABLE (s_collection));
        while (gee_iterator_next (s_it)) {
            int s;
            s = ((int) (gee_iterator_get (s_it)));
            {
                char * v;
                v = (char *) ((char *) (gee_map_get (GEE_MAP (_c_return), s)));
                VALUE rb_s;
                rb_s = INT2FIX(s);
                VALUE rb_v;
                      if (v == NULL) {
        rb_v = Qnil;
      }
      else {
        rb_v = rb_str_new2(v);
      }

                rb_hash_aset(_rb_return, rb_s, rb_v);
//                s = (g_free (s), NULL);
            }
        }
        (s_it == NULL ? NULL : (s_it = (g_object_unref (s_it), NULL)));
        (s_collection == NULL ? NULL : (s_collection = (g_object_unref (s_collection), NULL)));
    }

    return _rb_return;
}


/****  Gtk.Mate.SinglePattern methods *****/


static VALUE gtk_mate_single_pattern_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_single_pattern_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_single_pattern_get_match(VALUE self) {
    GtkMateSinglePattern* gtk_mate_single_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    OnigurumaRegex* _c_return = gtk_mate_single_pattern->match; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_single_pattern_set_match(VALUE self, VALUE match) {
    GtkMateSinglePattern* gtk_mate_single_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigurumaRegex* _c_match;
    _c_match = _ONIGURUMA_REGEX_SELF(match);
    // ValaMemberSet#body
    gtk_mate_single_pattern->match = _c_match;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_single_pattern_get_captures(VALUE self) {
    GtkMateSinglePattern* gtk_mate_single_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeHashMap* _c_return = gtk_mate_single_pattern->captures; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // HashMap#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        _rb_return = rb_hash_new();
        GeeSet* s_collection;
        GeeIterator* s_it;
        s_collection = gee_map_get_keys (GEE_MAP (_c_return));
        s_it = gee_iterable_iterator (GEE_ITERABLE (s_collection));
        while (gee_iterator_next (s_it)) {
            int s;
            s = ((int) (gee_iterator_get (s_it)));
            {
                char * v;
                v = (char *) ((char *) (gee_map_get (GEE_MAP (_c_return), s)));
                VALUE rb_s;
                rb_s = INT2FIX(s);
                VALUE rb_v;
                      if (v == NULL) {
        rb_v = Qnil;
      }
      else {
        rb_v = rb_str_new2(v);
      }

                rb_hash_aset(_rb_return, rb_s, rb_v);
//                s = (g_free (s), NULL);
            }
        }
        (s_it == NULL ? NULL : (s_it = (g_object_unref (s_it), NULL)));
        (s_collection == NULL ? NULL : (s_collection = (g_object_unref (s_collection), NULL)));
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_single_pattern_set_captures(VALUE self, VALUE captures) {
    GtkMateSinglePattern* gtk_mate_single_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(captures) != T_HASH) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a hash");
    }
    // Method#argument_type_conversions
    GeeHashMap* _c_captures;
        // HashMap#ruby_to_c(:before, "captures", "_c_captures")
    _c_captures = gee_hash_map_new (G_TYPE_INT, NULL, NULL, G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, g_str_hash, g_str_equal, g_direct_equal);
    VALUE rb_keys = rb_funcall(captures, rb_intern("keys"), 0);
    int len_val17 = RARRAY_LEN(rb_keys);
    {
        gint i;
        i = 0;
        for (; i < len_val17; i++) {
            VALUE _rb_key = rb_ary_entry(rb_keys, (long) i);
            VALUE _rb_value = rb_hash_aref(captures, _rb_key);
            int _c__rb_key;
            _c__rb_key = FIX2INT(_rb_key);
            char * _c__rb_value;
            _c__rb_value = g_strdup(STR2CSTR(_rb_value));
            gee_map_set (GEE_MAP (_c_captures), _c__rb_key,  (_c__rb_value));
        }
    }

    // ValaMemberSet#body
    gtk_mate_single_pattern->captures = _c_captures;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_single_pattern_create_from_plist(VALUE self, VALUE all_patterns, VALUE pd) {
    // Method#type_checks
    if (TYPE(all_patterns) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_all_patterns;
        // ArrayListType#ruby_to_c(:before, "all_patterns", "_c_all_patterns")
    int len_val18 = RARRAY_LEN(all_patterns);
    _c_all_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val18; i++) {
            VALUE _rb_el = rb_ary_entry(all_patterns, (long) i);
            GtkMatePattern* _c_el = _GTK_MATE_PATTERN_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_all_patterns), (_c_el));
        }
    }

    PListDict* _c_pd;
    _c_pd = _PLIST_DICT_SELF(pd);
    // Method#body
    
    GtkMateSinglePattern* _c_return;
    _c_return = gtk_mate_single_pattern_create_from_plist(_c_all_patterns, _c_pd);
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}


/****  Gtk.Mate.DoublePattern methods *****/


static VALUE gtk_mate_double_pattern_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_double_pattern_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_double_pattern_get_begin(VALUE self) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    OnigurumaRegex* _c_return = gtk_mate_double_pattern->begin; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_double_pattern_set_begin(VALUE self, VALUE begin) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigurumaRegex* _c_begin;
    _c_begin = _ONIGURUMA_REGEX_SELF(begin);
    // ValaMemberSet#body
    gtk_mate_double_pattern->begin = _c_begin;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_double_pattern_get_end(VALUE self) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    OnigurumaRegex* _c_return = gtk_mate_double_pattern->end; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_double_pattern_set_end(VALUE self, VALUE end) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigurumaRegex* _c_end;
    _c_end = _ONIGURUMA_REGEX_SELF(end);
    // ValaMemberSet#body
    gtk_mate_double_pattern->end = _c_end;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_double_pattern_get_begin_string(VALUE self) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_double_pattern->begin_string; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == NULL) {
        _rb_return = Qnil;
      }
      else {
        _rb_return = rb_str_new2(_c_return);
      }

    return _rb_return;
}

static VALUE rb_gtk_mate_double_pattern_set_begin_string(VALUE self, VALUE begin_string) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(begin_string) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_begin_string;
    _c_begin_string = g_strdup(STR2CSTR(begin_string));
    // ValaMemberSet#body
    gtk_mate_double_pattern->begin_string = _c_begin_string;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_double_pattern_get_begin_captures(VALUE self) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeHashMap* _c_return = gtk_mate_double_pattern->begin_captures; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // HashMap#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        _rb_return = rb_hash_new();
        GeeSet* s_collection;
        GeeIterator* s_it;
        s_collection = gee_map_get_keys (GEE_MAP (_c_return));
        s_it = gee_iterable_iterator (GEE_ITERABLE (s_collection));
        while (gee_iterator_next (s_it)) {
            int s;
            s = ((int) (gee_iterator_get (s_it)));
            {
                char * v;
                v = (char *) ((char *) (gee_map_get (GEE_MAP (_c_return), s)));
                VALUE rb_s;
                rb_s = INT2FIX(s);
                VALUE rb_v;
                      if (v == NULL) {
        rb_v = Qnil;
      }
      else {
        rb_v = rb_str_new2(v);
      }

                rb_hash_aset(_rb_return, rb_s, rb_v);
//                s = (g_free (s), NULL);
            }
        }
        (s_it == NULL ? NULL : (s_it = (g_object_unref (s_it), NULL)));
        (s_collection == NULL ? NULL : (s_collection = (g_object_unref (s_collection), NULL)));
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_double_pattern_set_begin_captures(VALUE self, VALUE begin_captures) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(begin_captures) != T_HASH) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a hash");
    }
    // Method#argument_type_conversions
    GeeHashMap* _c_begin_captures;
        // HashMap#ruby_to_c(:before, "begin_captures", "_c_begin_captures")
    _c_begin_captures = gee_hash_map_new (G_TYPE_INT, NULL, NULL, G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, g_str_hash, g_str_equal, g_direct_equal);
    VALUE rb_keys = rb_funcall(begin_captures, rb_intern("keys"), 0);
    int len_val19 = RARRAY_LEN(rb_keys);
    {
        gint i;
        i = 0;
        for (; i < len_val19; i++) {
            VALUE _rb_key = rb_ary_entry(rb_keys, (long) i);
            VALUE _rb_value = rb_hash_aref(begin_captures, _rb_key);
            int _c__rb_key;
            _c__rb_key = FIX2INT(_rb_key);
            char * _c__rb_value;
            _c__rb_value = g_strdup(STR2CSTR(_rb_value));
            gee_map_set (GEE_MAP (_c_begin_captures), _c__rb_key,  (_c__rb_value));
        }
    }

    // ValaMemberSet#body
    gtk_mate_double_pattern->begin_captures = _c_begin_captures;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_double_pattern_get_end_captures(VALUE self) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeHashMap* _c_return = gtk_mate_double_pattern->end_captures; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // HashMap#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        _rb_return = rb_hash_new();
        GeeSet* s_collection;
        GeeIterator* s_it;
        s_collection = gee_map_get_keys (GEE_MAP (_c_return));
        s_it = gee_iterable_iterator (GEE_ITERABLE (s_collection));
        while (gee_iterator_next (s_it)) {
            int s;
            s = ((int) (gee_iterator_get (s_it)));
            {
                char * v;
                v = (char *) ((char *) (gee_map_get (GEE_MAP (_c_return), s)));
                VALUE rb_s;
                rb_s = INT2FIX(s);
                VALUE rb_v;
                      if (v == NULL) {
        rb_v = Qnil;
      }
      else {
        rb_v = rb_str_new2(v);
      }

                rb_hash_aset(_rb_return, rb_s, rb_v);
//                s = (g_free (s), NULL);
            }
        }
        (s_it == NULL ? NULL : (s_it = (g_object_unref (s_it), NULL)));
        (s_collection == NULL ? NULL : (s_collection = (g_object_unref (s_collection), NULL)));
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_double_pattern_set_end_captures(VALUE self, VALUE end_captures) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(end_captures) != T_HASH) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a hash");
    }
    // Method#argument_type_conversions
    GeeHashMap* _c_end_captures;
        // HashMap#ruby_to_c(:before, "end_captures", "_c_end_captures")
    _c_end_captures = gee_hash_map_new (G_TYPE_INT, NULL, NULL, G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, g_str_hash, g_str_equal, g_direct_equal);
    VALUE rb_keys = rb_funcall(end_captures, rb_intern("keys"), 0);
    int len_val20 = RARRAY_LEN(rb_keys);
    {
        gint i;
        i = 0;
        for (; i < len_val20; i++) {
            VALUE _rb_key = rb_ary_entry(rb_keys, (long) i);
            VALUE _rb_value = rb_hash_aref(end_captures, _rb_key);
            int _c__rb_key;
            _c__rb_key = FIX2INT(_rb_key);
            char * _c__rb_value;
            _c__rb_value = g_strdup(STR2CSTR(_rb_value));
            gee_map_set (GEE_MAP (_c_end_captures), _c__rb_key,  (_c__rb_value));
        }
    }

    // ValaMemberSet#body
    gtk_mate_double_pattern->end_captures = _c_end_captures;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_double_pattern_get_patterns(VALUE self) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeArrayList* _c_return = gtk_mate_double_pattern->patterns; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val21;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val21 = 0; it_val21 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val21 = it_val21 + 1) {
            GtkMatePattern* i_val22;
            i_val22 =  (gee_list_get (GEE_LIST (_c_return), it_val21));
            VALUE rb_ival22;
            rb_ival22 = GOBJ2RVAL(i_val22);
            rb_ary_store (_rb_return, it_val21, rb_ival22);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_double_pattern_set_patterns(VALUE self, VALUE patterns) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(patterns) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_patterns;
        // ArrayListType#ruby_to_c(:before, "patterns", "_c_patterns")
    int len_val23 = RARRAY_LEN(patterns);
    _c_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val23; i++) {
            VALUE _rb_el = rb_ary_entry(patterns, (long) i);
            GtkMatePattern* _c_el = _GTK_MATE_PATTERN_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_patterns), (_c_el));
        }
    }

    // ValaMemberSet#body
    gtk_mate_double_pattern->patterns = _c_patterns;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_double_pattern_create_from_plist(VALUE self, VALUE all_patterns, VALUE pd) {
    // Method#type_checks
    if (TYPE(all_patterns) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_all_patterns;
        // ArrayListType#ruby_to_c(:before, "all_patterns", "_c_all_patterns")
    int len_val24 = RARRAY_LEN(all_patterns);
    _c_all_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val24; i++) {
            VALUE _rb_el = rb_ary_entry(all_patterns, (long) i);
            GtkMatePattern* _c_el = _GTK_MATE_PATTERN_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_all_patterns), (_c_el));
        }
    }

    PListDict* _c_pd;
    _c_pd = _PLIST_DICT_SELF(pd);
    // Method#body
    
    GtkMateDoublePattern* _c_return;
    _c_return = gtk_mate_double_pattern_create_from_plist(_c_all_patterns, _c_pd);
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}

static VALUE rb_gtk_mate_double_pattern_replace_include_patterns(VALUE self, VALUE g) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateGrammar* _c_g;
    _c_g = _GTK_MATE_GRAMMAR_SELF(g);
    // Method#body
    
    gtk_mate_double_pattern_replace_include_patterns(gtk_mate_double_pattern, _c_g);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_double_pattern_replace_repository_includes(VALUE self, VALUE g) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateGrammar* _c_g;
    _c_g = _GTK_MATE_GRAMMAR_SELF(g);
    // Method#body
    
    gtk_mate_double_pattern_replace_repository_includes(gtk_mate_double_pattern, _c_g);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_double_pattern_replace_base_and_self_includes(VALUE self, VALUE g) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateGrammar* _c_g;
    _c_g = _GTK_MATE_GRAMMAR_SELF(g);
    // Method#body
    
    gtk_mate_double_pattern_replace_base_and_self_includes(gtk_mate_double_pattern, _c_g);
    // Method#return_type_conversion
    return Qnil;
}


/****  Gtk.Mate.IncludePattern methods *****/


static VALUE gtk_mate_include_pattern_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_include_pattern_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_include_pattern_create_from_plist(VALUE self, VALUE pd) {
    // Method#type_checks
    // Method#argument_type_conversions
    PListDict* _c_pd;
    _c_pd = _PLIST_DICT_SELF(pd);
    // Method#body
    
    GtkMateIncludePattern* _c_return;
    _c_return = gtk_mate_include_pattern_create_from_plist(_c_pd);
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}


/****  Gtk.Mate.Scope methods *****/


static VALUE gtk_mate_scope_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_scope_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_pattern(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkMatePattern* _c_return = gtk_mate_scope->pattern; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_pattern(VALUE self, VALUE pattern) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMatePattern* _c_pattern;
    _c_pattern = _GTK_MATE_PATTERN_SELF(pattern);
    // ValaMemberSet#body
    gtk_mate_scope->pattern = _c_pattern;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_name(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_scope->name; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == NULL) {
        _rb_return = Qnil;
      }
      else {
        _rb_return = rb_str_new2(_c_return);
      }

    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_name(VALUE self, VALUE name) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(name) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_name;
    _c_name = g_strdup(STR2CSTR(name));
    // ValaMemberSet#body
    gtk_mate_scope->name = _c_name;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_open_match(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    OnigurumaMatch* _c_return = gtk_mate_scope->open_match; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_open_match(VALUE self, VALUE open_match) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigurumaMatch* _c_open_match;
    _c_open_match = _ONIGURUMA_MATCH_SELF(open_match);
    // ValaMemberSet#body
    gtk_mate_scope->open_match = _c_open_match;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_close_match(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    OnigurumaMatch* _c_return = gtk_mate_scope->close_match; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_close_match(VALUE self, VALUE close_match) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigurumaMatch* _c_close_match;
    _c_close_match = _ONIGURUMA_MATCH_SELF(close_match);
    // ValaMemberSet#body
    gtk_mate_scope->close_match = _c_close_match;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_closing_regex(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    OnigurumaRegex* _c_return = gtk_mate_scope->closing_regex; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_closing_regex(VALUE self, VALUE closing_regex) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigurumaRegex* _c_closing_regex;
    _c_closing_regex = _ONIGURUMA_REGEX_SELF(closing_regex);
    // ValaMemberSet#body
    gtk_mate_scope->closing_regex = _c_closing_regex;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_start_mark(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkSourceMark* _c_return = gtk_mate_scope->start_mark; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_start_mark(VALUE self, VALUE start_mark) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkSourceMark* _c_start_mark;
    _c_start_mark = _GTK_SOURCE_MARK_SELF(start_mark);
    // ValaMemberSet#body
    gtk_mate_scope->start_mark = _c_start_mark;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_inner_start_mark(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkSourceMark* _c_return = gtk_mate_scope->inner_start_mark; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_inner_start_mark(VALUE self, VALUE inner_start_mark) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkSourceMark* _c_inner_start_mark;
    _c_inner_start_mark = _GTK_SOURCE_MARK_SELF(inner_start_mark);
    // ValaMemberSet#body
    gtk_mate_scope->inner_start_mark = _c_inner_start_mark;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_inner_end_mark(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkSourceMark* _c_return = gtk_mate_scope->inner_end_mark; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_inner_end_mark(VALUE self, VALUE inner_end_mark) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkSourceMark* _c_inner_end_mark;
    _c_inner_end_mark = _GTK_SOURCE_MARK_SELF(inner_end_mark);
    // ValaMemberSet#body
    gtk_mate_scope->inner_end_mark = _c_inner_end_mark;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_end_mark(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkSourceMark* _c_return = gtk_mate_scope->end_mark; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_end_mark(VALUE self, VALUE end_mark) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkSourceMark* _c_end_mark;
    _c_end_mark = _GTK_SOURCE_MARK_SELF(end_mark);
    // ValaMemberSet#body
    gtk_mate_scope->end_mark = _c_end_mark;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_tag(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkTextTag* _c_return = gtk_mate_scope->tag; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_tag(VALUE self, VALUE tag) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkTextTag* _c_tag;
    _c_tag = _GTK_TEXT_TAG_SELF(tag);
    // ValaMemberSet#body
    gtk_mate_scope->tag = _c_tag;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_inner_tag(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkTextTag* _c_return = gtk_mate_scope->inner_tag; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_inner_tag(VALUE self, VALUE inner_tag) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkTextTag* _c_inner_tag;
    _c_inner_tag = _GTK_TEXT_TAG_SELF(inner_tag);
    // ValaMemberSet#body
    gtk_mate_scope->inner_tag = _c_inner_tag;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_bg_color(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_scope->bg_color; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == NULL) {
        _rb_return = Qnil;
      }
      else {
        _rb_return = rb_str_new2(_c_return);
      }

    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_bg_color(VALUE self, VALUE bg_color) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(bg_color) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_bg_color;
    _c_bg_color = g_strdup(STR2CSTR(bg_color));
    // ValaMemberSet#body
    gtk_mate_scope->bg_color = _c_bg_color;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_is_capture(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    gboolean _c_return = gtk_mate_scope->is_capture; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_is_capture(VALUE self, VALUE is_capture) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(is_capture) != T_TRUE && TYPE(is_capture) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    gboolean _c_is_capture;
          if (is_capture == Qtrue)
          _c_is_capture = TRUE;
      else
          _c_is_capture = FALSE;

    // ValaMemberSet#body
    gtk_mate_scope->is_capture = _c_is_capture;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_children(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeArrayList* _c_return = gtk_mate_scope->children; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val25;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val25 = 0; it_val25 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val25 = it_val25 + 1) {
            GtkMateScope* i_val26;
            i_val26 =  (gee_list_get (GEE_LIST (_c_return), it_val25));
            VALUE rb_ival26;
            rb_ival26 = GOBJ2RVAL(i_val26);
            rb_ary_store (_rb_return, it_val25, rb_ival26);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_children(VALUE self, VALUE children) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(children) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_children;
        // ArrayListType#ruby_to_c(:before, "children", "_c_children")
    int len_val27 = RARRAY_LEN(children);
    _c_children = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val27; i++) {
            VALUE _rb_el = rb_ary_entry(children, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_children), (_c_el));
        }
    }

    // ValaMemberSet#body
    gtk_mate_scope->children = _c_children;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_parent(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkMateScope* _c_return = gtk_mate_scope->parent; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_parent(VALUE self, VALUE parent) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateScope* _c_parent;
    _c_parent = _GTK_MATE_SCOPE_SELF(parent);
    // ValaMemberSet#body
    gtk_mate_scope->parent = _c_parent;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_is_root(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gboolean _c_return;
    _c_return = gtk_mate_scope_is_root(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_scope_pretty(VALUE self, VALUE indent) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(indent) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_indent;
    _c_indent = FIX2INT(indent);
    // Method#body
    
    char * _c_return;
    _c_return = gtk_mate_scope_pretty(gtk_mate_scope, _c_indent);
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == NULL) {
        _rb_return = Qnil;
      }
      else {
        _rb_return = rb_str_new2(_c_return);
      }

    return _rb_return;
}


/****  Gtk.Mate.Grammar methods *****/


static VALUE gtk_mate_grammar_initialize(VALUE self, VALUE plist) {
    PListDict* _c_plist;
    _c_plist = _PLIST_DICT_SELF(plist);

    RBGTK_INITIALIZE(self, gtk_mate_grammar_new (_c_plist));
    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_file_types(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char** _c_return = gtk_mate_grammar->file_types; 
    gint _rb_return__length = gtk_mate_grammar->file_types_length1;
    // Method#return_type_conversion
    VALUE _rb_return; 
              if (_c_return == NULL) {
              _rb_return = Qnil;
          }
          else {
              _rb_return = rb_ary_new2(_rb_return__length);
              long val28;
              for(val28 = 0; val28 < _rb_return__length; val28++) {
                  rb_ary_store(_rb_return, val28, rb_str_new2(_c_return[val28]));
//                g_free(_c_return[val28]);
              }
          }

    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_file_types(VALUE self, VALUE file_types) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(file_types) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array of strings");
    }
    // Method#argument_type_conversions
    char** _c_file_types;
              gint _c_file_types__length = RARRAY_LEN(file_types);
          _c_file_types = malloc(_c_file_types__length*sizeof(char*));
          long val29;
          for(val29 = 0; val29 < _c_file_types__length; val29++) {
             *(_c_file_types+val29) = RSTRING_PTR(rb_ary_entry(file_types, (long) val29));
          }

    // ValaMemberSet#body
    gtk_mate_grammar->file_types = _c_file_types;
    gtk_mate_grammar->file_types_length1 = _c_file_types__length;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_first_line_match(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    OnigurumaRegex* _c_return = gtk_mate_grammar->first_line_match; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_first_line_match(VALUE self, VALUE first_line_match) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigurumaRegex* _c_first_line_match;
    _c_first_line_match = _ONIGURUMA_REGEX_SELF(first_line_match);
    // ValaMemberSet#body
    gtk_mate_grammar->first_line_match = _c_first_line_match;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_key_equivalent(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_grammar->key_equivalent; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == NULL) {
        _rb_return = Qnil;
      }
      else {
        _rb_return = rb_str_new2(_c_return);
      }

    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_key_equivalent(VALUE self, VALUE key_equivalent) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(key_equivalent) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_key_equivalent;
    _c_key_equivalent = g_strdup(STR2CSTR(key_equivalent));
    // ValaMemberSet#body
    gtk_mate_grammar->key_equivalent = _c_key_equivalent;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_scope_name(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_grammar->scope_name; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == NULL) {
        _rb_return = Qnil;
      }
      else {
        _rb_return = rb_str_new2(_c_return);
      }

    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_scope_name(VALUE self, VALUE scope_name) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(scope_name) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_scope_name;
    _c_scope_name = g_strdup(STR2CSTR(scope_name));
    // ValaMemberSet#body
    gtk_mate_grammar->scope_name = _c_scope_name;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_comment(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_grammar->comment; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == NULL) {
        _rb_return = Qnil;
      }
      else {
        _rb_return = rb_str_new2(_c_return);
      }

    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_comment(VALUE self, VALUE comment) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(comment) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_comment;
    _c_comment = g_strdup(STR2CSTR(comment));
    // ValaMemberSet#body
    gtk_mate_grammar->comment = _c_comment;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_all_patterns(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeArrayList* _c_return = gtk_mate_grammar->all_patterns; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val30;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val30 = 0; it_val30 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val30 = it_val30 + 1) {
            GtkMatePattern* i_val31;
            i_val31 =  (gee_list_get (GEE_LIST (_c_return), it_val30));
            VALUE rb_ival31;
            rb_ival31 = GOBJ2RVAL(i_val31);
            rb_ary_store (_rb_return, it_val30, rb_ival31);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_all_patterns(VALUE self, VALUE all_patterns) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(all_patterns) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_all_patterns;
        // ArrayListType#ruby_to_c(:before, "all_patterns", "_c_all_patterns")
    int len_val32 = RARRAY_LEN(all_patterns);
    _c_all_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val32; i++) {
            VALUE _rb_el = rb_ary_entry(all_patterns, (long) i);
            GtkMatePattern* _c_el = _GTK_MATE_PATTERN_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_all_patterns), (_c_el));
        }
    }

    // ValaMemberSet#body
    gtk_mate_grammar->all_patterns = _c_all_patterns;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_loaded(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    gboolean _c_return = gtk_mate_grammar->loaded; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_loaded(VALUE self, VALUE loaded) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(loaded) != T_TRUE && TYPE(loaded) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    gboolean _c_loaded;
          if (loaded == Qtrue)
          _c_loaded = TRUE;
      else
          _c_loaded = FALSE;

    // ValaMemberSet#body
    gtk_mate_grammar->loaded = _c_loaded;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_folding_start_marker(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    OnigurumaRegex* _c_return = gtk_mate_grammar->folding_start_marker; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_folding_start_marker(VALUE self, VALUE folding_start_marker) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigurumaRegex* _c_folding_start_marker;
    _c_folding_start_marker = _ONIGURUMA_REGEX_SELF(folding_start_marker);
    // ValaMemberSet#body
    gtk_mate_grammar->folding_start_marker = _c_folding_start_marker;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_folding_stop_marker(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    OnigurumaRegex* _c_return = gtk_mate_grammar->folding_stop_marker; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_folding_stop_marker(VALUE self, VALUE folding_stop_marker) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigurumaRegex* _c_folding_stop_marker;
    _c_folding_stop_marker = _ONIGURUMA_REGEX_SELF(folding_stop_marker);
    // ValaMemberSet#body
    gtk_mate_grammar->folding_stop_marker = _c_folding_stop_marker;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_patterns(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeArrayList* _c_return = gtk_mate_grammar->patterns; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val33;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val33 = 0; it_val33 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val33 = it_val33 + 1) {
            GtkMatePattern* i_val34;
            i_val34 =  (gee_list_get (GEE_LIST (_c_return), it_val33));
            VALUE rb_ival34;
            rb_ival34 = GOBJ2RVAL(i_val34);
            rb_ary_store (_rb_return, it_val33, rb_ival34);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_patterns(VALUE self, VALUE patterns) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(patterns) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_patterns;
        // ArrayListType#ruby_to_c(:before, "patterns", "_c_patterns")
    int len_val35 = RARRAY_LEN(patterns);
    _c_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val35; i++) {
            VALUE _rb_el = rb_ary_entry(patterns, (long) i);
            GtkMatePattern* _c_el = _GTK_MATE_PATTERN_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_patterns), (_c_el));
        }
    }

    // ValaMemberSet#body
    gtk_mate_grammar->patterns = _c_patterns;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_repository(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeHashMap* _c_return = gtk_mate_grammar->repository; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // HashMap#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        _rb_return = rb_hash_new();
        GeeSet* s_collection;
        GeeIterator* s_it;
        s_collection = gee_map_get_keys (GEE_MAP (_c_return));
        s_it = gee_iterable_iterator (GEE_ITERABLE (s_collection));
        while (gee_iterator_next (s_it)) {
            char * s;
            s = ((char *) (gee_iterator_get (s_it)));
            {
                GeeArrayList* v;
                v =  ( (gee_map_get (GEE_MAP (_c_return), s)));
                VALUE rb_s;
                      if (s == NULL) {
        rb_s = Qnil;
      }
      else {
        rb_s = rb_str_new2(s);
      }

                VALUE rb_v;
                    // ArrayListType#c_to_ruby(:after, "v", "rb_v")
    if (v == NULL) {
        rb_v = Qnil;
    }
    else {
        int it_val36;
        rb_v = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (v)));
        for (it_val36 = 0; it_val36 < gee_collection_get_size (GEE_COLLECTION (v)); it_val36 = it_val36 + 1) {
            GtkMatePattern* i_val37;
            i_val37 =  (gee_list_get (GEE_LIST (v), it_val36));
            VALUE rb_ival37;
            rb_ival37 = GOBJ2RVAL(i_val37);
            rb_ary_store (rb_v, it_val36, rb_ival37);
        }
    }

                rb_hash_aset(_rb_return, rb_s, rb_v);
//                s = (g_free (s), NULL);
            }
        }
        (s_it == NULL ? NULL : (s_it = (g_object_unref (s_it), NULL)));
        (s_collection == NULL ? NULL : (s_collection = (g_object_unref (s_collection), NULL)));
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_repository(VALUE self, VALUE repository) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(repository) != T_HASH) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a hash");
    }
    // Method#argument_type_conversions
    GeeHashMap* _c_repository;
        // HashMap#ruby_to_c(:before, "repository", "_c_repository")
    _c_repository = gee_hash_map_new (G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, GEE_TYPE_ARRAY_LIST, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_str_hash, g_str_equal, g_direct_equal);
    VALUE rb_keys = rb_funcall(repository, rb_intern("keys"), 0);
    int len_val38 = RARRAY_LEN(rb_keys);
    {
        gint i;
        i = 0;
        for (; i < len_val38; i++) {
            VALUE _rb_key = rb_ary_entry(rb_keys, (long) i);
            VALUE _rb_value = rb_hash_aref(repository, _rb_key);
            char * _c__rb_key;
            _c__rb_key = g_strdup(STR2CSTR(_rb_key));
            GeeArrayList* _c__rb_value;
                // ArrayListType#ruby_to_c(:before, "_rb_value", "_c__rb_value")
    int len_val39 = RARRAY_LEN(_rb_value);
    _c__rb_value = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val39; i++) {
            VALUE _rb_el = rb_ary_entry(_rb_value, (long) i);
            GtkMatePattern* _c_el = _GTK_MATE_PATTERN_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c__rb_value), (_c_el));
        }
    }

            gee_map_set (GEE_MAP (_c_repository), _c__rb_key,  (_c__rb_value));
        }
    }

    // ValaMemberSet#body
    gtk_mate_grammar->repository = _c_repository;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_grammar_init_for_reference(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gtk_mate_grammar_init_for_reference(gtk_mate_grammar);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_grammar_init_for_use(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gtk_mate_grammar_init_for_use(gtk_mate_grammar);
    // Method#return_type_conversion
    return Qnil;
}


/****  Gtk.Mate.View methods *****/


static VALUE gtk_mate_view_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_view_new ());
    return Qnil;
}


/****  Gtk.Mate.Buffer methods *****/


static VALUE gtk_mate_buffer_initialize(VALUE self) {

    G_INITIALIZE(self, gtk_mate_buffer_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_buffer_get_bundles(VALUE self) {
    // Method#type_checks
    // Method#argument_type_conversions
    // StaticMemberGet#body
    GeeArrayList* _c_return = gtk_mate_buffer_bundles;
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val40;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val40 = 0; it_val40 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val40 = it_val40 + 1) {
            GtkMateBundle* i_val41;
            i_val41 =  (gee_list_get (GEE_LIST (_c_return), it_val40));
            VALUE rb_ival41;
            rb_ival41 = GOBJ2RVAL(i_val41);
            rb_ary_store (_rb_return, it_val40, rb_ival41);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_buffer_set_bundles(VALUE self, VALUE bundles) {
    // Method#type_checks
    if (TYPE(bundles) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_bundles;
        // ArrayListType#ruby_to_c(:before, "bundles", "_c_bundles")
    int len_val42 = RARRAY_LEN(bundles);
    _c_bundles = gee_array_list_new (GTK_MATE_TYPE_BUNDLE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val42; i++) {
            VALUE _rb_el = rb_ary_entry(bundles, (long) i);
            GtkMateBundle* _c_el = _GTK_MATE_BUNDLE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_bundles), (_c_el));
        }
    }

    // StaticMemberSet#body
    gtk_mate_buffer_bundles = _c_bundles; 
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_buffer_get_themes(VALUE self) {
    // Method#type_checks
    // Method#argument_type_conversions
    // StaticMemberGet#body
    GeeArrayList* _c_return = gtk_mate_buffer_themes;
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val43;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val43 = 0; it_val43 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val43 = it_val43 + 1) {
            GtkMateTheme* i_val44;
            i_val44 =  (gee_list_get (GEE_LIST (_c_return), it_val43));
            VALUE rb_ival44;
            rb_ival44 = GOBJ2RVAL(i_val44);
            rb_ary_store (_rb_return, it_val43, rb_ival44);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_buffer_set_themes(VALUE self, VALUE themes) {
    // Method#type_checks
    if (TYPE(themes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_themes;
        // ArrayListType#ruby_to_c(:before, "themes", "_c_themes")
    int len_val45 = RARRAY_LEN(themes);
    _c_themes = gee_array_list_new (GTK_MATE_TYPE_THEME, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val45; i++) {
            VALUE _rb_el = rb_ary_entry(themes, (long) i);
            GtkMateTheme* _c_el = _GTK_MATE_THEME_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_themes), (_c_el));
        }
    }

    // StaticMemberSet#body
    gtk_mate_buffer_themes = _c_themes; 
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_buffer_get_parser(VALUE self) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkMateParser* _c_return = gtk_mate_buffer->parser; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_buffer_set_parser(VALUE self, VALUE parser) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateParser* _c_parser;
    _c_parser = _GTK_MATE_PARSER_SELF(parser);
    // ValaMemberSet#body
    gtk_mate_buffer->parser = _c_parser;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_buffer_set_grammar_by_name(VALUE self, VALUE name) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(name) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_name;
    _c_name = g_strdup(STR2CSTR(name));
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_buffer_set_grammar_by_name(gtk_mate_buffer, _c_name);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_buffer_set_grammar_by_extension(VALUE self, VALUE extension) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(extension) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_extension;
    _c_extension = g_strdup(STR2CSTR(extension));
    // Method#body
    
    char * _c_return;
    _c_return = gtk_mate_buffer_set_grammar_by_extension(gtk_mate_buffer, _c_extension);
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
              if (_c_return == NULL) {
        _rb_return = Qnil;
      }
      else {
        _rb_return = rb_str_new2(_c_return);
      }

    }
    return _rb_return;
}


/****  Gtk.Mate.Parser methods *****/


static VALUE gtk_mate_parser_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_parser_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_parser_get_root(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkMateScope* _c_return = gtk_mate_parser->root; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_parser_set_root(VALUE self, VALUE root) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateScope* _c_root;
    _c_root = _GTK_MATE_SCOPE_SELF(root);
    // ValaMemberSet#body
    gtk_mate_parser->root = _c_root;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_get_current(VALUE self) {
    // Method#type_checks
    // Method#argument_type_conversions
    // StaticMemberGet#body
    GtkMateParser* _c_return = gtk_mate_parser_current;
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_parser_set_current(VALUE self, VALUE current) {
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateParser* _c_current;
    _c_current = _GTK_MATE_PARSER_SELF(current);
    // StaticMemberSet#body
    gtk_mate_parser_current = _c_current; 
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_make_root(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gtk_mate_parser_make_root(gtk_mate_parser);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_connect_buffer_signals(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gtk_mate_parser_connect_buffer_signals(gtk_mate_parser);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_create(VALUE self, VALUE grammar, VALUE buffer) {
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateGrammar* _c_grammar;
    _c_grammar = _GTK_MATE_GRAMMAR_SELF(grammar);
    GtkMateBuffer* _c_buffer;
    _c_buffer = _GTK_MATE_BUFFER_SELF(buffer);
    // Method#body
    
    GtkMateParser* _c_return;
    _c_return = gtk_mate_parser_create(_c_grammar, _c_buffer);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}


/****  Gtk.Mate.Bundle methods *****/


static VALUE gtk_mate_bundle_initialize(VALUE self, VALUE name) {
    char * _c_name;
    _c_name = g_strdup(STR2CSTR(name));

    RBGTK_INITIALIZE(self, gtk_mate_bundle_new (_c_name));
    return Qnil;
}

static VALUE rb_gtk_mate_bundle_get_grammars(VALUE self) {
    GtkMateBundle* gtk_mate_bundle = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeArrayList* _c_return = gtk_mate_bundle->grammars; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val46;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val46 = 0; it_val46 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val46 = it_val46 + 1) {
            GtkMateGrammar* i_val47;
            i_val47 =  (gee_list_get (GEE_LIST (_c_return), it_val46));
            VALUE rb_ival47;
            rb_ival47 = GOBJ2RVAL(i_val47);
            rb_ary_store (_rb_return, it_val46, rb_ival47);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_bundle_set_grammars(VALUE self, VALUE grammars) {
    GtkMateBundle* gtk_mate_bundle = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(grammars) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_grammars;
        // ArrayListType#ruby_to_c(:before, "grammars", "_c_grammars")
    int len_val48 = RARRAY_LEN(grammars);
    _c_grammars = gee_array_list_new (GTK_MATE_TYPE_GRAMMAR, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val48; i++) {
            VALUE _rb_el = rb_ary_entry(grammars, (long) i);
            GtkMateGrammar* _c_el = _GTK_MATE_GRAMMAR_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_grammars), (_c_el));
        }
    }

    // ValaMemberSet#body
    gtk_mate_bundle->grammars = _c_grammars;
    // Method#return_type_conversion
    return Qnil;
}


/****  Oniguruma methods *****/


/****  Oniguruma.OnigError methods *****/


static VALUE oniguruma_onig_error_initialize(VALUE self) {

    G_INITIALIZE(self, oniguruma_onig_error_new ());
    return Qnil;
}

static VALUE rb_oniguruma_onig_error_get_code(VALUE self) {
    OnigurumaOnigError* oniguruma_onig_error = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    int _c_return = oniguruma_onig_error->code; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_oniguruma_onig_error_set_code(VALUE self, VALUE code) {
    OnigurumaOnigError* oniguruma_onig_error = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(code) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_code;
    _c_code = FIX2INT(code);
    // ValaMemberSet#body
    oniguruma_onig_error->code = _c_code;
    // Method#return_type_conversion
    return Qnil;
}


/****  Oniguruma.Match methods *****/


static VALUE oniguruma_match_initialize(VALUE self) {

    G_INITIALIZE(self, oniguruma_match_new ());
    return Qnil;
}

static VALUE rb_oniguruma_match_begin(VALUE self, VALUE capture) {
    OnigurumaMatch* oniguruma_match = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(capture) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_capture;
    _c_capture = FIX2INT(capture);
    // Method#body
    
    int _c_return;
    _c_return = oniguruma_match_begin(oniguruma_match, _c_capture);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_oniguruma_match_end(VALUE self, VALUE capture) {
    OnigurumaMatch* oniguruma_match = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(capture) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_capture;
    _c_capture = FIX2INT(capture);
    // Method#body
    
    int _c_return;
    _c_return = oniguruma_match_end(oniguruma_match, _c_capture);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}


/****  Oniguruma.Regex methods *****/


static VALUE oniguruma_regex_initialize(VALUE self) {

    G_INITIALIZE(self, oniguruma_regex_new ());
    return Qnil;
}

static VALUE rb_oniguruma_regex_search(VALUE self, VALUE target, VALUE start, VALUE end) {
    OnigurumaRegex* oniguruma_regex = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(target) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    if (TYPE(start) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(end) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    char * _c_target;
    _c_target = g_strdup(STR2CSTR(target));
    int _c_start;
    _c_start = FIX2INT(start);
    int _c_end;
    _c_end = FIX2INT(end);
    // Method#body
    
    OnigurumaMatch* _c_return;
    _c_return = oniguruma_regex_search(oniguruma_regex, _c_target, _c_start, _c_end);
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}

static VALUE rb_oniguruma_regex_make1(VALUE self, VALUE pattern) {
    // Method#type_checks
    if (TYPE(pattern) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_pattern;
    _c_pattern = g_strdup(STR2CSTR(pattern));
    // Method#body
    
    OnigurumaRegex* _c_return;
    _c_return = oniguruma_regex_make1(_c_pattern);
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}


/****  PList methods *****/

static VALUE rb_plist_parse(VALUE self, VALUE filename) {
    // Method#type_checks
    if (TYPE(filename) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_filename;
    _c_filename = g_strdup(STR2CSTR(filename));
    // Method#body
    GError* inner_error;
    inner_error = NULL;
    
    PListDict* _c_return;
    _c_return = plist_parse(_c_filename, &inner_error);
    if (inner_error != NULL) {
        if (inner_error->domain == XML_ERROR) {
            rb_raise(rb_vala_error, "[XmlError]: %s", inner_error->message);
        }
    }
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_plist_print_plist(VALUE self, VALUE indent, VALUE node) {
    // Method#type_checks
    if (TYPE(indent) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_indent;
    _c_indent = FIX2INT(indent);
    PListNode* _c_node;
    _c_node = _PLIST_NODE_SELF(node);
    // Method#body
    
    plist_print_plist(_c_indent, _c_node);
    // Method#return_type_conversion
    return Qnil;
}


/****  PList.Node methods *****/


static VALUE plist_node_initialize(VALUE self) {

    G_INITIALIZE(self, plist_node_new ());
    return Qnil;
}


/****  PList.String methods *****/


static VALUE plist_string_initialize(VALUE self) {

    G_INITIALIZE(self, plist_string_new ());
    return Qnil;
}

static VALUE rb_plist_string_get_str(VALUE self) {
    PListString* plist_string = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = plist_string->str; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == NULL) {
        _rb_return = Qnil;
      }
      else {
        _rb_return = rb_str_new2(_c_return);
      }

    return _rb_return;
}

static VALUE rb_plist_string_set_str(VALUE self, VALUE str) {
    PListString* plist_string = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(str) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_str;
    _c_str = g_strdup(STR2CSTR(str));
    // ValaMemberSet#body
    plist_string->str = _c_str;
    // Method#return_type_conversion
    return Qnil;
}


/****  PList.Array methods *****/


static VALUE plist_array_initialize(VALUE self) {

    G_INITIALIZE(self, plist_array_new ());
    return Qnil;
}

static VALUE rb_plist_array_get_array(VALUE self) {
    PListArray* plist_array = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeArrayList* _c_return = plist_array->array; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val49;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val49 = 0; it_val49 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val49 = it_val49 + 1) {
            PListNode* i_val50;
            i_val50 =  (gee_list_get (GEE_LIST (_c_return), it_val49));
            VALUE rb_ival50;
            rb_ival50 = GOBJ2RVAL(i_val50);
            rb_ary_store (_rb_return, it_val49, rb_ival50);
        }
    }

    return _rb_return;
}

static VALUE rb_plist_array_set_array(VALUE self, VALUE array) {
    PListArray* plist_array = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(array) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_array;
        // ArrayListType#ruby_to_c(:before, "array", "_c_array")
    int len_val51 = RARRAY_LEN(array);
    _c_array = gee_array_list_new (PLIST_TYPE_NODE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val51; i++) {
            VALUE _rb_el = rb_ary_entry(array, (long) i);
            PListNode* _c_el = _PLIST_NODE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_array), (_c_el));
        }
    }

    // ValaMemberSet#body
    plist_array->array = _c_array;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_plist_array_get(VALUE self, VALUE ix) {
    PListArray* plist_array = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(ix) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_ix;
    _c_ix = FIX2INT(ix);
    // Method#body
    
    PListNode* _c_return;
    _c_return = plist_array_get(plist_array, _c_ix);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}


/****  PList.Dict methods *****/


static VALUE plist_dict_initialize(VALUE self) {

    G_INITIALIZE(self, plist_dict_new ());
    return Qnil;
}

static VALUE rb_plist_dict_get_map(VALUE self) {
    PListDict* plist_dict = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeHashMap* _c_return = plist_dict->map; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // HashMap#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        _rb_return = rb_hash_new();
        GeeSet* s_collection;
        GeeIterator* s_it;
        s_collection = gee_map_get_keys (GEE_MAP (_c_return));
        s_it = gee_iterable_iterator (GEE_ITERABLE (s_collection));
        while (gee_iterator_next (s_it)) {
            char * s;
            s = ((char *) (gee_iterator_get (s_it)));
            {
                PListNode* v;
                v =  ( (gee_map_get (GEE_MAP (_c_return), s)));
                VALUE rb_s;
                      if (s == NULL) {
        rb_s = Qnil;
      }
      else {
        rb_s = rb_str_new2(s);
      }

                VALUE rb_v;
                rb_v = GOBJ2RVAL(v);
                rb_hash_aset(_rb_return, rb_s, rb_v);
//                s = (g_free (s), NULL);
            }
        }
        (s_it == NULL ? NULL : (s_it = (g_object_unref (s_it), NULL)));
        (s_collection == NULL ? NULL : (s_collection = (g_object_unref (s_collection), NULL)));
    }

    return _rb_return;
}

static VALUE rb_plist_dict_set_map(VALUE self, VALUE map) {
    PListDict* plist_dict = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(map) != T_HASH) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a hash");
    }
    // Method#argument_type_conversions
    GeeHashMap* _c_map;
        // HashMap#ruby_to_c(:before, "map", "_c_map")
    _c_map = gee_hash_map_new (G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, PLIST_TYPE_NODE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_str_hash, g_str_equal, g_direct_equal);
    VALUE rb_keys = rb_funcall(map, rb_intern("keys"), 0);
    int len_val52 = RARRAY_LEN(rb_keys);
    {
        gint i;
        i = 0;
        for (; i < len_val52; i++) {
            VALUE _rb_key = rb_ary_entry(rb_keys, (long) i);
            VALUE _rb_value = rb_hash_aref(map, _rb_key);
            char * _c__rb_key;
            _c__rb_key = g_strdup(STR2CSTR(_rb_key));
            PListNode* _c__rb_value;
            _c__rb_value = _PLIST_NODE_SELF(_rb_value);
            gee_map_set (GEE_MAP (_c_map), _c__rb_key,  (_c__rb_value));
        }
    }

    // ValaMemberSet#body
    plist_dict->map = _c_map;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_plist_dict_get(VALUE self, VALUE key) {
    PListDict* plist_dict = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(key) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_key;
    _c_key = g_strdup(STR2CSTR(key));
    // Method#body
    
    PListNode* _c_return;
    _c_return = plist_dict_get(plist_dict, _c_key);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_plist_dict_keys(VALUE self) {
    PListDict* plist_dict = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
              gint _rb_return__length;

    char** _c_return;
    _c_return = plist_dict_keys(plist_dict, &_rb_return__length);
    // Method#return_type_conversion
    VALUE _rb_return; 
              if (_c_return == NULL) {
              _rb_return = Qnil;
          }
          else {
              _rb_return = rb_ary_new2(_rb_return__length);
              long val53;
              for(val53 = 0; val53 < _rb_return__length; val53++) {
                  rb_ary_store(_rb_return, val53, rb_str_new2(_c_return[val53]));
//                g_free(_c_return[val53]);
              }
          }

    return _rb_return;
}

static VALUE rb_plist_dict_print_keys(VALUE self) {
    PListDict* plist_dict = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    plist_dict_print_keys(plist_dict);
    // Method#return_type_conversion
    return Qnil;
}

void Init_gtkmateview_rb() {
    rb_vala_error = rb_define_class("ValaError", rb_eval_string("Exception"));
    rbc_gtk = rb_eval_string("Gtk");
    rbc_plist = rb_define_class("PList", rb_cObject);
    rb_define_singleton_method(rbc_plist, "parse", rb_plist_parse, 1);
    rb_define_singleton_method(rbc_plist, "print_plist", rb_plist_print_plist, 2);
    rbc_gtk_mate = rb_define_class_under(rbc_gtk, "Mate", rb_cObject);
    rb_define_singleton_method(rbc_gtk_mate, "load_bundles", rb_gtk_mate_load_bundles, 0);
    rb_define_singleton_method(rbc_gtk_mate, "load_themes", rb_gtk_mate_load_themes, 0);
    rb_define_singleton_method(rbc_gtk_mate, "bundle_dirs", rb_gtk_mate_bundle_dirs, 0);
    rb_define_singleton_method(rbc_gtk_mate, "textmate_share_dir", rb_gtk_mate_textmate_share_dir, 0);
    VALUE rbc_gtk_mate_change_type = rb_define_class_under(rbc_gtk_mate, "ChangeType", rb_cObject);
    rb_define_const(rbc_gtk_mate_change_type, "INSERTION", INT2FIX(GTK_MATE_CHANGE_TYPE_INSERTION));
    rb_define_const(rbc_gtk_mate_change_type, "DELETION", INT2FIX(GTK_MATE_CHANGE_TYPE_DELETION));
    rbc_oniguruma = rb_define_class("Oniguruma", rb_cObject);
    rbc_plist_node = G_DEF_CLASS(plist_node_get_type(), "Node", rbc_plist);
    rb_define_method(rbc_plist_node, "initialize", plist_node_initialize, 0);
    rbc_plist_dict = G_DEF_CLASS(plist_dict_get_type(), "Dict", rbc_plist);
    rb_define_method(rbc_plist_dict, "initialize", plist_dict_initialize, 0);
    rb_define_method(rbc_plist_dict, "map", rb_plist_dict_get_map, 0);
    rb_define_method(rbc_plist_dict, "map=", rb_plist_dict_set_map, 1);
    rb_define_method(rbc_plist_dict, "get", rb_plist_dict_get, 1);
    rb_define_method(rbc_plist_dict, "keys", rb_plist_dict_keys, 0);
    rb_define_method(rbc_plist_dict, "print_keys", rb_plist_dict_print_keys, 0);
    rbc_plist_array = G_DEF_CLASS(plist_array_get_type(), "Array", rbc_plist);
    rb_define_method(rbc_plist_array, "initialize", plist_array_initialize, 0);
    rb_define_method(rbc_plist_array, "array", rb_plist_array_get_array, 0);
    rb_define_method(rbc_plist_array, "array=", rb_plist_array_set_array, 1);
    rb_define_method(rbc_plist_array, "get", rb_plist_array_get, 1);
    rbc_plist_string = G_DEF_CLASS(plist_string_get_type(), "String", rbc_plist);
    rb_define_method(rbc_plist_string, "initialize", plist_string_initialize, 0);
    rb_define_method(rbc_plist_string, "str", rb_plist_string_get_str, 0);
    rb_define_method(rbc_plist_string, "str=", rb_plist_string_set_str, 1);
    rbc_gtk_mate_view = G_DEF_CLASS(gtk_mate_view_get_type(), "View", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_view, "initialize", gtk_mate_view_initialize, 0);
    rbc_gtk_mate_theme = G_DEF_CLASS(gtk_mate_theme_get_type(), "Theme", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_theme, "initialize", gtk_mate_theme_initialize, 0);
    rb_define_singleton_method(rbc_gtk_mate_theme, "themes", rb_gtk_mate_theme_get_themes, 0);
    rb_define_singleton_method(rbc_gtk_mate_theme, "themes=", rb_gtk_mate_theme_set_themes, 1);
    rb_define_method(rbc_gtk_mate_theme, "author", rb_gtk_mate_theme_get_author, 0);
    rb_define_method(rbc_gtk_mate_theme, "author=", rb_gtk_mate_theme_set_author, 1);
    rb_define_method(rbc_gtk_mate_theme, "name", rb_gtk_mate_theme_get_name, 0);
    rb_define_method(rbc_gtk_mate_theme, "name=", rb_gtk_mate_theme_set_name, 1);
    rb_define_method(rbc_gtk_mate_theme, "global_settings", rb_gtk_mate_theme_get_global_settings, 0);
    rb_define_method(rbc_gtk_mate_theme, "global_settings=", rb_gtk_mate_theme_set_global_settings, 1);
    rb_define_method(rbc_gtk_mate_theme, "settings", rb_gtk_mate_theme_get_settings, 0);
    rb_define_method(rbc_gtk_mate_theme, "settings=", rb_gtk_mate_theme_set_settings, 1);
    rb_define_singleton_method(rbc_gtk_mate_theme, "create_from_plist", rb_gtk_mate_theme_create_from_plist, 1);
    rb_define_singleton_method(rbc_gtk_mate_theme, "theme_filenames", rb_gtk_mate_theme_theme_filenames, 0);
    rbc_gtk_mate_scope = G_DEF_CLASS(gtk_mate_scope_get_type(), "Scope", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_scope, "initialize", gtk_mate_scope_initialize, 0);
    rb_define_method(rbc_gtk_mate_scope, "pattern", rb_gtk_mate_scope_get_pattern, 0);
    rb_define_method(rbc_gtk_mate_scope, "pattern=", rb_gtk_mate_scope_set_pattern, 1);
    rb_define_method(rbc_gtk_mate_scope, "name", rb_gtk_mate_scope_get_name, 0);
    rb_define_method(rbc_gtk_mate_scope, "name=", rb_gtk_mate_scope_set_name, 1);
    rb_define_method(rbc_gtk_mate_scope, "open_match", rb_gtk_mate_scope_get_open_match, 0);
    rb_define_method(rbc_gtk_mate_scope, "open_match=", rb_gtk_mate_scope_set_open_match, 1);
    rb_define_method(rbc_gtk_mate_scope, "close_match", rb_gtk_mate_scope_get_close_match, 0);
    rb_define_method(rbc_gtk_mate_scope, "close_match=", rb_gtk_mate_scope_set_close_match, 1);
    rb_define_method(rbc_gtk_mate_scope, "closing_regex", rb_gtk_mate_scope_get_closing_regex, 0);
    rb_define_method(rbc_gtk_mate_scope, "closing_regex=", rb_gtk_mate_scope_set_closing_regex, 1);
    rb_define_method(rbc_gtk_mate_scope, "start_mark", rb_gtk_mate_scope_get_start_mark, 0);
    rb_define_method(rbc_gtk_mate_scope, "start_mark=", rb_gtk_mate_scope_set_start_mark, 1);
    rb_define_method(rbc_gtk_mate_scope, "inner_start_mark", rb_gtk_mate_scope_get_inner_start_mark, 0);
    rb_define_method(rbc_gtk_mate_scope, "inner_start_mark=", rb_gtk_mate_scope_set_inner_start_mark, 1);
    rb_define_method(rbc_gtk_mate_scope, "inner_end_mark", rb_gtk_mate_scope_get_inner_end_mark, 0);
    rb_define_method(rbc_gtk_mate_scope, "inner_end_mark=", rb_gtk_mate_scope_set_inner_end_mark, 1);
    rb_define_method(rbc_gtk_mate_scope, "end_mark", rb_gtk_mate_scope_get_end_mark, 0);
    rb_define_method(rbc_gtk_mate_scope, "end_mark=", rb_gtk_mate_scope_set_end_mark, 1);
    rb_define_method(rbc_gtk_mate_scope, "tag", rb_gtk_mate_scope_get_tag, 0);
    rb_define_method(rbc_gtk_mate_scope, "tag=", rb_gtk_mate_scope_set_tag, 1);
    rb_define_method(rbc_gtk_mate_scope, "inner_tag", rb_gtk_mate_scope_get_inner_tag, 0);
    rb_define_method(rbc_gtk_mate_scope, "inner_tag=", rb_gtk_mate_scope_set_inner_tag, 1);
    rb_define_method(rbc_gtk_mate_scope, "bg_color", rb_gtk_mate_scope_get_bg_color, 0);
    rb_define_method(rbc_gtk_mate_scope, "bg_color=", rb_gtk_mate_scope_set_bg_color, 1);
    rb_define_method(rbc_gtk_mate_scope, "is_capture", rb_gtk_mate_scope_get_is_capture, 0);
    rb_define_method(rbc_gtk_mate_scope, "is_capture=", rb_gtk_mate_scope_set_is_capture, 1);
    rb_define_method(rbc_gtk_mate_scope, "children", rb_gtk_mate_scope_get_children, 0);
    rb_define_method(rbc_gtk_mate_scope, "children=", rb_gtk_mate_scope_set_children, 1);
    rb_define_method(rbc_gtk_mate_scope, "parent", rb_gtk_mate_scope_get_parent, 0);
    rb_define_method(rbc_gtk_mate_scope, "parent=", rb_gtk_mate_scope_set_parent, 1);
    rb_define_method(rbc_gtk_mate_scope, "is_root", rb_gtk_mate_scope_is_root, 0);
    rb_define_method(rbc_gtk_mate_scope, "pretty", rb_gtk_mate_scope_pretty, 1);
    rbc_gtk_mate_buffer = G_DEF_CLASS(gtk_mate_buffer_get_type(), "Buffer", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_buffer, "initialize", gtk_mate_buffer_initialize, 0);
    rb_define_singleton_method(rbc_gtk_mate_buffer, "bundles", rb_gtk_mate_buffer_get_bundles, 0);
    rb_define_singleton_method(rbc_gtk_mate_buffer, "bundles=", rb_gtk_mate_buffer_set_bundles, 1);
    rb_define_singleton_method(rbc_gtk_mate_buffer, "themes", rb_gtk_mate_buffer_get_themes, 0);
    rb_define_singleton_method(rbc_gtk_mate_buffer, "themes=", rb_gtk_mate_buffer_set_themes, 1);
    rb_define_method(rbc_gtk_mate_buffer, "parser", rb_gtk_mate_buffer_get_parser, 0);
    rb_define_method(rbc_gtk_mate_buffer, "parser=", rb_gtk_mate_buffer_set_parser, 1);
    rb_define_method(rbc_gtk_mate_buffer, "set_grammar_by_name", rb_gtk_mate_buffer_set_grammar_by_name, 1);
    rb_define_method(rbc_gtk_mate_buffer, "set_grammar_by_extension", rb_gtk_mate_buffer_set_grammar_by_extension, 1);
    rbc_gtk_mate_parser = G_DEF_CLASS(gtk_mate_parser_get_type(), "Parser", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_parser, "initialize", gtk_mate_parser_initialize, 0);
    rb_define_method(rbc_gtk_mate_parser, "root", rb_gtk_mate_parser_get_root, 0);
    rb_define_method(rbc_gtk_mate_parser, "root=", rb_gtk_mate_parser_set_root, 1);
    rb_define_singleton_method(rbc_gtk_mate_parser, "current", rb_gtk_mate_parser_get_current, 0);
    rb_define_singleton_method(rbc_gtk_mate_parser, "current=", rb_gtk_mate_parser_set_current, 1);
    rb_define_method(rbc_gtk_mate_parser, "make_root", rb_gtk_mate_parser_make_root, 0);
    rb_define_method(rbc_gtk_mate_parser, "connect_buffer_signals", rb_gtk_mate_parser_connect_buffer_signals, 0);
    rb_define_singleton_method(rbc_gtk_mate_parser, "create", rb_gtk_mate_parser_create, 2);
    rbc_gtk_mate_bundle = G_DEF_CLASS(gtk_mate_bundle_get_type(), "Bundle", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_bundle, "initialize", gtk_mate_bundle_initialize, 1);
    rb_define_method(rbc_gtk_mate_bundle, "grammars", rb_gtk_mate_bundle_get_grammars, 0);
    rb_define_method(rbc_gtk_mate_bundle, "grammars=", rb_gtk_mate_bundle_set_grammars, 1);
    rbc_oniguruma_match = G_DEF_CLASS(oniguruma_match_get_type(), "Match", rbc_oniguruma);
    rb_define_method(rbc_oniguruma_match, "initialize", oniguruma_match_initialize, 0);
    rb_define_method(rbc_oniguruma_match, "begin", rb_oniguruma_match_begin, 1);
    rb_define_method(rbc_oniguruma_match, "end", rb_oniguruma_match_end, 1);
    rbc_oniguruma_regex = G_DEF_CLASS(oniguruma_regex_get_type(), "Regex", rbc_oniguruma);
    rb_define_method(rbc_oniguruma_regex, "initialize", oniguruma_regex_initialize, 0);
    rb_define_method(rbc_oniguruma_regex, "search", rb_oniguruma_regex_search, 3);
    rb_define_singleton_method(rbc_oniguruma_regex, "make1", rb_oniguruma_regex_make1, 1);
    rbc_gtk_mate_grammar = G_DEF_CLASS(gtk_mate_grammar_get_type(), "Grammar", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_grammar, "initialize", gtk_mate_grammar_initialize, 1);
    rb_define_method(rbc_gtk_mate_grammar, "file_types", rb_gtk_mate_grammar_get_file_types, 0);
    rb_define_method(rbc_gtk_mate_grammar, "file_types=", rb_gtk_mate_grammar_set_file_types, 1);
    rb_define_method(rbc_gtk_mate_grammar, "first_line_match", rb_gtk_mate_grammar_get_first_line_match, 0);
    rb_define_method(rbc_gtk_mate_grammar, "first_line_match=", rb_gtk_mate_grammar_set_first_line_match, 1);
    rb_define_method(rbc_gtk_mate_grammar, "key_equivalent", rb_gtk_mate_grammar_get_key_equivalent, 0);
    rb_define_method(rbc_gtk_mate_grammar, "key_equivalent=", rb_gtk_mate_grammar_set_key_equivalent, 1);
    rb_define_method(rbc_gtk_mate_grammar, "scope_name", rb_gtk_mate_grammar_get_scope_name, 0);
    rb_define_method(rbc_gtk_mate_grammar, "scope_name=", rb_gtk_mate_grammar_set_scope_name, 1);
    rb_define_method(rbc_gtk_mate_grammar, "comment", rb_gtk_mate_grammar_get_comment, 0);
    rb_define_method(rbc_gtk_mate_grammar, "comment=", rb_gtk_mate_grammar_set_comment, 1);
    rb_define_method(rbc_gtk_mate_grammar, "all_patterns", rb_gtk_mate_grammar_get_all_patterns, 0);
    rb_define_method(rbc_gtk_mate_grammar, "all_patterns=", rb_gtk_mate_grammar_set_all_patterns, 1);
    rb_define_method(rbc_gtk_mate_grammar, "loaded", rb_gtk_mate_grammar_get_loaded, 0);
    rb_define_method(rbc_gtk_mate_grammar, "loaded=", rb_gtk_mate_grammar_set_loaded, 1);
    rb_define_method(rbc_gtk_mate_grammar, "folding_start_marker", rb_gtk_mate_grammar_get_folding_start_marker, 0);
    rb_define_method(rbc_gtk_mate_grammar, "folding_start_marker=", rb_gtk_mate_grammar_set_folding_start_marker, 1);
    rb_define_method(rbc_gtk_mate_grammar, "folding_stop_marker", rb_gtk_mate_grammar_get_folding_stop_marker, 0);
    rb_define_method(rbc_gtk_mate_grammar, "folding_stop_marker=", rb_gtk_mate_grammar_set_folding_stop_marker, 1);
    rb_define_method(rbc_gtk_mate_grammar, "patterns", rb_gtk_mate_grammar_get_patterns, 0);
    rb_define_method(rbc_gtk_mate_grammar, "patterns=", rb_gtk_mate_grammar_set_patterns, 1);
    rb_define_method(rbc_gtk_mate_grammar, "repository", rb_gtk_mate_grammar_get_repository, 0);
    rb_define_method(rbc_gtk_mate_grammar, "repository=", rb_gtk_mate_grammar_set_repository, 1);
    rb_define_method(rbc_gtk_mate_grammar, "init_for_reference", rb_gtk_mate_grammar_init_for_reference, 0);
    rb_define_method(rbc_gtk_mate_grammar, "init_for_use", rb_gtk_mate_grammar_init_for_use, 0);
    rbc_gtk_mate_pattern = G_DEF_CLASS(gtk_mate_pattern_get_type(), "Pattern", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_pattern, "initialize", gtk_mate_pattern_initialize, 0);
    rb_define_method(rbc_gtk_mate_pattern, "name", rb_gtk_mate_pattern_get_name, 0);
    rb_define_method(rbc_gtk_mate_pattern, "name=", rb_gtk_mate_pattern_set_name, 1);
    rb_define_method(rbc_gtk_mate_pattern, "comment", rb_gtk_mate_pattern_get_comment, 0);
    rb_define_method(rbc_gtk_mate_pattern, "comment=", rb_gtk_mate_pattern_set_comment, 1);
    rb_define_singleton_method(rbc_gtk_mate_pattern, "all_patterns", rb_gtk_mate_pattern_get_all_patterns, 0);
    rb_define_singleton_method(rbc_gtk_mate_pattern, "all_patterns=", rb_gtk_mate_pattern_set_all_patterns, 1);
    rb_define_singleton_method(rbc_gtk_mate_pattern, "create_from_plist", rb_gtk_mate_pattern_create_from_plist, 2);
    rb_define_singleton_method(rbc_gtk_mate_pattern, "make_captures_from_plist", rb_gtk_mate_pattern_make_captures_from_plist, 1);
    rbc_oniguruma_onig_error = G_DEF_CLASS(oniguruma_onig_error_get_type(), "OnigError", rbc_oniguruma);
    rb_define_method(rbc_oniguruma_onig_error, "initialize", oniguruma_onig_error_initialize, 0);
    rb_define_method(rbc_oniguruma_onig_error, "code", rb_oniguruma_onig_error_get_code, 0);
    rb_define_method(rbc_oniguruma_onig_error, "code=", rb_oniguruma_onig_error_set_code, 1);
    rbc_gtk_mate_theme_setting = G_DEF_CLASS(gtk_mate_theme_setting_get_type(), "ThemeSetting", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_theme_setting, "initialize", gtk_mate_theme_setting_initialize, 0);
    rb_define_method(rbc_gtk_mate_theme_setting, "name", rb_gtk_mate_theme_setting_get_name, 0);
    rb_define_method(rbc_gtk_mate_theme_setting, "name=", rb_gtk_mate_theme_setting_set_name, 1);
    rb_define_method(rbc_gtk_mate_theme_setting, "scope", rb_gtk_mate_theme_setting_get_scope, 0);
    rb_define_method(rbc_gtk_mate_theme_setting, "scope=", rb_gtk_mate_theme_setting_set_scope, 1);
    rb_define_method(rbc_gtk_mate_theme_setting, "settings", rb_gtk_mate_theme_setting_get_settings, 0);
    rb_define_method(rbc_gtk_mate_theme_setting, "settings=", rb_gtk_mate_theme_setting_set_settings, 1);
    rb_define_singleton_method(rbc_gtk_mate_theme_setting, "create_from_plist", rb_gtk_mate_theme_setting_create_from_plist, 1);
    rbc_gtk_mate_single_pattern = G_DEF_CLASS(gtk_mate_single_pattern_get_type(), "SinglePattern", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_single_pattern, "initialize", gtk_mate_single_pattern_initialize, 0);
    rb_define_method(rbc_gtk_mate_single_pattern, "match", rb_gtk_mate_single_pattern_get_match, 0);
    rb_define_method(rbc_gtk_mate_single_pattern, "match=", rb_gtk_mate_single_pattern_set_match, 1);
    rb_define_method(rbc_gtk_mate_single_pattern, "captures", rb_gtk_mate_single_pattern_get_captures, 0);
    rb_define_method(rbc_gtk_mate_single_pattern, "captures=", rb_gtk_mate_single_pattern_set_captures, 1);
    rb_define_singleton_method(rbc_gtk_mate_single_pattern, "create_from_plist", rb_gtk_mate_single_pattern_create_from_plist, 2);
    rbc_gtk_mate_double_pattern = G_DEF_CLASS(gtk_mate_double_pattern_get_type(), "DoublePattern", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_double_pattern, "initialize", gtk_mate_double_pattern_initialize, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "begin", rb_gtk_mate_double_pattern_get_begin, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "begin=", rb_gtk_mate_double_pattern_set_begin, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "end", rb_gtk_mate_double_pattern_get_end, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "end=", rb_gtk_mate_double_pattern_set_end, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "begin_string", rb_gtk_mate_double_pattern_get_begin_string, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "begin_string=", rb_gtk_mate_double_pattern_set_begin_string, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "begin_captures", rb_gtk_mate_double_pattern_get_begin_captures, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "begin_captures=", rb_gtk_mate_double_pattern_set_begin_captures, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "end_captures", rb_gtk_mate_double_pattern_get_end_captures, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "end_captures=", rb_gtk_mate_double_pattern_set_end_captures, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "patterns", rb_gtk_mate_double_pattern_get_patterns, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "patterns=", rb_gtk_mate_double_pattern_set_patterns, 1);
    rb_define_singleton_method(rbc_gtk_mate_double_pattern, "create_from_plist", rb_gtk_mate_double_pattern_create_from_plist, 2);
    rb_define_method(rbc_gtk_mate_double_pattern, "replace_include_patterns", rb_gtk_mate_double_pattern_replace_include_patterns, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "replace_repository_includes", rb_gtk_mate_double_pattern_replace_repository_includes, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "replace_base_and_self_includes", rb_gtk_mate_double_pattern_replace_base_and_self_includes, 1);
    rbc_gtk_mate_include_pattern = G_DEF_CLASS(gtk_mate_include_pattern_get_type(), "IncludePattern", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_include_pattern, "initialize", gtk_mate_include_pattern_initialize, 0);
    rb_define_singleton_method(rbc_gtk_mate_include_pattern, "create_from_plist", rb_gtk_mate_include_pattern_create_from_plist, 1);
}
