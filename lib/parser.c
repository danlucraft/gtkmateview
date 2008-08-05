
#include "parser.h"
#include <gee/collection.h>
#include <stdio.h>
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
static void gtk_mate_parser_dispose (GObject * obj);
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
	char* _tmp2;
	const char* _tmp1;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	_tmp0 = NULL;
	self->root = (_tmp0 = g_object_ref_sink (gtk_mate_scope_new ()), (self->root == NULL ? NULL : (self->root = (g_object_unref (self->root), NULL))), _tmp0);
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->root->name = (_tmp2 = (_tmp1 = self->priv->_grammar->scope_name, (_tmp1 == NULL ? NULL : g_strdup (_tmp1))), (self->root->name = (g_free (self->root->name), NULL)), _tmp2);
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
	fprintf (stdout, "parse_from(%d, %d)\n", from_line, to_line);
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
	const char* _tmp2;
	GtkTextIter _tmp1 = {0};
	GtkTextIter _tmp0 = {0};
	char* line;
	gboolean _tmp3;
	g_return_val_if_fail (GTK_MATE_IS_PARSER (self), FALSE);
	_tmp2 = NULL;
	line = (_tmp2 = gtk_text_buffer_get_slice (GTK_TEXT_BUFFER (self->priv->_buffer), (_tmp0 = gtk_mate_buffer_iter_line_start (self->priv->_buffer, line_ix), &_tmp0), (_tmp1 = gtk_mate_buffer_iter_line_start (self->priv->_buffer, line_ix + 1), &_tmp1), TRUE), (_tmp2 == NULL ? NULL : g_strdup (_tmp2)));
	fprintf (stdout, "parse line: %d: '%s'\n", line_ix, line);
	return (_tmp3 = FALSE, (line = (g_free (line), NULL)), _tmp3);
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
	fprintf (stdout, "insert_text(pos, \"%s\", %d)\n", text, length);
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
	fprintf (stdout, "delete_range(%d, %d)\n", gtk_text_iter_get_offset (&(*pos)), gtk_text_iter_get_offset (&(*pos2)));
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
	gtk_mate_parser_set_grammar (p, grammar);
	gtk_mate_parser_set_buffer (p, buffer);
	_tmp0 = NULL;
	p->changes = (_tmp0 = range_set_new (), (p->changes == NULL ? NULL : (p->changes = (g_object_unref (p->changes), NULL))), _tmp0);
	/*p.is_parsing = true;*/
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
	G_OBJECT_CLASS (klass)->dispose = gtk_mate_parser_dispose;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_PARSER_GRAMMAR, g_param_spec_object ("grammar", "grammar", "grammar", GTK_MATE_TYPE_GRAMMAR, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_PARSER_BUFFER, g_param_spec_object ("buffer", "buffer", "buffer", GTK_MATE_TYPE_BUFFER, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void gtk_mate_parser_instance_init (GtkMateParser * self) {
	self->priv = GTK_MATE_PARSER_GET_PRIVATE (self);
}


static void gtk_mate_parser_dispose (GObject * obj) {
	GtkMateParser * self;
	self = GTK_MATE_PARSER (obj);
	(self->priv->_grammar == NULL ? NULL : (self->priv->_grammar = (g_object_unref (self->priv->_grammar), NULL)));
	(self->priv->_buffer == NULL ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL)));
	(self->root == NULL ? NULL : (self->root = (g_object_unref (self->root), NULL)));
	(self->changes == NULL ? NULL : (self->changes = (g_object_unref (self->changes), NULL)));
	G_OBJECT_CLASS (gtk_mate_parser_parent_class)->dispose (obj);
}


GType gtk_mate_parser_get_type (void) {
	static volatile gsize gtk_mate_parser_type_id = 0;
	if (g_once_init_enter (&gtk_mate_parser_type_id)) {
		GType gtk_mate_parser_type_id_temp;
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateParserClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_parser_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateParser), 0, (GInstanceInitFunc) gtk_mate_parser_instance_init };
		gtk_mate_parser_type_id_temp = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateParser", &g_define_type_info, 0);
		g_once_init_leave (&gtk_mate_parser_type_id, gtk_mate_parser_type_id_temp);
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




