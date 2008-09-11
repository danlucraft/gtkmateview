
#include "view.h"
#include <gtk/gtk.h>
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
	g_return_val_if_fail (GTK_MATE_IS_VIEW (self), FALSE);
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
					gtk_mate_parser_change_theme ((GTK_MATE_BUFFER (gtk_text_view_get_buffer (GTK_TEXT_VIEW (self))))->parser, theme);
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
	g_return_if_fail (GTK_MATE_IS_VIEW (self));
	if ((GTK_MATE_BUFFER (gtk_text_view_get_buffer (GTK_TEXT_VIEW (self))))->parser != NULL && gtk_mate_parser_get_colourer ((GTK_MATE_BUFFER (gtk_text_view_get_buffer (GTK_TEXT_VIEW (self))))->parser) != NULL) {
		gtk_mate_colourer_set_global_settings (gtk_mate_parser_get_colourer ((GTK_MATE_BUFFER (gtk_text_view_get_buffer (GTK_TEXT_VIEW (self))))->parser), self);
	}
}


GtkMateView* gtk_mate_view_new (void) {
	GtkMateView * self;
	self = g_object_newv (GTK_MATE_TYPE_VIEW, 0, NULL);
	return self;
}


static void gtk_mate_view_class_init (GtkMateViewClass * klass) {
	gtk_mate_view_parent_class = g_type_class_peek_parent (klass);
}


static void gtk_mate_view_instance_init (GtkMateView * self) {
}


GType gtk_mate_view_get_type (void) {
	static GType gtk_mate_view_type_id = 0;
	if (gtk_mate_view_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateViewClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_view_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateView), 0, (GInstanceInitFunc) gtk_mate_view_instance_init };
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




