/* Vala string utility functions*/

#include "string_helper.h"




enum  {
	STRING_HELPER_DUMMY_PROPERTY
};
static gpointer string_helper_parent_class = NULL;



/* Replace all occurences of match_string with replacement_string inside start_string.*/
char* string_helper_gsub (const char* start_string, const char* match_string, const char* replacement_string) {
	GError * inner_error;
	GRegex* grx;
	char* result;
	char* _tmp4;
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
		_tmp1 = NULL;
		_tmp0 = NULL;
		grx = (_tmp1 = g_regex_new ((_tmp0 = g_regex_escape_string (match_string, -1)), 0, 0, &inner_error), (grx == NULL ? NULL : (grx = (g_regex_unref (grx), NULL))), _tmp1);
		if (inner_error != NULL) {
			if (inner_error->domain == G_REGEX_ERROR) {
				goto __catch5_g_regex_error;
			}
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
			g_clear_error (&inner_error);
		}
		_tmp0 = (g_free (_tmp0), NULL);
		_tmp2 = NULL;
		result = (_tmp2 = g_regex_replace_literal (grx, start_string, strlen (start_string), 0, replacement_string, 0, &inner_error), (result = (g_free (result), NULL)), _tmp2);
		if (inner_error != NULL) {
			if (inner_error->domain == G_REGEX_ERROR) {
				goto __catch5_g_regex_error;
			}
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, inner_error->message);
			g_clear_error (&inner_error);
		}
	}
	goto __finally5;
	__catch5_g_regex_error:
	{
		GError * e;
		e = inner_error;
		inner_error = NULL;
		{
			char* _tmp3;
			_tmp3 = NULL;
			return (_tmp3 = g_strdup (""), (e == NULL ? NULL : (e = (g_error_free (e), NULL))), (grx == NULL ? NULL : (grx = (g_regex_unref (grx), NULL))), (result = (g_free (result), NULL)), _tmp3);
		}
	}
	__finally5:
	;
	_tmp4 = NULL;
	return (_tmp4 = result, (grx == NULL ? NULL : (grx = (g_regex_unref (grx), NULL))), _tmp4);
}


/* Started: 30 Aug 08*/
StringHelper* string_helper_new (void) {
	StringHelper* self;
	self = ((StringHelper*) (g_type_create_instance (TYPE_STRING_HELPER)));
	return self;
}


static void string_helper_class_init (StringHelperClass * klass) {
	string_helper_parent_class = g_type_class_peek_parent (klass);
}


static void string_helper_instance_init (StringHelper * self) {
	self->ref_count = 1;
}


GType string_helper_get_type (void) {
	static GType string_helper_type_id = 0;
	if (string_helper_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (StringHelperClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) string_helper_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (StringHelper), 0, (GInstanceInitFunc) string_helper_instance_init };
		static const GTypeFundamentalInfo g_define_type_fundamental_info = { (G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE | G_TYPE_FLAG_DERIVABLE | G_TYPE_FLAG_DEEP_DERIVABLE) };
		string_helper_type_id = g_type_register_fundamental (g_type_fundamental_next (), "StringHelper", &g_define_type_info, &g_define_type_fundamental_info, 0);
	}
	return string_helper_type_id;
}


gpointer string_helper_ref (gpointer instance) {
	StringHelper* self;
	self = instance;
	g_atomic_int_inc (&self->ref_count);
	return instance;
}


void string_helper_unref (gpointer instance) {
	StringHelper* self;
	self = instance;
	if (g_atomic_int_dec_and_test (&self->ref_count)) {
		g_type_free_instance (((GTypeInstance *) (self)));
	}
}




