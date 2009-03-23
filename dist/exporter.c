
#include "exporter.h"
#include "buffer.h"
#include "parser.h"
#include "colourer.h"
#include "theme.h"




enum  {
	GTK_MATE_EXPORTER_DUMMY_PROPERTY
};
static char* gtk_mate_exporter_html_header (GtkMateExporter* self, const char* title);
static char* gtk_mate_exporter_css (GtkMateExporter* self);
static char* gtk_mate_exporter_html (GtkMateExporter* self);
static gpointer gtk_mate_exporter_parent_class = NULL;
static void gtk_mate_exporter_finalize (GObject* obj);



GtkMateExporter* gtk_mate_exporter_construct (GType object_type, GtkMateView* v) {
	GtkMateExporter * self;
	GtkMateView* _tmp1;
	GtkMateView* _tmp0;
	g_return_val_if_fail (v != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	_tmp1 = NULL;
	_tmp0 = NULL;
	self->view = (_tmp1 = (_tmp0 = v, (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0)), (self->view == NULL) ? NULL : (self->view = (g_object_unref (self->view), NULL)), _tmp1);
	return self;
}


GtkMateExporter* gtk_mate_exporter_new (GtkMateView* v) {
	return gtk_mate_exporter_construct (GTK_MATE_TYPE_EXPORTER, v);
}


char* gtk_mate_exporter_to_html (GtkMateExporter* self, const char* title) {
	char* html;
	char* _tmp0;
	char* _tmp1;
	char* _tmp2;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (title != NULL, NULL);
	html = gtk_mate_exporter_html_header (self, title);
	_tmp0 = NULL;
	_tmp1 = NULL;
	_tmp2 = NULL;
	return (_tmp2 = (_tmp1 = g_strconcat (html, _tmp0 = gtk_mate_exporter_css (self), NULL), _tmp0 = (g_free (_tmp0), NULL), _tmp1), html = (g_free (html), NULL), _tmp2);
}


static char* gtk_mate_exporter_html_header (GtkMateExporter* self, const char* title) {
	char* _tmp1;
	char* _tmp0;
	char* _tmp2;
	char* header;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (title != NULL, NULL);
	_tmp1 = NULL;
	_tmp0 = NULL;
	_tmp2 = NULL;
	header = (_tmp2 = g_strconcat (_tmp1 = g_strconcat (_tmp0 = g_strconcat ("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\">\n" "<head>\n" "\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n" "\t<title>", title, NULL), "</title>\n", NULL), "\t<style type=\"text/css\">\n", NULL), _tmp1 = (g_free (_tmp1), NULL), _tmp0 = (g_free (_tmp0), NULL), _tmp2);
	return header;
}


static char* gtk_mate_exporter_css (GtkMateExporter* self) {
	const char* _tmp0;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0 = NULL;
	return (_tmp0 = gtk_mate_colourer_get_theme (gtk_mate_parser_get_colourer (GTK_MATE_BUFFER (gtk_text_view_get_buffer ((GtkTextView*) self->view))->parser))->name, (_tmp0 == NULL) ? NULL : g_strdup (_tmp0));
}


static char* gtk_mate_exporter_html (GtkMateExporter* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return g_strdup ("");
}


static void gtk_mate_exporter_class_init (GtkMateExporterClass * klass) {
	gtk_mate_exporter_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_exporter_finalize;
}


static void gtk_mate_exporter_instance_init (GtkMateExporter * self) {
}


static void gtk_mate_exporter_finalize (GObject* obj) {
	GtkMateExporter * self;
	self = GTK_MATE_EXPORTER (obj);
	(self->view == NULL) ? NULL : (self->view = (g_object_unref (self->view), NULL));
	G_OBJECT_CLASS (gtk_mate_exporter_parent_class)->finalize (obj);
}


GType gtk_mate_exporter_get_type (void) {
	static GType gtk_mate_exporter_type_id = 0;
	if (gtk_mate_exporter_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateExporterClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_exporter_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateExporter), 0, (GInstanceInitFunc) gtk_mate_exporter_instance_init, NULL };
		gtk_mate_exporter_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateExporter", &g_define_type_info, 0);
	}
	return gtk_mate_exporter_type_id;
}




