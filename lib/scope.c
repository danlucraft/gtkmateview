
#include "scope.h"




enum  {
	GTK_MATE_SCOPE_DUMMY_PROPERTY
};
static gpointer gtk_mate_scope_parent_class = NULL;
static void gtk_mate_scope_dispose (GObject * obj);



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




