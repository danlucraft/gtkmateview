
#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <gee/arraylist.h>
#include <stdlib.h>
#include <string.h>
#include <gee/collection.h>
#include <gee/list.h>
#include <gee/iterable.h>
#include <gee/iterator.h>


#define GTK_MATE_TYPE_MATCHER (gtk_mate_matcher_get_type ())
#define GTK_MATE_MATCHER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_MATCHER, GtkMateMatcher))
#define GTK_MATE_MATCHER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_MATCHER, GtkMateMatcherClass))
#define GTK_MATE_IS_MATCHER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_MATCHER))
#define GTK_MATE_IS_MATCHER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_MATCHER))
#define GTK_MATE_MATCHER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_MATCHER, GtkMateMatcherClass))

typedef struct _GtkMateMatcher GtkMateMatcher;
typedef struct _GtkMateMatcherClass GtkMateMatcherClass;
typedef struct _GtkMateMatcherPrivate GtkMateMatcherPrivate;

#define ONIG_TYPE_RX (onig_rx_get_type ())
#define ONIG_RX(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIG_TYPE_RX, OnigRx))
#define ONIG_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIG_TYPE_RX, OnigRxClass))
#define ONIG_IS_RX(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIG_TYPE_RX))
#define ONIG_IS_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIG_TYPE_RX))
#define ONIG_RX_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIG_TYPE_RX, OnigRxClass))

typedef struct _OnigRx OnigRx;
typedef struct _OnigRxClass OnigRxClass;

#define ONIG_TYPE_MATCH (onig_match_get_type ())
#define ONIG_MATCH(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIG_TYPE_MATCH, OnigMatch))
#define ONIG_MATCH_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIG_TYPE_MATCH, OnigMatchClass))
#define ONIG_IS_MATCH(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIG_TYPE_MATCH))
#define ONIG_IS_MATCH_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIG_TYPE_MATCH))
#define ONIG_MATCH_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIG_TYPE_MATCH, OnigMatchClass))

typedef struct _OnigMatch OnigMatch;
typedef struct _OnigMatchClass OnigMatchClass;

struct _GtkMateMatcher {
	GtkObject parent_instance;
	GtkMateMatcherPrivate * priv;
	OnigRx* pos_rx;
	GeeArrayList* neg_rxs;
};

struct _GtkMateMatcherClass {
	GtkObjectClass parent_class;
};



GType gtk_mate_matcher_get_type (void);
GType onig_rx_get_type (void);
enum  {
	GTK_MATE_MATCHER_DUMMY_PROPERTY
};
GeeArrayList* string_helper_occurrences (const char* s, const char* t);
GType onig_match_get_type (void);
gint onig_match_num_captures (OnigMatch* self);
gint onig_match_begin (OnigMatch* self, gint capture);
static gint gtk_mate_matcher_sorted_ix (GeeArrayList* ixs, gint val);
gint onig_match_end (OnigMatch* self, gint capture);
gint gtk_mate_matcher_compare_match (const char* scope_string, OnigMatch* m1, OnigMatch* m2);
gboolean gtk_mate_matcher_match (const char* selector_string, const char* scope_string, OnigMatch** match);
char* gtk_mate_matcher_test_rank (const char* selector_a, const char* selector_b, const char* scope_string);
OnigMatch* gtk_mate_matcher_get_match (const char* selector_string, const char* scope_string);
gboolean gtk_mate_matcher_test_match (const char* selector_string, const char* scope_string);
GeeArrayList* gtk_mate_matcher_compile (const char* selector_string);
gboolean gtk_mate_matcher_test_match_re (OnigRx* positive_selector_regex, GeeArrayList* negative_selector_regex, const char* scope_string, OnigMatch** match);
GtkMateMatcher* gtk_mate_matcher_new (void);
GtkMateMatcher* gtk_mate_matcher_construct (GType object_type);
char* string_helper_gsub (const char* start_string, const char* match_string, const char* replacement_string);
OnigRx* onig_rx_make1 (const char* pattern);
OnigMatch* onig_rx_search (OnigRx* self, const char* target, gint start, gint end);
GtkMateMatcher* gtk_mate_matcher_new (void);
static gpointer gtk_mate_matcher_parent_class = NULL;
static void gtk_mate_matcher_finalize (GObject* obj);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static gint _vala_array_length (gpointer array);



/* returns 1 if m1 is better than m2, -1 if m1 is worse than m2, 0 if equally good*/
gint gtk_mate_matcher_compare_match (const char* scope_string, OnigMatch* m1, OnigMatch* m2) {
	GeeArrayList* space_ixs;
	gint max_cap1;
	gint max_cap2;
	gint cap1_ix;
	gint cap1_el_ix;
	gint len1;
	gint cap2_ix;
	gint cap2_el_ix;
	gint len2;
	gint _tmp4_;
	g_return_val_if_fail (scope_string != NULL, 0);
	g_return_val_if_fail (m1 != NULL, 0);
	g_return_val_if_fail (m2 != NULL, 0);
	space_ixs = string_helper_occurrences (scope_string, " ");
	max_cap1 = onig_match_num_captures (m1);
	max_cap2 = onig_match_num_captures (m2);
	cap1_ix = 0;
	cap1_el_ix = 0;
	len1 = 0;
	cap2_ix = 0;
	cap2_el_ix = 0;
	len2 = 0;
	{
		gint i;
		i = 0;
		for (; i < MIN (max_cap1, max_cap2); i++) {
			/* first try element depth:*/
			cap1_ix = onig_match_begin (m1, (max_cap1 - 1) - i);
			cap2_ix = onig_match_begin (m2, (max_cap2 - 1) - i);
			cap1_el_ix = gtk_mate_matcher_sorted_ix (space_ixs, cap1_ix);
			cap2_el_ix = gtk_mate_matcher_sorted_ix (space_ixs, cap2_ix);
			if (cap1_el_ix > cap2_el_ix) {
				gint _tmp0_;
				return (_tmp0_ = 1, (space_ixs == NULL) ? NULL : (space_ixs = (g_object_unref (space_ixs), NULL)), _tmp0_);
			} else {
				if (cap1_el_ix < cap2_el_ix) {
					gint _tmp1_;
					return (_tmp1_ = -1, (space_ixs == NULL) ? NULL : (space_ixs = (g_object_unref (space_ixs), NULL)), _tmp1_);
				}
			}
			/* next try length of match*/
			len1 = onig_match_end (m1, (max_cap1 - 1) - i) - cap1_ix;
			len2 = onig_match_end (m2, (max_cap2 - 1) - i) - cap2_ix;
			if (len1 > len2) {
				gint _tmp2_;
				return (_tmp2_ = 1, (space_ixs == NULL) ? NULL : (space_ixs = (g_object_unref (space_ixs), NULL)), _tmp2_);
			} else {
				if (len1 < len2) {
					gint _tmp3_;
					return (_tmp3_ = -1, (space_ixs == NULL) ? NULL : (space_ixs = (g_object_unref (space_ixs), NULL)), _tmp3_);
				}
			}
		}
	}
	return (_tmp4_ = 0, (space_ixs == NULL) ? NULL : (space_ixs = (g_object_unref (space_ixs), NULL)), _tmp4_);
}


static gint gtk_mate_matcher_sorted_ix (GeeArrayList* ixs, gint val) {
	g_return_val_if_fail (ixs != NULL, 0);
	if (gee_collection_get_size ((GeeCollection*) ixs) == 0) {
		return 0;
	}
	if (val < GPOINTER_TO_INT (gee_list_get ((GeeList*) ixs, 0))) {
		return 0;
	}
	if (gee_collection_get_size ((GeeCollection*) ixs) == 1) {
		if (val > GPOINTER_TO_INT (gee_list_get ((GeeList*) ixs, 0))) {
			return 1;
		} else {
			return 0;
		}
	} else {
		{
			gint i;
			i = 0;
			for (; i < (gee_collection_get_size ((GeeCollection*) ixs) - 1); i++) {
				gboolean _tmp4_;
				_tmp4_ = FALSE;
				if (val > GPOINTER_TO_INT (gee_list_get ((GeeList*) ixs, i))) {
					_tmp4_ = val < GPOINTER_TO_INT (gee_list_get ((GeeList*) ixs, i + 1));
				} else {
					_tmp4_ = FALSE;
				}
				if (_tmp4_) {
					return i + 1;
				}
			}
		}
		return gee_collection_get_size ((GeeCollection*) ixs);
	}
}


/* this method is mainly for testing in the Ruby specs*/
char* gtk_mate_matcher_test_rank (const char* selector_a, const char* selector_b, const char* scope_string) {
	OnigMatch* m1;
	OnigMatch* m2;
	OnigMatch* _tmp2_;
	gboolean _tmp1_;
	OnigMatch* _tmp0_;
	OnigMatch* _tmp5_;
	gboolean _tmp4_;
	OnigMatch* _tmp3_;
	gint r;
	g_return_val_if_fail (selector_a != NULL, NULL);
	g_return_val_if_fail (selector_b != NULL, NULL);
	g_return_val_if_fail (scope_string != NULL, NULL);
	m1 = NULL;
	m2 = NULL;
	_tmp2_ = NULL;
	_tmp0_ = NULL;
	_tmp1_ = gtk_mate_matcher_match (selector_a, scope_string, &_tmp0_);
	m1 = (_tmp2_ = _tmp0_, (m1 == NULL) ? NULL : (m1 = (g_object_unref (m1), NULL)), _tmp2_);
	_tmp1_;
	_tmp5_ = NULL;
	_tmp3_ = NULL;
	_tmp4_ = gtk_mate_matcher_match (selector_b, scope_string, &_tmp3_);
	m2 = (_tmp5_ = _tmp3_, (m2 == NULL) ? NULL : (m2 = (g_object_unref (m2), NULL)), _tmp5_);
	_tmp4_;
	r = gtk_mate_matcher_compare_match (scope_string, m1, m2);
	if (r > 0) {
		const char* _tmp6_;
		char* _tmp7_;
		_tmp6_ = NULL;
		_tmp7_ = NULL;
		return (_tmp7_ = (_tmp6_ = selector_a, (_tmp6_ == NULL) ? NULL : g_strdup (_tmp6_)), (m1 == NULL) ? NULL : (m1 = (g_object_unref (m1), NULL)), (m2 == NULL) ? NULL : (m2 = (g_object_unref (m2), NULL)), _tmp7_);
	} else {
		if (r == 0) {
			char* _tmp8_;
			char* _tmp9_;
			char* _tmp10_;
			_tmp8_ = NULL;
			_tmp9_ = NULL;
			_tmp10_ = NULL;
			return (_tmp10_ = (_tmp9_ = g_strconcat (_tmp8_ = g_strconcat (selector_a, " == ", NULL), selector_b, NULL), _tmp8_ = (g_free (_tmp8_), NULL), _tmp9_), (m1 == NULL) ? NULL : (m1 = (g_object_unref (m1), NULL)), (m2 == NULL) ? NULL : (m2 = (g_object_unref (m2), NULL)), _tmp10_);
		} else {
			const char* _tmp11_;
			char* _tmp12_;
			_tmp11_ = NULL;
			_tmp12_ = NULL;
			return (_tmp12_ = (_tmp11_ = selector_b, (_tmp11_ == NULL) ? NULL : g_strdup (_tmp11_)), (m1 == NULL) ? NULL : (m1 = (g_object_unref (m1), NULL)), (m2 == NULL) ? NULL : (m2 = (g_object_unref (m2), NULL)), _tmp12_);
		}
	}
	(m1 == NULL) ? NULL : (m1 = (g_object_unref (m1), NULL));
	(m2 == NULL) ? NULL : (m2 = (g_object_unref (m2), NULL));
}


/* this method is mainly for testing in the Ruby specs*/
gboolean gtk_mate_matcher_test_match (const char* selector_string, const char* scope_string) {
	OnigMatch* m;
	gboolean _tmp0_;
	g_return_val_if_fail (selector_string != NULL, FALSE);
	g_return_val_if_fail (scope_string != NULL, FALSE);
	m = gtk_mate_matcher_get_match (selector_string, scope_string);
	return (_tmp0_ = m != NULL, (m == NULL) ? NULL : (m = (g_object_unref (m), NULL)), _tmp0_);
}


OnigMatch* gtk_mate_matcher_get_match (const char* selector_string, const char* scope_string) {
	OnigMatch* m;
	OnigMatch* _tmp2_;
	gboolean _tmp1_;
	OnigMatch* _tmp0_;
	g_return_val_if_fail (selector_string != NULL, NULL);
	g_return_val_if_fail (scope_string != NULL, NULL);
	m = NULL;
	_tmp2_ = NULL;
	_tmp0_ = NULL;
	_tmp1_ = gtk_mate_matcher_match (selector_string, scope_string, &_tmp0_);
	m = (_tmp2_ = _tmp0_, (m == NULL) ? NULL : (m = (g_object_unref (m), NULL)), _tmp2_);
	_tmp1_;
	/* stdout.printf("test_match('%s', '%s') == %d\n", selector_string, scope_string, result ? 1 : 0);*/
	return m;
}


gboolean gtk_mate_matcher_match (const char* selector_string, const char* scope_string, OnigMatch** match) {
	GeeArrayList* matchers;
	gboolean _tmp4_;
	g_return_val_if_fail (selector_string != NULL, FALSE);
	g_return_val_if_fail (scope_string != NULL, FALSE);
	*match = NULL;
	matchers = gtk_mate_matcher_compile (selector_string);
	{
		GeeIterator* _matcher_it;
		_matcher_it = gee_iterable_iterator ((GeeIterable*) matchers);
		while (gee_iterator_next (_matcher_it)) {
			GtkMateMatcher* matcher;
			OnigMatch* _tmp2_;
			gboolean _tmp1_;
			OnigMatch* _tmp0_;
			matcher = (GtkMateMatcher*) gee_iterator_get (_matcher_it);
			_tmp2_ = NULL;
			_tmp0_ = NULL;
			if ((_tmp1_ = gtk_mate_matcher_test_match_re (matcher->pos_rx, matcher->neg_rxs, scope_string, &_tmp0_), (*match) = (_tmp2_ = _tmp0_, ((*match) == NULL) ? NULL : ((*match) = (g_object_unref ((*match)), NULL)), _tmp2_), _tmp1_)) {
				gboolean _tmp3_;
				return (_tmp3_ = TRUE, (matcher == NULL) ? NULL : (matcher = (g_object_unref (matcher), NULL)), (_matcher_it == NULL) ? NULL : (_matcher_it = (g_object_unref (_matcher_it), NULL)), (matchers == NULL) ? NULL : (matchers = (g_object_unref (matchers), NULL)), _tmp3_);
			}
			(matcher == NULL) ? NULL : (matcher = (g_object_unref (matcher), NULL));
		}
		(_matcher_it == NULL) ? NULL : (_matcher_it = (g_object_unref (_matcher_it), NULL));
	}
	return (_tmp4_ = FALSE, (matchers == NULL) ? NULL : (matchers = (g_object_unref (matchers), NULL)), _tmp4_);
}


GeeArrayList* gtk_mate_matcher_compile (const char* selector_string) {
	GeeArrayList* ms;
	char** _tmp1_;
	gint scope_ors1_size;
	gint scope_ors1_length1;
	char** _tmp0_;
	char** scope_ors1;
	GeeArrayList* _tmp11_;
	g_return_val_if_fail (selector_string != NULL, NULL);
	ms = gee_array_list_new (GTK_MATE_TYPE_MATCHER, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	/* FIXME should validate and throw UTF8 error if bad.*/
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	scope_ors1 = (_tmp1_ = _tmp0_ = g_strsplit (selector_string, ",", 0), scope_ors1_length1 = _vala_array_length (_tmp0_), scope_ors1_size = scope_ors1_length1, _tmp1_);
	/*stdout.printf("match: selector: '%s', scope: '%s'\n", selector_string, scope_string);*/
	{
		char** selector_string1_collection;
		int selector_string1_collection_length1;
		int selector_string1_it;
		selector_string1_collection = scope_ors1;
		selector_string1_collection_length1 = scope_ors1_length1;
		for (selector_string1_it = 0; selector_string1_it < scope_ors1_length1; selector_string1_it = selector_string1_it + 1) {
			const char* _tmp10_;
			char* selector_string1;
			_tmp10_ = NULL;
			selector_string1 = (_tmp10_ = selector_string1_collection[selector_string1_it], (_tmp10_ == NULL) ? NULL : g_strdup (_tmp10_));
			{
				GtkMateMatcher* m;
				GeeArrayList* _tmp2_;
				char** _tmp4_;
				gint positives_and_negatives_size;
				gint positives_and_negatives_length1;
				char** _tmp3_;
				char** positives_and_negatives;
				m = g_object_ref_sink (gtk_mate_matcher_new ());
				_tmp2_ = NULL;
				m->neg_rxs = (_tmp2_ = gee_array_list_new (ONIG_TYPE_RX, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (m->neg_rxs == NULL) ? NULL : (m->neg_rxs = (g_object_unref (m->neg_rxs), NULL)), _tmp2_);
				_tmp4_ = NULL;
				_tmp3_ = NULL;
				positives_and_negatives = (_tmp4_ = _tmp3_ = g_strsplit (selector_string1, " -", 0), positives_and_negatives_length1 = _vala_array_length (_tmp3_), positives_and_negatives_size = positives_and_negatives_length1, _tmp4_);
				{
					char** sub_selector_string_collection;
					int sub_selector_string_collection_length1;
					int sub_selector_string_it;
					sub_selector_string_collection = positives_and_negatives;
					sub_selector_string_collection_length1 = positives_and_negatives_length1;
					for (sub_selector_string_it = 0; sub_selector_string_it < positives_and_negatives_length1; sub_selector_string_it = sub_selector_string_it + 1) {
						const char* _tmp9_;
						char* sub_selector_string;
						_tmp9_ = NULL;
						sub_selector_string = (_tmp9_ = sub_selector_string_collection[sub_selector_string_it], (_tmp9_ == NULL) ? NULL : g_strdup (_tmp9_));
						{
							if (m->pos_rx == NULL) {
								char* s1;
								char* s2;
								OnigRx* _tmp7_;
								char* _tmp6_;
								char* _tmp5_;
								s1 = string_helper_gsub (g_strstrip (sub_selector_string), ".", "\\.");
								s2 = string_helper_gsub (s1, " ", ").* .*(");
								/*stdout.printf("positive '%s' -> '%s'\n", selector_string, "("+s2+")");*/
								_tmp7_ = NULL;
								_tmp6_ = NULL;
								_tmp5_ = NULL;
								m->pos_rx = (_tmp7_ = onig_rx_make1 (_tmp6_ = g_strconcat (_tmp5_ = g_strconcat ("(", s2, NULL), ")", NULL)), (m->pos_rx == NULL) ? NULL : (m->pos_rx = (g_object_unref (m->pos_rx), NULL)), _tmp7_);
								_tmp6_ = (g_free (_tmp6_), NULL);
								_tmp5_ = (g_free (_tmp5_), NULL);
								s1 = (g_free (s1), NULL);
								s2 = (g_free (s2), NULL);
							} else {
								char* s1;
								char* s2;
								OnigRx* _tmp8_;
								s1 = string_helper_gsub (g_strstrip (sub_selector_string), ".", "\\.");
								s2 = string_helper_gsub (s1, " ", ".* .*");
								/*stdout.printf("negative '%s' -> '%s'\n", selector_string, s2);*/
								_tmp8_ = NULL;
								gee_collection_add ((GeeCollection*) m->neg_rxs, _tmp8_ = onig_rx_make1 (s2));
								(_tmp8_ == NULL) ? NULL : (_tmp8_ = (g_object_unref (_tmp8_), NULL));
								s1 = (g_free (s1), NULL);
								s2 = (g_free (s2), NULL);
							}
							sub_selector_string = (g_free (sub_selector_string), NULL);
						}
					}
				}
				gee_collection_add ((GeeCollection*) ms, m);
				selector_string1 = (g_free (selector_string1), NULL);
				(m == NULL) ? NULL : (m = (g_object_unref (m), NULL));
				positives_and_negatives = (_vala_array_free (positives_and_negatives, positives_and_negatives_length1, (GDestroyNotify) g_free), NULL);
			}
		}
	}
	_tmp11_ = NULL;
	return (_tmp11_ = ms, scope_ors1 = (_vala_array_free (scope_ors1, scope_ors1_length1, (GDestroyNotify) g_free), NULL), _tmp11_);
}


gboolean gtk_mate_matcher_test_match_re (OnigRx* positive_selector_regex, GeeArrayList* negative_selector_regex, const char* scope_string, OnigMatch** match) {
	OnigMatch* m;
	g_return_val_if_fail (positive_selector_regex != NULL, FALSE);
	g_return_val_if_fail (negative_selector_regex != NULL, FALSE);
	g_return_val_if_fail (scope_string != NULL, FALSE);
	*match = NULL;
	m = onig_rx_search (positive_selector_regex, scope_string, 0, (gint) strlen (scope_string));
	if (m != NULL) {
		OnigMatch* _tmp2_;
		OnigMatch* _tmp1_;
		gboolean _tmp3_;
		{
			GeeIterator* _neg_rx_it;
			_neg_rx_it = gee_iterable_iterator ((GeeIterable*) negative_selector_regex);
			while (gee_iterator_next (_neg_rx_it)) {
				OnigRx* neg_rx;
				OnigMatch* m1;
				neg_rx = (OnigRx*) gee_iterator_get (_neg_rx_it);
				m1 = onig_rx_search (neg_rx, scope_string, 0, (gint) strlen (scope_string));
				if (m1 != NULL) {
					gboolean _tmp0_;
					return (_tmp0_ = FALSE, (neg_rx == NULL) ? NULL : (neg_rx = (g_object_unref (neg_rx), NULL)), (m1 == NULL) ? NULL : (m1 = (g_object_unref (m1), NULL)), (_neg_rx_it == NULL) ? NULL : (_neg_rx_it = (g_object_unref (_neg_rx_it), NULL)), (m == NULL) ? NULL : (m = (g_object_unref (m), NULL)), _tmp0_);
				}
				(neg_rx == NULL) ? NULL : (neg_rx = (g_object_unref (neg_rx), NULL));
				(m1 == NULL) ? NULL : (m1 = (g_object_unref (m1), NULL));
			}
			(_neg_rx_it == NULL) ? NULL : (_neg_rx_it = (g_object_unref (_neg_rx_it), NULL));
		}
		_tmp2_ = NULL;
		_tmp1_ = NULL;
		(*match) = (_tmp2_ = (_tmp1_ = m, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), ((*match) == NULL) ? NULL : ((*match) = (g_object_unref ((*match)), NULL)), _tmp2_);
		return (_tmp3_ = TRUE, (m == NULL) ? NULL : (m = (g_object_unref (m), NULL)), _tmp3_);
	} else {
		gboolean _tmp4_;
		return (_tmp4_ = FALSE, (m == NULL) ? NULL : (m = (g_object_unref (m), NULL)), _tmp4_);
	}
	(m == NULL) ? NULL : (m = (g_object_unref (m), NULL));
}


GtkMateMatcher* gtk_mate_matcher_construct (GType object_type) {
	GtkMateMatcher * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


GtkMateMatcher* gtk_mate_matcher_new (void) {
	return gtk_mate_matcher_construct (GTK_MATE_TYPE_MATCHER);
}


static void gtk_mate_matcher_class_init (GtkMateMatcherClass * klass) {
	gtk_mate_matcher_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_matcher_finalize;
}


static void gtk_mate_matcher_instance_init (GtkMateMatcher * self) {
}


static void gtk_mate_matcher_finalize (GObject* obj) {
	GtkMateMatcher * self;
	self = GTK_MATE_MATCHER (obj);
	(self->pos_rx == NULL) ? NULL : (self->pos_rx = (g_object_unref (self->pos_rx), NULL));
	(self->neg_rxs == NULL) ? NULL : (self->neg_rxs = (g_object_unref (self->neg_rxs), NULL));
	G_OBJECT_CLASS (gtk_mate_matcher_parent_class)->finalize (obj);
}


GType gtk_mate_matcher_get_type (void) {
	static GType gtk_mate_matcher_type_id = 0;
	if (gtk_mate_matcher_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateMatcherClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_matcher_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateMatcher), 0, (GInstanceInitFunc) gtk_mate_matcher_instance_init, NULL };
		gtk_mate_matcher_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateMatcher", &g_define_type_info, 0);
	}
	return gtk_mate_matcher_type_id;
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
}


static gint _vala_array_length (gpointer array) {
	int length;
	length = 0;
	if (array) {
		while (((gpointer*) array)[length]) {
			length++;
		}
	}
	return length;
}




