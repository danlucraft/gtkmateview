
#include "colourer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"
#include "scope.h"
#include "pattern.h"




struct _GtkMateColourerPrivate {
	GtkMateBuffer* _buffer;
	GtkMateTheme* _theme;
};

#define GTK_MATE_COLOURER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_TYPE_COLOURER, GtkMateColourerPrivate))
enum  {
	GTK_MATE_COLOURER_DUMMY_PROPERTY,
	GTK_MATE_COLOURER_BUFFER,
	GTK_MATE_COLOURER_THEME
};
static gpointer gtk_mate_colourer_parent_class = NULL;
static void gtk_mate_colourer_finalize (GObject * obj);



GtkMateColourer* gtk_mate_colourer_new (GtkMateBuffer* buffer) {
	GtkMateColourer * self;
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (buffer), NULL);
	self = g_object_newv (GTK_MATE_TYPE_COLOURER, 0, NULL);
	gtk_mate_colourer_set_buffer (self, buffer);
	return self;
}


void gtk_mate_colourer_colour_line_with_scopes (GtkMateColourer* self, GeeArrayList* scopes) {
	g_return_if_fail (GTK_MATE_IS_COLOURER (self));
	g_return_if_fail (GEE_IS_ARRAY_LIST (scopes));
	if (self->priv->_theme == NULL) {
		return;
	}
	{
		GeeArrayList* scope_collection;
		int scope_it;
		scope_collection = scopes;
		for (scope_it = 0; scope_it < gee_collection_get_size (GEE_COLLECTION (scope_collection)); scope_it = scope_it + 1) {
			GtkMateScope* scope;
			scope = ((GtkMateScope*) (gee_list_get (GEE_LIST (scope_collection), scope_it)));
			{
				fprintf (stdout, "colouring scope: %s\n", gtk_mate_scope_get_name (scope));
				if (scope->parent == NULL) {
					fprintf (stdout, "  no parent\n");
					(scope == NULL ? NULL : (scope = (g_object_unref (scope), NULL)));
					continue;
				}
				if (gtk_mate_scope_get_name (scope) == NULL && scope->pattern != NULL && (GTK_MATE_IS_SINGLE_PATTERN (scope->pattern) || (GTK_MATE_DOUBLE_PATTERN (scope->pattern))->content_name == NULL)) {
					fprintf (stdout, "  no pattern name\n");
					(scope == NULL ? NULL : (scope = (g_object_unref (scope), NULL)));
					continue;
				}
				if (gtk_mate_scope_get_is_coloured (scope)) {
					fprintf (stdout, "  already coloured\n");
					(scope == NULL ? NULL : (scope = (g_object_unref (scope), NULL)));
					continue;
				}
				gtk_mate_colourer_colour_scope (self, scope, FALSE);
				if (GTK_MATE_IS_DOUBLE_PATTERN (scope->pattern) && (GTK_MATE_DOUBLE_PATTERN (scope->pattern))->content_name != NULL) {
					gtk_mate_colourer_colour_scope (self, scope, TRUE);
				}
				(scope == NULL ? NULL : (scope = (g_object_unref (scope), NULL)));
			}
		}
	}
}


void gtk_mate_colourer_colour_scope (GtkMateColourer* self, GtkMateScope* scope, gboolean colour_inner) {
	gint priority;
	GtkTextTag* tag;
	g_return_if_fail (GTK_MATE_IS_COLOURER (self));
	g_return_if_fail (GTK_MATE_IS_SCOPE (scope));
	fprintf (stdout, "  colouring\n");
	priority = gtk_mate_scope_priority (scope);
	tag = NULL;
	fprintf (stdout, "  priority: %d\n", priority);
	gtk_mate_scope_set_is_coloured (scope, TRUE);
	if (colour_inner) {
		GtkTextIter start_iter;
		GtkTextIter end_iter;
		start_iter = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, scope->inner_start_mark);
		end_iter = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, scope->inner_end_mark);
		if (scope->inner_tag != NULL) {
			GtkTextTag* _tmp1;
			GtkTextTag* _tmp0;
			_tmp1 = NULL;
			_tmp0 = NULL;
			tag = (_tmp1 = (_tmp0 = scope->inner_tag, (_tmp0 == NULL ? NULL : g_object_ref (_tmp0))), (tag == NULL ? NULL : (tag = (g_object_unref (tag), NULL))), _tmp1);
		}
	} else {
		GtkTextIter start_iter;
		GtkTextIter end_iter;
		start_iter = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, scope->start_mark);
		end_iter = gtk_mate_buffer_iter_from_mark (self->priv->_buffer, scope->end_mark);
		if (scope->tag != NULL) {
			GtkTextTag* _tmp3;
			GtkTextTag* _tmp2;
			_tmp3 = NULL;
			_tmp2 = NULL;
			tag = (_tmp3 = (_tmp2 = scope->tag, (_tmp2 == NULL ? NULL : g_object_ref (_tmp2))), (tag == NULL ? NULL : (tag = (g_object_unref (tag), NULL))), _tmp3);
		}
	}
	if (tag == NULL) {
		GeeArrayList* settings;
		settings = gtk_mate_theme_settings_for_scope (self->priv->_theme, scope);
		(settings == NULL ? NULL : (settings = (g_object_unref (settings), NULL)));
	}
	(tag == NULL ? NULL : (tag = (g_object_unref (tag), NULL)));
}


GtkMateBuffer* gtk_mate_colourer_get_buffer (GtkMateColourer* self) {
	g_return_val_if_fail (GTK_MATE_IS_COLOURER (self), NULL);
	return self->priv->_buffer;
}


void gtk_mate_colourer_set_buffer (GtkMateColourer* self, GtkMateBuffer* value) {
	GtkMateBuffer* _tmp2;
	GtkMateBuffer* _tmp1;
	g_return_if_fail (GTK_MATE_IS_COLOURER (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_buffer = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (self->priv->_buffer == NULL ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL))), _tmp2);
	g_object_notify (((GObject *) (self)), "buffer");
}


GtkMateTheme* gtk_mate_colourer_get_theme (GtkMateColourer* self) {
	g_return_val_if_fail (GTK_MATE_IS_COLOURER (self), NULL);
	return self->priv->_theme;
}


void gtk_mate_colourer_set_theme (GtkMateColourer* self, GtkMateTheme* value) {
	GtkMateTheme* _tmp2;
	GtkMateTheme* _tmp1;
	g_return_if_fail (GTK_MATE_IS_COLOURER (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_theme = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (self->priv->_theme == NULL ? NULL : (self->priv->_theme = (g_object_unref (self->priv->_theme), NULL))), _tmp2);
	g_object_notify (((GObject *) (self)), "theme");
}


static void gtk_mate_colourer_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateColourer * self;
	self = GTK_MATE_COLOURER (object);
	switch (property_id) {
		case GTK_MATE_COLOURER_BUFFER:
		g_value_set_object (value, gtk_mate_colourer_get_buffer (self));
		break;
		case GTK_MATE_COLOURER_THEME:
		g_value_set_object (value, gtk_mate_colourer_get_theme (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_colourer_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GtkMateColourer * self;
	self = GTK_MATE_COLOURER (object);
	switch (property_id) {
		case GTK_MATE_COLOURER_BUFFER:
		gtk_mate_colourer_set_buffer (self, g_value_get_object (value));
		break;
		case GTK_MATE_COLOURER_THEME:
		gtk_mate_colourer_set_theme (self, g_value_get_object (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_colourer_class_init (GtkMateColourerClass * klass) {
	gtk_mate_colourer_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GtkMateColourerPrivate));
	G_OBJECT_CLASS (klass)->get_property = gtk_mate_colourer_get_property;
	G_OBJECT_CLASS (klass)->set_property = gtk_mate_colourer_set_property;
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_colourer_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_COLOURER_BUFFER, g_param_spec_object ("buffer", "buffer", "buffer", GTK_MATE_TYPE_BUFFER, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_COLOURER_THEME, g_param_spec_object ("theme", "theme", "theme", GTK_MATE_TYPE_THEME, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void gtk_mate_colourer_instance_init (GtkMateColourer * self) {
	self->priv = GTK_MATE_COLOURER_GET_PRIVATE (self);
}


static void gtk_mate_colourer_finalize (GObject * obj) {
	GtkMateColourer * self;
	self = GTK_MATE_COLOURER (obj);
	(self->priv->_buffer == NULL ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL)));
	(self->priv->_theme == NULL ? NULL : (self->priv->_theme = (g_object_unref (self->priv->_theme), NULL)));
	G_OBJECT_CLASS (gtk_mate_colourer_parent_class)->finalize (obj);
}


GType gtk_mate_colourer_get_type (void) {
	static GType gtk_mate_colourer_type_id = 0;
	if (gtk_mate_colourer_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateColourerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_colourer_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateColourer), 0, (GInstanceInitFunc) gtk_mate_colourer_instance_init };
		gtk_mate_colourer_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateColourer", &g_define_type_info, 0);
	}
	return gtk_mate_colourer_type_id;
}




