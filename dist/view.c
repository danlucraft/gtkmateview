
#include "view.h"
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include "theme.h"
#include "buffer.h"
#include "parser.h"
#include "colourer.h"




enum  {
	GTK_MATE_VIEW_DUMMY_PROPERTY
};
static gpointer gtk_mate_view_parent_class = NULL;
static int _vala_strcmp0 (const char * str1, const char * str2);



gboolean gtk_mate_view_set_theme_by_name (GtkMateView* self, const char* name) {
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (name != NULL, FALSE);
	{
		GeeArrayList* theme_collection;
		int theme_it;
		theme_collection = gtk_mate_theme_themes;
		for (theme_it = 0; theme_it < gee_collection_get_size (GEE_COLLECTION (theme_collection)); theme_it = theme_it + 1) {
			GtkMateTheme* theme;
			theme = ((GtkMateTheme*) (gee_list_get (GEE_LIST (theme_collection), theme_it)));
			{
				if (_vala_strcmp0 (theme->name, name) == 0) {
					gboolean _tmp0;
					gtk_mate_theme_init_for_use (theme);
					gtk_mate_parser_change_theme ((GTK_MATE_BUFFER (gtk_text_view_get_buffer (((GtkTextView*) (self)))))->parser, theme);
					gtk_mate_view_set_global_theme_settings (self);
					return (_tmp0 = TRUE, (theme == NULL ? NULL : (theme = (g_object_unref (theme), NULL))), _tmp0);
				}
				(theme == NULL ? NULL : (theme = (g_object_unref (theme), NULL)));
			}
		}
	}
	return FALSE;
}


void gtk_mate_view_set_global_theme_settings (GtkMateView* self) {
	g_return_if_fail (self != NULL);
	if ((GTK_MATE_BUFFER (gtk_text_view_get_buffer (((GtkTextView*) (self)))))->parser != NULL && gtk_mate_parser_get_colourer ((GTK_MATE_BUFFER (gtk_text_view_get_buffer (((GtkTextView*) (self)))))->parser) != NULL) {
		gtk_mate_colourer_set_global_settings (gtk_mate_parser_get_colourer ((GTK_MATE_BUFFER (gtk_text_view_get_buffer (((GtkTextView*) (self)))))->parser), self);
	}
}


/* TODO finish this off once Vala gets signal_connect_after support
 public void connect_signals() {
 stdout.printf("mateview connect_signals\n");
 this.parent_set += (prev_parent) => {
 if (this.get_parent() is Gtk.ScrolledWindow) {
 stdout.printf("parent is scrolled window\n");
 }
 };
 }*/
void gtk_mate_view_value_changed_handler (GtkMateView* self) {
	GtkMateParser* parser;
	g_return_if_fail (self != NULL);
	parser = gtk_mate_view_get_parser (self);
	if (parser != NULL) {
		gtk_mate_parser_last_visible_line_changed (parser, gtk_mate_view_last_visible_line (self));
	}
	(parser == NULL ? NULL : (parser = (g_object_unref (parser), NULL)));
}


GtkMateParser* gtk_mate_view_get_parser (GtkMateView* self) {
	GtkMateParser* _tmp0;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0 = NULL;
	return (_tmp0 = (GTK_MATE_BUFFER (gtk_text_view_get_buffer (((GtkTextView*) (self)))))->parser, (_tmp0 == NULL ? NULL : g_object_ref (_tmp0)));
}


gint gtk_mate_view_last_visible_line (GtkMateView* self) {
	GdkRectangle rect = {0};
	gint bufy;
	GtkTextIter iter = {0};
	gint line;
	g_return_val_if_fail (self != NULL, 0);
	gtk_text_view_get_visible_rect (((GtkTextView*) (self)), &rect);
	bufy = rect.y + rect.height;
	gtk_text_view_get_line_at_y (((GtkTextView*) (self)), &iter, bufy, NULL);
	line = gtk_text_iter_get_line (&iter);
	return line;
}


GtkMateView* gtk_mate_view_construct (GType object_type) {
	GtkMateView * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


GtkMateView* gtk_mate_view_new (void) {
	return gtk_mate_view_construct (GTK_MATE_TYPE_VIEW);
}


static void gtk_mate_view_class_init (GtkMateViewClass * klass) {
	gtk_mate_view_parent_class = g_type_class_peek_parent (klass);
}


static void gtk_mate_view_instance_init (GtkMateView * self) {
}


GType gtk_mate_view_get_type (void) {
	static GType gtk_mate_view_type_id = 0;
	if (gtk_mate_view_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateViewClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_view_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateView), 0, (GInstanceInitFunc) gtk_mate_view_instance_init, NULL };
		gtk_mate_view_type_id = g_type_register_static (GTK_TYPE_SOURCE_VIEW, "GtkMateView", &g_define_type_info, 0);
	}
	return gtk_mate_view_type_id;
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




