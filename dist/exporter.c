
#include "exporter.h"
#include <gee/map.h>
#include <float.h>
#include <math.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include "buffer.h"
#include "parser.h"
#include "colourer.h"
#include "theme.h"
#include "string_helper.h"
#include "scope.h"




static glong string_get_length (const char* self);
enum  {
	GTK_MATE_EXPORTER_DUMMY_PROPERTY
};
static void gtk_mate_exporter_add_indent (GtkMateExporter* self, GString* sb, gint indent);
static char* gtk_mate_exporter_code (GtkMateExporter* self);
static void gtk_mate_exporter_scope_to_html (GtkMateExporter* self, gint indent, GString* result, GtkMateScope* scope);
static GtkMateBuffer* gtk_mate_exporter_buffer (GtkMateExporter* self);
static char* gtk_mate_exporter_theme_name (GtkMateExporter* self);
static char* gtk_mate_exporter_html_header (GtkMateExporter* self, const char* title);
static char* gtk_mate_exporter_body_start (GtkMateExporter* self);
static char* gtk_mate_exporter_body_end (GtkMateExporter* self);
static char* gtk_mate_exporter_colour (GtkMateExporter* self, const char* colour);
static char* gtk_mate_exporter_css (GtkMateExporter* self);
static char* gtk_mate_exporter_html (GtkMateExporter* self);
static gpointer gtk_mate_exporter_parent_class = NULL;
static void gtk_mate_exporter_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



static glong string_get_length (const char* self) {
	g_return_val_if_fail (self != NULL, 0L);
	return g_utf8_strlen (self, -1);
}


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
	GString* result;
	char* _tmp0;
	char* _tmp1;
	char* _tmp2;
	char* _tmp3;
	char* _tmp4;
	const char* _tmp5;
	char* _tmp6;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (title != NULL, NULL);
	result = g_string_new ("");
	_tmp0 = NULL;
	g_string_append (result, _tmp0 = gtk_mate_exporter_html_header (self, title));
	_tmp0 = (g_free (_tmp0), NULL);
	_tmp1 = NULL;
	g_string_append (result, _tmp1 = gtk_mate_exporter_css (self));
	_tmp1 = (g_free (_tmp1), NULL);
	_tmp2 = NULL;
	g_string_append (result, _tmp2 = gtk_mate_exporter_body_start (self));
	_tmp2 = (g_free (_tmp2), NULL);
	_tmp3 = NULL;
	g_string_append (result, _tmp3 = gtk_mate_exporter_code (self));
	_tmp3 = (g_free (_tmp3), NULL);
	_tmp4 = NULL;
	g_string_append (result, _tmp4 = gtk_mate_exporter_body_end (self));
	_tmp4 = (g_free (_tmp4), NULL);
	_tmp5 = NULL;
	_tmp6 = NULL;
	return (_tmp6 = (_tmp5 = result->str, (_tmp5 == NULL) ? NULL : g_strdup (_tmp5)), (result == NULL) ? NULL : (result = (g_string_free (result, TRUE), NULL)), _tmp6);
}


static void gtk_mate_exporter_add_indent (GtkMateExporter* self, GString* sb, gint indent) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (sb != NULL);
	{
		gint i;
		i = 0;
		for (; i < indent; i++) {
			g_string_append (sb, "\t");
		}
	}
}


static char* gtk_mate_exporter_code (GtkMateExporter* self) {
	GString* result;
	char* _tmp3;
	char* _tmp2;
	char* _tmp1;
	char* _tmp0;
	GtkMateBuffer* _tmp4;
	const char* _tmp5;
	char* _tmp6;
	g_return_val_if_fail (self != NULL, NULL);
	result = g_string_new ("");
	gtk_mate_exporter_add_indent (self, result, 1);
	_tmp3 = NULL;
	_tmp2 = NULL;
	_tmp1 = NULL;
	_tmp0 = NULL;
	g_string_append (result, _tmp3 = g_strconcat (_tmp2 = g_strconcat ("<pre class=\"textmate-source ", _tmp1 = g_utf8_strdown (_tmp0 = gtk_mate_exporter_theme_name (self), -1), NULL), "\">\n", NULL));
	_tmp3 = (g_free (_tmp3), NULL);
	_tmp2 = (g_free (_tmp2), NULL);
	_tmp1 = (g_free (_tmp1), NULL);
	_tmp0 = (g_free (_tmp0), NULL);
	_tmp4 = NULL;
	gtk_mate_exporter_scope_to_html (self, 2, result, (_tmp4 = gtk_mate_exporter_buffer (self))->parser->root);
	(_tmp4 == NULL) ? NULL : (_tmp4 = (g_object_unref (_tmp4), NULL));
	_tmp5 = NULL;
	_tmp6 = NULL;
	return (_tmp6 = (_tmp5 = result->str, (_tmp5 == NULL) ? NULL : g_strdup (_tmp5)), (result == NULL) ? NULL : (result = (g_string_free (result, TRUE), NULL)), _tmp6);
}


static void gtk_mate_exporter_scope_to_html (GtkMateExporter* self, gint indent, GString* result, GtkMateScope* scope) {
	GSequenceIter* iter;
	g_return_if_fail (self != NULL);
	g_return_if_fail (result != NULL);
	g_return_if_fail (scope != NULL);
	gtk_mate_exporter_add_indent (self, result, indent);
	g_string_append (result, "<span class=\"\">\n");
	iter = g_sequence_get_begin_iter (gtk_mate_scope_get_children (scope));
	while (!g_sequence_iter_is_end (iter)) {
		gtk_mate_exporter_scope_to_html (self, indent + 1, result, (GtkMateScope*) g_sequence_get (iter));
		iter = g_sequence_iter_next (iter);
	}
	gtk_mate_exporter_add_indent (self, result, indent);
	g_string_append (result, "</span>\n");
	return;
}


static GtkMateBuffer* gtk_mate_exporter_buffer (GtkMateExporter* self) {
	GtkMateBuffer* _tmp0;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0 = NULL;
	return (_tmp0 = GTK_MATE_BUFFER (gtk_text_view_get_buffer ((GtkTextView*) self->view)), (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
}


static char* gtk_mate_exporter_theme_name (GtkMateExporter* self) {
	const char* _tmp1;
	GtkMateBuffer* _tmp0;
	char* _tmp2;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp1 = NULL;
	_tmp0 = NULL;
	_tmp2 = NULL;
	return (_tmp2 = (_tmp1 = gtk_mate_colourer_get_theme (gtk_mate_parser_get_colourer ((_tmp0 = gtk_mate_exporter_buffer (self))->parser))->name, (_tmp1 == NULL) ? NULL : g_strdup (_tmp1)), (_tmp0 == NULL) ? NULL : (_tmp0 = (g_object_unref (_tmp0), NULL)), _tmp2);
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


static char* gtk_mate_exporter_body_start (GtkMateExporter* self) {
	char* html;
	g_return_val_if_fail (self != NULL, NULL);
	html = g_strdup ("\t</style>\n</head>\n\n<body>\n");
	return html;
}


static char* gtk_mate_exporter_body_end (GtkMateExporter* self) {
	char* html;
	g_return_val_if_fail (self != NULL, NULL);
	html = g_strdup ("</body>\n</html>");
	return html;
}


static char* gtk_mate_exporter_colour (GtkMateExporter* self, const char* colour) {
	GString* result;
	const char* _tmp9;
	char* _tmp10;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (colour != NULL, NULL);
	result = g_string_new ("");
	if (string_get_length (colour) == 9) {
		char* _tmp1;
		char* _tmp0;
		char* _tmp3;
		char* _tmp2;
		char* _tmp5;
		char* _tmp4;
		char* _tmp6;
		g_string_append (result, "\tbackground-color: rgba(");
		_tmp1 = NULL;
		_tmp0 = NULL;
		g_string_append (result, _tmp1 = g_strconcat (_tmp0 = g_strdup_printf ("%d", gtk_mate_colourer_hex_to_int (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 1)), g_utf8_get_char (g_utf8_offset_to_pointer (colour, 2)))), ", ", NULL));
		_tmp1 = (g_free (_tmp1), NULL);
		_tmp0 = (g_free (_tmp0), NULL);
		_tmp3 = NULL;
		_tmp2 = NULL;
		g_string_append (result, _tmp3 = g_strconcat (_tmp2 = g_strdup_printf ("%d", gtk_mate_colourer_hex_to_int (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 3)), g_utf8_get_char (g_utf8_offset_to_pointer (colour, 4)))), ", ", NULL));
		_tmp3 = (g_free (_tmp3), NULL);
		_tmp2 = (g_free (_tmp2), NULL);
		_tmp5 = NULL;
		_tmp4 = NULL;
		g_string_append (result, _tmp5 = g_strconcat (_tmp4 = g_strdup_printf ("%d", gtk_mate_colourer_hex_to_int (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 5)), g_utf8_get_char (g_utf8_offset_to_pointer (colour, 6)))), ", ", NULL));
		_tmp5 = (g_free (_tmp5), NULL);
		_tmp4 = (g_free (_tmp4), NULL);
		_tmp6 = NULL;
		g_string_append (result, _tmp6 = g_strdup_printf ("%0.2f", ((double) gtk_mate_colourer_hex_to_int (g_utf8_get_char (g_utf8_offset_to_pointer (colour, 7)), g_utf8_get_char (g_utf8_offset_to_pointer (colour, 8)))) / 256.0));
		_tmp6 = (g_free (_tmp6), NULL);
		g_string_append (result, ");\n");
	} else {
		if (string_get_length (colour) == 7) {
			char* _tmp8;
			char* _tmp7;
			_tmp8 = NULL;
			_tmp7 = NULL;
			g_string_append (result, _tmp8 = g_strconcat (_tmp7 = g_strconcat ("\tbackground-color: ", colour, NULL), ";\n", NULL));
			_tmp8 = (g_free (_tmp8), NULL);
			_tmp7 = (g_free (_tmp7), NULL);
		}
	}
	_tmp9 = NULL;
	_tmp10 = NULL;
	return (_tmp10 = (_tmp9 = result->str, (_tmp9 == NULL) ? NULL : g_strdup (_tmp9)), (result == NULL) ? NULL : (result = (g_string_free (result, TRUE), NULL)), _tmp10);
}


static char* gtk_mate_exporter_css (GtkMateExporter* self) {
	GtkMateColourer* _tmp0;
	GtkMateColourer* colourer;
	GString* result;
	const char* _tmp1;
	char* theme_name;
	char* _tmp3;
	char* _tmp2;
	char* _tmp13;
	char* _tmp12;
	char* _tmp11;
	char* _tmp10;
	char* _tmp9;
	char* _tmp8;
	char* _tmp7;
	char* _tmp6;
	char* _tmp5;
	char* _tmp4;
	char* _tmp16;
	char* _tmp15;
	char* _tmp14;
	char* selection_colour;
	gboolean _tmp17;
	const char* _tmp43;
	char* _tmp44;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0 = NULL;
	colourer = (_tmp0 = gtk_mate_parser_get_colourer (GTK_MATE_BUFFER (gtk_text_view_get_buffer ((GtkTextView*) self->view))->parser), (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
	result = g_string_new ("");
	_tmp1 = NULL;
	theme_name = (_tmp1 = gtk_mate_colourer_get_theme (colourer)->name, (_tmp1 == NULL) ? NULL : g_strdup (_tmp1));
	_tmp3 = NULL;
	_tmp2 = NULL;
	g_string_append (result, _tmp3 = g_strconcat (_tmp2 = g_strconcat ("/* Stylesheet generated from theme: ", theme_name, NULL), " */\n\n", NULL));
	_tmp3 = (g_free (_tmp3), NULL);
	_tmp2 = (g_free (_tmp2), NULL);
	g_string_append (result, "body {\n\tmargin: 0;\n\tpadding: 0;\n}\n\n");
	g_string_append (result, "pre.textmate-source {\n\tmargin: 0;\n\tpadding: 0 0 0 2px;\n\tfont-family: Monaco, monospace;\n" "\tfont-size: 11px;\n\tline-height: 1.3em;\n\tword-wrap: break-word;\n\twhite-space: pre;\n" "\twhite-space: pre-wrap;\n\twhite-space: -moz-pre-wrap;\n\twhite-space: -o-pre-wrap;\n}\n\n");
	_tmp13 = NULL;
	_tmp12 = NULL;
	_tmp11 = NULL;
	_tmp10 = NULL;
	_tmp9 = NULL;
	_tmp8 = NULL;
	_tmp7 = NULL;
	_tmp6 = NULL;
	_tmp5 = NULL;
	_tmp4 = NULL;
	g_string_append (result, _tmp13 = g_strconcat (_tmp12 = g_strconcat (_tmp10 = g_strconcat (_tmp9 = g_strconcat (_tmp7 = g_strconcat (_tmp6 = g_strconcat (_tmp5 = g_strconcat ("pre.textmate-source.", _tmp4 = g_utf8_strdown (theme_name, -1), NULL), " {\n", NULL), "\tcolor: ", NULL), _tmp8 = gtk_mate_colourer_global_foreground_colour (colourer), NULL), ";\n\tbackground-color: ", NULL), _tmp11 = gtk_mate_colourer_global_background_colour (colourer), NULL), ";\n}\n\n", NULL));
	_tmp13 = (g_free (_tmp13), NULL);
	_tmp12 = (g_free (_tmp12), NULL);
	_tmp11 = (g_free (_tmp11), NULL);
	_tmp10 = (g_free (_tmp10), NULL);
	_tmp9 = (g_free (_tmp9), NULL);
	_tmp8 = (g_free (_tmp8), NULL);
	_tmp7 = (g_free (_tmp7), NULL);
	_tmp6 = (g_free (_tmp6), NULL);
	_tmp5 = (g_free (_tmp5), NULL);
	_tmp4 = (g_free (_tmp4), NULL);
	g_string_append (result, "pre.textmate-source .linenum {\n");
	g_string_append (result, "\twidth: 75px;\n");
	g_string_append (result, "\tpadding: 0.1em 1em 0.2em 0;\n");
	g_string_append (result, "\tcolor: #888;\n");
	g_string_append (result, "\tbackground-color: #eee;\n");
	g_string_append (result, "}\n\n");
	_tmp16 = NULL;
	_tmp15 = NULL;
	_tmp14 = NULL;
	g_string_append (result, _tmp16 = g_strconcat (_tmp15 = g_strconcat ("pre.textmate-source.", _tmp14 = g_utf8_strdown (theme_name, -1), NULL), " span {\n", NULL));
	_tmp16 = (g_free (_tmp16), NULL);
	_tmp15 = (g_free (_tmp15), NULL);
	_tmp14 = (g_free (_tmp14), NULL);
	g_string_append (result, "\tpadding-top: 0.2em;\n");
	g_string_append (result, "\tpadding-bottom: 0.1em;\n");
	g_string_append (result, "}\n\n");
	selection_colour = (char*) gee_map_get ((GeeMap*) gtk_mate_colourer_get_theme (colourer)->global_settings, "selection");
	_tmp17 = FALSE;
	if (selection_colour != NULL) {
		_tmp17 = _vala_strcmp0 (selection_colour, "") != 0;
	} else {
		_tmp17 = FALSE;
	}
	if (_tmp17) {
		char* _tmp20;
		char* _tmp19;
		char* _tmp18;
		char* _tmp21;
		_tmp20 = NULL;
		_tmp19 = NULL;
		_tmp18 = NULL;
		g_string_append (result, _tmp20 = g_strconcat (_tmp19 = g_strconcat ("pre.textmate-source.", _tmp18 = g_utf8_strdown (theme_name, -1), NULL), " ::selection {\n", NULL));
		_tmp20 = (g_free (_tmp20), NULL);
		_tmp19 = (g_free (_tmp19), NULL);
		_tmp18 = (g_free (_tmp18), NULL);
		_tmp21 = NULL;
		g_string_append (result, _tmp21 = gtk_mate_exporter_colour (self, selection_colour));
		_tmp21 = (g_free (_tmp21), NULL);
		g_string_append (result, "}\n\n");
	}
	{
		GeeIterator* _setting_it;
		_setting_it = gee_iterable_iterator ((GeeIterable*) gtk_mate_colourer_get_theme (colourer)->settings);
		while (gee_iterator_next (_setting_it)) {
			GtkMateThemeSetting* setting;
			char* _tmp23;
			char* _tmp22;
			char* _tmp34;
			char* _tmp33;
			char* _tmp32;
			char* _tmp31;
			char* _tmp30;
			char* _tmp29;
			char* _tmp28;
			char* _tmp27;
			char* _tmp26;
			char* _tmp25;
			char* _tmp24;
			char* _tmp35;
			gboolean _tmp36;
			char* _tmp40;
			gboolean _tmp41;
			char* bg_colour;
			setting = (GtkMateThemeSetting*) gee_iterator_get (_setting_it);
			_tmp23 = NULL;
			_tmp22 = NULL;
			g_string_append (result, _tmp23 = g_strconcat (_tmp22 = g_strconcat ("/* ", setting->name, NULL), " */\n", NULL));
			_tmp23 = (g_free (_tmp23), NULL);
			_tmp22 = (g_free (_tmp22), NULL);
			_tmp34 = NULL;
			_tmp33 = NULL;
			_tmp32 = NULL;
			_tmp31 = NULL;
			_tmp30 = NULL;
			_tmp29 = NULL;
			_tmp28 = NULL;
			_tmp27 = NULL;
			_tmp26 = NULL;
			_tmp25 = NULL;
			_tmp24 = NULL;
			g_string_append (result, _tmp34 = g_strconcat (_tmp33 = g_strconcat (_tmp26 = g_strconcat (_tmp25 = g_strconcat ("pre.textmate-source.", _tmp24 = g_utf8_strdown (theme_name, -1), NULL), " .", NULL), _tmp32 = string_helper_gsub (_tmp28 = string_helper_gsub (_tmp27 = string_helper_gsub (setting->selector, ".", "_"), " ", " ."), ", ", _tmp31 = g_strconcat (_tmp30 = g_strconcat (", pre.textmate-source.", _tmp29 = g_utf8_strdown (theme_name, -1), NULL), " ", NULL)), NULL), " {\n", NULL));
			_tmp34 = (g_free (_tmp34), NULL);
			_tmp33 = (g_free (_tmp33), NULL);
			_tmp32 = (g_free (_tmp32), NULL);
			_tmp31 = (g_free (_tmp31), NULL);
			_tmp30 = (g_free (_tmp30), NULL);
			_tmp29 = (g_free (_tmp29), NULL);
			_tmp28 = (g_free (_tmp28), NULL);
			_tmp27 = (g_free (_tmp27), NULL);
			_tmp26 = (g_free (_tmp26), NULL);
			_tmp25 = (g_free (_tmp25), NULL);
			_tmp24 = (g_free (_tmp24), NULL);
			_tmp35 = NULL;
			if ((_tmp36 = (_tmp35 = (char*) gee_map_get ((GeeMap*) setting->settings, "foreground")) != NULL, _tmp35 = (g_free (_tmp35), NULL), _tmp36)) {
				char* _tmp39;
				char* _tmp38;
				char* _tmp37;
				_tmp39 = NULL;
				_tmp38 = NULL;
				_tmp37 = NULL;
				g_string_append (result, _tmp39 = g_strconcat (_tmp38 = g_strconcat ("\tcolor: ", _tmp37 = (char*) gee_map_get ((GeeMap*) setting->settings, "foreground"), NULL), ";\n", NULL));
				_tmp39 = (g_free (_tmp39), NULL);
				_tmp38 = (g_free (_tmp38), NULL);
				_tmp37 = (g_free (_tmp37), NULL);
			}
			_tmp40 = NULL;
			if ((_tmp41 = _vala_strcmp0 (_tmp40 = (char*) gee_map_get ((GeeMap*) setting->settings, "fontStyle"), "italic") == 0, _tmp40 = (g_free (_tmp40), NULL), _tmp41)) {
				g_string_append (result, "\tfont-style: italic;\n");
			}
			bg_colour = (char*) gee_map_get ((GeeMap*) setting->settings, "background");
			if (bg_colour != NULL) {
				char* _tmp42;
				_tmp42 = NULL;
				g_string_append (result, _tmp42 = gtk_mate_exporter_colour (self, bg_colour));
				_tmp42 = (g_free (_tmp42), NULL);
			}
			g_string_append (result, "}\n\n");
			(setting == NULL) ? NULL : (setting = (g_object_unref (setting), NULL));
			bg_colour = (g_free (bg_colour), NULL);
		}
		(_setting_it == NULL) ? NULL : (_setting_it = (g_object_unref (_setting_it), NULL));
	}
	_tmp43 = NULL;
	_tmp44 = NULL;
	return (_tmp44 = (_tmp43 = result->str, (_tmp43 == NULL) ? NULL : g_strdup (_tmp43)), (colourer == NULL) ? NULL : (colourer = (g_object_unref (colourer), NULL)), (result == NULL) ? NULL : (result = (g_string_free (result, TRUE), NULL)), theme_name = (g_free (theme_name), NULL), selection_colour = (g_free (selection_colour), NULL), _tmp44);
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


static int _vala_strcmp0 (const char * str1, const char * str2) {
	if (str1 == NULL) {
		return -(str1 != str2);
	}
	if (str2 == NULL) {
		return str1 != str2;
	}
	return strcmp (str1, str2);
}




