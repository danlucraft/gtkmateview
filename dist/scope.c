
#include "scope.h"
#include <gee/collection.h>
#include "parser.h"




struct _GtkMateScopePrivate {
	char* _name;
	GtkMateBuffer* _buffer;
	GSequence* _children;
	gboolean _is_coloured;
};

#define GTK_MATE_SCOPE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_TYPE_SCOPE, GtkMateScopePrivate))
enum  {
	GTK_MATE_SCOPE_DUMMY_PROPERTY,
	GTK_MATE_SCOPE_NAME,
	GTK_MATE_SCOPE_BUFFER,
	GTK_MATE_SCOPE_CHILDREN,
	GTK_MATE_SCOPE_IS_COLOURED
};
gint gtk_mate_scope_scope_count = 0;
static GObject * gtk_mate_scope_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer gtk_mate_scope_parent_class = NULL;
static void gtk_mate_scope_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



GtkMateScope* gtk_mate_scope_construct (GType object_type, GtkMateBuffer* buf, const char* name) {
	GtkMateScope * self;
	g_return_val_if_fail (buf != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	gtk_mate_scope_set_name (self, name);
	gtk_mate_scope_set_buffer (self, buf);
	gtk_mate_scope_set_is_coloured (self, FALSE);
	return self;
}


GtkMateScope* gtk_mate_scope_new (GtkMateBuffer* buf, const char* name) {
	return gtk_mate_scope_construct (GTK_MATE_TYPE_SCOPE, buf, name);
}


gboolean gtk_mate_scope_is_root (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, FALSE);
	if (self->parent == NULL) {
		return TRUE;
	}
	return FALSE;
}


/* compare two Scope's. Returns 1 if a is later than b,
 -1 if a is before b and 0 if b is overlapping with a*/
gint gtk_mate_scope_compare (GtkMateScope* a, GtkMateScope* b, void* data) {
	GtkTextIter _tmp1 = {0};
	GtkTextIter _tmp0 = {0};
	g_return_val_if_fail (a != NULL, 0);
	g_return_val_if_fail (b != NULL, 0);
	return gtk_text_iter_compare ((_tmp0 = gtk_mate_scope_start_iter (a), &_tmp0), (_tmp1 = gtk_mate_scope_start_iter (b), &_tmp1));
}


gint gtk_mate_scope_compare_by_loc (GtkMateScope* a, GtkMateScope* b, void* data) {
	GtkMateTextLoc* a_start;
	GtkMateTextLoc* b_start;
	g_return_val_if_fail (a != NULL, 0);
	g_return_val_if_fail (b != NULL, 0);
	a_start = gtk_mate_scope_start_loc (a);
	b_start = gtk_mate_scope_start_loc (b);
	/*stdout.printf("comparing: %s (%d, %d) to %s (%d, %d)\n", a.name, a_start.line, a_start.line_offset,
	b.name, b_start.line, b_start.line_offset);*/
	if (gtk_mate_text_loc_lt (a_start, b_start)) {
		gint _tmp0;
		/*stdout.printf("  -1\n");*/
		return (_tmp0 = -1, (a_start == NULL) ? NULL : (a_start = (g_object_unref (a_start), NULL)), (b_start == NULL) ? NULL : (b_start = (g_object_unref (b_start), NULL)), _tmp0);
	} else {
		if (gtk_mate_text_loc_equal (a_start, b_start)) {
			gint _tmp1;
			/*stdout.printf("  0\n");*/
			return (_tmp1 = 0, (a_start == NULL) ? NULL : (a_start = (g_object_unref (a_start), NULL)), (b_start == NULL) ? NULL : (b_start = (g_object_unref (b_start), NULL)), _tmp1);
		} else {
			gint _tmp2;
			/*stdout.printf("  1\n");*/
			return (_tmp2 = 1, (a_start == NULL) ? NULL : (a_start = (g_object_unref (a_start), NULL)), (b_start == NULL) ? NULL : (b_start = (g_object_unref (b_start), NULL)), _tmp2);
		}
	}
	(a_start == NULL) ? NULL : (a_start = (g_object_unref (a_start), NULL));
	(b_start == NULL) ? NULL : (b_start = (g_object_unref (b_start), NULL));
}


gboolean gtk_mate_scope_surface_identical_to_modulo_ending (GtkMateScope* self, GtkMateScope* other) {
	gboolean _tmp0;
	gboolean _tmp1;
	gboolean _tmp2;
	gboolean _tmp3;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (other != NULL, FALSE);
	_tmp0 = FALSE;
	_tmp1 = FALSE;
	_tmp2 = FALSE;
	_tmp3 = FALSE;
	if (_vala_strcmp0 (self->priv->_name, other->priv->_name) == 0) {
		_tmp3 = self->pattern == other->pattern;
	} else {
		_tmp3 = FALSE;
	}
	if (_tmp3) {
		GtkMateTextLoc* _tmp5;
		GtkMateTextLoc* _tmp4;
		_tmp5 = NULL;
		_tmp4 = NULL;
		_tmp2 = gtk_mate_text_loc_equal (_tmp4 = gtk_mate_scope_start_loc (self), _tmp5 = gtk_mate_scope_start_loc (other));
		(_tmp5 == NULL) ? NULL : (_tmp5 = (g_object_unref (_tmp5), NULL));
		(_tmp4 == NULL) ? NULL : (_tmp4 = (g_object_unref (_tmp4), NULL));
	} else {
		_tmp2 = FALSE;
	}
	if (_tmp2) {
		GtkMateTextLoc* _tmp7;
		GtkMateTextLoc* _tmp6;
		_tmp7 = NULL;
		_tmp6 = NULL;
		_tmp1 = gtk_mate_text_loc_equal (_tmp6 = gtk_mate_scope_inner_start_loc (self), _tmp7 = gtk_mate_scope_inner_start_loc (other));
		(_tmp7 == NULL) ? NULL : (_tmp7 = (g_object_unref (_tmp7), NULL));
		(_tmp6 == NULL) ? NULL : (_tmp6 = (g_object_unref (_tmp6), NULL));
	} else {
		_tmp1 = FALSE;
	}
	if (_tmp1) {
		_tmp0 = _vala_strcmp0 (self->begin_match_string, other->begin_match_string) == 0;
	} else {
		_tmp0 = FALSE;
	}
	/* stdout.printf("%s == %s and %s == %s and %s == %s and %s == %s and %s == %s",
	   name, other.name, pattern.name, other.pattern.name, start_loc().to_s(),
	   other.start_loc().to_s(), inner_start_loc().to_s(), other.inner_start_loc().to_s(),
	   begin_match_string, other.begin_match_string);*/
	if (_tmp0) {
		return TRUE;
	}
	return FALSE;
}


gboolean gtk_mate_scope_surface_identical_to (GtkMateScope* self, GtkMateScope* other) {
	gboolean _tmp0;
	gboolean _tmp1;
	gboolean _tmp2;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (other != NULL, FALSE);
	_tmp0 = FALSE;
	_tmp1 = FALSE;
	_tmp2 = FALSE;
	if (gtk_mate_scope_surface_identical_to_modulo_ending (self, other)) {
		GtkMateTextLoc* _tmp4;
		GtkMateTextLoc* _tmp3;
		_tmp4 = NULL;
		_tmp3 = NULL;
		_tmp2 = gtk_mate_text_loc_equal (_tmp3 = gtk_mate_scope_end_loc (self), _tmp4 = gtk_mate_scope_end_loc (other));
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
		_tmp1 = gtk_mate_text_loc_equal (_tmp5 = gtk_mate_scope_inner_end_loc (self), _tmp6 = gtk_mate_scope_inner_end_loc (other));
		(_tmp6 == NULL) ? NULL : (_tmp6 = (g_object_unref (_tmp6), NULL));
		(_tmp5 == NULL) ? NULL : (_tmp5 = (g_object_unref (_tmp5), NULL));
	} else {
		_tmp1 = FALSE;
	}
	if (_tmp1) {
		_tmp0 = _vala_strcmp0 (self->begin_match_string, other->begin_match_string) == 0;
	} else {
		_tmp0 = FALSE;
	}
	if (_tmp0) {
		return TRUE;
	}
	return FALSE;
}


GtkMateScope* gtk_mate_scope_scope_at (GtkMateScope* self, gint line, gint line_offset) {
	GtkMateTextLoc* loc;
	GtkMateTextLoc* start;
	gboolean _tmp0;
	g_return_val_if_fail (self != NULL, NULL);
	loc = gtk_mate_text_loc_make (line, line_offset);
	start = gtk_mate_scope_start_loc (self);
	_tmp0 = FALSE;
	if (gtk_mate_text_loc_lte (start, loc)) {
		_tmp0 = TRUE;
	} else {
		_tmp0 = self->parent == NULL;
	}
	if (_tmp0) {
		GtkMateTextLoc* _tmp1;
		gboolean _tmp2;
		_tmp1 = NULL;
		if ((_tmp2 = gtk_mate_text_loc_gte (_tmp1 = gtk_mate_scope_end_loc (self), loc), (_tmp1 == NULL) ? NULL : (_tmp1 = (g_object_unref (_tmp1), NULL)), _tmp2)) {
			GtkMateScope* s;
			GtkMateTextLoc* _tmp6;
			GtkMateTextLoc* _tmp5;
			GtkMateTextLoc* _tmp8;
			GtkMateTextLoc* _tmp7;
			GSequenceIter* iter;
			GtkMateScope* _tmp13;
			GtkMateScope* _tmp14;
			if (g_sequence_get_length (gtk_mate_scope_get_children (self)) == 0) {
				GtkMateScope* _tmp3;
				GtkMateScope* _tmp4;
				_tmp3 = NULL;
				_tmp4 = NULL;
				return (_tmp4 = (_tmp3 = self, (_tmp3 == NULL) ? NULL : g_object_ref (_tmp3)), (loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL)), (start == NULL) ? NULL : (start = (g_object_unref (start), NULL)), _tmp4);
			}
			s = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, ""));
			_tmp6 = NULL;
			_tmp5 = NULL;
			s->dummy_start_loc = (_tmp6 = (_tmp5 = loc, (_tmp5 == NULL) ? NULL : g_object_ref (_tmp5)), (s->dummy_start_loc == NULL) ? NULL : (s->dummy_start_loc = (g_object_unref (s->dummy_start_loc), NULL)), _tmp6);
			_tmp8 = NULL;
			_tmp7 = NULL;
			s->dummy_end_loc = (_tmp8 = (_tmp7 = loc, (_tmp7 == NULL) ? NULL : g_object_ref (_tmp7)), (s->dummy_end_loc == NULL) ? NULL : (s->dummy_end_loc = (g_object_unref (s->dummy_end_loc), NULL)), _tmp8);
			iter = g_sequence_search (gtk_mate_scope_get_children (self), s, (GCompareDataFunc) gtk_mate_scope_compare_by_loc, NULL);
			if (!g_sequence_iter_is_begin (iter)) {
				GtkMateScope* _tmp9;
				GtkMateScope* prev_scope;
				_tmp9 = NULL;
				prev_scope = (_tmp9 = (GtkMateScope*) g_sequence_get (g_sequence_iter_prev (iter)), (_tmp9 == NULL) ? NULL : g_object_ref (_tmp9));
				if (gtk_mate_scope_contains_loc (prev_scope, loc)) {
					GtkMateScope* _tmp10;
					_tmp10 = NULL;
					return (_tmp10 = gtk_mate_scope_scope_at (prev_scope, line, line_offset), (prev_scope == NULL) ? NULL : (prev_scope = (g_object_unref (prev_scope), NULL)), (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), (loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL)), (start == NULL) ? NULL : (start = (g_object_unref (start), NULL)), _tmp10);
				}
				(prev_scope == NULL) ? NULL : (prev_scope = (g_object_unref (prev_scope), NULL));
			}
			if (!g_sequence_iter_is_end (iter)) {
				GtkMateScope* _tmp11;
				GtkMateScope* next_scope;
				_tmp11 = NULL;
				next_scope = (_tmp11 = (GtkMateScope*) g_sequence_get (iter), (_tmp11 == NULL) ? NULL : g_object_ref (_tmp11));
				/* .next());*/
				if (gtk_mate_scope_contains_loc (next_scope, loc)) {
					GtkMateScope* _tmp12;
					_tmp12 = NULL;
					return (_tmp12 = gtk_mate_scope_scope_at (next_scope, line, line_offset), (next_scope == NULL) ? NULL : (next_scope = (g_object_unref (next_scope), NULL)), (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), (loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL)), (start == NULL) ? NULL : (start = (g_object_unref (start), NULL)), _tmp12);
				}
				(next_scope == NULL) ? NULL : (next_scope = (g_object_unref (next_scope), NULL));
			}
			_tmp13 = NULL;
			_tmp14 = NULL;
			return (_tmp14 = (_tmp13 = self, (_tmp13 == NULL) ? NULL : g_object_ref (_tmp13)), (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), (loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL)), (start == NULL) ? NULL : (start = (g_object_unref (start), NULL)), _tmp14);
		} else {
			GtkMateScope* _tmp15;
			_tmp15 = NULL;
			return (_tmp15 = NULL, (loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL)), (start == NULL) ? NULL : (start = (g_object_unref (start), NULL)), _tmp15);
		}
	} else {
		GtkMateScope* _tmp16;
		_tmp16 = NULL;
		return (_tmp16 = NULL, (loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL)), (start == NULL) ? NULL : (start = (g_object_unref (start), NULL)), _tmp16);
	}
	(loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL));
	(start == NULL) ? NULL : (start = (g_object_unref (start), NULL));
}


GtkMateScope* gtk_mate_scope_containing_double_scope (GtkMateScope* self, gint line_ix) {
	GtkMateScope* _tmp0;
	GtkMateScope* scope;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0 = NULL;
	scope = (_tmp0 = self, (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
	while (TRUE) {
		gboolean _tmp1;
		gboolean _tmp2;
		gboolean _tmp3;
		GtkMateScope* _tmp6;
		GtkMateScope* _tmp5;
		_tmp1 = FALSE;
		_tmp2 = FALSE;
		_tmp3 = FALSE;
		if (GTK_MATE_IS_SINGLE_PATTERN (scope->pattern)) {
			_tmp3 = TRUE;
		} else {
			_tmp3 = scope->is_capture;
		}
		if (_tmp3) {
			_tmp2 = TRUE;
		} else {
			gboolean _tmp4;
			_tmp4 = FALSE;
			if (gtk_mate_scope_start_line (scope) == line_ix) {
				_tmp4 = gtk_mate_scope_start_line_offset (scope) == 0;
			} else {
				_tmp4 = FALSE;
			}
			_tmp2 = _tmp4;
		}
		if (_tmp2) {
			_tmp1 = scope->parent != NULL;
		} else {
			_tmp1 = FALSE;
		}
		if (!_tmp1) {
			break;
		}
		_tmp6 = NULL;
		_tmp5 = NULL;
		scope = (_tmp6 = (_tmp5 = scope->parent, (_tmp5 == NULL) ? NULL : g_object_ref (_tmp5)), (scope == NULL) ? NULL : (scope = (g_object_unref (scope), NULL)), _tmp6);
	}
	return scope;
}


GtkMateScope* gtk_mate_scope_first_child_after (GtkMateScope* self, GtkMateTextLoc* loc) {
	GtkMateScope* s;
	GtkMateTextLoc* _tmp2;
	GtkMateTextLoc* _tmp1;
	GtkMateTextLoc* _tmp4;
	GtkMateTextLoc* _tmp3;
	GSequenceIter* iter;
	GtkMateScope* _tmp9;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (loc != NULL, NULL);
	/*stdout.printf("\"%s\".first_child_after(%d, %d)\n", name, loc.line, loc.line_offset);*/
	if (g_sequence_get_length (gtk_mate_scope_get_children (self)) == 0) {
		return NULL;
	}
	s = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, ""));
	_tmp2 = NULL;
	_tmp1 = NULL;
	s->dummy_start_loc = (_tmp2 = (_tmp1 = loc, (_tmp1 == NULL) ? NULL : g_object_ref (_tmp1)), (s->dummy_start_loc == NULL) ? NULL : (s->dummy_start_loc = (g_object_unref (s->dummy_start_loc), NULL)), _tmp2);
	_tmp4 = NULL;
	_tmp3 = NULL;
	s->dummy_end_loc = (_tmp4 = (_tmp3 = loc, (_tmp3 == NULL) ? NULL : g_object_ref (_tmp3)), (s->dummy_end_loc == NULL) ? NULL : (s->dummy_end_loc = (g_object_unref (s->dummy_end_loc), NULL)), _tmp4);
	iter = g_sequence_search (gtk_mate_scope_get_children (self), s, (GCompareDataFunc) gtk_mate_scope_compare_by_loc, NULL);
	if (!g_sequence_iter_is_begin (iter)) {
		GtkMateScope* _tmp5;
		GtkMateScope* prev_scope;
		_tmp5 = NULL;
		prev_scope = (_tmp5 = (GtkMateScope*) g_sequence_get (g_sequence_iter_prev (iter)), (_tmp5 == NULL) ? NULL : g_object_ref (_tmp5));
		if (gtk_mate_scope_compare_by_loc (prev_scope, s, NULL) == 0) {
			GtkMateScope* _tmp6;
			_tmp6 = NULL;
			return (_tmp6 = prev_scope, (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), _tmp6);
		}
		(prev_scope == NULL) ? NULL : (prev_scope = (g_object_unref (prev_scope), NULL));
	}
	if (!g_sequence_iter_is_end (iter)) {
		GtkMateScope* _tmp7;
		GtkMateScope* _tmp8;
		_tmp7 = NULL;
		_tmp8 = NULL;
		return (_tmp8 = (_tmp7 = (GtkMateScope*) g_sequence_get (iter), (_tmp7 == NULL) ? NULL : g_object_ref (_tmp7)), (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), _tmp8);
	}
	_tmp9 = NULL;
	return (_tmp9 = NULL, (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), _tmp9);
}


gboolean gtk_mate_scope_contains_loc (GtkMateScope* self, GtkMateTextLoc* loc) {
	gboolean _tmp0;
	GtkMateTextLoc* _tmp1;
	gboolean _tmp2;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (loc != NULL, FALSE);
	_tmp0 = FALSE;
	_tmp1 = NULL;
	if ((_tmp2 = gtk_mate_text_loc_lte (_tmp1 = gtk_mate_scope_start_loc (self), loc), (_tmp1 == NULL) ? NULL : (_tmp1 = (g_object_unref (_tmp1), NULL)), _tmp2)) {
		GtkMateTextLoc* _tmp3;
		_tmp3 = NULL;
		_tmp0 = gtk_mate_text_loc_gt (_tmp3 = gtk_mate_scope_end_loc (self), loc);
		(_tmp3 == NULL) ? NULL : (_tmp3 = (g_object_unref (_tmp3), NULL));
	} else {
		_tmp0 = FALSE;
	}
	if (_tmp0) {
		return TRUE;
	} else {
		return FALSE;
	}
}


gboolean gtk_mate_scope_overlaps_with (GtkMateScope* self, GtkMateScope* other) {
	GtkTextIter _tmp1 = {0};
	GtkTextIter _tmp0 = {0};
	GtkTextIter _tmp7 = {0};
	GtkTextIter _tmp6 = {0};
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (other != NULL, FALSE);
	/* sd1    +---
	 sd2  +---*/
	if (gtk_text_iter_compare ((_tmp0 = gtk_mate_scope_start_iter (self), &_tmp0), (_tmp1 = gtk_mate_scope_start_iter (other), &_tmp1)) >= 0) {
		GtkTextIter _tmp3 = {0};
		GtkTextIter _tmp2 = {0};
		if (gtk_text_iter_compare ((_tmp2 = gtk_mate_scope_start_iter (self), &_tmp2), (_tmp3 = gtk_mate_scope_end_iter (other), &_tmp3)) < 0) {
			return TRUE;
		}
		return FALSE;
	}
	/* sd1 +---
	 sd2   +---*/
	if (gtk_text_iter_compare ((_tmp6 = gtk_mate_scope_end_iter (self), &_tmp6), (_tmp7 = gtk_mate_scope_start_iter (other), &_tmp7)) > 0) {
		return TRUE;
	}
	return FALSE;
}


void gtk_mate_scope_add_child (GtkMateScope* self, GtkMateScope* s) {
	GtkMateScope* _tmp0;
	g_return_if_fail (self != NULL);
	g_return_if_fail (s != NULL);
	_tmp0 = NULL;
	g_sequence_insert_sorted (gtk_mate_scope_get_children (self), (_tmp0 = s, (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0)), (GCompareDataFunc) gtk_mate_scope_compare, NULL);
}


void gtk_mate_scope_delete_child (GtkMateScope* self, GtkMateScope* s) {
	GSequenceIter* iter;
	g_return_if_fail (self != NULL);
	g_return_if_fail (s != NULL);
	iter = g_sequence_search (gtk_mate_scope_get_children (self), s, (GCompareDataFunc) gtk_mate_scope_compare, NULL);
	/* The gsequence docs don't say whether iter will now be pointing to
	 the equal element, so we have to look on the left and on the right.*/
	if (!g_sequence_iter_is_begin (iter)) {
		GtkMateScope* _tmp0;
		GtkMateScope* prev_scope;
		_tmp0 = NULL;
		prev_scope = (_tmp0 = (GtkMateScope*) g_sequence_get (g_sequence_iter_prev (iter)), (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
		if (prev_scope == s) {
			/* stdout.printf("leftremove\n");*/
			g_sequence_remove (g_sequence_iter_prev (iter));
			(prev_scope == NULL) ? NULL : (prev_scope = (g_object_unref (prev_scope), NULL));
			return;
		}
		(prev_scope == NULL) ? NULL : (prev_scope = (g_object_unref (prev_scope), NULL));
	}
	if (!g_sequence_iter_is_end (iter)) {
		GtkMateScope* _tmp1;
		GtkMateScope* next_scope;
		_tmp1 = NULL;
		next_scope = (_tmp1 = (GtkMateScope*) g_sequence_get (iter), (_tmp1 == NULL) ? NULL : g_object_ref (_tmp1));
		if (next_scope == s) {
			/* stdout.printf("rightremove\n");*/
			g_sequence_remove (iter);
			(next_scope == NULL) ? NULL : (next_scope = (g_object_unref (next_scope), NULL));
			return;
		}
		(next_scope == NULL) ? NULL : (next_scope = (g_object_unref (next_scope), NULL));
	}
}


GeeArrayList* gtk_mate_scope_delete_any_on_line_not_in (GtkMateScope* self, gint line_ix, GeeArrayList* scopes) {
	GeeArrayList* removed_scopes;
	gboolean removed;
	GtkMateScope* s;
	GtkMateTextLoc* loc;
	GtkMateTextLoc* _tmp1;
	GtkMateTextLoc* _tmp0;
	GtkMateTextLoc* _tmp3;
	GtkMateTextLoc* _tmp2;
	GSequenceIter* iter;
	GeeArrayList* _tmp6;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (scopes != NULL, NULL);
	/*var start_scope = scope_at(line_ix, -1);*/
	removed_scopes = gee_array_list_new (GTK_MATE_TYPE_SCOPE, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal);
	/*var iter = children.get_begin_iter();*/
	removed = FALSE;
	s = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, ""));
	loc = gtk_mate_text_loc_make (line_ix, -1);
	_tmp1 = NULL;
	_tmp0 = NULL;
	s->dummy_start_loc = (_tmp1 = (_tmp0 = loc, (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0)), (s->dummy_start_loc == NULL) ? NULL : (s->dummy_start_loc = (g_object_unref (s->dummy_start_loc), NULL)), _tmp1);
	_tmp3 = NULL;
	_tmp2 = NULL;
	s->dummy_end_loc = (_tmp3 = (_tmp2 = loc, (_tmp2 == NULL) ? NULL : g_object_ref (_tmp2)), (s->dummy_end_loc == NULL) ? NULL : (s->dummy_end_loc = (g_object_unref (s->dummy_end_loc), NULL)), _tmp3);
	iter = g_sequence_search (gtk_mate_scope_get_children (self), s, (GCompareDataFunc) gtk_mate_scope_compare_by_loc, NULL);
	while (!g_sequence_iter_is_end (iter)) {
		GtkMateScope* _tmp4;
		GtkMateScope* child;
		removed = FALSE;
		_tmp4 = NULL;
		child = (_tmp4 = (GtkMateScope*) g_sequence_get (iter), (_tmp4 == NULL) ? NULL : g_object_ref (_tmp4));
		if (gtk_mate_scope_start_line (child) > line_ix) {
			GeeArrayList* _tmp5;
			_tmp5 = NULL;
			return (_tmp5 = removed_scopes, (child == NULL) ? NULL : (child = (g_object_unref (child), NULL)), (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), (loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL)), _tmp5);
		}
		if (gtk_mate_scope_start_line (child) == line_ix) {
			if (!gee_collection_contains ((GeeCollection*) scopes, child)) {
				gee_collection_add ((GeeCollection*) removed_scopes, child);
				iter = g_sequence_iter_next (iter);
				g_sequence_remove (g_sequence_iter_prev (iter));
				removed = TRUE;
			}
		}
		if (!removed) {
			iter = g_sequence_iter_next (iter);
		}
		(child == NULL) ? NULL : (child = (g_object_unref (child), NULL));
	}
	_tmp6 = NULL;
	return (_tmp6 = removed_scopes, (s == NULL) ? NULL : (s = (g_object_unref (s), NULL)), (loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL)), _tmp6);
}


void gtk_mate_scope_clear_after (GtkMateScope* self, gint line_ix, gint line_offset) {
	GtkMateTextLoc* loc;
	GtkMateScope* s;
	GtkMateTextLoc* _tmp1;
	GtkMateTextLoc* _tmp0;
	GtkMateTextLoc* _tmp3;
	GtkMateTextLoc* _tmp2;
	GSequenceIter* iter;
	GSequenceIter* prev_iter;
	GSequenceIter* end_iter;
	g_return_if_fail (self != NULL);
	loc = gtk_mate_text_loc_make (line_ix, line_offset);
	s = g_object_ref_sink (gtk_mate_scope_new (self->priv->_buffer, ""));
	_tmp1 = NULL;
	_tmp0 = NULL;
	s->dummy_start_loc = (_tmp1 = (_tmp0 = loc, (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0)), (s->dummy_start_loc == NULL) ? NULL : (s->dummy_start_loc = (g_object_unref (s->dummy_start_loc), NULL)), _tmp1);
	_tmp3 = NULL;
	_tmp2 = NULL;
	s->dummy_end_loc = (_tmp3 = (_tmp2 = loc, (_tmp2 == NULL) ? NULL : g_object_ref (_tmp2)), (s->dummy_end_loc == NULL) ? NULL : (s->dummy_end_loc = (g_object_unref (s->dummy_end_loc), NULL)), _tmp3);
	iter = g_sequence_search (gtk_mate_scope_get_children (self), s, (GCompareDataFunc) gtk_mate_scope_compare_by_loc, NULL);
	prev_iter = g_sequence_iter_prev (iter);
	if (!g_sequence_iter_is_end (prev_iter)) {
		GtkMateScope* _tmp4;
		GtkMateScope* prev_child;
		GtkMateTextLoc* _tmp5;
		gboolean _tmp6;
		_tmp4 = NULL;
		prev_child = (_tmp4 = (GtkMateScope*) g_sequence_get (g_sequence_iter_prev (iter)), (_tmp4 == NULL) ? NULL : g_object_ref (_tmp4));
		_tmp5 = NULL;
		if ((_tmp6 = gtk_mate_text_loc_gt (_tmp5 = gtk_mate_scope_end_loc (prev_child), loc), (_tmp5 == NULL) ? NULL : (_tmp5 = (g_object_unref (_tmp5), NULL)), _tmp6)) {
			gtk_mate_scope_clear_after (prev_child, line_ix, line_offset);
		}
		(prev_child == NULL) ? NULL : (prev_child = (g_object_unref (prev_child), NULL));
	}
	end_iter = g_sequence_get_end_iter (gtk_mate_scope_get_children (self));
	g_sequence_remove_range (iter, end_iter);
	(loc == NULL) ? NULL : (loc = (g_object_unref (loc), NULL));
	(s == NULL) ? NULL : (s = (g_object_unref (s), NULL));
}


char* gtk_mate_scope_pretty (GtkMateScope* self, gint indent) {
	GString* _tmp0;
	char* _tmp1;
	gboolean _tmp2;
	gboolean _tmp3;
	const char* _tmp11;
	GSequenceIter* iter;
	const char* _tmp13;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0 = NULL;
	self->pretty_string = (_tmp0 = g_string_new (""), (self->pretty_string == NULL) ? NULL : (self->pretty_string = (g_string_free (self->pretty_string, TRUE), NULL)), _tmp0);
	self->indent = indent;
	{
		gint i;
		i = 0;
		for (; i < self->indent; i++) {
			g_string_append (self->pretty_string, "  ");
		}
	}
	if (self->is_capture) {
		g_string_append (self->pretty_string, "c");
	} else {
		g_string_append (self->pretty_string, "+");
	}
	_tmp1 = NULL;
	g_string_append (self->pretty_string, _tmp1 = g_strconcat (" ", self->priv->_name, NULL));
	_tmp1 = (g_free (_tmp1), NULL);
	_tmp2 = FALSE;
	_tmp3 = FALSE;
	if (GTK_MATE_IS_DOUBLE_PATTERN (self->pattern)) {
		_tmp3 = self->is_capture == FALSE;
	} else {
		_tmp3 = FALSE;
	}
	if (_tmp3) {
		_tmp2 = GTK_MATE_DOUBLE_PATTERN (self->pattern)->content_name != NULL;
	} else {
		_tmp2 = FALSE;
	}
	if (_tmp2) {
		char* _tmp4;
		_tmp4 = NULL;
		g_string_append (self->pretty_string, _tmp4 = g_strconcat (" ", GTK_MATE_DOUBLE_PATTERN (self->pattern)->content_name, NULL));
		_tmp4 = (g_free (_tmp4), NULL);
	}
	g_string_append (self->pretty_string, " (");
	if (self->start_mark == NULL) {
		g_string_append (self->pretty_string, "inf");
	} else {
		char* _tmp7;
		GtkTextIter _tmp6 = {0};
		GtkTextIter _tmp5 = {0};
		_tmp7 = NULL;
		g_string_append (self->pretty_string, _tmp7 = g_strdup_printf ("%d,%d", gtk_text_iter_get_line ((_tmp5 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark), &_tmp5)), gtk_text_iter_get_line_offset ((_tmp6 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark), &_tmp6))));
		_tmp7 = (g_free (_tmp7), NULL);
	}
	g_string_append (self->pretty_string, ")-(");
	if (self->end_mark == NULL) {
		g_string_append (self->pretty_string, "inf");
	} else {
		char* _tmp10;
		GtkTextIter _tmp9 = {0};
		GtkTextIter _tmp8 = {0};
		_tmp10 = NULL;
		g_string_append (self->pretty_string, _tmp10 = g_strdup_printf ("%d,%d", gtk_text_iter_get_line ((_tmp8 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark), &_tmp8)), gtk_text_iter_get_line_offset ((_tmp9 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark), &_tmp9))));
		_tmp10 = (g_free (_tmp10), NULL);
	}
	g_string_append (self->pretty_string, ")");
	_tmp11 = NULL;
	if (self->is_open) {
		_tmp11 = " open";
	} else {
		_tmp11 = " closed";
	}
	g_string_append (self->pretty_string, _tmp11);
	g_string_append (self->pretty_string, "\n");
	self->indent = self->indent + 1;
	iter = g_sequence_get_begin_iter (gtk_mate_scope_get_children (self));
	while (!g_sequence_iter_is_end (iter)) {
		char* _tmp12;
		_tmp12 = NULL;
		g_string_append (self->pretty_string, _tmp12 = gtk_mate_scope_pretty ((GtkMateScope*) g_sequence_get (iter), self->indent));
		_tmp12 = (g_free (_tmp12), NULL);
		iter = g_sequence_iter_next (iter);
	}
	self->indent = self->indent - 1;
	_tmp13 = NULL;
	return (_tmp13 = self->pretty_string->str, (_tmp13 == NULL) ? NULL : g_strdup (_tmp13));
}


void gtk_mate_scope_start_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity) {
	GtkTextMark* _tmp2;
	GtkTextMark* _tmp1;
	GtkTextIter _tmp0 = {0};
	g_return_if_fail (self != NULL);
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->start_mark = (_tmp2 = (_tmp1 = gtk_text_buffer_create_mark ((GtkTextBuffer*) self->priv->_buffer, NULL, (_tmp0 = gtk_mate_buffer_iter_at_line_index (self->priv->_buffer, line, line_offset), &_tmp0), has_left_gravity), (_tmp1 == NULL) ? NULL : g_object_ref (_tmp1)), (self->start_mark == NULL) ? NULL : (self->start_mark = (g_object_unref (self->start_mark), NULL)), _tmp2);
}


void gtk_mate_scope_inner_start_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity) {
	GtkTextMark* _tmp2;
	GtkTextMark* _tmp1;
	GtkTextIter _tmp0 = {0};
	g_return_if_fail (self != NULL);
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->inner_start_mark = (_tmp2 = (_tmp1 = gtk_text_buffer_create_mark ((GtkTextBuffer*) self->priv->_buffer, NULL, (_tmp0 = gtk_mate_buffer_iter_at_line_index (self->priv->_buffer, line, line_offset), &_tmp0), has_left_gravity), (_tmp1 == NULL) ? NULL : g_object_ref (_tmp1)), (self->inner_start_mark == NULL) ? NULL : (self->inner_start_mark = (g_object_unref (self->inner_start_mark), NULL)), _tmp2);
}


void gtk_mate_scope_inner_end_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity) {
	GtkTextMark* _tmp2;
	GtkTextMark* _tmp1;
	GtkTextIter _tmp0 = {0};
	g_return_if_fail (self != NULL);
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->inner_end_mark = (_tmp2 = (_tmp1 = gtk_text_buffer_create_mark ((GtkTextBuffer*) self->priv->_buffer, NULL, (_tmp0 = gtk_mate_buffer_iter_at_line_index (self->priv->_buffer, line, line_offset), &_tmp0), has_left_gravity), (_tmp1 == NULL) ? NULL : g_object_ref (_tmp1)), (self->inner_end_mark == NULL) ? NULL : (self->inner_end_mark = (g_object_unref (self->inner_end_mark), NULL)), _tmp2);
}


void gtk_mate_scope_end_mark_set (GtkMateScope* self, gint line, gint line_offset, gboolean has_left_gravity) {
	GtkTextMark* _tmp2;
	GtkTextMark* _tmp1;
	GtkTextIter _tmp0 = {0};
	g_return_if_fail (self != NULL);
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->end_mark = (_tmp2 = (_tmp1 = gtk_text_buffer_create_mark ((GtkTextBuffer*) self->priv->_buffer, NULL, (_tmp0 = gtk_mate_buffer_iter_at_line_index (self->priv->_buffer, line, line_offset), &_tmp0), has_left_gravity), (_tmp1 == NULL) ? NULL : g_object_ref (_tmp1)), (self->end_mark == NULL) ? NULL : (self->end_mark = (g_object_unref (self->end_mark), NULL)), _tmp2);
}


GtkTextIter gtk_mate_scope_start_iter (GtkMateScope* self) {
	return gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark);
}


GtkTextIter gtk_mate_scope_inner_start_iter (GtkMateScope* self) {
	return gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->inner_start_mark);
}


GtkTextIter gtk_mate_scope_inner_end_iter (GtkMateScope* self) {
	if (self->inner_end_mark != NULL) {
		return gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->inner_end_mark);
	} else {
		return gtk_mate_scope_end_iter (self);
	}
}


GtkTextIter gtk_mate_scope_end_iter (GtkMateScope* self) {
	if (self->end_mark != NULL) {
		return gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark);
	} else {
		return gtk_mate_buffer_iter_ (self->priv->_buffer, gtk_text_buffer_get_char_count ((GtkTextBuffer*) self->priv->_buffer));
	}
}


gint gtk_mate_scope_start_offset (GtkMateScope* self) {
	GtkTextIter _tmp0 = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_offset ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark), &_tmp0));
}


gint gtk_mate_scope_inner_start_offset (GtkMateScope* self) {
	GtkTextIter _tmp0 = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_offset ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->inner_start_mark), &_tmp0));
}


gint gtk_mate_scope_inner_end_offset (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, 0);
	if (self->inner_end_mark != NULL) {
		GtkTextIter _tmp0 = {0};
		return gtk_text_iter_get_offset ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->inner_end_mark), &_tmp0));
	} else {
		return G_MAXINT;
	}
}


gint gtk_mate_scope_end_offset (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, 0);
	if (self->end_mark != NULL) {
		GtkTextIter _tmp0 = {0};
		return gtk_text_iter_get_offset ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark), &_tmp0));
	} else {
		return G_MAXINT;
	}
}


gint gtk_mate_scope_start_line (GtkMateScope* self) {
	GtkTextIter _tmp0 = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_line ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark), &_tmp0));
}


gint gtk_mate_scope_inner_start_line (GtkMateScope* self) {
	GtkTextIter _tmp0 = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_line ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->inner_start_mark), &_tmp0));
}


gint gtk_mate_scope_inner_end_line (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, 0);
	if (self->inner_end_mark != NULL) {
		GtkTextIter _tmp0 = {0};
		return gtk_text_iter_get_line ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->inner_end_mark), &_tmp0));
	} else {
		return G_MAXINT;
	}
}


gint gtk_mate_scope_end_line (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, 0);
	if (self->end_mark != NULL) {
		GtkTextIter _tmp0 = {0};
		return gtk_text_iter_get_line ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark), &_tmp0));
	} else {
		return G_MAXINT;
	}
}


gint gtk_mate_scope_start_line_offset (GtkMateScope* self) {
	GtkTextIter _tmp0 = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_line_offset ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->start_mark), &_tmp0));
}


gint gtk_mate_scope_inner_start_line_offset (GtkMateScope* self) {
	GtkTextIter _tmp0 = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_line_offset ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->inner_start_mark), &_tmp0));
}


gint gtk_mate_scope_inner_end_line_offset (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, 0);
	if (self->inner_end_mark != NULL) {
		GtkTextIter _tmp0 = {0};
		return gtk_text_iter_get_line_offset ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->inner_end_mark), &_tmp0));
	} else {
		return G_MAXINT;
	}
}


gint gtk_mate_scope_end_line_offset (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, 0);
	if (self->end_mark != NULL) {
		GtkTextIter _tmp0 = {0};
		return gtk_text_iter_get_line_offset ((_tmp0 = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, self->end_mark), &_tmp0));
	} else {
		return G_MAXINT;
	}
}


GtkMateTextLoc* gtk_mate_scope_start_loc (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->dummy_start_loc != NULL) {
		GtkMateTextLoc* _tmp0;
		_tmp0 = NULL;
		return (_tmp0 = self->dummy_start_loc, (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
	} else {
		GtkTextIter s_iter;
		s_iter = gtk_mate_scope_start_iter (self);
		return gtk_mate_text_loc_make (gtk_text_iter_get_line (&s_iter), gtk_text_iter_get_line_offset (&s_iter));
	}
}


GtkMateTextLoc* gtk_mate_scope_inner_start_loc (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->inner_start_mark != NULL) {
		GtkTextIter is_iter;
		is_iter = gtk_mate_scope_inner_start_iter (self);
		return gtk_mate_text_loc_make (gtk_text_iter_get_line (&is_iter), gtk_text_iter_get_line_offset (&is_iter));
	} else {
		return gtk_mate_scope_start_loc (self);
	}
}


GtkMateTextLoc* gtk_mate_scope_inner_end_loc (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->inner_end_mark != NULL) {
		GtkTextIter ie_iter;
		ie_iter = gtk_mate_scope_inner_end_iter (self);
		return gtk_mate_text_loc_make (gtk_text_iter_get_line (&ie_iter), gtk_text_iter_get_line_offset (&ie_iter));
	} else {
		return gtk_mate_scope_end_loc (self);
	}
}


GtkMateTextLoc* gtk_mate_scope_end_loc (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->dummy_end_loc != NULL) {
		GtkMateTextLoc* _tmp0;
		_tmp0 = NULL;
		return (_tmp0 = self->dummy_end_loc, (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
	} else {
		GtkTextIter e_iter;
		e_iter = gtk_mate_scope_end_iter (self);
		return gtk_mate_text_loc_make (gtk_text_iter_get_line (&e_iter), gtk_text_iter_get_line_offset (&e_iter));
	}
}


GtkMateScope* gtk_mate_scope_root (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->parent == NULL) {
		GtkMateScope* _tmp0;
		_tmp0 = NULL;
		return (_tmp0 = self, (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
	} else {
		return gtk_mate_scope_root (self->parent);
	}
}


gint gtk_mate_scope_priority (GtkMateScope* self, gboolean inner) {
	g_return_val_if_fail (self != NULL, 0);
	if (self->parent == NULL) {
		if (inner) {
			return 2;
		} else {
			return 1;
		}
	} else {
		if (inner) {
			return gtk_mate_scope_priority (self->parent, TRUE) + 2;
		} else {
			return gtk_mate_scope_priority (self->parent, TRUE) + 1;
		}
	}
}


char* gtk_mate_scope_hierarchy_names (GtkMateScope* self, gboolean inner) {
	char* self_name;
	gboolean _tmp0;
	gboolean _tmp1;
	g_return_val_if_fail (self != NULL, NULL);
	self_name = NULL;
	_tmp0 = FALSE;
	_tmp1 = FALSE;
	if (GTK_MATE_IS_DOUBLE_PATTERN (self->pattern)) {
		_tmp1 = GTK_MATE_DOUBLE_PATTERN (self->pattern)->content_name != NULL;
	} else {
		_tmp1 = FALSE;
	}
	if (_tmp1) {
		_tmp0 = inner;
	} else {
		_tmp0 = FALSE;
	}
	/* stdout.printf("'%s'.hierarchy_names(%s)\n", name, inner ? "true" : "false");*/
	if (_tmp0) {
		char* _tmp3;
		char* _tmp2;
		_tmp3 = NULL;
		_tmp2 = NULL;
		self_name = (_tmp3 = g_strconcat (_tmp2 = g_strconcat (self->priv->_name, " ", NULL), GTK_MATE_DOUBLE_PATTERN (self->pattern)->content_name, NULL), self_name = (g_free (self_name), NULL), _tmp3);
		_tmp2 = (g_free (_tmp2), NULL);
	} else {
		char* _tmp5;
		const char* _tmp4;
		_tmp5 = NULL;
		_tmp4 = NULL;
		self_name = (_tmp5 = (_tmp4 = self->priv->_name, (_tmp4 == NULL) ? NULL : g_strdup (_tmp4)), self_name = (g_free (self_name), NULL), _tmp5);
	}
	if (self->parent != NULL) {
		gboolean next_inner;
		char* _tmp7;
		char* _tmp6;
		char* _tmp8;
		char* _tmp9;
		next_inner = FALSE;
		if (self->is_capture) {
			next_inner = FALSE;
		} else {
			next_inner = TRUE;
		}
		_tmp7 = NULL;
		_tmp6 = NULL;
		_tmp8 = NULL;
		_tmp9 = NULL;
		return (_tmp9 = (_tmp8 = g_strconcat (_tmp7 = g_strconcat (_tmp6 = gtk_mate_scope_hierarchy_names (self->parent, next_inner), " ", NULL), self_name, NULL), _tmp7 = (g_free (_tmp7), NULL), _tmp6 = (g_free (_tmp6), NULL), _tmp8), self_name = (g_free (self_name), NULL), _tmp9);
	} else {
		return self_name;
	}
	self_name = (g_free (self_name), NULL);
}


/* public int scope_id() {
 if (id == null) {
 Scope.id_count++;
 id = Scope.id_count;
 }
 return id;
 }*/
char* gtk_mate_scope_nearest_background_colour (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->parent != NULL) {
		return gtk_mate_scope_nearest_background_colour1 (self->parent);
	}
	return NULL;
}


char* gtk_mate_scope_nearest_background_colour1 (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->bg_colour != NULL) {
		const char* _tmp0;
		_tmp0 = NULL;
		return (_tmp0 = self->bg_colour, (_tmp0 == NULL) ? NULL : g_strdup (_tmp0));
	}
	if (self->parent != NULL) {
		return gtk_mate_scope_nearest_background_colour1 (self->parent);
	}
	return NULL;
}


char* gtk_mate_scope_nearest_foreground_colour (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->parent != NULL) {
		return gtk_mate_scope_nearest_foreground_colour1 (self->parent);
	}
	return NULL;
}


char* gtk_mate_scope_nearest_foreground_colour1 (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->fg_colour != NULL) {
		const char* _tmp0;
		_tmp0 = NULL;
		return (_tmp0 = self->fg_colour, (_tmp0 == NULL) ? NULL : g_strdup (_tmp0));
	}
	if (self->parent != NULL) {
		return gtk_mate_scope_nearest_foreground_colour1 (self->parent);
	}
	return NULL;
}


const char* gtk_mate_scope_get_name (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_name;
}


void gtk_mate_scope_set_name (GtkMateScope* self, const char* value) {
	char* _tmp2;
	const char* _tmp1;
	g_return_if_fail (self != NULL);
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_name = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL) ? NULL : g_strdup (_tmp1)), self->priv->_name = (g_free (self->priv->_name), NULL), _tmp2);
	g_object_notify ((GObject *) self, "name");
}


GtkMateBuffer* gtk_mate_scope_get_buffer (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_buffer;
}


void gtk_mate_scope_set_buffer (GtkMateScope* self, GtkMateBuffer* value) {
	GtkMateBuffer* _tmp2;
	GtkMateBuffer* _tmp1;
	g_return_if_fail (self != NULL);
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_buffer = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL) ? NULL : g_object_ref (_tmp1)), (self->priv->_buffer == NULL) ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL)), _tmp2);
	g_object_notify ((GObject *) self, "buffer");
}


GSequence* gtk_mate_scope_get_children (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, NULL);
	if (self->priv->_children == NULL) {
		GSequence* _tmp0;
		_tmp0 = NULL;
		self->priv->_children = (_tmp0 = g_sequence_new (NULL), (self->priv->_children == NULL) ? NULL : (self->priv->_children = (g_sequence_free (self->priv->_children), NULL)), _tmp0);
	}
	return self->priv->_children;
}


gboolean gtk_mate_scope_get_is_coloured (GtkMateScope* self) {
	g_return_val_if_fail (self != NULL, FALSE);
	return self->priv->_is_coloured;
}


void gtk_mate_scope_set_is_coloured (GtkMateScope* self, gboolean value) {
	g_return_if_fail (self != NULL);
	self->priv->_is_coloured = value;
	g_object_notify ((GObject *) self, "is-coloured");
}


static GObject * gtk_mate_scope_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GtkMateScopeClass * klass;
	GObjectClass * parent_class;
	GtkMateScope * self;
	klass = GTK_MATE_SCOPE_CLASS (g_type_class_peek (GTK_MATE_TYPE_SCOPE));
	parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = GTK_MATE_SCOPE (obj);
	{
		gtk_mate_scope_scope_count++;
	}
	return obj;
}


static void gtk_mate_scope_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateScope * self;
	gpointer boxed;
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
		case GTK_MATE_SCOPE_IS_COLOURED:
		g_value_set_boolean (value, gtk_mate_scope_get_is_coloured (self));
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
		case GTK_MATE_SCOPE_IS_COLOURED:
		gtk_mate_scope_set_is_coloured (self, g_value_get_boolean (value));
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
	G_OBJECT_CLASS (klass)->constructor = gtk_mate_scope_constructor;
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_scope_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCOPE_NAME, g_param_spec_string ("name", "name", "name", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCOPE_BUFFER, g_param_spec_object ("buffer", "buffer", "buffer", GTK_MATE_TYPE_BUFFER, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCOPE_CHILDREN, g_param_spec_pointer ("children", "children", "children", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_SCOPE_IS_COLOURED, g_param_spec_boolean ("is-coloured", "is-coloured", "is-coloured", FALSE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void gtk_mate_scope_instance_init (GtkMateScope * self) {
	self->priv = GTK_MATE_SCOPE_GET_PRIVATE (self);
}


static void gtk_mate_scope_finalize (GObject* obj) {
	GtkMateScope * self;
	self = GTK_MATE_SCOPE (obj);
	(self->pattern == NULL) ? NULL : (self->pattern = (g_object_unref (self->pattern), NULL));
	self->priv->_name = (g_free (self->priv->_name), NULL);
	(self->priv->_buffer == NULL) ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL));
	(self->open_match == NULL) ? NULL : (self->open_match = (g_object_unref (self->open_match), NULL));
	(self->close_match == NULL) ? NULL : (self->close_match = (g_object_unref (self->close_match), NULL));
	(self->closing_regex == NULL) ? NULL : (self->closing_regex = (g_object_unref (self->closing_regex), NULL));
	(self->start_mark == NULL) ? NULL : (self->start_mark = (g_object_unref (self->start_mark), NULL));
	(self->inner_start_mark == NULL) ? NULL : (self->inner_start_mark = (g_object_unref (self->inner_start_mark), NULL));
	(self->inner_end_mark == NULL) ? NULL : (self->inner_end_mark = (g_object_unref (self->inner_end_mark), NULL));
	(self->end_mark == NULL) ? NULL : (self->end_mark = (g_object_unref (self->end_mark), NULL));
	(self->tag == NULL) ? NULL : (self->tag = (g_object_unref (self->tag), NULL));
	(self->inner_tag == NULL) ? NULL : (self->inner_tag = (g_object_unref (self->inner_tag), NULL));
	self->bg_colour = (g_free (self->bg_colour), NULL);
	self->fg_colour = (g_free (self->fg_colour), NULL);
	(self->dummy_start_loc == NULL) ? NULL : (self->dummy_start_loc = (g_object_unref (self->dummy_start_loc), NULL));
	(self->dummy_end_loc == NULL) ? NULL : (self->dummy_end_loc = (g_object_unref (self->dummy_end_loc), NULL));
	self->begin_match_string = (g_free (self->begin_match_string), NULL);
	self->end_match_string = (g_free (self->end_match_string), NULL);
	(self->priv->_children == NULL) ? NULL : (self->priv->_children = (g_sequence_free (self->priv->_children), NULL));
	(self->parent == NULL) ? NULL : (self->parent = (g_object_unref (self->parent), NULL));
	(self->pretty_string == NULL) ? NULL : (self->pretty_string = (g_string_free (self->pretty_string, TRUE), NULL));
	(self->theme_setting == NULL) ? NULL : (self->theme_setting = (g_object_unref (self->theme_setting), NULL));
	G_OBJECT_CLASS (gtk_mate_scope_parent_class)->finalize (obj);
}


GType gtk_mate_scope_get_type (void) {
	static GType gtk_mate_scope_type_id = 0;
	if (gtk_mate_scope_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateScopeClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_scope_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateScope), 0, (GInstanceInitFunc) gtk_mate_scope_instance_init, NULL };
		gtk_mate_scope_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateScope", &g_define_type_info, 0);
	}
	return gtk_mate_scope_type_id;
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




