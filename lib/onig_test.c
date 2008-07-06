
#include "onig_test.h"
#include <oniguruma.h>
#include <stdio.h>




enum  {
	ONIG_TEST_DUMMY_PROPERTY
};
static gpointer onig_test_parent_class = NULL;



void onig_test_main (char** args, int args_length1) {
	const char* _tmp0;
	char* pattern;
	const char* _tmp1;
	char* target;
	_tmp0 = NULL;
	pattern = (_tmp0 = args[1], (_tmp0 == NULL ? NULL : g_strdup (_tmp0)));
	/*"(a)s(df)";*/
	_tmp1 = NULL;
	target = (_tmp1 = args[2], (_tmp1 == NULL ? NULL : g_strdup (_tmp1)));
	/*"fooasdfgoo";*/
	onig_test_search (pattern, target);
	pattern = (g_free (pattern), NULL);
	target = (g_free (target), NULL);
}


int main (int argc, char ** argv) {
	g_type_init ();
	onig_test_main (argv, argc);
	return 0;
}


void onig_test_search (const char* str_pattern, const char* str_target) {
	gchar* pattern;
	gchar* target;
	regex_t* rx;
	OnigErrorInfo err_info = {0};
	regex_t* _tmp2;
	gint _tmp1;
	regex_t* _tmp0;
	gint r;
	OnigRegion* rg;
	g_return_if_fail (str_pattern != NULL);
	g_return_if_fail (str_target != NULL);
	pattern = str_pattern;
	target = str_target;
	rx = NULL;
	fprintf (stdout, "pattern: %s\n", ((const char*) (pattern)));
	fprintf (stdout, "target: %s\n", ((const char*) (target)));
	_tmp2 = NULL;
	_tmp0 = NULL;
	r = (_tmp1 = onig_new (&_tmp0, pattern, (pattern + strlen (str_pattern)), ONIG_OPTION_IGNORECASE, ((gint) (ONIG_ENCODING_ASCII)), ONIG_SYNTAX_DEFAULT, &err_info), rx = (_tmp2 = _tmp0, (rx == NULL ? NULL : (rx = ( (rx), NULL))), _tmp2), _tmp1);
	if (r < 0) {
		fprintf (stdout, "error code: %d\n", r);
		(rx == NULL ? NULL : (rx = ( (rx), NULL)));
		return;
	}
	fprintf (stdout, "code: %d\n", r);
	fprintf (stdout, "allocated re. num_captures: %d\n", onig_number_of_captures (rx));
	rg = onig_region_new ();
	fprintf (stdout, "allocated region\n");
	onig_search (rx, target, (target + strlen (str_target)), target, (target + strlen (str_target)), rg, ONIG_OPTION_NONE);
	fprintf (stdout, "count: %d\n", rg->num_regs);
	{
		gint i;
		i = 0;
		for (; i < rg->num_regs; i++) {
			fprintf (stdout, "  %d begins at %d\n", i, rg->beg[i]);
		}
	}
	(rx == NULL ? NULL : (rx = ( (rx), NULL)));
	(rg == NULL ? NULL : (rg = ( (rg), NULL)));
}


gint onig_test_strlen (gchar* str) {
	gint i;
	gchar c;
	i = 0;
	c = '\0';
	while ((c = str[i]) != '\0') {
		i = i + (1);
	}
	return i;
}


/* oniguruma test
 valac -o onig_test onig_test.vala --save-temps --vapidir=./../vapi/ --pkg=oniguruma --Xcc="-lonig"*/
OnigTest* onig_test_new (void) {
	OnigTest * self;
	self = g_object_newv (TYPE_ONIG_TEST, 0, NULL);
	return self;
}


static void onig_test_class_init (OnigTestClass * klass) {
	onig_test_parent_class = g_type_class_peek_parent (klass);
}


static void onig_test_instance_init (OnigTest * self) {
}


GType onig_test_get_type (void) {
	static GType onig_test_type_id = 0;
	if (G_UNLIKELY (onig_test_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (OnigTestClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) onig_test_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (OnigTest), 0, (GInstanceInitFunc) onig_test_instance_init };
		onig_test_type_id = g_type_register_static (G_TYPE_OBJECT, "OnigTest", &g_define_type_info, 0);
	}
	return onig_test_type_id;
}




