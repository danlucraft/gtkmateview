#include "ruby.h"
#include "rbgtk.h"
#include "buffer.h"
#include "bundle.h"
#include "colourer.h"
#include "pattern.h"
#include "grammar.h"
#include "scanner.h"
#include "matcher.h"
#include "parser.h"
#include "scope.h"
#include "theme.h"
#include "view.h"
#include "gtkmateview.h"
#include "onig_wrap.h"
#include "plist.h"
#include "string_helper.h"
#include "range_set.h"
static VALUE rb_vala_error, rbc_gtk;

/****  Gtk wrapper *****/

#define _GTK_SELF(s) GTK(RVAL2GOBJ(s))
static VALUE rbc_gtk;

/****  Gtk.Mate wrapper *****/

#define _GTK_MATE_SELF(s) GTK_MATE(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate;

/****  Gtk.Mate.Buffer wrapper *****/

#define _GTK_MATE_BUFFER_SELF(s) GTK_MATE_BUFFER(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_buffer;
GeeArrayList* gtk_mate_buffer_bundles;
GeeArrayList* gtk_mate_buffer_themes;

/****  Gtk.Mate.Bundle wrapper *****/

#define _GTK_MATE_BUNDLE_SELF(s) GTK_MATE_BUNDLE(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_bundle;

/****  Gtk.Mate.Colourer wrapper *****/

#define _GTK_MATE_COLOURER_SELF(s) GTK_MATE_COLOURER(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_colourer;

/****  Gtk.Mate.DoublePattern wrapper *****/

#define _GTK_MATE_DOUBLE_PATTERN_SELF(s) GTK_MATE_DOUBLE_PATTERN(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_double_pattern;

/****  Gtk.Mate.Grammar wrapper *****/

#define _GTK_MATE_GRAMMAR_SELF(s) GTK_MATE_GRAMMAR(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_grammar;

/****  Gtk.Mate.IncludePattern wrapper *****/

#define _GTK_MATE_INCLUDE_PATTERN_SELF(s) GTK_MATE_INCLUDE_PATTERN(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_include_pattern;

/****  Gtk.Mate.Marker wrapper *****/

#define _GTK_MATE_MARKER_SELF(s) GTK_MATE_MARKER(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_marker;

/****  Gtk.Mate.Matcher wrapper *****/

#define _GTK_MATE_MATCHER_SELF(s) GTK_MATE_MATCHER(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_matcher;

/****  Gtk.Mate.Parser wrapper *****/

#define _GTK_MATE_PARSER_SELF(s) GTK_MATE_PARSER(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_parser;
GeeArrayList* gtk_mate_parser_existing_parsers;

/****  Gtk.Mate.Pattern wrapper *****/

#define _GTK_MATE_PATTERN_SELF(s) GTK_MATE_PATTERN(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_pattern;
GeeArrayList* gtk_mate_pattern_all_patterns;

/****  Gtk.Mate.Scanner wrapper *****/

#define _GTK_MATE_SCANNER_SELF(s) GTK_MATE_SCANNER(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_scanner;

/****  Gtk.Mate.Scope wrapper *****/

#define _GTK_MATE_SCOPE_SELF(s) GTK_MATE_SCOPE(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_scope;
int gtk_mate_scope_scope_count;

/****  Gtk.Mate.SinglePattern wrapper *****/

#define _GTK_MATE_SINGLE_PATTERN_SELF(s) GTK_MATE_SINGLE_PATTERN(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_single_pattern;

/****  Gtk.Mate.TextLoc wrapper *****/

#define _GTK_MATE_TEXT_LOC_SELF(s) GTK_MATE_TEXT_LOC(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_text_loc;

/****  Gtk.Mate.Theme wrapper *****/

#define _GTK_MATE_THEME_SELF(s) GTK_MATE_THEME(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_theme;
GeeArrayList* gtk_mate_theme_themes;

/****  Gtk.Mate.ThemeSetting wrapper *****/

#define _GTK_MATE_THEME_SETTING_SELF(s) GTK_MATE_THEME_SETTING(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_theme_setting;

/****  Gtk.Mate.View wrapper *****/

#define _GTK_MATE_VIEW_SELF(s) GTK_MATE_VIEW(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_view;

/****  Onig wrapper *****/

#define _ONIG_SELF(s) ONIG(RVAL2GOBJ(s))
static VALUE rbc_onig;

/****  Onig.Match wrapper *****/

#define _ONIG_MATCH_SELF(s) ONIG_MATCH(RVAL2GOBJ(s))
static VALUE rbc_onig_match;
int onig_match_count;

/****  Onig.OnigError wrapper *****/

#define _ONIG_ONIG_ERROR_SELF(s) ONIG_ONIG_ERROR(RVAL2GOBJ(s))
static VALUE rbc_onig_onig_error;

/****  Onig.Rx wrapper *****/

#define _ONIG_RX_SELF(s) ONIG_RX(RVAL2GOBJ(s))
static VALUE rbc_onig_rx;

/****  PList wrapper *****/

#define _PLIST_SELF(s) PLIST(RVAL2GOBJ(s))
static VALUE rbc_plist;

/****  PList.Array wrapper *****/

#define _PLIST_ARRAY_SELF(s) PLIST_ARRAY(RVAL2GOBJ(s))
static VALUE rbc_plist_array;

/****  PList.Dict wrapper *****/

#define _PLIST_DICT_SELF(s) PLIST_DICT(RVAL2GOBJ(s))
static VALUE rbc_plist_dict;

/****  PList.Integer wrapper *****/

#define _PLIST_INTEGER_SELF(s) PLIST_INTEGER(RVAL2GOBJ(s))
static VALUE rbc_plist_integer;

/****  PList.Node wrapper *****/

#define _PLIST_NODE_SELF(s) PLIST_NODE(RVAL2GOBJ(s))
static VALUE rbc_plist_node;

/****  PList.String wrapper *****/

#define _PLIST_STRING_SELF(s) PLIST_STRING(RVAL2GOBJ(s))
static VALUE rbc_plist_string;

/****  StringHelper wrapper *****/

#define _STRING_HELPER_SELF(s) STRING_HELPER(RVAL2GOBJ(s))
static VALUE rbc_string_helper;

/****  RangeSet wrapper *****/

#define _RANGE_SET_SELF(s) RANGE_SET(RVAL2GOBJ(s))
static VALUE rbc_range_set;

/****  RangeSet.Range wrapper *****/

#define _RANGE_SET_RANGE_SELF(s) RANGE_SET_RANGE(RVAL2GOBJ(s))
static VALUE rbc_range_set_range;

/****  Gtk methods *****/


/****  Gtk.Mate methods *****/

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
        int it_val3;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val3 = 0; it_val3 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val3 = it_val3 + 1) {
            GtkMateBundle* i_val4;
            i_val4 =  (gee_list_get (GEE_LIST (_c_return), it_val3));
            VALUE rb_ival4;
            rb_ival4 = GOBJ2RVAL(i_val4);
            rb_ary_store (_rb_return, it_val3, rb_ival4);
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
    int len_val5 = RARRAY_LEN(bundles);
    _c_bundles = gee_array_list_new (GTK_MATE_TYPE_BUNDLE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val5; i++) {
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
        int it_val6;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val6 = 0; it_val6 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val6 = it_val6 + 1) {
            GtkMateTheme* i_val7;
            i_val7 =  (gee_list_get (GEE_LIST (_c_return), it_val6));
            VALUE rb_ival7;
            rb_ival7 = GOBJ2RVAL(i_val7);
            rb_ary_store (_rb_return, it_val6, rb_ival7);
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
    int len_val8 = RARRAY_LEN(themes);
    _c_themes = gee_array_list_new (GTK_MATE_TYPE_THEME, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val8; i++) {
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

static VALUE rb_gtk_mate_buffer_current_scope_range(VALUE self) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    GeeArrayList* _c_return;
    _c_return = gtk_mate_buffer_current_scope_range(gtk_mate_buffer);
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val9;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val9 = 0; it_val9 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val9 = it_val9 + 1) {
            int i_val10;
            i_val10 = GPOINTER_TO_INT (gee_list_get (GEE_LIST (_c_return), it_val9));
            VALUE rb_ival10;
            rb_ival10 = INT2FIX(i_val10);
            rb_ary_store (_rb_return, it_val9, rb_ival10);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_buffer_cursor_line(VALUE self) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_buffer_cursor_line(gtk_mate_buffer);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_buffer_cursor_line_offset(VALUE self) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_buffer_cursor_line_offset(gtk_mate_buffer);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_buffer_cursor_mark(VALUE self) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    GtkTextMark* _c_return;
    _c_return = gtk_mate_buffer_cursor_mark(gtk_mate_buffer);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_buffer_cursor_offset(VALUE self) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_buffer_cursor_offset(gtk_mate_buffer);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_buffer_end_mark(VALUE self) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    GtkTextMark* _c_return;
    _c_return = gtk_mate_buffer_end_mark(gtk_mate_buffer);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_buffer_get_line(VALUE self, VALUE line) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_line;
    _c_line = FIX2INT(line);
    // Method#body
    
    char * _c_return;
    _c_return = gtk_mate_buffer_get_line(gtk_mate_buffer, _c_line);
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

static VALUE rb_gtk_mate_buffer_get_line1(VALUE self, VALUE line_ix) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line_ix) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_line_ix;
    _c_line_ix = FIX2INT(line_ix);
    // Method#body
    
    char * _c_return;
    _c_return = gtk_mate_buffer_get_line1(gtk_mate_buffer, _c_line_ix);
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

static VALUE rb_gtk_mate_buffer_get_line_length(VALUE self, VALUE line) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_line;
    _c_line = FIX2INT(line);
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_buffer_get_line_length(gtk_mate_buffer, _c_line);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_buffer_select_current_scope(VALUE self) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gtk_mate_buffer_select_current_scope(gtk_mate_buffer);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_buffer_selection_mark(VALUE self) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    GtkTextMark* _c_return;
    _c_return = gtk_mate_buffer_selection_mark(gtk_mate_buffer);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_buffer_set_grammar_by_filename(VALUE self, VALUE filename) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(filename) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_filename;
    _c_filename = g_strdup(STR2CSTR(filename));
    // Method#body
    
    char * _c_return;
    _c_return = gtk_mate_buffer_set_grammar_by_filename(gtk_mate_buffer, _c_filename);
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

static VALUE rb_gtk_mate_buffer_set_grammar_by_first_line(VALUE self, VALUE first_line) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(first_line) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_first_line;
    _c_first_line = g_strdup(STR2CSTR(first_line));
    // Method#body
    
    char * _c_return;
    _c_return = gtk_mate_buffer_set_grammar_by_first_line(gtk_mate_buffer, _c_first_line);
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
    
    gboolean _c_return;
    _c_return = gtk_mate_buffer_set_grammar_by_name(gtk_mate_buffer, _c_name);
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_buffer_start_mark(VALUE self) {
    GtkMateBuffer* gtk_mate_buffer = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    GtkTextMark* _c_return;
    _c_return = gtk_mate_buffer_start_mark(gtk_mate_buffer);
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
        int it_val11;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val11 = 0; it_val11 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val11 = it_val11 + 1) {
            GtkMateGrammar* i_val12;
            i_val12 =  (gee_list_get (GEE_LIST (_c_return), it_val11));
            VALUE rb_ival12;
            rb_ival12 = GOBJ2RVAL(i_val12);
            rb_ary_store (_rb_return, it_val11, rb_ival12);
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
    int len_val13 = RARRAY_LEN(grammars);
    _c_grammars = gee_array_list_new (GTK_MATE_TYPE_GRAMMAR, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val13; i++) {
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


/****  Gtk.Mate.Colourer methods *****/


static VALUE gtk_mate_colourer_initialize(VALUE self, VALUE buffer) {
    GtkMateBuffer* _c_buffer;
    _c_buffer = _GTK_MATE_BUFFER_SELF(buffer);

    RBGTK_INITIALIZE(self, gtk_mate_colourer_new (_c_buffer));
    return Qnil;
}

static VALUE rb_gtk_mate_colourer_char_to_hex(VALUE self, VALUE ch) {
    // Method#type_checks
    if (TYPE(ch) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    gunichar _c_ch;
    _c_ch = *g_utf8_to_ucs4(STR2CSTR(ch), RSTRING_LEN(ch), NULL, NULL, NULL);
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_colourer_char_to_hex(_c_ch);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_colourer_colour_line_with_scopes(VALUE self, VALUE scopes) {
    GtkMateColourer* gtk_mate_colourer = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_scopes;
        // ArrayListType#ruby_to_c(:before, "scopes", "_c_scopes")
    int len_val14 = RARRAY_LEN(scopes);
    _c_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val14; i++) {
            VALUE _rb_el = rb_ary_entry(scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_scopes), (_c_el));
        }
    }

    // Method#body
    
    gtk_mate_colourer_colour_line_with_scopes(gtk_mate_colourer, _c_scopes);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_colourer_colour_scope(VALUE self, VALUE scope, VALUE inner, VALUE force) {
    GtkMateColourer* gtk_mate_colourer = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(inner) != T_TRUE && TYPE(inner) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    if (TYPE(force) != T_TRUE && TYPE(force) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    GtkMateScope* _c_scope;
    _c_scope = _GTK_MATE_SCOPE_SELF(scope);
    gboolean _c_inner;
          if (inner == Qtrue)
          _c_inner = TRUE;
      else
          _c_inner = FALSE;

    gboolean _c_force;
          if (force == Qtrue)
          _c_force = TRUE;
      else
          _c_force = FALSE;

    // Method#body
    
    gtk_mate_colourer_colour_scope(gtk_mate_colourer, _c_scope, _c_inner, _c_force);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_colourer_merge_colour(VALUE self, VALUE parent_colour, VALUE colour) {
    // Method#type_checks
    if (TYPE(parent_colour) != T_STRING && parent_colour != Qnil) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string or nil");
    }
    if (TYPE(colour) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_parent_colour;
    if (parent_colour == Qnil)
        _c_parent_colour = NULL;
    else {
        _c_parent_colour = g_strdup(STR2CSTR(parent_colour));
    }
    char * _c_colour;
    _c_colour = g_strdup(STR2CSTR(colour));
    // Method#body
    
    char * _c_return;
    _c_return = gtk_mate_colourer_merge_colour(_c_parent_colour, _c_colour);
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

static VALUE rb_gtk_mate_colourer_set_global_settings(VALUE self, VALUE view) {
    GtkMateColourer* gtk_mate_colourer = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateView* _c_view;
    _c_view = _GTK_MATE_VIEW_SELF(view);
    // Method#body
    
    gtk_mate_colourer_set_global_settings(gtk_mate_colourer, _c_view);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_colourer_set_tag_properties(VALUE self, VALUE scope, VALUE tag, VALUE setting) {
    GtkMateColourer* gtk_mate_colourer = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateScope* _c_scope;
    _c_scope = _GTK_MATE_SCOPE_SELF(scope);
    GtkTextTag* _c_tag;
    _c_tag = _GTK_TEXT_TAG_SELF(tag);
    GtkMateThemeSetting* _c_setting;
    _c_setting = _GTK_MATE_THEME_SETTING_SELF(setting);
    // Method#body
    
    gtk_mate_colourer_set_tag_properties(gtk_mate_colourer, _c_scope, _c_tag, _c_setting);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_colourer_uncolour_scope(VALUE self, VALUE scope, VALUE recurse) {
    GtkMateColourer* gtk_mate_colourer = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(recurse) != T_TRUE && TYPE(recurse) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    GtkMateScope* _c_scope;
    _c_scope = _GTK_MATE_SCOPE_SELF(scope);
    gboolean _c_recurse;
          if (recurse == Qtrue)
          _c_recurse = TRUE;
      else
          _c_recurse = FALSE;

    // Method#body
    
    gtk_mate_colourer_uncolour_scope(gtk_mate_colourer, _c_scope, _c_recurse);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_colourer_uncolour_scopes(VALUE self, VALUE scopes) {
    GtkMateColourer* gtk_mate_colourer = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_scopes;
        // ArrayListType#ruby_to_c(:before, "scopes", "_c_scopes")
    int len_val15 = RARRAY_LEN(scopes);
    _c_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val15; i++) {
            VALUE _rb_el = rb_ary_entry(scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_scopes), (_c_el));
        }
    }

    // Method#body
    
    gtk_mate_colourer_uncolour_scopes(gtk_mate_colourer, _c_scopes);
    // Method#return_type_conversion
    return Qnil;
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
    OnigRx* _c_return = gtk_mate_double_pattern->begin; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_double_pattern_set_begin(VALUE self, VALUE begin) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigRx* _c_begin;
    _c_begin = _ONIG_RX_SELF(begin);
    // ValaMemberSet#body
    gtk_mate_double_pattern->begin = _c_begin;
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
    int len_val16 = RARRAY_LEN(rb_keys);
    {
        gint i;
        i = 0;
        for (; i < len_val16; i++) {
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

static VALUE rb_gtk_mate_double_pattern_get_both_captures(VALUE self) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeHashMap* _c_return = gtk_mate_double_pattern->both_captures; 
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

static VALUE rb_gtk_mate_double_pattern_set_both_captures(VALUE self, VALUE both_captures) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(both_captures) != T_HASH) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a hash");
    }
    // Method#argument_type_conversions
    GeeHashMap* _c_both_captures;
        // HashMap#ruby_to_c(:before, "both_captures", "_c_both_captures")
    _c_both_captures = gee_hash_map_new (G_TYPE_INT, NULL, NULL, G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, g_str_hash, g_str_equal, g_direct_equal);
    VALUE rb_keys = rb_funcall(both_captures, rb_intern("keys"), 0);
    int len_val17 = RARRAY_LEN(rb_keys);
    {
        gint i;
        i = 0;
        for (; i < len_val17; i++) {
            VALUE _rb_key = rb_ary_entry(rb_keys, (long) i);
            VALUE _rb_value = rb_hash_aref(both_captures, _rb_key);
            int _c__rb_key;
            _c__rb_key = FIX2INT(_rb_key);
            char * _c__rb_value;
            _c__rb_value = g_strdup(STR2CSTR(_rb_value));
            gee_map_set (GEE_MAP (_c_both_captures), _c__rb_key,  (_c__rb_value));
        }
    }

    // ValaMemberSet#body
    gtk_mate_double_pattern->both_captures = _c_both_captures;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_double_pattern_get_content_name(VALUE self) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_double_pattern->content_name; 
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

static VALUE rb_gtk_mate_double_pattern_set_content_name(VALUE self, VALUE content_name) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(content_name) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_content_name;
    _c_content_name = g_strdup(STR2CSTR(content_name));
    // ValaMemberSet#body
    gtk_mate_double_pattern->content_name = _c_content_name;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_double_pattern_get_end(VALUE self) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    OnigRx* _c_return = gtk_mate_double_pattern->end; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_double_pattern_set_end(VALUE self, VALUE end) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigRx* _c_end;
    _c_end = _ONIG_RX_SELF(end);
    // ValaMemberSet#body
    gtk_mate_double_pattern->end = _c_end;
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
    int len_val18 = RARRAY_LEN(rb_keys);
    {
        gint i;
        i = 0;
        for (; i < len_val18; i++) {
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

static VALUE rb_gtk_mate_double_pattern_get_end_string(VALUE self) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_double_pattern->end_string; 
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

static VALUE rb_gtk_mate_double_pattern_set_end_string(VALUE self, VALUE end_string) {
    GtkMateDoublePattern* gtk_mate_double_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(end_string) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_end_string;
    _c_end_string = g_strdup(STR2CSTR(end_string));
    // ValaMemberSet#body
    gtk_mate_double_pattern->end_string = _c_end_string;
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
        int it_val19;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val19 = 0; it_val19 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val19 = it_val19 + 1) {
            GtkMatePattern* i_val20;
            i_val20 =  (gee_list_get (GEE_LIST (_c_return), it_val19));
            VALUE rb_ival20;
            rb_ival20 = GOBJ2RVAL(i_val20);
            rb_ary_store (_rb_return, it_val19, rb_ival20);
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
    int len_val21 = RARRAY_LEN(patterns);
    _c_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val21; i++) {
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
    int len_val22 = RARRAY_LEN(all_patterns);
    _c_all_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val22; i++) {
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


/****  Gtk.Mate.Grammar methods *****/


static VALUE gtk_mate_grammar_initialize(VALUE self, VALUE plist) {
    PListDict* _c_plist;
    _c_plist = _PLIST_DICT_SELF(plist);

    RBGTK_INITIALIZE(self, gtk_mate_grammar_new (_c_plist));
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
        int it_val23;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val23 = 0; it_val23 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val23 = it_val23 + 1) {
            GtkMatePattern* i_val24;
            i_val24 =  (gee_list_get (GEE_LIST (_c_return), it_val23));
            VALUE rb_ival24;
            rb_ival24 = GOBJ2RVAL(i_val24);
            rb_ary_store (_rb_return, it_val23, rb_ival24);
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
    int len_val25 = RARRAY_LEN(all_patterns);
    _c_all_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val25; i++) {
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
              long val26;
              for(val26 = 0; val26 < _rb_return__length; val26++) {
                  rb_ary_store(_rb_return, val26, rb_str_new2(_c_return[val26]));
//                g_free(_c_return[val26]);
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
          long val27;
          for(val27 = 0; val27 < _c_file_types__length; val27++) {
             *(_c_file_types+val27) = RSTRING_PTR(rb_ary_entry(file_types, (long) val27));
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
    OnigRx* _c_return = gtk_mate_grammar->first_line_match; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_first_line_match(VALUE self, VALUE first_line_match) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigRx* _c_first_line_match;
    _c_first_line_match = _ONIG_RX_SELF(first_line_match);
    // ValaMemberSet#body
    gtk_mate_grammar->first_line_match = _c_first_line_match;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_grammar_get_folding_start_marker(VALUE self) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    OnigRx* _c_return = gtk_mate_grammar->folding_start_marker; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_folding_start_marker(VALUE self, VALUE folding_start_marker) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigRx* _c_folding_start_marker;
    _c_folding_start_marker = _ONIG_RX_SELF(folding_start_marker);
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
    OnigRx* _c_return = gtk_mate_grammar->folding_stop_marker; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_grammar_set_folding_stop_marker(VALUE self, VALUE folding_stop_marker) {
    GtkMateGrammar* gtk_mate_grammar = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigRx* _c_folding_stop_marker;
    _c_folding_stop_marker = _ONIG_RX_SELF(folding_stop_marker);
    // ValaMemberSet#body
    gtk_mate_grammar->folding_stop_marker = _c_folding_stop_marker;
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
        int it_val28;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val28 = 0; it_val28 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val28 = it_val28 + 1) {
            GtkMatePattern* i_val29;
            i_val29 =  (gee_list_get (GEE_LIST (_c_return), it_val28));
            VALUE rb_ival29;
            rb_ival29 = GOBJ2RVAL(i_val29);
            rb_ary_store (_rb_return, it_val28, rb_ival29);
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
    int len_val30 = RARRAY_LEN(patterns);
    _c_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val30; i++) {
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
        int it_val31;
        rb_v = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (v)));
        for (it_val31 = 0; it_val31 < gee_collection_get_size (GEE_COLLECTION (v)); it_val31 = it_val31 + 1) {
            GtkMatePattern* i_val32;
            i_val32 =  (gee_list_get (GEE_LIST (v), it_val31));
            VALUE rb_ival32;
            rb_ival32 = GOBJ2RVAL(i_val32);
            rb_ary_store (rb_v, it_val31, rb_ival32);
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
    int len_val33 = RARRAY_LEN(rb_keys);
    {
        gint i;
        i = 0;
        for (; i < len_val33; i++) {
            VALUE _rb_key = rb_ary_entry(rb_keys, (long) i);
            VALUE _rb_value = rb_hash_aref(repository, _rb_key);
            char * _c__rb_key;
            _c__rb_key = g_strdup(STR2CSTR(_rb_key));
            GeeArrayList* _c__rb_value;
                // ArrayListType#ruby_to_c(:before, "_rb_value", "_c__rb_value")
    int len_val34 = RARRAY_LEN(_rb_value);
    _c__rb_value = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val34; i++) {
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

static VALUE rb_gtk_mate_grammar_find_by_scope_name(VALUE self, VALUE scope) {
    // Method#type_checks
    if (TYPE(scope) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_scope;
    _c_scope = g_strdup(STR2CSTR(scope));
    // Method#body
    
    GtkMateGrammar* _c_return;
    _c_return = gtk_mate_grammar_find_by_scope_name(_c_scope);
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
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


/****  Gtk.Mate.Marker methods *****/


static VALUE gtk_mate_marker_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_marker_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_marker_get_from(VALUE self) {
    GtkMateMarker* gtk_mate_marker = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    int _c_return = gtk_mate_marker->from; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_marker_set_from(VALUE self, VALUE from) {
    GtkMateMarker* gtk_mate_marker = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(from) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_from;
    _c_from = FIX2INT(from);
    // ValaMemberSet#body
    gtk_mate_marker->from = _c_from;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_marker_get_hint(VALUE self) {
    GtkMateMarker* gtk_mate_marker = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    int _c_return = gtk_mate_marker->hint; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_marker_set_hint(VALUE self, VALUE hint) {
    GtkMateMarker* gtk_mate_marker = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(hint) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_hint;
    _c_hint = FIX2INT(hint);
    // ValaMemberSet#body
    gtk_mate_marker->hint = _c_hint;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_marker_get_is_close_scope(VALUE self) {
    GtkMateMarker* gtk_mate_marker = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    gboolean _c_return = gtk_mate_marker->is_close_scope; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_marker_set_is_close_scope(VALUE self, VALUE is_close_scope) {
    GtkMateMarker* gtk_mate_marker = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(is_close_scope) != T_TRUE && TYPE(is_close_scope) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    gboolean _c_is_close_scope;
          if (is_close_scope == Qtrue)
          _c_is_close_scope = TRUE;
      else
          _c_is_close_scope = FALSE;

    // ValaMemberSet#body
    gtk_mate_marker->is_close_scope = _c_is_close_scope;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_marker_get_match(VALUE self) {
    GtkMateMarker* gtk_mate_marker = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    OnigMatch* _c_return = gtk_mate_marker->match; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_marker_set_match(VALUE self, VALUE match) {
    GtkMateMarker* gtk_mate_marker = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigMatch* _c_match;
    _c_match = _ONIG_MATCH_SELF(match);
    // ValaMemberSet#body
    gtk_mate_marker->match = _c_match;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_marker_get_pattern(VALUE self) {
    GtkMateMarker* gtk_mate_marker = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkMatePattern* _c_return = gtk_mate_marker->pattern; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_marker_set_pattern(VALUE self, VALUE pattern) {
    GtkMateMarker* gtk_mate_marker = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMatePattern* _c_pattern;
    _c_pattern = _GTK_MATE_PATTERN_SELF(pattern);
    // ValaMemberSet#body
    gtk_mate_marker->pattern = _c_pattern;
    // Method#return_type_conversion
    return Qnil;
}


/****  Gtk.Mate.Matcher methods *****/


static VALUE gtk_mate_matcher_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_matcher_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_matcher_get_neg_rxs(VALUE self) {
    GtkMateMatcher* gtk_mate_matcher = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeArrayList* _c_return = gtk_mate_matcher->neg_rxs; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val35;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val35 = 0; it_val35 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val35 = it_val35 + 1) {
            OnigRx* i_val36;
            i_val36 =  (gee_list_get (GEE_LIST (_c_return), it_val35));
            VALUE rb_ival36;
            rb_ival36 = GOBJ2RVAL(i_val36);
            rb_ary_store (_rb_return, it_val35, rb_ival36);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_matcher_set_neg_rxs(VALUE self, VALUE neg_rxs) {
    GtkMateMatcher* gtk_mate_matcher = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(neg_rxs) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_neg_rxs;
        // ArrayListType#ruby_to_c(:before, "neg_rxs", "_c_neg_rxs")
    int len_val37 = RARRAY_LEN(neg_rxs);
    _c_neg_rxs = gee_array_list_new (ONIG_TYPE_RX, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val37; i++) {
            VALUE _rb_el = rb_ary_entry(neg_rxs, (long) i);
            OnigRx* _c_el = _ONIG_RX_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_neg_rxs), (_c_el));
        }
    }

    // ValaMemberSet#body
    gtk_mate_matcher->neg_rxs = _c_neg_rxs;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_matcher_get_pos_rx(VALUE self) {
    GtkMateMatcher* gtk_mate_matcher = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    OnigRx* _c_return = gtk_mate_matcher->pos_rx; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_matcher_set_pos_rx(VALUE self, VALUE pos_rx) {
    GtkMateMatcher* gtk_mate_matcher = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigRx* _c_pos_rx;
    _c_pos_rx = _ONIG_RX_SELF(pos_rx);
    // ValaMemberSet#body
    gtk_mate_matcher->pos_rx = _c_pos_rx;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_matcher_compare_match(VALUE self, VALUE scope_string, VALUE m1, VALUE m2) {
    // Method#type_checks
    if (TYPE(scope_string) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_scope_string;
    _c_scope_string = g_strdup(STR2CSTR(scope_string));
    OnigMatch* _c_m1;
    _c_m1 = _ONIG_MATCH_SELF(m1);
    OnigMatch* _c_m2;
    _c_m2 = _ONIG_MATCH_SELF(m2);
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_matcher_compare_match(_c_scope_string, _c_m1, _c_m2);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_matcher_compile(VALUE self, VALUE selector_string) {
    // Method#type_checks
    if (TYPE(selector_string) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_selector_string;
    _c_selector_string = g_strdup(STR2CSTR(selector_string));
    // Method#body
    
    GeeArrayList* _c_return;
    _c_return = gtk_mate_matcher_compile(_c_selector_string);
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val38;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val38 = 0; it_val38 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val38 = it_val38 + 1) {
            GtkMateMatcher* i_val39;
            i_val39 =  (gee_list_get (GEE_LIST (_c_return), it_val38));
            VALUE rb_ival39;
            rb_ival39 = GOBJ2RVAL(i_val39);
            rb_ary_store (_rb_return, it_val38, rb_ival39);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_matcher_get_match(VALUE self, VALUE selector_string, VALUE scope_string) {
    // Method#type_checks
    if (TYPE(selector_string) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    if (TYPE(scope_string) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_selector_string;
    _c_selector_string = g_strdup(STR2CSTR(selector_string));
    char * _c_scope_string;
    _c_scope_string = g_strdup(STR2CSTR(scope_string));
    // Method#body
    
    OnigMatch* _c_return;
    _c_return = gtk_mate_matcher_get_match(_c_selector_string, _c_scope_string);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_matcher_test_match(VALUE self, VALUE selector_string, VALUE scope_string) {
    // Method#type_checks
    if (TYPE(selector_string) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    if (TYPE(scope_string) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_selector_string;
    _c_selector_string = g_strdup(STR2CSTR(selector_string));
    char * _c_scope_string;
    _c_scope_string = g_strdup(STR2CSTR(scope_string));
    // Method#body
    
    gboolean _c_return;
    _c_return = gtk_mate_matcher_test_match(_c_selector_string, _c_scope_string);
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_matcher_test_rank(VALUE self, VALUE selector_a, VALUE selector_b, VALUE scope_string) {
    // Method#type_checks
    if (TYPE(selector_a) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    if (TYPE(selector_b) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    if (TYPE(scope_string) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_selector_a;
    _c_selector_a = g_strdup(STR2CSTR(selector_a));
    char * _c_selector_b;
    _c_selector_b = g_strdup(STR2CSTR(selector_b));
    char * _c_scope_string;
    _c_scope_string = g_strdup(STR2CSTR(scope_string));
    // Method#body
    
    char * _c_return;
    _c_return = gtk_mate_matcher_test_rank(_c_selector_a, _c_selector_b, _c_scope_string);
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


/****  Gtk.Mate.Parser methods *****/


static VALUE gtk_mate_parser_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_parser_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_parser_get_always_parse_all(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    gboolean _c_return = gtk_mate_parser->always_parse_all; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_parser_set_always_parse_all(VALUE self, VALUE always_parse_all) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(always_parse_all) != T_TRUE && TYPE(always_parse_all) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    gboolean _c_always_parse_all;
          if (always_parse_all == Qtrue)
          _c_always_parse_all = TRUE;
      else
          _c_always_parse_all = FALSE;

    // ValaMemberSet#body
    gtk_mate_parser->always_parse_all = _c_always_parse_all;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_get_changes(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    RangeSet* _c_return = gtk_mate_parser->changes; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_parser_set_changes(VALUE self, VALUE changes) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    RangeSet* _c_changes;
    _c_changes = _RANGE_SET_SELF(changes);
    // ValaMemberSet#body
    gtk_mate_parser->changes = _c_changes;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_get_deactivation_level(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    int _c_return = gtk_mate_parser->deactivation_level; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_parser_set_deactivation_level(VALUE self, VALUE deactivation_level) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(deactivation_level) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_deactivation_level;
    _c_deactivation_level = FIX2INT(deactivation_level);
    // ValaMemberSet#body
    gtk_mate_parser->deactivation_level = _c_deactivation_level;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_get_dummy_tag(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkTextTag* _c_return = gtk_mate_parser->dummy_tag; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_parser_set_dummy_tag(VALUE self, VALUE dummy_tag) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkTextTag* _c_dummy_tag;
    _c_dummy_tag = _GTK_TEXT_TAG_SELF(dummy_tag);
    // ValaMemberSet#body
    gtk_mate_parser->dummy_tag = _c_dummy_tag;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_get_dummy_tag2(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkTextTag* _c_return = gtk_mate_parser->dummy_tag2; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_parser_set_dummy_tag2(VALUE self, VALUE dummy_tag2) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkTextTag* _c_dummy_tag2;
    _c_dummy_tag2 = _GTK_TEXT_TAG_SELF(dummy_tag2);
    // ValaMemberSet#body
    gtk_mate_parser->dummy_tag2 = _c_dummy_tag2;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_get_existing_parsers(VALUE self) {
    // Method#type_checks
    // Method#argument_type_conversions
    // StaticMemberGet#body
    GeeArrayList* _c_return = gtk_mate_parser_existing_parsers;
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
            GtkMateParser* i_val41;
            i_val41 =  (gee_list_get (GEE_LIST (_c_return), it_val40));
            VALUE rb_ival41;
            rb_ival41 = GOBJ2RVAL(i_val41);
            rb_ary_store (_rb_return, it_val40, rb_ival41);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_parser_set_existing_parsers(VALUE self, VALUE existing_parsers) {
    // Method#type_checks
    if (TYPE(existing_parsers) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_existing_parsers;
        // ArrayListType#ruby_to_c(:before, "existing_parsers", "_c_existing_parsers")
    int len_val42 = RARRAY_LEN(existing_parsers);
    _c_existing_parsers = gee_array_list_new (GTK_MATE_TYPE_PARSER, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val42; i++) {
            VALUE _rb_el = rb_ary_entry(existing_parsers, (long) i);
            GtkMateParser* _c_el = _GTK_MATE_PARSER_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_existing_parsers), (_c_el));
        }
    }

    // StaticMemberSet#body
    gtk_mate_parser_existing_parsers = _c_existing_parsers; 
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_get_last_visible_line(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    int _c_return = gtk_mate_parser->last_visible_line; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_parser_set_last_visible_line(VALUE self, VALUE last_visible_line) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(last_visible_line) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_last_visible_line;
    _c_last_visible_line = FIX2INT(last_visible_line);
    // ValaMemberSet#body
    gtk_mate_parser->last_visible_line = _c_last_visible_line;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_get_parsed_upto(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    int _c_return = gtk_mate_parser->parsed_upto; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_parser_set_parsed_upto(VALUE self, VALUE parsed_upto) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(parsed_upto) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_parsed_upto;
    _c_parsed_upto = FIX2INT(parsed_upto);
    // ValaMemberSet#body
    gtk_mate_parser->parsed_upto = _c_parsed_upto;
    // Method#return_type_conversion
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

static VALUE rb_gtk_mate_parser_added_tag(VALUE self, VALUE tag) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkTextTag* _c_tag;
    _c_tag = _GTK_TEXT_TAG_SELF(tag);
    // Method#body
    
    gtk_mate_parser_added_tag(gtk_mate_parser, _c_tag);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_change_theme(VALUE self, VALUE theme) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateTheme* _c_theme;
    _c_theme = _GTK_MATE_THEME_SELF(theme);
    // Method#body
    
    gtk_mate_parser_change_theme(gtk_mate_parser, _c_theme);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_clear_line(VALUE self, VALUE line_ix, VALUE start_scope, VALUE all_scopes, VALUE closed_scopes, VALUE removed_scopes) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line_ix) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(all_scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    if (TYPE(closed_scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    if (TYPE(removed_scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    int _c_line_ix;
    _c_line_ix = FIX2INT(line_ix);
    GtkMateScope* _c_start_scope;
    _c_start_scope = _GTK_MATE_SCOPE_SELF(start_scope);
    GeeArrayList* _c_all_scopes;
        // ArrayListType#ruby_to_c(:before, "all_scopes", "_c_all_scopes")
    int len_val43 = RARRAY_LEN(all_scopes);
    _c_all_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val43; i++) {
            VALUE _rb_el = rb_ary_entry(all_scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_all_scopes), (_c_el));
        }
    }

    GeeArrayList* _c_closed_scopes;
        // ArrayListType#ruby_to_c(:before, "closed_scopes", "_c_closed_scopes")
    int len_val44 = RARRAY_LEN(closed_scopes);
    _c_closed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val44; i++) {
            VALUE _rb_el = rb_ary_entry(closed_scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_closed_scopes), (_c_el));
        }
    }

    GeeArrayList* _c_removed_scopes;
        // ArrayListType#ruby_to_c(:before, "removed_scopes", "_c_removed_scopes")
    int len_val45 = RARRAY_LEN(removed_scopes);
    _c_removed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val45; i++) {
            VALUE _rb_el = rb_ary_entry(removed_scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_removed_scopes), (_c_el));
        }
    }

    // Method#body
    
    gtk_mate_parser_clear_line(gtk_mate_parser, _c_line_ix, _c_start_scope, _c_all_scopes, _c_closed_scopes, _c_removed_scopes);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_close(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gtk_mate_parser_close(gtk_mate_parser);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_close_scope(VALUE self, VALUE scanner, VALUE expected_scope, VALUE line_ix, VALUE line, VALUE m, VALUE all_scopes, VALUE closed_scopes, VALUE removed_scopes) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line_ix) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(line) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    if (TYPE(all_scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    if (TYPE(closed_scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    if (TYPE(removed_scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GtkMateScanner* _c_scanner;
    _c_scanner = _GTK_MATE_SCANNER_SELF(scanner);
    GtkMateScope* _c_expected_scope;
    if (expected_scope == Qnil)
        _c_expected_scope = NULL;
    else {
        _c_expected_scope = _GTK_MATE_SCOPE_SELF(expected_scope);
    }
    int _c_line_ix;
    _c_line_ix = FIX2INT(line_ix);
    char * _c_line;
    _c_line = g_strdup(STR2CSTR(line));
    GtkMateMarker* _c_m;
    _c_m = _GTK_MATE_MARKER_SELF(m);
    GeeArrayList* _c_all_scopes;
        // ArrayListType#ruby_to_c(:before, "all_scopes", "_c_all_scopes")
    int len_val46 = RARRAY_LEN(all_scopes);
    _c_all_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val46; i++) {
            VALUE _rb_el = rb_ary_entry(all_scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_all_scopes), (_c_el));
        }
    }

    GeeArrayList* _c_closed_scopes;
        // ArrayListType#ruby_to_c(:before, "closed_scopes", "_c_closed_scopes")
    int len_val47 = RARRAY_LEN(closed_scopes);
    _c_closed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val47; i++) {
            VALUE _rb_el = rb_ary_entry(closed_scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_closed_scopes), (_c_el));
        }
    }

    GeeArrayList* _c_removed_scopes;
        // ArrayListType#ruby_to_c(:before, "removed_scopes", "_c_removed_scopes")
    int len_val48 = RARRAY_LEN(removed_scopes);
    _c_removed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val48; i++) {
            VALUE _rb_el = rb_ary_entry(removed_scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_removed_scopes), (_c_el));
        }
    }

    // Method#body
    
    gtk_mate_parser_close_scope(gtk_mate_parser, _c_scanner, _c_expected_scope, _c_line_ix, _c_line, _c_m, _c_all_scopes, _c_closed_scopes, _c_removed_scopes);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_collect_child_captures(VALUE self, VALUE line_ix, VALUE scope, VALUE m, VALUE all_scopes, VALUE closed_scopes) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line_ix) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(all_scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    if (TYPE(closed_scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    int _c_line_ix;
    _c_line_ix = FIX2INT(line_ix);
    GtkMateScope* _c_scope;
    _c_scope = _GTK_MATE_SCOPE_SELF(scope);
    GtkMateMarker* _c_m;
    _c_m = _GTK_MATE_MARKER_SELF(m);
    GeeArrayList* _c_all_scopes;
        // ArrayListType#ruby_to_c(:before, "all_scopes", "_c_all_scopes")
    int len_val49 = RARRAY_LEN(all_scopes);
    _c_all_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val49; i++) {
            VALUE _rb_el = rb_ary_entry(all_scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_all_scopes), (_c_el));
        }
    }

    GeeArrayList* _c_closed_scopes;
        // ArrayListType#ruby_to_c(:before, "closed_scopes", "_c_closed_scopes")
    int len_val50 = RARRAY_LEN(closed_scopes);
    _c_closed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val50; i++) {
            VALUE _rb_el = rb_ary_entry(closed_scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_closed_scopes), (_c_el));
        }
    }

    // Method#body
    
    gtk_mate_parser_collect_child_captures(gtk_mate_parser, _c_line_ix, _c_scope, _c_m, _c_all_scopes, _c_closed_scopes);
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

static VALUE rb_gtk_mate_parser_get_expected_scope(VALUE self, VALUE current_scope, VALUE line, VALUE line_offset) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(line_offset) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    GtkMateScope* _c_current_scope;
    _c_current_scope = _GTK_MATE_SCOPE_SELF(current_scope);
    int _c_line;
    _c_line = FIX2INT(line);
    int _c_line_offset;
    _c_line_offset = FIX2INT(line_offset);
    // Method#body
    
    GtkMateScope* _c_return;
    _c_return = gtk_mate_parser_get_expected_scope(gtk_mate_parser, _c_current_scope, _c_line, _c_line_offset);
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}

static VALUE rb_gtk_mate_parser_handle_captures(VALUE self, VALUE line_ix, VALUE line, VALUE scope, VALUE m, VALUE all_scopes, VALUE closed_scopes) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line_ix) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(line) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    if (TYPE(all_scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    if (TYPE(closed_scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    int _c_line_ix;
    _c_line_ix = FIX2INT(line_ix);
    char * _c_line;
    _c_line = g_strdup(STR2CSTR(line));
    GtkMateScope* _c_scope;
    _c_scope = _GTK_MATE_SCOPE_SELF(scope);
    GtkMateMarker* _c_m;
    _c_m = _GTK_MATE_MARKER_SELF(m);
    GeeArrayList* _c_all_scopes;
        // ArrayListType#ruby_to_c(:before, "all_scopes", "_c_all_scopes")
    int len_val51 = RARRAY_LEN(all_scopes);
    _c_all_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val51; i++) {
            VALUE _rb_el = rb_ary_entry(all_scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_all_scopes), (_c_el));
        }
    }

    GeeArrayList* _c_closed_scopes;
        // ArrayListType#ruby_to_c(:before, "closed_scopes", "_c_closed_scopes")
    int len_val52 = RARRAY_LEN(closed_scopes);
    _c_closed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val52; i++) {
            VALUE _rb_el = rb_ary_entry(closed_scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_closed_scopes), (_c_el));
        }
    }

    // Method#body
    
    gtk_mate_parser_handle_captures(gtk_mate_parser, _c_line_ix, _c_line, _c_scope, _c_m, _c_all_scopes, _c_closed_scopes);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_is_parsing(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gboolean _c_return;
    _c_return = gtk_mate_parser_is_parsing(gtk_mate_parser);
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_parser_last_line_parsed(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_parser_last_line_parsed(gtk_mate_parser);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_parser_last_visible_line_changed(VALUE self, VALUE new_last_visible_line) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(new_last_visible_line) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_new_last_visible_line;
    _c_new_last_visible_line = FIX2INT(new_last_visible_line);
    // Method#body
    
    gtk_mate_parser_last_visible_line_changed(gtk_mate_parser, _c_new_last_visible_line);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_make_closing_regex(VALUE self, VALUE line, VALUE scope, VALUE m) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_line;
    _c_line = g_strdup(STR2CSTR(line));
    GtkMateScope* _c_scope;
    _c_scope = _GTK_MATE_SCOPE_SELF(scope);
    GtkMateMarker* _c_m;
    _c_m = _GTK_MATE_MARKER_SELF(m);
    // Method#body
    
    OnigRx* _c_return;
    _c_return = gtk_mate_parser_make_closing_regex(gtk_mate_parser, _c_line, _c_scope, _c_m);
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
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

static VALUE rb_gtk_mate_parser_open_scope(VALUE self, VALUE scanner, VALUE expected_scope, VALUE line_ix, VALUE line, VALUE length, VALUE m, VALUE all_scopes, VALUE closed_scopes, VALUE removed_scopes) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line_ix) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(line) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    if (TYPE(length) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(all_scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    if (TYPE(closed_scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    if (TYPE(removed_scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GtkMateScanner* _c_scanner;
    _c_scanner = _GTK_MATE_SCANNER_SELF(scanner);
    GtkMateScope* _c_expected_scope;
    if (expected_scope == Qnil)
        _c_expected_scope = NULL;
    else {
        _c_expected_scope = _GTK_MATE_SCOPE_SELF(expected_scope);
    }
    int _c_line_ix;
    _c_line_ix = FIX2INT(line_ix);
    char * _c_line;
    _c_line = g_strdup(STR2CSTR(line));
    int _c_length;
    _c_length = FIX2INT(length);
    GtkMateMarker* _c_m;
    _c_m = _GTK_MATE_MARKER_SELF(m);
    GeeArrayList* _c_all_scopes;
        // ArrayListType#ruby_to_c(:before, "all_scopes", "_c_all_scopes")
    int len_val53 = RARRAY_LEN(all_scopes);
    _c_all_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val53; i++) {
            VALUE _rb_el = rb_ary_entry(all_scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_all_scopes), (_c_el));
        }
    }

    GeeArrayList* _c_closed_scopes;
        // ArrayListType#ruby_to_c(:before, "closed_scopes", "_c_closed_scopes")
    int len_val54 = RARRAY_LEN(closed_scopes);
    _c_closed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val54; i++) {
            VALUE _rb_el = rb_ary_entry(closed_scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_closed_scopes), (_c_el));
        }
    }

    GeeArrayList* _c_removed_scopes;
        // ArrayListType#ruby_to_c(:before, "removed_scopes", "_c_removed_scopes")
    int len_val55 = RARRAY_LEN(removed_scopes);
    _c_removed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val55; i++) {
            VALUE _rb_el = rb_ary_entry(removed_scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_removed_scopes), (_c_el));
        }
    }

    // Method#body
    
    gtk_mate_parser_open_scope(gtk_mate_parser, _c_scanner, _c_expected_scope, _c_line_ix, _c_line, _c_length, _c_m, _c_all_scopes, _c_closed_scopes, _c_removed_scopes);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_recolour_children(VALUE self, VALUE scope) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateScope* _c_scope;
    _c_scope = _GTK_MATE_SCOPE_SELF(scope);
    // Method#body
    
    gtk_mate_parser_recolour_children(gtk_mate_parser, _c_scope);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_remove_tags(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gtk_mate_parser_remove_tags(gtk_mate_parser);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_reset_table_priorities(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gtk_mate_parser_reset_table_priorities(gtk_mate_parser);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_single_scope(VALUE self, VALUE scanner, VALUE expected_scope, VALUE line_ix, VALUE line, VALUE length, VALUE m, VALUE all_scopes, VALUE closed_scopes, VALUE removed_scopes) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line_ix) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(line) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    if (TYPE(length) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(all_scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    if (TYPE(closed_scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    if (TYPE(removed_scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GtkMateScanner* _c_scanner;
    _c_scanner = _GTK_MATE_SCANNER_SELF(scanner);
    GtkMateScope* _c_expected_scope;
    if (expected_scope == Qnil)
        _c_expected_scope = NULL;
    else {
        _c_expected_scope = _GTK_MATE_SCOPE_SELF(expected_scope);
    }
    int _c_line_ix;
    _c_line_ix = FIX2INT(line_ix);
    char * _c_line;
    _c_line = g_strdup(STR2CSTR(line));
    int _c_length;
    _c_length = FIX2INT(length);
    GtkMateMarker* _c_m;
    _c_m = _GTK_MATE_MARKER_SELF(m);
    GeeArrayList* _c_all_scopes;
        // ArrayListType#ruby_to_c(:before, "all_scopes", "_c_all_scopes")
    int len_val56 = RARRAY_LEN(all_scopes);
    _c_all_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val56; i++) {
            VALUE _rb_el = rb_ary_entry(all_scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_all_scopes), (_c_el));
        }
    }

    GeeArrayList* _c_closed_scopes;
        // ArrayListType#ruby_to_c(:before, "closed_scopes", "_c_closed_scopes")
    int len_val57 = RARRAY_LEN(closed_scopes);
    _c_closed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val57; i++) {
            VALUE _rb_el = rb_ary_entry(closed_scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_closed_scopes), (_c_el));
        }
    }

    GeeArrayList* _c_removed_scopes;
        // ArrayListType#ruby_to_c(:before, "removed_scopes", "_c_removed_scopes")
    int len_val58 = RARRAY_LEN(removed_scopes);
    _c_removed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val58; i++) {
            VALUE _rb_el = rb_ary_entry(removed_scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_removed_scopes), (_c_el));
        }
    }

    // Method#body
    
    gtk_mate_parser_single_scope(gtk_mate_parser, _c_scanner, _c_expected_scope, _c_line_ix, _c_line, _c_length, _c_m, _c_all_scopes, _c_closed_scopes, _c_removed_scopes);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_start_parsing(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gtk_mate_parser_start_parsing(gtk_mate_parser);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_parser_stop_parsing(VALUE self) {
    GtkMateParser* gtk_mate_parser = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gtk_mate_parser_stop_parsing(gtk_mate_parser);
    // Method#return_type_conversion
    return Qnil;
}


/****  Gtk.Mate.Pattern methods *****/


static VALUE gtk_mate_pattern_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_pattern_new ());
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
        int it_val59;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val59 = 0; it_val59 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val59 = it_val59 + 1) {
            GtkMatePattern* i_val60;
            i_val60 =  (gee_list_get (GEE_LIST (_c_return), it_val59));
            VALUE rb_ival60;
            rb_ival60 = GOBJ2RVAL(i_val60);
            rb_ary_store (_rb_return, it_val59, rb_ival60);
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
    int len_val61 = RARRAY_LEN(all_patterns);
    _c_all_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val61; i++) {
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

static VALUE rb_gtk_mate_pattern_get_disabled(VALUE self) {
    GtkMatePattern* gtk_mate_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    gboolean _c_return = gtk_mate_pattern->disabled; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_pattern_set_disabled(VALUE self, VALUE disabled) {
    GtkMatePattern* gtk_mate_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(disabled) != T_TRUE && TYPE(disabled) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    gboolean _c_disabled;
          if (disabled == Qtrue)
          _c_disabled = TRUE;
      else
          _c_disabled = FALSE;

    // ValaMemberSet#body
    gtk_mate_pattern->disabled = _c_disabled;
    // Method#return_type_conversion
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

static VALUE rb_gtk_mate_pattern_create_from_plist(VALUE self, VALUE all_patterns, VALUE pd) {
    // Method#type_checks
    if (TYPE(all_patterns) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_all_patterns;
        // ArrayListType#ruby_to_c(:before, "all_patterns", "_c_all_patterns")
    int len_val62 = RARRAY_LEN(all_patterns);
    _c_all_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val62; i++) {
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
    if (pd == Qnil)
        _c_pd = NULL;
    else {
        _c_pd = _PLIST_DICT_SELF(pd);
    }
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

static VALUE rb_gtk_mate_pattern_replace_base_and_self_includes(VALUE self, VALUE patlist, VALUE g) {
    // Method#type_checks
    if (TYPE(patlist) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_patlist;
        // ArrayListType#ruby_to_c(:before, "patlist", "_c_patlist")
    int len_val63 = RARRAY_LEN(patlist);
    _c_patlist = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val63; i++) {
            VALUE _rb_el = rb_ary_entry(patlist, (long) i);
            GtkMatePattern* _c_el = _GTK_MATE_PATTERN_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_patlist), (_c_el));
        }
    }

    GtkMateGrammar* _c_g;
    _c_g = _GTK_MATE_GRAMMAR_SELF(g);
    // Method#body
    
    gtk_mate_pattern_replace_base_and_self_includes(_c_patlist, _c_g);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_pattern_replace_include_patterns(VALUE self, VALUE patlist, VALUE g) {
    // Method#type_checks
    if (TYPE(patlist) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_patlist;
        // ArrayListType#ruby_to_c(:before, "patlist", "_c_patlist")
    int len_val64 = RARRAY_LEN(patlist);
    _c_patlist = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val64; i++) {
            VALUE _rb_el = rb_ary_entry(patlist, (long) i);
            GtkMatePattern* _c_el = _GTK_MATE_PATTERN_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_patlist), (_c_el));
        }
    }

    GtkMateGrammar* _c_g;
    _c_g = _GTK_MATE_GRAMMAR_SELF(g);
    // Method#body
    
    gtk_mate_pattern_replace_include_patterns(_c_patlist, _c_g);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_pattern_replace_repository_includes(VALUE self, VALUE patlist, VALUE g) {
    // Method#type_checks
    if (TYPE(patlist) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_patlist;
        // ArrayListType#ruby_to_c(:before, "patlist", "_c_patlist")
    int len_val65 = RARRAY_LEN(patlist);
    _c_patlist = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val65; i++) {
            VALUE _rb_el = rb_ary_entry(patlist, (long) i);
            GtkMatePattern* _c_el = _GTK_MATE_PATTERN_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_patlist), (_c_el));
        }
    }

    GtkMateGrammar* _c_g;
    _c_g = _GTK_MATE_GRAMMAR_SELF(g);
    // Method#body
    
    gtk_mate_pattern_replace_repository_includes(_c_patlist, _c_g);
    // Method#return_type_conversion
    return Qnil;
}


/****  Gtk.Mate.Scanner methods *****/


static VALUE gtk_mate_scanner_initialize(VALUE self, VALUE s, VALUE line, VALUE line_length) {
    GtkMateScope* _c_s;
    _c_s = _GTK_MATE_SCOPE_SELF(s);
    char * _c_line;
    _c_line = g_strdup(STR2CSTR(line));
    int _c_line_length;
    _c_line_length = FIX2INT(line_length);

    RBGTK_INITIALIZE(self, gtk_mate_scanner_new (_c_s, _c_line, _c_line_length));
    return Qnil;
}

static VALUE rb_gtk_mate_scanner_get_cached_markers(VALUE self) {
    GtkMateScanner* gtk_mate_scanner = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeArrayList* _c_return = gtk_mate_scanner->cached_markers; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val66;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val66 = 0; it_val66 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val66 = it_val66 + 1) {
            GtkMateMarker* i_val67;
            i_val67 =  (gee_list_get (GEE_LIST (_c_return), it_val66));
            VALUE rb_ival67;
            rb_ival67 = GOBJ2RVAL(i_val67);
            rb_ary_store (_rb_return, it_val66, rb_ival67);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_scanner_set_cached_markers(VALUE self, VALUE cached_markers) {
    GtkMateScanner* gtk_mate_scanner = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(cached_markers) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_cached_markers;
        // ArrayListType#ruby_to_c(:before, "cached_markers", "_c_cached_markers")
    int len_val68 = RARRAY_LEN(cached_markers);
    _c_cached_markers = gee_array_list_new (GTK_MATE_TYPE_MARKER, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val68; i++) {
            VALUE _rb_el = rb_ary_entry(cached_markers, (long) i);
            GtkMateMarker* _c_el = _GTK_MATE_MARKER_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_cached_markers), (_c_el));
        }
    }

    // ValaMemberSet#body
    gtk_mate_scanner->cached_markers = _c_cached_markers;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scanner_get_position(VALUE self) {
    GtkMateScanner* gtk_mate_scanner = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    int _c_return = gtk_mate_scanner->position; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scanner_set_position(VALUE self, VALUE position) {
    GtkMateScanner* gtk_mate_scanner = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(position) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_position;
    _c_position = FIX2INT(position);
    // ValaMemberSet#body
    gtk_mate_scanner->position = _c_position;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scanner_find_next_marker(VALUE self) {
    GtkMateScanner* gtk_mate_scanner = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    GtkMateMarker* _c_return;
    _c_return = gtk_mate_scanner_find_next_marker(gtk_mate_scanner);
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}

static VALUE rb_gtk_mate_scanner_get_cached_marker(VALUE self) {
    GtkMateScanner* gtk_mate_scanner = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    GtkMateMarker* _c_return;
    _c_return = gtk_mate_scanner_get_cached_marker(gtk_mate_scanner);
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}

static VALUE rb_gtk_mate_scanner_remove_preceding_cached_markers(VALUE self, VALUE m) {
    GtkMateScanner* gtk_mate_scanner = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateMarker* _c_m;
    _c_m = _GTK_MATE_MARKER_SELF(m);
    // Method#body
    
    gtk_mate_scanner_remove_preceding_cached_markers(gtk_mate_scanner, _c_m);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scanner_scan_for_match(VALUE self, VALUE from, VALUE p) {
    GtkMateScanner* gtk_mate_scanner = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(from) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_from;
    _c_from = FIX2INT(from);
    GtkMatePattern* _c_p;
    _c_p = _GTK_MATE_PATTERN_SELF(p);
    // Method#body
    
    OnigMatch* _c_return;
    _c_return = gtk_mate_scanner_scan_for_match(gtk_mate_scanner, _c_from, _c_p);
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


static VALUE gtk_mate_scope_initialize(VALUE self, VALUE buf, VALUE name) {
    GtkMateBuffer* _c_buf;
    _c_buf = _GTK_MATE_BUFFER_SELF(buf);
    char * _c_name;
    if (name == Qnil)
        _c_name = NULL;
    else {
        _c_name = g_strdup(STR2CSTR(name));
    }

    RBGTK_INITIALIZE(self, gtk_mate_scope_new (_c_buf, _c_name));
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_begin_match_string(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_scope->begin_match_string; 
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

static VALUE rb_gtk_mate_scope_set_begin_match_string(VALUE self, VALUE begin_match_string) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(begin_match_string) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_begin_match_string;
    _c_begin_match_string = g_strdup(STR2CSTR(begin_match_string));
    // ValaMemberSet#body
    gtk_mate_scope->begin_match_string = _c_begin_match_string;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_bg_colour(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_scope->bg_colour; 
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

static VALUE rb_gtk_mate_scope_set_bg_colour(VALUE self, VALUE bg_colour) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(bg_colour) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_bg_colour;
    _c_bg_colour = g_strdup(STR2CSTR(bg_colour));
    // ValaMemberSet#body
    gtk_mate_scope->bg_colour = _c_bg_colour;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_close_match(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    OnigMatch* _c_return = gtk_mate_scope->close_match; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_close_match(VALUE self, VALUE close_match) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigMatch* _c_close_match;
    _c_close_match = _ONIG_MATCH_SELF(close_match);
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
    OnigRx* _c_return = gtk_mate_scope->closing_regex; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_closing_regex(VALUE self, VALUE closing_regex) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigRx* _c_closing_regex;
    _c_closing_regex = _ONIG_RX_SELF(closing_regex);
    // ValaMemberSet#body
    gtk_mate_scope->closing_regex = _c_closing_regex;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_dummy_end_loc(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkMateTextLoc* _c_return = gtk_mate_scope->dummy_end_loc; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_dummy_end_loc(VALUE self, VALUE dummy_end_loc) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateTextLoc* _c_dummy_end_loc;
    _c_dummy_end_loc = _GTK_MATE_TEXT_LOC_SELF(dummy_end_loc);
    // ValaMemberSet#body
    gtk_mate_scope->dummy_end_loc = _c_dummy_end_loc;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_dummy_start_loc(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkMateTextLoc* _c_return = gtk_mate_scope->dummy_start_loc; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_dummy_start_loc(VALUE self, VALUE dummy_start_loc) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateTextLoc* _c_dummy_start_loc;
    _c_dummy_start_loc = _GTK_MATE_TEXT_LOC_SELF(dummy_start_loc);
    // ValaMemberSet#body
    gtk_mate_scope->dummy_start_loc = _c_dummy_start_loc;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_end_mark(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkTextMark* _c_return = gtk_mate_scope->end_mark; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_end_mark(VALUE self, VALUE end_mark) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkTextMark* _c_end_mark;
    _c_end_mark = _GTK_TEXT_MARK_SELF(end_mark);
    // ValaMemberSet#body
    gtk_mate_scope->end_mark = _c_end_mark;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_end_match_string(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_scope->end_match_string; 
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

static VALUE rb_gtk_mate_scope_set_end_match_string(VALUE self, VALUE end_match_string) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(end_match_string) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_end_match_string;
    _c_end_match_string = g_strdup(STR2CSTR(end_match_string));
    // ValaMemberSet#body
    gtk_mate_scope->end_match_string = _c_end_match_string;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_fg_colour(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_scope->fg_colour; 
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

static VALUE rb_gtk_mate_scope_set_fg_colour(VALUE self, VALUE fg_colour) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(fg_colour) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_fg_colour;
    _c_fg_colour = g_strdup(STR2CSTR(fg_colour));
    // ValaMemberSet#body
    gtk_mate_scope->fg_colour = _c_fg_colour;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_indent(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    int _c_return = gtk_mate_scope->indent; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_indent(VALUE self, VALUE indent) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(indent) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_indent;
    _c_indent = FIX2INT(indent);
    // ValaMemberSet#body
    gtk_mate_scope->indent = _c_indent;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_inner_end_mark(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkTextMark* _c_return = gtk_mate_scope->inner_end_mark; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_inner_end_mark(VALUE self, VALUE inner_end_mark) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkTextMark* _c_inner_end_mark;
    _c_inner_end_mark = _GTK_TEXT_MARK_SELF(inner_end_mark);
    // ValaMemberSet#body
    gtk_mate_scope->inner_end_mark = _c_inner_end_mark;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_inner_start_mark(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkTextMark* _c_return = gtk_mate_scope->inner_start_mark; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_inner_start_mark(VALUE self, VALUE inner_start_mark) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkTextMark* _c_inner_start_mark;
    _c_inner_start_mark = _GTK_TEXT_MARK_SELF(inner_start_mark);
    // ValaMemberSet#body
    gtk_mate_scope->inner_start_mark = _c_inner_start_mark;
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

static VALUE rb_gtk_mate_scope_get_is_open(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    gboolean _c_return = gtk_mate_scope->is_open; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_is_open(VALUE self, VALUE is_open) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(is_open) != T_TRUE && TYPE(is_open) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    gboolean _c_is_open;
          if (is_open == Qtrue)
          _c_is_open = TRUE;
      else
          _c_is_open = FALSE;

    // ValaMemberSet#body
    gtk_mate_scope->is_open = _c_is_open;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_open_match(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    OnigMatch* _c_return = gtk_mate_scope->open_match; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_open_match(VALUE self, VALUE open_match) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigMatch* _c_open_match;
    _c_open_match = _ONIG_MATCH_SELF(open_match);
    // ValaMemberSet#body
    gtk_mate_scope->open_match = _c_open_match;
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

static VALUE rb_gtk_mate_scope_get_scope_count(VALUE self) {
    // Method#type_checks
    // Method#argument_type_conversions
    // StaticMemberGet#body
    int _c_return = gtk_mate_scope_scope_count;
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_scope_count(VALUE self, VALUE scope_count) {
    // Method#type_checks
    if (TYPE(scope_count) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_scope_count;
    _c_scope_count = FIX2INT(scope_count);
    // StaticMemberSet#body
    gtk_mate_scope_scope_count = _c_scope_count; 
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_get_start_mark(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkTextMark* _c_return = gtk_mate_scope->start_mark; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_start_mark(VALUE self, VALUE start_mark) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkTextMark* _c_start_mark;
    _c_start_mark = _GTK_TEXT_MARK_SELF(start_mark);
    // ValaMemberSet#body
    gtk_mate_scope->start_mark = _c_start_mark;
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

static VALUE rb_gtk_mate_scope_get_theme_setting(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GtkMateThemeSetting* _c_return = gtk_mate_scope->theme_setting; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_set_theme_setting(VALUE self, VALUE theme_setting) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateThemeSetting* _c_theme_setting;
    _c_theme_setting = _GTK_MATE_THEME_SETTING_SELF(theme_setting);
    // ValaMemberSet#body
    gtk_mate_scope->theme_setting = _c_theme_setting;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_add_child(VALUE self, VALUE s) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateScope* _c_s;
    _c_s = _GTK_MATE_SCOPE_SELF(s);
    // Method#body
    
    gtk_mate_scope_add_child(gtk_mate_scope, _c_s);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_clear_after(VALUE self, VALUE line_ix, VALUE line_offset) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line_ix) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(line_offset) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_line_ix;
    _c_line_ix = FIX2INT(line_ix);
    int _c_line_offset;
    _c_line_offset = FIX2INT(line_offset);
    // Method#body
    
    gtk_mate_scope_clear_after(gtk_mate_scope, _c_line_ix, _c_line_offset);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_contains_loc(VALUE self, VALUE loc) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateTextLoc* _c_loc;
    _c_loc = _GTK_MATE_TEXT_LOC_SELF(loc);
    // Method#body
    
    gboolean _c_return;
    _c_return = gtk_mate_scope_contains_loc(gtk_mate_scope, _c_loc);
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_scope_delete_any_on_line_not_in(VALUE self, VALUE line_ix, VALUE scopes) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line_ix) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(scopes) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    int _c_line_ix;
    _c_line_ix = FIX2INT(line_ix);
    GeeArrayList* _c_scopes;
        // ArrayListType#ruby_to_c(:before, "scopes", "_c_scopes")
    int len_val69 = RARRAY_LEN(scopes);
    _c_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val69; i++) {
            VALUE _rb_el = rb_ary_entry(scopes, (long) i);
            GtkMateScope* _c_el = _GTK_MATE_SCOPE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_scopes), (_c_el));
        }
    }

    // Method#body
    
    GeeArrayList* _c_return;
    _c_return = gtk_mate_scope_delete_any_on_line_not_in(gtk_mate_scope, _c_line_ix, _c_scopes);
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val70;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val70 = 0; it_val70 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val70 = it_val70 + 1) {
            GtkMateScope* i_val71;
            i_val71 =  (gee_list_get (GEE_LIST (_c_return), it_val70));
            VALUE rb_ival71;
            rb_ival71 = GOBJ2RVAL(i_val71);
            rb_ary_store (_rb_return, it_val70, rb_ival71);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_scope_delete_child(VALUE self, VALUE s) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateScope* _c_s;
    _c_s = _GTK_MATE_SCOPE_SELF(s);
    // Method#body
    
    gtk_mate_scope_delete_child(gtk_mate_scope, _c_s);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_end_line(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_scope_end_line(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_end_line_offset(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_scope_end_line_offset(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_end_loc(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    GtkMateTextLoc* _c_return;
    _c_return = gtk_mate_scope_end_loc(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_end_mark_set(VALUE self, VALUE line, VALUE line_offset, VALUE has_left_gravity) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(line_offset) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(has_left_gravity) != T_TRUE && TYPE(has_left_gravity) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    int _c_line;
    _c_line = FIX2INT(line);
    int _c_line_offset;
    _c_line_offset = FIX2INT(line_offset);
    gboolean _c_has_left_gravity;
          if (has_left_gravity == Qtrue)
          _c_has_left_gravity = TRUE;
      else
          _c_has_left_gravity = FALSE;

    // Method#body
    
    gtk_mate_scope_end_mark_set(gtk_mate_scope, _c_line, _c_line_offset, _c_has_left_gravity);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_end_offset(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_scope_end_offset(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_first_child_after(VALUE self, VALUE loc) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateTextLoc* _c_loc;
    _c_loc = _GTK_MATE_TEXT_LOC_SELF(loc);
    // Method#body
    
    GtkMateScope* _c_return;
    _c_return = gtk_mate_scope_first_child_after(gtk_mate_scope, _c_loc);
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_hierarchy_names(VALUE self, VALUE inner) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(inner) != T_TRUE && TYPE(inner) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    gboolean _c_inner;
          if (inner == Qtrue)
          _c_inner = TRUE;
      else
          _c_inner = FALSE;

    // Method#body
    
    char * _c_return;
    _c_return = gtk_mate_scope_hierarchy_names(gtk_mate_scope, _c_inner);
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

static VALUE rb_gtk_mate_scope_inner_end_line(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_scope_inner_end_line(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_inner_end_line_offset(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_scope_inner_end_line_offset(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_inner_end_loc(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    GtkMateTextLoc* _c_return;
    _c_return = gtk_mate_scope_inner_end_loc(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_inner_end_mark_set(VALUE self, VALUE line, VALUE line_offset, VALUE has_left_gravity) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(line_offset) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(has_left_gravity) != T_TRUE && TYPE(has_left_gravity) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    int _c_line;
    _c_line = FIX2INT(line);
    int _c_line_offset;
    _c_line_offset = FIX2INT(line_offset);
    gboolean _c_has_left_gravity;
          if (has_left_gravity == Qtrue)
          _c_has_left_gravity = TRUE;
      else
          _c_has_left_gravity = FALSE;

    // Method#body
    
    gtk_mate_scope_inner_end_mark_set(gtk_mate_scope, _c_line, _c_line_offset, _c_has_left_gravity);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_inner_end_offset(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_scope_inner_end_offset(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_inner_start_line(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_scope_inner_start_line(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_inner_start_line_offset(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_scope_inner_start_line_offset(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_inner_start_loc(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    GtkMateTextLoc* _c_return;
    _c_return = gtk_mate_scope_inner_start_loc(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_inner_start_mark_set(VALUE self, VALUE line, VALUE line_offset, VALUE has_left_gravity) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(line_offset) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(has_left_gravity) != T_TRUE && TYPE(has_left_gravity) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    int _c_line;
    _c_line = FIX2INT(line);
    int _c_line_offset;
    _c_line_offset = FIX2INT(line_offset);
    gboolean _c_has_left_gravity;
          if (has_left_gravity == Qtrue)
          _c_has_left_gravity = TRUE;
      else
          _c_has_left_gravity = FALSE;

    // Method#body
    
    gtk_mate_scope_inner_start_mark_set(gtk_mate_scope, _c_line, _c_line_offset, _c_has_left_gravity);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_inner_start_offset(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_scope_inner_start_offset(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
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

static VALUE rb_gtk_mate_scope_nearest_background_colour(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    char * _c_return;
    _c_return = gtk_mate_scope_nearest_background_colour(gtk_mate_scope);
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

static VALUE rb_gtk_mate_scope_nearest_background_colour1(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    char * _c_return;
    _c_return = gtk_mate_scope_nearest_background_colour1(gtk_mate_scope);
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

static VALUE rb_gtk_mate_scope_nearest_foreground_colour(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    char * _c_return;
    _c_return = gtk_mate_scope_nearest_foreground_colour(gtk_mate_scope);
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

static VALUE rb_gtk_mate_scope_nearest_foreground_colour1(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    char * _c_return;
    _c_return = gtk_mate_scope_nearest_foreground_colour1(gtk_mate_scope);
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

static VALUE rb_gtk_mate_scope_overlaps_with(VALUE self, VALUE other) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateScope* _c_other;
    _c_other = _GTK_MATE_SCOPE_SELF(other);
    // Method#body
    
    gboolean _c_return;
    _c_return = gtk_mate_scope_overlaps_with(gtk_mate_scope, _c_other);
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

static VALUE rb_gtk_mate_scope_priority(VALUE self, VALUE inner) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(inner) != T_TRUE && TYPE(inner) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    gboolean _c_inner;
          if (inner == Qtrue)
          _c_inner = TRUE;
      else
          _c_inner = FALSE;

    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_scope_priority(gtk_mate_scope, _c_inner);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_root(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    GtkMateScope* _c_return;
    _c_return = gtk_mate_scope_root(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_scope_at(VALUE self, VALUE line, VALUE line_offset) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(line_offset) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_line;
    _c_line = FIX2INT(line);
    int _c_line_offset;
    _c_line_offset = FIX2INT(line_offset);
    // Method#body
    
    GtkMateScope* _c_return;
    _c_return = gtk_mate_scope_scope_at(gtk_mate_scope, _c_line, _c_line_offset);
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_start_line(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_scope_start_line(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_start_line_offset(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_scope_start_line_offset(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_start_loc(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    GtkMateTextLoc* _c_return;
    _c_return = gtk_mate_scope_start_loc(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_start_mark_set(VALUE self, VALUE line, VALUE line_offset, VALUE has_left_gravity) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(line_offset) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(has_left_gravity) != T_TRUE && TYPE(has_left_gravity) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    int _c_line;
    _c_line = FIX2INT(line);
    int _c_line_offset;
    _c_line_offset = FIX2INT(line_offset);
    gboolean _c_has_left_gravity;
          if (has_left_gravity == Qtrue)
          _c_has_left_gravity = TRUE;
      else
          _c_has_left_gravity = FALSE;

    // Method#body
    
    gtk_mate_scope_start_mark_set(gtk_mate_scope, _c_line, _c_line_offset, _c_has_left_gravity);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_scope_start_offset(VALUE self) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_scope_start_offset(gtk_mate_scope);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_scope_surface_identical_to(VALUE self, VALUE other) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateScope* _c_other;
    _c_other = _GTK_MATE_SCOPE_SELF(other);
    // Method#body
    
    gboolean _c_return;
    _c_return = gtk_mate_scope_surface_identical_to(gtk_mate_scope, _c_other);
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_scope_surface_identical_to_modulo_ending(VALUE self, VALUE other) {
    GtkMateScope* gtk_mate_scope = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateScope* _c_other;
    _c_other = _GTK_MATE_SCOPE_SELF(other);
    // Method#body
    
    gboolean _c_return;
    _c_return = gtk_mate_scope_surface_identical_to_modulo_ending(gtk_mate_scope, _c_other);
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}


/****  Gtk.Mate.SinglePattern methods *****/


static VALUE gtk_mate_single_pattern_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_single_pattern_new ());
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
    int len_val72 = RARRAY_LEN(rb_keys);
    {
        gint i;
        i = 0;
        for (; i < len_val72; i++) {
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

static VALUE rb_gtk_mate_single_pattern_get_match(VALUE self) {
    GtkMateSinglePattern* gtk_mate_single_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    OnigRx* _c_return = gtk_mate_single_pattern->match; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_single_pattern_set_match(VALUE self, VALUE match) {
    GtkMateSinglePattern* gtk_mate_single_pattern = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    OnigRx* _c_match;
    _c_match = _ONIG_RX_SELF(match);
    // ValaMemberSet#body
    gtk_mate_single_pattern->match = _c_match;
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
    int len_val73 = RARRAY_LEN(all_patterns);
    _c_all_patterns = gee_array_list_new (GTK_MATE_TYPE_PATTERN, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val73; i++) {
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


/****  Gtk.Mate.TextLoc methods *****/


static VALUE gtk_mate_text_loc_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_text_loc_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_text_loc_get_line(VALUE self) {
    GtkMateTextLoc* gtk_mate_text_loc = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    int _c_return = gtk_mate_text_loc->line; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_text_loc_set_line(VALUE self, VALUE line) {
    GtkMateTextLoc* gtk_mate_text_loc = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_line;
    _c_line = FIX2INT(line);
    // ValaMemberSet#body
    gtk_mate_text_loc->line = _c_line;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_text_loc_get_line_offset(VALUE self) {
    GtkMateTextLoc* gtk_mate_text_loc = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    int _c_return = gtk_mate_text_loc->line_offset; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_text_loc_set_line_offset(VALUE self, VALUE line_offset) {
    GtkMateTextLoc* gtk_mate_text_loc = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(line_offset) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_line_offset;
    _c_line_offset = FIX2INT(line_offset);
    // ValaMemberSet#body
    gtk_mate_text_loc->line_offset = _c_line_offset;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_text_loc_equal(VALUE self, VALUE t1, VALUE t2) {
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateTextLoc* _c_t1;
    _c_t1 = _GTK_MATE_TEXT_LOC_SELF(t1);
    GtkMateTextLoc* _c_t2;
    _c_t2 = _GTK_MATE_TEXT_LOC_SELF(t2);
    // Method#body
    
    gboolean _c_return;
    _c_return = gtk_mate_text_loc_equal(_c_t1, _c_t2);
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_text_loc_gt(VALUE self, VALUE t1, VALUE t2) {
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateTextLoc* _c_t1;
    _c_t1 = _GTK_MATE_TEXT_LOC_SELF(t1);
    GtkMateTextLoc* _c_t2;
    _c_t2 = _GTK_MATE_TEXT_LOC_SELF(t2);
    // Method#body
    
    gboolean _c_return;
    _c_return = gtk_mate_text_loc_gt(_c_t1, _c_t2);
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_text_loc_gte(VALUE self, VALUE t1, VALUE t2) {
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateTextLoc* _c_t1;
    _c_t1 = _GTK_MATE_TEXT_LOC_SELF(t1);
    GtkMateTextLoc* _c_t2;
    _c_t2 = _GTK_MATE_TEXT_LOC_SELF(t2);
    // Method#body
    
    gboolean _c_return;
    _c_return = gtk_mate_text_loc_gte(_c_t1, _c_t2);
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_text_loc_lt(VALUE self, VALUE t1, VALUE t2) {
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateTextLoc* _c_t1;
    _c_t1 = _GTK_MATE_TEXT_LOC_SELF(t1);
    GtkMateTextLoc* _c_t2;
    _c_t2 = _GTK_MATE_TEXT_LOC_SELF(t2);
    // Method#body
    
    gboolean _c_return;
    _c_return = gtk_mate_text_loc_lt(_c_t1, _c_t2);
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_text_loc_lte(VALUE self, VALUE t1, VALUE t2) {
    // Method#type_checks
    // Method#argument_type_conversions
    GtkMateTextLoc* _c_t1;
    _c_t1 = _GTK_MATE_TEXT_LOC_SELF(t1);
    GtkMateTextLoc* _c_t2;
    _c_t2 = _GTK_MATE_TEXT_LOC_SELF(t2);
    // Method#body
    
    gboolean _c_return;
    _c_return = gtk_mate_text_loc_lte(_c_t1, _c_t2);
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_text_loc_make(VALUE self, VALUE l, VALUE lo) {
    // Method#type_checks
    if (TYPE(l) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(lo) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_l;
    _c_l = FIX2INT(l);
    int _c_lo;
    _c_lo = FIX2INT(lo);
    // Method#body
    
    GtkMateTextLoc* _c_return;
    _c_return = gtk_mate_text_loc_make(_c_l, _c_lo);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_text_loc_to_s(VALUE self) {
    GtkMateTextLoc* gtk_mate_text_loc = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    char * _c_return;
    _c_return = gtk_mate_text_loc_to_s(gtk_mate_text_loc);
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


/****  Gtk.Mate.Theme methods *****/


static VALUE gtk_mate_theme_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_theme_new ());
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

static VALUE rb_gtk_mate_theme_get_cached_setting_for_scopes(VALUE self) {
    GtkMateTheme* gtk_mate_theme = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeHashMap* _c_return = gtk_mate_theme->cached_setting_for_scopes; 
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
                GtkMateThemeSetting* v;
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

static VALUE rb_gtk_mate_theme_set_cached_setting_for_scopes(VALUE self, VALUE cached_setting_for_scopes) {
    GtkMateTheme* gtk_mate_theme = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(cached_setting_for_scopes) != T_HASH) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a hash");
    }
    // Method#argument_type_conversions
    GeeHashMap* _c_cached_setting_for_scopes;
        // HashMap#ruby_to_c(:before, "cached_setting_for_scopes", "_c_cached_setting_for_scopes")
    _c_cached_setting_for_scopes = gee_hash_map_new (G_TYPE_STRING, ((GBoxedCopyFunc) (g_strdup)), g_free, GTK_MATE_TYPE_THEME_SETTING, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_str_hash, g_str_equal, g_direct_equal);
    VALUE rb_keys = rb_funcall(cached_setting_for_scopes, rb_intern("keys"), 0);
    int len_val74 = RARRAY_LEN(rb_keys);
    {
        gint i;
        i = 0;
        for (; i < len_val74; i++) {
            VALUE _rb_key = rb_ary_entry(rb_keys, (long) i);
            VALUE _rb_value = rb_hash_aref(cached_setting_for_scopes, _rb_key);
            char * _c__rb_key;
            _c__rb_key = g_strdup(STR2CSTR(_rb_key));
            GtkMateThemeSetting* _c__rb_value;
            _c__rb_value = _GTK_MATE_THEME_SETTING_SELF(_rb_value);
            gee_map_set (GEE_MAP (_c_cached_setting_for_scopes), _c__rb_key,  (_c__rb_value));
        }
    }

    // ValaMemberSet#body
    gtk_mate_theme->cached_setting_for_scopes = _c_cached_setting_for_scopes;
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
    int len_val75 = RARRAY_LEN(rb_keys);
    {
        gint i;
        i = 0;
        for (; i < len_val75; i++) {
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

static VALUE rb_gtk_mate_theme_get_is_initialized(VALUE self) {
    GtkMateTheme* gtk_mate_theme = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    gboolean _c_return = gtk_mate_theme->is_initialized; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_theme_set_is_initialized(VALUE self, VALUE is_initialized) {
    GtkMateTheme* gtk_mate_theme = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(is_initialized) != T_TRUE && TYPE(is_initialized) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    gboolean _c_is_initialized;
          if (is_initialized == Qtrue)
          _c_is_initialized = TRUE;
      else
          _c_is_initialized = FALSE;

    // ValaMemberSet#body
    gtk_mate_theme->is_initialized = _c_is_initialized;
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
        int it_val76;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val76 = 0; it_val76 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val76 = it_val76 + 1) {
            GtkMateThemeSetting* i_val77;
            i_val77 =  (gee_list_get (GEE_LIST (_c_return), it_val76));
            VALUE rb_ival77;
            rb_ival77 = GOBJ2RVAL(i_val77);
            rb_ary_store (_rb_return, it_val76, rb_ival77);
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
    int len_val78 = RARRAY_LEN(settings);
    _c_settings = gee_array_list_new (GTK_MATE_TYPE_THEME_SETTING, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val78; i++) {
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
        int it_val79;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val79 = 0; it_val79 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val79 = it_val79 + 1) {
            GtkMateTheme* i_val80;
            i_val80 =  (gee_list_get (GEE_LIST (_c_return), it_val79));
            VALUE rb_ival80;
            rb_ival80 = GOBJ2RVAL(i_val80);
            rb_ary_store (_rb_return, it_val79, rb_ival80);
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
    int len_val81 = RARRAY_LEN(themes);
    _c_themes = gee_array_list_new (GTK_MATE_TYPE_THEME, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val81; i++) {
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

static VALUE rb_gtk_mate_theme_init_for_use(VALUE self) {
    GtkMateTheme* gtk_mate_theme = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gtk_mate_theme_init_for_use(gtk_mate_theme);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_theme_settings_for_scope(VALUE self, VALUE scope, VALUE inner, VALUE exclude_setting) {
    GtkMateTheme* gtk_mate_theme = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(inner) != T_TRUE && TYPE(inner) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    GtkMateScope* _c_scope;
    _c_scope = _GTK_MATE_SCOPE_SELF(scope);
    gboolean _c_inner;
          if (inner == Qtrue)
          _c_inner = TRUE;
      else
          _c_inner = FALSE;

    GtkMateThemeSetting* _c_exclude_setting;
    if (exclude_setting == Qnil)
        _c_exclude_setting = NULL;
    else {
        _c_exclude_setting = _GTK_MATE_THEME_SETTING_SELF(exclude_setting);
    }
    // Method#body
    
    GtkMateThemeSetting* _c_return;
    _c_return = gtk_mate_theme_settings_for_scope(gtk_mate_theme, _c_scope, _c_inner, _c_exclude_setting);
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
        int it_val82;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val82 = 0; it_val82 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val82 = it_val82 + 1) {
            char * i_val83;
            i_val83 = (char *) (gee_list_get (GEE_LIST (_c_return), it_val82));
            VALUE rb_ival83;
                  if (i_val83 == NULL) {
        rb_ival83 = Qnil;
      }
      else {
        rb_ival83 = rb_str_new2(i_val83);
      }

            rb_ary_store (_rb_return, it_val82, rb_ival83);
        }
    }

    return _rb_return;
}


/****  Gtk.Mate.ThemeSetting methods *****/


static VALUE gtk_mate_theme_setting_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_theme_setting_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_theme_setting_get_matchers(VALUE self) {
    GtkMateThemeSetting* gtk_mate_theme_setting = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeArrayList* _c_return = gtk_mate_theme_setting->matchers; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val84;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val84 = 0; it_val84 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val84 = it_val84 + 1) {
            GtkMateMatcher* i_val85;
            i_val85 =  (gee_list_get (GEE_LIST (_c_return), it_val84));
            VALUE rb_ival85;
            rb_ival85 = GOBJ2RVAL(i_val85);
            rb_ary_store (_rb_return, it_val84, rb_ival85);
        }
    }

    return _rb_return;
}

static VALUE rb_gtk_mate_theme_setting_set_matchers(VALUE self, VALUE matchers) {
    GtkMateThemeSetting* gtk_mate_theme_setting = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(matchers) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_matchers;
        // ArrayListType#ruby_to_c(:before, "matchers", "_c_matchers")
    int len_val86 = RARRAY_LEN(matchers);
    _c_matchers = gee_array_list_new (GTK_MATE_TYPE_MATCHER, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val86; i++) {
            VALUE _rb_el = rb_ary_entry(matchers, (long) i);
            GtkMateMatcher* _c_el = _GTK_MATE_MATCHER_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_matchers), (_c_el));
        }
    }

    // ValaMemberSet#body
    gtk_mate_theme_setting->matchers = _c_matchers;
    // Method#return_type_conversion
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

static VALUE rb_gtk_mate_theme_setting_get_selector(VALUE self) {
    GtkMateThemeSetting* gtk_mate_theme_setting = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    char * _c_return = gtk_mate_theme_setting->selector; 
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

static VALUE rb_gtk_mate_theme_setting_set_selector(VALUE self, VALUE selector) {
    GtkMateThemeSetting* gtk_mate_theme_setting = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(selector) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_selector;
    _c_selector = g_strdup(STR2CSTR(selector));
    // ValaMemberSet#body
    gtk_mate_theme_setting->selector = _c_selector;
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
    int len_val87 = RARRAY_LEN(rb_keys);
    {
        gint i;
        i = 0;
        for (; i < len_val87; i++) {
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

static VALUE rb_gtk_mate_theme_setting_compile_scope_matchers(VALUE self) {
    GtkMateThemeSetting* gtk_mate_theme_setting = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gtk_mate_theme_setting_compile_scope_matchers(gtk_mate_theme_setting);
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


/****  Gtk.Mate.View methods *****/


static VALUE gtk_mate_view_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_view_new ());
    return Qnil;
}

static VALUE rb_gtk_mate_view_get_parser(VALUE self) {
    GtkMateView* gtk_mate_view = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    GtkMateParser* _c_return;
    _c_return = gtk_mate_view_get_parser(gtk_mate_view);
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}

static VALUE rb_gtk_mate_view_last_visible_line(VALUE self) {
    GtkMateView* gtk_mate_view = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = gtk_mate_view_last_visible_line(gtk_mate_view);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_gtk_mate_view_set_global_theme_settings(VALUE self) {
    GtkMateView* gtk_mate_view = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gtk_mate_view_set_global_theme_settings(gtk_mate_view);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_gtk_mate_view_set_theme_by_name(VALUE self, VALUE name) {
    GtkMateView* gtk_mate_view = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(name) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_name;
    _c_name = g_strdup(STR2CSTR(name));
    // Method#body
    
    gboolean _c_return;
    _c_return = gtk_mate_view_set_theme_by_name(gtk_mate_view, _c_name);
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_gtk_mate_view_value_changed_handler(VALUE self) {
    GtkMateView* gtk_mate_view = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gtk_mate_view_value_changed_handler(gtk_mate_view);
    // Method#return_type_conversion
    return Qnil;
}


/****  Onig methods *****/


/****  Onig.Match methods *****/


static VALUE onig_match_initialize(VALUE self) {

    G_INITIALIZE(self, onig_match_new ());
    return Qnil;
}

static VALUE rb_onig_match_get_count(VALUE self) {
    // Method#type_checks
    // Method#argument_type_conversions
    // StaticMemberGet#body
    int _c_return = onig_match_count;
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_onig_match_set_count(VALUE self, VALUE count) {
    // Method#type_checks
    if (TYPE(count) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_count;
    _c_count = FIX2INT(count);
    // StaticMemberSet#body
    onig_match_count = _c_count; 
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_onig_match_begin(VALUE self, VALUE capture) {
    OnigMatch* onig_match = RVAL2GOBJ(self);
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
    _c_return = onig_match_begin(onig_match, _c_capture);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_onig_match_end(VALUE self, VALUE capture) {
    OnigMatch* onig_match = RVAL2GOBJ(self);
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
    _c_return = onig_match_end(onig_match, _c_capture);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_onig_match_num_captures(VALUE self) {
    OnigMatch* onig_match = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = onig_match_num_captures(onig_match);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}


/****  Onig.OnigError methods *****/


static VALUE onig_onig_error_initialize(VALUE self) {

    G_INITIALIZE(self, onig_onig_error_new ());
    return Qnil;
}

static VALUE rb_onig_onig_error_get_code(VALUE self) {
    OnigOnigError* onig_onig_error = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    int _c_return = onig_onig_error->code; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_onig_onig_error_set_code(VALUE self, VALUE code) {
    OnigOnigError* onig_onig_error = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(code) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_code;
    _c_code = FIX2INT(code);
    // ValaMemberSet#body
    onig_onig_error->code = _c_code;
    // Method#return_type_conversion
    return Qnil;
}


/****  Onig.Rx methods *****/


static VALUE onig_rx_initialize(VALUE self) {

    G_INITIALIZE(self, onig_rx_new ());
    return Qnil;
}

static VALUE rb_onig_rx_get_matches_start_of_line(VALUE self) {
    OnigRx* onig_rx = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    gboolean _c_return = onig_rx->matches_start_of_line; 
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_onig_rx_set_matches_start_of_line(VALUE self, VALUE matches_start_of_line) {
    OnigRx* onig_rx = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(matches_start_of_line) != T_TRUE && TYPE(matches_start_of_line) != T_FALSE) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected true or false");
    }
    // Method#argument_type_conversions
    gboolean _c_matches_start_of_line;
          if (matches_start_of_line == Qtrue)
          _c_matches_start_of_line = TRUE;
      else
          _c_matches_start_of_line = FALSE;

    // ValaMemberSet#body
    onig_rx->matches_start_of_line = _c_matches_start_of_line;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_onig_rx_make1(VALUE self, VALUE pattern) {
    // Method#type_checks
    if (TYPE(pattern) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_pattern;
    _c_pattern = g_strdup(STR2CSTR(pattern));
    // Method#body
    
    OnigRx* _c_return;
    _c_return = onig_rx_make1(_c_pattern);
    // Method#return_type_conversion
    VALUE _rb_return;
    if (_c_return == NULL)
        _rb_return = Qnil;
    else {
        _rb_return = GOBJ2RVAL(_c_return);
    }
    return _rb_return;
}

static VALUE rb_onig_rx_search(VALUE self, VALUE target, VALUE start, VALUE end) {
    OnigRx* onig_rx = RVAL2GOBJ(self);
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
    
    OnigMatch* _c_return;
    _c_return = onig_rx_search(onig_rx, _c_target, _c_start, _c_end);
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
        int it_val88;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val88 = 0; it_val88 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val88 = it_val88 + 1) {
            PListNode* i_val89;
            i_val89 =  (gee_list_get (GEE_LIST (_c_return), it_val88));
            VALUE rb_ival89;
            rb_ival89 = GOBJ2RVAL(i_val89);
            rb_ary_store (_rb_return, it_val88, rb_ival89);
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
    int len_val90 = RARRAY_LEN(array);
    _c_array = gee_array_list_new (PLIST_TYPE_NODE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val90; i++) {
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
    int len_val91 = RARRAY_LEN(rb_keys);
    {
        gint i;
        i = 0;
        for (; i < len_val91; i++) {
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
              long val92;
              for(val92 = 0; val92 < _rb_return__length; val92++) {
                  rb_ary_store(_rb_return, val92, rb_str_new2(_c_return[val92]));
//                g_free(_c_return[val92]);
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


/****  PList.Integer methods *****/


static VALUE plist_integer_initialize(VALUE self) {

    G_INITIALIZE(self, plist_integer_new ());
    return Qnil;
}

static VALUE rb_plist_integer_get_value(VALUE self) {
    PListInteger* plist_integer = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    int _c_return = plist_integer->value; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_plist_integer_set_value(VALUE self, VALUE value) {
    PListInteger* plist_integer = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(value) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_value;
    _c_value = FIX2INT(value);
    // ValaMemberSet#body
    plist_integer->value = _c_value;
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


/****  StringHelper methods *****/


static VALUE string_helper_initialize(VALUE self) {

    G_INITIALIZE(self, string_helper_new ());
    return Qnil;
}

static VALUE rb_string_helper_gsub(VALUE self, VALUE start_string, VALUE match_string, VALUE replacement_string) {
    // Method#type_checks
    if (TYPE(start_string) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    if (TYPE(match_string) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    if (TYPE(replacement_string) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_start_string;
    _c_start_string = g_strdup(STR2CSTR(start_string));
    char * _c_match_string;
    _c_match_string = g_strdup(STR2CSTR(match_string));
    char * _c_replacement_string;
    _c_replacement_string = g_strdup(STR2CSTR(replacement_string));
    // Method#body
    
    char * _c_return;
    _c_return = string_helper_gsub(_c_start_string, _c_match_string, _c_replacement_string);
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

static VALUE rb_string_helper_occurrences(VALUE self, VALUE s, VALUE t) {
    // Method#type_checks
    if (TYPE(s) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    if (TYPE(t) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    // Method#argument_type_conversions
    char * _c_s;
    _c_s = g_strdup(STR2CSTR(s));
    char * _c_t;
    _c_t = g_strdup(STR2CSTR(t));
    // Method#body
    
    GeeArrayList* _c_return;
    _c_return = string_helper_occurrences(_c_s, _c_t);
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val93;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val93 = 0; it_val93 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val93 = it_val93 + 1) {
            int i_val94;
            i_val94 = GPOINTER_TO_INT (gee_list_get (GEE_LIST (_c_return), it_val93));
            VALUE rb_ival94;
            rb_ival94 = INT2FIX(i_val94);
            rb_ary_store (_rb_return, it_val93, rb_ival94);
        }
    }

    return _rb_return;
}


/****  RangeSet methods *****/


static VALUE range_set_initialize(VALUE self) {

    G_INITIALIZE(self, range_set_new ());
    return Qnil;
}

static VALUE rb_range_set_get_ranges(VALUE self) {
    RangeSet* range_set = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    GeeArrayList* _c_return = range_set->ranges; 
    // Method#return_type_conversion
    VALUE _rb_return; 
        // ArrayListType#c_to_ruby(:after, "_c_return", "_rb_return")
    if (_c_return == NULL) {
        _rb_return = Qnil;
    }
    else {
        int it_val95;
        _rb_return = rb_ary_new2((long) gee_collection_get_size (GEE_COLLECTION (_c_return)));
        for (it_val95 = 0; it_val95 < gee_collection_get_size (GEE_COLLECTION (_c_return)); it_val95 = it_val95 + 1) {
            RangeSetRange* i_val96;
            i_val96 =  (gee_list_get (GEE_LIST (_c_return), it_val95));
            VALUE rb_ival96;
            rb_ival96 = GOBJ2RVAL(i_val96);
            rb_ary_store (_rb_return, it_val95, rb_ival96);
        }
    }

    return _rb_return;
}

static VALUE rb_range_set_set_ranges(VALUE self, VALUE ranges) {
    RangeSet* range_set = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(ranges) != T_ARRAY) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected an array");
    }
    // Method#argument_type_conversions
    GeeArrayList* _c_ranges;
        // ArrayListType#ruby_to_c(:before, "ranges", "_c_ranges")
    int len_val97 = RARRAY_LEN(ranges);
    _c_ranges = gee_array_list_new (RANGE_SET_TYPE_RANGE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
    {
        gint i;
        i = 0;
        for (; i < len_val97; i++) {
            VALUE _rb_el = rb_ary_entry(ranges, (long) i);
            RangeSetRange* _c_el = _RANGE_SET_RANGE_SELF(_rb_el);
            gee_collection_add (GEE_COLLECTION (_c_ranges), (_c_el));
        }
    }

    // ValaMemberSet#body
    range_set->ranges = _c_ranges;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_range_set_add(VALUE self, VALUE a, VALUE b) {
    RangeSet* range_set = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(a) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(b) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_a;
    _c_a = FIX2INT(a);
    int _c_b;
    _c_b = FIX2INT(b);
    // Method#body
    
    range_set_add(range_set, _c_a, _c_b);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_range_set_is_empty(VALUE self) {
    RangeSet* range_set = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    gboolean _c_return;
    _c_return = range_set_is_empty(range_set);
    // Method#return_type_conversion
    VALUE _rb_return; 
          if (_c_return == TRUE)
          _rb_return = Qtrue;
      else
          _rb_return = Qfalse;

    return _rb_return;
}

static VALUE rb_range_set_length(VALUE self) {
    RangeSet* range_set = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = range_set_length(range_set);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_range_set_max(VALUE self, VALUE a, VALUE b) {
    RangeSet* range_set = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(a) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(b) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_a;
    _c_a = FIX2INT(a);
    int _c_b;
    _c_b = FIX2INT(b);
    // Method#body
    
    int _c_return;
    _c_return = range_set_max(range_set, _c_a, _c_b);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_range_set_merge(VALUE self, VALUE ix) {
    RangeSet* range_set = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(ix) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_ix;
    _c_ix = FIX2INT(ix);
    // Method#body
    
    range_set_merge(range_set, _c_ix);
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_range_set_min(VALUE self, VALUE a, VALUE b) {
    RangeSet* range_set = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(a) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    if (TYPE(b) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_a;
    _c_a = FIX2INT(a);
    int _c_b;
    _c_b = FIX2INT(b);
    // Method#body
    
    int _c_return;
    _c_return = range_set_min(range_set, _c_a, _c_b);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_range_set_present(VALUE self) {
    RangeSet* range_set = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    char * _c_return;
    _c_return = range_set_present(range_set);
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

static VALUE rb_range_set_size(VALUE self) {
    RangeSet* range_set = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // Method#body
    
    int _c_return;
    _c_return = range_set_size(range_set);
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}


/****  RangeSet.Range methods *****/


static VALUE range_set_range_initialize(VALUE self) {

    G_INITIALIZE(self, range_set_range_new ());
    return Qnil;
}

static VALUE rb_range_set_range_get_a(VALUE self) {
    RangeSetRange* range_set_range = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    int _c_return = range_set_range->a; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_range_set_range_set_a(VALUE self, VALUE a) {
    RangeSetRange* range_set_range = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(a) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_a;
    _c_a = FIX2INT(a);
    // ValaMemberSet#body
    range_set_range->a = _c_a;
    // Method#return_type_conversion
    return Qnil;
}

static VALUE rb_range_set_range_get_b(VALUE self) {
    RangeSetRange* range_set_range = RVAL2GOBJ(self);
    // Method#type_checks
    // Method#argument_type_conversions
    // ValaMemberGet#body
    int _c_return = range_set_range->b; 
    // Method#return_type_conversion
    VALUE _rb_return; 
    _rb_return = INT2FIX(_c_return);
    return _rb_return;
}

static VALUE rb_range_set_range_set_b(VALUE self, VALUE b) {
    RangeSetRange* range_set_range = RVAL2GOBJ(self);
    // Method#type_checks
    if (TYPE(b) != T_FIXNUM) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a small integer");
    }
    // Method#argument_type_conversions
    int _c_b;
    _c_b = FIX2INT(b);
    // ValaMemberSet#body
    range_set_range->b = _c_b;
    // Method#return_type_conversion
    return Qnil;
}

void Init_gtkmateview_rb() {
    rb_vala_error = rb_define_class("ValaError", rb_eval_string("Exception"));
    rbc_gtk = rb_eval_string("Gtk");
    rbc_onig = rb_define_class("Onig", rb_cObject);
    rbc_plist = rb_define_class("PList", rb_cObject);
    rb_define_singleton_method(rbc_plist, "parse", rb_plist_parse, 1);
    rb_define_singleton_method(rbc_plist, "print_plist", rb_plist_print_plist, 2);
    rbc_onig_rx = G_DEF_CLASS(onig_rx_get_type(), "Rx", rbc_onig);
    rb_define_method(rbc_onig_rx, "initialize", onig_rx_initialize, 0);
    rb_define_method(rbc_onig_rx, "matches_start_of_line", rb_onig_rx_get_matches_start_of_line, 0);
    rb_define_method(rbc_onig_rx, "matches_start_of_line=", rb_onig_rx_set_matches_start_of_line, 1);
    rb_define_singleton_method(rbc_onig_rx, "make1", rb_onig_rx_make1, 1);
    rb_define_method(rbc_onig_rx, "search", rb_onig_rx_search, 3);
    rbc_gtk_mate = rb_define_class_under(rbc_gtk, "Mate", rb_cObject);
    rb_define_singleton_method(rbc_gtk_mate, "bundle_dirs", rb_gtk_mate_bundle_dirs, 0);
    rb_define_singleton_method(rbc_gtk_mate, "load_bundles", rb_gtk_mate_load_bundles, 0);
    rb_define_singleton_method(rbc_gtk_mate, "load_themes", rb_gtk_mate_load_themes, 0);
    rb_define_singleton_method(rbc_gtk_mate, "textmate_share_dir", rb_gtk_mate_textmate_share_dir, 0);
    rbc_range_set = G_DEF_CLASS(range_set_get_type(), "RangeSet", rb_cObject);
    rb_define_method(rbc_range_set, "initialize", range_set_initialize, 0);
    rb_define_method(rbc_range_set, "ranges", rb_range_set_get_ranges, 0);
    rb_define_method(rbc_range_set, "ranges=", rb_range_set_set_ranges, 1);
    rb_define_method(rbc_range_set, "add", rb_range_set_add, 2);
    rb_define_method(rbc_range_set, "is_empty", rb_range_set_is_empty, 0);
    rb_define_method(rbc_range_set, "length", rb_range_set_length, 0);
    rb_define_method(rbc_range_set, "max", rb_range_set_max, 2);
    rb_define_method(rbc_range_set, "merge", rb_range_set_merge, 1);
    rb_define_method(rbc_range_set, "min", rb_range_set_min, 2);
    rb_define_method(rbc_range_set, "present", rb_range_set_present, 0);
    rb_define_method(rbc_range_set, "size", rb_range_set_size, 0);
    rbc_plist_node = G_DEF_CLASS(plist_node_get_type(), "Node", rbc_plist);
    rb_define_method(rbc_plist_node, "initialize", plist_node_initialize, 0);
    rbc_onig_match = G_DEF_CLASS(onig_match_get_type(), "Match", rbc_onig);
    rb_define_method(rbc_onig_match, "initialize", onig_match_initialize, 0);
    rb_define_singleton_method(rbc_onig_match, "count", rb_onig_match_get_count, 0);
    rb_define_singleton_method(rbc_onig_match, "count=", rb_onig_match_set_count, 1);
    rb_define_method(rbc_onig_match, "begin", rb_onig_match_begin, 1);
    rb_define_method(rbc_onig_match, "end", rb_onig_match_end, 1);
    rb_define_method(rbc_onig_match, "num_captures", rb_onig_match_num_captures, 0);
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
    rbc_string_helper = G_DEF_CLASS(string_helper_get_type(), "StringHelper", rb_cObject);
    rb_define_method(rbc_string_helper, "initialize", string_helper_initialize, 0);
    rb_define_singleton_method(rbc_string_helper, "gsub", rb_string_helper_gsub, 3);
    rb_define_singleton_method(rbc_string_helper, "occurrences", rb_string_helper_occurrences, 2);
    rbc_plist_string = G_DEF_CLASS(plist_string_get_type(), "String", rbc_plist);
    rb_define_method(rbc_plist_string, "initialize", plist_string_initialize, 0);
    rb_define_method(rbc_plist_string, "str", rb_plist_string_get_str, 0);
    rb_define_method(rbc_plist_string, "str=", rb_plist_string_set_str, 1);
    rbc_plist_integer = G_DEF_CLASS(plist_integer_get_type(), "Integer", rbc_plist);
    rb_define_method(rbc_plist_integer, "initialize", plist_integer_initialize, 0);
    rb_define_method(rbc_plist_integer, "value", rb_plist_integer_get_value, 0);
    rb_define_method(rbc_plist_integer, "value=", rb_plist_integer_set_value, 1);
    rbc_gtk_mate_view = G_DEF_CLASS(gtk_mate_view_get_type(), "View", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_view, "initialize", gtk_mate_view_initialize, 0);
    rb_define_method(rbc_gtk_mate_view, "get_parser", rb_gtk_mate_view_get_parser, 0);
    rb_define_method(rbc_gtk_mate_view, "last_visible_line", rb_gtk_mate_view_last_visible_line, 0);
    rb_define_method(rbc_gtk_mate_view, "set_global_theme_settings", rb_gtk_mate_view_set_global_theme_settings, 0);
    rb_define_method(rbc_gtk_mate_view, "set_theme_by_name", rb_gtk_mate_view_set_theme_by_name, 1);
    rb_define_method(rbc_gtk_mate_view, "value_changed_handler", rb_gtk_mate_view_value_changed_handler, 0);
    rbc_gtk_mate_theme = G_DEF_CLASS(gtk_mate_theme_get_type(), "Theme", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_theme, "initialize", gtk_mate_theme_initialize, 0);
    rb_define_method(rbc_gtk_mate_theme, "author", rb_gtk_mate_theme_get_author, 0);
    rb_define_method(rbc_gtk_mate_theme, "author=", rb_gtk_mate_theme_set_author, 1);
    rb_define_method(rbc_gtk_mate_theme, "cached_setting_for_scopes", rb_gtk_mate_theme_get_cached_setting_for_scopes, 0);
    rb_define_method(rbc_gtk_mate_theme, "cached_setting_for_scopes=", rb_gtk_mate_theme_set_cached_setting_for_scopes, 1);
    rb_define_method(rbc_gtk_mate_theme, "global_settings", rb_gtk_mate_theme_get_global_settings, 0);
    rb_define_method(rbc_gtk_mate_theme, "global_settings=", rb_gtk_mate_theme_set_global_settings, 1);
    rb_define_method(rbc_gtk_mate_theme, "is_initialized", rb_gtk_mate_theme_get_is_initialized, 0);
    rb_define_method(rbc_gtk_mate_theme, "is_initialized=", rb_gtk_mate_theme_set_is_initialized, 1);
    rb_define_method(rbc_gtk_mate_theme, "name", rb_gtk_mate_theme_get_name, 0);
    rb_define_method(rbc_gtk_mate_theme, "name=", rb_gtk_mate_theme_set_name, 1);
    rb_define_method(rbc_gtk_mate_theme, "settings", rb_gtk_mate_theme_get_settings, 0);
    rb_define_method(rbc_gtk_mate_theme, "settings=", rb_gtk_mate_theme_set_settings, 1);
    rb_define_singleton_method(rbc_gtk_mate_theme, "themes", rb_gtk_mate_theme_get_themes, 0);
    rb_define_singleton_method(rbc_gtk_mate_theme, "themes=", rb_gtk_mate_theme_set_themes, 1);
    rb_define_singleton_method(rbc_gtk_mate_theme, "create_from_plist", rb_gtk_mate_theme_create_from_plist, 1);
    rb_define_method(rbc_gtk_mate_theme, "init_for_use", rb_gtk_mate_theme_init_for_use, 0);
    rb_define_method(rbc_gtk_mate_theme, "settings_for_scope", rb_gtk_mate_theme_settings_for_scope, 3);
    rb_define_singleton_method(rbc_gtk_mate_theme, "theme_filenames", rb_gtk_mate_theme_theme_filenames, 0);
    rbc_range_set_range = G_DEF_CLASS(range_set_range_get_type(), "Range", rbc_range_set);
    rb_define_method(rbc_range_set_range, "initialize", range_set_range_initialize, 0);
    rb_define_method(rbc_range_set_range, "a", rb_range_set_range_get_a, 0);
    rb_define_method(rbc_range_set_range, "a=", rb_range_set_range_set_a, 1);
    rb_define_method(rbc_range_set_range, "b", rb_range_set_range_get_b, 0);
    rb_define_method(rbc_range_set_range, "b=", rb_range_set_range_set_b, 1);
    rbc_onig_onig_error = G_DEF_CLASS(onig_onig_error_get_type(), "OnigError", rbc_onig);
    rb_define_method(rbc_onig_onig_error, "initialize", onig_onig_error_initialize, 0);
    rb_define_method(rbc_onig_onig_error, "code", rb_onig_onig_error_get_code, 0);
    rb_define_method(rbc_onig_onig_error, "code=", rb_onig_onig_error_set_code, 1);
    rbc_gtk_mate_scope = G_DEF_CLASS(gtk_mate_scope_get_type(), "Scope", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_scope, "initialize", gtk_mate_scope_initialize, 2);
    rb_define_method(rbc_gtk_mate_scope, "begin_match_string", rb_gtk_mate_scope_get_begin_match_string, 0);
    rb_define_method(rbc_gtk_mate_scope, "begin_match_string=", rb_gtk_mate_scope_set_begin_match_string, 1);
    rb_define_method(rbc_gtk_mate_scope, "bg_colour", rb_gtk_mate_scope_get_bg_colour, 0);
    rb_define_method(rbc_gtk_mate_scope, "bg_colour=", rb_gtk_mate_scope_set_bg_colour, 1);
    rb_define_method(rbc_gtk_mate_scope, "close_match", rb_gtk_mate_scope_get_close_match, 0);
    rb_define_method(rbc_gtk_mate_scope, "close_match=", rb_gtk_mate_scope_set_close_match, 1);
    rb_define_method(rbc_gtk_mate_scope, "closing_regex", rb_gtk_mate_scope_get_closing_regex, 0);
    rb_define_method(rbc_gtk_mate_scope, "closing_regex=", rb_gtk_mate_scope_set_closing_regex, 1);
    rb_define_method(rbc_gtk_mate_scope, "dummy_end_loc", rb_gtk_mate_scope_get_dummy_end_loc, 0);
    rb_define_method(rbc_gtk_mate_scope, "dummy_end_loc=", rb_gtk_mate_scope_set_dummy_end_loc, 1);
    rb_define_method(rbc_gtk_mate_scope, "dummy_start_loc", rb_gtk_mate_scope_get_dummy_start_loc, 0);
    rb_define_method(rbc_gtk_mate_scope, "dummy_start_loc=", rb_gtk_mate_scope_set_dummy_start_loc, 1);
    rb_define_method(rbc_gtk_mate_scope, "end_mark", rb_gtk_mate_scope_get_end_mark, 0);
    rb_define_method(rbc_gtk_mate_scope, "end_mark=", rb_gtk_mate_scope_set_end_mark, 1);
    rb_define_method(rbc_gtk_mate_scope, "end_match_string", rb_gtk_mate_scope_get_end_match_string, 0);
    rb_define_method(rbc_gtk_mate_scope, "end_match_string=", rb_gtk_mate_scope_set_end_match_string, 1);
    rb_define_method(rbc_gtk_mate_scope, "fg_colour", rb_gtk_mate_scope_get_fg_colour, 0);
    rb_define_method(rbc_gtk_mate_scope, "fg_colour=", rb_gtk_mate_scope_set_fg_colour, 1);
    rb_define_method(rbc_gtk_mate_scope, "indent", rb_gtk_mate_scope_get_indent, 0);
    rb_define_method(rbc_gtk_mate_scope, "indent=", rb_gtk_mate_scope_set_indent, 1);
    rb_define_method(rbc_gtk_mate_scope, "inner_end_mark", rb_gtk_mate_scope_get_inner_end_mark, 0);
    rb_define_method(rbc_gtk_mate_scope, "inner_end_mark=", rb_gtk_mate_scope_set_inner_end_mark, 1);
    rb_define_method(rbc_gtk_mate_scope, "inner_start_mark", rb_gtk_mate_scope_get_inner_start_mark, 0);
    rb_define_method(rbc_gtk_mate_scope, "inner_start_mark=", rb_gtk_mate_scope_set_inner_start_mark, 1);
    rb_define_method(rbc_gtk_mate_scope, "inner_tag", rb_gtk_mate_scope_get_inner_tag, 0);
    rb_define_method(rbc_gtk_mate_scope, "inner_tag=", rb_gtk_mate_scope_set_inner_tag, 1);
    rb_define_method(rbc_gtk_mate_scope, "is_capture", rb_gtk_mate_scope_get_is_capture, 0);
    rb_define_method(rbc_gtk_mate_scope, "is_capture=", rb_gtk_mate_scope_set_is_capture, 1);
    rb_define_method(rbc_gtk_mate_scope, "is_open", rb_gtk_mate_scope_get_is_open, 0);
    rb_define_method(rbc_gtk_mate_scope, "is_open=", rb_gtk_mate_scope_set_is_open, 1);
    rb_define_method(rbc_gtk_mate_scope, "open_match", rb_gtk_mate_scope_get_open_match, 0);
    rb_define_method(rbc_gtk_mate_scope, "open_match=", rb_gtk_mate_scope_set_open_match, 1);
    rb_define_method(rbc_gtk_mate_scope, "parent", rb_gtk_mate_scope_get_parent, 0);
    rb_define_method(rbc_gtk_mate_scope, "parent=", rb_gtk_mate_scope_set_parent, 1);
    rb_define_method(rbc_gtk_mate_scope, "pattern", rb_gtk_mate_scope_get_pattern, 0);
    rb_define_method(rbc_gtk_mate_scope, "pattern=", rb_gtk_mate_scope_set_pattern, 1);
    rb_define_singleton_method(rbc_gtk_mate_scope, "scope_count", rb_gtk_mate_scope_get_scope_count, 0);
    rb_define_singleton_method(rbc_gtk_mate_scope, "scope_count=", rb_gtk_mate_scope_set_scope_count, 1);
    rb_define_method(rbc_gtk_mate_scope, "start_mark", rb_gtk_mate_scope_get_start_mark, 0);
    rb_define_method(rbc_gtk_mate_scope, "start_mark=", rb_gtk_mate_scope_set_start_mark, 1);
    rb_define_method(rbc_gtk_mate_scope, "tag", rb_gtk_mate_scope_get_tag, 0);
    rb_define_method(rbc_gtk_mate_scope, "tag=", rb_gtk_mate_scope_set_tag, 1);
    rb_define_method(rbc_gtk_mate_scope, "theme_setting", rb_gtk_mate_scope_get_theme_setting, 0);
    rb_define_method(rbc_gtk_mate_scope, "theme_setting=", rb_gtk_mate_scope_set_theme_setting, 1);
    rb_define_method(rbc_gtk_mate_scope, "add_child", rb_gtk_mate_scope_add_child, 1);
    rb_define_method(rbc_gtk_mate_scope, "clear_after", rb_gtk_mate_scope_clear_after, 2);
    rb_define_method(rbc_gtk_mate_scope, "contains_loc", rb_gtk_mate_scope_contains_loc, 1);
    rb_define_method(rbc_gtk_mate_scope, "delete_any_on_line_not_in", rb_gtk_mate_scope_delete_any_on_line_not_in, 2);
    rb_define_method(rbc_gtk_mate_scope, "delete_child", rb_gtk_mate_scope_delete_child, 1);
    rb_define_method(rbc_gtk_mate_scope, "end_line", rb_gtk_mate_scope_end_line, 0);
    rb_define_method(rbc_gtk_mate_scope, "end_line_offset", rb_gtk_mate_scope_end_line_offset, 0);
    rb_define_method(rbc_gtk_mate_scope, "end_loc", rb_gtk_mate_scope_end_loc, 0);
    rb_define_method(rbc_gtk_mate_scope, "end_mark_set", rb_gtk_mate_scope_end_mark_set, 3);
    rb_define_method(rbc_gtk_mate_scope, "end_offset", rb_gtk_mate_scope_end_offset, 0);
    rb_define_method(rbc_gtk_mate_scope, "first_child_after", rb_gtk_mate_scope_first_child_after, 1);
    rb_define_method(rbc_gtk_mate_scope, "hierarchy_names", rb_gtk_mate_scope_hierarchy_names, 1);
    rb_define_method(rbc_gtk_mate_scope, "inner_end_line", rb_gtk_mate_scope_inner_end_line, 0);
    rb_define_method(rbc_gtk_mate_scope, "inner_end_line_offset", rb_gtk_mate_scope_inner_end_line_offset, 0);
    rb_define_method(rbc_gtk_mate_scope, "inner_end_loc", rb_gtk_mate_scope_inner_end_loc, 0);
    rb_define_method(rbc_gtk_mate_scope, "inner_end_mark_set", rb_gtk_mate_scope_inner_end_mark_set, 3);
    rb_define_method(rbc_gtk_mate_scope, "inner_end_offset", rb_gtk_mate_scope_inner_end_offset, 0);
    rb_define_method(rbc_gtk_mate_scope, "inner_start_line", rb_gtk_mate_scope_inner_start_line, 0);
    rb_define_method(rbc_gtk_mate_scope, "inner_start_line_offset", rb_gtk_mate_scope_inner_start_line_offset, 0);
    rb_define_method(rbc_gtk_mate_scope, "inner_start_loc", rb_gtk_mate_scope_inner_start_loc, 0);
    rb_define_method(rbc_gtk_mate_scope, "inner_start_mark_set", rb_gtk_mate_scope_inner_start_mark_set, 3);
    rb_define_method(rbc_gtk_mate_scope, "inner_start_offset", rb_gtk_mate_scope_inner_start_offset, 0);
    rb_define_method(rbc_gtk_mate_scope, "is_root", rb_gtk_mate_scope_is_root, 0);
    rb_define_method(rbc_gtk_mate_scope, "nearest_background_colour", rb_gtk_mate_scope_nearest_background_colour, 0);
    rb_define_method(rbc_gtk_mate_scope, "nearest_background_colour1", rb_gtk_mate_scope_nearest_background_colour1, 0);
    rb_define_method(rbc_gtk_mate_scope, "nearest_foreground_colour", rb_gtk_mate_scope_nearest_foreground_colour, 0);
    rb_define_method(rbc_gtk_mate_scope, "nearest_foreground_colour1", rb_gtk_mate_scope_nearest_foreground_colour1, 0);
    rb_define_method(rbc_gtk_mate_scope, "overlaps_with", rb_gtk_mate_scope_overlaps_with, 1);
    rb_define_method(rbc_gtk_mate_scope, "pretty", rb_gtk_mate_scope_pretty, 1);
    rb_define_method(rbc_gtk_mate_scope, "priority", rb_gtk_mate_scope_priority, 1);
    rb_define_method(rbc_gtk_mate_scope, "root", rb_gtk_mate_scope_root, 0);
    rb_define_method(rbc_gtk_mate_scope, "scope_at", rb_gtk_mate_scope_scope_at, 2);
    rb_define_method(rbc_gtk_mate_scope, "start_line", rb_gtk_mate_scope_start_line, 0);
    rb_define_method(rbc_gtk_mate_scope, "start_line_offset", rb_gtk_mate_scope_start_line_offset, 0);
    rb_define_method(rbc_gtk_mate_scope, "start_loc", rb_gtk_mate_scope_start_loc, 0);
    rb_define_method(rbc_gtk_mate_scope, "start_mark_set", rb_gtk_mate_scope_start_mark_set, 3);
    rb_define_method(rbc_gtk_mate_scope, "start_offset", rb_gtk_mate_scope_start_offset, 0);
    rb_define_method(rbc_gtk_mate_scope, "surface_identical_to", rb_gtk_mate_scope_surface_identical_to, 1);
    rb_define_method(rbc_gtk_mate_scope, "surface_identical_to_modulo_ending", rb_gtk_mate_scope_surface_identical_to_modulo_ending, 1);
    rbc_gtk_mate_bundle = G_DEF_CLASS(gtk_mate_bundle_get_type(), "Bundle", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_bundle, "initialize", gtk_mate_bundle_initialize, 1);
    rb_define_method(rbc_gtk_mate_bundle, "grammars", rb_gtk_mate_bundle_get_grammars, 0);
    rb_define_method(rbc_gtk_mate_bundle, "grammars=", rb_gtk_mate_bundle_set_grammars, 1);
    rbc_gtk_mate_marker = G_DEF_CLASS(gtk_mate_marker_get_type(), "Marker", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_marker, "initialize", gtk_mate_marker_initialize, 0);
    rb_define_method(rbc_gtk_mate_marker, "from", rb_gtk_mate_marker_get_from, 0);
    rb_define_method(rbc_gtk_mate_marker, "from=", rb_gtk_mate_marker_set_from, 1);
    rb_define_method(rbc_gtk_mate_marker, "hint", rb_gtk_mate_marker_get_hint, 0);
    rb_define_method(rbc_gtk_mate_marker, "hint=", rb_gtk_mate_marker_set_hint, 1);
    rb_define_method(rbc_gtk_mate_marker, "is_close_scope", rb_gtk_mate_marker_get_is_close_scope, 0);
    rb_define_method(rbc_gtk_mate_marker, "is_close_scope=", rb_gtk_mate_marker_set_is_close_scope, 1);
    rb_define_method(rbc_gtk_mate_marker, "match", rb_gtk_mate_marker_get_match, 0);
    rb_define_method(rbc_gtk_mate_marker, "match=", rb_gtk_mate_marker_set_match, 1);
    rb_define_method(rbc_gtk_mate_marker, "pattern", rb_gtk_mate_marker_get_pattern, 0);
    rb_define_method(rbc_gtk_mate_marker, "pattern=", rb_gtk_mate_marker_set_pattern, 1);
    rbc_gtk_mate_parser = G_DEF_CLASS(gtk_mate_parser_get_type(), "Parser", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_parser, "initialize", gtk_mate_parser_initialize, 0);
    rb_define_method(rbc_gtk_mate_parser, "always_parse_all", rb_gtk_mate_parser_get_always_parse_all, 0);
    rb_define_method(rbc_gtk_mate_parser, "always_parse_all=", rb_gtk_mate_parser_set_always_parse_all, 1);
    rb_define_method(rbc_gtk_mate_parser, "changes", rb_gtk_mate_parser_get_changes, 0);
    rb_define_method(rbc_gtk_mate_parser, "changes=", rb_gtk_mate_parser_set_changes, 1);
    rb_define_method(rbc_gtk_mate_parser, "deactivation_level", rb_gtk_mate_parser_get_deactivation_level, 0);
    rb_define_method(rbc_gtk_mate_parser, "deactivation_level=", rb_gtk_mate_parser_set_deactivation_level, 1);
    rb_define_method(rbc_gtk_mate_parser, "dummy_tag", rb_gtk_mate_parser_get_dummy_tag, 0);
    rb_define_method(rbc_gtk_mate_parser, "dummy_tag=", rb_gtk_mate_parser_set_dummy_tag, 1);
    rb_define_method(rbc_gtk_mate_parser, "dummy_tag2", rb_gtk_mate_parser_get_dummy_tag2, 0);
    rb_define_method(rbc_gtk_mate_parser, "dummy_tag2=", rb_gtk_mate_parser_set_dummy_tag2, 1);
    rb_define_singleton_method(rbc_gtk_mate_parser, "existing_parsers", rb_gtk_mate_parser_get_existing_parsers, 0);
    rb_define_singleton_method(rbc_gtk_mate_parser, "existing_parsers=", rb_gtk_mate_parser_set_existing_parsers, 1);
    rb_define_method(rbc_gtk_mate_parser, "last_visible_line", rb_gtk_mate_parser_get_last_visible_line, 0);
    rb_define_method(rbc_gtk_mate_parser, "last_visible_line=", rb_gtk_mate_parser_set_last_visible_line, 1);
    rb_define_method(rbc_gtk_mate_parser, "parsed_upto", rb_gtk_mate_parser_get_parsed_upto, 0);
    rb_define_method(rbc_gtk_mate_parser, "parsed_upto=", rb_gtk_mate_parser_set_parsed_upto, 1);
    rb_define_method(rbc_gtk_mate_parser, "root", rb_gtk_mate_parser_get_root, 0);
    rb_define_method(rbc_gtk_mate_parser, "root=", rb_gtk_mate_parser_set_root, 1);
    rb_define_method(rbc_gtk_mate_parser, "added_tag", rb_gtk_mate_parser_added_tag, 1);
    rb_define_method(rbc_gtk_mate_parser, "change_theme", rb_gtk_mate_parser_change_theme, 1);
    rb_define_method(rbc_gtk_mate_parser, "clear_line", rb_gtk_mate_parser_clear_line, 5);
    rb_define_method(rbc_gtk_mate_parser, "close", rb_gtk_mate_parser_close, 0);
    rb_define_method(rbc_gtk_mate_parser, "close_scope", rb_gtk_mate_parser_close_scope, 8);
    rb_define_method(rbc_gtk_mate_parser, "collect_child_captures", rb_gtk_mate_parser_collect_child_captures, 5);
    rb_define_method(rbc_gtk_mate_parser, "connect_buffer_signals", rb_gtk_mate_parser_connect_buffer_signals, 0);
    rb_define_singleton_method(rbc_gtk_mate_parser, "create", rb_gtk_mate_parser_create, 2);
    rb_define_method(rbc_gtk_mate_parser, "get_expected_scope", rb_gtk_mate_parser_get_expected_scope, 3);
    rb_define_method(rbc_gtk_mate_parser, "handle_captures", rb_gtk_mate_parser_handle_captures, 6);
    rb_define_method(rbc_gtk_mate_parser, "is_parsing", rb_gtk_mate_parser_is_parsing, 0);
    rb_define_method(rbc_gtk_mate_parser, "last_line_parsed", rb_gtk_mate_parser_last_line_parsed, 0);
    rb_define_method(rbc_gtk_mate_parser, "last_visible_line_changed", rb_gtk_mate_parser_last_visible_line_changed, 1);
    rb_define_method(rbc_gtk_mate_parser, "make_closing_regex", rb_gtk_mate_parser_make_closing_regex, 3);
    rb_define_method(rbc_gtk_mate_parser, "make_root", rb_gtk_mate_parser_make_root, 0);
    rb_define_method(rbc_gtk_mate_parser, "open_scope", rb_gtk_mate_parser_open_scope, 9);
    rb_define_method(rbc_gtk_mate_parser, "recolour_children", rb_gtk_mate_parser_recolour_children, 1);
    rb_define_method(rbc_gtk_mate_parser, "remove_tags", rb_gtk_mate_parser_remove_tags, 0);
    rb_define_method(rbc_gtk_mate_parser, "reset_table_priorities", rb_gtk_mate_parser_reset_table_priorities, 0);
    rb_define_method(rbc_gtk_mate_parser, "single_scope", rb_gtk_mate_parser_single_scope, 9);
    rb_define_method(rbc_gtk_mate_parser, "start_parsing", rb_gtk_mate_parser_start_parsing, 0);
    rb_define_method(rbc_gtk_mate_parser, "stop_parsing", rb_gtk_mate_parser_stop_parsing, 0);
    rbc_gtk_mate_buffer = G_DEF_CLASS(gtk_mate_buffer_get_type(), "Buffer", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_buffer, "initialize", gtk_mate_buffer_initialize, 0);
    rb_define_singleton_method(rbc_gtk_mate_buffer, "bundles", rb_gtk_mate_buffer_get_bundles, 0);
    rb_define_singleton_method(rbc_gtk_mate_buffer, "bundles=", rb_gtk_mate_buffer_set_bundles, 1);
    rb_define_method(rbc_gtk_mate_buffer, "parser", rb_gtk_mate_buffer_get_parser, 0);
    rb_define_method(rbc_gtk_mate_buffer, "parser=", rb_gtk_mate_buffer_set_parser, 1);
    rb_define_singleton_method(rbc_gtk_mate_buffer, "themes", rb_gtk_mate_buffer_get_themes, 0);
    rb_define_singleton_method(rbc_gtk_mate_buffer, "themes=", rb_gtk_mate_buffer_set_themes, 1);
    rb_define_method(rbc_gtk_mate_buffer, "current_scope_range", rb_gtk_mate_buffer_current_scope_range, 0);
    rb_define_method(rbc_gtk_mate_buffer, "cursor_line", rb_gtk_mate_buffer_cursor_line, 0);
    rb_define_method(rbc_gtk_mate_buffer, "cursor_line_offset", rb_gtk_mate_buffer_cursor_line_offset, 0);
    rb_define_method(rbc_gtk_mate_buffer, "cursor_mark", rb_gtk_mate_buffer_cursor_mark, 0);
    rb_define_method(rbc_gtk_mate_buffer, "cursor_offset", rb_gtk_mate_buffer_cursor_offset, 0);
    rb_define_method(rbc_gtk_mate_buffer, "end_mark", rb_gtk_mate_buffer_end_mark, 0);
    rb_define_method(rbc_gtk_mate_buffer, "get_line", rb_gtk_mate_buffer_get_line, 1);
    rb_define_method(rbc_gtk_mate_buffer, "get_line1", rb_gtk_mate_buffer_get_line1, 1);
    rb_define_method(rbc_gtk_mate_buffer, "get_line_length", rb_gtk_mate_buffer_get_line_length, 1);
    rb_define_method(rbc_gtk_mate_buffer, "select_current_scope", rb_gtk_mate_buffer_select_current_scope, 0);
    rb_define_method(rbc_gtk_mate_buffer, "selection_mark", rb_gtk_mate_buffer_selection_mark, 0);
    rb_define_method(rbc_gtk_mate_buffer, "set_grammar_by_filename", rb_gtk_mate_buffer_set_grammar_by_filename, 1);
    rb_define_method(rbc_gtk_mate_buffer, "set_grammar_by_first_line", rb_gtk_mate_buffer_set_grammar_by_first_line, 1);
    rb_define_method(rbc_gtk_mate_buffer, "set_grammar_by_name", rb_gtk_mate_buffer_set_grammar_by_name, 1);
    rb_define_method(rbc_gtk_mate_buffer, "start_mark", rb_gtk_mate_buffer_start_mark, 0);
    rbc_gtk_mate_matcher = G_DEF_CLASS(gtk_mate_matcher_get_type(), "Matcher", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_matcher, "initialize", gtk_mate_matcher_initialize, 0);
    rb_define_method(rbc_gtk_mate_matcher, "neg_rxs", rb_gtk_mate_matcher_get_neg_rxs, 0);
    rb_define_method(rbc_gtk_mate_matcher, "neg_rxs=", rb_gtk_mate_matcher_set_neg_rxs, 1);
    rb_define_method(rbc_gtk_mate_matcher, "pos_rx", rb_gtk_mate_matcher_get_pos_rx, 0);
    rb_define_method(rbc_gtk_mate_matcher, "pos_rx=", rb_gtk_mate_matcher_set_pos_rx, 1);
    rb_define_singleton_method(rbc_gtk_mate_matcher, "compare_match", rb_gtk_mate_matcher_compare_match, 3);
    rb_define_singleton_method(rbc_gtk_mate_matcher, "compile", rb_gtk_mate_matcher_compile, 1);
    rb_define_singleton_method(rbc_gtk_mate_matcher, "get_match", rb_gtk_mate_matcher_get_match, 2);
    rb_define_singleton_method(rbc_gtk_mate_matcher, "test_match", rb_gtk_mate_matcher_test_match, 2);
    rb_define_singleton_method(rbc_gtk_mate_matcher, "test_rank", rb_gtk_mate_matcher_test_rank, 3);
    rbc_gtk_mate_pattern = G_DEF_CLASS(gtk_mate_pattern_get_type(), "Pattern", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_pattern, "initialize", gtk_mate_pattern_initialize, 0);
    rb_define_singleton_method(rbc_gtk_mate_pattern, "all_patterns", rb_gtk_mate_pattern_get_all_patterns, 0);
    rb_define_singleton_method(rbc_gtk_mate_pattern, "all_patterns=", rb_gtk_mate_pattern_set_all_patterns, 1);
    rb_define_method(rbc_gtk_mate_pattern, "comment", rb_gtk_mate_pattern_get_comment, 0);
    rb_define_method(rbc_gtk_mate_pattern, "comment=", rb_gtk_mate_pattern_set_comment, 1);
    rb_define_method(rbc_gtk_mate_pattern, "disabled", rb_gtk_mate_pattern_get_disabled, 0);
    rb_define_method(rbc_gtk_mate_pattern, "disabled=", rb_gtk_mate_pattern_set_disabled, 1);
    rb_define_method(rbc_gtk_mate_pattern, "name", rb_gtk_mate_pattern_get_name, 0);
    rb_define_method(rbc_gtk_mate_pattern, "name=", rb_gtk_mate_pattern_set_name, 1);
    rb_define_singleton_method(rbc_gtk_mate_pattern, "create_from_plist", rb_gtk_mate_pattern_create_from_plist, 2);
    rb_define_singleton_method(rbc_gtk_mate_pattern, "make_captures_from_plist", rb_gtk_mate_pattern_make_captures_from_plist, 1);
    rb_define_singleton_method(rbc_gtk_mate_pattern, "replace_base_and_self_includes", rb_gtk_mate_pattern_replace_base_and_self_includes, 2);
    rb_define_singleton_method(rbc_gtk_mate_pattern, "replace_include_patterns", rb_gtk_mate_pattern_replace_include_patterns, 2);
    rb_define_singleton_method(rbc_gtk_mate_pattern, "replace_repository_includes", rb_gtk_mate_pattern_replace_repository_includes, 2);
    rbc_gtk_mate_scanner = G_DEF_CLASS(gtk_mate_scanner_get_type(), "Scanner", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_scanner, "initialize", gtk_mate_scanner_initialize, 3);
    rb_define_method(rbc_gtk_mate_scanner, "cached_markers", rb_gtk_mate_scanner_get_cached_markers, 0);
    rb_define_method(rbc_gtk_mate_scanner, "cached_markers=", rb_gtk_mate_scanner_set_cached_markers, 1);
    rb_define_method(rbc_gtk_mate_scanner, "position", rb_gtk_mate_scanner_get_position, 0);
    rb_define_method(rbc_gtk_mate_scanner, "position=", rb_gtk_mate_scanner_set_position, 1);
    rb_define_method(rbc_gtk_mate_scanner, "find_next_marker", rb_gtk_mate_scanner_find_next_marker, 0);
    rb_define_method(rbc_gtk_mate_scanner, "get_cached_marker", rb_gtk_mate_scanner_get_cached_marker, 0);
    rb_define_method(rbc_gtk_mate_scanner, "remove_preceding_cached_markers", rb_gtk_mate_scanner_remove_preceding_cached_markers, 1);
    rb_define_method(rbc_gtk_mate_scanner, "scan_for_match", rb_gtk_mate_scanner_scan_for_match, 2);
    rbc_gtk_mate_grammar = G_DEF_CLASS(gtk_mate_grammar_get_type(), "Grammar", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_grammar, "initialize", gtk_mate_grammar_initialize, 1);
    rb_define_method(rbc_gtk_mate_grammar, "all_patterns", rb_gtk_mate_grammar_get_all_patterns, 0);
    rb_define_method(rbc_gtk_mate_grammar, "all_patterns=", rb_gtk_mate_grammar_set_all_patterns, 1);
    rb_define_method(rbc_gtk_mate_grammar, "comment", rb_gtk_mate_grammar_get_comment, 0);
    rb_define_method(rbc_gtk_mate_grammar, "comment=", rb_gtk_mate_grammar_set_comment, 1);
    rb_define_method(rbc_gtk_mate_grammar, "file_types", rb_gtk_mate_grammar_get_file_types, 0);
    rb_define_method(rbc_gtk_mate_grammar, "file_types=", rb_gtk_mate_grammar_set_file_types, 1);
    rb_define_method(rbc_gtk_mate_grammar, "first_line_match", rb_gtk_mate_grammar_get_first_line_match, 0);
    rb_define_method(rbc_gtk_mate_grammar, "first_line_match=", rb_gtk_mate_grammar_set_first_line_match, 1);
    rb_define_method(rbc_gtk_mate_grammar, "folding_start_marker", rb_gtk_mate_grammar_get_folding_start_marker, 0);
    rb_define_method(rbc_gtk_mate_grammar, "folding_start_marker=", rb_gtk_mate_grammar_set_folding_start_marker, 1);
    rb_define_method(rbc_gtk_mate_grammar, "folding_stop_marker", rb_gtk_mate_grammar_get_folding_stop_marker, 0);
    rb_define_method(rbc_gtk_mate_grammar, "folding_stop_marker=", rb_gtk_mate_grammar_set_folding_stop_marker, 1);
    rb_define_method(rbc_gtk_mate_grammar, "key_equivalent", rb_gtk_mate_grammar_get_key_equivalent, 0);
    rb_define_method(rbc_gtk_mate_grammar, "key_equivalent=", rb_gtk_mate_grammar_set_key_equivalent, 1);
    rb_define_method(rbc_gtk_mate_grammar, "loaded", rb_gtk_mate_grammar_get_loaded, 0);
    rb_define_method(rbc_gtk_mate_grammar, "loaded=", rb_gtk_mate_grammar_set_loaded, 1);
    rb_define_method(rbc_gtk_mate_grammar, "patterns", rb_gtk_mate_grammar_get_patterns, 0);
    rb_define_method(rbc_gtk_mate_grammar, "patterns=", rb_gtk_mate_grammar_set_patterns, 1);
    rb_define_method(rbc_gtk_mate_grammar, "repository", rb_gtk_mate_grammar_get_repository, 0);
    rb_define_method(rbc_gtk_mate_grammar, "repository=", rb_gtk_mate_grammar_set_repository, 1);
    rb_define_method(rbc_gtk_mate_grammar, "scope_name", rb_gtk_mate_grammar_get_scope_name, 0);
    rb_define_method(rbc_gtk_mate_grammar, "scope_name=", rb_gtk_mate_grammar_set_scope_name, 1);
    rb_define_singleton_method(rbc_gtk_mate_grammar, "find_by_scope_name", rb_gtk_mate_grammar_find_by_scope_name, 1);
    rb_define_method(rbc_gtk_mate_grammar, "init_for_reference", rb_gtk_mate_grammar_init_for_reference, 0);
    rb_define_method(rbc_gtk_mate_grammar, "init_for_use", rb_gtk_mate_grammar_init_for_use, 0);
    rbc_gtk_mate_text_loc = G_DEF_CLASS(gtk_mate_text_loc_get_type(), "TextLoc", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_text_loc, "initialize", gtk_mate_text_loc_initialize, 0);
    rb_define_method(rbc_gtk_mate_text_loc, "line", rb_gtk_mate_text_loc_get_line, 0);
    rb_define_method(rbc_gtk_mate_text_loc, "line=", rb_gtk_mate_text_loc_set_line, 1);
    rb_define_method(rbc_gtk_mate_text_loc, "line_offset", rb_gtk_mate_text_loc_get_line_offset, 0);
    rb_define_method(rbc_gtk_mate_text_loc, "line_offset=", rb_gtk_mate_text_loc_set_line_offset, 1);
    rb_define_singleton_method(rbc_gtk_mate_text_loc, "equal", rb_gtk_mate_text_loc_equal, 2);
    rb_define_singleton_method(rbc_gtk_mate_text_loc, "gt", rb_gtk_mate_text_loc_gt, 2);
    rb_define_singleton_method(rbc_gtk_mate_text_loc, "gte", rb_gtk_mate_text_loc_gte, 2);
    rb_define_singleton_method(rbc_gtk_mate_text_loc, "lt", rb_gtk_mate_text_loc_lt, 2);
    rb_define_singleton_method(rbc_gtk_mate_text_loc, "lte", rb_gtk_mate_text_loc_lte, 2);
    rb_define_singleton_method(rbc_gtk_mate_text_loc, "make", rb_gtk_mate_text_loc_make, 2);
    rb_define_method(rbc_gtk_mate_text_loc, "to_s", rb_gtk_mate_text_loc_to_s, 0);
    rbc_gtk_mate_colourer = G_DEF_CLASS(gtk_mate_colourer_get_type(), "Colourer", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_colourer, "initialize", gtk_mate_colourer_initialize, 1);
    rb_define_singleton_method(rbc_gtk_mate_colourer, "char_to_hex", rb_gtk_mate_colourer_char_to_hex, 1);
    rb_define_method(rbc_gtk_mate_colourer, "colour_line_with_scopes", rb_gtk_mate_colourer_colour_line_with_scopes, 1);
    rb_define_method(rbc_gtk_mate_colourer, "colour_scope", rb_gtk_mate_colourer_colour_scope, 3);
    rb_define_singleton_method(rbc_gtk_mate_colourer, "merge_colour", rb_gtk_mate_colourer_merge_colour, 2);
    rb_define_method(rbc_gtk_mate_colourer, "set_global_settings", rb_gtk_mate_colourer_set_global_settings, 1);
    rb_define_method(rbc_gtk_mate_colourer, "set_tag_properties", rb_gtk_mate_colourer_set_tag_properties, 3);
    rb_define_method(rbc_gtk_mate_colourer, "uncolour_scope", rb_gtk_mate_colourer_uncolour_scope, 2);
    rb_define_method(rbc_gtk_mate_colourer, "uncolour_scopes", rb_gtk_mate_colourer_uncolour_scopes, 1);
    rbc_gtk_mate_theme_setting = G_DEF_CLASS(gtk_mate_theme_setting_get_type(), "ThemeSetting", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_theme_setting, "initialize", gtk_mate_theme_setting_initialize, 0);
    rb_define_method(rbc_gtk_mate_theme_setting, "matchers", rb_gtk_mate_theme_setting_get_matchers, 0);
    rb_define_method(rbc_gtk_mate_theme_setting, "matchers=", rb_gtk_mate_theme_setting_set_matchers, 1);
    rb_define_method(rbc_gtk_mate_theme_setting, "name", rb_gtk_mate_theme_setting_get_name, 0);
    rb_define_method(rbc_gtk_mate_theme_setting, "name=", rb_gtk_mate_theme_setting_set_name, 1);
    rb_define_method(rbc_gtk_mate_theme_setting, "selector", rb_gtk_mate_theme_setting_get_selector, 0);
    rb_define_method(rbc_gtk_mate_theme_setting, "selector=", rb_gtk_mate_theme_setting_set_selector, 1);
    rb_define_method(rbc_gtk_mate_theme_setting, "settings", rb_gtk_mate_theme_setting_get_settings, 0);
    rb_define_method(rbc_gtk_mate_theme_setting, "settings=", rb_gtk_mate_theme_setting_set_settings, 1);
    rb_define_method(rbc_gtk_mate_theme_setting, "compile_scope_matchers", rb_gtk_mate_theme_setting_compile_scope_matchers, 0);
    rb_define_singleton_method(rbc_gtk_mate_theme_setting, "create_from_plist", rb_gtk_mate_theme_setting_create_from_plist, 1);
    rbc_gtk_mate_single_pattern = G_DEF_CLASS(gtk_mate_single_pattern_get_type(), "SinglePattern", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_single_pattern, "initialize", gtk_mate_single_pattern_initialize, 0);
    rb_define_method(rbc_gtk_mate_single_pattern, "captures", rb_gtk_mate_single_pattern_get_captures, 0);
    rb_define_method(rbc_gtk_mate_single_pattern, "captures=", rb_gtk_mate_single_pattern_set_captures, 1);
    rb_define_method(rbc_gtk_mate_single_pattern, "match", rb_gtk_mate_single_pattern_get_match, 0);
    rb_define_method(rbc_gtk_mate_single_pattern, "match=", rb_gtk_mate_single_pattern_set_match, 1);
    rb_define_singleton_method(rbc_gtk_mate_single_pattern, "create_from_plist", rb_gtk_mate_single_pattern_create_from_plist, 2);
    rbc_gtk_mate_double_pattern = G_DEF_CLASS(gtk_mate_double_pattern_get_type(), "DoublePattern", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_double_pattern, "initialize", gtk_mate_double_pattern_initialize, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "begin", rb_gtk_mate_double_pattern_get_begin, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "begin=", rb_gtk_mate_double_pattern_set_begin, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "begin_captures", rb_gtk_mate_double_pattern_get_begin_captures, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "begin_captures=", rb_gtk_mate_double_pattern_set_begin_captures, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "begin_string", rb_gtk_mate_double_pattern_get_begin_string, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "begin_string=", rb_gtk_mate_double_pattern_set_begin_string, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "both_captures", rb_gtk_mate_double_pattern_get_both_captures, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "both_captures=", rb_gtk_mate_double_pattern_set_both_captures, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "content_name", rb_gtk_mate_double_pattern_get_content_name, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "content_name=", rb_gtk_mate_double_pattern_set_content_name, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "end", rb_gtk_mate_double_pattern_get_end, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "end=", rb_gtk_mate_double_pattern_set_end, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "end_captures", rb_gtk_mate_double_pattern_get_end_captures, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "end_captures=", rb_gtk_mate_double_pattern_set_end_captures, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "end_string", rb_gtk_mate_double_pattern_get_end_string, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "end_string=", rb_gtk_mate_double_pattern_set_end_string, 1);
    rb_define_method(rbc_gtk_mate_double_pattern, "patterns", rb_gtk_mate_double_pattern_get_patterns, 0);
    rb_define_method(rbc_gtk_mate_double_pattern, "patterns=", rb_gtk_mate_double_pattern_set_patterns, 1);
    rb_define_singleton_method(rbc_gtk_mate_double_pattern, "create_from_plist", rb_gtk_mate_double_pattern_create_from_plist, 2);
    rbc_gtk_mate_include_pattern = G_DEF_CLASS(gtk_mate_include_pattern_get_type(), "IncludePattern", rbc_gtk_mate);
    rb_define_method(rbc_gtk_mate_include_pattern, "initialize", gtk_mate_include_pattern_initialize, 0);
    rb_define_singleton_method(rbc_gtk_mate_include_pattern, "create_from_plist", rb_gtk_mate_include_pattern_create_from_plist, 1);
}
