#include "ruby.h"
#include "rbgtk.h"
#include "gtkmateview.h"
#include "onig_wrap.h"
#include "plist.h"
static VALUE rb_vala_error, rbc_gtk;

/****  Gtk wrapper *****/

#define _GTK_SELF(s) GTK(RVAL2GOBJ(s))
static VALUE rbc_gtk;

/****  Gtk.MateView wrapper *****/

#define _GTK_MATE_VIEW_SELF(s) GTK_MATE_VIEW(RVAL2GOBJ(s))
static VALUE rbc_gtk_mate_view;

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


/****  Gtk.MateView methods *****/


static VALUE gtk_mate_view_initialize(VALUE self) {

    RBGTK_INITIALIZE(self, gtk_mate_view_new ());
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


    int _c_return = oniguruma_onig_error->code;
    VALUE _rb_return;
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
    oniguruma_onig_error->code = _c_code;

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
    VALUE _rb_return;
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
    _c_target = STR2CSTR(target);
    int _c_start;
    _c_start = FIX2INT(start);
    int _c_end;
    _c_end = FIX2INT(end);
    
    OnigurumaMatch* _c_return;
    _c_return = oniguruma_regex_search(oniguruma_regex, _c_target, _c_start, _c_end);
    VALUE _rb_return;
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
    _c_pattern = STR2CSTR(pattern);
    
    OnigurumaRegex* _c_return;
    _c_return = oniguruma_regex_make1(_c_pattern);
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
    if (TYPE(filename) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    char * _c_filename;
    _c_filename = STR2CSTR(filename);
    GError* inner_error;
    inner_error = NULL;
    
    PListDict* _c_return;
    _c_return = plist_parse(_c_filename, &inner_error);
    if (inner_error != NULL) {
        if (inner_error->domain == XML_ERROR) {
            rb_raise(rb_vala_error, "[XmlError]: %s", inner_error->message);
        }
    }
    VALUE _rb_return;
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


    char * _c_return = plist_string->str;
    VALUE _rb_return;
    _rb_return = rb_str_new2(_c_return);
    return _rb_return;
}

static VALUE rb_plist_string_set_str(VALUE self, VALUE str) {
    PListString* plist_string = RVAL2GOBJ(self);
    if (TYPE(str) != T_STRING) {
        VALUE rb_arg_error = rb_eval_string("ArgumentError");
        rb_raise(rb_arg_error, "expected a string");
    }
    char * _c_str;
    _c_str = STR2CSTR(str);
    plist_string->str = _c_str;

    return Qnil;
}


/****  PList.Array methods *****/


static VALUE plist_array_initialize(VALUE self) {

    G_INITIALIZE(self, plist_array_new ());
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
    VALUE _rb_return;
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
    _c_key = STR2CSTR(key);
    
    PListNode* _c_return;
    _c_return = plist_dict_get(plist_dict, _c_key);
    VALUE _rb_return;
    _rb_return = GOBJ2RVAL(_c_return);
    return _rb_return;
}

static VALUE rb_plist_dict_keys(VALUE self) {
    PListDict* plist_dict = RVAL2GOBJ(self);


              int _rb_return__length;

    char** _c_return;
    _c_return = plist_dict_keys(plist_dict, &_rb_return__length);
    VALUE _rb_return;
              _rb_return = rb_ary_new2(_rb_return__length);
          long valar__1;
          for(valar__1 = 0; valar__1 < _rb_return__length; valar__1++) {
              rb_ary_store(_rb_return, valar__1, rb_str_new2(_c_return[valar__1]));
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
    rb_define_method(rbc_plist_array, "get", rb_plist_array_get, 1);
    rbc_plist_string = G_DEF_CLASS(plist_string_get_type(), "String", rbc_plist);
    rb_define_method(rbc_plist_string, "initialize", plist_string_initialize, 0);
    rb_define_method(rbc_plist_string, "str", rb_plist_string_get_str, 0);
    rb_define_method(rbc_plist_string, "str=", rb_plist_string_set_str, 1);
    rbc_gtk_mate_view = G_DEF_CLASS(gtk_mate_view_get_type(), "MateView", rbc_gtk);
    rb_define_method(rbc_gtk_mate_view, "initialize", gtk_mate_view_initialize, 0);
    rbc_oniguruma_match = G_DEF_CLASS(oniguruma_match_get_type(), "Match", rbc_oniguruma);
    rb_define_method(rbc_oniguruma_match, "initialize", oniguruma_match_initialize, 0);
    rb_define_method(rbc_oniguruma_match, "begin", rb_oniguruma_match_begin, 1);
    rb_define_method(rbc_oniguruma_match, "end", rb_oniguruma_match_end, 1);
    rbc_oniguruma_regex = G_DEF_CLASS(oniguruma_regex_get_type(), "Regex", rbc_oniguruma);
    rb_define_method(rbc_oniguruma_regex, "initialize", oniguruma_regex_initialize, 0);
    rb_define_method(rbc_oniguruma_regex, "search", rb_oniguruma_regex_search, 3);
    rb_define_singleton_method(rbc_oniguruma_regex, "make1", rb_oniguruma_regex_make1, 1);
    rbc_oniguruma_onig_error = G_DEF_CLASS(oniguruma_onig_error_get_type(), "OnigError", rbc_oniguruma);
    rb_define_method(rbc_oniguruma_onig_error, "initialize", oniguruma_onig_error_initialize, 0);
    rb_define_method(rbc_oniguruma_onig_error, "code", rb_oniguruma_onig_error_get_code, 0);
    rb_define_method(rbc_oniguruma_onig_error, "code=", rb_oniguruma_onig_error_set_code, 1);
}
