
#include "scope.h"




enum  {
	GTK_MATE_SCOPE_DUMMY_PROPERTY
};
static gpointer gtk_mate_scope_parent_class = NULL;
static void gtk_mate_scope_dispose (GObject * obj);



gboolean gtk_mate_scope_is_root (GtkMateScope* self) {
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), FALSE);
	if (self->parent == NULL) {
		return TRUE;
	}
	return FALSE;
}


/* compare two Scope's. Returns 1 if b is later than a,
 -1 if b is before a and 0 if b is overlapping with a*/
gint gtk_mate_scope_compare (GtkMateScope* a, GtkMateScope* b) {
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
	buf = (_tmp3 = gtk_text_mark_get_buffer (GTK_TEXT_MARK (a->start_mark)), (_tmp3 == NULL ? NULL : g_object_ref (_tmp3)));
	gtk_text_buffer_get_iter_at_mark (buf, &a_start, GTK_TEXT_MARK (a->start_mark));
	gtk_text_buffer_get_iter_at_mark (buf, &b_start, GTK_TEXT_MARK (b->start_mark));
	if (gtk_text_iter_get_line (&a_start) > gtk_text_iter_get_line (&b_start)) {
		gint _tmp4;
		return (_tmp4 = -1, (buf == NULL ? NULL : (buf = (g_object_unref (buf), NULL))), _tmp4);
	} else {
		if (gtk_text_iter_get_line (&a_start) < gtk_text_iter_get_line (&b_start)) {
			gint _tmp5;
			return (_tmp5 = 1, (buf == NULL ? NULL : (buf = (g_object_unref (buf), NULL))), _tmp5);
		} else {
			if (gtk_text_iter_get_line (&a_start) == gtk_text_iter_get_line (&b_start)) {
				if (gtk_text_iter_get_line_offset (&a_start) > gtk_text_iter_get_line_offset (&b_start)) {
					gint _tmp6;
					return (_tmp6 = -1, (buf == NULL ? NULL : (buf = (g_object_unref (buf), NULL))), _tmp6);
				} else {
					if (gtk_text_iter_get_line_offset (&a_start) < gtk_text_iter_get_line_offset (&b_start)) {
						gint _tmp7;
						return (_tmp7 = 1, (buf == NULL ? NULL : (buf = (g_object_unref (buf), NULL))), _tmp7);
					}
				}
			}
		}
	}
	return (_tmp8 = 0, (buf == NULL ? NULL : (buf = (g_object_unref (buf), NULL))), _tmp8);
}


char* gtk_mate_scope_pretty (GtkMateScope* self, gint indent) {
	GString* _tmp0;
	char* _tmp1;
	const char* _tmp2;
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
	g_string_append (self->pretty_string, (_tmp1 = g_strconcat (self->name, " (", NULL)));
	_tmp1 = (g_free (_tmp1), NULL);
	if (self->start_mark == NULL) {
		g_string_append (self->pretty_string, "inf");
	}
	g_string_append (self->pretty_string, ")-(");
	if (self->end_mark == NULL) {
		g_string_append (self->pretty_string, "inf");
	}
	g_string_append (self->pretty_string, ")\n");
	self->indent = self->indent + (1);
	if (self->children != NULL) {
		g_sequence_foreach (self->children, ((GFunc) (gtk_mate_scope_append_pretty)), NULL);
	}
	_tmp2 = NULL;
	return (_tmp2 = self->pretty_string->str, (_tmp2 == NULL ? NULL : g_strdup (_tmp2)));
}


void gtk_mate_scope_append_pretty (GtkMateScope* self, GtkMateScope* child) {
	char* _tmp0;
	g_return_if_fail (GTK_MATE_IS_SCOPE (self));
	g_return_if_fail (GTK_MATE_IS_SCOPE (child));
	_tmp0 = NULL;
	g_string_append (self->pretty_string, (_tmp0 = gtk_mate_scope_pretty (child, self->indent)));
	_tmp0 = (g_free (_tmp0), NULL);
}


GtkMateScope* gtk_mate_scope_new (void) {
	GtkMateScope * self;
	self = g_object_newv (GTK_MATE_TYPE_SCOPE, 0, NULL);
	return self;
}


static void gtk_mate_scope_class_init (GtkMateScopeClass * klass) {
	gtk_mate_scope_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->dispose = gtk_mate_scope_dispose;
}


static void gtk_mate_scope_instance_init (GtkMateScope * self) {
}


static void gtk_mate_scope_dispose (GObject * obj) {
	GtkMateScope * self;
	self = GTK_MATE_SCOPE (obj);
	(self->pattern == NULL ? NULL : (self->pattern = (g_object_unref (self->pattern), NULL)));
	self->name = (g_free (self->name), NULL);
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
	(self->children == NULL ? NULL : (self->children = (g_sequence_free (self->children), NULL)));
	(self->parent == NULL ? NULL : (self->parent = (g_object_unref (self->parent), NULL)));
	(self->pretty_string == NULL ? NULL : (self->pretty_string = (g_string_free (self->pretty_string, TRUE), NULL)));
	G_OBJECT_CLASS (gtk_mate_scope_parent_class)->dispose (obj);
}


GType gtk_mate_scope_get_type (void) {
	static volatile gsize gtk_mate_scope_type_id = 0;
	if (g_once_init_enter (&gtk_mate_scope_type_id)) {
		GType gtk_mate_scope_type_id_temp;
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateScopeClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_scope_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateScope), 0, (GInstanceInitFunc) gtk_mate_scope_instance_init };
		gtk_mate_scope_type_id_temp = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateScope", &g_define_type_info, 0);
		g_once_init_leave (&gtk_mate_scope_type_id, gtk_mate_scope_type_id_temp);
	}
	return gtk_mate_scope_type_id;
}




