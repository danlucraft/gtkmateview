
#include "view.h"




enum  {
	GTK_MATE_VIEW_DUMMY_PROPERTY
};
static gpointer gtk_mate_view_parent_class = NULL;



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
	if (G_UNLIKELY (gtk_mate_view_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateViewClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_view_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateView), 0, (GInstanceInitFunc) gtk_mate_view_instance_init };
		gtk_mate_view_type_id = g_type_register_static (GTK_TYPE_SOURCE_VIEW, "GtkMateView", &g_define_type_info, 0);
	}
	return gtk_mate_view_type_id;
}




