/* Vala string utility functions*/

#include "string_helper.h"
#include <gee/collection.h>




enum  {
	STRING_HELPER_DUMMY_PROPERTY
};
static gpointer string_helper_parent_class = NULL;



/* Replace all occurences of match_string with replacement_string inside start_string.*/
char* string_helper_gsub (const char* start_string, const char* match_string, const char* replacement_string) {
	GError * inner_error;
	GRegex* grx;
	char* result;
	char* _tmp5;
	g_return_val_if_fail (start_string != NULL, NULL);
	g_return_val_if_fail (match_string != NULL, NULL);
	g_return_val_if_fail (replacement_string != NULL, NULL);
	inner_error = NULL;
	grx = NULL;
	result = NULL;
	{
		GRegex* _tmp1;
		char* _tmp0;
		char* _tmp2;
		char* _tmp3;
		_tmp1 = NULL;
		_tmp0 = NULL;
		grx = (_tmp1 = g_regex_new (_tmp0 = g_regex_escape_string (match_string, -1), 0, 0, &inner_error), (grx == NULL) ? NULL : (grx = (g_regex_unref (grx), NULL)), _tmp1);
		if (inner_error != NULL) {
			if (inner_error->domain == G_REGEX_ERROR) {
				goto __catch5_g_regex_error;
			}
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
			g_clear_error (&inner_error);
		}
		_tmp0 = (g_free (_tmp0), NULL);
		_tmp2 = g_regex_replace_literal (grx, start_string, strlen (start_string), 0, replacement_string, 0, &inner_error);
		if (inner_error != NULL) {
			if (inner_error->domain == G_REGEX_ERROR) {
				goto __catch5_g_regex_error;
			}
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
			g_clear_error (&inner_error);
		}
		_tmp3 = NULL;
		result = (_tmp3 = _tmp2, result = (g_free (result), NULL), _tmp3);
	}
	goto __finally5;
	__catch5_g_regex_error:
	{
		GError * e;
		e = inner_error;
		inner_error = NULL;
		{
			char* _tmp4;
			_tmp4 = NULL;
			return (_tmp4 = g_strdup (""), (e == NULL) ? NULL : (e = (g_error_free (e), NULL)), (grx == NULL) ? NULL : (grx = (g_regex_unref (grx), NULL)), result = (g_free (result), NULL), _tmp4);
		}
	}
	__finally5:
	;
	_tmp5 = NULL;
	return (_tmp5 = result, (grx == NULL) ? NULL : (grx = (g_regex_unref (grx), NULL)), _tmp5);
}


GeeArrayList* string_helper_occurrences (const char* s, const char* t) {
	GError * inner_error;
	GRegex* grx;
	GeeArrayList* poss;
	GMatchInfo* m;
	GeeArrayList* _tmp7;
	g_return_val_if_fail (s != NULL, NULL);
	g_return_val_if_fail (t != NULL, NULL);
	inner_error = NULL;
	grx = NULL;
	poss = gee_array_list_new (G_TYPE_INT, NULL, NULL, g_direct_equal);
	m = NULL;
	{
		GRegex* _tmp1;
		char* _tmp0;
		GMatchInfo* _tmp4;
		gboolean _tmp3;
		GMatchInfo* _tmp2;
		_tmp1 = NULL;
		_tmp0 = NULL;
		grx = (_tmp1 = g_regex_new (_tmp0 = g_regex_escape_string (t, -1), 0, 0, &inner_error), (grx == NULL) ? NULL : (grx = (g_regex_unref (grx), NULL)), _tmp1);
		if (inner_error != NULL) {
			if (inner_error->domain == G_REGEX_ERROR) {
				goto __catch6_g_regex_error;
			}
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
			g_clear_error (&inner_error);
		}
		_tmp0 = (g_free (_tmp0), NULL);
		_tmp4 = NULL;
		_tmp2 = NULL;
		if ((_tmp3 = g_regex_match (grx, s, 0, &_tmp2), m = (_tmp4 = _tmp2, (m == NULL) ? NULL : (m = (g_match_info_free (m), NULL)), _tmp4), _tmp3)) {
			gint spos;
			gint epos;
			spos = 0;
			epos = 0;
			g_match_info_fetch_pos (m, 0, &spos, &epos);
			gee_collection_add ((GeeCollection*) poss, GINT_TO_POINTER (spos));
			while (TRUE) {
				gboolean _tmp5;
				gint spos;
				gint epos;
				_tmp5 = g_match_info_next (m, &inner_error);
				if (inner_error != NULL) {
					if (inner_error->domain == G_REGEX_ERROR) {
						goto __catch6_g_regex_error;
					}
					g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
					g_clear_error (&inner_error);
				}
				if (!_tmp5) {
					break;
				}
				spos = 0;
				epos = 0;
				g_match_info_fetch_pos (m, 0, &spos, &epos);
				gee_collection_add ((GeeCollection*) poss, GINT_TO_POINTER (spos));
			}
		}
	}
	goto __finally6;
	__catch6_g_regex_error:
	{
		GError * e;
		e = inner_error;
		inner_error = NULL;
		{
			GeeArrayList* _tmp6;
			_tmp6 = NULL;
			return (_tmp6 = gee_array_list_new (G_TYPE_INT, NULL, NULL, g_direct_equal), (e == NULL) ? NULL : (e = (g_error_free (e), NULL)), (grx == NULL) ? NULL : (grx = (g_regex_unref (grx), NULL)), (poss == NULL) ? NULL : (poss = (g_object_unref (poss), NULL)), (m == NULL) ? NULL : (m = (g_match_info_free (m), NULL)), _tmp6);
		}
	}
	__finally6:
	;
	_tmp7 = NULL;
	return (_tmp7 = poss, (grx == NULL) ? NULL : (grx = (g_regex_unref (grx), NULL)), (m == NULL) ? NULL : (m = (g_match_info_free (m), NULL)), _tmp7);
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




