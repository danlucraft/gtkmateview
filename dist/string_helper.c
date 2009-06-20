/* Vala string utility functions*/

#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>
#include <gee/collection.h>


#define TYPE_STRING_HELPER (string_helper_get_type ())
#define STRING_HELPER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_STRING_HELPER, StringHelper))
#define STRING_HELPER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_STRING_HELPER, StringHelperClass))
#define IS_STRING_HELPER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_STRING_HELPER))
#define IS_STRING_HELPER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_STRING_HELPER))
#define STRING_HELPER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_STRING_HELPER, StringHelperClass))

typedef struct _StringHelper StringHelper;
typedef struct _StringHelperClass StringHelperClass;
typedef struct _StringHelperPrivate StringHelperPrivate;

/* Started: 30 Aug 08*/
struct _StringHelper {
	GObject parent_instance;
	StringHelperPrivate * priv;
};

struct _StringHelperClass {
	GObjectClass parent_class;
};



GType string_helper_get_type (void);
enum  {
	STRING_HELPER_DUMMY_PROPERTY
};
char* string_helper_gsub (const char* start_string, const char* match_string, const char* replacement_string);
GeeArrayList* string_helper_occurrences (const char* s, const char* t);
StringHelper* string_helper_new (void);
StringHelper* string_helper_construct (GType object_type);
StringHelper* string_helper_new (void);
static gpointer string_helper_parent_class = NULL;



/* Replace all occurences of match_string with replacement_string inside start_string.*/
char* string_helper_gsub (const char* start_string, const char* match_string, const char* replacement_string) {
	GError * _inner_error_;
	GRegex* grx;
	char* _result_;
	char* _tmp5_;
	g_return_val_if_fail (start_string != NULL, NULL);
	g_return_val_if_fail (match_string != NULL, NULL);
	g_return_val_if_fail (replacement_string != NULL, NULL);
	_inner_error_ = NULL;
	grx = NULL;
	_result_ = NULL;
	{
		GRegex* _tmp1_;
		char* _tmp0_;
		char* _tmp2_;
		char* _tmp3_;
		_tmp1_ = NULL;
		_tmp0_ = NULL;
		grx = (_tmp1_ = g_regex_new (_tmp0_ = g_regex_escape_string (match_string, -1), 0, 0, &_inner_error_), (grx == NULL) ? NULL : (grx = (g_regex_unref (grx), NULL)), _tmp1_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_REGEX_ERROR) {
				goto __catch4_g_regex_error;
			}
			goto __finally4;
		}
		_tmp0_ = (g_free (_tmp0_), NULL);
		_tmp2_ = g_regex_replace_literal (grx, start_string, strlen (start_string), 0, replacement_string, 0, &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_REGEX_ERROR) {
				goto __catch4_g_regex_error;
			}
			goto __finally4;
		}
		_tmp3_ = NULL;
		_result_ = (_tmp3_ = _tmp2_, _result_ = (g_free (_result_), NULL), _tmp3_);
	}
	goto __finally4;
	__catch4_g_regex_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			char* _tmp4_;
			_tmp4_ = NULL;
			return (_tmp4_ = g_strdup (""), (e == NULL) ? NULL : (e = (g_error_free (e), NULL)), (grx == NULL) ? NULL : (grx = (g_regex_unref (grx), NULL)), _result_ = (g_free (_result_), NULL), _tmp4_);
		}
	}
	__finally4:
	if (_inner_error_ != NULL) {
		(grx == NULL) ? NULL : (grx = (g_regex_unref (grx), NULL));
		_result_ = (g_free (_result_), NULL);
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	_tmp5_ = NULL;
	return (_tmp5_ = _result_, (grx == NULL) ? NULL : (grx = (g_regex_unref (grx), NULL)), _tmp5_);
}


GeeArrayList* string_helper_occurrences (const char* s, const char* t) {
	GError * _inner_error_;
	GRegex* grx;
	GeeArrayList* poss;
	GMatchInfo* m;
	GeeArrayList* _tmp7_;
	g_return_val_if_fail (s != NULL, NULL);
	g_return_val_if_fail (t != NULL, NULL);
	_inner_error_ = NULL;
	grx = NULL;
	poss = gee_array_list_new (G_TYPE_INT, NULL, NULL, g_direct_equal);
	m = NULL;
	{
		GRegex* _tmp1_;
		char* _tmp0_;
		GMatchInfo* _tmp4_;
		gboolean _tmp3_;
		GMatchInfo* _tmp2_;
		_tmp1_ = NULL;
		_tmp0_ = NULL;
		grx = (_tmp1_ = g_regex_new (_tmp0_ = g_regex_escape_string (t, -1), 0, 0, &_inner_error_), (grx == NULL) ? NULL : (grx = (g_regex_unref (grx), NULL)), _tmp1_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_REGEX_ERROR) {
				goto __catch5_g_regex_error;
			}
			goto __finally5;
		}
		_tmp0_ = (g_free (_tmp0_), NULL);
		_tmp4_ = NULL;
		_tmp2_ = NULL;
		if ((_tmp3_ = g_regex_match (grx, s, 0, &_tmp2_), m = (_tmp4_ = _tmp2_, (m == NULL) ? NULL : (m = (g_match_info_free (m), NULL)), _tmp4_), _tmp3_)) {
			gint spos;
			gint epos;
			spos = 0;
			epos = 0;
			g_match_info_fetch_pos (m, 0, &spos, &epos);
			gee_collection_add ((GeeCollection*) poss, GINT_TO_POINTER (spos));
			while (TRUE) {
				gboolean _tmp5_;
				gint mspos;
				gint mepos;
				_tmp5_ = g_match_info_next (m, &_inner_error_);
				if (_inner_error_ != NULL) {
					if (_inner_error_->domain == G_REGEX_ERROR) {
						goto __catch5_g_regex_error;
					}
					goto __finally5;
				}
				if (!_tmp5_) {
					break;
				}
				mspos = 0;
				mepos = 0;
				g_match_info_fetch_pos (m, 0, &mspos, &mepos);
				gee_collection_add ((GeeCollection*) poss, GINT_TO_POINTER (mspos));
			}
		}
	}
	goto __finally5;
	__catch5_g_regex_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			GeeArrayList* _tmp6_;
			_tmp6_ = NULL;
			return (_tmp6_ = gee_array_list_new (G_TYPE_INT, NULL, NULL, g_direct_equal), (e == NULL) ? NULL : (e = (g_error_free (e), NULL)), (grx == NULL) ? NULL : (grx = (g_regex_unref (grx), NULL)), (poss == NULL) ? NULL : (poss = (g_object_unref (poss), NULL)), (m == NULL) ? NULL : (m = (g_match_info_free (m), NULL)), _tmp6_);
		}
	}
	__finally5:
	if (_inner_error_ != NULL) {
		(grx == NULL) ? NULL : (grx = (g_regex_unref (grx), NULL));
		(poss == NULL) ? NULL : (poss = (g_object_unref (poss), NULL));
		(m == NULL) ? NULL : (m = (g_match_info_free (m), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	_tmp7_ = NULL;
	return (_tmp7_ = poss, (grx == NULL) ? NULL : (grx = (g_regex_unref (grx), NULL)), (m == NULL) ? NULL : (m = (g_match_info_free (m), NULL)), _tmp7_);
}


/* Started: 30 Aug 08*/
StringHelper* string_helper_construct (GType object_type) {
	StringHelper * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


StringHelper* string_helper_new (void) {
	return string_helper_construct (TYPE_STRING_HELPER);
}


static void string_helper_class_init (StringHelperClass * klass) {
	string_helper_parent_class = g_type_class_peek_parent (klass);
}


static void string_helper_instance_init (StringHelper * self) {
}


GType string_helper_get_type (void) {
	static GType string_helper_type_id = 0;
	if (string_helper_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (StringHelperClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) string_helper_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (StringHelper), 0, (GInstanceInitFunc) string_helper_instance_init, NULL };
		string_helper_type_id = g_type_register_static (G_TYPE_OBJECT, "StringHelper", &g_define_type_info, 0);
	}
	return string_helper_type_id;
}




