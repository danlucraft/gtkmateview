
#include "parser.h"
#include <stdio.h>
#include <gee/collection.h>
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
static void _gtk_mate_parser_insert_text_handler_gtk_text_buffer_insert_text (GtkMateBuffer* _sender, GtkTextIter* pos, const char* text, gint length, gpointer self);
static void _gtk_mate_parser_delete_range_handler_gtk_text_buffer_delete_range (GtkMateBuffer* _sender, GtkTextIter* start, GtkTextIter* end, gpointer self);
static GtkMateChange* _gtk_mate_change_dup (GtkMateChange* self);
static gpointer gtk_mate_parser_parent_class = NULL;
static void gtk_mate_parser_dispose (GObject * obj);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);




GType gtk_mate_change_type_get_type (void) {
	static GType gtk_mate_change_type_type_id = 0;
	if (G_UNLIKELY (gtk_mate_change_type_type_id == 0)) {
		static const GEnumValue values[] = {{GTK_MATE_CHANGE_TYPE_INSERTION, "GTK_MATE_CHANGE_TYPE_INSERTION", "insertion"}, {GTK_MATE_CHANGE_TYPE_DELETION, "GTK_MATE_CHANGE_TYPE_DELETION", "deletion"}, {0, NULL, NULL}};
		gtk_mate_change_type_type_id = g_enum_register_static ("GtkMateChangeType", values);
	}
	return gtk_mate_change_type_type_id;
}


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
	GtkMateChange _tmp0 = {0};
	GtkMateChange c;
	char** _tmp1;
	gint ss_length1;
	char** ss;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_BUFFER (bf));
	g_return_if_fail (text != NULL);
	fprintf (stdout, "insert_text(pos, \"%s\", %d)\n", text, length);
	c = (memset (&_tmp0, 0, sizeof (GtkMateChange)), _tmp0);
	c.type = GTK_MATE_CHANGE_TYPE_INSERTION;
	c.from = gtk_mate_text_loc_make (gtk_text_iter_get_line (&(*pos)), gtk_text_iter_get_line_offset (&(*pos)));
	c.length = length;
	_tmp1 = NULL;
	ss = (_tmp1 = g_strsplit (text, "\n", 0), ss_length1 = -1, _tmp1);
	c.num_lines = -1;
	{
		char** s_collection;
		int s_collection_length1;
		int s_it;
		s_collection = ss;
		s_collection_length1 = ss_length1;
		for (s_it = 0; (ss_length1 != -1 && s_it < ss_length1) || (ss_length1 == -1 && s_collection[s_it] != NULL); s_it = s_it + 1) {
			const char* _tmp2;
			char* s;
			_tmp2 = NULL;
			s = (_tmp2 = s_collection[s_it], (_tmp2 == NULL ? NULL : g_strdup (_tmp2)));
			{
				c.num_lines++;
				s = (g_free (s), NULL);
			}
		}
	}
	/* stdout.printf("lines: %d\n", c.num_lines);*/
	gee_collection_add (GEE_COLLECTION (self->changes), &c);
	ss = (_vala_array_free (ss, ss_length1, ((GDestroyNotify) (g_free))), NULL);
}


void gtk_mate_parser_delete_range_handler (GtkMateParser* self, GtkMateBuffer* bf, GtkTextIter* pos, GtkTextIter* pos2) {
	GtkMateChange _tmp0 = {0};
	GtkMateChange c;
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_BUFFER (bf));
	fprintf (stdout, "delete_range(%d, %d)\n", gtk_text_iter_get_offset (&(*pos)), gtk_text_iter_get_offset (&(*pos2)));
	c = (memset (&_tmp0, 0, sizeof (GtkMateChange)), _tmp0);
	c.type = GTK_MATE_CHANGE_TYPE_DELETION;
	c.from = gtk_mate_text_loc_make (gtk_text_iter_get_line (&(*pos)), gtk_text_iter_get_line_offset (&(*pos)));
	c.to = gtk_mate_text_loc_make (gtk_text_iter_get_line (&(*pos)), gtk_text_iter_get_line_offset (&(*pos)));
	c.length = gtk_text_iter_get_offset (&(*pos2)) - gtk_text_iter_get_offset (&(*pos));
	c.num_lines = gtk_text_iter_get_line (&(*pos2)) - gtk_text_iter_get_line (&(*pos));
	fprintf (stdout, "lines: %d\n", c.num_lines);
	gee_collection_add (GEE_COLLECTION (self->changes), &c);
}


void gtk_mate_parser_insert_text_after_handler (GtkMateParser* self, GtkMateBuffer* bf, GtkTextIter* pos, const char* text, gint length) {
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_BUFFER (bf));
	g_return_if_fail (text != NULL);
	fprintf (stdout, "insert_text_after(pos, \"%s\", %d)\n", text, length);
}


void gtk_mate_parser_delete_range_after_handler (GtkMateParser* self, GtkMateBuffer* bf, GtkTextIter* pos, GtkTextIter* pos2) {
	g_return_if_fail (GTK_MATE_IS_PARSER (self));
	g_return_if_fail (GTK_MATE_IS_BUFFER (bf));
	fprintf (stdout, "delete_range_after(%d, %d)\n", gtk_text_iter_get_offset (&(*pos)), gtk_text_iter_get_offset (&(*pos2)));
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


static GtkMateChange* _gtk_mate_change_dup (GtkMateChange* self) {
	return g_memdup (self, sizeof (GtkMateChange));
}


GtkMateParser* gtk_mate_parser_create (GtkMateGrammar* grammar, GtkMateBuffer* buffer) {
	GtkMateParser* p;
	GeeArrayList* _tmp0;
	GtkMateParser* _tmp2;
	GtkMateParser* _tmp1;
	g_return_val_if_fail (GTK_MATE_IS_GRAMMAR (grammar), NULL);
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (buffer), NULL);
	gtk_mate_grammar_init_for_use (grammar);
	p = g_object_ref_sink (gtk_mate_parser_new ());
	gtk_mate_parser_set_grammar (p, grammar);
	gtk_mate_parser_set_buffer (p, buffer);
	_tmp0 = NULL;
	p->changes = (_tmp0 = gee_array_list_new (G_TYPE_POINTER, ((GBoxedCopyFunc) (_gtk_mate_change_dup)), g_free, g_direct_equal), (p->changes == NULL ? NULL : (p->changes = (g_object_unref (p->changes), NULL))), _tmp0);
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
	static GType gtk_mate_parser_type_id = 0;
	if (G_UNLIKELY (gtk_mate_parser_type_id == 0)) {
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




