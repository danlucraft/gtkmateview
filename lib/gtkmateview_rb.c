#include "ruby.h"
#include "rbgtk.h"
#include "pattern.h"
#include "view.h"
#include "grammar.h"
#include "gtkmateview.h"
#include "buffer.h"
#include "bundle.h"
#include "onig_wrap.h"
#include "plist.h"
static VALUE rb_vala_error, rbc_gtk;

/****  Gtk wrapper *****/

#define _GTK_SELF(s) GTK(RVAL2GOBJ(s))
static VALUE rbc_gtk;

/****  Gtk.Mate wrapper *****/

#define _GTK_MATE_SELF(s) GTK_MATE(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate;

/****  Gtk.Mate.Pattern wrapper *****/

#define _GTK_MATE_PATTERN_SELF(s) GTK_MATE_PATTERN(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_pattern;

/****  Gtk.Mate.SinglePattern wrapper *****/

#define _GTK_MATE_SINGLE_PATTERN_SELF(s) GTK_MATE_SINGLE_PATTERN(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_single_pattern;

/****  Gtk.Mate.DoublePattern wrapper *****/

#define _GTK_MATE_DOUBLE_PATTERN_SELF(s) GTK_MATE_DOUBLE_PATTERN(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_double_pattern;

/****  Gtk.Mate.IncludePattern wrapper *****/

#define _GTK_MATE_INCLUDE_PATTERN_SELF(s) GTK_MATE_INCLUDE_PATTERN(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_include_pattern;

/****  Gtk.Mate.View wrapper *****/

#define _GTK_MATE_VIEW_SELF(s) GTK_MATE_VIEW(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_view;

/****  Gtk.Mate.Grammar wrapper *****/

#define _GTK_MATE_GRAMMAR_SELF(s) GTK_MATE_GRAMMAR(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_grammar;

/****  Gtk.Mate.Theme wrapper *****/

#define _GTK_MATE_THEME_SELF(s) GTK_MATE_THEME(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_theme;

/****  Gtk.Mate.Buffer wrapper *****/

#define _GTK_MATE_BUFFER_SELF(s) GTK_MATE_BUFFER(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_buffer;

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


    
    int _c_return;
    _c_return = gtk_mate_load_bundles();
    VALUE _rb_return;                                       // Method#return_type_conversion
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_bundle_dirs(VALUE self) {


    
    GeeArrayList* _c_return;
    _c_return = gtk_mate_bundle_dirs();
    VALUE _rb_return;                                       // Method#return_type_conversion
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

    return _rb_return;
}

static VALUE rb_gtk_mate_textmate_share_dir(VALUE self) {


    
    char * _c_return;
    _c_return = gtk_mate_textmate_share_dir();
    VALUE _rb_return;                                           // Method#return_type_conversion
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


/****  Gtk.Mate.Pattern methods *****/


static VALUE gtk_mate_pattern_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_pattern_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_pattern_get_name(VALUE self) {
    GtkMatePattern* gtk_mate_pattern = RVAL2GOBJ(self);


    char * _c_return = gtk_mate_pattern->name; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
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
    if (TYPE(name) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    char * _c_name;
    _c_name = g_strdup(STR2CSTR(name));
    gtk_mate_pattern->name = _c_name;  // ValaMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_pattern_get_comment(VALUE self) {
    GtkMatePattern* gtk_mate_pattern = RVAL2GOBJ(self);


    char * _c_return = gtk_mate_pattern->comment; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
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
    if (TYPE(comment) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    char * _c_comment;
    _c_comment = g_strdup(STR2CSTR(comment));
    gtk_mate_pattern->comment = _c_comment;  // ValaMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_pattern_get_all_patterns(VALUE self) {


    GeeArrayList* _c_return = gtk_mate_pattern_all_patterns; // StaticMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
        int it_val3;
    _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
    for (it_val3 = 0; it_val3 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val3 = it_val3 + 1) {
        GtkMatePattern* i_val4;
        i_val4 =  (gee_list_get (GEE_LIST (_c_return), it_val3));
        VALUE rb_ival4;
        rb_ival4 = GOBJ2RVAL(i_val4);
        rb_ary_store (_rb_return, it_val3, rb_ival4);
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_pattern_set_all_patterns(VALUE self, VALUE all_patterns) {
    if (TYPE(all_patterns) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    GeeArrayList* _c_all_patterns;
        int len_val5 = RARRAY_LEN(all_patterns);
    _c_all_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val5; i++) {
            VALUE _rb_el = rb_ary_entry(all_patterns, (long) i);
            GtkMatePattern* _c_el = _GTK_MATE_PATTERN_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_all_patterns), (_c_el));
        }
    }

    gtk_mate_pattern_all_patterns = _c_all_patterns; // StaticMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_pattern_create_from_plist(VALUE self, VALUE pd) {

    PListDict* _c_pd;
    _c_pd = _PLIST_DICT_SELF(pd);
    
    GtkMatePattern* _c_return;
    _c_return = gtk_mate_pattern_create_from_plist(_c_pd);
    VALUE _rb_return;                                           // Method#return_type_conversion
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
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


    OnigurumaRegex* _c_return = gtk_mate_single_pattern->match; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_single_pattern_set_match(VALUE self, VALUE match) {
    GtkMateSinglePattern* gtk_mate_single_pattern = RVAL2GOBJ(self);

    OnigurumaRegex* _c_match;
    _c_match = _ONIGURUMA_REGEX_SELF(match);
    gtk_mate_single_pattern->match = _c_match;  // ValaMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_single_pattern_create_from_plist(VALUE self, VALUE pd) {

    PListDict* _c_pd;
    _c_pd = _PLIST_DICT_SELF(pd);
    
    GtkMateSinglePattern* _c_return;
    _c_return = gtk_mate_single_pattern_create_from_plist(_c_pd);
    VALUE _rb_return;                                           // Method#return_type_conversion
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


    OnigurumaRegex* _c_return = gtk_mate_double_pattern->begin; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_double_pattern_set_begin(VALUE self, VALUE begin) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);

    OnigurumaRegex* _c_begin;
    _c_begin = _ONIGURUMA_REGEX_SELF(begin);
    gtk_mate_double_pattern->begin = _c_begin;  // ValaMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_double_pattern_get_end(VALUE self) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);


    OnigurumaRegex* _c_return = gtk_mate_double_pattern->end; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_double_pattern_set_end(VALUE self, VALUE end) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);

    OnigurumaRegex* _c_end;
    _c_end = _ONIGURUMA_REGEX_SELF(end);
    gtk_mate_double_pattern->end = _c_end;  // ValaMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_double_pattern_get_patterns(VALUE self) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);


    GeeArrayList* _c_return = gtk_mate_double_pattern->patterns; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
        int it_val6;
    _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
    for (it_val6 = 0; it_val6 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val6 = it_val6 + 1) {
        GtkMatePattern* i_val7;
        i_val7 =  (gee_list_get (GEE_LIST (_c_return), it_val6));
        VALUE rb_ival7;
        rb_ival7 = GOBJ2RVAL(i_val7);
        rb_ary_store (_rb_return, it_val6, rb_ival7);
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_double_pattern_set_patterns(VALUE self, VALUE patterns) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    if (TYPE(patterns) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    GeeArrayList* _c_patterns;
        int len_val8 = RARRAY_LEN(patterns);
    _c_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val8; i++) {
            VALUE _rb_el = rb_ary_entry(patterns, (long) i);
            GtkMatePattern* _c_el = _GTK_MATE_PATTERN_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_patterns), (_c_el));
        }
    }

    gtk_mate_double_pattern->patterns = _c_patterns;  // ValaMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_double_pattern_create_from_plist(VALUE self, VALUE pd) {

    PListDict* _c_pd;
    _c_pd = _PLIST_DICT_SELF(pd);
    
    GtkMateDoublePattern* _c_return;
    _c_return = gtk_mate_double_pattern_create_from_plist(_c_pd);
    VALUE _rb_return;                                           // Method#return_type_conversion
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}


/****  Gtk.Mate.IncludePattern methods *****/


static VALUE gtk_mate_include_pattern_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_include_pattern_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_include_pattern_create_from_plist(VALUE self, VALUE pd) {

    PListDict* _c_pd;
    _c_pd = _PLIST_DICT_SELF(pd);
    
    GtkMateIncludePattern* _c_return;
    _c_return = gtk_mate_include_pattern_create_from_plist(_c_pd);
    VALUE _rb_return;                                           // Method#return_type_conversion
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}


/****  Gtk.Mate.View methods *****/


static VALUE gtk_mate_view_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_view_new ());
    return Qnil;
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


    GeeArrayList* _c_return = gtk_mate_grammar->file_types; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
        int it_val9;
    _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
    for (it_val9 = 0; it_val9 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val9 = it_val9 + 1) {
        char * i_val10;
        i_val10 = (char *) (gee_list_get (GEE_LIST (_c_return), it_val9));
        VALUE rb_ival10;
              if (i_val10 == NULL) {
        rb_ival10 = Qnil;
      }
      else {
        rb_ival10 = rb_str_new2(i_val10);
      }

        rb_ary_store (_rb_return, it_val9, rb_ival10);
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_file_types(VALUE self, VALUE file_types) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    if (TYPE(file_types) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    GeeArrayList* _c_file_types;
        int len_val11 = RARRAY_LEN(file_types);
    _c_file_types = gee_array_list_new (G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val11; i++) {
            VALUE _rb_el = rb_ary_entry(file_types, (long) i);
            char * _c_el = g_strdup(STR2CSTR(_rb_el));
            gee_collection_add (GEE_COLLECTION (_c_file_types), (_c_el));
        }
    }

    gtk_mate_grammar->file_types = _c_file_types;  // ValaMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_first_line_match(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);


    OnigurumaRegex* _c_return = gtk_mate_grammar->first_line_match; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_first_line_match(VALUE self, VALUE first_line_match) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);

    OnigurumaRegex* _c_first_line_match;
    _c_first_line_match = _ONIGURUMA_REGEX_SELF(first_line_match);
    gtk_mate_grammar->first_line_match = _c_first_line_match;  // ValaMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_key_equivalent(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);


    char * _c_return = gtk_mate_grammar->key_equivalent; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
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
    if (TYPE(key_equivalent) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    char * _c_key_equivalent;
    _c_key_equivalent = g_strdup(STR2CSTR(key_equivalent));
    gtk_mate_grammar->key_equivalent = _c_key_equivalent;  // ValaMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_scope_name(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);


    char * _c_return = gtk_mate_grammar->scope_name; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
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
    if (TYPE(scope_name) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    char * _c_scope_name;
    _c_scope_name = g_strdup(STR2CSTR(scope_name));
    gtk_mate_grammar->scope_name = _c_scope_name;  // ValaMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_comment(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);


    char * _c_return = gtk_mate_grammar->comment; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
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
    if (TYPE(comment) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    char * _c_comment;
    _c_comment = g_strdup(STR2CSTR(comment));
    gtk_mate_grammar->comment = _c_comment;  // ValaMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_loaded(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);


    gboolean _c_return = gtk_mate_grammar->loaded; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_loaded(VALUE self, VALUE loaded) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    if (TYPE(loaded) != T_TRUE && TYPE(loaded) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    gboolean _c_loaded;
          if (loaded == Qtrue)
          _c_loaded = TRUE;
      else
          _c_loaded = FALSE;

    gtk_mate_grammar->loaded = _c_loaded;  // ValaMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_folding_start_marker(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);


    OnigurumaRegex* _c_return = gtk_mate_grammar->folding_start_marker; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_folding_start_marker(VALUE self, VALUE folding_start_marker) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);

    OnigurumaRegex* _c_folding_start_marker;
    _c_folding_start_marker = _ONIGURUMA_REGEX_SELF(folding_start_marker);
    gtk_mate_grammar->folding_start_marker = _c_folding_start_marker;  // ValaMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_folding_stop_marker(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);


    OnigurumaRegex* _c_return = gtk_mate_grammar->folding_stop_marker; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_folding_stop_marker(VALUE self, VALUE folding_stop_marker) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);

    OnigurumaRegex* _c_folding_stop_marker;
    _c_folding_stop_marker = _ONIGURUMA_REGEX_SELF(folding_stop_marker);
    gtk_mate_grammar->folding_stop_marker = _c_folding_stop_marker;  // ValaMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_patterns(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);


    GeeArrayList* _c_return = gtk_mate_grammar->patterns; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
        int it_val12;
    _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
    for (it_val12 = 0; it_val12 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val12 = it_val12 + 1) {
        GtkMatePattern* i_val13;
        i_val13 =  (gee_list_get (GEE_LIST (_c_return), it_val12));
        VALUE rb_ival13;
        rb_ival13 = GOBJ2RVAL(i_val13);
        rb_ary_store (_rb_return, it_val12, rb_ival13);
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_patterns(VALUE self, VALUE patterns) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    if (TYPE(patterns) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    GeeArrayList* _c_patterns;
        int len_val14 = RARRAY_LEN(patterns);
    _c_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val14; i++) {
            VALUE _rb_el = rb_ary_entry(patterns, (long) i);
            GtkMatePattern* _c_el = _GTK_MATE_PATTERN_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_patterns), (_c_el));
        }
    }

    gtk_mate_grammar->patterns = _c_patterns;  // ValaMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_grammar_init_for_reference(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);


    
    gtk_mate_grammar_init_for_reference(gtk_mate_grammar);

    return Qnil;
}

static VALUE rb_gtk_mate_grammar_init_for_use(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);


    
    gtk_mate_grammar_init_for_use(gtk_mate_grammar);

    return Qnil;
}

static VALUE rb_gtk_mate_grammar_replace_include_patterns(VALUE self, VALUE pattern, VALUE ps) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    if (TYPE(ps) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    GtkMateDoublePattern* _c_pattern;
    if (pattern == Qnil)
        _c_pattern = NULL;
    else {
        _c_pattern = _GTK_MATE_DOUBLE_PATTERN_SELF(pattern);
    }
    GeeArrayList* _c_ps;
        int len_val15 = RARRAY_LEN(ps);
    _c_ps = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val15; i++) {
            VALUE _rb_el = rb_ary_entry(ps, (long) i);
            GtkMatePattern* _c_el = _GTK_MATE_PATTERN_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_ps), (_c_el));
        }
    }

    
    gtk_mate_grammar_replace_include_patterns(gtk_mate_grammar, _c_pattern, _c_ps);

    return Qnil;
}


/****  Gtk.Mate.Theme methods *****/


static VALUE gtk_mate_theme_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_theme_new ());
    return Qnil;
}


/****  Gtk.Mate.Buffer methods *****/


static VALUE gtk_mate_buffer_initialize(VALUE self) {

    G_INITIALIZE(self, gtk_mate_buffer_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_buffer_get_bundles(VALUE self) {


    GeeArrayList* _c_return = gtk_mate_buffer_bundles; // StaticMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
        int it_val16;
    _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
    for (it_val16 = 0; it_val16 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val16 = it_val16 + 1) {
        GtkMateBundle* i_val17;
        i_val17 =  (gee_list_get (GEE_LIST (_c_return), it_val16));
        VALUE rb_ival17;
        rb_ival17 = GOBJ2RVAL(i_val17);
        rb_ary_store (_rb_return, it_val16, rb_ival17);
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_buffer_set_bundles(VALUE self, VALUE bundles) {
    if (TYPE(bundles) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    GeeArrayList* _c_bundles;
        int len_val18 = RARRAY_LEN(bundles);
    _c_bundles = gee_array_list_new (GTK_MATE_TYPE_BUNDLE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val18; i++) {
            VALUE _rb_el = rb_ary_entry(bundles, (long) i);
            GtkMateBundle* _c_el = _GTK_MATE_BUNDLE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_bundles), (_c_el));
        }
    }

    gtk_mate_buffer_bundles = _c_bundles; // StaticMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_buffer_get_themes(VALUE self) {


    GeeArrayList* _c_return = gtk_mate_buffer_themes; // StaticMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
        int it_val19;
    _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
    for (it_val19 = 0; it_val19 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val19 = it_val19 + 1) {
        GtkMateTheme* i_val20;
        i_val20 =  (gee_list_get (GEE_LIST (_c_return), it_val19));
        VALUE rb_ival20;
        rb_ival20 = GOBJ2RVAL(i_val20);
        rb_ary_store (_rb_return, it_val19, rb_ival20);
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_buffer_set_themes(VALUE self, VALUE themes) {
    if (TYPE(themes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    GeeArrayList* _c_themes;
        int len_val21 = RARRAY_LEN(themes);
    _c_themes = gee_array_list_new (GTK_MATE_TYPE_THEME, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val21; i++) {
            VALUE _rb_el = rb_ary_entry(themes, (long) i);
            GtkMateTheme* _c_el = _GTK_MATE_THEME_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_themes), (_c_el));
        }
    }

    gtk_mate_buffer_themes = _c_themes; // StaticMemberSet#body

    return Qnil;
}

static VALUE rb_gtk_mate_buffer_set_grammar_by_extension(VALUE self, VALUE extension) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    if (TYPE(extension) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    char * _c_extension;
    _c_extension = g_strdup(STR2CSTR(extension));
    
    char * _c_return;
    _c_return = gtk_mate_buffer_set_grammar_by_extension(gtk_mate_buffer, _c_extension);
    VALUE _rb_return;                                           // Method#return_type_conversion
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


/****  Gtk.Mate.Bundle methods *****/


static VALUE gtk_mate_bundle_initialize(VALUE self, VALUE name) {
    char * _c_name;
    _c_name = g_strdup(STR2CSTR(name));

    RBGTK_INITIALIZE(self, gtk_mate_bundle_new (_c_name));
    return Qnil;
}

static VALUE rb_gtk_mate_bundle_get_grammars(VALUE self) {
    GtkMateBundle* gtk_mate_bundle = RVAL2GOBJ(self);


    GeeArrayList* _c_return = gtk_mate_bundle->grammars; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
        int it_val22;
    _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
    for (it_val22 = 0; it_val22 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val22 = it_val22 + 1) {
        GtkMateGrammar* i_val23;
        i_val23 =  (gee_list_get (GEE_LIST (_c_return), it_val22));
        VALUE rb_ival23;
        rb_ival23 = GOBJ2RVAL(i_val23);
        rb_ary_store (_rb_return, it_val22, rb_ival23);
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_bundle_set_grammars(VALUE self, VALUE grammars) {
    GtkMateBundle* gtk_mate_bundle = RVAL2GOBJ(self);
    if (TYPE(grammars) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    GeeArrayList* _c_grammars;
        int len_val24 = RARRAY_LEN(grammars);
    _c_grammars = gee_array_list_new (GTK_MATE_TYPE_GRAMMAR, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val24; i++) {
            VALUE _rb_el = rb_ary_entry(grammars, (long) i);
            GtkMateGrammar* _c_el = _GTK_MATE_GRAMMAR_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_grammars), (_c_el));
        }
    }

    gtk_mate_bundle->grammars = _c_grammars;  // ValaMemberSet#body

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


    int _c_return = oniguruma_onig_error->code; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_oniguruma_onig_error_set_code(VALUE self, VALUE code) {
    OnigurumaOnigError* oniguruma_onig_error = RVAL2GOBJ(self);
    if (TYPE(code) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    int _c_code;
    _c_code = FIX2INT(code);
    oniguruma_onig_error->code = _c_code;  // ValaMemberSet#body

    return Qnil;
}


/****  Oniguruma.Match methods *****/


static VALUE oniguruma_match_initialize(VALUE self) {

    G_INITIALIZE(self, oniguruma_match_new ());
    return Qnil;
}

static VALUE rb_oniguruma_match_begin(VALUE self, VALUE capture) {
    OnigurumaMatch* oniguruma_match = RVAL2GOBJ(self);
    if (TYPE(capture) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    int _c_capture;
    _c_capture = FIX2INT(capture);
    
    int _c_return;
    _c_return = oniguruma_match_begin(oniguruma_match, _c_capture);
    VALUE _rb_return;                                       // Method#return_type_conversion
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_oniguruma_match_end(VALUE self, VALUE capture) {
    OnigurumaMatch* oniguruma_match = RVAL2GOBJ(self);
    if (TYPE(capture) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    int _c_capture;
    _c_capture = FIX2INT(capture);
    
    int _c_return;
    _c_return = oniguruma_match_end(oniguruma_match, _c_capture);
    VALUE _rb_return;                                       // Method#return_type_conversion
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
    char * _c_target;
    _c_target = g_strdup(STR2CSTR(target));
    int _c_start;
    _c_start = FIX2INT(start);
    int _c_end;
    _c_end = FIX2INT(end);
    
    OnigurumaMatch* _c_return;
    _c_return = oniguruma_regex_search(oniguruma_regex, _c_target, _c_start, _c_end);
    VALUE _rb_return;                                           // Method#return_type_conversion
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}

static VALUE rb_oniguruma_regex_make1(VALUE self, VALUE pattern) {
    if (TYPE(pattern) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    char * _c_pattern;
    _c_pattern = g_strdup(STR2CSTR(pattern));
    
    OnigurumaRegex* _c_return;
    _c_return = oniguruma_regex_make1(_c_pattern);
    VALUE _rb_return;                                           // Method#return_type_conversion
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}


/****  PList methods *****/

static VALUE rb_plist_parse(VALUE self, VALUE filename) {
    if (TYPE(filename) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    char * _c_filename;
    _c_filename = g_strdup(STR2CSTR(filename));
    GError* inner_error;
    inner_error = NULL;
    
    PListDict* _c_return;
    _c_return = plist_parse(_c_filename, &inner_error);
    if (inner_error != NULL) {
        if (inner_error->domain == XML_ERROR) {
            rb_raise(rb_vala_error, "[XmlError]: %s", inner_error->message);
        }
    }
    VALUE _rb_return;                                       // Method#return_type_conversion
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_plist_print_plist(VALUE self, VALUE indent, VALUE node) {
    if (TYPE(indent) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    int _c_indent;
    _c_indent = FIX2INT(indent);
    PListNode* _c_node;
    _c_node = _PLIST_NODE_SELF(node);
    
    plist_print_plist(_c_indent, _c_node);

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


    char * _c_return = plist_string->str; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
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
    if (TYPE(str) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    char * _c_str;
    _c_str = g_strdup(STR2CSTR(str));
    plist_string->str = _c_str;  // ValaMemberSet#body

    return Qnil;
}


/****  PList.Array methods *****/


static VALUE plist_array_initialize(VALUE self) {

    G_INITIALIZE(self, plist_array_new ());
    return Qnil;
}

static VALUE rb_plist_array_get_array(VALUE self) {
    PListArray* plist_array = RVAL2GOBJ(self);


    GeeArrayList* _c_return = plist_array->array; // ValaMemberGet#body
    VALUE _rb_return;                                       // Method#return_type_conversion
        int it_val25;
    _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
    for (it_val25 = 0; it_val25 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val25 = it_val25 + 1) {
        PListNode* i_val26;
        i_val26 =  (gee_list_get (GEE_LIST (_c_return), it_val25));
        VALUE rb_ival26;
        rb_ival26 = GOBJ2RVAL(i_val26);
        rb_ary_store (_rb_return, it_val25, rb_ival26);
    }

    return _rb_return;
}

static VALUE rb_plist_array_set_array(VALUE self, VALUE array) {
    PListArray* plist_array = RVAL2GOBJ(self);
    if (TYPE(array) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    GeeArrayList* _c_array;
        int len_val27 = RARRAY_LEN(array);
    _c_array = gee_array_list_new (PLIST_TYPE_NODE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val27; i++) {
            VALUE _rb_el = rb_ary_entry(array, (long) i);
            PListNode* _c_el = _PLIST_NODE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_array), (_c_el));
        }
    }

    plist_array->array = _c_array;  // ValaMemberSet#body

    return Qnil;
}

static VALUE rb_plist_array_get(VALUE self, VALUE ix) {
    PListArray* plist_array = RVAL2GOBJ(self);
    if (TYPE(ix) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    int _c_ix;
    _c_ix = FIX2INT(ix);
    
    PListNode* _c_return;
    _c_return = plist_array_get(plist_array, _c_ix);
    VALUE _rb_return;                                       // Method#return_type_conversion
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}


/****  PList.Dict methods *****/


static VALUE plist_dict_initialize(VALUE self) {

    G_INITIALIZE(self, plist_dict_new ());
    return Qnil;
}

static VALUE rb_plist_dict_get(VALUE self, VALUE key) {
    PListDict* plist_dict = RVAL2GOBJ(self);
    if (TYPE(key) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    char * _c_key;
    _c_key = g_strdup(STR2CSTR(key));
    
    PListNode* _c_return;
    _c_return = plist_dict_get(plist_dict, _c_key);
    VALUE _rb_return;                                       // Method#return_type_conversion
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_plist_dict_keys(VALUE self) {
    PListDict* plist_dict = RVAL2GOBJ(self);


              int _rb_return__length;

    char** _c_return;
    _c_return = plist_dict_keys(plist_dict, &_rb_return__length);
    VALUE _rb_return;                                       // Method#return_type_conversion
              _rb_return = rb_ary_new2(_rb_return__length);
          long val28;
          for(val28 = 0; val28 < _rb_return__length; val28++) {
              rb_ary_store(_rb_return, val28, rb_str_new2(_c_return[val28]));
              g_free(_c_return[val28]);
          }

    return _rb_return;
}

static VALUE rb_plist_dict_print_keys(VALUE self) {
    PListDict* plist_dict = RVAL2GOBJ(self);


    
    plist_dict_print_keys(plist_dict);

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
    rb_define_singleton_method(rbc_gtk_mate, "bundle_dirs", rb_gtk_mate_bundle_dirs, 0);
    rb_define_singleton_method(rbc_gtk_mate, "textmate_share_dir", rb_gtk_mate_textmate_share_dir, 0);
    rbc_oniguruma = rb_define_class("Oniguruma", rb_cObject);
    rbc_plist_node = G_DEF_CLASS(plist_node_get_type(), "Node", rbc_plist);
    rb_define_method(rbc_plist_node, "initialize", plist_node_initialize, 0);
    rbc_plist_dict = G_DEF_CLASS(plist_dict_get_type(), "Dict", rbc_plist);
    rb_define_method(rbc_plist_dict, "initialize", plist_dict_initialize, 0);
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
    rbc_oniguruma_match = G_DEF_CLASS(oniguruma_match_get_type(), "Match", rbc_oniguruma);
    rb_define_method(rbc_oniguruma_match, "initialize", oniguruma_match_initialize, 0);
    rb_define_method(rbc_oniguruma_match, "begin", rb_oniguruma_match_begin, 1);
    rb_define_method(rbc_oniguruma_match, "end", rb_oniguruma_match_end, 1);
    rbc_gtk_mate_bundle = G_DEF_CLASS(gtk_mate_bundle_get_type(), "Bundle", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_bundle, "initialize", gtk_mate_bundle_initialize, 1);
    rb_define_method(rbc_gtk_mate_bundle, "grammars", rb_gtk_mate_bundle_get_grammars, 0);
    rb_define_method(rbc_gtk_mate_bundle, "grammars=", rb_gtk_mate_bundle_set_grammars, 1);
    rbc_gtk_mate_buffer = G_DEF_CLASS(gtk_mate_buffer_get_type(), "Buffer", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_buffer, "initialize", gtk_mate_buffer_initialize, 0);
    rb_define_singleton_method(rbc_gtk_mate_buffer, "bundles", rb_gtk_mate_buffer_get_bundles, 0);
    rb_define_singleton_method(rbc_gtk_mate_buffer, "bundles=", rb_gtk_mate_buffer_set_bundles, 1);
    rb_define_singleton_method(rbc_gtk_mate_buffer, "themes", rb_gtk_mate_buffer_get_themes, 0);
    rb_define_singleton_method(rbc_gtk_mate_buffer, "themes=", rb_gtk_mate_buffer_set_themes, 1);
    rb_define_method(rbc_gtk_mate_buffer, "set_grammar_by_extension", rb_gtk_mate_buffer_set_grammar_by_extension, 1);
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
    rb_define_method(rbc_gtk_mate_grammar, "loaded", rb_gtk_mate_grammar_get_loaded, 0);
    rb_define_method(rbc_gtk_mate_grammar, "loaded=", rb_gtk_mate_grammar_set_loaded, 1);
    rb_define_method(rbc_gtk_mate_grammar, "folding_start_marker", rb_gtk_mate_grammar_get_folding_start_marker, 0);
    rb_define_method(rbc_gtk_mate_grammar, "folding_start_marker=", rb_gtk_mate_grammar_set_folding_start_marker, 1);
    rb_define_method(rbc_gtk_mate_grammar, "folding_stop_marker", rb_gtk_mate_grammar_get_folding_stop_marker, 0);
    rb_define_method(rbc_gtk_mate_grammar, "folding_stop_marker=", rb_gtk_mate_grammar_set_folding_stop_marker, 1);
    rb_define_method(rbc_gtk_mate_grammar, "patterns", rb_gtk_mate_grammar_get_patterns, 0);
    rb_define_method(rbc_gtk_mate_grammar, "patterns=", rb_gtk_mate_grammar_set_patterns, 1);
    rb_define_method(rbc_gtk_mate_grammar, "init_for_reference", rb_gtk_mate_grammar_init_for_reference, 0);
    rb_define_method(rbc_gtk_mate_grammar, "init_for_use", rb_gtk_mate_grammar_init_for_use, 0);
    rb_define_method(rbc_gtk_mate_grammar, "replace_include_patterns", rb_gtk_mate_grammar_replace_include_patterns, 2);
    rbc_gtk_mate_pattern = G_DEF_CLASS(gtk_mate_pattern_get_type(), "Pattern", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_pattern, "initialize", gtk_mate_pattern_initialize, 0);
    rb_define_method(rbc_gtk_mate_pattern, "name", rb_gtk_mate_pattern_get_name, 0);
    rb_define_method(rbc_gtk_mate_pattern, "name=", rb_gtk_mate_pattern_set_name, 1);
    rb_define_method(rbc_gtk_mate_pattern, "comment", rb_gtk_mate_pattern_get_comment, 0);
    rb_define_method(rbc_gtk_mate_pattern, "comment=", rb_gtk_mate_pattern_set_comment, 1);
    rb_define_singleton_method(rbc_gtk_mate_pattern, "all_patterns", rb_gtk_mate_pattern_get_all_patterns, 0);
    rb_define_singleton_method(rbc_gtk_mate_pattern, "all_patterns=", rb_gtk_mate_pattern_set_all_patterns, 1);
    rb_define_singleton_method(rbc_gtk_mate_pattern, "create_from_plist", rb_gtk_mate_pattern_create_from_plist, 1);
    rbc_oniguruma_onig_error = G_DEF_CLASS(oniguruma_onig_error_get_type(), "OnigError", rbc_oniguruma);
    rb_define_method(rbc_oniguruma_onig_error, "initialize", oniguruma_onig_error_initialize, 0);
    rb_define_method(rbc_oniguruma_onig_error, "code", rb_oniguruma_onig_error_get_code, 0);
    rb_define_method(rbc_oniguruma_onig_error, "code=", rb_oniguruma_onig_error_set_code, 1);
    rbc_gtk_mate_single_pattern = G_DEF_CLASS(gtk_mate_single_pattern_get_type(), "SinglePattern", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_single_pattern, "initialize", gtk_mate_single_pattern_initialize, 0);
    rb_define_method(rbc_gtk_mate_single_pattern, "match", rb_gtk_mate_single_pattern_get_match, 0);
    rb_define_method(rbc_gtk_mate_single_pattern, "match=", rb_gtk_mate_single_pattern_set_match, 1);
    rb_define_singleton_method(rbc_gtk_mate_single_pattern, "create_from_plist", rb_gtk_mate_single_pattern_create_from_plist, 1);
    rbc_gtk_mate_double_pattern = G_DEF_CLASS(gtk_mate_double_pattern_get_type(), "DoublePattern", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_double_pattern, "initialize", gtk_mate_double_pattern_initialize, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "begin", rb_gtk_mate_double_pattern_get_begin, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "begin=", rb_gtk_mate_double_pattern_set_begin, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "end", rb_gtk_mate_double_pattern_get_end, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "end=", rb_gtk_mate_double_pattern_set_end, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "patterns", rb_gtk_mate_double_pattern_get_patterns, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "patterns=", rb_gtk_mate_double_pattern_set_patterns, 1);
    rb_define_singleton_method(rbc_gtk_mate_double_pattern, "create_from_plist", rb_gtk_mate_double_pattern_create_from_plist, 1);
    rbc_gtk_mate_include_pattern = G_DEF_CLASS(gtk_mate_include_pattern_get_type(), "IncludePattern", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_include_pattern, "initialize", gtk_mate_include_pattern_initialize, 0);
    rb_define_singleton_method(rbc_gtk_mate_include_pattern, "create_from_plist", rb_gtk_mate_include_pattern_create_from_plist, 1);
}
