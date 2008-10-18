
#include "parser.h"
#include <gee/collection.h>
#include <gee/hashmap.h>
#include <gee/map.h>
#include "colourer.h"
#include "buffer.h"
#include "scope.h"
#include "pattern.h"
#include "scanner.h"




static glong string_get_length (const char* self);
enum  {
	GTK_MATE_TEXT_LOC_DUMMY_PROPERTY
};
static gpointer gtk_mate_text_loc_parent_class = NULL;
static void gtk_mate_text_loc_finalize (GObject * obj);
struct _GtkMateParserPrivate {
	GtkMateGrammar* _grammar;
	GtkMateColourer* _colourer;
	GtkMateBuffer* _buffer;
};

#define GTK_MATE_PARSER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_TYPE_PARSER, GtkMateParserPrivate))
enum  {
	GTK_MATE_PARSER_DUMMY_PROPERTY,
	GTK_MATE_PARSER_GRAMMAR,
	GTK_MATE_PARSER_COLOURER,
	GTK_MATE_PARSER_BUFFER
};
GeeArrayList* gtk_mate_parser_existing_parsers = NULL;
static void gtk_mate_parser_process_changes (GtkMateParser* self);
static gint gtk_mate_parser_parse_range (GtkMateParser* self, gint from_line, gint to_line);
static gboolean gtk_mate_parser_parse_line (GtkMateParser* self, gint line_ix);
static void _gtk_mate_parser_insert_text_handler_gtk_text_buffer_insert_text (GtkMateBuffer* _sender, GtkTextIter* pos, const char* text, gint length, gpointer self);
static void _gtk_mate_parser_delete_range_handler_gtk_text_buffer_delete_range (GtkMateBuffer* _sender, GtkTextIter* start, GtkTextIter* end, gpointer self);
static gpointer gtk_mate_parser_parent_class = NULL;
static void gtk_mate_parser_finalize (GObject * obj);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static int _vala_strcmp0 (const char * str1, const char * str2);



static glong string_get_length (const char* self) {
	g_return_val_if_fail (self != NULL, 0L);
	return g_utf8_strlen (self, -1);
}


GtkMateTextLoc* gtk_mate_text_loc_make (gint l, gint lo) {
	GtkMateTextLoc* tl;
	tl = g_object_ref_sink (gtk_mate_text_loc_new ());
	tl->line = l;
	tl->line_offset = lo;
	return tl;
}


gboolean gtk_mate_text_loc_equal (GtkMateTextLoc* t1, GtkMateTextLoc* t2) {
	g_return_val_if_fail (GTK_MATE_IS_TEXT_LOC (t1), FALSE);
	g_return_val_if_fail (GTK_MATE_IS_TEXT_LOC (t2), FALSE);
	return (t1->line == t2->line && t1->line_offset == t2->line_offset);
}


gboolean gtk_mate_text_loc_gt (GtkMateTextLoc* t1, GtkMateTextLoc* t2) {
	g_return_val_if_fail (GTK_MATE_IS_TEXT_LOC (t1), FALSE);
	g_return_val_if_fail (GTK_MATE_IS_TEXT_LOC (t2), FALSE);
	return ((t1->line > t2->line) || (t1->line >= t2->line && t1->line_offset > t2->line_offset));
}


gboolean gtk_mate_text_loc_lt (GtkMateTextLoc* t1, GtkMateTextLoc* t2) {
	g_return_val_if_fail (GTK_MATE_IS_TEXT_LOC (t1), FALSE);
	g_return_val_if_fail (GTK_MATE_IS_TEXT_LOC (t2), FALSE);
	return (!gtk_mate_text_loc_equal (t1, t2) && !gtk_mate_text_loc_gt (t1, t2));
}


gboolean gtk_mate_text_loc_gte (GtkMateTextLoc* t1, GtkMateTextLoc* t2) {
	g_return_val_if_fail (GTK_MATE_IS_TEXT_LOC (t1), FALSE);
	g_return_val_if_fail (GTK_MATE_IS_TEXT_LOC (t2), FALSE);
	return (!gtk_mate_text_loc_lt (t1, t2));
}


gboolean gtk_mate_text_loc_lte (GtkMateTextLoc* t1, GtkMateTextLoc* t2) {
	g_return_val_if_fail (GTK_MATE_IS_TEXT_LOC (t1), FALSE);
	g_return_val_if_fail (GTK_MATE_IS_TEXT_LOC (t2), FALSE);
	return (!gtk_mate_text_loc_gt (t1, t2));
}


char* gtk_mate_text_loc_to_s (GtkMateTextLoc* self) {
	g_return_val_if_fail (GTK_MATE_IS_TEXT_LOC (self), NULL);
	return g_strdup_printf ("{%d,%d}", self->line, self->line_offset);
}


GtkMateTextLoc* gtk_mate_text_loc_new (void) {
	GtkMateTextLoc * self;
	self = g_object_newv (GTK_MATE_TYPE_TEXT_LOC, 0, NULL);
	return self;
}


static void gtk_mate_text_loc_class_init (GtkMateTextLocClass * klass) {
	gtk_mate_text_loc_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_text_loc_finalize;
}


static void gtk_mate_text_loc_instance_init (GtkMateTextLoc * self) {
}


static void gtk_mate_text_loc_finalize (GObject * obj) {
	GtkMateTextLoc * self;
	self = GTK_MATE_TEXT_LOC (obj);
	G_OBJECT_CLASS (gtk_mate_text_loc_parent_class)->finalize (obj);
}


GType gtk_mate_text_loc_get_type (void) {
	static GType gtk_mate_text_loc_type_id = 0;
	if (gtk_mate_text_loc_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateTextLocClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_text_loc_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateTextLoc), 0, (GInstanceInitFunc) gtk_mate_text_loc_instance_init };
		gtk_mate_text_loc_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateTextLoc", &g_define_type_info, 0);
	}
	return gtk_mate_text_loc_type_id;
}


void gtk_mate_parser_make_root (GtkMateParser* self) {
	GtkMateScope* _tmp0;
	GtkTextIter _tmp2 = {0};
	GtkTextIter _tmp1 = {0};
	GtkMateDoublePattern* dp;
	char* _tmp4;
	const char* _tmp3;
	GeeArrayList* _tmp6;
	GeeArrayList* _tmp5;
	GtkMatePattern* _tmp8;
	GtkMatePattern* _tmp7;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	_tmp0 = NULL;
	self->root = (_tmp0 = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, self->priv->_grammar->scope_name)), (self->root == NULL ? NULL : (self->root = (g_object_unref (self->root), NULL))), _tmp0);
	self->root->is_open = TRUE;
	gtk_mate_scope_start_mark_set (self->root, 0, 0, TRUE);
	gtk_mate_scope_end_mark_set (self->root, gtk_text_iter_get_line ((_tmp1 = gtk_mate_buffer_end_iter (self->priv->_buffer), &_tmp1)), gtk_text_iter_get_line_offset ((_tmp2 = gtk_mate_buffer_end_iter (self->priv->_buffer), &_tmp2)), FALSE);
	dp = g_object_ref_sink (gtk_mate_double_pattern_new ());
	_tmp4 = NULL;
	_tmp3 = NULL;
	GTK_MATE_PATTERN (dp)->name = (_tmp4 = (_tmp3 = gtk_mate_grammar_get_name (self->priv->_grammar), (_tmp3 == NULL ? NULL : g_strdup (_tmp3))), (GTK_MATE_PATTERN (dp)->name = (g_free (GTK_MATE_PATTERN (dp)->name), NULL)), _tmp4);
	_tmp6 = NULL;
	_tmp5 = NULL;
	dp->patterns = (_tmp6 = (_tmp5 = self->priv->_grammar->patterns, (_tmp5 == NULL ? NULL : g_object_ref (_tmp5))), (dp->patterns == NULL ? NULL : (dp->patterns = (g_object_unref (dp->patterns), NULL))), _tmp6);
	_tmp8 = NULL;
	_tmp7 = NULL;
	self->root->pattern = (_tmp8 = (_tmp7 = GTK_MATE_PATTERN (dp), (_tmp7 == NULL ? NULL : g_object_ref (_tmp7))), (self->root->pattern == NULL ? NULL : (self->root->pattern = (g_object_unref (self->root->pattern), NULL))), _tmp8);
	(dp == NULL ? NULL : (dp = (g_object_unref (dp), NULL)));
}


void gtk_mate_parser_stop_parsing (GtkMateParser* self) {
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	self->deactivation_level = self->deactivation_level + (1);
}


void gtk_mate_parser_start_parsing (GtkMateParser* self) {
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	if (self->deactivation_level > 0) {
		self->deactivation_level = self->deactivation_level - (1);
	}
	if (self->deactivation_level == 0) {
		gtk_mate_parser_process_changes (self);
	}
}


gboolean gtk_mate_parser_is_parsing (GtkMateParser* self) {
	g_return_val_if_fail (GTK_MATE_IS_PARSER (self), FALSE);
	return (self->deactivation_level == 0);
}


/* Process all change ranges.*/
static void gtk_mate_parser_process_changes (GtkMateParser* self) {
	gint parsed_upto;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	parsed_upto = -1;
	{
		RangeSet* range_collection;
		GeeIterator* range_it;
		range_collection = self->changes;
		range_it = gee_iterable_iterator (GEE_ITERABLE (range_collection));
		while (gee_iterator_next (range_it)) {
			RangeSetRange* range;
			range = ((RangeSetRange*) (gee_iterator_get (range_it)));
			{
				if (range->b > parsed_upto) {
					parsed_upto = gtk_mate_parser_parse_range (self, range->a, range->b);
				}
				(range == NULL ? NULL : (range = (g_object_unref (range), NULL)));
			}
		}
		(range_it == NULL ? NULL : (range_it = (g_object_unref (range_it), NULL)));
	}
	/*//stdout.printf("%s\n", root.pretty(0));*/
	gee_collection_clear (GEE_COLLECTION (self->changes->ranges));
}


/* Parse from from_line to *at least* to_line. Will parse
 more if necessary. Returns the index of the last line
 parsed.*/
static gint gtk_mate_parser_parse_range (GtkMateParser* self, gint from_line, gint to_line) {
	gint line_ix;
	gboolean scope_changed;
	gboolean scope_ever_changed;
	g_return_val_if_fail (GTK_MATE_IS_PARSER (self), 0);
	/*stdout.printf("parse_from(%d, %d)\n", from_line, to_line);*/
	line_ix = from_line;
	scope_changed = FALSE;
	scope_ever_changed = FALSE;
	while (line_ix <= to_line || (scope_ever_changed && line_ix <= gtk_text_buffer_get_line_count (GTK_TEXT_BUFFER (self->priv->_buffer)) - 1)) {
		scope_changed = gtk_mate_parser_parse_line (self, line_ix++);
		if (scope_changed) {
			scope_ever_changed = TRUE;
			/* In the old scheme this wasn't necessary because 
			 the scope_at used a simple scan from the front. The GSequences
			 on the other hand can get confused if the later scopes
			 are inconsistent with earler ones. So we have to clear everything.
			 TODO: figure out a way to OPTIMIZE this again.*/
			gtk_mate_scope_clear_after (self->root, line_ix, -1);
		}
	}
	/*stdout.printf("parse_line returned: %s\n", scope_changed ? "true" : "false");
	stdout.printf("pretty:\n%s\n", root.pretty(2));
	stdout.printf("parse_from:out\n");*/
	return to_line;
}


/* Parse line line_ix. Returns true if the ending
 scope of the line has changed.*/
static gboolean gtk_mate_parser_parse_line (GtkMateParser* self, gint line_ix) {
	char* line;
	gint length;
	GtkMateScope* start_scope;
	GtkMateScope* end_scope1;
	GtkMateScanner* scanner;
	gint i;
	GtkMateScope* s;
	GeeArrayList* all_scopes;
	GeeArrayList* closed_scopes;
	GeeArrayList* removed_scopes;
	GtkMateScope* end_scope2;
	gboolean _tmp0;
	g_return_val_if_fail (GTK_MATE_IS_PARSER (self), FALSE);
	line = gtk_mate_buffer_get_line1 (self->priv->_buffer, line_ix);
	length = ((gint) (string_get_length (line)));
	/*buffer.get_line_length(line_ix);
	 stdout.printf("\nparse line: %d (%d): '%s'\n", line_ix, length, line);*/
	start_scope = gtk_mate_scope_scope_at (self->root, line_ix, -1);
	end_scope1 = gtk_mate_scope_scope_at (self->root, line_ix, G_MAXINT);
	/*stdout.printf("scope_at returns: %s\n", start_scope.name);
	if (start_scope == null)
	stdout.printf("pretty:\n%s\n", root.pretty(2));
	stdout.printf("end_scope1: %s\n", end_scope1.name);*/
	scanner = g_object_ref_sink (gtk_mate_scanner_new (start_scope, line, length));
	i = 0;
	s = NULL;
	all_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
	closed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
	removed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
	gee_collection_add (GEE_COLLECTION (all_scopes), start_scope);
	{
		GtkMateScanner* m_collection;
		GeeIterator* m_it;
		m_collection = scanner;
		m_it = gee_iterable_iterator (GEE_ITERABLE (m_collection));
		while (gee_iterator_next (m_it)) {
			GtkMateMarker* m;
			m = ((GtkMateMarker*) (gee_iterator_get (m_it)));
			{
				GtkMateScope* expected_scope;
				expected_scope = gtk_mate_parser_get_expected_scope (self, gtk_mate_scanner_get_current_scope (scanner), line_ix, scanner->position);
				/* if (expected_scope != null)
				 stdout.printf("expected_scope: %s\n", expected_scope.name);
				 else
				 stdout.printf("no expected scope\n");
				 stdout.printf("  scope: %s\n", m.pattern.name);*/
				if (m->is_close_scope) {
					gtk_mate_parser_close_scope (self, scanner, expected_scope, line_ix, line, m, all_scopes, closed_scopes, removed_scopes);
				} else {
					if (GTK_MATE_IS_DOUBLE_PATTERN (m->pattern)) {
						gtk_mate_parser_open_scope (self, scanner, expected_scope, line_ix, line, length, m, all_scopes, closed_scopes, removed_scopes);
					} else {
						gtk_mate_parser_single_scope (self, scanner, expected_scope, line_ix, line, length, m, all_scopes, closed_scopes, removed_scopes);
					}
				}
				scanner->position = onig_match_end (m->match, 0);
				(m == NULL ? NULL : (m = (g_object_unref (m), NULL)));
				(expected_scope == NULL ? NULL : (expected_scope = (g_object_unref (expected_scope), NULL)));
			}
		}
		(m_it == NULL ? NULL : (m_it = (g_object_unref (m_it), NULL)));
	}
	gtk_mate_parser_clear_line (self, line_ix, start_scope, all_scopes, closed_scopes, removed_scopes);
	end_scope2 = gtk_mate_scope_scope_at (self->root, line_ix, G_MAXINT);
	/*stdout.printf("end_scope2: %s\n", end_scope2.name);*/
	if (self->priv->_colourer != NULL) {
		/*stdout.printf("before_uncolour_scopes\n");*/
		gtk_mate_colourer_uncolour_scopes (self->priv->_colourer, removed_scopes);
		/*stdout.printf("before_colour_line_with_scopes\n");*/
		gtk_mate_colourer_colour_line_with_scopes (self->priv->_colourer, all_scopes);
	} else {
	}
	/*stdout.printf("after_colour_line_with_scopes\n");
	 stdout.printf("no colourer");
	 stdout.printf("%s\n", this.root.pretty(0));*/
	return (_tmp0 = (end_scope1 != end_scope2), (line = (g_free (line), NULL)), (start_scope == NULL ? NULL : (start_scope = (g_object_unref (start_scope), NULL))), (end_scope1 == NULL ? NULL : (end_scope1 = (g_object_unref (end_scope1), NULL))), (scanner == NULL ? NULL : (scanner = (g_object_unref (scanner), NULL))), (s == NULL ? NULL : (s = (g_object_unref (s), NULL))), (all_scopes == NULL ? NULL : (all_scopes = (g_object_unref (all_scopes), NULL))), (closed_scopes == NULL ? NULL : (closed_scopes = (g_object_unref (closed_scopes), NULL))), (removed_scopes == NULL ? NULL : (removed_scopes = (g_object_unref (removed_scopes), NULL))), (end_scope2 == NULL ? NULL : (end_scope2 = (g_object_unref (end_scope2), NULL))), _tmp0);
}


void gtk_mate_parser_clear_line (GtkMateParser* self, gint line_ix, GtkMateScope* start_scope, GeeArrayList* all_scopes, GeeArrayList* closed_scopes, GeeArrayList* removed_scopes) {
	GtkMateScope* _tmp0;
	GtkMateScope* cs;
	GeeArrayList* scopes_that_closed_on_line;
	GtkMateScope* _tmp3;
	GtkMateScope* ts;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_SCOPE (start_scope));
	g_return_if_fail (GEE_IS_ARRAY_LIST (all_scopes));
	g_return_if_fail (GEE_IS_ARRAY_LIST (closed_scopes));
	g_return_if_fail (GEE_IS_ARRAY_LIST (removed_scopes));
	/* If we are reparsing, we might find that some scopes have disappeared,
	 delete them:*/
	_tmp0 = NULL;
	cs = (_tmp0 = start_scope, (_tmp0 == NULL ? NULL : g_object_ref (_tmp0)));
	while (cs != NULL) {
		GeeArrayList* removed;
		GtkMateScope* _tmp2;
		GtkMateScope* _tmp1;
		/*stdout.printf("  removing_scopes from: %s\n", cs.name);*/
		removed = gtk_mate_scope_delete_any_on_line_not_in (cs, line_ix, all_scopes);
		{
			GeeArrayList* rs_collection;
			int rs_it;
			rs_collection = removed;
			for (rs_it = 0; rs_it < gee_collection_get_size (GEE_COLLECTION (rs_collection)); rs_it = rs_it + 1) {
				GtkMateScope* rs;
				rs = ((GtkMateScope*) (gee_list_get (GEE_LIST (rs_collection), rs_it)));
				{
					gee_collection_add (GEE_COLLECTION (removed_scopes), rs);
					(rs == NULL ? NULL : (rs = (g_object_unref (rs), NULL)));
				}
			}
		}
		_tmp2 = NULL;
		_tmp1 = NULL;
		cs = (_tmp2 = (_tmp1 = cs->parent, (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (cs == NULL ? NULL : (cs = (g_object_unref (cs), NULL))), _tmp2);
		(removed == NULL ? NULL : (removed = (g_object_unref (removed), NULL)));
	}
	/* @removed_scopes += removed_scopes
	 any that we expected to close on this line that now don't?
	  first build list of scopes that close on this line (including ones
	  that did but haven't been removed yet).*/
	scopes_that_closed_on_line = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
	_tmp3 = NULL;
	ts = (_tmp3 = start_scope, (_tmp3 == NULL ? NULL : g_object_ref (_tmp3)));
	while (ts->parent != NULL) {
		GtkMateScope* _tmp5;
		GtkMateScope* _tmp4;
		if (gtk_mate_scope_end_line (ts) == line_ix) {
			gee_collection_add (GEE_COLLECTION (scopes_that_closed_on_line), ts);
		}
		_tmp5 = NULL;
		_tmp4 = NULL;
		ts = (_tmp5 = (_tmp4 = ts->parent, (_tmp4 == NULL ? NULL : g_object_ref (_tmp4))), (ts == NULL ? NULL : (ts = (g_object_unref (ts), NULL))), _tmp5);
	}
	{
		GeeArrayList* s_collection;
		int s_it;
		s_collection = scopes_that_closed_on_line;
		for (s_it = 0; s_it < gee_collection_get_size (GEE_COLLECTION (s_collection)); s_it = s_it + 1) {
			GtkMateScope* s;
			s = ((GtkMateScope*) (gee_list_get (GEE_LIST (s_collection), s_it)));
			{
				if (!gee_collection_contains (GEE_COLLECTION (closed_scopes), s)) {
					if (s->is_capture) {
						gtk_mate_scope_delete_child (s->parent, s);
						gee_collection_add (GEE_COLLECTION (removed_scopes), s);
					} else {
						GtkTextMark* _tmp6;
						GtkTextMark* _tmp7;
						/* @removed_scopes << s*/
						if (self->priv->_colourer != NULL) {
							gtk_mate_colourer_uncolour_scope (self->priv->_colourer, s, FALSE);
						}
						_tmp6 = NULL;
						s->inner_end_mark = (_tmp6 = NULL, (s->inner_end_mark == NULL ? NULL : (s->inner_end_mark = (g_object_unref (s->inner_end_mark), NULL))), _tmp6);
						_tmp7 = NULL;
						s->end_mark = (_tmp7 = NULL, (s->end_mark == NULL ? NULL : (s->end_mark = (g_object_unref (s->end_mark), NULL))), _tmp7);
						s->is_open = TRUE;
					}
				}
				(s == NULL ? NULL : (s = (g_object_unref (s), NULL)));
			}
		}
	}
	(cs == NULL ? NULL : (cs = (g_object_unref (cs), NULL)));
	(scopes_that_closed_on_line == NULL ? NULL : (scopes_that_closed_on_line = (g_object_unref (scopes_that_closed_on_line), NULL)));
	(ts == NULL ? NULL : (ts = (g_object_unref (ts), NULL)));
}


GtkMateScope* gtk_mate_parser_get_expected_scope (GtkMateParser* self, GtkMateScope* current_scope, gint line, gint line_offset) {
	GtkMateTextLoc* _tmp0;
	GtkMateScope* _tmp1;
	GtkMateScope* expected_scope;
	g_return_val_if_fail (GTK_MATE_IS_PARSER (self), NULL);
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (current_scope), NULL);
	/* //stdout.printf("get_expected_scope(%s, %d, %d)\n", current_scope.name, line, line_offset);*/
	_tmp0 = NULL;
	_tmp1 = NULL;
	expected_scope = (_tmp1 = gtk_mate_scope_first_child_after (current_scope, (_tmp0 = gtk_mate_text_loc_make (line, line_offset))), (_tmp0 == NULL ? NULL : (_tmp0 = (g_object_unref (_tmp0), NULL))), _tmp1);
	/* //stdout.printf("first_child_after: %s\n", expected_scope.name);*/
	g_assert (expected_scope != current_scope);
	if (expected_scope != NULL) {
		if (gtk_mate_scope_start_line (expected_scope) != line) {
			GtkMateScope* _tmp2;
			_tmp2 = NULL;
			expected_scope = (_tmp2 = NULL, (expected_scope == NULL ? NULL : (expected_scope = (g_object_unref (expected_scope), NULL))), _tmp2);
		}
		while (expected_scope != NULL && expected_scope->is_capture) {
			GtkMateScope* _tmp4;
			GtkMateScope* _tmp3;
			_tmp4 = NULL;
			_tmp3 = NULL;
			expected_scope = (_tmp4 = (_tmp3 = expected_scope->parent, (_tmp3 == NULL ? NULL : g_object_ref (_tmp3))), (expected_scope == NULL ? NULL : (expected_scope = (g_object_unref (expected_scope), NULL))), _tmp4);
		}
	}
	return expected_scope;
}


void gtk_mate_parser_close_scope (GtkMateParser* self, GtkMateScanner* scanner, GtkMateScope* expected_scope, gint line_ix, const char* line, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes, GeeArrayList* removed_scopes) {
	char* _tmp0;
	char* end_match_string;
	GtkMateTextLoc* _tmp4;
	GtkMateTextLoc* _tmp3;
	GtkMateTextLoc* _tmp2;
	GtkMateTextLoc* _tmp1;
	gboolean _tmp5;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_SCANNER (scanner));
	g_return_if_fail (expected_scope == NULL || GTK_MATE_IS_SCOPE (expected_scope));
	g_return_if_fail (line != NULL);
	g_return_if_fail (GTK_MATE_IS_MARKER (m));
	g_return_if_fail (GEE_IS_ARRAY_LIST (all_scopes));
	g_return_if_fail (GEE_IS_ARRAY_LIST (closed_scopes));
	g_return_if_fail (GEE_IS_ARRAY_LIST (removed_scopes));
	_tmp0 = NULL;
	end_match_string = (_tmp0 = g_utf8_offset_to_pointer (line, ((glong) (m->from))), g_strndup (_tmp0, g_utf8_offset_to_pointer (_tmp0, ((glong) (onig_match_end (m->match, 0) - m->from))) - _tmp0));
	_tmp4 = NULL;
	_tmp3 = NULL;
	_tmp2 = NULL;
	_tmp1 = NULL;
	if ((_tmp5 = gtk_mate_scanner_get_current_scope (scanner)->end_mark != NULL && gtk_mate_text_loc_equal ((_tmp1 = gtk_mate_scope_end_loc (gtk_mate_scanner_get_current_scope (scanner))), (_tmp2 = gtk_mate_text_loc_make (line_ix, onig_match_end (m->match, 0)))) && gtk_mate_text_loc_equal ((_tmp3 = gtk_mate_scope_inner_end_loc (gtk_mate_scanner_get_current_scope (scanner))), (_tmp4 = gtk_mate_text_loc_make (line_ix, m->from))) && _vala_strcmp0 (gtk_mate_scanner_get_current_scope (scanner)->end_match_string, end_match_string) == 0, (_tmp4 == NULL ? NULL : (_tmp4 = (g_object_unref (_tmp4), NULL))), (_tmp3 == NULL ? NULL : (_tmp3 = (g_object_unref (_tmp3), NULL))), (_tmp2 == NULL ? NULL : (_tmp2 = (g_object_unref (_tmp2), NULL))), (_tmp1 == NULL ? NULL : (_tmp1 = (g_object_unref (_tmp1), NULL))), _tmp5)) {
		GSequenceIter* _tmp6;
		GSequenceIter* iter;
		/* we have already parsed this line and this scope ends here
		 Re-add the captures from the end of the current scope to the 
		 tracking arrays*/
		_tmp6 = NULL;
		iter = (_tmp6 = g_sequence_get_begin_iter (gtk_mate_scope_get_children (gtk_mate_scanner_get_current_scope (scanner))), (_tmp6 == NULL ? NULL :  (_tmp6)));
		while (!g_sequence_iter_is_end (iter)) {
			GtkMateScope* _tmp7;
			GtkMateScope* child;
			GSequenceIter* _tmp9;
			GSequenceIter* _tmp8;
			_tmp7 = NULL;
			child = (_tmp7 = ((GtkMateScope*) (g_sequence_get (iter))), (_tmp7 == NULL ? NULL : g_object_ref (_tmp7)));
			if (child->is_capture && gtk_mate_scope_start_line (child) == line_ix) {
				if (!gee_collection_contains (GEE_COLLECTION (closed_scopes), child)) {
					gee_collection_add (GEE_COLLECTION (closed_scopes), child);
				}
				if (!gee_collection_contains (GEE_COLLECTION (all_scopes), child)) {
					gee_collection_add (GEE_COLLECTION (all_scopes), child);
				}
			}
			_tmp9 = NULL;
			_tmp8 = NULL;
			iter = (_tmp9 = (_tmp8 = g_sequence_iter_next (iter), (_tmp8 == NULL ? NULL :  (_tmp8))), (iter == NULL ? NULL : (iter = ( (iter), NULL))), _tmp9);
			(child == NULL ? NULL : (child = (g_object_unref (child), NULL)));
		}
		(iter == NULL ? NULL : (iter = ( (iter), NULL)));
	} else {
		char* _tmp11;
		const char* _tmp10;
		/* stdout.printf("closing scope matches expected\n");
		 stdout.printf("closing scope at %d\n", m.from);*/
		if (self->priv->_colourer != NULL) {
			gtk_mate_colourer_uncolour_scope (self->priv->_colourer, gtk_mate_scanner_get_current_scope (scanner), FALSE);
		}
		gtk_mate_scope_inner_end_mark_set (gtk_mate_scanner_get_current_scope (scanner), line_ix, m->from, TRUE);
		gtk_mate_scope_end_mark_set (gtk_mate_scanner_get_current_scope (scanner), line_ix, onig_match_end (m->match, 0), TRUE);
		gtk_mate_scanner_get_current_scope (scanner)->is_open = FALSE;
		_tmp11 = NULL;
		_tmp10 = NULL;
		gtk_mate_scanner_get_current_scope (scanner)->end_match_string = (_tmp11 = (_tmp10 = end_match_string, (_tmp10 == NULL ? NULL : g_strdup (_tmp10))), (gtk_mate_scanner_get_current_scope (scanner)->end_match_string = (g_free (gtk_mate_scanner_get_current_scope (scanner)->end_match_string), NULL)), _tmp11);
		/*stdout.printf("end_match_string: '%s'\n", scanner.current_scope.end_match_string);*/
		gtk_mate_parser_handle_captures (self, line_ix, line, gtk_mate_scanner_get_current_scope (scanner), m, all_scopes, closed_scopes);
		if (expected_scope != NULL) {
			gtk_mate_scope_delete_child (gtk_mate_scanner_get_current_scope (scanner), expected_scope);
			gee_collection_add (GEE_COLLECTION (removed_scopes), expected_scope);
		}
	}
	/* @removed_scopes << expected_scope*/
	gee_collection_add (GEE_COLLECTION (removed_scopes), gtk_mate_scanner_get_current_scope (scanner));
	/* so it gets uncoloured*/
	gee_collection_add (GEE_COLLECTION (closed_scopes), gtk_mate_scanner_get_current_scope (scanner));
	gtk_mate_scanner_set_current_scope (scanner, gtk_mate_scanner_get_current_scope (scanner)->parent);
	gee_collection_add (GEE_COLLECTION (all_scopes), gtk_mate_scanner_get_current_scope (scanner));
	end_match_string = (g_free (end_match_string), NULL);
}


void gtk_mate_parser_open_scope (GtkMateParser* self, GtkMateScanner* scanner, GtkMateScope* expected_scope, gint line_ix, const char* line, gint length, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes, GeeArrayList* removed_scopes) {
	GtkMateScope* s;
	GtkMatePattern* _tmp1;
	GtkMatePattern* _tmp0;
	OnigMatch* _tmp3;
	OnigMatch* _tmp2;
	char* _tmp5;
	char* _tmp4;
	GtkTextIter end_iter;
	gint end_line;
	gint end_line_offset;
	GtkMateScope* _tmp7;
	GtkMateScope* _tmp6;
	GtkMateScope* _tmp8;
	GtkMateScope* new_scope;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_SCANNER (scanner));
	g_return_if_fail (expected_scope == NULL || GTK_MATE_IS_SCOPE (expected_scope));
	g_return_if_fail (line != NULL);
	g_return_if_fail (GTK_MATE_IS_MARKER (m));
	g_return_if_fail (GEE_IS_ARRAY_LIST (all_scopes));
	g_return_if_fail (GEE_IS_ARRAY_LIST (closed_scopes));
	g_return_if_fail (GEE_IS_ARRAY_LIST (removed_scopes));
	/*stdout.printf("[opening with %d patterns], \n", ((DoublePattern) m.pattern).patterns.size);*/
	s = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, m->pattern->name));
	_tmp1 = NULL;
	_tmp0 = NULL;
	s->pattern = (_tmp1 = (_tmp0 = m->pattern, (_tmp0 == NULL ? NULL : g_object_ref (_tmp0))), (s->pattern == NULL ? NULL : (s->pattern = (g_object_unref (s->pattern), NULL))), _tmp1);
	_tmp3 = NULL;
	_tmp2 = NULL;
	s->open_match = (_tmp3 = (_tmp2 = m->match, (_tmp2 == NULL ? NULL : g_object_ref (_tmp2))), (s->open_match == NULL ? NULL : (s->open_match = (g_object_unref (s->open_match), NULL))), _tmp3);
	gtk_mate_scope_start_mark_set (s, line_ix, m->from, FALSE);
	gtk_mate_scope_inner_start_mark_set (s, line_ix, MIN (onig_match_end (m->match, 0), length), TRUE);
	/* had right gravity in Ruby version. Important?*/
	_tmp5 = NULL;
	_tmp4 = NULL;
	s->begin_match_string = (_tmp5 = (_tmp4 = g_utf8_offset_to_pointer (line, ((glong) (m->from))), g_strndup (_tmp4, g_utf8_offset_to_pointer (_tmp4, ((glong) (onig_match_end (m->match, 0) - m->from))) - _tmp4)), (s->begin_match_string = (g_free (s->begin_match_string), NULL)), _tmp5);
	/*stdout.printf("begin_match_string: '%s'\n", s.begin_match_string);*/
	end_iter = gtk_mate_buffer_end_iter (self->priv->_buffer);
	end_line = gtk_text_iter_get_line (&end_iter);
	end_line_offset = gtk_text_iter_get_line_offset (&end_iter);
	gtk_mate_scope_inner_end_mark_set (s, end_line, end_line_offset, FALSE);
	gtk_mate_scope_end_mark_set (s, end_line, end_line_offset, FALSE);
	s->is_open = TRUE;
	s->is_capture = FALSE;
	_tmp7 = NULL;
	_tmp6 = NULL;
	s->parent = (_tmp7 = (_tmp6 = gtk_mate_scanner_get_current_scope (scanner), (_tmp6 == NULL ? NULL : g_object_ref (_tmp6))), (s->parent == NULL ? NULL : (s->parent = (g_object_unref (s->parent), NULL))), _tmp7);
	_tmp8 = NULL;
	new_scope = (_tmp8 = s, (_tmp8 == NULL ? NULL : g_object_ref (_tmp8)));
	/* is this a bug? captures aren't necessarily to be put into all_scopes yet surely?*/
	gtk_mate_parser_handle_captures (self, line_ix, line, s, m, all_scopes, closed_scopes);
	if (expected_scope != NULL) {
		/* check mod ending scopes as the new one will not have a closing marker
		 but the expected one will:*/
		if (gtk_mate_scope_surface_identical_to_modulo_ending (s, expected_scope)) {
			GtkMateScope* _tmp10;
			GtkMateScope* _tmp9;
			GSequenceIter* _tmp11;
			GSequenceIter* iter;
			/*stdout.printf("surface_identical_mod_ending: keep expected\n");
			 don't need to do anything as we have already found this,
			 but let's keep the old scope since it will have children and what not.*/
			_tmp10 = NULL;
			_tmp9 = NULL;
			new_scope = (_tmp10 = (_tmp9 = expected_scope, (_tmp9 == NULL ? NULL : g_object_ref (_tmp9))), (new_scope == NULL ? NULL : (new_scope = (g_object_unref (new_scope), NULL))), _tmp10);
			_tmp11 = NULL;
			iter = (_tmp11 = g_sequence_get_begin_iter (gtk_mate_scope_get_children (expected_scope)), (_tmp11 == NULL ? NULL :  (_tmp11)));
			while (!g_sequence_iter_is_end (iter)) {
				GSequenceIter* _tmp13;
				GSequenceIter* _tmp12;
				gee_collection_add (GEE_COLLECTION (closed_scopes), ((GtkMateScope*) (g_sequence_get (iter))));
				_tmp13 = NULL;
				_tmp12 = NULL;
				iter = (_tmp13 = (_tmp12 = g_sequence_iter_next (iter), (_tmp12 == NULL ? NULL :  (_tmp12))), (iter == NULL ? NULL : (iter = ( (iter), NULL))), _tmp13);
			}
			gtk_mate_scanner_set_current_scope (scanner, expected_scope);
			(iter == NULL ? NULL : (iter = ( (iter), NULL)));
		} else {
			/*stdout.printf("surface_NOT_identical_mod_ending: replace expected\n");*/
			if (gtk_mate_scope_overlaps_with (s, expected_scope)) {
				gtk_mate_scope_delete_child (gtk_mate_scanner_get_current_scope (scanner), expected_scope);
				/* removed_scopes << expected_scope*/
				gee_collection_add (GEE_COLLECTION (removed_scopes), expected_scope);
			}
			gtk_mate_scope_add_child (gtk_mate_scanner_get_current_scope (scanner), s);
			gtk_mate_scanner_set_current_scope (scanner, s);
		}
	} else {
		gtk_mate_scope_add_child (gtk_mate_scanner_get_current_scope (scanner), s);
		gtk_mate_scanner_set_current_scope (scanner, s);
	}
	gee_collection_add (GEE_COLLECTION (all_scopes), new_scope);
	(s == NULL ? NULL : (s = (g_object_unref (s), NULL)));
	(new_scope == NULL ? NULL : (new_scope = (g_object_unref (new_scope), NULL)));
}


void gtk_mate_parser_single_scope (GtkMateParser* self, GtkMateScanner* scanner, GtkMateScope* expected_scope, gint line_ix, const char* line, gint length, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes, GeeArrayList* removed_scopes) {
	GtkMateScope* s;
	GtkMatePattern* _tmp1;
	GtkMatePattern* _tmp0;
	OnigMatch* _tmp3;
	OnigMatch* _tmp2;
	char* _tmp5;
	char* _tmp4;
	GtkMateScope* _tmp7;
	GtkMateScope* _tmp6;
	GtkMateScope* _tmp8;
	GtkMateScope* new_scope;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_SCANNER (scanner));
	g_return_if_fail (expected_scope == NULL || GTK_MATE_IS_SCOPE (expected_scope));
	g_return_if_fail (line != NULL);
	g_return_if_fail (GTK_MATE_IS_MARKER (m));
	g_return_if_fail (GEE_IS_ARRAY_LIST (all_scopes));
	g_return_if_fail (GEE_IS_ARRAY_LIST (closed_scopes));
	g_return_if_fail (GEE_IS_ARRAY_LIST (removed_scopes));
	s = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, m->pattern->name));
	_tmp1 = NULL;
	_tmp0 = NULL;
	s->pattern = (_tmp1 = (_tmp0 = m->pattern, (_tmp0 == NULL ? NULL : g_object_ref (_tmp0))), (s->pattern == NULL ? NULL : (s->pattern = (g_object_unref (s->pattern), NULL))), _tmp1);
	_tmp3 = NULL;
	_tmp2 = NULL;
	s->open_match = (_tmp3 = (_tmp2 = m->match, (_tmp2 == NULL ? NULL : g_object_ref (_tmp2))), (s->open_match == NULL ? NULL : (s->open_match = (g_object_unref (s->open_match), NULL))), _tmp3);
	gtk_mate_scope_start_mark_set (s, line_ix, m->from, FALSE);
	gtk_mate_scope_end_mark_set (s, line_ix, MIN (onig_match_end (m->match, 0), length), TRUE);
	s->is_open = FALSE;
	s->is_capture = FALSE;
	_tmp5 = NULL;
	_tmp4 = NULL;
	s->begin_match_string = (_tmp5 = (_tmp4 = g_utf8_offset_to_pointer (line, ((glong) (m->from))), g_strndup (_tmp4, g_utf8_offset_to_pointer (_tmp4, ((glong) (onig_match_end (m->match, 0) - m->from))) - _tmp4)), (s->begin_match_string = (g_free (s->begin_match_string), NULL)), _tmp5);
	/*stdout.printf("_match_string: '%s'\n", s.begin_match_string);*/
	_tmp7 = NULL;
	_tmp6 = NULL;
	s->parent = (_tmp7 = (_tmp6 = gtk_mate_scanner_get_current_scope (scanner), (_tmp6 == NULL ? NULL : g_object_ref (_tmp6))), (s->parent == NULL ? NULL : (s->parent = (g_object_unref (s->parent), NULL))), _tmp7);
	_tmp8 = NULL;
	new_scope = (_tmp8 = s, (_tmp8 == NULL ? NULL : g_object_ref (_tmp8)));
	if (expected_scope != NULL) {
		if (gtk_mate_scope_surface_identical_to (s, expected_scope)) {
			GtkMateScope* _tmp10;
			GtkMateScope* _tmp9;
			GSequenceIter* _tmp11;
			GSequenceIter* iter;
			_tmp10 = NULL;
			_tmp9 = NULL;
			new_scope = (_tmp10 = (_tmp9 = expected_scope, (_tmp9 == NULL ? NULL : g_object_ref (_tmp9))), (new_scope == NULL ? NULL : (new_scope = (g_object_unref (new_scope), NULL))), _tmp10);
			_tmp11 = NULL;
			iter = (_tmp11 = g_sequence_get_begin_iter (gtk_mate_scope_get_children (expected_scope)), (_tmp11 == NULL ? NULL :  (_tmp11)));
			while (!g_sequence_iter_is_end (iter)) {
				GSequenceIter* _tmp13;
				GSequenceIter* _tmp12;
				gee_collection_add (GEE_COLLECTION (closed_scopes), ((GtkMateScope*) (g_sequence_get (iter))));
				_tmp13 = NULL;
				_tmp12 = NULL;
				iter = (_tmp13 = (_tmp12 = g_sequence_iter_next (iter), (_tmp12 == NULL ? NULL :  (_tmp12))), (iter == NULL ? NULL : (iter = ( (iter), NULL))), _tmp13);
			}
			(iter == NULL ? NULL : (iter = ( (iter), NULL)));
		} else {
			gtk_mate_parser_handle_captures (self, line_ix, line, s, m, all_scopes, closed_scopes);
			if (gtk_mate_scope_overlaps_with (s, expected_scope)) {
				gtk_mate_scope_delete_child (gtk_mate_scanner_get_current_scope (scanner), expected_scope);
				/* removed_scopes << expected_scope*/
				gee_collection_add (GEE_COLLECTION (removed_scopes), expected_scope);
			}
			gtk_mate_scope_add_child (gtk_mate_scanner_get_current_scope (scanner), s);
		}
	} else {
		gtk_mate_parser_handle_captures (self, line_ix, line, s, m, all_scopes, closed_scopes);
		gtk_mate_scope_add_child (gtk_mate_scanner_get_current_scope (scanner), s);
	}
	gee_collection_add (GEE_COLLECTION (all_scopes), new_scope);
	gee_collection_add (GEE_COLLECTION (closed_scopes), new_scope);
	(s == NULL ? NULL : (s = (g_object_unref (s), NULL)));
	(new_scope == NULL ? NULL : (new_scope = (g_object_unref (new_scope), NULL)));
}


/* Opens scopes for captures AND creates closing regexp from
 captures if necessary.*/
void gtk_mate_parser_handle_captures (GtkMateParser* self, gint line_ix, const char* line, GtkMateScope* scope, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes) {
	OnigRx* _tmp0;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (line != NULL);
	g_return_if_fail (GTK_MATE_IS_SCOPE (scope));
	g_return_if_fail (GTK_MATE_IS_MARKER (m));
	g_return_if_fail (GEE_IS_ARRAY_LIST (all_scopes));
	g_return_if_fail (GEE_IS_ARRAY_LIST (closed_scopes));
	_tmp0 = NULL;
	_tmp0 = gtk_mate_parser_make_closing_regex (self, line, scope, m);
	(_tmp0 == NULL ? NULL : (_tmp0 = (g_object_unref (_tmp0), NULL)));
	gtk_mate_parser_collect_child_captures (self, line_ix, scope, m, all_scopes, closed_scopes);
}


OnigRx* gtk_mate_parser_make_closing_regex (GtkMateParser* self, const char* line, GtkMateScope* scope, GtkMateMarker* m) {
	g_return_val_if_fail (GTK_MATE_IS_PARSER (self), NULL);
	g_return_val_if_fail (line != NULL, NULL);
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (scope), NULL);
	g_return_val_if_fail (GTK_MATE_IS_MARKER (m), NULL);
	/* new_end = pattern.end.gsub(/\\([0-9]+)/) do
	 md.captures.send(:[], $1.to_i-1)
	 end*/
	if (GTK_MATE_IS_DOUBLE_PATTERN (m->pattern) && !m->is_close_scope) {
		GtkMateDoublePattern* _tmp0;
		GtkMateDoublePattern* dp;
		OnigRx* rx;
		OnigMatch* match;
		gint pos;
		GString* src;
		gboolean found;
		OnigMatch* _tmp1;
		OnigRx* _tmp8;
		_tmp0 = NULL;
		dp = (_tmp0 = GTK_MATE_DOUBLE_PATTERN (m->pattern), (_tmp0 == NULL ? NULL : g_object_ref (_tmp0)));
		/*stdout.printf("making closing regex: %s (%d)\n", dp.end_string, (int) dp.end_string.length);*/
		rx = onig_rx_make1 ("\\\\(\\d+)");
		match = NULL;
		pos = 0;
		src = g_string_new ("");
		found = FALSE;
		_tmp1 = NULL;
		while ((match = (_tmp1 = onig_rx_search (rx, dp->end_string, pos, ((gint) (string_get_length (dp->end_string)))), (match == NULL ? NULL : (match = (g_object_unref (match), NULL))), _tmp1)) != NULL) {
			char* _tmp3;
			char* _tmp2;
			char* _tmp4;
			char* numstr;
			gint num;
			char* _tmp5;
			char* capstr;
			found = TRUE;
			_tmp3 = NULL;
			_tmp2 = NULL;
			g_string_append (src, (_tmp3 = (_tmp2 = g_utf8_offset_to_pointer (dp->end_string, ((glong) (pos))), g_strndup (_tmp2, g_utf8_offset_to_pointer (_tmp2, ((glong) (onig_match_begin (match, 0) - pos))) - _tmp2))));
			_tmp3 = (g_free (_tmp3), NULL);
			_tmp4 = NULL;
			numstr = (_tmp4 = g_utf8_offset_to_pointer (dp->end_string, ((glong) (onig_match_begin (match, 1)))), g_strndup (_tmp4, g_utf8_offset_to_pointer (_tmp4, ((glong) (onig_match_end (match, 1) - onig_match_begin (match, 1)))) - _tmp4));
			num = atoi (numstr);
			/*stdout.printf("capture found: %d\n", num);*/
			_tmp5 = NULL;
			capstr = (_tmp5 = g_utf8_offset_to_pointer (line, ((glong) (onig_match_begin (m->match, num)))), g_strndup (_tmp5, g_utf8_offset_to_pointer (_tmp5, ((glong) (onig_match_end (m->match, num) - onig_match_begin (m->match, num)))) - _tmp5));
			g_string_append (src, capstr);
			pos = onig_match_end (match, 1);
			numstr = (g_free (numstr), NULL);
			capstr = (g_free (capstr), NULL);
		}
		if (found) {
			char* _tmp7;
			char* _tmp6;
			_tmp7 = NULL;
			_tmp6 = NULL;
			g_string_append (src, (_tmp7 = (_tmp6 = g_utf8_offset_to_pointer (dp->end_string, ((glong) (pos))), g_strndup (_tmp6, g_utf8_offset_to_pointer (_tmp6, string_get_length (dp->end_string) - pos) - _tmp6))));
			_tmp7 = (g_free (_tmp7), NULL);
		} else {
			g_string_append (src, dp->end_string);
		}
		/*stdout.printf("src: '%s'\n", src.str);*/
		_tmp8 = NULL;
		scope->closing_regex = (_tmp8 = onig_rx_make1 (src->str), (scope->closing_regex == NULL ? NULL : (scope->closing_regex = (g_object_unref (scope->closing_regex), NULL))), _tmp8);
		(dp == NULL ? NULL : (dp = (g_object_unref (dp), NULL)));
		(rx == NULL ? NULL : (rx = (g_object_unref (rx), NULL)));
		(match == NULL ? NULL : (match = (g_object_unref (match), NULL)));
		(src == NULL ? NULL : (src = (g_string_free (src, TRUE), NULL)));
	}
	return NULL;
}


void gtk_mate_parser_collect_child_captures (GtkMateParser* self, gint line_ix, GtkMateScope* scope, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes) {
	GtkMateScope* s;
	GeeHashMap* captures;
	GeeArrayList* capture_scopes;
	gint best_length;
	gint new_length;
	GeeArrayList* placed_scopes;
	GtkMateScope* parent_scope;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_SCOPE (scope));
	g_return_if_fail (GTK_MATE_IS_MARKER (m));
	g_return_if_fail (GEE_IS_ARRAY_LIST (all_scopes));
	g_return_if_fail (GEE_IS_ARRAY_LIST (closed_scopes));
	s = NULL;
	captures = NULL;
	if (GTK_MATE_IS_SINGLE_PATTERN (m->pattern)) {
		GeeHashMap* _tmp1;
		GeeHashMap* _tmp0;
		_tmp1 = NULL;
		_tmp0 = NULL;
		captures = (_tmp1 = (_tmp0 = (GTK_MATE_SINGLE_PATTERN (m->pattern))->captures, (_tmp0 == NULL ? NULL : g_object_ref (_tmp0))), (captures == NULL ? NULL : (captures = (g_object_unref (captures), NULL))), _tmp1);
	} else {
		if (m->is_close_scope) {
			GeeHashMap* _tmp3;
			GeeHashMap* _tmp2;
			_tmp3 = NULL;
			_tmp2 = NULL;
			captures = (_tmp3 = (_tmp2 = (GTK_MATE_DOUBLE_PATTERN (m->pattern))->end_captures, (_tmp2 == NULL ? NULL : g_object_ref (_tmp2))), (captures == NULL ? NULL : (captures = (g_object_unref (captures), NULL))), _tmp3);
		} else {
			GeeHashMap* _tmp5;
			GeeHashMap* _tmp4;
			_tmp5 = NULL;
			_tmp4 = NULL;
			captures = (_tmp5 = (_tmp4 = (GTK_MATE_DOUBLE_PATTERN (m->pattern))->begin_captures, (_tmp4 == NULL ? NULL : g_object_ref (_tmp4))), (captures == NULL ? NULL : (captures = (g_object_unref (captures), NULL))), _tmp5);
		}
		if ((GTK_MATE_DOUBLE_PATTERN (m->pattern))->both_captures != NULL) {
			GeeHashMap* _tmp7;
			GeeHashMap* _tmp6;
			_tmp7 = NULL;
			_tmp6 = NULL;
			captures = (_tmp7 = (_tmp6 = (GTK_MATE_DOUBLE_PATTERN (m->pattern))->both_captures, (_tmp6 == NULL ? NULL : g_object_ref (_tmp6))), (captures == NULL ? NULL : (captures = (g_object_unref (captures), NULL))), _tmp7);
		}
	}
	capture_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
	/* create capture scopes*/
	if (captures != NULL) {
		{
			GeeSet* cap_collection;
			GeeIterator* cap_it;
			cap_collection = gee_map_get_keys (GEE_MAP (captures));
			cap_it = gee_iterable_iterator (GEE_ITERABLE (cap_collection));
			while (gee_iterator_next (cap_it)) {
				gint cap;
				cap = GPOINTER_TO_INT (gee_iterator_get (cap_it));
				{
					if (onig_match_begin (m->match, cap) != -1) {
						GtkMateScope* _tmp9;
						char* _tmp8;
						GtkMateScope* _tmp11;
						GtkMateScope* _tmp10;
						_tmp9 = NULL;
						_tmp8 = NULL;
						s = (_tmp9 = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, (_tmp8 = ((char*) (gee_map_get (GEE_MAP (captures), GINT_TO_POINTER (cap))))))), (s == NULL ? NULL : (s = (g_object_unref (s), NULL))), _tmp9);
						_tmp8 = (g_free (_tmp8), NULL);
						gtk_mate_scope_start_mark_set (s, line_ix, onig_match_begin (m->match, cap), FALSE);
						gtk_mate_scope_end_mark_set (s, line_ix, onig_match_end (m->match, cap), TRUE);
						s->is_open = FALSE;
						s->is_capture = TRUE;
						_tmp11 = NULL;
						_tmp10 = NULL;
						s->parent = (_tmp11 = (_tmp10 = scope, (_tmp10 == NULL ? NULL : g_object_ref (_tmp10))), (s->parent == NULL ? NULL : (s->parent = (g_object_unref (s->parent), NULL))), _tmp11);
						gee_collection_add (GEE_COLLECTION (capture_scopes), s);
						gee_collection_add (GEE_COLLECTION (all_scopes), s);
						gee_collection_add (GEE_COLLECTION (closed_scopes), s);
					}
				}
			}
			(cap_it == NULL ? NULL : (cap_it = (g_object_unref (cap_it), NULL)));
			(cap_collection == NULL ? NULL : (cap_collection = (g_object_unref (cap_collection), NULL)));
		}
	}
	/* Now we arrange the capture scopes into a tree under the matched
	 scope. We do this by processing the captures in order of offset and 
	 length. For each capture, we check to see if it is a child of an already 
	 placed capture, and if so we add it as a child (we know that the latest 
	 such capture is the one to add it to by the ordering). If not we
	 add it as a child of the matched scope.*/
	best_length = 0;
	new_length = 0;
	placed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
	parent_scope = NULL;
	while (gee_collection_get_size (GEE_COLLECTION (capture_scopes)) > 0) {
		GtkMateScope* _tmp12;
		GtkMateScope* _tmp15;
		_tmp12 = NULL;
		s = (_tmp12 = NULL, (s == NULL ? NULL : (s = (g_object_unref (s), NULL))), _tmp12);
		/* find first and longest remaining scope (put it in 's')*/
		{
			GeeArrayList* cs_collection;
			int cs_it;
			cs_collection = capture_scopes;
			for (cs_it = 0; cs_it < gee_collection_get_size (GEE_COLLECTION (cs_collection)); cs_it = cs_it + 1) {
				GtkMateScope* cs;
				cs = ((GtkMateScope*) (gee_list_get (GEE_LIST (cs_collection), cs_it)));
				{
					new_length = gtk_mate_scope_end_offset (cs) - gtk_mate_scope_start_offset (cs);
					if (s == NULL || (gtk_mate_scope_start_offset (cs) < gtk_mate_scope_start_offset (s) && new_length >= best_length)) {
						GtkMateScope* _tmp14;
						GtkMateScope* _tmp13;
						_tmp14 = NULL;
						_tmp13 = NULL;
						s = (_tmp14 = (_tmp13 = cs, (_tmp13 == NULL ? NULL : g_object_ref (_tmp13))), (s == NULL ? NULL : (s = (g_object_unref (s), NULL))), _tmp14);
						best_length = new_length;
					}
					(cs == NULL ? NULL : (cs = (g_object_unref (cs), NULL)));
				}
			}
		}
		/* look for somewhere to put it from placed_scopes*/
		_tmp15 = NULL;
		parent_scope = (_tmp15 = NULL, (parent_scope == NULL ? NULL : (parent_scope = (g_object_unref (parent_scope), NULL))), _tmp15);
		{
			GeeArrayList* ps_collection;
			int ps_it;
			ps_collection = placed_scopes;
			for (ps_it = 0; ps_it < gee_collection_get_size (GEE_COLLECTION (ps_collection)); ps_it = ps_it + 1) {
				GtkMateScope* ps;
				ps = ((GtkMateScope*) (gee_list_get (GEE_LIST (ps_collection), ps_it)));
				{
					if (gtk_mate_scope_start_offset (s) >= gtk_mate_scope_start_offset (ps) && gtk_mate_scope_end_offset (s) <= gtk_mate_scope_end_offset (ps)) {
						GtkMateScope* _tmp17;
						GtkMateScope* _tmp16;
						_tmp17 = NULL;
						_tmp16 = NULL;
						parent_scope = (_tmp17 = (_tmp16 = ps, (_tmp16 == NULL ? NULL : g_object_ref (_tmp16))), (parent_scope == NULL ? NULL : (parent_scope = (g_object_unref (parent_scope), NULL))), _tmp17);
					}
					(ps == NULL ? NULL : (ps = (g_object_unref (ps), NULL)));
				}
			}
		}
		if (parent_scope != NULL) {
			GtkMateScope* _tmp18;
			GtkMateScope* _tmp20;
			GtkMateScope* _tmp19;
			_tmp18 = NULL;
			g_sequence_append (gtk_mate_scope_get_children (parent_scope), (_tmp18 = s, (_tmp18 == NULL ? NULL : g_object_ref (_tmp18))));
			_tmp20 = NULL;
			_tmp19 = NULL;
			s->parent = (_tmp20 = (_tmp19 = parent_scope, (_tmp19 == NULL ? NULL : g_object_ref (_tmp19))), (s->parent == NULL ? NULL : (s->parent = (g_object_unref (s->parent), NULL))), _tmp20);
		} else {
			GtkMateScope* _tmp21;
			_tmp21 = NULL;
			g_sequence_append (gtk_mate_scope_get_children (scope), (_tmp21 = s, (_tmp21 == NULL ? NULL : g_object_ref (_tmp21))));
		}
		gee_collection_add (GEE_COLLECTION (placed_scopes), s);
		gee_collection_remove (GEE_COLLECTION (capture_scopes), s);
	}
	(s == NULL ? NULL : (s = (g_object_unref (s), NULL)));
	(captures == NULL ? NULL : (captures = (g_object_unref (captures), NULL)));
	(capture_scopes == NULL ? NULL : (capture_scopes = (g_object_unref (capture_scopes), NULL)));
	(placed_scopes == NULL ? NULL : (placed_scopes = (g_object_unref (placed_scopes), NULL)));
	(parent_scope == NULL ? NULL : (parent_scope = (g_object_unref (parent_scope), NULL)));
}


void gtk_mate_parser_reset_table_priorities (GtkMateParser* self) {
	GSequenceIter* _tmp0;
	GSequenceIter* iter;
	gint i;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	/* stdout.printf("\nreset_table_priorities() for %d tags\n", buffer.get_tag_table().get_size());*/
	_tmp0 = NULL;
	iter = (_tmp0 = g_sequence_get_begin_iter (self->tags), (_tmp0 == NULL ? NULL :  (_tmp0)));
	i = 0;
	while (!g_sequence_iter_is_end (g_sequence_iter_next (iter))) {
		GtkTextTag* _tmp1;
		GtkTextTag* t;
		GSequenceIter* _tmp3;
		GSequenceIter* _tmp2;
		_tmp1 = NULL;
		t = (_tmp1 = ((GtkTextTag*) (g_sequence_get (iter))), (_tmp1 == NULL ? NULL : g_object_ref (_tmp1)));
		gtk_text_tag_set_priority (t, i);
		/* stdout.printf("tag: '%s', pri: %d\n", t.name, i);*/
		i++;
		_tmp3 = NULL;
		_tmp2 = NULL;
		iter = (_tmp3 = (_tmp2 = g_sequence_iter_next (iter), (_tmp2 == NULL ? NULL :  (_tmp2))), (iter == NULL ? NULL : (iter = ( (iter), NULL))), _tmp3);
		(t == NULL ? NULL : (t = (g_object_unref (t), NULL)));
	}
	(iter == NULL ? NULL : (iter = ( (iter), NULL)));
}


void gtk_mate_parser_remove_tags (GtkMateParser* self) {
	GSequenceIter* _tmp0;
	GSequenceIter* iter;
	GtkTextTagTable* _tmp1;
	GtkTextTagTable* table;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	_tmp0 = NULL;
	iter = (_tmp0 = g_sequence_get_begin_iter (self->tags), (_tmp0 == NULL ? NULL :  (_tmp0)));
	_tmp1 = NULL;
	table = (_tmp1 = gtk_text_buffer_get_tag_table (GTK_TEXT_BUFFER (self->priv->_buffer)), (_tmp1 == NULL ? NULL : g_object_ref (_tmp1)));
	while (!g_sequence_iter_is_end (iter)) {
		GSequenceIter* _tmp3;
		GSequenceIter* _tmp2;
		gtk_text_tag_table_remove (table, ((GtkTextTag*) (g_sequence_get (iter))));
		_tmp3 = NULL;
		_tmp2 = NULL;
		iter = (_tmp3 = (_tmp2 = g_sequence_iter_next (iter), (_tmp2 == NULL ? NULL :  (_tmp2))), (iter == NULL ? NULL : (iter = ( (iter), NULL))), _tmp3);
	}
	g_sequence_remove_range (g_sequence_get_begin_iter (self->tags), g_sequence_get_end_iter (self->tags));
	(iter == NULL ? NULL : (iter = ( (iter), NULL)));
	(table == NULL ? NULL : (table = (g_object_unref (table), NULL)));
}


void gtk_mate_parser_change_theme (GtkMateParser* self, GtkMateTheme* theme) {
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_THEME (theme));
	/* stdout.printf("parser.change_theme(%s)\n", theme.name);*/
	gtk_mate_colourer_uncolour_scope (self->priv->_colourer, self->root, TRUE);
	gtk_mate_colourer_set_theme (self->priv->_colourer, theme);
	gtk_mate_parser_remove_tags (self);
	gtk_mate_parser_recolour_children (self, self->root);
}


/* stdout.printf("parser.change_theme(%s):out\n", theme.name);*/
void gtk_mate_parser_recolour_children (GtkMateParser* self, GtkMateScope* scope) {
	GSequenceIter* _tmp0;
	GSequenceIter* iter;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_SCOPE (scope));
	_tmp0 = NULL;
	iter = (_tmp0 = g_sequence_get_begin_iter (gtk_mate_scope_get_children (scope)), (_tmp0 == NULL ? NULL :  (_tmp0)));
	while (!g_sequence_iter_is_end (iter)) {
		GtkMateScope* _tmp1;
		GtkMateScope* child;
		GSequenceIter* _tmp3;
		GSequenceIter* _tmp2;
		_tmp1 = NULL;
		child = (_tmp1 = ((GtkMateScope*) (g_sequence_get (iter))), (_tmp1 == NULL ? NULL : g_object_ref (_tmp1)));
		gtk_mate_colourer_colour_scope (self->priv->_colourer, child, FALSE, TRUE);
		if (GTK_MATE_IS_DOUBLE_PATTERN (child->pattern) && (GTK_MATE_DOUBLE_PATTERN (child->pattern))->content_name != NULL) {
			gtk_mate_colourer_colour_scope (self->priv->_colourer, child, TRUE, TRUE);
		}
		gtk_mate_parser_recolour_children (self, child);
		_tmp3 = NULL;
		_tmp2 = NULL;
		iter = (_tmp3 = (_tmp2 = g_sequence_iter_next (iter), (_tmp2 == NULL ? NULL :  (_tmp2))), (iter == NULL ? NULL : (iter = ( (iter), NULL))), _tmp3);
		(child == NULL ? NULL : (child = (g_object_unref (child), NULL)));
	}
	(iter == NULL ? NULL : (iter = ( (iter), NULL)));
}


static void _gtk_mate_parser_insert_text_handler_gtk_text_buffer_insert_text (GtkMateBuffer* _sender, GtkTextIter* pos, const char* text, gint length, gpointer self) {
	gtk_mate_parser_insert_text_handler (self, _sender, pos, text, length);
}


static void _gtk_mate_parser_delete_range_handler_gtk_text_buffer_delete_range (GtkMateBuffer* _sender, GtkTextIter* start, GtkTextIter* end, gpointer self) {
	gtk_mate_parser_delete_range_handler (self, _sender, start, end);
}


void gtk_mate_parser_connect_buffer_signals (GtkMateParser* self) {
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_signal_connect_object (GTK_TEXT_BUFFER (self->priv->_buffer), "insert-text", ((GCallback) (_gtk_mate_parser_insert_text_handler_gtk_text_buffer_insert_text)), self, 0);
	g_signal_connect_object (GTK_TEXT_BUFFER (self->priv->_buffer), "delete-range", ((GCallback) (_gtk_mate_parser_delete_range_handler_gtk_text_buffer_delete_range)), self, 0);
	/* buffer.get_tag_table().tag_added += this.tag_added_handler;
	 remove when signal_connect_after works:*/
	g_signal_connect_after (self->priv->_buffer, "insert_text", ((GCallback) (gtk_mate_parser_static_insert_text_after_handler)), NULL);
	g_signal_connect_after (self->priv->_buffer, "delete_range", ((GCallback) (gtk_mate_parser_static_delete_range_after_handler)), NULL);
}


/* Signal.connect_after(buffer.get_tag_table(), "tag_added", 
  (GLib.Callback) Parser.static_tag_added_after_handler, null);*/
void gtk_mate_parser_insert_text_handler (GtkMateParser* self, GtkMateBuffer* bf, GtkTextIter* pos, const char* text, gint length) {
	char** _tmp0;
	gint ss_length1;
	char** ss;
	gint num_lines;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_BUFFER (bf));
	g_return_if_fail (text != NULL);
	/*//stdout.printf("insert_text(pos, \"%s\", %d)\n", text, length);*/
	_tmp0 = NULL;
	ss = (_tmp0 = g_strsplit (text, "\n", 0), ss_length1 = -1, _tmp0);
	num_lines = -1;
	{
		char** s_collection;
		int s_collection_length1;
		int s_it;
		s_collection = ss;
		s_collection_length1 = ss_length1;
		for (s_it = 0; (ss_length1 != -1 && s_it < ss_length1) || (ss_length1 == -1 && s_collection[s_it] != NULL); s_it = s_it + 1) {
			const char* _tmp1;
			char* s;
			_tmp1 = NULL;
			s = (_tmp1 = s_collection[s_it], (_tmp1 == NULL ? NULL : g_strdup (_tmp1)));
			{
				num_lines++;
				s = (g_free (s), NULL);
			}
		}
	}
	/*//stdout.printf("add_change(%d, %d)\n", pos.get_line(), pos.get_line() + num_lines);*/
	range_set_add (self->changes, gtk_text_iter_get_line (&(*pos)), gtk_text_iter_get_line (&(*pos)) + num_lines);
	ss = (_vala_array_free (ss, ss_length1, ((GDestroyNotify) (g_free))), NULL);
}


void gtk_mate_parser_delete_range_handler (GtkMateParser* self, GtkMateBuffer* bf, GtkTextIter* pos, GtkTextIter* pos2) {
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_BUFFER (bf));
	/*//stdout.printf("delete_range(%d, %d)\n", pos.get_offset(), pos2.get_offset());*/
	range_set_add (self->changes, gtk_text_iter_get_line (&(*pos)), gtk_text_iter_get_line (&(*pos)));
}


void gtk_mate_parser_insert_text_after_handler (GtkMateParser* self, GtkMateBuffer* bf, GtkTextIter* pos, const char* text, gint length) {
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_BUFFER (bf));
	g_return_if_fail (text != NULL);
	if (gtk_mate_parser_is_parsing (self) && !range_set_is_empty (self->changes)) {
		gtk_mate_parser_process_changes (self);
	}
}


void gtk_mate_parser_delete_range_after_handler (GtkMateParser* self, GtkMateBuffer* bf, GtkTextIter* pos, GtkTextIter* pos2) {
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_BUFFER (bf));
	if (gtk_mate_parser_is_parsing (self) && !range_set_is_empty (self->changes)) {
		gtk_mate_parser_process_changes (self);
	}
}


void gtk_mate_parser_static_insert_text_after_handler (GtkMateBuffer* bf, GtkTextIter* pos, const char* text, gint length) {
	g_return_if_fail (GTK_MATE_IS_BUFFER (bf));
	g_return_if_fail (text != NULL);
	{
		GeeArrayList* parser_collection;
		int parser_it;
		parser_collection = gtk_mate_parser_existing_parsers;
		for (parser_it = 0; parser_it < gee_collection_get_size (GEE_COLLECTION (parser_collection)); parser_it = parser_it + 1) {
			GtkMateParser* parser;
			parser = ((GtkMateParser*) (gee_list_get (GEE_LIST (parser_collection), parser_it)));
			{
				gtk_mate_parser_insert_text_after_handler (parser, bf, &(*pos), text, length);
				(parser == NULL ? NULL : (parser = (g_object_unref (parser), NULL)));
			}
		}
	}
}


void gtk_mate_parser_static_delete_range_after_handler (GtkMateBuffer* bf, GtkTextIter* pos, GtkTextIter* pos2) {
	g_return_if_fail (GTK_MATE_IS_BUFFER (bf));
	{
		GeeArrayList* parser_collection;
		int parser_it;
		parser_collection = gtk_mate_parser_existing_parsers;
		for (parser_it = 0; parser_it < gee_collection_get_size (GEE_COLLECTION (parser_collection)); parser_it = parser_it + 1) {
			GtkMateParser* parser;
			parser = ((GtkMateParser*) (gee_list_get (GEE_LIST (parser_collection), parser_it)));
			{
				gtk_mate_parser_delete_range_after_handler (parser, bf, &(*pos), &(*pos2));
				(parser == NULL ? NULL : (parser = (g_object_unref (parser), NULL)));
			}
		}
	}
}


void gtk_mate_parser_added_tag (GtkMateParser* self, GtkTextTag* tag) {
	char* _tmp1;
	char* _tmp0;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_IS_TEXT_TAG (tag));
	_tmp1 = NULL;
	_tmp0 = NULL;
	if ((g_object_get (G_OBJECT (tag), "name", &_tmp0, NULL), _tmp0) != NULL && g_str_has_prefix ((g_object_get (G_OBJECT (tag), "name", &_tmp1, NULL), _tmp1), "gmv(")) {
		GtkTextTag* _tmp2;
		_tmp2 = NULL;
		g_sequence_insert_sorted (self->tags, (_tmp2 = tag, (_tmp2 == NULL ? NULL : g_object_ref (_tmp2))), ((GCompareDataFunc) (gtk_mate_parser_tag_compare)), NULL);
	}
	gtk_mate_parser_reset_table_priorities (self);
}


/* public static void static_tag_added_after_handler(TextTagTable tt, TextTag tag) {
 foreach(var parser in existing_parsers) {
 if (parser.tag_added && tag.name != null && tag.name.has_prefix("gmv(")) {
 parser.tags.insert_sorted(tag, (CompareDataFunc) Parser.tag_compare);
 }
 parser.reset_table_priorities();
 parser.tag_added = false;
 }
 }*/
gint gtk_mate_parser_tag_compare (GtkTextTag* tag1, GtkTextTag* tag2, void* data) {
	char* _tmp0;
	gint pri1;
	char* _tmp1;
	gint pri2;
	g_return_val_if_fail (GTK_IS_TEXT_TAG (tag1), 0);
	g_return_val_if_fail (GTK_IS_TEXT_TAG (tag2), 0);
	_tmp0 = NULL;
	pri1 = g_unichar_digit_value (g_utf8_get_char (g_utf8_offset_to_pointer ((g_object_get (G_OBJECT (tag1), "name", &_tmp0, NULL), _tmp0), 4)));
	_tmp1 = NULL;
	pri2 = g_unichar_digit_value (g_utf8_get_char (g_utf8_offset_to_pointer ((g_object_get (G_OBJECT (tag2), "name", &_tmp1, NULL), _tmp1), 4)));
	if (pri1 > pri2) {
		return 1;
	} else {
		if (pri2 > pri1) {
			return -1;
		}
	}
	return 0;
}


void gtk_mate_parser_close (GtkMateParser* self) {
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	gee_collection_remove (GEE_COLLECTION (gtk_mate_parser_existing_parsers), self);
}


GtkMateParser* gtk_mate_parser_create (GtkMateGrammar* grammar, GtkMateBuffer* buffer) {
	GtkMateParser* p;
	GSequence* _tmp1;
	RangeSet* _tmp2;
	GtkMateColourer* _tmp3;
	g_return_val_if_fail (GTK_MATE_IS_GRAMMAR (grammar), NULL);
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (buffer), NULL);
	gtk_mate_grammar_init_for_use (grammar);
	p = g_object_ref_sink (gtk_mate_parser_new ());
	/*//stdout.printf("grammar: %s\n", grammar.name); 
	 remove when signal_connect_after works:*/
	if (gtk_mate_parser_existing_parsers == NULL) {
		GeeArrayList* _tmp0;
		_tmp0 = NULL;
		gtk_mate_parser_existing_parsers = (_tmp0 = gee_array_list_new (GTK_MATE_TYPE_PARSER, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal), (gtk_mate_parser_existing_parsers == NULL ? NULL : (gtk_mate_parser_existing_parsers = (g_object_unref (gtk_mate_parser_existing_parsers), NULL))), _tmp0);
	}
	gee_collection_add (GEE_COLLECTION (gtk_mate_parser_existing_parsers), p);
	gtk_mate_parser_set_grammar (p, grammar);
	gtk_mate_parser_set_buffer (p, buffer);
	_tmp1 = NULL;
	p->tags = (_tmp1 = g_sequence_new (NULL), (p->tags == NULL ? NULL : (p->tags = (g_sequence_free (p->tags), NULL))), _tmp1);
	_tmp2 = NULL;
	p->changes = (_tmp2 = range_set_new (), (p->changes == NULL ? NULL : (p->changes = (g_object_unref (p->changes), NULL))), _tmp2);
	_tmp3 = NULL;
	gtk_mate_parser_set_colourer (p, (_tmp3 = g_object_ref_sink (gtk_mate_colourer_new (buffer))));
	(_tmp3 == NULL ? NULL : (_tmp3 = (g_object_unref (_tmp3), NULL)));
	p->deactivation_level = 0;
	gtk_mate_parser_make_root (p);
	gtk_mate_parser_connect_buffer_signals (p);
	/* // required to stop GTK crashing on reset_table_priorities
	 p.dummy_tag = buffer.create_tag("dummy tag");
	 p.dummy_tag2 = buffer.create_tag("dummy tag2");*/
	return p;
}


GtkMateParser* gtk_mate_parser_new (void) {
	GtkMateParser * self;
	self = g_object_newv (GTK_MATE_TYPE_PARSER, 0, NULL);
	return self;
}


GtkMateGrammar* gtk_mate_parser_get_grammar (GtkMateParser* self) {
	g_return_val_if_fail (GTK_MATE_IS_PARSER (self), NULL);
	return self->priv->_grammar;
}


void gtk_mate_parser_set_grammar (GtkMateParser* self, GtkMateGrammar* value) {
	GtkMateGrammar* _tmp2;
	GtkMateGrammar* _tmp1;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_grammar = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (self->priv->_grammar == NULL ? NULL : (self->priv->_grammar = (g_object_unref (self->priv->_grammar), NULL))), _tmp2);
	g_object_notify (((GObject *) (self)), "grammar");
}


GtkMateColourer* gtk_mate_parser_get_colourer (GtkMateParser* self) {
	g_return_val_if_fail (GTK_MATE_IS_PARSER (self), NULL);
	return self->priv->_colourer;
}


void gtk_mate_parser_set_colourer (GtkMateParser* self, GtkMateColourer* value) {
	GtkMateColourer* _tmp2;
	GtkMateColourer* _tmp1;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_colourer = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (self->priv->_colourer == NULL ? NULL : (self->priv->_colourer = (g_object_unref (self->priv->_colourer), NULL))), _tmp2);
	g_object_notify (((GObject *) (self)), "colourer");
}


GtkMateBuffer* gtk_mate_parser_get_buffer (GtkMateParser* self) {
	g_return_val_if_fail (GTK_MATE_IS_PARSER (self), NULL);
	return self->priv->_buffer;
}


void gtk_mate_parser_set_buffer (GtkMateParser* self, GtkMateBuffer* value) {
	GtkMateBuffer* _tmp2;
	GtkMateBuffer* _tmp1;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_buffer = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (self->priv->_buffer == NULL ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL))), _tmp2);
	g_object_notify (((GObject *) (self)), "buffer");
}


static void gtk_mate_parser_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateParser * self;
	self = GTK_MATE_PARSER (object);
	switch (property_id) {
		case GTK_MATE_PARSER_GRAMMAR:
		g_value_set_object (value, gtk_mate_parser_get_grammar (self));
		break;
		case GTK_MATE_PARSER_COLOURER:
		g_value_set_object (value, gtk_mate_parser_get_colourer (self));
		break;
		case GTK_MATE_PARSER_BUFFER:
		g_value_set_object (value, gtk_mate_parser_get_buffer (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_parser_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GtkMateParser * self;
	self = GTK_MATE_PARSER (object);
	switch (property_id) {
		case GTK_MATE_PARSER_GRAMMAR:
		gtk_mate_parser_set_grammar (self, g_value_get_object (value));
		break;
		case GTK_MATE_PARSER_COLOURER:
		gtk_mate_parser_set_colourer (self, g_value_get_object (value));
		break;
		case GTK_MATE_PARSER_BUFFER:
		gtk_mate_parser_set_buffer (self, g_value_get_object (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_parser_class_init (GtkMateParserClass * klass) {
	gtk_mate_parser_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GtkMateParserPrivate));
	G_OBJECT_CLASS (klass)->get_property = gtk_mate_parser_get_property;
	G_OBJECT_CLASS (klass)->set_property = gtk_mate_parser_set_property;
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_parser_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_PARSER_GRAMMAR, g_param_spec_object ("grammar", "grammar", "grammar", GTK_MATE_TYPE_GRAMMAR, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_PARSER_COLOURER, g_param_spec_object ("colourer", "colourer", "colourer", GTK_MATE_TYPE_COLOURER, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_PARSER_BUFFER, g_param_spec_object ("buffer", "buffer", "buffer", GTK_MATE_TYPE_BUFFER, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void gtk_mate_parser_instance_init (GtkMateParser * self) {
	self->priv = GTK_MATE_PARSER_GET_PRIVATE (self);
}


static void gtk_mate_parser_finalize (GObject * obj) {
	GtkMateParser * self;
	self = GTK_MATE_PARSER (obj);
	(self->priv->_grammar == NULL ? NULL : (self->priv->_grammar = (g_object_unref (self->priv->_grammar), NULL)));
	(self->priv->_colourer == NULL ? NULL : (self->priv->_colourer = (g_object_unref (self->priv->_colourer), NULL)));
	(self->priv->_buffer == NULL ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL)));
	(self->root == NULL ? NULL : (self->root = (g_object_unref (self->root), NULL)));
	(self->changes == NULL ? NULL : (self->changes = (g_object_unref (self->changes), NULL)));
	(self->dummy_tag == NULL ? NULL : (self->dummy_tag = (g_object_unref (self->dummy_tag), NULL)));
	(self->dummy_tag2 == NULL ? NULL : (self->dummy_tag2 = (g_object_unref (self->dummy_tag2), NULL)));
	(self->tags == NULL ? NULL : (self->tags = (g_sequence_free (self->tags), NULL)));
	G_OBJECT_CLASS (gtk_mate_parser_parent_class)->finalize (obj);
}


GType gtk_mate_parser_get_type (void) {
	static GType gtk_mate_parser_type_id = 0;
	if (gtk_mate_parser_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateParserClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_parser_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateParser), 0, (GInstanceInitFunc) gtk_mate_parser_instance_init };
		gtk_mate_parser_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateParser", &g_define_type_info, 0);
	}
	return gtk_mate_parser_type_id;
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


static int _vala_strcmp0 (const char * str1, const char * str2) {
	if (str1 == NULL) {
		return -(str1 != str2);
	}
	if (str2 == NULL) {
		return (str1 != str2);
	}
	return strcmp (str1, str2);
}




