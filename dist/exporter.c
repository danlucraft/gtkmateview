
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
#include "pattern.h"




static glong string_get_length (const char* self);
enum  {
	GTK_MATE_EXPORTER_DUMMY_PROPERTY
};
static void gtk_mate_exporter_add_indent (GtkMateExporter* self, GString* sb, gint indent);
static char* gtk_mate_exporter_code (GtkMateExporter* self);
static char* gtk_mate_exporter_css_names (GtkMateExporter* self, GtkMateScope* scope, gboolean inner);
static gboolean gtk_mate_exporter_scope_has_inner (GtkMateExporter* self, GtkMateScope* scope);
static void gtk_mate_exporter_scope_to_html (GtkMateExporter* self, GString* result, GtkMateScope* scope);
static GtkMateBuffer* gtk_mate_exporter_buffer (GtkMateExporter* self);
static char* gtk_mate_exporter_theme_name (GtkMateExporter* self);
static char* gtk_mate_exporter_theme_name_css (GtkMateExporter* self);
static char* gtk_mate_exporter_html_header (GtkMateExporter* self, const char* title);
static char* gtk_mate_exporter_body_start (GtkMateExporter* self);
static char* gtk_mate_exporter_body_end (GtkMateExporter* self);
static char* gtk_mate_exporter_colour (GtkMateExporter* self, const char* colour);
static char* gtk_mate_exporter_css (GtkMateExporter* self);
static char* gtk_mate_exporter_html (GtkMateExporter* self);
static gpointer gtk_mate_exporter_parent_class = NULL;
static void gtk_mate_exporter_finalize (GObject* obj);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static gint _vala_array_length (gpointer array);
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
	char* _tmp2;
	char* _tmp1;
	char* _tmp0;
	GtkMateBuffer* _tmp3;
	const char* _tmp4;
	char* _tmp5;
	g_return_val_if_fail (self != NULL, NULL);
	result = g_string_new ("");
	gtk_mate_exporter_add_indent (self, result, 1);
	_tmp2 = NULL;
	_tmp1 = NULL;
	_tmp0 = NULL;
	g_string_append (result, _tmp2 = g_strconcat (_tmp1 = g_strconcat ("<pre class=\"textmate-source ", _tmp0 = gtk_mate_exporter_theme_name_css (self), NULL), "\">", NULL));
	_tmp2 = (g_free (_tmp2), NULL);
	_tmp1 = (g_free (_tmp1), NULL);
	_tmp0 = (g_free (_tmp0), NULL);
	_tmp3 = NULL;
	gtk_mate_exporter_scope_to_html (self, result, (_tmp3 = gtk_mate_exporter_buffer (self))->parser->root);
	(_tmp3 == NULL) ? NULL : (_tmp3 = (g_object_unref (_tmp3), NULL));
	g_string_append (result, "</pre>\n");
	_tmp4 = NULL;
	_tmp5 = NULL;
	return (_tmp5 = (_tmp4 = result->str, (_tmp4 == NULL) ? NULL : g_strdup (_tmp4)), (result == NULL) ? NULL : (result = (g_string_free (result, TRUE), NULL)), _tmp5);
}


static char* gtk_mate_exporter_css_names (GtkMateExporter* self, GtkMateScope* scope, gboolean inner) {
	char* this_name;
	gboolean _tmp0;
	gboolean _tmp1;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (scope != NULL, NULL);
	this_name = NULL;
	_tmp0 = FALSE;
	_tmp1 = FALSE;
	if (GTK_MATE_IS_DOUBLE_PATTERN (scope->pattern)) {
		_tmp1 = GTK_MATE_DOUBLE_PATTERN (scope->pattern)->content_name != NULL;
	} else {
		_tmp1 = FALSE;
	}
	if (_tmp1) {
		_tmp0 = inner;
	} else {
		_tmp0 = FALSE;
	}
	if (_tmp0) {
		char* _tmp3;
		const char* _tmp2;
		_tmp3 = NULL;
		_tmp2 = NULL;
		this_name = (_tmp3 = (_tmp2 = GTK_MATE_DOUBLE_PATTERN (scope->pattern)->content_name, (_tmp2 == NULL) ? NULL : g_strdup (_tmp2)), this_name = (g_free (this_name), NULL), _tmp3);
	} else {
		char* _tmp5;
		const char* _tmp4;
		_tmp5 = NULL;
		_tmp4 = NULL;
		this_name = (_tmp5 = (_tmp4 = gtk_mate_scope_get_name (scope), (_tmp4 == NULL) ? NULL : g_strdup (_tmp4)), this_name = (g_free (this_name), NULL), _tmp5);
	}
	if (this_name != NULL) {
		char** _tmp7;
		gint bits_size;
		gint bits_length1;
		char** _tmp6;
		char** bits;
		const char* _tmp8;
		char* current;
		GString* result;
		char* _tmp12;
		const char* _tmp11;
		_tmp7 = NULL;
		_tmp6 = NULL;
		bits = (_tmp7 = _tmp6 = g_strsplit (this_name, ".", 0), bits_length1 = _vala_array_length (_tmp6), bits_size = bits_length1, _tmp7);
		/* bits == ["meta", "class", "ruby"]*/
		_tmp8 = NULL;
		current = (_tmp8 = bits[0], (_tmp8 == NULL) ? NULL : g_strdup (_tmp8));
		result = g_string_new ("");
		{
			gint i;
			i = 1;
			for (; i < bits_length1; i++) {
				char* _tmp10;
				char* _tmp9;
				g_string_append (result, current);
				_tmp10 = NULL;
				_tmp9 = NULL;
				current = (_tmp10 = g_strconcat (_tmp9 = g_strconcat (current, "_", NULL), bits[i], NULL), current = (g_free (current), NULL), _tmp10);
				_tmp9 = (g_free (_tmp9), NULL);
				g_string_append (result, " ");
			}
		}
		g_string_append (result, current);
		_tmp12 = NULL;
		_tmp11 = NULL;
		this_name = (_tmp12 = (_tmp11 = result->str, (_tmp11 == NULL) ? NULL : g_strdup (_tmp11)), this_name = (g_free (this_name), NULL), _tmp12);
		bits = (_vala_array_free (bits, bits_length1, (GDestroyNotify) g_free), NULL);
		current = (g_free (current), NULL);
		(result == NULL) ? NULL : (result = (g_string_free (result, TRUE), NULL));
	}
	return this_name;
}


static gboolean gtk_mate_exporter_scope_has_inner (GtkMateExporter* self, GtkMateScope* scope) {
	gboolean _tmp0;
	gboolean _tmp1;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (scope != NULL, FALSE);
	_tmp0 = FALSE;
	_tmp1 = FALSE;
	if (GTK_MATE_IS_DOUBLE_PATTERN (scope->pattern)) {
		_tmp1 = GTK_MATE_DOUBLE_PATTERN (scope->pattern)->content_name != NULL;
	} else {
		_tmp1 = FALSE;
	}
	if (_tmp1) {
		_tmp0 = _vala_strcmp0 (GTK_MATE_DOUBLE_PATTERN (scope->pattern)->content_name, "") != 0;
	} else {
		_tmp0 = FALSE;
	}
	return _tmp0;
}


static void gtk_mate_exporter_scope_to_html (GtkMateExporter* self, GString* result, GtkMateScope* scope) {
	char* names;
	gboolean _tmp0;
	GtkTextIter position;
	gboolean opened_inner;
	gboolean closed_inner;
	gboolean _tmp26;
	g_return_if_fail (self != NULL);
	g_return_if_fail (result != NULL);
	g_return_if_fail (scope != NULL);
	names = gtk_mate_exporter_css_names (self, scope, FALSE);
	_tmp0 = FALSE;
	if (_vala_strcmp0 (names, "") != 0) {
		_tmp0 = names != NULL;
	} else {
		_tmp0 = FALSE;
	}
	if (_tmp0) {
		char* _tmp2;
		char* _tmp1;
		_tmp2 = NULL;
		_tmp1 = NULL;
		g_string_append (result, _tmp2 = g_strconcat (_tmp1 = g_strconcat ("<span class=\"", names, NULL), "\">", NULL));
		_tmp2 = (g_free (_tmp2), NULL);
		_tmp1 = (g_free (_tmp1), NULL);
	}
	position = gtk_mate_scope_start_iter (scope);
	opened_inner = FALSE;
	closed_inner = FALSE;
	if (g_sequence_get_length (gtk_mate_scope_get_children (scope)) > 0) {
		GSequenceIter* iter;
		GtkMateScope* child;
		gboolean _tmp15;
		iter = g_sequence_get_begin_iter (gtk_mate_scope_get_children (scope));
		child = NULL;
		while (!g_sequence_iter_is_end (iter)) {
			GtkMateScope* _tmp8;
			GtkMateScope* _tmp7;
			GtkTextIter _tmp9 = {0};
			if (gtk_mate_exporter_scope_has_inner (self, scope)) {
				gboolean _tmp3;
				GtkTextIter _tmp4 = {0};
				_tmp3 = FALSE;
				if (gtk_text_iter_compare (&position, (_tmp4 = gtk_mate_scope_inner_start_iter (scope), &_tmp4)) >= 0) {
					_tmp3 = !opened_inner;
				} else {
					_tmp3 = FALSE;
				}
				if (_tmp3) {
					char* inner_names;
					char* _tmp6;
					char* _tmp5;
					inner_names = gtk_mate_exporter_css_names (self, scope, TRUE);
					_tmp6 = NULL;
					_tmp5 = NULL;
					g_string_append (result, _tmp6 = g_strconcat (_tmp5 = g_strconcat ("<span class=\"", inner_names, NULL), "\">", NULL));
					_tmp6 = (g_free (_tmp6), NULL);
					_tmp5 = (g_free (_tmp5), NULL);
					opened_inner = TRUE;
					inner_names = (g_free (inner_names), NULL);
				}
			}
			_tmp8 = NULL;
			_tmp7 = NULL;
			child = (_tmp8 = (_tmp7 = (GtkMateScope*) g_sequence_get (iter), (_tmp7 == NULL) ? NULL : g_object_ref (_tmp7)), (child == NULL) ? NULL : (child = (g_object_unref (child), NULL)), _tmp8);
			if (gtk_text_iter_compare ((_tmp9 = gtk_mate_scope_start_iter (child), &_tmp9), &position) > 0) {
				char* _tmp12;
				GtkTextIter _tmp11 = {0};
				GtkMateBuffer* _tmp10;
				_tmp12 = NULL;
				_tmp10 = NULL;
				g_string_append (result, _tmp12 = g_markup_escape_text (gtk_text_buffer_get_slice ((GtkTextBuffer*) (_tmp10 = gtk_mate_exporter_buffer (self)), &position, (_tmp11 = gtk_mate_scope_start_iter (child), &_tmp11), TRUE), -1));
				_tmp12 = (g_free (_tmp12), NULL);
				(_tmp10 == NULL) ? NULL : (_tmp10 = (g_object_unref (_tmp10), NULL));
				position = gtk_mate_scope_start_iter (child);
			}
			if (gtk_mate_exporter_scope_has_inner (self, scope)) {
				gboolean _tmp13;
				GtkTextIter _tmp14 = {0};
				_tmp13 = FALSE;
				if (gtk_text_iter_compare (&position, (_tmp14 = gtk_mate_scope_inner_end_iter (scope), &_tmp14)) >= 0) {
					_tmp13 = !closed_inner;
				} else {
					_tmp13 = FALSE;
				}
				if (_tmp13) {
					g_string_append (result, "</span>");
					closed_inner = TRUE;
				}
			}
			gtk_mate_exporter_scope_to_html (self, result, child);
			position = gtk_mate_scope_end_iter (child);
			iter = g_sequence_iter_next (iter);
		}
		_tmp15 = FALSE;
		if (child != NULL) {
			GtkTextIter _tmp17 = {0};
			GtkTextIter _tmp16 = {0};
			_tmp15 = gtk_text_iter_compare ((_tmp16 = gtk_mate_scope_end_iter (child), &_tmp16), (_tmp17 = gtk_mate_scope_end_iter (scope), &_tmp17)) < 0;
		} else {
			_tmp15 = FALSE;
		}
		if (_tmp15) {
			char* _tmp21;
			GtkTextIter _tmp20 = {0};
			GtkTextIter _tmp19 = {0};
			GtkMateBuffer* _tmp18;
			_tmp21 = NULL;
			_tmp18 = NULL;
			g_string_append (result, _tmp21 = g_markup_escape_text (gtk_text_buffer_get_slice ((GtkTextBuffer*) (_tmp18 = gtk_mate_exporter_buffer (self)), (_tmp19 = gtk_mate_scope_end_iter (child), &_tmp19), (_tmp20 = gtk_mate_scope_end_iter (scope), &_tmp20), TRUE), -1));
			_tmp21 = (g_free (_tmp21), NULL);
			(_tmp18 == NULL) ? NULL : (_tmp18 = (g_object_unref (_tmp18), NULL));
		}
		(child == NULL) ? NULL : (child = (g_object_unref (child), NULL));
	} else {
		char* _tmp25;
		GtkTextIter _tmp24 = {0};
		GtkTextIter _tmp23 = {0};
		GtkMateBuffer* _tmp22;
		_tmp25 = NULL;
		_tmp22 = NULL;
		g_string_append (result, _tmp25 = g_markup_escape_text (gtk_text_buffer_get_slice ((GtkTextBuffer*) (_tmp22 = gtk_mate_exporter_buffer (self)), (_tmp23 = gtk_mate_scope_start_iter (scope), &_tmp23), (_tmp24 = gtk_mate_scope_end_iter (scope), &_tmp24), TRUE), -1));
		_tmp25 = (g_free (_tmp25), NULL);
		(_tmp22 == NULL) ? NULL : (_tmp22 = (g_object_unref (_tmp22), NULL));
	}
	_tmp26 = FALSE;
	if (_vala_strcmp0 (names, "") != 0) {
		_tmp26 = names != NULL;
	} else {
		_tmp26 = FALSE;
	}
	if (_tmp26) {
		g_string_append (result, "</span>");
	}
	names = (g_free (names), NULL);
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


static char* gtk_mate_exporter_theme_name_css (GtkMateExporter* self) {
	char* _tmp1;
	GtkMateBuffer* _tmp0;
	char* _tmp2;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp1 = NULL;
	_tmp0 = NULL;
	_tmp2 = NULL;
	return (_tmp2 = string_helper_gsub (_tmp1 = g_utf8_strdown (gtk_mate_colourer_get_theme (gtk_mate_parser_get_colourer ((_tmp0 = gtk_mate_exporter_buffer (self))->parser))->name, -1), " ", "_"), _tmp1 = (g_free (_tmp1), NULL), (_tmp0 == NULL) ? NULL : (_tmp0 = (g_object_unref (_tmp0), NULL)), _tmp2);
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
	html = g_strdup ("</body>\n</html>\n");
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
	char* _tmp3;
	char* _tmp2;
	char* _tmp1;
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
	const char* _tmp44;
	char* _tmp45;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0 = NULL;
	colourer = (_tmp0 = gtk_mate_parser_get_colourer (GTK_MATE_BUFFER (gtk_text_view_get_buffer ((GtkTextView*) self->view))->parser), (_tmp0 == NULL) ? NULL : g_object_ref (_tmp0));
	result = g_string_new ("");
	_tmp3 = NULL;
	_tmp2 = NULL;
	_tmp1 = NULL;
	g_string_append (result, _tmp3 = g_strconcat (_tmp2 = g_strconcat ("/* Stylesheet generated from theme: ", _tmp1 = gtk_mate_exporter_theme_name (self), NULL), " */\n\n", NULL));
	_tmp3 = (g_free (_tmp3), NULL);
	_tmp2 = (g_free (_tmp2), NULL);
	_tmp1 = (g_free (_tmp1), NULL);
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
	g_string_append (result, _tmp13 = g_strconcat (_tmp12 = g_strconcat (_tmp10 = g_strconcat (_tmp9 = g_strconcat (_tmp7 = g_strconcat (_tmp6 = g_strconcat (_tmp5 = g_strconcat ("pre.textmate-source.", _tmp4 = gtk_mate_exporter_theme_name_css (self), NULL), " {\n", NULL), "\tcolor: ", NULL), _tmp8 = gtk_mate_colourer_global_foreground_colour (colourer), NULL), ";\n\tbackground-color: ", NULL), _tmp11 = gtk_mate_colourer_global_background_colour (colourer), NULL), ";\n}\n\n", NULL));
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
	g_string_append (result, _tmp16 = g_strconcat (_tmp15 = g_strconcat ("pre.textmate-source.", _tmp14 = gtk_mate_exporter_theme_name_css (self), NULL), " span {\n", NULL));
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
		g_string_append (result, _tmp20 = g_strconcat (_tmp19 = g_strconcat ("pre.textmate-source.", _tmp18 = gtk_mate_exporter_theme_name_css (self), NULL), " ::selection {\n", NULL));
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
			char* font_style;
			gboolean _tmp40;
			gboolean _tmp41;
			gboolean _tmp42;
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
			g_string_append (result, _tmp34 = g_strconcat (_tmp33 = g_strconcat (_tmp26 = g_strconcat (_tmp25 = g_strconcat ("pre.textmate-source.", _tmp24 = gtk_mate_exporter_theme_name_css (self), NULL), " .", NULL), _tmp32 = string_helper_gsub (_tmp28 = string_helper_gsub (_tmp27 = string_helper_gsub (setting->selector, ".", "_"), " ", " ."), ", ", _tmp31 = g_strconcat (_tmp30 = g_strconcat (", pre.textmate-source.", _tmp29 = gtk_mate_exporter_theme_name_css (self), NULL), " ", NULL)), NULL), " {\n", NULL));
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
			font_style = (char*) gee_map_get ((GeeMap*) setting->settings, "fontStyle");
			_tmp40 = FALSE;
			if (font_style != NULL) {
				_tmp40 = strstr (font_style, "italic") != NULL;
			} else {
				_tmp40 = FALSE;
			}
			if (_tmp40) {
				g_string_append (result, "\tfont-style: italic;\n");
			}
			_tmp41 = FALSE;
			if (font_style != NULL) {
				_tmp41 = strstr (font_style, "underline") != NULL;
			} else {
				_tmp41 = FALSE;
			}
			if (_tmp41) {
				g_string_append (result, "\ttext-decoration: underline;\n");
			}
			_tmp42 = FALSE;
			if (font_style != NULL) {
				_tmp42 = strstr (font_style, "bold") != NULL;
			} else {
				_tmp42 = FALSE;
			}
			if (_tmp42) {
				g_string_append (result, "\tfont-weight: bold;\n");
			}
			bg_colour = (char*) gee_map_get ((GeeMap*) setting->settings, "background");
			if (bg_colour != NULL) {
				char* _tmp43;
				_tmp43 = NULL;
				g_string_append (result, _tmp43 = gtk_mate_exporter_colour (self, bg_colour));
				_tmp43 = (g_free (_tmp43), NULL);
			}
			g_string_append (result, "}\n\n");
			(setting == NULL) ? NULL : (setting = (g_object_unref (setting), NULL));
			font_style = (g_free (font_style), NULL);
			bg_colour = (g_free (bg_colour), NULL);
		}
		(_setting_it == NULL) ? NULL : (_setting_it = (g_object_unref (_setting_it), NULL));
	}
	_tmp44 = NULL;
	_tmp45 = NULL;
	return (_tmp45 = (_tmp44 = result->str, (_tmp44 == NULL) ? NULL : g_strdup (_tmp44)), (colourer == NULL) ? NULL : (colourer = (g_object_unref (colourer), NULL)), (result == NULL) ? NULL : (result = (g_string_free (result, TRUE), NULL)), selection_colour = (g_free (selection_colour), NULL), _tmp45);
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


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
	g_free (array);
}


static gint _vala_array_length (gpointer array) {
	int length;
	length = 0;
	if (array) {
		while (((gpointer*) array)[length]) {
			length++;
		}
	}
	return length;
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




