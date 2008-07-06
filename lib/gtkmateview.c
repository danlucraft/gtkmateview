
#include <gtkmateview.h>
#include <stdlib.h>
#include <string.h>
#include <oniguruma.h>
#include <stdio.h>
#include <onig_wrap.h>




enum  {
	GTK_MATE_VIEW_DUMMY_PROPERTY
};
static gpointer gtk_mate_view_parent_class = NULL;



void gtk_mate_view_main (char** args, int args_length1) {
	const char* _tmp0;
	char* pattern;
	const char* _tmp1;
	char* target;
	OnigurumaRegex* rx;
	OnigurumaOnigError* err;
	OnigurumaRegex* _tmp5;
	OnigurumaOnigError* _tmp4;
	OnigurumaRegex* _tmp3;
	OnigurumaOnigError* _tmp2;
	_tmp0 = NULL;
	pattern = (_tmp0 = args[1], (_tmp0 == NULL ? NULL : g_strdup (_tmp0)));
	_tmp1 = NULL;
	target = (_tmp1 = args[2], (_tmp1 == NULL ? NULL : g_strdup (_tmp1)));
	rx = NULL;
	err = NULL;
	_tmp5 = NULL;
	_tmp4 = NULL;
	_tmp3 = NULL;
	_tmp2 = NULL;
	rx = (_tmp5 = (_tmp3 = oniguruma_regex_make (pattern, ONIG_OPTION_NONE, &_tmp2), err = (_tmp4 = _tmp2, (err == NULL ? NULL : (err = (g_object_unref (err), NULL))), _tmp4), _tmp3), (rx == NULL ? NULL : (rx = (g_object_unref (rx), NULL))), _tmp5);
	if (rx == NULL) {
		char* err_buf;
		err_buf = g_strdup ("                                                                                                    ");
		/*char* cerr_buf = err_buf;*/
		onig_error_code_to_str (err_buf, err->code);
		fprintf (stdout, "caught onigerror: %d, '%s'\n", err->code, err_buf);
		err_buf = (g_free (err_buf), NULL);
	} else {
		oniguruma_regex_search (rx, target, 0, 11);
	}
	pattern = (g_free (pattern), NULL);
	target = (g_free (target), NULL);
	(rx == NULL ? NULL : (rx = (g_object_unref (rx), NULL)));
	(err == NULL ? NULL : (err = (g_object_unref (err), NULL)));
}


int main (int argc, char ** argv) {
	g_type_init ();
	gtk_mate_view_main (argv, argc);
	return 0;
}


GtkMateView* gtk_mate_view_new (void) {
	GtkMateView * self;
	self = g_object_newv (TYPE_GTK_MATE_VIEW, 0, NULL);
	return self;
}


static void gtk_mate_view_class_init (GtkMateViewClass * klass) {
	gtk_mate_view_parent_class = g_type_class_peek_parent (klass);
}


static void gtk_mate_view_instance_init (GtkMateView * self) {
}


GType gtk_mate_view_get_type (void) {
	static GType gtk_mate_view_type_id = 0;
	if (G_UNLIKELY (gtk_mate_view_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateViewClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_view_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateView), 0, (GInstanceInitFunc) gtk_mate_view_instance_init };
		gtk_mate_view_type_id = g_type_register_static (G_TYPE_OBJECT, "GtkMateView", &g_define_type_info, 0);
	}
	return gtk_mate_view_type_id;
}




