
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


char* gtk_mate_scope_pretty (GtkMateScope* self, gint indent) {
	GString* s;
	char* _tmp0;
	const char* _tmp2;
	char* _tmp3;
	g_return_val_if_fail (GTK_MATE_IS_SCOPE (self), NULL);
	s = g_string_new ("");
	{
		gint i;
		i = 0;
		for (; i < indent; i++) {
			g_string_append (s, "  ");
		}
	}
	_tmp0 = NULL;
	g_string_append (s, (_tmp0 = g_strconcat (self->name, " (", NULL)));
	_tmp0 = (g_free (_tmp0), NULL);
	if (self->start_mark == NULL) {
		g_string_append (s, "inf");
	}
	g_string_append (s, ")-(");
	if (self->end_mark == NULL) {
		g_string_append (s, "inf");
	}
	g_string_append (s, ")\n");
	if (self->children != NULL) {
		{
			GeeArrayList* ss_collection;
			int ss_it;
			ss_collection = self->children;
			for (ss_it = 0; ss_it < gee_collection_get_size (GEE_COLLECTION (ss_collection)); ss_it = ss_it + 1) {
				GtkMateScope* ss;
				ss = ((GtkMateScope*) (gee_list_get (GEE_LIST (ss_collection), ss_it)));
				{
					char* _tmp1;
					_tmp1 = NULL;
					g_string_append (s, (_tmp1 = gtk_mate_scope_pretty (ss, indent + 1)));
					_tmp1 = (g_free (_tmp1), NULL);
					(ss == NULL ? NULL : (ss = (g_object_unref (ss), NULL)));
				}
			}
		}
	}
	_tmp2 = NULL;
	_tmp3 = NULL;
	return (_tmp3 = (_tmp2 = s->str, (_tmp2 == NULL ? NULL : g_strdup (_tmp2))), (s == NULL ? NULL : (s = (g_string_free (s, TRUE), NULL))), _tmp3);
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
	(self->children == NULL ? NULL : (self->children = (g_object_unref (self->children), NULL)));
	(self->parent == NULL ? NULL : (self->parent = (g_object_unref (self->parent), NULL)));
	G_OBJECT_CLASS (gtk_mate_scope_parent_class)->dispose (obj);
}


GType gtk_mate_scope_get_type (void) {
	static GType gtk_mate_scope_type_id = 0;
	if (G_UNLIKELY (gtk_mate_scope_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateScopeClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_scope_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateScope), 0, (GInstanceInitFunc) gtk_mate_scope_instance_init };
		gtk_mate_scope_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateScope", &g_define_type_info, 0);
	}
	return gtk_mate_scope_type_id;
}




