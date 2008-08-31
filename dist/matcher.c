
#include "matcher.h"
#include <stdio.h>
#include <gee/collection.h>
#include "string_helper.h"




enum  {
	GTK_MATE_MATCHER_DUMMY_PROPERTY
};
static gpointer gtk_mate_matcher_parent_class = NULL;
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);



/* public static int compare_match(Oniguruma.Match m1, Oniguruma.Match m2) {
 }*/
gboolean gtk_mate_matcher_test_match (const char* selector_string, const char* scope_string) {
	char** _tmp0;
	gint scope_ors1_length1;
	char** scope_ors1;
	gboolean _tmp11;
	g_return_val_if_fail (selector_string != NULL, FALSE);
	g_return_val_if_fail (scope_string != NULL, FALSE);
	/* FIXME should validate and throw UTF8 error if bad.*/
	_tmp0 = NULL;
	scope_ors1 = (_tmp0 = g_strsplit (selector_string, ",", 0), scope_ors1_length1 = -1, _tmp0);
	{
		char** selector_string1_collection;
		int selector_string1_collection_length1;
		int selector_string1_it;
		selector_string1_collection = scope_ors1;
		selector_string1_collection_length1 = scope_ors1_length1;
		for (selector_string1_it = 0; (scope_ors1_length1 != -1 && selector_string1_it < scope_ors1_length1) || (scope_ors1_length1 == -1 && selector_string1_collection[selector_string1_it] != NULL); selector_string1_it = selector_string1_it + 1) {
			const char* _tmp10;
			char* selector_string1;
			_tmp10 = NULL;
			selector_string1 = (_tmp10 = selector_string1_collection[selector_string1_it], (_tmp10 == NULL ? NULL : g_strdup (_tmp10)));
			{
				OnigurumaRegex* pos_rx;
				GeeArrayList* neg_rxs;
				char** _tmp1;
				gint positives_and_negatives_length1;
				char** positives_and_negatives;
				pos_rx = NULL;
				neg_rxs = gee_array_list_new (ONIGURUMA_TYPE_REGEX, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
				_tmp1 = NULL;
				positives_and_negatives = (_tmp1 = g_strsplit (selector_string1, "-", 0), positives_and_negatives_length1 = -1, _tmp1);
				{
					char** sub_selector_string_collection;
					int sub_selector_string_collection_length1;
					int sub_selector_string_it;
					sub_selector_string_collection = positives_and_negatives;
					sub_selector_string_collection_length1 = positives_and_negatives_length1;
					for (sub_selector_string_it = 0; (positives_and_negatives_length1 != -1 && sub_selector_string_it < positives_and_negatives_length1) || (positives_and_negatives_length1 == -1 && sub_selector_string_collection[sub_selector_string_it] != NULL); sub_selector_string_it = sub_selector_string_it + 1) {
						const char* _tmp8;
						char* sub_selector_string;
						_tmp8 = NULL;
						sub_selector_string = (_tmp8 = sub_selector_string_collection[sub_selector_string_it], (_tmp8 == NULL ? NULL : g_strdup (_tmp8)));
						{
							if (pos_rx == NULL) {
								char* s1;
								char* s2;
								char* _tmp3;
								char* _tmp2;
								OnigurumaRegex* _tmp6;
								char* _tmp5;
								char* _tmp4;
								s1 = string_helper_gsub (g_strstrip (sub_selector_string), ".", "\\.");
								s2 = string_helper_gsub (s1, " ", ").*(");
								_tmp3 = NULL;
								_tmp2 = NULL;
								fprintf (stdout, "positive '%s' -> '%s'\n", selector_string, (_tmp3 = g_strconcat ((_tmp2 = g_strconcat ("(", s2, NULL)), ")", NULL)));
								_tmp3 = (g_free (_tmp3), NULL);
								_tmp2 = (g_free (_tmp2), NULL);
								_tmp6 = NULL;
								_tmp5 = NULL;
								_tmp4 = NULL;
								pos_rx = (_tmp6 = oniguruma_regex_make1 ((_tmp5 = g_strconcat ((_tmp4 = g_strconcat ("(", s2, NULL)), ")", NULL))), (pos_rx == NULL ? NULL : (pos_rx = (g_object_unref (pos_rx), NULL))), _tmp6);
								_tmp5 = (g_free (_tmp5), NULL);
								_tmp4 = (g_free (_tmp4), NULL);
								s1 = (g_free (s1), NULL);
								s2 = (g_free (s2), NULL);
							} else {
								char* s1;
								char* s2;
								OnigurumaRegex* _tmp7;
								s1 = string_helper_gsub (g_strstrip (sub_selector_string), ".", "\\.");
								s2 = string_helper_gsub (s1, " ", ".*");
								fprintf (stdout, "negative '%s' -> '%s'\n", selector_string, s2);
								_tmp7 = NULL;
								gee_collection_add (GEE_COLLECTION (neg_rxs), (_tmp7 = oniguruma_regex_make1 (s2)));
								(_tmp7 == NULL ? NULL : (_tmp7 = (g_object_unref (_tmp7), NULL)));
								s1 = (g_free (s1), NULL);
								s2 = (g_free (s2), NULL);
							}
							sub_selector_string = (g_free (sub_selector_string), NULL);
						}
					}
				}
				if (gtk_mate_matcher_test_match_re (pos_rx, neg_rxs, scope_string)) {
					gboolean _tmp9;
					return (_tmp9 = TRUE, (selector_string1 = (g_free (selector_string1), NULL)), (pos_rx == NULL ? NULL : (pos_rx = (g_object_unref (pos_rx), NULL))), (neg_rxs == NULL ? NULL : (neg_rxs = (g_object_unref (neg_rxs), NULL))), (positives_and_negatives = (_vala_array_free (positives_and_negatives, positives_and_negatives_length1, ((GDestroyNotify) (g_free))), NULL)), (scope_ors1 = (_vala_array_free (scope_ors1, scope_ors1_length1, ((GDestroyNotify) (g_free))), NULL)), _tmp9);
				}
				selector_string1 = (g_free (selector_string1), NULL);
				(pos_rx == NULL ? NULL : (pos_rx = (g_object_unref (pos_rx), NULL)));
				(neg_rxs == NULL ? NULL : (neg_rxs = (g_object_unref (neg_rxs), NULL)));
				positives_and_negatives = (_vala_array_free (positives_and_negatives, positives_and_negatives_length1, ((GDestroyNotify) (g_free))), NULL);
			}
		}
	}
	return (_tmp11 = FALSE, (scope_ors1 = (_vala_array_free (scope_ors1, scope_ors1_length1, ((GDestroyNotify) (g_free))), NULL)), _tmp11);
}


gboolean gtk_mate_matcher_test_match_re (OnigurumaRegex* positive_selector_regex, GeeArrayList* negative_selector_regex, const char* scope_string) {
	OnigurumaMatch* m;
	g_return_val_if_fail (ONIGURUMA_IS_REGEX (positive_selector_regex), FALSE);
	g_return_val_if_fail (GEE_IS_ARRAY_LIST (negative_selector_regex), FALSE);
	g_return_val_if_fail (scope_string != NULL, FALSE);
	m = oniguruma_regex_search (positive_selector_regex, scope_string, 0, ((gint) (strlen (scope_string))) - 1);
	if (m != NULL) {
		gboolean _tmp1;
		{
			GeeArrayList* neg_rx_collection;
			int neg_rx_it;
			neg_rx_collection = negative_selector_regex;
			for (neg_rx_it = 0; neg_rx_it < gee_collection_get_size (GEE_COLLECTION (neg_rx_collection)); neg_rx_it = neg_rx_it + 1) {
				OnigurumaRegex* neg_rx;
				neg_rx = ((OnigurumaRegex*) (gee_list_get (GEE_LIST (neg_rx_collection), neg_rx_it)));
				{
					OnigurumaMatch* m1;
					m1 = oniguruma_regex_search (neg_rx, scope_string, 0, ((gint) (strlen (scope_string))) - 1);
					if (m1 != NULL) {
						gboolean _tmp0;
						return (_tmp0 = FALSE, (neg_rx == NULL ? NULL : (neg_rx = (g_object_unref (neg_rx), NULL))), (m1 == NULL ? NULL : (m1 = (g_object_unref (m1), NULL))), (m == NULL ? NULL : (m = (g_object_unref (m), NULL))), _tmp0);
					}
					(neg_rx == NULL ? NULL : (neg_rx = (g_object_unref (neg_rx), NULL)));
					(m1 == NULL ? NULL : (m1 = (g_object_unref (m1), NULL)));
				}
			}
		}
		return (_tmp1 = TRUE, (m == NULL ? NULL : (m = (g_object_unref (m), NULL))), _tmp1);
	} else {
		gboolean _tmp2;
		return (_tmp2 = FALSE, (m == NULL ? NULL : (m = (g_object_unref (m), NULL))), _tmp2);
	}
	(m == NULL ? NULL : (m = (g_object_unref (m), NULL)));
}


GtkMateMatcher* gtk_mate_matcher_new (void) {
	GtkMateMatcher * self;
	self = g_object_newv (GTK_MATE_TYPE_MATCHER, 0, NULL);
	return self;
}


static void gtk_mate_matcher_class_init (GtkMateMatcherClass * klass) {
	gtk_mate_matcher_parent_class = g_type_class_peek_parent (klass);
}


static void gtk_mate_matcher_instance_init (GtkMateMatcher * self) {
}


GType gtk_mate_matcher_get_type (void) {
	static GType gtk_mate_matcher_type_id = 0;
	if (gtk_mate_matcher_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateMatcherClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_matcher_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateMatcher), 0, (GInstanceInitFunc) gtk_mate_matcher_instance_init };
		gtk_mate_matcher_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateMatcher", &g_define_type_info, 0);
	}
	return gtk_mate_matcher_type_id;
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if (array != NULL && destroy_func != NULL) {
		int i;
		if (array_length >= 0)
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) (array))[i] != NULL)
			destroy_func (((gpointer*) (array))[i]);
		}
		else
		for (i = 0; ((gpointer*) (array))[i] != NULL; i = i + 1) {
			destroy_func (((gpointer*) (array))[i]);
		}
	}
	g_free (array);
}




