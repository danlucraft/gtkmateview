
#include "scope.h"
#include "buffer.h"
#include "parser.h"




struct _GtkMateScopePrivate {
	char* _name;
	GtkMateBuffer* _buffer;
	GSequence* _children;
};

#define GTK_MATE_SCOPE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_TYPE_SCOPE, GtkMateScopePrivate))
enum  {
	GTK_MATE_SCOPE_DUMMY_PROPERTY,
	GTK_MATE_SCOPE_NAME,
	GTK_MATE_SCOPE_BUFFER,
	GTK_MATE_SCOPE_CHILDREN
};
static gpointer gtk_mate_scope_parent_class = NULL;
static void gtk_mate_scope_finalize (GObject * obj);



GtkMateScope* gtk_mate_scope_new (GtkMateBuffer* buf, const char* name) {
	GtkMateScope * self;
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (buf), NULL);
	self = g_object_newv (GTK_MATE_TYPE_SCOPE, 0, NULL);
	gtk_mate_scope_set_name (self, name);
	gtk_mate_scope_set_buffer (self, buf);
	return self;
}


gboolean gtk_mate_scope_is_root (GtkMateScope* self) {
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), FALSE);
	if (self->parent == NULL) {
		return TRUE;
	}
	return FALSE;
}


/* compare two Scope's. Returns 1 if a is later than b,
 -1 if a is before b and 0 if b is overlapping with a*/
gint gtk_mate_scope_compare (GtkMateScope* a, GtkMateScope* b, void* data) {
	GtkTextIter a_start = {0};
	GtkTextIter b_start = {0};
	GtkTextBuffer* _tmp3;
	GtkTextBuffer* buf;
	gint _tmp8;
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (a), 0);
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (b), 0);
	if (a->start_mark == NULL) {
		if (b->start_mark == NULL) {
			return 0;
		} else {
			return 1;
		}
	} else {
		if (b->start_mark == NULL) {
			return -1;
		}
	}
	_tmp3 = NULL;
	buf = (_tmp3 = gtk_text_mark_get_buffer (a->start_mark), (_tmp3 == NULL ? NULL : g_object_ref (_tmp3)));
	gtk_text_buffer_get_iter_at_mark (buf, &a_start, a->start_mark);
	gtk_text_buffer_get_iter_at_mark (buf, &b_start, b->start_mark);
	if (gtk_text_iter_get_line (&a_start) > gtk_text_iter_get_line (&b_start)) {
		gint _tmp4;
		return (_tmp4 = 1, (buf == NULL ? NULL : (buf = (g_object_unref (buf), NULL))), _tmp4);
	} else {
		if (gtk_text_iter_get_line (&a_start) < gtk_text_iter_get_line (&b_start)) {
			gint _tmp5;
			return (_tmp5 = -1, (buf == NULL ? NULL : (buf = (g_object_unref (buf), NULL))), _tmp5);
		} else {
			if (gtk_text_iter_get_line (&a_start) == gtk_text_iter_get_line (&b_start)) {
				if (gtk_text_iter_get_line_offset (&a_start) > gtk_text_iter_get_line_offset (&b_start)) {
					gint _tmp6;
					return (_tmp6 = 1, (buf == NULL ? NULL : (buf = (g_object_unref (buf), NULL))), _tmp6);
				} else {
					if (gtk_text_iter_get_line_offset (&a_start) < gtk_text_iter_get_line_offset (&b_start)) {
						gint _tmp7;
						return (_tmp7 = -1, (buf == NULL ? NULL : (buf = (g_object_unref (buf), NULL))), _tmp7);
					}
				}
			}
		}
	}
	return (_tmp8 = 0, (buf == NULL ? NULL : (buf = (g_object_unref (buf), NULL))), _tmp8);
}


gint gtk_mate_scope_compare_by_loc (GtkMateScope* a, GtkMateScope* b, void* data) {
	GtkMateTextLoc* _tmp1;
	GtkMateTextLoc* _tmp0;
	gboolean _tmp2;
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (a), 0);
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (b), 0);
	_tmp1 = NULL;
	_tmp0 = NULL;
	if ((_tmp2 = gtk_mate_text_loc_lt ((_tmp0 = gtk_mate_scope_start_loc (a)), (_tmp1 = gtk_mate_scope_start_loc (b))), (_tmp1 == NULL ? NULL : (_tmp1 = (g_object_unref (_tmp1), NULL))), (_tmp0 == NULL ? NULL : (_tmp0 = (g_object_unref (_tmp0), NULL))), _tmp2)) {
		return -1;
	} else {
		GtkMateTextLoc* _tmp5;
		GtkMateTextLoc* _tmp4;
		gboolean _tmp6;
		_tmp5 = NULL;
		_tmp4 = NULL;
		if ((_tmp6 = gtk_mate_text_loc_equal ((_tmp4 = gtk_mate_scope_start_loc (a)), (_tmp5 = gtk_mate_scope_start_loc (b))), (_tmp5 == NULL ? NULL : (_tmp5 = (g_object_unref (_tmp5), NULL))), (_tmp4 == NULL ? NULL : (_tmp4 = (g_object_unref (_tmp4), NULL))), _tmp6)) {
			return 0;
		} else {
			return 1;
		}
	}
}


GtkMateScope* gtk_mate_scope_scope_at (GtkMateScope* self, gint line, gint line_offset) {
	GtkMateTextLoc* loc;
	GtkMateTextLoc* start;
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), NULL);
	loc = gtk_mate_text_loc_make (line, line_offset);
	start = gtk_mate_scope_start_loc (self);
	if (gtk_mate_text_loc_lte (start, loc) || self->parent == NULL) {
		GtkMateTextLoc* _tmp0;
		gboolean _tmp1;
		_tmp0 = NULL;
		if ((_tmp1 = gtk_mate_text_loc_gte ((_tmp0 = gtk_mate_scope_end_loc (self)), loc), (_tmp0 == NULL ? NULL : (_tmp0 = (g_object_unref (_tmp0), NULL))), _tmp1)) {
			GtkMateScope* s;
			GtkMateTextLoc* _tmp5;
			GtkMateTextLoc* _tmp4;
			GtkMateTextLoc* _tmp7;
			GtkMateTextLoc* _tmp6;
			GSequenceIter* _tmp8;
			GSequenceIter* iter;
			GtkMateScope* _tmp13;
			GtkMateScope* _tmp14;
			if (g_sequence_get_length (gtk_mate_scope_get_children (self)) == 0) {
				GtkMateScope* _tmp2;
				GtkMateScope* _tmp3;
				_tmp2 = NULL;
				_tmp3 = NULL;
				return (_tmp3 = (_tmp2 = self, (_tmp2 == NULL ? NULL : g_object_ref (_tmp2))), (loc == NULL ? NULL : (loc = (g_object_unref (loc), NULL))), (start == NULL ? NULL : (start = (g_object_unref (start), NULL))), _tmp3);
			}
			s = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, ""));
			_tmp5 = NULL;
			_tmp4 = NULL;
			s->dummy_start_loc = (_tmp5 = (_tmp4 = loc, (_tmp4 == NULL ? NULL : g_object_ref (_tmp4))), (s->dummy_start_loc == NULL ? NULL : (s->dummy_start_loc = (g_object_unref (s->dummy_start_loc), NULL))), _tmp5);
			_tmp7 = NULL;
			_tmp6 = NULL;
			s->dummy_end_loc = (_tmp7 = (_tmp6 = loc, (_tmp6 == NULL ? NULL : g_object_ref (_tmp6))), (s->dummy_end_loc == NULL ? NULL : (s->dummy_end_loc = (g_object_unref (s->dummy_end_loc), NULL))), _tmp7);
			_tmp8 = NULL;
			iter = (_tmp8 = g_sequence_search (gtk_mate_scope_get_children (self), s, ((GCompareDataFunc) (gtk_mate_scope_compare_by_loc)), NULL), (_tmp8 == NULL ? NULL :  (_tmp8)));
			if (!g_sequence_iter_is_begin (iter)) {
				GtkMateScope* _tmp9;
				GtkMateScope* prev_scope;
				_tmp9 = NULL;
				prev_scope = (_tmp9 = ((GtkMateScope*) (g_sequence_get (g_sequence_iter_prev (iter)))), (_tmp9 == NULL ? NULL : g_object_ref (_tmp9)));
				if (gtk_mate_scope_contains_loc (prev_scope, loc)) {
					GtkMateScope* _tmp10;
					_tmp10 = NULL;
					return (_tmp10 = gtk_mate_scope_scope_at (prev_scope, line, line_offset), (prev_scope == NULL ? NULL : (prev_scope = (g_object_unref (prev_scope), NULL))), (s == NULL ? NULL : (s = (g_object_unref (s), NULL))), (iter == NULL ? NULL : (iter = ( (iter), NULL))), (loc == NULL ? NULL : (loc = (g_object_unref (loc), NULL))), (start == NULL ? NULL : (start = (g_object_unref (start), NULL))), _tmp10);
				}
				(prev_scope == NULL ? NULL : (prev_scope = (g_object_unref (prev_scope), NULL)));
			}
			if (!g_sequence_iter_is_end (iter)) {
				GtkMateScope* _tmp11;
				GtkMateScope* next_scope;
				_tmp11 = NULL;
				next_scope = (_tmp11 = ((GtkMateScope*) (g_sequence_get (g_sequence_iter_next (iter)))), (_tmp11 == NULL ? NULL : g_object_ref (_tmp11)));
				if (gtk_mate_scope_contains_loc (next_scope, loc)) {
					GtkMateScope* _tmp12;
					_tmp12 = NULL;
					return (_tmp12 = gtk_mate_scope_scope_at (next_scope, line, line_offset), (next_scope == NULL ? NULL : (next_scope = (g_object_unref (next_scope), NULL))), (s == NULL ? NULL : (s = (g_object_unref (s), NULL))), (iter == NULL ? NULL : (iter = ( (iter), NULL))), (loc == NULL ? NULL : (loc = (g_object_unref (loc), NULL))), (start == NULL ? NULL : (start = (g_object_unref (start), NULL))), _tmp12);
				}
				(next_scope == NULL ? NULL : (next_scope = (g_object_unref (next_scope), NULL)));
			}
			_tmp13 = NULL;
			_tmp14 = NULL;
			return (_tmp14 = (_tmp13 = self, (_tmp13 == NULL ? NULL : g_object_ref (_tmp13))), (s == NULL ? NULL : (s = (g_object_unref (s), NULL))), (iter == NULL ? NULL : (iter = ( (iter), NULL))), (loc == NULL ? NULL : (loc = (g_object_unref (loc), NULL))), (start == NULL ? NULL : (start = (g_object_unref (start), NULL))), _tmp14);
		} else {
			GtkMateScope* _tmp15;
			_tmp15 = NULL;
			return (_tmp15 = NULL, (loc == NULL ? NULL : (loc = (g_object_unref (loc), NULL))), (start == NULL ? NULL : (start = (g_object_unref (start), NULL))), _tmp15);
		}
	} else {
		GtkMateScope* _tmp16;
		_tmp16 = NULL;
		return (_tmp16 = NULL, (loc == NULL ? NULL : (loc = (g_object_unref (loc), NULL))), (start == NULL ? NULL : (start = (g_object_unref (start), NULL))), _tmp16);
	}
	(loc == NULL ? NULL : (loc = (g_object_unref (loc), NULL)));
	(start == NULL ? NULL : (start = (g_object_unref (start), NULL)));
}


gboolean gtk_mate_scope_contains_loc (GtkMateScope* self, GtkMateTextLoc* loc) {
	GtkMateTextLoc* _tmp1;
	GtkMateTextLoc* _tmp0;
	gboolean _tmp2;
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), FALSE);
	g_return_val_if_fail (GTK_MATE_IS_TEXT_LOC (loc), FALSE);
	_tmp1 = NULL;
	_tmp0 = NULL;
	if ((_tmp2 = gtk_mate_text_loc_lte ((_tmp0 = gtk_mate_scope_start_loc (self)), loc) && gtk_mate_text_loc_gt ((_tmp1 = gtk_mate_scope_end_loc (self)), loc), (_tmp1 == NULL ? NULL : (_tmp1 = (g_object_unref (_tmp1), NULL))), (_tmp0 == NULL ? NULL : (_tmp0 = (g_object_unref (_tmp0), NULL))), _tmp2)) {
		return TRUE;
	} else {
		return FALSE;
	}
}


char* gtk_mate_scope_pretty (GtkMateScope* self, gint indent) {
	GString* _tmp0;
	char* _tmp1;
	GSequenceIter* _tmp9;
	GSequenceIter* iter;
	const char* _tmp13;
	char* _tmp14;
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), NULL);
	_tmp0 = NULL;
	self->pretty_string = (_tmp0 = g_string_new (""), (self->pretty_string == NULL ? NULL : (self->pretty_string = (g_string_free (self->pretty_string, TRUE), NULL))), _tmp0);
	self->indent = indent;
	{
		gint i;
		i = 0;
		for (; i < self->indent; i++) {
			g_string_append (self->pretty_string, "  ");
		}
	}
	_tmp1 = NULL;
	g_string_append (self->pretty_string, (_tmp1 = g_strconcat ("+ ", self->priv->_name, NULL)));
	_tmp1 = (g_free (_tmp1), NULL);
	if (GTK_MATE_IS_DOUBLE_PATTERN (self->pattern) && (GTK_MATE_DOUBLE_PATTERN (self->pattern))->content_name != NULL) {
		char* _tmp2;
		_tmp2 = NULL;
		g_string_append (self->pretty_string, (_tmp2 = g_strconcat (" ", (GTK_MATE_DOUBLE_PATTERN (self->pattern))->content_name, NULL)));
		_tmp2 = (g_free (_tmp2), NULL);
	}
	g_string_append (self->pretty_string, " (");
	if (self->start_mark == NULL) {
		g_string_append (self->pretty_string, "inf");
	} else {
		char* _tmp5;
		GtkTextIter _tmp4 = {0};
		GtkTextIter _tmp3 = {0};
		_tmp5 = NULL;
		g_string_append (self->pretty_string, (_tmp5 = g_strdup_printf ("%d,%d", gtk_text_iter_get_line ((_tmp3 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark), &_tmp3)), gtk_text_iter_get_line_offset ((_tmp4 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark), &_tmp4)))));
		_tmp5 = (g_free (_tmp5), NULL);
	}
	g_string_append (self->pretty_string, ")-(");
	if (self->end_mark == NULL) {
		g_string_append (self->pretty_string, "inf");
	} else {
		char* _tmp8;
		GtkTextIter _tmp7 = {0};
		GtkTextIter _tmp6 = {0};
		_tmp8 = NULL;
		g_string_append (self->pretty_string, (_tmp8 = g_strdup_printf ("%d,%d", gtk_text_iter_get_line ((_tmp6 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark), &_tmp6)), gtk_text_iter_get_line_offset ((_tmp7 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark), &_tmp7)))));
		_tmp8 = (g_free (_tmp8), NULL);
	}
	g_string_append (self->pretty_string, ")");
	g_string_append (self->pretty_string, ((self->is_open ? " open" : " closed")));
	g_string_append (self->pretty_string, "\n");
	self->indent = self->indent + (1);
	_tmp9 = NULL;
	iter = (_tmp9 = g_sequence_get_begin_iter (gtk_mate_scope_get_children (self)), (_tmp9 == NULL ? NULL :  (_tmp9)));
	while (!g_sequence_iter_is_end (iter)) {
		char* _tmp10;
		GSequenceIter* _tmp12;
		GSequenceIter* _tmp11;
		_tmp10 = NULL;
		g_string_append (self->pretty_string, (_tmp10 = gtk_mate_scope_pretty (((GtkMateScope*) (g_sequence_get (iter))), self->indent)));
		_tmp10 = (g_free (_tmp10), NULL);
		_tmp12 = NULL;
		_tmp11 = NULL;
		iter = (_tmp12 = (_tmp11 = g_sequence_iter_next (iter), (_tmp11 == NULL ? NULL :  (_tmp11))), (iter == NULL ? NULL : (iter = ( (iter), NULL))), _tmp12);
	}
	self->indent = self->indent - (1);
	_tmp13 = NULL;
	_tmp14 = NULL;
	return (_tmp14 = (_tmp13 = self->pretty_string->str, (_tmp13 == NULL ? NULL : g_strdup (_tmp13))), (iter == NULL ? NULL : (iter = ( (iter), NULL))), _tmp14);
}


void gtk_mate_scope_start_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity) {
	GtkTextMark* _tmp2;
	GtkTextMark* _tmp1;
	GtkTextIter _tmp0 = {0};
	g_return_if_fail (GTK_MATE_IS_SCOPE (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->start_mark = (_tmp2 = (_tmp1 = gtk_text_buffer_create_mark (GTK_TEXT_BUFFER (self->priv->_buffer), NULL, (_tmp0 = gtk_mate_buffer_iter_at_line_offset (self->priv->_buffer, line, line_offset), &_tmp0), has_left_gravity), (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (self->start_mark == NULL ? NULL : (self->start_mark = (g_object_unref (self->start_mark), NULL))), _tmp2);
}


void gtk_mate_scope_inner_start_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity) {
	GtkTextMark* _tmp2;
	GtkTextMark* _tmp1;
	GtkTextIter _tmp0 = {0};
	g_return_if_fail (GTK_MATE_IS_SCOPE (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->inner_start_mark = (_tmp2 = (_tmp1 = gtk_text_buffer_create_mark (GTK_TEXT_BUFFER (self->priv->_buffer), NULL, (_tmp0 = gtk_mate_buffer_iter_at_line_offset (self->priv->_buffer, line, line_offset), &_tmp0), has_left_gravity), (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (self->inner_start_mark == NULL ? NULL : (self->inner_start_mark = (g_object_unref (self->inner_start_mark), NULL))), _tmp2);
}


void gtk_mate_scope_inner_end_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity) {
	GtkTextMark* _tmp2;
	GtkTextMark* _tmp1;
	GtkTextIter _tmp0 = {0};
	g_return_if_fail (GTK_MATE_IS_SCOPE (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->inner_end_mark = (_tmp2 = (_tmp1 = gtk_text_buffer_create_mark (GTK_TEXT_BUFFER (self->priv->_buffer), NULL, (_tmp0 = gtk_mate_buffer_iter_at_line_offset (self->priv->_buffer, line, line_offset), &_tmp0), has_left_gravity), (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (self->inner_end_mark == NULL ? NULL : (self->inner_end_mark = (g_object_unref (self->inner_end_mark), NULL))), _tmp2);
}


void gtk_mate_scope_end_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity) {
	GtkTextMark* _tmp2;
	GtkTextMark* _tmp1;
	GtkTextIter _tmp0 = {0};
	g_return_if_fail (GTK_MATE_IS_SCOPE (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->end_mark = (_tmp2 = (_tmp1 = gtk_text_buffer_create_mark (GTK_TEXT_BUFFER (self->priv->_buffer), NULL, (_tmp0 = gtk_mate_buffer_iter_at_line_offset (self->priv->_buffer, line, line_offset), &_tmp0), has_left_gravity), (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (self->end_mark == NULL ? NULL : (self->end_mark = (g_object_unref (self->end_mark), NULL))), _tmp2);
}


gint gtk_mate_scope_start_offset (GtkMateScope* self) {
	GtkTextIter _tmp0 = {0};
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), 0);
	return gtk_text_iter_get_offset ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark), &_tmp0));
}


gint gtk_mate_scope_end_offset (GtkMateScope* self) {
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), 0);
	if (self->end_mark != NULL) {
		GtkTextIter _tmp0 = {0};
		return gtk_text_iter_get_offset ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark), &_tmp0));
	} else {
		return G_MAXINT;
	}
}


gint gtk_mate_scope_start_line (GtkMateScope* self) {
	GtkTextIter _tmp0 = {0};
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), 0);
	return gtk_text_iter_get_line ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark), &_tmp0));
}


gint gtk_mate_scope_end_line (GtkMateScope* self) {
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), 0);
	if (self->end_mark != NULL) {
		GtkTextIter _tmp0 = {0};
		return gtk_text_iter_get_line ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark), &_tmp0));
	} else {
		return G_MAXINT;
	}
}


gint gtk_mate_scope_start_line_offset (GtkMateScope* self) {
	GtkTextIter _tmp0 = {0};
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), 0);
	return gtk_text_iter_get_line_offset ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark), &_tmp0));
}


gint gtk_mate_scope_end_line_offset (GtkMateScope* self) {
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), 0);
	if (self->end_mark != NULL) {
		GtkTextIter _tmp0 = {0};
		return gtk_text_iter_get_line_offset ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark), &_tmp0));
	} else {
		return G_MAXINT;
	}
}


GtkMateTextLoc* gtk_mate_scope_start_loc (GtkMateScope* self) {
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), NULL);
	if (self->dummy_start_loc != NULL) {
		GtkMateTextLoc* _tmp0;
		_tmp0 = NULL;
		return (_tmp0 = self->dummy_start_loc, (_tmp0 == NULL ? NULL : g_object_ref (_tmp0)));
	} else {
		return gtk_mate_text_loc_make (gtk_mate_scope_start_line (self), gtk_mate_scope_start_line_offset (self));
	}
}


GtkMateTextLoc* gtk_mate_scope_end_loc (GtkMateScope* self) {
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), NULL);
	if (self->dummy_end_loc != NULL) {
		GtkMateTextLoc* _tmp0;
		_tmp0 = NULL;
		return (_tmp0 = self->dummy_end_loc, (_tmp0 == NULL ? NULL : g_object_ref (_tmp0)));
	} else {
		return gtk_mate_text_loc_make (gtk_mate_scope_end_line (self), gtk_mate_scope_end_line_offset (self));
	}
}


const char* gtk_mate_scope_get_name (GtkMateScope* self) {
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), NULL);
	return self->priv->_name;
}


void gtk_mate_scope_set_name (GtkMateScope* self, const char* value) {
	char* _tmp2;
	const char* _tmp1;
	g_return_if_fail (GTK_MATE_IS_SCOPE (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_name = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_strdup (_tmp1))), (self->priv->_name = (g_free (self->priv->_name), NULL)), _tmp2);
	g_object_notify (((GObject *) (self)), "name");
}


GtkMateBuffer* gtk_mate_scope_get_buffer (GtkMateScope* self) {
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), NULL);
	return self->priv->_buffer;
}


void gtk_mate_scope_set_buffer (GtkMateScope* self, GtkMateBuffer* value) {
	GtkMateBuffer* _tmp2;
	GtkMateBuffer* _tmp1;
	g_return_if_fail (GTK_MATE_IS_SCOPE (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_buffer = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (self->priv->_buffer == NULL ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL))), _tmp2);
	g_object_notify (((GObject *) (self)), "buffer");
}


GSequence* gtk_mate_scope_get_children (GtkMateScope* self) {
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), NULL);
	if (self->priv->_children == NULL) {
		GSequence* _tmp0;
		_tmp0 = NULL;
		self->priv->_children = (_tmp0 = g_sequence_new (NULL), (self->priv->_children == NULL ? NULL : (self->priv->_children = (g_sequence_free (self->priv->_children), NULL))), _tmp0);
	}
	return self->priv->_children;
}


static void gtk_mate_scope_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateScope * self;
	self = GTK_MATE_SCOPE (object);
	switch (property_id) {
		case GTK_MATE_SCOPE_NAME:
		g_value_set_string (value, gtk_mate_scope_get_name (self));
		break;
		case GTK_MATE_SCOPE_BUFFER:
		g_value_set_object (value, gtk_mate_scope_get_buffer (self));
		break;
		case GTK_MATE_SCOPE_CHILDREN:
		g_value_set_pointer (value, gtk_mate_scope_get_children (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_scope_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GtkMateScope * self;
	self = GTK_MATE_SCOPE (object);
	switch (property_id) {
		case GTK_MATE_SCOPE_NAME:
		gtk_mate_scope_set_name (self, g_value_get_string (value));
		break;
		case GTK_MATE_SCOPE_BUFFER:
		gtk_mate_scope_set_buffer (self, g_value_get_object (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_scope_class_init (GtkMateScopeClass * klass) {
	gtk_mate_scope_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GtkMateScopePrivate));
	G_OBJECT_CLASS (klass)->get_property = gtk_mate_scope_get_property;
	G_OBJECT_CLASS (klass)->set_property = gtk_mate_scope_set_property;
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_scope_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCOPE_NAME, g_param_spec_string ("name", "name", "name", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCOPE_BUFFER, g_param_spec_object ("buffer", "buffer", "buffer", GTK_MATE_TYPE_BUFFER, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCOPE_CHILDREN, g_param_spec_pointer ("children", "children", "children", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
}


static void gtk_mate_scope_instance_init (GtkMateScope * self) {
	self->priv = GTK_MATE_SCOPE_GET_PRIVATE (self);
}


static void gtk_mate_scope_finalize (GObject * obj) {
	GtkMateScope * self;
	self = GTK_MATE_SCOPE (obj);
	(self->pattern == NULL ? NULL : (self->pattern = (g_object_unref (self->pattern), NULL)));
	self->priv->_name = (g_free (self->priv->_name), NULL);
	(self->priv->_buffer == NULL ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL)));
	(self->open_match == NULL ? NULL : (self->open_match = (g_object_unref (self->open_match), NULL)));
	(self->close_match == NULL ? NULL : (self->close_match = (g_object_unref (self->close_match), NULL)));
	(self->closing_regex == NULL ? NULL : (self->closing_regex = (g_object_unref (self->closing_regex), NULL)));
	(self->start_mark == NULL ? NULL : (self->start_mark = (g_object_unref (self->start_mark), NULL)));
	(self->inner_start_mark == NULL ? NULL : (self->inner_start_mark = (g_object_unref (self->inner_start_mark), NULL)));
	(self->inner_end_mark == NULL ? NULL : (self->inner_end_mark = (g_object_unref (self->inner_end_mark), NULL)));
	(self->end_mark == NULL ? NULL : (self->end_mark = (g_object_unref (self->end_mark), NULL)));
	(self->tag == NULL ? NULL : (self->tag = (g_object_unref (self->tag), NULL)));
	(self->inner_tag == NULL ? NULL : (self->inner_tag = (g_object_unref (self->inner_tag), NULL)));
	self->bg_color = (g_free (self->bg_color), NULL);
	(self->dummy_start_loc == NULL ? NULL : (self->dummy_start_loc = (g_object_unref (self->dummy_start_loc), NULL)));
	(self->dummy_end_loc == NULL ? NULL : (self->dummy_end_loc = (g_object_unref (self->dummy_end_loc), NULL)));
	(self->priv->_children == NULL ? NULL : (self->priv->_children = (g_sequence_free (self->priv->_children), NULL)));
	(self->parent == NULL ? NULL : (self->parent = (g_object_unref (self->parent), NULL)));
	(self->pretty_string == NULL ? NULL : (self->pretty_string = (g_string_free (self->pretty_string, TRUE), NULL)));
	G_OBJECT_CLASS (gtk_mate_scope_parent_class)->finalize (obj);
}


GType gtk_mate_scope_get_type (void) {
	static GType gtk_mate_scope_type_id = 0;
	if (gtk_mate_scope_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateScopeClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_scope_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateScope), 0, (GInstanceInitFunc) gtk_mate_scope_instance_init };
		gtk_mate_scope_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateScope", &g_define_type_info, 0);
	}
	return gtk_mate_scope_type_id;
}




