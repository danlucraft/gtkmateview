
#include "colourer.h"
#include <gee/map.h>
#include <stdio.h>
#include <pango/pango.h>
#include "buffer.h"
#include "theme.h"
#include "scope.h"
#include "pattern.h"
#include "parser.h"




static glong string_get_length (const char* self);
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
static void gtk_mate_colourer_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



static glong string_get_length (const char* self) {
	g_return_val_if_fail (self != NULL, 0L);
	return g_utf8_strlen (self, -1);
}


void gtk_mate_colourer_set_global_settings (GtkMateColourer* self, GtkMateView* view) {
	char* bg_colour;
	char* fg_colour;
	g_return_if_fail (self != NULL);
	g_return_if_fail (view != NULL);
	/*stdout.printf("set_theme_settings()\n");*/
	bg_colour = ((char*) (gee_map_get (((GeeMap*) (self->priv->_theme->global_settings)), "background")));
	if (bg_colour != NULL && _vala_strcmp0 (bg_colour, "") != 0) {
		char* _tmp0;
		GdkColor _tmp1 = {0};
		_tmp0 = NULL;
		bg_colour = (_tmp0 = gtk_mate_colourer_merge_colour ("#FFFFFF", bg_colour), (bg_colour = (g_free (bg_colour), NULL)), _tmp0);
		fprintf (stdout, "bg_colour: %s\n", bg_colour);
		gtk_widget_modify_base ((GTK_WIDGET (view)), GTK_STATE_NORMAL, (_tmp1 = gtk_mate_colourer_parse_colour (self, bg_colour), &_tmp1));
	}
	/* ((Gtk.SourceView) view).background = bg_colour;*/
	fg_colour = ((char*) (gee_map_get (((GeeMap*) (self->priv->_theme->global_settings)), "foreground")));
	if (fg_colour != NULL && _vala_strcmp0 (fg_colour, "") != 0) {
		char* _tmp2;
		GdkColor _tmp3 = {0};
		_tmp2 = NULL;
		fg_colour = (_tmp2 = gtk_mate_colourer_merge_colour ("#FFFFFF", fg_colour), (fg_colour = (g_free (fg_colour), NULL)), _tmp2);
		gtk_widget_modify_text ((GTK_WIDGET (view)), GTK_STATE_NORMAL, (_tmp3 = gtk_mate_colourer_parse_colour (self, fg_colour), &_tmp3));
	}
	bg_colour = (g_free (bg_colour), NULL);
	fg_colour = (g_free (fg_colour), NULL);
}


GtkMateColourer* gtk_mate_colourer_construct (GType object_type, GtkMateBuffer* buffer) {
	GtkMateColourer * self;
	g_return_val_if_fail (buffer != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	gtk_mate_colourer_set_buffer (self, buffer);
	return self;
}


GtkMateColourer* gtk_mate_colourer_new (GtkMateBuffer* buffer) {
	return gtk_mate_colourer_construct (GTK_MATE_TYPE_COLOURER, buffer);
}


GdkColor gtk_mate_colourer_parse_colour (GtkMateColourer* self, const char* colour) {
	GdkColor c = {0};
	0;
	0;
	gdk_color_parse (colour, &c);
	return c;
}


void gtk_mate_colourer_colour_line_with_scopes (GtkMateColourer* self, GeeArrayList* scopes) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (scopes != NULL);
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
				if (scope->parent == NULL) {
					(scope == NULL ? NULL : (scope = (g_object_unref (scope), NULL)));
					continue;
				}
				if (gtk_mate_scope_get_name (scope) == NULL && scope->pattern != NULL && (GTK_MATE_IS_SINGLE_PATTERN (scope->pattern) || (GTK_MATE_DOUBLE_PATTERN (scope->pattern))->content_name == NULL)) {
					/*stdout.printf("  no pattern name\n");*/
					(scope == NULL ? NULL : (scope = (g_object_unref (scope), NULL)));
					continue;
				}
				/* if (scope.is_coloured) {
				 //stdout.printf("  already coloured\n");
				 continue;
				 }*/
				gtk_mate_colourer_colour_scope (self, scope, FALSE, TRUE);
				if (GTK_MATE_IS_DOUBLE_PATTERN (scope->pattern) && (GTK_MATE_DOUBLE_PATTERN (scope->pattern))->content_name != NULL) {
					gtk_mate_colourer_colour_scope (self, scope, TRUE, TRUE);
				}
				(scope == NULL ? NULL : (scope = (g_object_unref (scope), NULL)));
			}
		}
	}
}


void gtk_mate_colourer_colour_scope (GtkMateColourer* self, GtkMateScope* scope, gboolean inner, gboolean force) {
	gint priority;
	GtkTextTag* tag;
	GtkTextIter start_iter = {0};
	GtkTextIter end_iter = {0};
	GtkMateThemeSetting* setting;
	char* tag_name;
	GtkTextTagTable* _tmp7;
	GtkTextTagTable* tag_table;
	gboolean new_tag;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	/* stdout.printf("colour_scope: %s (%s) [%d - %d]\n", scope.name, inner ? "true" : "false",
	   scope.start_offset(), scope.end_offset());*/
	priority = gtk_mate_scope_priority (scope, inner);
	tag = NULL;
	/* stdout.printf("  priority: %d\n", priority);*/
	gtk_mate_scope_set_is_coloured (scope, TRUE);
	if (inner) {
		start_iter = gtk_mate_scope_inner_start_iter (scope);
		end_iter = gtk_mate_scope_inner_end_iter (scope);
		if (scope->inner_tag != NULL) {
			GtkTextTag* _tmp1;
			GtkTextTag* _tmp0;
			_tmp1 = NULL;
			_tmp0 = NULL;
			tag = (_tmp1 = (_tmp0 = scope->inner_tag, (_tmp0 == NULL ? NULL : g_object_ref (_tmp0))), (tag == NULL ? NULL : (tag = (g_object_unref (tag), NULL))), _tmp1);
		}
	} else {
		start_iter = gtk_mate_scope_start_iter (scope);
		end_iter = gtk_mate_scope_end_iter (scope);
		if (scope->tag != NULL) {
			GtkTextTag* _tmp3;
			GtkTextTag* _tmp2;
			_tmp3 = NULL;
			_tmp2 = NULL;
			tag = (_tmp3 = (_tmp2 = scope->tag, (_tmp2 == NULL ? NULL : g_object_ref (_tmp2))), (tag == NULL ? NULL : (tag = (g_object_unref (tag), NULL))), _tmp3);
		}
	}
	/* TODO: allow for multiple settings that set different 
	 parts of the style.*/
	setting = NULL;
	tag_name = NULL;
	if (tag == NULL || force) {
		GtkMateThemeSetting* _tmp4;
		_tmp4 = NULL;
		setting = (_tmp4 = gtk_mate_theme_settings_for_scope (self->priv->_theme, scope, inner), (setting == NULL ? NULL : (setting = (g_object_unref (setting), NULL))), _tmp4);
		if (setting == NULL) {
			char* _tmp5;
			_tmp5 = NULL;
			tag_name = (_tmp5 = g_strdup_printf ("gmv(%d):default", priority - 1), (tag_name = (g_free (tag_name), NULL)), _tmp5);
		} else {
			char* _tmp6;
			_tmp6 = NULL;
			tag_name = (_tmp6 = g_strdup_printf ("gmv(%d):%s", priority - 1, gtk_mate_scope_get_name (scope)), (tag_name = (g_free (tag_name), NULL)), _tmp6);
		}
	}
	_tmp7 = NULL;
	tag_table = (_tmp7 = gtk_text_buffer_get_tag_table (((GtkTextBuffer*) (self->priv->_buffer))), (_tmp7 == NULL ? NULL : g_object_ref (_tmp7)));
	new_tag = FALSE;
	if (tag == NULL || force) {
		GtkTextTag* _tmp9;
		GtkTextTag* _tmp8;
		_tmp9 = NULL;
		_tmp8 = NULL;
		tag = (_tmp9 = (_tmp8 = gtk_text_tag_table_lookup (tag_table, tag_name), (_tmp8 == NULL ? NULL : g_object_ref (_tmp8))), (tag == NULL ? NULL : (tag = (g_object_unref (tag), NULL))), _tmp9);
		if (tag == NULL) {
			GtkTextTag* _tmp11;
			GtkTextTag* _tmp10;
			/* stdout.printf("create_tag\n");*/
			_tmp11 = NULL;
			_tmp10 = NULL;
			tag = (_tmp11 = (_tmp10 = gtk_text_buffer_create_tag (((GtkTextBuffer*) (self->priv->_buffer)), tag_name, NULL), (_tmp10 == NULL ? NULL : g_object_ref (_tmp10))), (tag == NULL ? NULL : (tag = (g_object_unref (tag), NULL))), _tmp11);
			new_tag = TRUE;
		}
	}
	/* stdout.printf("      tag: '%s'\n", tag_name);*/
	if (setting != NULL) {
		gtk_mate_colourer_set_tag_properties (self, scope, tag, setting);
	}
	if (inner) {
		GtkTextTag* _tmp13;
		GtkTextTag* _tmp12;
		_tmp13 = NULL;
		_tmp12 = NULL;
		scope->inner_tag = (_tmp13 = (_tmp12 = tag, (_tmp12 == NULL ? NULL : g_object_ref (_tmp12))), (scope->inner_tag == NULL ? NULL : (scope->inner_tag = (g_object_unref (scope->inner_tag), NULL))), _tmp13);
	} else {
		GtkTextTag* _tmp15;
		GtkTextTag* _tmp14;
		_tmp15 = NULL;
		_tmp14 = NULL;
		scope->tag = (_tmp15 = (_tmp14 = tag, (_tmp14 == NULL ? NULL : g_object_ref (_tmp14))), (scope->tag == NULL ? NULL : (scope->tag = (g_object_unref (scope->tag), NULL))), _tmp15);
	}
	gtk_text_buffer_apply_tag (((GtkTextBuffer*) (self->priv->_buffer)), tag, &start_iter, &end_iter);
	if (new_tag) {
		gtk_mate_parser_added_tag (self->priv->_buffer->parser, tag);
	}
	(tag == NULL ? NULL : (tag = (g_object_unref (tag), NULL)));
	(setting == NULL ? NULL : (setting = (g_object_unref (setting), NULL)));
	tag_name = (g_free (tag_name), NULL);
	(tag_table == NULL ? NULL : (tag_table = (g_object_unref (tag_table), NULL)));
}


void gtk_mate_colourer_set_tag_properties (GtkMateColourer* self, GtkMateScope* scope, GtkTextTag* tag, GtkMateThemeSetting* setting) {
	char* font_style;
	char* background;
	char* merged_bg_colour;
	char* parent_bg;
	char* foreground;
	char* parent_fg;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	g_return_if_fail (tag != NULL);
	g_return_if_fail (setting != NULL);
	font_style = ((char*) (gee_map_get (((GeeMap*) (setting->settings)), "fontStyle")));
	if (_vala_strcmp0 (font_style, "italic") == 0) {
		PangoStyle _tmp0;
		g_object_set (tag, "style", PANGO_STYLE_ITALIC | (g_object_get (G_OBJECT (tag), "style", &_tmp0, NULL), _tmp0), NULL);
	} else {
		PangoStyle _tmp1;
		g_object_set (tag, "style", PANGO_STYLE_NORMAL | (g_object_get (G_OBJECT (tag), "style", &_tmp1, NULL), _tmp1), NULL);
	}
	if (_vala_strcmp0 (font_style, "underline") == 0) {
		PangoStyle _tmp2;
		g_object_set (tag, "style", PANGO_UNDERLINE_SINGLE | (g_object_get (G_OBJECT (tag), "style", &_tmp2, NULL), _tmp2), NULL);
	} else {
		PangoStyle _tmp3;
		g_object_set (tag, "style", PANGO_UNDERLINE_NONE | (g_object_get (G_OBJECT (tag), "style", &_tmp3, NULL), _tmp3), NULL);
	}
	background = ((char*) (gee_map_get (((GeeMap*) (setting->settings)), "background")));
	/* stdout.printf("        background:        %s\n", background);*/
	merged_bg_colour = NULL;
	parent_bg = gtk_mate_scope_nearest_background_colour (scope);
	if (parent_bg == NULL) {
		char* _tmp4;
		_tmp4 = NULL;
		parent_bg = (_tmp4 = ((char*) (gee_map_get (((GeeMap*) (self->priv->_theme->global_settings)), "background"))), (parent_bg = (g_free (parent_bg), NULL)), _tmp4);
	}
	/* stdout.printf("        parent_background: %s\n", parent_bg);*/
	if (background != NULL && _vala_strcmp0 (background, "") != 0) {
		char* _tmp5;
		_tmp5 = NULL;
		merged_bg_colour = (_tmp5 = gtk_mate_colourer_merge_colour (parent_bg, background), (merged_bg_colour = (g_free (merged_bg_colour), NULL)), _tmp5);
		if (merged_bg_colour != NULL) {
			char* _tmp7;
			const char* _tmp6;
			_tmp7 = NULL;
			_tmp6 = NULL;
			scope->bg_colour = (_tmp7 = (_tmp6 = merged_bg_colour, (_tmp6 == NULL ? NULL : g_strdup (_tmp6))), (scope->bg_colour = (g_free (scope->bg_colour), NULL)), _tmp7);
			g_object_set (tag, "background", merged_bg_colour, NULL);
		}
	} else {
		char* _tmp9;
		const char* _tmp8;
		/* stdout.printf("       tag.background = %s\n", merged_bg_colour);*/
		_tmp9 = NULL;
		_tmp8 = NULL;
		merged_bg_colour = (_tmp9 = (_tmp8 = parent_bg, (_tmp8 == NULL ? NULL : g_strdup (_tmp8))), (merged_bg_colour = (g_free (merged_bg_colour), NULL)), _tmp9);
	}
	/* stdout.printf("        merged_bg_colour:  %s\n", merged_bg_colour);*/
	foreground = ((char*) (gee_map_get (((GeeMap*) (setting->settings)), "foreground")));
	parent_fg = gtk_mate_scope_nearest_foreground_colour (scope);
	if (parent_fg == NULL) {
		char* _tmp10;
		_tmp10 = NULL;
		parent_fg = (_tmp10 = ((char*) (gee_map_get (((GeeMap*) (self->priv->_theme->global_settings)), "foreground"))), (parent_fg = (g_free (parent_fg), NULL)), _tmp10);
	}
	/* stdout.printf("        foreground:        %s\n", foreground);*/
	if (foreground != NULL && _vala_strcmp0 (foreground, "") != 0) {
		char* merged_fg_colour;
		merged_fg_colour = NULL;
		if (parent_fg != NULL) {
			char* _tmp11;
			_tmp11 = NULL;
			merged_fg_colour = (_tmp11 = gtk_mate_colourer_merge_colour (parent_fg, foreground), (merged_fg_colour = (g_free (merged_fg_colour), NULL)), _tmp11);
		} else {
			char* _tmp13;
			const char* _tmp12;
			_tmp13 = NULL;
			_tmp12 = NULL;
			merged_fg_colour = (_tmp13 = (_tmp12 = foreground, (_tmp12 == NULL ? NULL : g_strdup (_tmp12))), (merged_fg_colour = (g_free (merged_fg_colour), NULL)), _tmp13);
		}
		if (merged_fg_colour != NULL) {
			char* _tmp15;
			const char* _tmp14;
			_tmp15 = NULL;
			_tmp14 = NULL;
			scope->fg_colour = (_tmp15 = (_tmp14 = merged_fg_colour, (_tmp14 == NULL ? NULL : g_strdup (_tmp14))), (scope->fg_colour = (g_free (scope->fg_colour), NULL)), _tmp15);
			g_object_set (tag, "foreground", merged_fg_colour, NULL);
		}
		merged_fg_colour = (g_free (merged_fg_colour), NULL);
	}
	font_style = (g_free (font_style), NULL);
	background = (g_free (background), NULL);
	merged_bg_colour = (g_free (merged_bg_colour), NULL);
	parent_bg = (g_free (parent_bg), NULL);
	foreground = (g_free (foreground), NULL);
	parent_fg = (g_free (parent_fg), NULL);
}


/* stdout.printf("       merged_fg_colour: %s\n", merged_fg_colour);
 stdout.printf("\n");*/
gint gtk_mate_colourer_char_to_hex (gunichar ch) {
	if (g_unichar_isxdigit (ch)) {
		return g_unichar_xdigit_value (ch);
	}
	return 0;
}


/* Here parent_colour is like '#FFFFFF' and
 colour is like '#000000DD'.*/
char* gtk_mate_colourer_merge_colour (const char* parent_colour, const char* colour) {
	gint pre_r;
	gint pre_g;
	gint pre_b;
	gint post_r;
	gint post_g;
	gint post_b;
	gint opacity;
	gint new_r;
	gint new_g;
	gint new_b;
	char* new_colour;
	char* _tmp5;
	g_return_val_if_fail (colour != NULL, NULL);
	pre_r = 0;
	pre_g = 0;
	pre_b = 0;
	post_r = 0;
	post_g = 0;
	post_b = 0;
	opacity = 0;
	new_r = 0;
	new_g = 0;
	new_b = 0;
	new_colour = NULL;
	if (parent_colour == NULL) {
		char* _tmp0;
		_tmp0 = NULL;
		return (_tmp0 = NULL, (new_colour = (g_free (new_colour), NULL)), _tmp0);
	}
	if (string_get_length (colour) == 7) {
		const char* _tmp1;
		char* _tmp2;
		_tmp1 = NULL;
		_tmp2 = NULL;
		return (_tmp2 = (_tmp1 = colour, (_tmp1 == NULL ? NULL : g_strdup (_tmp1))), (new_colour = (g_free (new_colour), NULL)), _tmp2);
	}
	if (string_get_length (colour) == 9) {
		char* _tmp3;
		pre_r = gtk_mate_colourer_char_to_hex (g_utf8_get_char (g_utf8_offset_to_pointer (parent_colour, 1))) * 16 + gtk_mate_colourer_char_to_hex (g_utf8_get_char (g_utf8_offset_to_pointer (parent_colour, 2)));
		pre_g = gtk_mate_colourer_char_to_hex (g_utf8_get_char (g_utf8_offset_to_pointer (parent_colour, 3))) * 16 + gtk_mate_colourer_char_to_hex (g_utf8_get_char (g_utf8_offset_to_pointer (parent_colour, 4)));
		pre_b = gtk_mate_colourer_char_to_hex (g_utf8_get_char (g_utf8_offset_to_pointer (parent_colour, 5))) * 16 + gtk_mate_colourer_char_to_hex (g_utf8_get_char (g_utf8_offset_to_pointer (parent_colour, 6)));
		post_r = gtk_mate_colourer_char_to_hex (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 1))) * 16 + gtk_mate_colourer_char_to_hex (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 2)));
		post_g = gtk_mate_colourer_char_to_hex (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 3))) * 16 + gtk_mate_colourer_char_to_hex (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 4)));
		post_b = gtk_mate_colourer_char_to_hex (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 5))) * 16 + gtk_mate_colourer_char_to_hex (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 6)));
		opacity = gtk_mate_colourer_char_to_hex (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 7))) * 16 + gtk_mate_colourer_char_to_hex (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 8)));
		new_r = (pre_r * (255 - opacity) + post_r * opacity) / 255;
		new_g = (pre_g * (255 - opacity) + post_g * opacity) / 255;
		new_b = (pre_b * (255 - opacity) + post_b * opacity) / 255;
		_tmp3 = NULL;
		new_colour = (_tmp3 = g_strdup_printf ("#%.2x%.2x%.2x", ((guint) (new_r)), ((guint) (new_g)), ((guint) (new_b))), (new_colour = (g_free (new_colour), NULL)), _tmp3);
		/* stdout.printf("%s/%s/%s - %d,%d,%d\n", parent_colour, colour, new_colour, new_r, new_g, new_b);*/
		return new_colour;
	}
	_tmp5 = NULL;
	return (_tmp5 = g_strdup ("#000000"), (new_colour = (g_free (new_colour), NULL)), _tmp5);
}


void gtk_mate_colourer_uncolour_scopes (GtkMateColourer* self, GeeArrayList* scopes) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (scopes != NULL);
	{
		GeeArrayList* scope_collection;
		int scope_it;
		scope_collection = scopes;
		for (scope_it = 0; scope_it < gee_collection_get_size (GEE_COLLECTION (scope_collection)); scope_it = scope_it + 1) {
			GtkMateScope* scope;
			scope = ((GtkMateScope*) (gee_list_get (GEE_LIST (scope_collection), scope_it)));
			{
				gtk_mate_colourer_uncolour_scope (self, scope, TRUE);
				(scope == NULL ? NULL : (scope = (g_object_unref (scope), NULL)));
			}
		}
	}
}


void gtk_mate_colourer_uncolour_scope (GtkMateColourer* self, GtkMateScope* scope, gboolean recurse) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope != NULL);
	/* stdout.printf("uncolour scope: %s\n", scope.name);*/
	if (scope->inner_tag != NULL) {
		GtkTextIter _tmp1 = {0};
		GtkTextIter _tmp0 = {0};
		gtk_text_buffer_remove_tag (((GtkTextBuffer*) (self->priv->_buffer)), scope->inner_tag, (_tmp0 = gtk_mate_scope_inner_start_iter (scope), &_tmp0), (_tmp1 = gtk_mate_scope_inner_end_iter (scope), &_tmp1));
	}
	if (scope->tag != NULL) {
		GtkTextIter _tmp3 = {0};
		GtkTextIter _tmp2 = {0};
		gtk_text_buffer_remove_tag (((GtkTextBuffer*) (self->priv->_buffer)), scope->tag, (_tmp2 = gtk_mate_scope_start_iter (scope), &_tmp2), (_tmp3 = gtk_mate_scope_end_iter (scope), &_tmp3));
	}
	gtk_mate_scope_set_is_coloured (scope, FALSE);
	if (recurse) {
		GSequenceIter* iter;
		iter = g_sequence_get_begin_iter (gtk_mate_scope_get_children (scope));
		while (!g_sequence_iter_is_end (iter)) {
			gtk_mate_colourer_uncolour_scope (self, ((GtkMateScope*) (g_sequence_get (iter))), recurse);
			iter = g_sequence_iter_next (iter);
		}
	}
}


GtkMateBuffer* gtk_mate_colourer_get_buffer (GtkMateColourer* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_buffer;
}


void gtk_mate_colourer_set_buffer (GtkMateColourer* self, GtkMateBuffer* value) {
	GtkMateBuffer* _tmp2;
	GtkMateBuffer* _tmp1;
	g_return_if_fail (self != NULL);
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_buffer = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (self->priv->_buffer == NULL ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL))), _tmp2);
	g_object_notify (((GObject *) (self)), "buffer");
}


GtkMateTheme* gtk_mate_colourer_get_theme (GtkMateColourer* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_theme;
}


void gtk_mate_colourer_set_theme (GtkMateColourer* self, GtkMateTheme* value) {
	GtkMateTheme* _tmp2;
	GtkMateTheme* _tmp1;
	g_return_if_fail (self != NULL);
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


static void gtk_mate_colourer_finalize (GObject* obj) {
	GtkMateColourer * self;
	self = GTK_MATE_COLOURER (obj);
	(self->priv->_buffer == NULL ? NULL : (self->priv->_buffer = (g_object_unref (self->priv->_buffer), NULL)));
	(self->priv->_theme == NULL ? NULL : (self->priv->_theme = (g_object_unref (self->priv->_theme), NULL)));
	G_OBJECT_CLASS (gtk_mate_colourer_parent_class)->finalize (obj);
}


GType gtk_mate_colourer_get_type (void) {
	static GType gtk_mate_colourer_type_id = 0;
	if (gtk_mate_colourer_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateColourerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_colourer_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateColourer), 0, (GInstanceInitFunc) gtk_mate_colourer_instance_init, NULL };
		gtk_mate_colourer_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateColourer", &g_define_type_info, 0);
	}
	return gtk_mate_colourer_type_id;
}


static int _vala_strcmp0 (const char * str1, const char * str2) {
	if (str1 == NULL) {
		return -(str1 != str2);
	}
	if (str2 == NULL) {
		return (str1 != str2);
	}
	return strcmp (str1, str2);
}




