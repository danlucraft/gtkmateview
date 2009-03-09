
#include "buffer.h"
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>
#include "parser.h"
#include "grammar.h"
#include "bundle.h"
#include "onig_wrap.h"
#include "scope.h"
#include "gtkmateview.h"




static char* string_substring (const char* self, glong offset, glong len);
static glong string_get_length (const char* self);
enum  {
	GTK_MATE_BUFFER_DUMMY_PROPERTY
};
GeeArrayList* gtk_mate_buffer_bundles = NULL;
GeeArrayList* gtk_mate_buffer_themes = NULL;
static GObject * gtk_mate_buffer_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer gtk_mate_buffer_parent_class = NULL;
static void gtk_mate_buffer_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



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


static glong string_get_length (const char* self) {
	g_return_val_if_fail (self != NULL, 0L);
	return g_utf8_strlen (self, -1);
}


/* Sets the grammar explicitly by name.*/
gboolean gtk_mate_buffer_set_grammar_by_name (GtkMateBuffer* self, const char* name) {
	gboolean _tmp0;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (name != NULL, FALSE);
	_tmp0 = FALSE;
	if (self->parser != NULL) {
		_tmp0 = _vala_strcmp0 (gtk_mate_grammar_get_name (gtk_mate_parser_get_grammar (self->parser)), name) == 0;
	} else {
		_tmp0 = FALSE;
	}
	if (_tmp0) {
		return TRUE;
	}
	{
		GeeIterator* _bundle_it;
		_bundle_it = gee_iterable_iterator ((GeeIterable*) gtk_mate_buffer_bundles);
		while (gee_iterator_next (_bundle_it)) {
			GtkMateBundle* bundle;
			bundle = (GtkMateBundle*) gee_iterator_get (_bundle_it);
			{
				GeeIterator* _gr_it;
				_gr_it = gee_iterable_iterator ((GeeIterable*) bundle->grammars);
				while (gee_iterator_next (_gr_it)) {
					GtkMateGrammar* gr;
					gr = (GtkMateGrammar*) gee_iterator_get (_gr_it);
					if (_vala_strcmp0 (gtk_mate_grammar_get_name (gr), name) == 0) {
						GtkMateParser* _tmp2;
						gboolean _tmp3;
						if (self->parser != NULL) {
							gtk_mate_parser_close (self->parser);
						}
						_tmp2 = NULL;
						self->parser = (_tmp2 = gtk_mate_parser_create (gr, self), (self->parser == NULL) ? NULL : (self->parser = (g_object_unref (self->parser), NULL)), _tmp2);
						return (_tmp3 = TRUE, (gr == NULL) ? NULL : (gr = (g_object_unref (gr), NULL)), (_gr_it == NULL) ? NULL : (_gr_it = (g_object_unref (_gr_it), NULL)), (bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL)), (_bundle_it == NULL) ? NULL : (_bundle_it = (g_object_unref (_bundle_it), NULL)), _tmp3);
					}
					(gr == NULL) ? NULL : (gr = (g_object_unref (gr), NULL));
				}
				(_gr_it == NULL) ? NULL : (_gr_it = (g_object_unref (_gr_it), NULL));
			}
			(bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL));
		}
		(_bundle_it == NULL) ? NULL : (_bundle_it = (g_object_unref (_bundle_it), NULL));
	}
	return FALSE;
}


/* Sets the grammar by the file extension. If unable to find
 a grammar, sets the grammar to null. Returns the grammar
 name or null.*/
char* gtk_mate_buffer_set_grammar_by_filename (GtkMateBuffer* self, const char* filename) {
	GtkMateGrammar* best;
	glong best_length;
	char* _tmp9;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (filename != NULL, NULL);
	best = NULL;
	best_length = (glong) 0;
	{
		GeeIterator* _bundle_it;
		_bundle_it = gee_iterable_iterator ((GeeIterable*) gtk_mate_buffer_bundles);
		while (gee_iterator_next (_bundle_it)) {
			GtkMateBundle* bundle;
			bundle = (GtkMateBundle*) gee_iterator_get (_bundle_it);
			{
				GeeIterator* _gr_it;
				_gr_it = gee_iterable_iterator ((GeeIterable*) bundle->grammars);
				while (gee_iterator_next (_gr_it)) {
					GtkMateGrammar* gr;
					gr = (GtkMateGrammar*) gee_iterator_get (_gr_it);
					{
						char** ext_collection;
						int ext_collection_length1;
						int ext_it;
						ext_collection = gr->file_types;
						ext_collection_length1 = gr->file_types_length1;
						for (ext_it = 0; ext_it < gr->file_types_length1; ext_it = ext_it + 1) {
							const char* _tmp4;
							char* ext;
							_tmp4 = NULL;
							ext = (_tmp4 = ext_collection[ext_it], (_tmp4 == NULL) ? NULL : g_strdup (_tmp4));
							{
								gboolean _tmp0;
								_tmp0 = FALSE;
								if (g_str_has_suffix (filename, ext)) {
									gboolean _tmp1;
									_tmp1 = FALSE;
									if (best == NULL) {
										_tmp1 = TRUE;
									} else {
										_tmp1 = string_get_length (ext) > best_length;
									}
									_tmp0 = _tmp1;
								} else {
									_tmp0 = FALSE;
								}
								if (_tmp0) {
									GtkMateGrammar* _tmp3;
									GtkMateGrammar* _tmp2;
									_tmp3 = NULL;
									_tmp2 = NULL;
									best = (_tmp3 = (_tmp2 = gr, (_tmp2 == NULL) ? NULL : g_object_ref (_tmp2)), (best == NULL) ? NULL : (best = (g_object_unref (best), NULL)), _tmp3);
									best_length = string_get_length (ext);
								}
								ext = (g_free (ext), NULL);
							}
						}
					}
					(gr == NULL) ? NULL : (gr = (g_object_unref (gr), NULL));
				}
				(_gr_it == NULL) ? NULL : (_gr_it = (g_object_unref (_gr_it), NULL));
			}
			(bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL));
		}
		(_bundle_it == NULL) ? NULL : (_bundle_it = (g_object_unref (_bundle_it), NULL));
	}
	if (best != NULL) {
		gboolean _tmp5;
		const char* _tmp7;
		char* _tmp8;
		_tmp5 = FALSE;
		if (self->parser == NULL) {
			_tmp5 = TRUE;
		} else {
			_tmp5 = _vala_strcmp0 (gtk_mate_grammar_get_name (gtk_mate_parser_get_grammar (self->parser)), gtk_mate_grammar_get_name (best)) != 0;
		}
		if (_tmp5) {
			GtkMateParser* _tmp6;
			_tmp6 = NULL;
			self->parser = (_tmp6 = gtk_mate_parser_create (best, self), (self->parser == NULL) ? NULL : (self->parser = (g_object_unref (self->parser), NULL)), _tmp6);
		}
		_tmp7 = NULL;
		_tmp8 = NULL;
		return (_tmp8 = (_tmp7 = gtk_mate_grammar_get_name (best), (_tmp7 == NULL) ? NULL : g_strdup (_tmp7)), (best == NULL) ? NULL : (best = (g_object_unref (best), NULL)), _tmp8);
	}
	_tmp9 = NULL;
	return (_tmp9 = NULL, (best == NULL) ? NULL : (best = (g_object_unref (best), NULL)), _tmp9);
}


/* Sets the grammar by examining the first line. If unable to find
 a grammar, sets the grammar to null. Returns the grammar
 name or null.*/
char* gtk_mate_buffer_set_grammar_by_first_line (GtkMateBuffer* self, const char* first_line) {
	OnigRx* re;
	char* _tmp7;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (first_line != NULL, NULL);
	re = NULL;
	{
		GeeIterator* _bundle_it;
		_bundle_it = gee_iterable_iterator ((GeeIterable*) gtk_mate_buffer_bundles);
		while (gee_iterator_next (_bundle_it)) {
			GtkMateBundle* bundle;
			bundle = (GtkMateBundle*) gee_iterator_get (_bundle_it);
			{
				GeeIterator* _gr_it;
				_gr_it = gee_iterable_iterator ((GeeIterable*) bundle->grammars);
				while (gee_iterator_next (_gr_it)) {
					GtkMateGrammar* gr;
					OnigRx* _tmp1;
					OnigRx* _tmp0;
					gr = (GtkMateGrammar*) gee_iterator_get (_gr_it);
					_tmp1 = NULL;
					_tmp0 = NULL;
					if ((re = (_tmp1 = (_tmp0 = gr->first_line_match, (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0)), (re == NULL) ? NULL : (re = (g_object_unref (re), NULL)), _tmp1)) != NULL) {
						OnigMatch* _tmp2;
						gboolean _tmp3;
						_tmp2 = NULL;
						if ((_tmp3 = (_tmp2 = onig_rx_search (re, first_line, 0, (gint) strlen (first_line))) != NULL, (_tmp2 == NULL) ? NULL : (_tmp2 = (g_object_unref (_tmp2), NULL)), _tmp3)) {
							GtkMateParser* _tmp4;
							const char* _tmp5;
							char* _tmp6;
							_tmp4 = NULL;
							self->parser = (_tmp4 = gtk_mate_parser_create (gr, self), (self->parser == NULL) ? NULL : (self->parser = (g_object_unref (self->parser), NULL)), _tmp4);
							_tmp5 = NULL;
							_tmp6 = NULL;
							return (_tmp6 = (_tmp5 = gtk_mate_grammar_get_name (gr), (_tmp5 == NULL) ? NULL : g_strdup (_tmp5)), (gr == NULL) ? NULL : (gr = (g_object_unref (gr), NULL)), (_gr_it == NULL) ? NULL : (_gr_it = (g_object_unref (_gr_it), NULL)), (bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL)), (_bundle_it == NULL) ? NULL : (_bundle_it = (g_object_unref (_bundle_it), NULL)), (re == NULL) ? NULL : (re = (g_object_unref (re), NULL)), _tmp6);
						}
					}
					(gr == NULL) ? NULL : (gr = (g_object_unref (gr), NULL));
				}
				(_gr_it == NULL) ? NULL : (_gr_it = (g_object_unref (_gr_it), NULL));
			}
			(bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL));
		}
		(_bundle_it == NULL) ? NULL : (_bundle_it = (g_object_unref (_bundle_it), NULL));
	}
	_tmp7 = NULL;
	return (_tmp7 = NULL, (re == NULL) ? NULL : (re = (g_object_unref (re), NULL)), _tmp7);
}


/* HELPER METHODS
 Offset from start of document -> Iter*/
GtkTextIter gtk_mate_buffer_iter_ (GtkMateBuffer* self, gint offset) {
	GtkTextIter i = {0};
	gtk_text_buffer_get_iter_at_offset ((GtkTextBuffer*) self, &i, offset);
	return i;
}


GtkTextIter gtk_mate_buffer_start_iter (GtkMateBuffer* self) {
	GtkTextIter i = {0};
	gtk_text_buffer_get_iter_at_offset ((GtkTextBuffer*) self, &i, 0);
	return i;
}


GtkTextIter gtk_mate_buffer_end_iter (GtkMateBuffer* self) {
	GtkTextIter i = {0};
	gtk_text_buffer_get_iter_at_offset ((GtkTextBuffer*) self, &i, gtk_text_buffer_get_char_count ((GtkTextBuffer*) self));
	return i;
}


GtkTextIter gtk_mate_buffer_cursor_iter (GtkMateBuffer* self) {
	GtkTextIter i = {0};
	GtkTextMark* _tmp0;
	_tmp0 = NULL;
	gtk_text_buffer_get_iter_at_mark ((GtkTextBuffer*) self, &i, _tmp0 = gtk_mate_buffer_cursor_mark (self));
	(_tmp0 == NULL) ? NULL : (_tmp0 = (g_object_unref (_tmp0), NULL));
	return i;
}


GtkTextIter gtk_mate_buffer_iter_from_mark (GtkMateBuffer* self, GtkTextMark* mark) {
	GtkTextIter i = {0};
	gtk_text_buffer_get_iter_at_mark ((GtkTextBuffer*) self, &i, mark);
	return i;
}


GtkTextIter gtk_mate_buffer_iter_at_line_offset (GtkMateBuffer* self, gint line, gint line_offset) {
	GtkTextIter i = {0};
	gtk_text_buffer_get_iter_at_line_offset ((GtkTextBuffer*) self, &i, line, line_offset);
	return i;
}


GtkTextIter gtk_mate_buffer_iter_at_line_index (GtkMateBuffer* self, gint line, gint line_offset) {
	GtkTextIter i = {0};
	gtk_text_buffer_get_iter_at_line_index ((GtkTextBuffer*) self, &i, line, line_offset);
	return i;
}


GtkTextIter gtk_mate_buffer_line_start_iter (GtkMateBuffer* self, gint line) {
	GtkTextIter i = {0};
	gtk_text_buffer_get_iter_at_line ((GtkTextBuffer*) self, &i, line);
	return i;
}


/* Iter at end of line, after the "\n" (if present).*/
GtkTextIter gtk_mate_buffer_line_end_iter (GtkMateBuffer* self, gint line) {
	if (line >= (gtk_text_buffer_get_line_count ((GtkTextBuffer*) self) - 1)) {
		return gtk_mate_buffer_end_iter (self);
	} else {
		return gtk_mate_buffer_line_start_iter (self, line + 1);
	}
}


/* Iter at end of line, before the "\n" (if present).*/
GtkTextIter gtk_mate_buffer_line_end_iter1 (GtkMateBuffer* self, gint line) {
	if (line >= (gtk_text_buffer_get_line_count ((GtkTextBuffer*) self) - 1)) {
		return gtk_mate_buffer_end_iter (self);
	} else {
		GtkTextIter i;
		i = gtk_mate_buffer_line_start_iter (self, line + 1);
		gtk_text_iter_backward_char (&i);
		return i;
	}
}


GtkTextMark* gtk_mate_buffer_start_mark (GtkMateBuffer* self) {
	GtkTextMark* _tmp0;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0 = NULL;
	return (_tmp0 = gtk_text_buffer_get_mark ((GtkTextBuffer*) self, "start_mark"), (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
}


GtkTextMark* gtk_mate_buffer_end_mark (GtkMateBuffer* self) {
	GtkTextMark* _tmp0;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0 = NULL;
	return (_tmp0 = gtk_text_buffer_get_mark ((GtkTextBuffer*) self, "end_mark"), (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
}


GtkTextMark* gtk_mate_buffer_cursor_mark (GtkMateBuffer* self) {
	GtkTextMark* _tmp0;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0 = NULL;
	return (_tmp0 = gtk_text_buffer_get_mark ((GtkTextBuffer*) self, "insert"), (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
}


GtkTextMark* gtk_mate_buffer_selection_mark (GtkMateBuffer* self) {
	GtkTextMark* _tmp0;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0 = NULL;
	return (_tmp0 = gtk_text_buffer_get_mark ((GtkTextBuffer*) self, "selection_bound"), (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
}


/* Get text of line, including the "\n" if present. Returns null if line 
 does not exist.*/
char* gtk_mate_buffer_get_line (GtkMateBuffer* self, gint line) {
	GtkTextIter ei = {0};
	const char* _tmp3;
	GtkTextIter _tmp2 = {0};
	g_return_val_if_fail (self != NULL, NULL);
	if (line == (gtk_text_buffer_get_line_count ((GtkTextBuffer*) self) - 1)) {
		ei = gtk_mate_buffer_end_iter (self);
	} else {
		gboolean _tmp0;
		_tmp0 = FALSE;
		if (line > (gtk_text_buffer_get_line_count ((GtkTextBuffer*) self) - 1)) {
			_tmp0 = TRUE;
		} else {
			_tmp0 = line < 0;
		}
		if (_tmp0) {
			return NULL;
		} else {
			ei = gtk_mate_buffer_line_start_iter (self, line + 1);
		}
	}
	_tmp3 = NULL;
	return (_tmp3 = gtk_text_buffer_get_slice ((GtkTextBuffer*) self, (_tmp2 = gtk_mate_buffer_line_start_iter (self, line), &_tmp2), &ei, TRUE), (_tmp3 == NULL) ? NULL : g_strdup (_tmp3));
}


/* Get text of line, not including the "\n". Returns null if line
 does not exist.*/
char* gtk_mate_buffer_get_line1 (GtkMateBuffer* self, gint line_ix) {
	char* line;
	char* _tmp0;
	char* _tmp3;
	g_return_val_if_fail (self != NULL, NULL);
	line = NULL;
	_tmp0 = NULL;
	if ((line = (_tmp0 = gtk_mate_buffer_get_line (self, line_ix), line = (g_free (line), NULL), _tmp0)) != NULL) {
		if (line_ix == (gtk_text_buffer_get_line_count ((GtkTextBuffer*) self) - 1)) {
			return line;
		} else {
			char* _tmp2;
			_tmp2 = NULL;
			return (_tmp2 = string_substring (line, (glong) 0, string_get_length (line) - 1), line = (g_free (line), NULL), _tmp2);
		}
	}
	_tmp3 = NULL;
	return (_tmp3 = NULL, line = (g_free (line), NULL), _tmp3);
}


gint gtk_mate_buffer_get_line_length (GtkMateBuffer* self, gint line) {
	gboolean _tmp0;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0 = FALSE;
	if (line >= gtk_text_buffer_get_line_count ((GtkTextBuffer*) self)) {
		_tmp0 = TRUE;
	} else {
		_tmp0 = line < 0;
	}
	if (_tmp0) {
		return -1;
	}
	if (line == (gtk_text_buffer_get_line_count ((GtkTextBuffer*) self) - 1)) {
		GtkTextIter _tmp3 = {0};
		GtkTextIter _tmp2 = {0};
		return gtk_text_iter_get_offset ((_tmp2 = gtk_mate_buffer_end_iter (self), &_tmp2)) - gtk_text_iter_get_offset ((_tmp3 = gtk_mate_buffer_line_start_iter (self, line), &_tmp3));
	} else {
		GtkTextIter _tmp6 = {0};
		GtkTextIter _tmp5 = {0};
		return (gtk_text_iter_get_offset ((_tmp5 = gtk_mate_buffer_line_end_iter (self, line), &_tmp5)) - gtk_text_iter_get_offset ((_tmp6 = gtk_mate_buffer_line_start_iter (self, line), &_tmp6))) - 1;
	}
}


gint gtk_mate_buffer_cursor_line (GtkMateBuffer* self) {
	GtkTextIter _tmp0 = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_line ((_tmp0 = gtk_mate_buffer_cursor_iter (self), &_tmp0));
}


gint gtk_mate_buffer_cursor_line_offset (GtkMateBuffer* self) {
	GtkTextIter _tmp0 = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_line_offset ((_tmp0 = gtk_mate_buffer_cursor_iter (self), &_tmp0));
}


gint gtk_mate_buffer_cursor_offset (GtkMateBuffer* self) {
	GtkTextIter _tmp0 = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_offset ((_tmp0 = gtk_mate_buffer_cursor_iter (self), &_tmp0));
}


void gtk_mate_buffer_select_current_scope (GtkMateBuffer* self) {
	GtkTextIter _tmp1 = {0};
	GtkTextIter _tmp0 = {0};
	GtkMateScope* current_scope;
	GtkTextIter start_iter;
	GtkTextIter end_iter;
	GtkTextMark* _tmp2;
	GtkTextMark* _tmp3;
	g_return_if_fail (self != NULL);
	current_scope = gtk_mate_scope_scope_at (self->parser->root, gtk_text_iter_get_line ((_tmp0 = gtk_mate_buffer_cursor_iter (self), &_tmp0)), gtk_text_iter_get_line_offset ((_tmp1 = gtk_mate_buffer_cursor_iter (self), &_tmp1)));
	start_iter = gtk_mate_scope_start_iter (current_scope);
	end_iter = gtk_mate_scope_end_iter (current_scope);
	_tmp2 = NULL;
	gtk_text_buffer_move_mark ((GtkTextBuffer*) self, _tmp2 = gtk_mate_buffer_selection_mark (self), &start_iter);
	(_tmp2 == NULL) ? NULL : (_tmp2 = (g_object_unref (_tmp2), NULL));
	_tmp3 = NULL;
	gtk_text_buffer_move_mark ((GtkTextBuffer*) self, _tmp3 = gtk_mate_buffer_cursor_mark (self), &end_iter);
	(_tmp3 == NULL) ? NULL : (_tmp3 = (g_object_unref (_tmp3), NULL));
	(current_scope == NULL) ? NULL : (current_scope = (g_object_unref (current_scope), NULL));
}


GeeArrayList* gtk_mate_buffer_current_scope_range (GtkMateBuffer* self) {
	GtkTextIter _tmp1 = {0};
	GtkTextIter _tmp0 = {0};
	GtkMateScope* current_scope;
	GtkTextIter start_iter;
	GtkTextIter end_iter;
	GeeArrayList* range;
	GeeArrayList* _tmp2;
	g_return_val_if_fail (self != NULL, NULL);
	current_scope = gtk_mate_scope_scope_at (self->parser->root, gtk_text_iter_get_line ((_tmp0 = gtk_mate_buffer_cursor_iter (self), &_tmp0)), gtk_text_iter_get_line_offset ((_tmp1 = gtk_mate_buffer_cursor_iter (self), &_tmp1)));
	start_iter = gtk_mate_scope_start_iter (current_scope);
	end_iter = gtk_mate_scope_end_iter (current_scope);
	range = gee_array_list_new (G_TYPE_INT, NULL, NULL, g_direct_equal);
	gee_collection_add ((GeeCollection*) range, GINT_TO_POINTER (gtk_text_iter_get_offset (&start_iter)));
	gee_collection_add ((GeeCollection*) range, GINT_TO_POINTER (gtk_text_iter_get_offset (&end_iter)));
	_tmp2 = NULL;
	return (_tmp2 = range, (current_scope == NULL) ? NULL : (current_scope = (g_object_unref (current_scope), NULL)), _tmp2);
}


GtkMateBuffer* gtk_mate_buffer_construct (GType object_type) {
	GtkMateBuffer * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


GtkMateBuffer* gtk_mate_buffer_new (void) {
	return gtk_mate_buffer_construct (GTK_MATE_TYPE_BUFFER);
}


static GObject * gtk_mate_buffer_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GtkMateBufferClass * klass;
	GObjectClass * parent_class;
	GtkMateBuffer * self;
	klass = GTK_MATE_BUFFER_CLASS (g_type_class_peek (GTK_MATE_TYPE_BUFFER));
	parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = GTK_MATE_BUFFER (obj);
	{
		gtk_mate_load_bundles ();
		gtk_mate_load_themes ();
	}
	return obj;
}


static void gtk_mate_buffer_class_init (GtkMateBufferClass * klass) {
	gtk_mate_buffer_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = gtk_mate_buffer_constructor;
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_buffer_finalize;
	g_signal_new ("grammar_changed", GTK_MATE_TYPE_BUFFER, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__STRING, G_TYPE_NONE, 1, G_TYPE_STRING);
}


static void gtk_mate_buffer_instance_init (GtkMateBuffer * self) {
}


static void gtk_mate_buffer_finalize (GObject* obj) {
	GtkMateBuffer * self;
	self = GTK_MATE_BUFFER (obj);
	(self->parser == NULL) ? NULL : (self->parser = (g_object_unref (self->parser), NULL));
	G_OBJECT_CLASS (gtk_mate_buffer_parent_class)->finalize (obj);
}


GType gtk_mate_buffer_get_type (void) {
	static GType gtk_mate_buffer_type_id = 0;
	if (gtk_mate_buffer_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateBufferClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_buffer_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateBuffer), 0, (GInstanceInitFunc) gtk_mate_buffer_instance_init, NULL };
		gtk_mate_buffer_type_id = g_type_register_static (GTK_TYPE_SOURCE_BUFFER, "GtkMateBuffer", &g_define_type_info, 0);
	}
	return gtk_mate_buffer_type_id;
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




