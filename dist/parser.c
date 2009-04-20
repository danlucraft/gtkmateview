
#include "parser.h"
#include <gee/collection.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/hashmap.h>
#include <gee/map.h>
#include "theme.h"
#include "colourer.h"
#include "scope.h"
#include "pattern.h"




static glong string_get_length (const char* self);
static char* string_substring (const char* self, glong offset, glong len);
enum  {
	GTK_MATE_TEXT_LOC_DUMMY_PROPERTY
};
static gpointer gtk_mate_text_loc_parent_class = NULL;
static void gtk_mate_text_loc_finalize (GObject* obj);
struct _GtkMateParserPrivate {
	GtkMateGrammar* _grammar;
	GtkMateColourer* _colourer;
	GtkMateBuffer* _buffer;
	gint _look_ahead;
};

#define GTK_MATE_PARSER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_TYPE_PARSER, GtkMateParserPrivate))
enum  {
	GTK_MATE_PARSER_DUMMY_PROPERTY,
	GTK_MATE_PARSER_GRAMMAR,
	GTK_MATE_PARSER_COLOURER,
	GTK_MATE_PARSER_BUFFER,
	GTK_MATE_PARSER_LOOK_AHEAD
};
GeeArrayList* gtk_mate_parser_existing_parsers = NULL;
static void gtk_mate_parser_process_changes (GtkMateParser* self);
static gint gtk_mate_parser_parse_range (GtkMateParser* self, gint from_line, gint to_line);
static void gtk_mate_parser_remove_colour_after (GtkMateParser* self, gint line_ix, gint line_offset);
static gboolean gtk_mate_parser_parse_line (GtkMateParser* self, gint line_ix);
static void _gtk_mate_parser_insert_text_handler_gtk_text_buffer_insert_text (GtkMateBuffer* _sender, const GtkTextIter* pos, const char* text, gint length, gpointer self);
static void _gtk_mate_parser_delete_range_handler_gtk_text_buffer_delete_range (GtkMateBuffer* _sender, const GtkTextIter* start, const GtkTextIter* end, gpointer self);
static gpointer gtk_mate_parser_parent_class = NULL;
static void gtk_mate_parser_finalize (GObject* obj);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static gint _vala_array_length (gpointer array);
static int _vala_strcmp0 (const char * str1, const char * str2);



static glong string_get_length (const char* self) {
	g_return_val_if_fail (self != NULL, 0L);
	return g_utf8_strlen (self, -1);
}


static char* string_substring (const char* self, glong offset, glong len) {
	glong string_length;
	const char* start;
	g_return_val_if_fail (self != NULL, NULL);
	string_length = g_utf8_strlen (self, -1);
	if (offset < 0) {
		offset = string_length + offset;
		g_return_val_if_fail (offset >= 0, NULL);
	} else {
		g_return_val_if_fail (offset <= string_length, NULL);
	}
	if (len < 0) {
		len = string_length - offset;
	}
	g_return_val_if_fail ((offset + len) <= string_length, NULL);
	start = g_utf8_offset_to_pointer (self, offset);
	return g_strndup (start, ((gchar*) g_utf8_offset_to_pointer (start, len)) - ((gchar*) start));
}


GtkMateTextLoc* gtk_mate_text_loc_make (gint l, gint lo) {
	GtkMateTextLoc* tl;
	tl = g_object_ref_sink (gtk_mate_text_loc_new ());
	tl->line = l;
	tl->line_offset = lo;
	return tl;
}


gboolean gtk_mate_text_loc_equal (GtkMateTextLoc* t1, GtkMateTextLoc* t2) {
	gboolean _tmp0;
	g_return_val_if_fail (t1 != NULL, FALSE);
	g_return_val_if_fail (t2 != NULL, FALSE);
	_tmp0 = FALSE;
	if (t1->line == t2->line) {
		_tmp0 = t1->line_offset == t2->line_offset;
	} else {
		_tmp0 = FALSE;
	}
	return _tmp0;
}


gboolean gtk_mate_text_loc_gt (GtkMateTextLoc* t1, GtkMateTextLoc* t2) {
	gboolean _tmp0;
	g_return_val_if_fail (t1 != NULL, FALSE);
	g_return_val_if_fail (t2 != NULL, FALSE);
	_tmp0 = FALSE;
	if (t1->line > t2->line) {
		_tmp0 = TRUE;
	} else {
		gboolean _tmp1;
		_tmp1 = FALSE;
		if (t1->line >= t2->line) {
			_tmp1 = t1->line_offset > t2->line_offset;
		} else {
			_tmp1 = FALSE;
		}
		_tmp0 = _tmp1;
	}
	return _tmp0;
}


gboolean gtk_mate_text_loc_lt (GtkMateTextLoc* t1, GtkMateTextLoc* t2) {
	gboolean _tmp0;
	g_return_val_if_fail (t1 != NULL, FALSE);
	g_return_val_if_fail (t2 != NULL, FALSE);
	_tmp0 = FALSE;
	if (!gtk_mate_text_loc_equal (t1, t2)) {
		_tmp0 = !gtk_mate_text_loc_gt (t1, t2);
	} else {
		_tmp0 = FALSE;
	}
	return _tmp0;
}


gboolean gtk_mate_text_loc_gte (GtkMateTextLoc* t1, GtkMateTextLoc* t2) {
	g_return_val_if_fail (t1 != NULL, FALSE);
	g_return_val_if_fail (t2 != NULL, FALSE);
	return !gtk_mate_text_loc_lt (t1, t2);
}


gboolean gtk_mate_text_loc_lte (GtkMateTextLoc* t1, GtkMateTextLoc* t2) {
	g_return_val_if_fail (t1 != NULL, FALSE);
	g_return_val_if_fail (t2 != NULL, FALSE);
	return !gtk_mate_text_loc_gt (t1, t2);
}


char* gtk_mate_text_loc_to_s (GtkMateTextLoc* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return g_strdup_printf ("{%d,%d}", self->line, self->line_offset);
}


GtkMateTextLoc* gtk_mate_text_loc_construct (GType object_type) {
	GtkMateTextLoc * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


GtkMateTextLoc* gtk_mate_text_loc_new (void) {
	return gtk_mate_text_loc_construct (GTK_MATE_TYPE_TEXT_LOC);
}


static void gtk_mate_text_loc_class_init (GtkMateTextLocClass * klass) {
	gtk_mate_text_loc_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_text_loc_finalize;
}


static void gtk_mate_text_loc_instance_init (GtkMateTextLoc * self) {
}


static void gtk_mate_text_loc_finalize (GObject* obj) {
	GtkMateTextLoc * self;
	self = GTK_MATE_TEXT_LOC (obj);
	G_OBJECT_CLASS (gtk_mate_text_loc_parent_class)->finalize (obj);
}


GType gtk_mate_text_loc_get_type (void) {
	static GType gtk_mate_text_loc_type_id = 0;
	if (gtk_mate_text_loc_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateTextLocClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_text_loc_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateTextLoc), 0, (GInstanceInitFunc) gtk_mate_text_loc_instance_init, NULL };
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
	g_return_if_fail (self != NULL);
	_tmp0 = NULL;
	self->root = (_tmp0 = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, self->priv->_grammar->scope_name)), (self->root == NULL) ? NULL : (self->root = (g_object_unref (self->root), NULL)), _tmp0);
	self->root->is_open = TRUE;
	gtk_mate_scope_start_mark_set (self->root, 0, 0, TRUE);
	gtk_mate_scope_end_mark_set (self->root, gtk_text_iter_get_line ((_tmp1 = gtk_mate_buffer_end_iter (self->priv->_buffer), &_tmp1)), gtk_text_iter_get_line_index ((_tmp2 = gtk_mate_buffer_end_iter (self->priv->_buffer), &_tmp2)), FALSE);
	dp = g_object_ref_sink (gtk_mate_double_pattern_new ());
	_tmp4 = NULL;
	_tmp3 = NULL;
	((GtkMatePattern*) dp)->name = (_tmp4 = (_tmp3 = gtk_mate_grammar_get_name (self->priv->_grammar), (_tmp3 == NULL) ? NULL : g_strdup (_tmp3)), ((GtkMatePattern*) dp)->name = (g_free (((GtkMatePattern*) dp)->name), NULL), _tmp4);
	_tmp6 = NULL;
	_tmp5 = NULL;
	dp->patterns = (_tmp6 = (_tmp5 = self->priv->_grammar->patterns, (_tmp5 == NULL) ? NULL : g_object_ref (_tmp5)), (dp->patterns == NULL) ? NULL : (dp->patterns = (g_object_unref (dp->patterns), NULL)), _tmp6);
	gtk_mate_pattern_set_grammar ((GtkMatePattern*) dp, self->priv->_grammar);
	_tmp8 = NULL;
	_tmp7 = NULL;
	self->root->pattern = (_tmp8 = (_tmp7 = (GtkMatePattern*) dp, (_tmp7 == NULL) ? NULL : g_object_ref (_tmp7)), (self->root->pattern == NULL) ? NULL : (self->root->pattern = (g_object_unref (self->root->pattern), NULL)), _tmp8);
	(dp == NULL) ? NULL : (dp = (g_object_unref (dp), NULL));
}


void gtk_mate_parser_stop_parsing (GtkMateParser* self) {
	g_return_if_fail (self != NULL);
	self->deactivation_level = self->deactivation_level + 1;
}


void gtk_mate_parser_start_parsing (GtkMateParser* self) {
	g_return_if_fail (self != NULL);
	if (self->deactivation_level > 0) {
		self->deactivation_level = self->deactivation_level - 1;
	}
	if (self->deactivation_level == 0) {
		gtk_mate_parser_process_changes (self);
	}
}


gboolean gtk_mate_parser_is_parsing (GtkMateParser* self) {
	g_return_val_if_fail (self != NULL, FALSE);
	return self->deactivation_level == 0;
}


/* Process all change ranges.*/
static void gtk_mate_parser_process_changes (GtkMateParser* self) {
	gint this_parsed_upto;
	g_return_if_fail (self != NULL);
	this_parsed_upto = -1;
	/* stdout.printf("process_changes (last_visible_line: %d)\n", last_visible_line);*/
	{
		GeeIterator* _range_it;
		/* stdout.printf("process_changes (last_visible_line: %d)\n", last_visible_line);*/
		_range_it = gee_iterable_iterator ((GeeIterable*) self->changes);
		/* stdout.printf("process_changes (last_visible_line: %d)\n", last_visible_line);*/
		while (gee_iterator_next (_range_it)) {
			RangeSetRange* range;
			gboolean _tmp0;
			/* stdout.printf("process_changes (last_visible_line: %d)\n", last_visible_line);*/
			range = (RangeSetRange*) gee_iterator_get (_range_it);
			_tmp0 = FALSE;
			if (range->b > this_parsed_upto) {
				_tmp0 = range->a <= (self->last_visible_line + self->priv->_look_ahead);
			} else {
				_tmp0 = FALSE;
			}
			if (_tmp0) {
				gint range_end;
				range_end = MIN (self->last_visible_line + self->priv->_look_ahead, range->b);
				this_parsed_upto = gtk_mate_parser_parse_range (self, range->a, range_end);
			}
			(range == NULL) ? NULL : (range = (g_object_unref (range), NULL));
		}
		(_range_it == NULL) ? NULL : (_range_it = (g_object_unref (_range_it), NULL));
	}
	/*//stdout.printf("%s\n", root.pretty(0));*/
	gee_collection_clear ((GeeCollection*) self->changes->ranges);
}


/* Parse from from_line to *at least* to_line. Will parse
 more if necessary. Returns the index of the last line
 parsed.*/
static gint gtk_mate_parser_parse_range (GtkMateParser* self, gint from_line, gint to_line) {
	gint line_ix;
	gboolean scope_changed;
	gboolean scope_ever_changed;
	gint end_line;
	g_return_val_if_fail (self != NULL, 0);
	/* stdout.printf("parse_range(%d, %d)\n", from_line, to_line);*/
	line_ix = from_line;
	scope_changed = FALSE;
	scope_ever_changed = FALSE;
	end_line = MIN (self->last_visible_line + 100, gtk_text_buffer_get_line_count ((GtkTextBuffer*) self->priv->_buffer) - 1);
	while (TRUE) {
		gboolean _tmp0;
		_tmp0 = FALSE;
		if (line_ix <= to_line) {
			_tmp0 = TRUE;
		} else {
			gboolean _tmp1;
			_tmp1 = FALSE;
			if (scope_ever_changed) {
				_tmp1 = line_ix <= end_line;
			} else {
				_tmp1 = FALSE;
			}
			_tmp0 = _tmp1;
		}
		if (!_tmp0) {
			break;
		}
		scope_changed = gtk_mate_parser_parse_line (self, line_ix++);
		if (scope_changed) {
			scope_ever_changed = TRUE;
			/* In the old scheme this wasn't necessary because 
			 the scope_at used a simple scan from the front. The GSequences
			 on the other hand can get confused if the later scopes
			 are inconsistent with earler ones. So we have to clear everything.
			 TODO: figure out a way to OPTIMIZE this again.*/
			gtk_mate_scope_clear_after (self->root, line_ix, -1);
			gtk_mate_parser_remove_colour_after (self, line_ix, 0);
			self->parsed_upto = line_ix;
		}
	}
	/* stdout.printf("parse_line returned: %s\n", scope_changed ? "true" : "false");
	stdout.printf("pretty:\n%s\n", root.pretty(2));*/
	return to_line;
}


static void gtk_mate_parser_remove_colour_after (GtkMateParser* self, gint line_ix, gint line_offset) {
	GSequenceIter* iter;
	GtkTextIter start_iter;
	GtkTextIter end_iter;
	g_return_if_fail (self != NULL);
	iter = g_sequence_get_begin_iter (self->tags);
	start_iter = gtk_mate_buffer_iter_at_line_offset (self->priv->_buffer, line_ix, line_offset);
	end_iter = gtk_mate_buffer_end_iter (self->priv->_buffer);
	while (!g_sequence_iter_is_end (g_sequence_iter_next (iter))) {
		GtkTextTag* _tmp0;
		GtkTextTag* t;
		_tmp0 = NULL;
		t = (_tmp0 = (GtkTextTag*) g_sequence_get (iter), (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
		gtk_text_buffer_remove_tag ((GtkTextBuffer*) self->priv->_buffer, t, &start_iter, &end_iter);
		iter = g_sequence_iter_next (iter);
		(t == NULL) ? NULL : (t = (g_object_unref (t), NULL));
	}
}


/* Parse line line_ix. Returns true if the ending
 scope of the line has changed.*/
static gboolean gtk_mate_parser_parse_line (GtkMateParser* self, gint line_ix) {
	char* line;
	gint length;
	GtkMateScope* start_scope;
	GtkMateScope* end_scope1;
	GtkMateScanner* scanner;
	GeeArrayList* all_scopes;
	GeeArrayList* closed_scopes;
	GeeArrayList* removed_scopes;
	GtkMateScope* end_scope2;
	gboolean _tmp3;
	g_return_val_if_fail (self != NULL, FALSE);
	line = gtk_mate_buffer_get_line (self->priv->_buffer, line_ix);
	length = (gint) strlen (line);
	/*buffer.get_line_length(line_ix);
	 stdout.printf("p%d, ", line_ix);
	 stdout.flush();*/
	if (line_ix > self->parsed_upto) {
		self->parsed_upto = line_ix;
	}
	/* stdout.flush();*/
	start_scope = gtk_mate_scope_scope_at (self->root, line_ix, 0);
	if (start_scope != NULL) {
		GtkMateScope* _tmp0;
		/* stdout.printf("start_scope is: %s\n", start_scope.name);*/
		_tmp0 = NULL;
		start_scope = (_tmp0 = gtk_mate_scope_containing_double_scope (start_scope, line_ix), (start_scope == NULL) ? NULL : (start_scope = (g_object_unref (start_scope), NULL)), _tmp0);
	}
	/* stdout.printf("start_scope is: %s\n", start_scope.name);*/
	end_scope1 = gtk_mate_scope_scope_at (self->root, line_ix, G_MAXINT);
	if (end_scope1 != NULL) {
		GtkMateScope* _tmp1;
		_tmp1 = NULL;
		end_scope1 = (_tmp1 = gtk_mate_scope_containing_double_scope (end_scope1, line_ix), (end_scope1 == NULL) ? NULL : (end_scope1 = (g_object_unref (end_scope1), NULL)), _tmp1);
	}
	/* stdout.printf("end_scope1: %s\n", end_scope1.name);*/
	scanner = g_object_ref_sink (gtk_mate_scanner_new (start_scope, line, length));
	all_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	gee_collection_add ((GeeCollection*) all_scopes, start_scope);
	closed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	removed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	gee_collection_add ((GeeCollection*) all_scopes, start_scope);
	{
		GeeIterator* _m_it;
		_m_it = gee_iterable_iterator ((GeeIterable*) scanner);
		while (gee_iterator_next (_m_it)) {
			GtkMateMarker* m;
			GtkMateScope* expected_scope;
			m = (GtkMateMarker*) gee_iterator_get (_m_it);
			expected_scope = gtk_mate_parser_get_expected_scope (self, gtk_mate_scanner_get_current_scope (scanner), line_ix, scanner->position);
			/* if (expected_scope != null)
			 stdout.printf("expected_scope: %s (%d, %d)\n", expected_scope.name, expected_scope.start_loc().line, 
			  expected_scope.start_loc().line_offset);
			 else
			 stdout.printf("no expected scope\n");
			 stdout.printf("  scope: %s (%d, %d) (line length: %d)\n", m.pattern.name, m.from, m.match.end(0), length);*/
			if (m->is_close_scope) {
				/* stdout.printf("     (closing)\n");*/
				gtk_mate_parser_close_scope (self, scanner, expected_scope, line_ix, line, length, m, all_scopes, closed_scopes, removed_scopes);
			} else {
				if (GTK_MATE_IS_DOUBLE_PATTERN (m->pattern)) {
					/* stdout.printf("     (opening)\n");*/
					gtk_mate_parser_open_scope (self, scanner, expected_scope, line_ix, line, length, m, all_scopes, closed_scopes, removed_scopes);
				} else {
					/* stdout.printf("     (single)\n");*/
					gtk_mate_parser_single_scope (self, scanner, expected_scope, line_ix, line, length, m, all_scopes, closed_scopes, removed_scopes);
				}
			}
			/*stdout.printf("pretty:\n%s\n", root.pretty(2));*/
			scanner->position = onig_match_end (m->match, 0);
			(m == NULL) ? NULL : (m = (g_object_unref (m), NULL));
			(expected_scope == NULL) ? NULL : (expected_scope = (g_object_unref (expected_scope), NULL));
		}
		(_m_it == NULL) ? NULL : (_m_it = (g_object_unref (_m_it), NULL));
	}
	gtk_mate_parser_clear_line (self, line_ix, start_scope, all_scopes, closed_scopes, removed_scopes);
	end_scope2 = gtk_mate_scope_scope_at (self->root, line_ix, G_MAXINT);
	if (end_scope2 != NULL) {
		GtkMateScope* _tmp2;
		_tmp2 = NULL;
		end_scope2 = (_tmp2 = gtk_mate_scope_containing_double_scope (end_scope2, line_ix), (end_scope2 == NULL) ? NULL : (end_scope2 = (g_object_unref (end_scope2), NULL)), _tmp2);
	}
	/* stdout.printf("end_scope2: %s\n", end_scope2.name);
	stdout.printf("%s\n", this.root.pretty(0));*/
	if (self->priv->_colourer != NULL) {
		/*stdout.printf("before_uncolour_scopes\n");*/
		gtk_mate_colourer_uncolour_scopes (self->priv->_colourer, removed_scopes);
		/*stdout.printf("before_colour_line_with_scopes\n");*/
		gtk_mate_colourer_colour_line_with_scopes (self->priv->_colourer, all_scopes);
	} else {
	}
	/*stdout.printf("after_colour_line_with_scopes\n");
	 stdout.printf("no colourer");*/
	return (_tmp3 = end_scope1 != end_scope2, line = (g_free (line), NULL), (start_scope == NULL) ? NULL : (start_scope = (g_object_unref (start_scope), NULL)), (end_scope1 == NULL) ? NULL : (end_scope1 = (g_object_unref (end_scope1), NULL)), (scanner == NULL) ? NULL : (scanner = (g_object_unref (scanner), NULL)), (all_scopes == NULL) ? NULL : (all_scopes = (g_object_unref (all_scopes), NULL)), (closed_scopes == NULL) ? NULL : (closed_scopes = (g_object_unref (closed_scopes), NULL)), (removed_scopes == NULL) ? NULL : (removed_scopes = (g_object_unref (removed_scopes), NULL)), (end_scope2 == NULL) ? NULL : (end_scope2 = (g_object_unref (end_scope2), NULL)), _tmp3);
}


void gtk_mate_parser_clear_line (GtkMateParser* self, gint line_ix, GtkMateScope* start_scope, GeeArrayList* all_scopes, GeeArrayList* closed_scopes, GeeArrayList* removed_scopes) {
	GtkMateScope* _tmp0;
	GtkMateScope* cs;
	GeeArrayList* scopes_that_closed_on_line;
	GtkMateScope* _tmp3;
	GtkMateScope* ts;
	g_return_if_fail (self != NULL);
	g_return_if_fail (start_scope != NULL);
	g_return_if_fail (all_scopes != NULL);
	g_return_if_fail (closed_scopes != NULL);
	g_return_if_fail (removed_scopes != NULL);
	/* If we are reparsing, we might find that some scopes have disappeared,
	 delete them:*/
	_tmp0 = NULL;
	cs = (_tmp0 = start_scope, (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
	while (cs != NULL) {
		GeeArrayList* removed;
		GtkMateScope* _tmp2;
		GtkMateScope* _tmp1;
		/*stdout.printf("  removing_scopes from: %s\n", cs.name);*/
		removed = gtk_mate_scope_delete_any_on_line_not_in (cs, line_ix, all_scopes);
		{
			GeeIterator* _rs_it;
			_rs_it = gee_iterable_iterator ((GeeIterable*) removed);
			while (gee_iterator_next (_rs_it)) {
				GtkMateScope* rs;
				rs = (GtkMateScope*) gee_iterator_get (_rs_it);
				gee_collection_add ((GeeCollection*) removed_scopes, rs);
				(rs == NULL) ? NULL : (rs = (g_object_unref (rs), NULL));
			}
			(_rs_it == NULL) ? NULL : (_rs_it = (g_object_unref (_rs_it), NULL));
		}
		_tmp2 = NULL;
		_tmp1 = NULL;
		cs = (_tmp2 = (_tmp1 = cs->parent, (_tmp1 == NULL) ? NULL : g_object_ref (_tmp1)), (cs == NULL) ? NULL : (cs = (g_object_unref (cs), NULL)), _tmp2);
		(removed == NULL) ? NULL : (removed = (g_object_unref (removed), NULL));
	}
	/* @removed_scopes += removed_scopes
	 any that we expected to close on this line that now don't?
	 first build list of scopes that close on this line (including ones
	 that did but haven't been removed yet).*/
	scopes_that_closed_on_line = gee_array_list_new (GTK_MATE_TYPE_SCOPE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	_tmp3 = NULL;
	ts = (_tmp3 = start_scope, (_tmp3 == NULL) ? NULL : g_object_ref (_tmp3));
	while (ts->parent != NULL) {
		GtkMateScope* _tmp5;
		GtkMateScope* _tmp4;
		/* stdout.printf("checking for closing scope: %s (%d)\n", ts.name, ts.inner_end_line());*/
		if (gtk_mate_scope_inner_end_line (ts) == line_ix) {
			/* stdout.printf("scope that closed on line: %s\n", ts.name);*/
			gee_collection_add ((GeeCollection*) scopes_that_closed_on_line, ts);
		}
		_tmp5 = NULL;
		_tmp4 = NULL;
		ts = (_tmp5 = (_tmp4 = ts->parent, (_tmp4 == NULL) ? NULL : g_object_ref (_tmp4)), (ts == NULL) ? NULL : (ts = (g_object_unref (ts), NULL)), _tmp5);
	}
	{
		GeeIterator* _s_it;
		_s_it = gee_iterable_iterator ((GeeIterable*) scopes_that_closed_on_line);
		while (gee_iterator_next (_s_it)) {
			GtkMateScope* s;
			s = (GtkMateScope*) gee_iterator_get (_s_it);
			if (!gee_collection_contains ((GeeCollection*) closed_scopes, s)) {
				if (s->is_capture) {
					/* stdout.printf("    removing scope: %s\n", s.name);*/
					gtk_mate_scope_delete_child (s->parent, s);
					gee_collection_add ((GeeCollection*) removed_scopes, s);
				} else {
					GtkTextIter end_iter;
					gint end_line;
					gint end_line_index;
					/* @removed_scopes << s*/
					if (self->priv->_colourer != NULL) {
						gtk_mate_colourer_uncolour_scope (self->priv->_colourer, s, FALSE);
					}
					/* s.inner_end_mark = null;
					 s.end_mark = null;
					 s.is_open = true;*/
					end_iter = gtk_mate_buffer_end_iter (self->priv->_buffer);
					end_line = gtk_text_iter_get_line (&end_iter);
					end_line_index = gtk_text_iter_get_line_index (&end_iter);
					gtk_mate_scope_inner_end_mark_set (s, end_line, end_line_index, FALSE);
					gtk_mate_scope_end_mark_set (s, end_line, end_line_index, FALSE);
					s->is_open = TRUE;
				}
			}
			(s == NULL) ? NULL : (s = (g_object_unref (s), NULL));
		}
		(_s_it == NULL) ? NULL : (_s_it = (g_object_unref (_s_it), NULL));
	}
	(cs == NULL) ? NULL : (cs = (g_object_unref (cs), NULL));
	(scopes_that_closed_on_line == NULL) ? NULL : (scopes_that_closed_on_line = (g_object_unref (scopes_that_closed_on_line), NULL));
	(ts == NULL) ? NULL : (ts = (g_object_unref (ts), NULL));
}


GtkMateScope* gtk_mate_parser_get_expected_scope (GtkMateParser* self, GtkMateScope* current_scope, gint line, gint line_offset) {
	GtkMateTextLoc* _tmp0;
	GtkMateScope* _tmp1;
	GtkMateScope* expected_scope;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (current_scope != NULL, NULL);
	/*stdout.printf("get_expected_scope(%s, %d, %d)\n", current_scope.name, line, line_offset);*/
	_tmp0 = NULL;
	_tmp1 = NULL;
	expected_scope = (_tmp1 = gtk_mate_scope_first_child_after (current_scope, _tmp0 = gtk_mate_text_loc_make (line, line_offset)), (_tmp0 == NULL) ? NULL : (_tmp0 = (g_object_unref (_tmp0), NULL)), _tmp1);
	/*stdout.printf("first_child_after: %s\n", expected_scope.name);*/
	g_assert (expected_scope != current_scope);
	if (expected_scope != NULL) {
		if (gtk_mate_scope_start_line (expected_scope) != line) {
			GtkMateScope* _tmp2;
			_tmp2 = NULL;
			expected_scope = (_tmp2 = NULL, (expected_scope == NULL) ? NULL : (expected_scope = (g_object_unref (expected_scope), NULL)), _tmp2);
		}
		while (TRUE) {
			gboolean _tmp3;
			GtkMateScope* _tmp5;
			GtkMateScope* _tmp4;
			_tmp3 = FALSE;
			if (expected_scope != NULL) {
				_tmp3 = expected_scope->is_capture;
			} else {
				_tmp3 = FALSE;
			}
			if (!_tmp3) {
				break;
			}
			_tmp5 = NULL;
			_tmp4 = NULL;
			expected_scope = (_tmp5 = (_tmp4 = expected_scope->parent, (_tmp4 == NULL) ? NULL : g_object_ref (_tmp4)), (expected_scope == NULL) ? NULL : (expected_scope = (g_object_unref (expected_scope), NULL)), _tmp5);
		}
	}
	return expected_scope;
}


void gtk_mate_parser_close_scope (GtkMateParser* self, GtkMateScanner* scanner, GtkMateScope* expected_scope, gint line_ix, const char* line, gint length, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes, GeeArrayList* removed_scopes) {
	char* end_match_string;
	gboolean _tmp0;
	gboolean _tmp1;
	gboolean _tmp2;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scanner != NULL);
	g_return_if_fail (line != NULL);
	g_return_if_fail (m != NULL);
	g_return_if_fail (all_scopes != NULL);
	g_return_if_fail (closed_scopes != NULL);
	g_return_if_fail (removed_scopes != NULL);
	end_match_string = string_substring (line, (glong) m->from, (glong) (onig_match_end (m->match, 0) - m->from));
	_tmp0 = FALSE;
	_tmp1 = FALSE;
	_tmp2 = FALSE;
	if (gtk_mate_scanner_get_current_scope (scanner)->end_mark != NULL) {
		GtkMateTextLoc* _tmp4;
		GtkMateTextLoc* _tmp3;
		_tmp4 = NULL;
		_tmp3 = NULL;
		_tmp2 = gtk_mate_text_loc_equal (_tmp3 = gtk_mate_scope_end_loc (gtk_mate_scanner_get_current_scope (scanner)), _tmp4 = gtk_mate_text_loc_make (line_ix, onig_match_end (m->match, 0)));
		(_tmp4 == NULL) ? NULL : (_tmp4 = (g_object_unref (_tmp4), NULL));
		(_tmp3 == NULL) ? NULL : (_tmp3 = (g_object_unref (_tmp3), NULL));
	} else {
		_tmp2 = FALSE;
	}
	if (_tmp2) {
		GtkMateTextLoc* _tmp6;
		GtkMateTextLoc* _tmp5;
		_tmp6 = NULL;
		_tmp5 = NULL;
		_tmp1 = gtk_mate_text_loc_equal (_tmp5 = gtk_mate_scope_inner_end_loc (gtk_mate_scanner_get_current_scope (scanner)), _tmp6 = gtk_mate_text_loc_make (line_ix, m->from));
		(_tmp6 == NULL) ? NULL : (_tmp6 = (g_object_unref (_tmp6), NULL));
		(_tmp5 == NULL) ? NULL : (_tmp5 = (g_object_unref (_tmp5), NULL));
	} else {
		_tmp1 = FALSE;
	}
	if (_tmp1) {
		_tmp0 = _vala_strcmp0 (gtk_mate_scanner_get_current_scope (scanner)->end_match_string, end_match_string) == 0;
	} else {
		_tmp0 = FALSE;
	}
	if (_tmp0) {
		GSequenceIter* iter;
		/* we have already parsed this line and this scope ends here
		 Re-add the captures from the end of the current scope to the 
		 tracking arrays*/
		iter = g_sequence_get_begin_iter (gtk_mate_scope_get_children (gtk_mate_scanner_get_current_scope (scanner)));
		while (!g_sequence_iter_is_end (iter)) {
			GtkMateScope* _tmp7;
			GtkMateScope* child;
			gboolean _tmp8;
			_tmp7 = NULL;
			child = (_tmp7 = (GtkMateScope*) g_sequence_get (iter), (_tmp7 == NULL) ? NULL : g_object_ref (_tmp7));
			_tmp8 = FALSE;
			if (child->is_capture) {
				_tmp8 = gtk_mate_scope_start_line (child) == line_ix;
			} else {
				_tmp8 = FALSE;
			}
			if (_tmp8) {
				if (!gee_collection_contains ((GeeCollection*) closed_scopes, child)) {
					gee_collection_add ((GeeCollection*) closed_scopes, child);
				}
				if (!gee_collection_contains ((GeeCollection*) all_scopes, child)) {
					gee_collection_add ((GeeCollection*) all_scopes, child);
				}
			}
			iter = g_sequence_iter_next (iter);
			(child == NULL) ? NULL : (child = (g_object_unref (child), NULL));
		}
	} else {
		char* _tmp10;
		const char* _tmp9;
		/* stdout.printf("closing scope matches expected\n");
		 stdout.printf("closing scope at %d\n", m.from);*/
		if (self->priv->_colourer != NULL) {
			gtk_mate_colourer_uncolour_scope (self->priv->_colourer, gtk_mate_scanner_get_current_scope (scanner), FALSE);
		}
		gtk_mate_parser_set_inner_end_mark_safely (self, gtk_mate_scanner_get_current_scope (scanner), m, line_ix, length, 0);
		gtk_mate_parser_set_end_mark_safely (self, gtk_mate_scanner_get_current_scope (scanner), m, line_ix, length, 0);
		gtk_mate_scanner_get_current_scope (scanner)->is_open = FALSE;
		_tmp10 = NULL;
		_tmp9 = NULL;
		gtk_mate_scanner_get_current_scope (scanner)->end_match_string = (_tmp10 = (_tmp9 = end_match_string, (_tmp9 == NULL) ? NULL : g_strdup (_tmp9)), gtk_mate_scanner_get_current_scope (scanner)->end_match_string = (g_free (gtk_mate_scanner_get_current_scope (scanner)->end_match_string), NULL), _tmp10);
		/*stdout.printf("end_match_string: '%s'\n", scanner.current_scope.end_match_string);*/
		gtk_mate_parser_handle_captures (self, line_ix, length, line, gtk_mate_scanner_get_current_scope (scanner), m, all_scopes, closed_scopes);
		if (expected_scope != NULL) {
			gtk_mate_scope_delete_child (gtk_mate_scanner_get_current_scope (scanner), expected_scope);
			gee_collection_add ((GeeCollection*) removed_scopes, expected_scope);
		}
	}
	/* @removed_scopes << expected_scope*/
	gee_collection_add ((GeeCollection*) removed_scopes, gtk_mate_scanner_get_current_scope (scanner));
	/* so it gets uncoloured*/
	gee_collection_add ((GeeCollection*) closed_scopes, gtk_mate_scanner_get_current_scope (scanner));
	gtk_mate_scanner_set_current_scope (scanner, gtk_mate_scanner_get_current_scope (scanner)->parent);
	gee_collection_add ((GeeCollection*) all_scopes, gtk_mate_scanner_get_current_scope (scanner));
	end_match_string = (g_free (end_match_string), NULL);
}


void gtk_mate_parser_open_scope (GtkMateParser* self, GtkMateScanner* scanner, GtkMateScope* expected_scope, gint line_ix, const char* line, gint length, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes, GeeArrayList* removed_scopes) {
	GtkMateScope* s;
	GtkMatePattern* _tmp1;
	GtkMatePattern* _tmp0;
	OnigMatch* _tmp3;
	OnigMatch* _tmp2;
	char* _tmp4;
	GtkTextIter end_iter;
	gint end_line;
	gint end_line_index;
	GtkMateScope* _tmp6;
	GtkMateScope* _tmp5;
	GtkMateScope* _tmp7;
	GtkMateScope* new_scope;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scanner != NULL);
	g_return_if_fail (line != NULL);
	g_return_if_fail (m != NULL);
	g_return_if_fail (all_scopes != NULL);
	g_return_if_fail (closed_scopes != NULL);
	g_return_if_fail (removed_scopes != NULL);
	/* stdout.printf("[opening with %d patterns], \n", ((DoublePattern) m.pattern).patterns.size);*/
	s = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, m->pattern->name));
	_tmp1 = NULL;
	_tmp0 = NULL;
	s->pattern = (_tmp1 = (_tmp0 = m->pattern, (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0)), (s->pattern == NULL) ? NULL : (s->pattern = (g_object_unref (s->pattern), NULL)), _tmp1);
	_tmp3 = NULL;
	_tmp2 = NULL;
	s->open_match = (_tmp3 = (_tmp2 = m->match, (_tmp2 == NULL) ? NULL : g_object_ref (_tmp2)), (s->open_match == NULL) ? NULL : (s->open_match = (g_object_unref (s->open_match), NULL)), _tmp3);
	gtk_mate_parser_set_start_mark_safely (self, s, m, line_ix, length, 0);
	gtk_mate_parser_set_inner_start_mark_safely (self, s, m, line_ix, length, 0);
	_tmp4 = NULL;
	s->begin_match_string = (_tmp4 = string_substring (line, (glong) m->from, (glong) (onig_match_end (m->match, 0) - m->from)), s->begin_match_string = (g_free (s->begin_match_string), NULL), _tmp4);
	end_iter = gtk_mate_buffer_end_iter (self->priv->_buffer);
	end_line = gtk_text_iter_get_line (&end_iter);
	end_line_index = gtk_text_iter_get_line_index (&end_iter);
	gtk_mate_scope_inner_end_mark_set (s, end_line, end_line_index, FALSE);
	gtk_mate_scope_end_mark_set (s, end_line, end_line_index, FALSE);
	s->is_open = TRUE;
	s->is_capture = FALSE;
	_tmp6 = NULL;
	_tmp5 = NULL;
	s->parent = (_tmp6 = (_tmp5 = gtk_mate_scanner_get_current_scope (scanner), (_tmp5 == NULL) ? NULL : g_object_ref (_tmp5)), (s->parent == NULL) ? NULL : (s->parent = (g_object_unref (s->parent), NULL)), _tmp6);
	_tmp7 = NULL;
	new_scope = (_tmp7 = s, (_tmp7 == NULL) ? NULL : g_object_ref (_tmp7));
	/* is this a bug? captures aren't necessarily to be put into all_scopes yet surely?*/
	if (expected_scope != NULL) {
		/* check mod ending scopes as the new one will not have a closing marker
		 but the expected one will:*/
		if (gtk_mate_scope_surface_identical_to_modulo_ending (s, expected_scope)) {
			GtkMateScope* _tmp9;
			GtkMateScope* _tmp8;
			GSequenceIter* iter;
			/* stdout.printf("surface_identical_mod_ending: keep expected\n");
			 don't need to do anything as we have already found this,
			 but let's keep the old scope since it will have children and what not.*/
			_tmp9 = NULL;
			_tmp8 = NULL;
			new_scope = (_tmp9 = (_tmp8 = expected_scope, (_tmp8 == NULL) ? NULL : g_object_ref (_tmp8)), (new_scope == NULL) ? NULL : (new_scope = (g_object_unref (new_scope), NULL)), _tmp9);
			iter = g_sequence_get_begin_iter (gtk_mate_scope_get_children (expected_scope));
			while (!g_sequence_iter_is_end (iter)) {
				GtkMateScope* _tmp10;
				GtkMateScope* child;
				_tmp10 = NULL;
				child = (_tmp10 = (GtkMateScope*) g_sequence_get (iter), (_tmp10 == NULL) ? NULL : g_object_ref (_tmp10));
				gee_collection_add ((GeeCollection*) closed_scopes, child);
				gee_collection_add ((GeeCollection*) all_scopes, child);
				iter = g_sequence_iter_next (iter);
				(child == NULL) ? NULL : (child = (g_object_unref (child), NULL));
			}
			gtk_mate_scanner_set_current_scope (scanner, expected_scope);
		} else {
			/*stdout.printf("surface_NOT_identical_mod_ending: replace expected\n");*/
			if (gtk_mate_scope_overlaps_with (s, expected_scope)) {
				gtk_mate_scope_delete_child (gtk_mate_scanner_get_current_scope (scanner), expected_scope);
				/* removed_scopes << expected_scope*/
				gee_collection_add ((GeeCollection*) removed_scopes, expected_scope);
			}
			gtk_mate_parser_handle_captures (self, line_ix, length, line, s, m, all_scopes, closed_scopes);
			gtk_mate_scope_add_child (gtk_mate_scanner_get_current_scope (scanner), s);
			gtk_mate_scanner_set_current_scope (scanner, s);
		}
	} else {
		gtk_mate_parser_handle_captures (self, line_ix, length, line, s, m, all_scopes, closed_scopes);
		gtk_mate_scope_add_child (gtk_mate_scanner_get_current_scope (scanner), s);
		gtk_mate_scanner_set_current_scope (scanner, s);
	}
	gee_collection_add ((GeeCollection*) all_scopes, new_scope);
	(s == NULL) ? NULL : (s = (g_object_unref (s), NULL));
	(new_scope == NULL) ? NULL : (new_scope = (g_object_unref (new_scope), NULL));
}


void gtk_mate_parser_single_scope (GtkMateParser* self, GtkMateScanner* scanner, GtkMateScope* expected_scope, gint line_ix, const char* line, gint length, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes, GeeArrayList* removed_scopes) {
	GtkMateScope* s;
	GtkMatePattern* _tmp1;
	GtkMatePattern* _tmp0;
	OnigMatch* _tmp3;
	OnigMatch* _tmp2;
	char* _tmp4;
	GtkMateScope* _tmp6;
	GtkMateScope* _tmp5;
	GtkMateScope* _tmp7;
	GtkMateScope* new_scope;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scanner != NULL);
	g_return_if_fail (line != NULL);
	g_return_if_fail (m != NULL);
	g_return_if_fail (all_scopes != NULL);
	g_return_if_fail (closed_scopes != NULL);
	g_return_if_fail (removed_scopes != NULL);
	s = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, m->pattern->name));
	_tmp1 = NULL;
	_tmp0 = NULL;
	s->pattern = (_tmp1 = (_tmp0 = m->pattern, (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0)), (s->pattern == NULL) ? NULL : (s->pattern = (g_object_unref (s->pattern), NULL)), _tmp1);
	_tmp3 = NULL;
	_tmp2 = NULL;
	s->open_match = (_tmp3 = (_tmp2 = m->match, (_tmp2 == NULL) ? NULL : g_object_ref (_tmp2)), (s->open_match == NULL) ? NULL : (s->open_match = (g_object_unref (s->open_match), NULL)), _tmp3);
	gtk_mate_parser_set_start_mark_safely (self, s, m, line_ix, length, 0);
	gtk_mate_parser_set_end_mark_safely (self, s, m, line_ix, length, 0);
	s->is_open = FALSE;
	s->is_capture = FALSE;
	_tmp4 = NULL;
	s->begin_match_string = (_tmp4 = string_substring (line, (glong) m->from, (glong) (onig_match_end (m->match, 0) - m->from)), s->begin_match_string = (g_free (s->begin_match_string), NULL), _tmp4);
	/*stdout.printf("_match_string: '%s'\n", s.begin_match_string);*/
	_tmp6 = NULL;
	_tmp5 = NULL;
	s->parent = (_tmp6 = (_tmp5 = gtk_mate_scanner_get_current_scope (scanner), (_tmp5 == NULL) ? NULL : g_object_ref (_tmp5)), (s->parent == NULL) ? NULL : (s->parent = (g_object_unref (s->parent), NULL)), _tmp6);
	_tmp7 = NULL;
	new_scope = (_tmp7 = s, (_tmp7 == NULL) ? NULL : g_object_ref (_tmp7));
	if (expected_scope != NULL) {
		if (gtk_mate_scope_surface_identical_to (s, expected_scope)) {
			GtkMateScope* _tmp9;
			GtkMateScope* _tmp8;
			GSequenceIter* iter;
			_tmp9 = NULL;
			_tmp8 = NULL;
			new_scope = (_tmp9 = (_tmp8 = expected_scope, (_tmp8 == NULL) ? NULL : g_object_ref (_tmp8)), (new_scope == NULL) ? NULL : (new_scope = (g_object_unref (new_scope), NULL)), _tmp9);
			iter = g_sequence_get_begin_iter (gtk_mate_scope_get_children (expected_scope));
			while (!g_sequence_iter_is_end (iter)) {
				gee_collection_add ((GeeCollection*) closed_scopes, (GtkMateScope*) g_sequence_get (iter));
				iter = g_sequence_iter_next (iter);
			}
		} else {
			gtk_mate_parser_handle_captures (self, line_ix, length, line, s, m, all_scopes, closed_scopes);
			if (gtk_mate_scope_overlaps_with (s, expected_scope)) {
				/* stdout.printf("%s overlaps with expected %s (current: %s)\n", s.name, expected_scope.name, scanner.current_scope.name);*/
				if (expected_scope == gtk_mate_scanner_get_current_scope (scanner)) {
				} else {
					/* we expected this scope to close, but it doesn't*/
					gtk_mate_scope_delete_child (gtk_mate_scanner_get_current_scope (scanner), expected_scope);
					/* removed_scopes << expected_scope*/
					gee_collection_add ((GeeCollection*) removed_scopes, expected_scope);
				}
			}
			gtk_mate_scope_add_child (gtk_mate_scanner_get_current_scope (scanner), s);
		}
	} else {
		gtk_mate_parser_handle_captures (self, line_ix, length, line, s, m, all_scopes, closed_scopes);
		gtk_mate_scope_add_child (gtk_mate_scanner_get_current_scope (scanner), s);
	}
	gee_collection_add ((GeeCollection*) all_scopes, new_scope);
	gee_collection_add ((GeeCollection*) closed_scopes, new_scope);
	(s == NULL) ? NULL : (s = (g_object_unref (s), NULL));
	(new_scope == NULL) ? NULL : (new_scope = (g_object_unref (new_scope), NULL));
}


/* Opens scopes for captures AND creates closing regexp from
 captures if necessary.*/
void gtk_mate_parser_handle_captures (GtkMateParser* self, gint line_ix, gint length, const char* line, GtkMateScope* scope, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes) {
	OnigRx* _tmp0;
	g_return_if_fail (self != NULL);
	g_return_if_fail (line != NULL);
	g_return_if_fail (scope != NULL);
	g_return_if_fail (m != NULL);
	g_return_if_fail (all_scopes != NULL);
	g_return_if_fail (closed_scopes != NULL);
	_tmp0 = NULL;
	_tmp0 = gtk_mate_parser_make_closing_regex (self, line, scope, m);
	(_tmp0 == NULL) ? NULL : (_tmp0 = (g_object_unref (_tmp0), NULL));
	gtk_mate_parser_collect_child_captures (self, line_ix, length, scope, m, all_scopes, closed_scopes);
}


OnigRx* gtk_mate_parser_make_closing_regex (GtkMateParser* self, const char* line, GtkMateScope* scope, GtkMateMarker* m) {
	gboolean _tmp0;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (line != NULL, NULL);
	g_return_val_if_fail (scope != NULL, NULL);
	g_return_val_if_fail (m != NULL, NULL);
	_tmp0 = FALSE;
	if (GTK_MATE_IS_DOUBLE_PATTERN (m->pattern)) {
		_tmp0 = !m->is_close_scope;
	} else {
		_tmp0 = FALSE;
	}
	/*stdout.printf("make_closing_regex\n");
	 new_end = pattern.end.gsub(/\\([0-9]+)/) do
	 md.captures.send(:[], $1.to_i-1)
	 end*/
	if (_tmp0) {
		GtkMateDoublePattern* _tmp1;
		GtkMateDoublePattern* dp;
		OnigRx* rx;
		OnigMatch* match;
		gint pos;
		GString* src;
		gboolean found;
		OnigMatch* _tmp2;
		OnigRx* _tmp5;
		_tmp1 = NULL;
		dp = (_tmp1 = GTK_MATE_DOUBLE_PATTERN (m->pattern), (_tmp1 == NULL) ? NULL : g_object_ref (_tmp1));
		/*stdout.printf("making closing regex: %s (%d)\n", dp.end_string, (int) dp.end_string.length);*/
		rx = onig_rx_make1 ("\\\\(\\d+)");
		match = NULL;
		pos = 0;
		src = g_string_new ("");
		found = FALSE;
		_tmp2 = NULL;
		while ((match = (_tmp2 = onig_rx_search (rx, dp->end_string, pos, (gint) string_get_length (dp->end_string)), (match == NULL) ? NULL : (match = (g_object_unref (match), NULL)), _tmp2)) != NULL) {
			char* _tmp3;
			char* numstr;
			gint num;
			char* capstr;
			found = TRUE;
			_tmp3 = NULL;
			g_string_append (src, _tmp3 = string_substring (dp->end_string, (glong) pos, (glong) (onig_match_begin (match, 0) - pos)));
			_tmp3 = (g_free (_tmp3), NULL);
			numstr = string_substring (dp->end_string, (glong) onig_match_begin (match, 1), (glong) (onig_match_end (match, 1) - onig_match_begin (match, 1)));
			num = atoi (numstr);
			/*stdout.printf("capture found: %d\n", num);*/
			capstr = string_substring (line, (glong) onig_match_begin (m->match, num), (glong) (onig_match_end (m->match, num) - onig_match_begin (m->match, num)));
			g_string_append (src, capstr);
			pos = onig_match_end (match, 1);
			numstr = (g_free (numstr), NULL);
			capstr = (g_free (capstr), NULL);
		}
		if (found) {
			char* _tmp4;
			_tmp4 = NULL;
			g_string_append (src, _tmp4 = string_substring (dp->end_string, (glong) pos, string_get_length (dp->end_string) - pos));
			_tmp4 = (g_free (_tmp4), NULL);
		} else {
			g_string_append (src, dp->end_string);
		}
		/*stdout.printf("src: '%s'\n", src.str);*/
		_tmp5 = NULL;
		scope->closing_regex = (_tmp5 = onig_rx_make1 (src->str), (scope->closing_regex == NULL) ? NULL : (scope->closing_regex = (g_object_unref (scope->closing_regex), NULL)), _tmp5);
		(dp == NULL) ? NULL : (dp = (g_object_unref (dp), NULL));
		(rx == NULL) ? NULL : (rx = (g_object_unref (rx), NULL));
		(match == NULL) ? NULL : (match = (g_object_unref (match), NULL));
		(src == NULL) ? NULL : (src = (g_string_free (src, TRUE), NULL));
	}
	return NULL;
}


void gtk_mate_parser_set_start_mark_safely (GtkMateParser* self, GtkMateScope* scope, GtkMateMarker* m, gint line_ix, gint length, gint cap) {
	gint to;
	gboolean _tmp0;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	g_return_if_fail (m != NULL);
	to = onig_match_begin (m->match, cap);
	_tmp0 = FALSE;
	if (to == length) {
		_tmp0 = gtk_text_buffer_get_line_count ((GtkTextBuffer*) self->priv->_buffer) > (line_ix + 1);
	} else {
		_tmp0 = FALSE;
	}
	if (_tmp0) {
		gtk_mate_scope_start_mark_set (scope, line_ix + 1, 0, FALSE);
	} else {
		gtk_mate_scope_start_mark_set (scope, line_ix, MIN (to, length), FALSE);
	}
}


void gtk_mate_parser_set_inner_start_mark_safely (GtkMateParser* self, GtkMateScope* scope, GtkMateMarker* m, gint line_ix, gint length, gint cap) {
	gint to;
	gboolean _tmp0;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	g_return_if_fail (m != NULL);
	to = onig_match_end (m->match, cap);
	_tmp0 = FALSE;
	if (to == length) {
		_tmp0 = gtk_text_buffer_get_line_count ((GtkTextBuffer*) self->priv->_buffer) > (line_ix + 1);
	} else {
		_tmp0 = FALSE;
	}
	if (_tmp0) {
		gtk_mate_scope_inner_start_mark_set (scope, line_ix + 1, 0, TRUE);
	} else {
		gtk_mate_scope_inner_start_mark_set (scope, line_ix, MIN (to, length), TRUE);
	}
}


void gtk_mate_parser_set_inner_end_mark_safely (GtkMateParser* self, GtkMateScope* scope, GtkMateMarker* m, gint line_ix, gint length, gint cap) {
	gint to;
	gboolean _tmp0;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	g_return_if_fail (m != NULL);
	to = onig_match_end (m->match, cap);
	_tmp0 = FALSE;
	if (to == length) {
		_tmp0 = gtk_text_buffer_get_line_count ((GtkTextBuffer*) self->priv->_buffer) > (line_ix + 1);
	} else {
		_tmp0 = FALSE;
	}
	if (_tmp0) {
		gtk_mate_scope_inner_end_mark_set (scope, line_ix + 1, 0, TRUE);
	} else {
		gtk_mate_scope_inner_end_mark_set (scope, line_ix, MIN (to, length), TRUE);
	}
}


void gtk_mate_parser_set_end_mark_safely (GtkMateParser* self, GtkMateScope* scope, GtkMateMarker* m, gint line_ix, gint length, gint cap) {
	gint to;
	gboolean _tmp0;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	g_return_if_fail (m != NULL);
	to = onig_match_end (m->match, cap);
	_tmp0 = FALSE;
	if (to == length) {
		_tmp0 = gtk_text_buffer_get_line_count ((GtkTextBuffer*) self->priv->_buffer) > (line_ix + 1);
	} else {
		_tmp0 = FALSE;
	}
	if (_tmp0) {
		gtk_mate_scope_end_mark_set (scope, line_ix + 1, 0, TRUE);
	} else {
		gtk_mate_scope_end_mark_set (scope, line_ix, MIN (to, length), TRUE);
	}
}


void gtk_mate_parser_collect_child_captures (GtkMateParser* self, gint line_ix, gint length, GtkMateScope* scope, GtkMateMarker* m, GeeArrayList* all_scopes, GeeArrayList* closed_scopes) {
	GtkMateScope* s;
	GeeHashMap* captures;
	GeeArrayList* capture_scopes;
	gint best_length;
	gint new_length;
	GeeArrayList* placed_scopes;
	GtkMateScope* parent_scope;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	g_return_if_fail (m != NULL);
	g_return_if_fail (all_scopes != NULL);
	g_return_if_fail (closed_scopes != NULL);
	s = NULL;
	captures = NULL;
	if (GTK_MATE_IS_SINGLE_PATTERN (m->pattern)) {
		GeeHashMap* _tmp1;
		GeeHashMap* _tmp0;
		_tmp1 = NULL;
		_tmp0 = NULL;
		captures = (_tmp1 = (_tmp0 = GTK_MATE_SINGLE_PATTERN (m->pattern)->captures, (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0)), (captures == NULL) ? NULL : (captures = (g_object_unref (captures), NULL)), _tmp1);
	} else {
		if (m->is_close_scope) {
			GeeHashMap* _tmp3;
			GeeHashMap* _tmp2;
			_tmp3 = NULL;
			_tmp2 = NULL;
			captures = (_tmp3 = (_tmp2 = GTK_MATE_DOUBLE_PATTERN (m->pattern)->end_captures, (_tmp2 == NULL) ? NULL : g_object_ref (_tmp2)), (captures == NULL) ? NULL : (captures = (g_object_unref (captures), NULL)), _tmp3);
		} else {
			GeeHashMap* _tmp5;
			GeeHashMap* _tmp4;
			_tmp5 = NULL;
			_tmp4 = NULL;
			captures = (_tmp5 = (_tmp4 = GTK_MATE_DOUBLE_PATTERN (m->pattern)->begin_captures, (_tmp4 == NULL) ? NULL : g_object_ref (_tmp4)), (captures == NULL) ? NULL : (captures = (g_object_unref (captures), NULL)), _tmp5);
		}
		if (GTK_MATE_DOUBLE_PATTERN (m->pattern)->both_captures != NULL) {
			GeeHashMap* _tmp7;
			GeeHashMap* _tmp6;
			_tmp7 = NULL;
			_tmp6 = NULL;
			captures = (_tmp7 = (_tmp6 = GTK_MATE_DOUBLE_PATTERN (m->pattern)->both_captures, (_tmp6 == NULL) ? NULL : g_object_ref (_tmp6)), (captures == NULL) ? NULL : (captures = (g_object_unref (captures), NULL)), _tmp7);
		}
	}
	capture_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	/* create capture scopes*/
	if (captures != NULL) {
		{
			GeeSet* _tmp8;
			GeeIterator* _tmp9;
			GeeIterator* _cap_it;
			_tmp8 = NULL;
			_tmp9 = NULL;
			_cap_it = (_tmp9 = gee_iterable_iterator ((GeeIterable*) (_tmp8 = gee_map_get_keys ((GeeMap*) captures))), (_tmp8 == NULL) ? NULL : (_tmp8 = (g_object_unref (_tmp8), NULL)), _tmp9);
			while (gee_iterator_next (_cap_it)) {
				gint cap;
				cap = GPOINTER_TO_INT (gee_iterator_get (_cap_it));
				if (onig_match_begin (m->match, cap) != (-1)) {
					GtkMateScope* _tmp11;
					char* _tmp10;
					GtkMatePattern* _tmp13;
					GtkMatePattern* _tmp12;
					GtkMateScope* _tmp15;
					GtkMateScope* _tmp14;
					_tmp11 = NULL;
					_tmp10 = NULL;
					s = (_tmp11 = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, _tmp10 = (char*) gee_map_get ((GeeMap*) captures, GINT_TO_POINTER (cap)))), (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), _tmp11);
					_tmp10 = (g_free (_tmp10), NULL);
					_tmp13 = NULL;
					_tmp12 = NULL;
					s->pattern = (_tmp13 = (_tmp12 = scope->pattern, (_tmp12 == NULL) ? NULL : g_object_ref (_tmp12)), (s->pattern == NULL) ? NULL : (s->pattern = (g_object_unref (s->pattern), NULL)), _tmp13);
					gtk_mate_scope_start_mark_set (s, line_ix, MIN (onig_match_begin (m->match, cap), length - 1), FALSE);
					gtk_mate_parser_set_end_mark_safely (self, s, m, line_ix, length, cap);
					s->is_open = FALSE;
					s->is_capture = TRUE;
					_tmp15 = NULL;
					_tmp14 = NULL;
					s->parent = (_tmp15 = (_tmp14 = scope, (_tmp14 == NULL) ? NULL : g_object_ref (_tmp14)), (s->parent == NULL) ? NULL : (s->parent = (g_object_unref (s->parent), NULL)), _tmp15);
					gee_collection_add ((GeeCollection*) capture_scopes, s);
					gee_collection_add ((GeeCollection*) all_scopes, s);
					gee_collection_add ((GeeCollection*) closed_scopes, s);
				}
			}
			(_cap_it == NULL) ? NULL : (_cap_it = (g_object_unref (_cap_it), NULL));
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
	placed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	parent_scope = NULL;
	while (gee_collection_get_size ((GeeCollection*) capture_scopes) > 0) {
		GtkMateScope* _tmp16;
		GtkMateScope* _tmp21;
		_tmp16 = NULL;
		s = (_tmp16 = NULL, (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), _tmp16);
		/* find first and longest remaining scope (put it in 's')*/
		{
			GeeIterator* _cs_it;
			/* find first and longest remaining scope (put it in 's')*/
			_cs_it = gee_iterable_iterator ((GeeIterable*) capture_scopes);
			/* find first and longest remaining scope (put it in 's')*/
			while (gee_iterator_next (_cs_it)) {
				GtkMateScope* cs;
				gboolean _tmp17;
				/* find first and longest remaining scope (put it in 's')*/
				cs = (GtkMateScope*) gee_iterator_get (_cs_it);
				new_length = gtk_mate_scope_end_offset (cs) - gtk_mate_scope_start_offset (cs);
				_tmp17 = FALSE;
				if (s == NULL) {
					_tmp17 = TRUE;
				} else {
					gboolean _tmp18;
					_tmp18 = FALSE;
					if (gtk_mate_scope_start_offset (cs) < gtk_mate_scope_start_offset (s)) {
						_tmp18 = new_length >= best_length;
					} else {
						_tmp18 = FALSE;
					}
					_tmp17 = _tmp18;
				}
				if (_tmp17) {
					GtkMateScope* _tmp20;
					GtkMateScope* _tmp19;
					_tmp20 = NULL;
					_tmp19 = NULL;
					s = (_tmp20 = (_tmp19 = cs, (_tmp19 == NULL) ? NULL : g_object_ref (_tmp19)), (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), _tmp20);
					best_length = new_length;
				}
				(cs == NULL) ? NULL : (cs = (g_object_unref (cs), NULL));
			}
			(_cs_it == NULL) ? NULL : (_cs_it = (g_object_unref (_cs_it), NULL));
		}
		/* look for somewhere to put it from placed_scopes*/
		_tmp21 = NULL;
		parent_scope = (_tmp21 = NULL, (parent_scope == NULL) ? NULL : (parent_scope = (g_object_unref (parent_scope), NULL)), _tmp21);
		{
			GeeIterator* _ps_it;
			_ps_it = gee_iterable_iterator ((GeeIterable*) placed_scopes);
			while (gee_iterator_next (_ps_it)) {
				GtkMateScope* ps;
				gboolean _tmp22;
				ps = (GtkMateScope*) gee_iterator_get (_ps_it);
				_tmp22 = FALSE;
				if (gtk_mate_scope_start_offset (s) >= gtk_mate_scope_start_offset (ps)) {
					_tmp22 = gtk_mate_scope_end_offset (s) <= gtk_mate_scope_end_offset (ps);
				} else {
					_tmp22 = FALSE;
				}
				if (_tmp22) {
					GtkMateScope* _tmp24;
					GtkMateScope* _tmp23;
					_tmp24 = NULL;
					_tmp23 = NULL;
					parent_scope = (_tmp24 = (_tmp23 = ps, (_tmp23 == NULL) ? NULL : g_object_ref (_tmp23)), (parent_scope == NULL) ? NULL : (parent_scope = (g_object_unref (parent_scope), NULL)), _tmp24);
				}
				(ps == NULL) ? NULL : (ps = (g_object_unref (ps), NULL));
			}
			(_ps_it == NULL) ? NULL : (_ps_it = (g_object_unref (_ps_it), NULL));
		}
		if (parent_scope != NULL) {
			GtkMateScope* _tmp25;
			GtkMateScope* _tmp27;
			GtkMateScope* _tmp26;
			_tmp25 = NULL;
			g_sequence_append (gtk_mate_scope_get_children (parent_scope), (_tmp25 = s, (_tmp25 == NULL) ? NULL : g_object_ref (_tmp25)));
			_tmp27 = NULL;
			_tmp26 = NULL;
			s->parent = (_tmp27 = (_tmp26 = parent_scope, (_tmp26 == NULL) ? NULL : g_object_ref (_tmp26)), (s->parent == NULL) ? NULL : (s->parent = (g_object_unref (s->parent), NULL)), _tmp27);
		} else {
			GtkMateScope* _tmp28;
			_tmp28 = NULL;
			g_sequence_append (gtk_mate_scope_get_children (scope), (_tmp28 = s, (_tmp28 == NULL) ? NULL : g_object_ref (_tmp28)));
		}
		gee_collection_add ((GeeCollection*) placed_scopes, s);
		gee_collection_remove ((GeeCollection*) capture_scopes, s);
	}
	(s == NULL) ? NULL : (s = (g_object_unref (s), NULL));
	(captures == NULL) ? NULL : (captures = (g_object_unref (captures), NULL));
	(capture_scopes == NULL) ? NULL : (capture_scopes = (g_object_unref (capture_scopes), NULL));
	(placed_scopes == NULL) ? NULL : (placed_scopes = (g_object_unref (placed_scopes), NULL));
	(parent_scope == NULL) ? NULL : (parent_scope = (g_object_unref (parent_scope), NULL));
}


void gtk_mate_parser_reset_table_priorities (GtkMateParser* self) {
	GSequenceIter* iter;
	gint i;
	g_return_if_fail (self != NULL);
	/* stdout.printf("\nreset_table_priorities() for %d tags\n", buffer.get_tag_table().get_size());*/
	iter = g_sequence_get_begin_iter (self->tags);
	i = 0;
	while (!g_sequence_iter_is_end (g_sequence_iter_next (iter))) {
		GtkTextTag* _tmp0;
		GtkTextTag* t;
		_tmp0 = NULL;
		t = (_tmp0 = (GtkTextTag*) g_sequence_get (iter), (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
		gtk_text_tag_set_priority (t, i);
		/* stdout.printf("tag: '%s', pri: %d\n", t.name, i);*/
		i++;
		iter = g_sequence_iter_next (iter);
		(t == NULL) ? NULL : (t = (g_object_unref (t), NULL));
	}
}


void gtk_mate_parser_remove_tags (GtkMateParser* self) {
	GSequenceIter* iter;
	GtkTextTagTable* _tmp0;
	GtkTextTagTable* table;
	g_return_if_fail (self != NULL);
	iter = g_sequence_get_begin_iter (self->tags);
	_tmp0 = NULL;
	table = (_tmp0 = gtk_text_buffer_get_tag_table ((GtkTextBuffer*) self->priv->_buffer), (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
	while (!g_sequence_iter_is_end (iter)) {
		gtk_text_tag_table_remove (table, (GtkTextTag*) g_sequence_get (iter));
		iter = g_sequence_iter_next (iter);
	}
	g_sequence_remove_range (g_sequence_get_begin_iter (self->tags), g_sequence_get_end_iter (self->tags));
	(table == NULL) ? NULL : (table = (g_object_unref (table), NULL));
}


void gtk_mate_parser_change_theme (GtkMateParser* self, GtkMateTheme* theme) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (theme != NULL);
	/* stdout.printf("parser.change_theme(%s)\n", theme.name);*/
	gtk_mate_colourer_uncolour_scope (self->priv->_colourer, self->root, TRUE);
	gtk_mate_colourer_set_theme (self->priv->_colourer, theme);
	gtk_mate_parser_remove_tags (self);
	gtk_mate_parser_recolour_children (self, self->root);
}


/* stdout.printf("parser.change_theme(%s):out\n", theme.name);*/
void gtk_mate_parser_recolour_children (GtkMateParser* self, GtkMateScope* scope) {
	GSequenceIter* iter;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	iter = g_sequence_get_begin_iter (gtk_mate_scope_get_children (scope));
	while (!g_sequence_iter_is_end (iter)) {
		GtkMateScope* _tmp0;
		GtkMateScope* child;
		gboolean _tmp1;
		gboolean _tmp2;
		_tmp0 = NULL;
		child = (_tmp0 = (GtkMateScope*) g_sequence_get (iter), (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
		gtk_mate_colourer_colour_scope (self->priv->_colourer, child, FALSE, TRUE);
		_tmp1 = FALSE;
		_tmp2 = FALSE;
		if (GTK_MATE_IS_DOUBLE_PATTERN (child->pattern)) {
			_tmp2 = GTK_MATE_DOUBLE_PATTERN (child->pattern)->content_name != NULL;
		} else {
			_tmp2 = FALSE;
		}
		if (_tmp2) {
			_tmp1 = child->is_capture == FALSE;
		} else {
			_tmp1 = FALSE;
		}
		if (_tmp1) {
			gtk_mate_colourer_colour_scope (self->priv->_colourer, child, TRUE, TRUE);
		}
		gtk_mate_parser_recolour_children (self, child);
		iter = g_sequence_iter_next (iter);
		(child == NULL) ? NULL : (child = (g_object_unref (child), NULL));
	}
}


void gtk_mate_parser_last_visible_line_changed (GtkMateParser* self, gint new_last_visible_line) {
	g_return_if_fail (self != NULL);
	self->last_visible_line = new_last_visible_line;
	/* stdout.printf("last_visible_line: %d\n", last_visible_line);
	 stdout.printf("already_parsed_upto: %d\n", parsed_upto);*/
	if ((self->last_visible_line + self->priv->_look_ahead) >= self->parsed_upto) {
		gint end_range;
		end_range = MIN (gtk_text_buffer_get_line_count ((GtkTextBuffer*) self->priv->_buffer) - 1, self->last_visible_line + self->priv->_look_ahead);
		/* stdout.printf("parse_range(%d, %d)\n", parsed_upto, end_range);*/
		gtk_mate_parser_parse_range (self, self->parsed_upto, end_range);
	}
}


gint gtk_mate_parser_last_line_parsed (GtkMateParser* self) {
	g_return_val_if_fail (self != NULL, 0);
	/*GLib.SequenceIter iter = root.children.get_end_iter();
	if (!iter.is_begin()) {
	iter = iter.prev();
	var child = root.children.get(iter);
	return child.end_line();
	}
	else {
	return 0;
	}*/
	return gtk_mate_scope_end_line (self->root);
}


static void _gtk_mate_parser_insert_text_handler_gtk_text_buffer_insert_text (GtkMateBuffer* _sender, const GtkTextIter* pos, const char* text, gint length, gpointer self) {
	gtk_mate_parser_insert_text_handler (self, _sender, pos, text, length);
}


static void _gtk_mate_parser_delete_range_handler_gtk_text_buffer_delete_range (GtkMateBuffer* _sender, const GtkTextIter* start, const GtkTextIter* end, gpointer self) {
	gtk_mate_parser_delete_range_handler (self, _sender, start, end);
}


void gtk_mate_parser_connect_buffer_signals (GtkMateParser* self) {
	g_return_if_fail (self != NULL);
	g_signal_connect_object ((GtkTextBuffer*) self->priv->_buffer, "insert-text", (GCallback) _gtk_mate_parser_insert_text_handler_gtk_text_buffer_insert_text, self, 0);
	g_signal_connect_object ((GtkTextBuffer*) self->priv->_buffer, "delete-range", (GCallback) _gtk_mate_parser_delete_range_handler_gtk_text_buffer_delete_range, self, 0);
	/* buffer.get_tag_table().tag_added += this.tag_added_handler;
	 remove when signal_connect_after works:*/
	g_signal_connect_after (self->priv->_buffer, "insert_text", (GCallback) gtk_mate_parser_static_insert_text_after_handler, NULL);
	g_signal_connect_after (self->priv->_buffer, "delete_range", (GCallback) gtk_mate_parser_static_delete_range_after_handler, NULL);
}


/* Signal.connect_after(buffer.get_tag_table(), "tag_added", 
  (GLib.Callback) Parser.static_tag_added_after_handler, null);*/
void gtk_mate_parser_insert_text_handler (GtkMateParser* self, GtkMateBuffer* bf, const GtkTextIter* pos, const char* text, gint length) {
	char** _tmp1;
	gint ss_size;
	gint ss_length1;
	char** _tmp0;
	char** ss;
	gint num_lines;
	g_return_if_fail (self != NULL);
	g_return_if_fail (bf != NULL);
	g_return_if_fail (text != NULL);
	/*//stdout.printf("insert_text(pos, \"%s\", %d)\n", text, length);*/
	_tmp1 = NULL;
	_tmp0 = NULL;
	ss = (_tmp1 = _tmp0 = g_strsplit (text, "\n", 0), ss_length1 = _vala_array_length (_tmp0), ss_size = ss_length1, _tmp1);
	num_lines = -1;
	{
		char** s_collection;
		int s_collection_length1;
		int s_it;
		s_collection = ss;
		s_collection_length1 = ss_length1;
		for (s_it = 0; s_it < ss_length1; s_it = s_it + 1) {
			const char* _tmp2;
			char* s;
			_tmp2 = NULL;
			s = (_tmp2 = s_collection[s_it], (_tmp2 == NULL) ? NULL : g_strdup (_tmp2));
			{
				num_lines++;
				s = (g_free (s), NULL);
			}
		}
	}
	/*//stdout.printf("add_change(%d, %d)\n", pos.get_line(), pos.get_line() + num_lines);*/
	range_set_add (self->changes, gtk_text_iter_get_line (&(*pos)), gtk_text_iter_get_line (&(*pos)) + num_lines);
	ss = (_vala_array_free (ss, ss_length1, (GDestroyNotify) g_free), NULL);
}


void gtk_mate_parser_delete_range_handler (GtkMateParser* self, GtkMateBuffer* bf, const GtkTextIter* pos, const GtkTextIter* pos2) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (bf != NULL);
	/*//stdout.printf("delete_range(%d, %d)\n", pos.get_offset(), pos2.get_offset());*/
	range_set_add (self->changes, gtk_text_iter_get_line (&(*pos)), gtk_text_iter_get_line (&(*pos)));
}


void gtk_mate_parser_insert_text_after_handler (GtkMateParser* self, GtkMateBuffer* bf, const GtkTextIter* pos, const char* text, gint length) {
	gboolean _tmp0;
	g_return_if_fail (self != NULL);
	g_return_if_fail (bf != NULL);
	g_return_if_fail (text != NULL);
	_tmp0 = FALSE;
	if (gtk_mate_parser_is_parsing (self)) {
		_tmp0 = !range_set_is_empty (self->changes);
	} else {
		_tmp0 = FALSE;
	}
	if (_tmp0) {
		gtk_mate_parser_process_changes (self);
	}
}


void gtk_mate_parser_delete_range_after_handler (GtkMateParser* self, GtkMateBuffer* bf, const GtkTextIter* pos, const GtkTextIter* pos2) {
	gboolean _tmp0;
	g_return_if_fail (self != NULL);
	g_return_if_fail (bf != NULL);
	_tmp0 = FALSE;
	if (gtk_mate_parser_is_parsing (self)) {
		_tmp0 = !range_set_is_empty (self->changes);
	} else {
		_tmp0 = FALSE;
	}
	if (_tmp0) {
		gtk_mate_parser_process_changes (self);
	}
}


void gtk_mate_parser_static_insert_text_after_handler (GtkMateBuffer* bf, const GtkTextIter* pos, const char* text, gint length) {
	g_return_if_fail (bf != NULL);
	g_return_if_fail (text != NULL);
	{
		GeeIterator* _parser_it;
		_parser_it = gee_iterable_iterator ((GeeIterable*) gtk_mate_parser_existing_parsers);
		while (gee_iterator_next (_parser_it)) {
			GtkMateParser* parser;
			parser = (GtkMateParser*) gee_iterator_get (_parser_it);
			gtk_mate_parser_insert_text_after_handler (parser, bf, &(*pos), text, length);
			(parser == NULL) ? NULL : (parser = (g_object_unref (parser), NULL));
		}
		(_parser_it == NULL) ? NULL : (_parser_it = (g_object_unref (_parser_it), NULL));
	}
}


void gtk_mate_parser_static_delete_range_after_handler (GtkMateBuffer* bf, const GtkTextIter* pos, const GtkTextIter* pos2) {
	g_return_if_fail (bf != NULL);
	{
		GeeIterator* _parser_it;
		_parser_it = gee_iterable_iterator ((GeeIterable*) gtk_mate_parser_existing_parsers);
		while (gee_iterator_next (_parser_it)) {
			GtkMateParser* parser;
			parser = (GtkMateParser*) gee_iterator_get (_parser_it);
			gtk_mate_parser_delete_range_after_handler (parser, bf, &(*pos), &(*pos2));
			(parser == NULL) ? NULL : (parser = (g_object_unref (parser), NULL));
		}
		(_parser_it == NULL) ? NULL : (_parser_it = (g_object_unref (_parser_it), NULL));
	}
}


void gtk_mate_parser_added_tag (GtkMateParser* self, GtkTextTag* tag) {
	gboolean _tmp0;
	char* _tmp2;
	char* _tmp1;
	gboolean _tmp3;
	g_return_if_fail (self != NULL);
	g_return_if_fail (tag != NULL);
	_tmp0 = FALSE;
	_tmp2 = NULL;
	_tmp1 = NULL;
	if ((_tmp3 = (_tmp2 = (g_object_get (tag, "name", &_tmp1, NULL), _tmp1)) != NULL, _tmp2 = (g_free (_tmp2), NULL), _tmp3)) {
		char* _tmp5;
		char* _tmp4;
		_tmp5 = NULL;
		_tmp4 = NULL;
		_tmp0 = g_str_has_prefix (_tmp5 = (g_object_get (tag, "name", &_tmp4, NULL), _tmp4), "gmv(");
		_tmp5 = (g_free (_tmp5), NULL);
	} else {
		_tmp0 = FALSE;
	}
	if (_tmp0) {
		GtkTextTag* _tmp6;
		_tmp6 = NULL;
		g_sequence_insert_sorted (self->tags, (_tmp6 = tag, (_tmp6 == NULL) ? NULL : g_object_ref (_tmp6)), (GCompareDataFunc) gtk_mate_parser_tag_compare, NULL);
	}
	gtk_mate_parser_reset_table_priorities (self);
}


gint gtk_mate_parser_tag_compare (GtkTextTag* tag1, GtkTextTag* tag2, void* data) {
	char* _tmp1;
	char* _tmp0;
	gint _tmp2;
	gint pri1;
	char* _tmp4;
	char* _tmp3;
	gint _tmp5;
	gint pri2;
	g_return_val_if_fail (tag1 != NULL, 0);
	g_return_val_if_fail (tag2 != NULL, 0);
	_tmp1 = NULL;
	_tmp0 = NULL;
	pri1 = (_tmp2 = g_unichar_digit_value (g_utf8_get_char (g_utf8_offset_to_pointer (_tmp1 = (g_object_get (tag1, "name", &_tmp0, NULL), _tmp0), 4))), _tmp1 = (g_free (_tmp1), NULL), _tmp2);
	_tmp4 = NULL;
	_tmp3 = NULL;
	pri2 = (_tmp5 = g_unichar_digit_value (g_utf8_get_char (g_utf8_offset_to_pointer (_tmp4 = (g_object_get (tag2, "name", &_tmp3, NULL), _tmp3), 4))), _tmp4 = (g_free (_tmp4), NULL), _tmp5);
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
	g_return_if_fail (self != NULL);
	gee_collection_remove ((GeeCollection*) gtk_mate_parser_existing_parsers, self);
}


GtkMateParser* gtk_mate_parser_create (GtkMateGrammar* grammar, GtkMateBuffer* buffer) {
	GtkMateParser* p;
	GSequence* _tmp1;
	RangeSet* _tmp2;
	GtkMateColourer* _tmp3;
	g_return_val_if_fail (grammar != NULL, NULL);
	g_return_val_if_fail (buffer != NULL, NULL);
	gtk_mate_grammar_init_for_use (grammar);
	p = g_object_ref_sink (gtk_mate_parser_new ());
	/* remove when signal_connect_after works:*/
	if (gtk_mate_parser_existing_parsers == NULL) {
		GeeArrayList* _tmp0;
		_tmp0 = NULL;
		gtk_mate_parser_existing_parsers = (_tmp0 = gee_array_list_new (GTK_MATE_TYPE_PARSER, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (gtk_mate_parser_existing_parsers == NULL) ? NULL : (gtk_mate_parser_existing_parsers = (g_object_unref (gtk_mate_parser_existing_parsers), NULL)), _tmp0);
	}
	gee_collection_add ((GeeCollection*) gtk_mate_parser_existing_parsers, p);
	gtk_mate_parser_set_look_ahead (p, 100);
	p->last_visible_line = 0;
	gtk_mate_parser_set_grammar (p, grammar);
	gtk_mate_parser_set_buffer (p, buffer);
	_tmp1 = NULL;
	p->tags = (_tmp1 = g_sequence_new (NULL), (p->tags == NULL) ? NULL : (p->tags = (g_sequence_free (p->tags), NULL)), _tmp1);
	_tmp2 = NULL;
	p->changes = (_tmp2 = range_set_new (), (p->changes == NULL) ? NULL : (p->changes = (g_object_unref (p->changes), NULL)), _tmp2);
	_tmp3 = NULL;
	gtk_mate_parser_set_colourer (p, _tmp3 = g_object_ref_sink (gtk_mate_colourer_new (buffer)));
	(_tmp3 == NULL) ? NULL : (_tmp3 = (g_object_unref (_tmp3), NULL));
	p->deactivation_level = 0;
	gtk_mate_parser_make_root (p);
	gtk_mate_parser_connect_buffer_signals (p);
	p->parsed_upto = 0;
	p->always_parse_all = FALSE;
	return p;
}


GtkMateParser* gtk_mate_parser_construct (GType object_type) {
	GtkMateParser * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


GtkMateParser* gtk_mate_parser_new (void) {
	return gtk_mate_parser_construct (GTK_MATE_TYPE_PARSER);
}


GtkMateGrammar* gtk_mate_parser_get_grammar (GtkMateParser* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_grammar;
}


void gtk_mate_parser_set_grammar (GtkMateParser* self, GtkMateGrammar* value) {
	GtkMateGrammar* _tmp2;
	GtkMateGrammar* _tmp1;
	g_return_if_fail (self != NULL);
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_grammar = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL) ? NULL : g_object_ref (_tmp1)), (self->priv->_grammar == NULL) ? NULL : (self->priv->_grammar = (g_object_unref (self->priv->_grammar), NULL)), _tmp2);
	g_object_notify ((GObject *) self, "grammar");
}


GtkMateColourer* gtk_mate_parser_get_colourer (GtkMateParser* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_colourer;
}


void gtk_mate_parser_set_colourer (GtkMateParser* self, GtkMateColourer* value) {
	GtkMateColourer* _tmp2;
	GtkMateColourer* _tmp1;
	g_return_if_fail (self != NULL);
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_colourer = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL) ? NULL : g_object_ref (_tmp1)), (self->priv->_colourer == NULL) ? NULL : (self->priv->_colourer = (g_object_unref (self->priv->_colourer), NULL)), _tmp2);
	g_object_notify ((GObject *) self, "colourer");
}


GtkMateBuffer* gtk_mate_parser_get_buffer (GtkMateParser* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_buffer;
}


void gtk_mate_parser_set_buffer (GtkMateParser* self, GtkMateBuffer* value) {
	GtkMateBuffer* _tmp2;
	GtkMateBuffer* _tmp1;
	g_return_if_fail (self != NULL);
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_buffer = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL) ? NULL : g_object_ref (_tmp1)), (self->priv->_buffer == NULL) ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL)), _tmp2);
	g_object_notify ((GObject *) self, "buffer");
}


gint gtk_mate_parser_get_look_ahead (GtkMateParser* self) {
	g_return_val_if_fail (self != NULL, 0);
	return self->priv->_look_ahead;
}


void gtk_mate_parser_set_look_ahead (GtkMateParser* self, gint value) {
	g_return_if_fail (self != NULL);
	self->priv->_look_ahead = value;
	g_object_notify ((GObject *) self, "look-ahead");
}


static void gtk_mate_parser_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateParser * self;
	gpointer boxed;
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
		case GTK_MATE_PARSER_LOOK_AHEAD:
		g_value_set_int (value, gtk_mate_parser_get_look_ahead (self));
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
		case GTK_MATE_PARSER_LOOK_AHEAD:
		gtk_mate_parser_set_look_ahead (self, g_value_get_int (value));
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
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_PARSER_LOOK_AHEAD, g_param_spec_int ("look-ahead", "look-ahead", "look-ahead", G_MININT, G_MAXINT, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void gtk_mate_parser_instance_init (GtkMateParser * self) {
	self->priv = GTK_MATE_PARSER_GET_PRIVATE (self);
}


static void gtk_mate_parser_finalize (GObject* obj) {
	GtkMateParser * self;
	self = GTK_MATE_PARSER (obj);
	(self->priv->_grammar == NULL) ? NULL : (self->priv->_grammar = (g_object_unref (self->priv->_grammar), NULL));
	(self->priv->_colourer == NULL) ? NULL : (self->priv->_colourer = (g_object_unref (self->priv->_colourer), NULL));
	(self->priv->_buffer == NULL) ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL));
	(self->root == NULL) ? NULL : (self->root = (g_object_unref (self->root), NULL));
	(self->dummy_tag == NULL) ? NULL : (self->dummy_tag = (g_object_unref (self->dummy_tag), NULL));
	(self->dummy_tag2 == NULL) ? NULL : (self->dummy_tag2 = (g_object_unref (self->dummy_tag2), NULL));
	(self->tags == NULL) ? NULL : (self->tags = (g_sequence_free (self->tags), NULL));
	(self->changes == NULL) ? NULL : (self->changes = (g_object_unref (self->changes), NULL));
	G_OBJECT_CLASS (gtk_mate_parser_parent_class)->finalize (obj);
}


GType gtk_mate_parser_get_type (void) {
	static GType gtk_mate_parser_type_id = 0;
	if (gtk_mate_parser_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateParserClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_parser_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateParser), 0, (GInstanceInitFunc) gtk_mate_parser_instance_init, NULL };
		gtk_mate_parser_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateParser", &g_define_type_info, 0);
	}
	return gtk_mate_parser_type_id;
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
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


static int _vala_strcmp0 (const char * str1, const char * str2) {
	if (str1 == NULL) {
		return -(str1 != str2);
	}
	if (str2 == NULL) {
		return str1 != str2;
	}
	return strcmp (str1, str2);
}




