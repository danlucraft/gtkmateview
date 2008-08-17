
#include "parser.h"
#include <gee/collection.h>
#include <stdio.h>
#include <gee/hashmap.h>
#include <gee/arraylist.h>
#include <gee/map.h>
#include "buffer.h"
#include "pattern.h"
#include "scanner.h"
#include <string.h>




struct _GtkMateParserPrivate {
	GtkMateGrammar* _grammar;
	GtkMateBuffer* _buffer;
};

#define GTK_MATE_PARSER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_TYPE_PARSER, GtkMateParserPrivate))
enum  {
	GTK_MATE_PARSER_DUMMY_PROPERTY,
	GTK_MATE_PARSER_GRAMMAR,
	GTK_MATE_PARSER_BUFFER
};
GtkMateParser* gtk_mate_parser_current = NULL;
static void gtk_mate_parser_process_changes (GtkMateParser* self);
static gint gtk_mate_parser_parse_range (GtkMateParser* self, gint from_line, gint to_line);
static gboolean gtk_mate_parser_parse_line (GtkMateParser* self, gint line_ix);
static void _gtk_mate_parser_insert_text_handler_gtk_text_buffer_insert_text (GtkMateBuffer* _sender, GtkTextIter* pos, const char* text, gint length, gpointer self);
static void _gtk_mate_parser_delete_range_handler_gtk_text_buffer_delete_range (GtkMateBuffer* _sender, GtkTextIter* start, GtkTextIter* end, gpointer self);
static gpointer gtk_mate_parser_parent_class = NULL;
static void gtk_mate_parser_finalize (GObject * obj);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);



GtkMateTextLoc gtk_mate_text_loc_make (gint l, gint lo) {
	GtkMateTextLoc _tmp0 = {0};
	GtkMateTextLoc tl;
	tl = (memset (&_tmp0, 0, sizeof (GtkMateTextLoc)), _tmp0);
	tl.line = l;
	tl.line_offset = lo;
	return tl;
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
	gee_collection_clear (GEE_COLLECTION (self->changes->ranges));
}


/* Parse from from_line to *at least* to_line. Will parse
 more if necessary. Returns the index of the last line
 parsed.*/
static gint gtk_mate_parser_parse_range (GtkMateParser* self, gint from_line, gint to_line) {
	gint line_ix;
	gboolean scope_changed;
	g_return_val_if_fail (GTK_MATE_IS_PARSER (self), 0);
	/*stdout.printf("parse_from(%d, %d)\n", from_line, to_line);*/
	line_ix = from_line;
	scope_changed = FALSE;
	while (line_ix <= to_line || scope_changed) {
		scope_changed = gtk_mate_parser_parse_line (self, line_ix++);
	}
	return to_line;
}


/* Parse line line_ix. Returns whether or not the ending
 scope of the line has changed.*/
static gboolean gtk_mate_parser_parse_line (GtkMateParser* self, gint line_ix) {
	char* line;
	gint length;
	char* _tmp1;
	char* _tmp0;
	GtkMateScanner* scanner;
	gint i;
	GtkMateScope* s;
	gboolean _tmp19;
	g_return_val_if_fail (GTK_MATE_IS_PARSER (self), FALSE);
	line = gtk_mate_buffer_get_line (self->priv->_buffer, line_ix);
	length = gtk_mate_buffer_get_line_length (self->priv->_buffer, line_ix);
	_tmp1 = NULL;
	_tmp0 = NULL;
	fprintf (stdout, "parse line: %d (%d): '%s'\n", line_ix, length, (_tmp1 = (_tmp0 = g_utf8_offset_to_pointer (line, ((glong) (0))), g_strndup (_tmp0, g_utf8_offset_to_pointer (_tmp0, ((glong) (length))) - _tmp0))));
	_tmp1 = (g_free (_tmp1), NULL);
	scanner = g_object_ref_sink (gtk_mate_scanner_new (self->root, line, length));
	i = 0;
	s = NULL;
	{
		GtkMateScanner* m_collection;
		GeeIterator* m_it;
		m_collection = scanner;
		m_it = gee_iterable_iterator (GEE_ITERABLE (m_collection));
		while (gee_iterator_next (m_it)) {
			GtkMateMarker* m;
			m = ((GtkMateMarker*) (gee_iterator_get (m_it)));
			{
				char* _tmp18;
				if (m->is_close_scope) {
					fprintf (stdout, "closing scope at %d\n", m->from);
					gtk_mate_scope_inner_end_mark_set (gtk_mate_scanner_get_current_scope (scanner), line_ix, m->from, TRUE);
					gtk_mate_scope_end_mark_set (gtk_mate_scanner_get_current_scope (scanner), line_ix, oniguruma_match_end (m->match, 0), TRUE);
					gtk_mate_scanner_get_current_scope (scanner)->is_open = FALSE;
					gtk_mate_scanner_set_current_scope (scanner, gtk_mate_scanner_get_current_scope (scanner)->parent);
				} else {
					if (GTK_MATE_IS_DOUBLE_PATTERN (m->pattern)) {
						GtkMateScope* _tmp2;
						GtkMatePattern* _tmp4;
						GtkMatePattern* _tmp3;
						OnigurumaMatch* _tmp6;
						OnigurumaMatch* _tmp5;
						GtkTextIter end_iter;
						gint end_line;
						gint end_line_offset;
						GtkMateScope* _tmp7;
						GtkMateScope* _tmp9;
						GtkMateScope* _tmp8;
						fprintf (stdout, "[opening with %d patterns], \n", gee_collection_get_size (GEE_COLLECTION ((GTK_MATE_DOUBLE_PATTERN (m->pattern))->patterns)));
						_tmp2 = NULL;
						s = (_tmp2 = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, m->pattern->name)), (s == NULL ? NULL : (s = (g_object_unref (s), NULL))), _tmp2);
						_tmp4 = NULL;
						_tmp3 = NULL;
						s->pattern = (_tmp4 = (_tmp3 = m->pattern, (_tmp3 == NULL ? NULL : g_object_ref (_tmp3))), (s->pattern == NULL ? NULL : (s->pattern = (g_object_unref (s->pattern), NULL))), _tmp4);
						_tmp6 = NULL;
						_tmp5 = NULL;
						s->open_match = (_tmp6 = (_tmp5 = m->match, (_tmp5 == NULL ? NULL : g_object_ref (_tmp5))), (s->open_match == NULL ? NULL : (s->open_match = (g_object_unref (s->open_match), NULL))), _tmp6);
						gtk_mate_scope_start_mark_set (s, line_ix, m->from, FALSE);
						gtk_mate_scope_inner_start_mark_set (s, line_ix, MIN (oniguruma_match_end (m->match, 0), length), FALSE);
						end_iter = gtk_mate_buffer_end_iter (self->priv->_buffer);
						end_line = gtk_text_iter_get_line (&end_iter);
						end_line_offset = gtk_text_iter_get_line_offset (&end_iter);
						gtk_mate_scope_inner_end_mark_set (s, end_line, end_line_offset, FALSE);
						gtk_mate_scope_end_mark_set (s, end_line, end_line_offset, FALSE);
						s->is_open = TRUE;
						_tmp7 = NULL;
						g_sequence_append (gtk_mate_scope_get_children (gtk_mate_scanner_get_current_scope (scanner)), (_tmp7 = s, (_tmp7 == NULL ? NULL : g_object_ref (_tmp7))));
						_tmp9 = NULL;
						_tmp8 = NULL;
						s->parent = (_tmp9 = (_tmp8 = gtk_mate_scanner_get_current_scope (scanner), (_tmp8 == NULL ? NULL : g_object_ref (_tmp8))), (s->parent == NULL ? NULL : (s->parent = (g_object_unref (s->parent), NULL))), _tmp9);
						gtk_mate_scanner_set_current_scope (scanner, s);
					} else {
						GtkMateScope* _tmp10;
						GtkMatePattern* _tmp12;
						GtkMatePattern* _tmp11;
						OnigurumaMatch* _tmp14;
						OnigurumaMatch* _tmp13;
						GtkMateScope* _tmp16;
						GtkMateScope* _tmp15;
						GtkMateScope* _tmp17;
						_tmp10 = NULL;
						s = (_tmp10 = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, m->pattern->name)), (s == NULL ? NULL : (s = (g_object_unref (s), NULL))), _tmp10);
						_tmp12 = NULL;
						_tmp11 = NULL;
						s->pattern = (_tmp12 = (_tmp11 = m->pattern, (_tmp11 == NULL ? NULL : g_object_ref (_tmp11))), (s->pattern == NULL ? NULL : (s->pattern = (g_object_unref (s->pattern), NULL))), _tmp12);
						_tmp14 = NULL;
						_tmp13 = NULL;
						s->open_match = (_tmp14 = (_tmp13 = m->match, (_tmp13 == NULL ? NULL : g_object_ref (_tmp13))), (s->open_match == NULL ? NULL : (s->open_match = (g_object_unref (s->open_match), NULL))), _tmp14);
						gtk_mate_scope_start_mark_set (s, line_ix, m->from, FALSE);
						gtk_mate_scope_end_mark_set (s, line_ix, MIN (oniguruma_match_end (m->match, 0), length), TRUE);
						s->is_open = FALSE;
						_tmp16 = NULL;
						_tmp15 = NULL;
						s->parent = (_tmp16 = (_tmp15 = gtk_mate_scanner_get_current_scope (scanner), (_tmp15 == NULL ? NULL : g_object_ref (_tmp15))), (s->parent == NULL ? NULL : (s->parent = (g_object_unref (s->parent), NULL))), _tmp16);
						_tmp17 = NULL;
						g_sequence_append (gtk_mate_scope_get_children (gtk_mate_scanner_get_current_scope (scanner)), (_tmp17 = s, (_tmp17 == NULL ? NULL : g_object_ref (_tmp17))));
					}
				}
				gtk_mate_parser_handle_captures (self, line_ix, s, m);
				_tmp18 = NULL;
				fprintf (stdout, "pretty: %s\n", (_tmp18 = gtk_mate_scope_pretty (s, 0)));
				_tmp18 = (g_free (_tmp18), NULL);
				scanner->position = oniguruma_match_end (m->match, 0);
				(m == NULL ? NULL : (m = (g_object_unref (m), NULL)));
			}
		}
		(m_it == NULL ? NULL : (m_it = (g_object_unref (m_it), NULL)));
	}
	return (_tmp19 = FALSE, (line = (g_free (line), NULL)), (scanner == NULL ? NULL : (scanner = (g_object_unref (scanner), NULL))), (s == NULL ? NULL : (s = (g_object_unref (s), NULL))), _tmp19);
}


/* Opens scopes for captures AND creates closing regexp from
 captures if necessary.*/
void gtk_mate_parser_handle_captures (GtkMateParser* self, gint line_ix, GtkMateScope* scope, GtkMateMarker* m) {
	OnigurumaRegex* _tmp0;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_SCOPE (scope));
	g_return_if_fail (GTK_MATE_IS_MARKER (m));
	_tmp0 = NULL;
	_tmp0 = gtk_mate_parser_make_closing_regex (self, scope, m);
	(_tmp0 == NULL ? NULL : (_tmp0 = (g_object_unref (_tmp0), NULL)));
	gtk_mate_parser_collect_child_captures (self, line_ix, scope, m);
}


OnigurumaRegex* gtk_mate_parser_make_closing_regex (GtkMateParser* self, GtkMateScope* scope, GtkMateMarker* m) {
	g_return_val_if_fail (GTK_MATE_IS_PARSER (self), NULL);
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (scope), NULL);
	g_return_val_if_fail (GTK_MATE_IS_MARKER (m), NULL);
	/* new_end = pattern.end.gsub(/\\([0-9]+)/) do
	 md.captures.send(:[], $1.to_i-1)
	 end*/
	if (GTK_MATE_IS_DOUBLE_PATTERN (m->pattern)) {
		GtkMateDoublePattern* _tmp0;
		GtkMateDoublePattern* dp;
		OnigurumaRegex* _tmp1;
		_tmp0 = NULL;
		dp = (_tmp0 = GTK_MATE_DOUBLE_PATTERN (m->pattern), (_tmp0 == NULL ? NULL : g_object_ref (_tmp0)));
		fprintf (stdout, "making closing regex: %s\n", dp->end_string);
		_tmp1 = NULL;
		scope->closing_regex = (_tmp1 = oniguruma_regex_make1 (dp->end_string), (scope->closing_regex == NULL ? NULL : (scope->closing_regex = (g_object_unref (scope->closing_regex), NULL))), _tmp1);
		(dp == NULL ? NULL : (dp = (g_object_unref (dp), NULL)));
	}
	return NULL;
}


void gtk_mate_parser_collect_child_captures (GtkMateParser* self, gint line_ix, GtkMateScope* scope, GtkMateMarker* m) {
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
	}
	capture_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
	/* create capture scopes*/
	{
		GeeSet* cap_collection;
		GeeIterator* cap_it;
		cap_collection = gee_map_get_keys (GEE_MAP (captures));
		cap_it = gee_iterable_iterator (GEE_ITERABLE (cap_collection));
		while (gee_iterator_next (cap_it)) {
			gint cap;
			cap = GPOINTER_TO_INT (gee_iterator_get (cap_it));
			{
				if (oniguruma_match_begin (m->match, cap) != -1) {
					GtkMateScope* _tmp7;
					char* _tmp6;
					_tmp7 = NULL;
					_tmp6 = NULL;
					s = (_tmp7 = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, (_tmp6 = ((char*) (gee_map_get (GEE_MAP (captures), GINT_TO_POINTER (cap))))))), (s == NULL ? NULL : (s = (g_object_unref (s), NULL))), _tmp7);
					_tmp6 = (g_free (_tmp6), NULL);
					gtk_mate_scope_start_mark_set (s, line_ix, oniguruma_match_begin (m->match, cap), FALSE);
					gtk_mate_scope_end_mark_set (s, line_ix, oniguruma_match_end (m->match, cap), TRUE);
					s->is_open = FALSE;
					gee_collection_add (GEE_COLLECTION (capture_scopes), s);
				}
			}
		}
		(cap_it == NULL ? NULL : (cap_it = (g_object_unref (cap_it), NULL)));
		(cap_collection == NULL ? NULL : (cap_collection = (g_object_unref (cap_collection), NULL)));
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
		GtkMateScope* _tmp8;
		GtkMateScope* _tmp11;
		_tmp8 = NULL;
		s = (_tmp8 = NULL, (s == NULL ? NULL : (s = (g_object_unref (s), NULL))), _tmp8);
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
						GtkMateScope* _tmp10;
						GtkMateScope* _tmp9;
						_tmp10 = NULL;
						_tmp9 = NULL;
						s = (_tmp10 = (_tmp9 = cs, (_tmp9 == NULL ? NULL : g_object_ref (_tmp9))), (s == NULL ? NULL : (s = (g_object_unref (s), NULL))), _tmp10);
						best_length = new_length;
					}
					(cs == NULL ? NULL : (cs = (g_object_unref (cs), NULL)));
				}
			}
		}
		/* look for somewhere to put it from placed_scopes*/
		_tmp11 = NULL;
		parent_scope = (_tmp11 = NULL, (parent_scope == NULL ? NULL : (parent_scope = (g_object_unref (parent_scope), NULL))), _tmp11);
		{
			GeeArrayList* ps_collection;
			int ps_it;
			ps_collection = placed_scopes;
			for (ps_it = 0; ps_it < gee_collection_get_size (GEE_COLLECTION (ps_collection)); ps_it = ps_it + 1) {
				GtkMateScope* ps;
				ps = ((GtkMateScope*) (gee_list_get (GEE_LIST (ps_collection), ps_it)));
				{
					if (gtk_mate_scope_start_offset (s) >= gtk_mate_scope_start_offset (ps) && gtk_mate_scope_end_offset (s) <= gtk_mate_scope_end_offset (ps)) {
						GtkMateScope* _tmp13;
						GtkMateScope* _tmp12;
						_tmp13 = NULL;
						_tmp12 = NULL;
						parent_scope = (_tmp13 = (_tmp12 = ps, (_tmp12 == NULL ? NULL : g_object_ref (_tmp12))), (parent_scope == NULL ? NULL : (parent_scope = (g_object_unref (parent_scope), NULL))), _tmp13);
					}
					(ps == NULL ? NULL : (ps = (g_object_unref (ps), NULL)));
				}
			}
		}
		if (parent_scope != NULL) {
			GtkMateScope* _tmp14;
			_tmp14 = NULL;
			g_sequence_append (gtk_mate_scope_get_children (parent_scope), (_tmp14 = s, (_tmp14 == NULL ? NULL : g_object_ref (_tmp14))));
		} else {
			GtkMateScope* _tmp15;
			_tmp15 = NULL;
			g_sequence_append (gtk_mate_scope_get_children (scope), (_tmp15 = s, (_tmp15 == NULL ? NULL : g_object_ref (_tmp15))));
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
	/* remove when signal_connect_after works:*/
	g_signal_connect_after (self->priv->_buffer, "insert_text", ((GCallback) (gtk_mate_parser_static_insert_text_after_handler)), NULL);
	g_signal_connect_after (self->priv->_buffer, "delete_range", ((GCallback) (gtk_mate_parser_static_delete_range_after_handler)), NULL);
}


void gtk_mate_parser_insert_text_handler (GtkMateParser* self, GtkMateBuffer* bf, GtkTextIter* pos, const char* text, gint length) {
	char** _tmp0;
	gint ss_length1;
	char** ss;
	gint num_lines;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_BUFFER (bf));
	g_return_if_fail (text != NULL);
	/*stdout.printf("insert_text(pos, \"%s\", %d)\n", text, length);*/
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
	/*stdout.printf("add_change(%d, %d)\n", pos.get_line(), pos.get_line() + num_lines);*/
	range_set_add (self->changes, gtk_text_iter_get_line (&(*pos)), gtk_text_iter_get_line (&(*pos)) + num_lines);
	ss = (_vala_array_free (ss, ss_length1, ((GDestroyNotify) (g_free))), NULL);
}


void gtk_mate_parser_delete_range_handler (GtkMateParser* self, GtkMateBuffer* bf, GtkTextIter* pos, GtkTextIter* pos2) {
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_BUFFER (bf));
	/*stdout.printf("delete_range(%d, %d)\n", pos.get_offset(), pos2.get_offset());*/
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
	gtk_mate_parser_insert_text_after_handler (gtk_mate_parser_current, bf, &(*pos), text, length);
}


void gtk_mate_parser_static_delete_range_after_handler (GtkMateBuffer* bf, GtkTextIter* pos, GtkTextIter* pos2) {
	g_return_if_fail (GTK_MATE_IS_BUFFER (bf));
	gtk_mate_parser_delete_range_after_handler (gtk_mate_parser_current, bf, &(*pos), &(*pos2));
}


GtkMateParser* gtk_mate_parser_create (GtkMateGrammar* grammar, GtkMateBuffer* buffer) {
	GtkMateParser* p;
	RangeSet* _tmp0;
	GtkMateParser* _tmp2;
	GtkMateParser* _tmp1;
	g_return_val_if_fail (GTK_MATE_IS_GRAMMAR (grammar), NULL);
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (buffer), NULL);
	gtk_mate_grammar_init_for_use (grammar);
	p = g_object_ref_sink (gtk_mate_parser_new ());
	/*stdout.printf("grammar: %s\n", grammar.name);*/
	gtk_mate_parser_set_grammar (p, grammar);
	gtk_mate_parser_set_buffer (p, buffer);
	_tmp0 = NULL;
	p->changes = (_tmp0 = range_set_new (), (p->changes == NULL ? NULL : (p->changes = (g_object_unref (p->changes), NULL))), _tmp0);
	p->deactivation_level = 0;
	gtk_mate_parser_make_root (p);
	gtk_mate_parser_connect_buffer_signals (p);
	_tmp2 = NULL;
	_tmp1 = NULL;
	gtk_mate_parser_current = (_tmp2 = (_tmp1 = p, (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (gtk_mate_parser_current == NULL ? NULL : (gtk_mate_parser_current = (g_object_unref (gtk_mate_parser_current), NULL))), _tmp2);
	/* remove when signal_connect_after works*/
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
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_PARSER_BUFFER, g_param_spec_object ("buffer", "buffer", "buffer", GTK_MATE_TYPE_BUFFER, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void gtk_mate_parser_instance_init (GtkMateParser * self) {
	self->priv = GTK_MATE_PARSER_GET_PRIVATE (self);
}


static void gtk_mate_parser_finalize (GObject * obj) {
	GtkMateParser * self;
	self = GTK_MATE_PARSER (obj);
	(self->priv->_grammar == NULL ? NULL : (self->priv->_grammar = (g_object_unref (self->priv->_grammar), NULL)));
	(self->priv->_buffer == NULL ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL)));
	(self->root == NULL ? NULL : (self->root = (g_object_unref (self->root), NULL)));
	(self->changes == NULL ? NULL : (self->changes = (g_object_unref (self->changes), NULL)));
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




