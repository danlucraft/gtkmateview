
#include "buffer.h"
#include "bundle.h"
#include "grammar.h"
#include "parser.h"
#include "onig_wrap.h"
#include "gtkmateview.h"




static glong string_get_length (const char* self);
enum  {
	GTK_MATE_BUFFER_DUMMY_PROPERTY
};
GeeArrayList* gtk_mate_buffer_bundles = NULL;
GeeArrayList* gtk_mate_buffer_themes = NULL;
static GObject * gtk_mate_buffer_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer gtk_mate_buffer_parent_class = NULL;
static void gtk_mate_buffer_finalize (GObject * obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



static glong string_get_length (const char* self) {
	g_return_val_if_fail (self != NULL, 0L);
	return g_utf8_strlen (self, -1);
}


/* Sets the grammar explicitly by name.*/
gboolean gtk_mate_buffer_set_grammar_by_name (GtkMateBuffer* self, const char* name) {
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (self), FALSE);
	g_return_val_if_fail (name != NULL, FALSE);
	{
		GeeArrayList* bundle_collection;
		int bundle_it;
		bundle_collection = gtk_mate_buffer_bundles;
		for (bundle_it = 0; bundle_it < gee_collection_get_size (GEE_COLLECTION (bundle_collection)); bundle_it = bundle_it + 1) {
			GtkMateBundle* bundle;
			bundle = ((GtkMateBundle*) (gee_list_get (GEE_LIST (bundle_collection), bundle_it)));
			{
				{
					GeeArrayList* gr_collection;
					int gr_it;
					gr_collection = bundle->grammars;
					for (gr_it = 0; gr_it < gee_collection_get_size (GEE_COLLECTION (gr_collection)); gr_it = gr_it + 1) {
						GtkMateGrammar* gr;
						gr = ((GtkMateGrammar*) (gee_list_get (GEE_LIST (gr_collection), gr_it)));
						{
							if (_vala_strcmp0 (gtk_mate_grammar_get_name (gr), name) == 0) {
								GtkMateParser* _tmp0;
								gboolean _tmp1;
								_tmp0 = NULL;
								self->parser = (_tmp0 = gtk_mate_parser_create (gr, self), (self->parser == NULL ? NULL : (self->parser = (g_object_unref (self->parser), NULL))), _tmp0);
								return (_tmp1 = TRUE, (gr == NULL ? NULL : (gr = (g_object_unref (gr), NULL))), (bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL))), _tmp1);
							}
							(gr == NULL ? NULL : (gr = (g_object_unref (gr), NULL)));
						}
					}
				}
				(bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL)));
			}
		}
	}
	return FALSE;
}


/* Sets the grammar by the file extension. If unable to find
 a grammar, sets the grammar to null. Returns the grammar
 name or null.*/
char* gtk_mate_buffer_set_grammar_by_filename (GtkMateBuffer* self, const char* filename) {
	GtkMateGrammar* best;
	glong best_length;
	char* _tmp6;
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (self), NULL);
	g_return_val_if_fail (filename != NULL, NULL);
	best = NULL;
	best_length = 0L;
	{
		GeeArrayList* bundle_collection;
		int bundle_it;
		bundle_collection = gtk_mate_buffer_bundles;
		for (bundle_it = 0; bundle_it < gee_collection_get_size (GEE_COLLECTION (bundle_collection)); bundle_it = bundle_it + 1) {
			GtkMateBundle* bundle;
			bundle = ((GtkMateBundle*) (gee_list_get (GEE_LIST (bundle_collection), bundle_it)));
			{
				{
					GeeArrayList* gr_collection;
					int gr_it;
					gr_collection = bundle->grammars;
					for (gr_it = 0; gr_it < gee_collection_get_size (GEE_COLLECTION (gr_collection)); gr_it = gr_it + 1) {
						GtkMateGrammar* gr;
						gr = ((GtkMateGrammar*) (gee_list_get (GEE_LIST (gr_collection), gr_it)));
						{
							{
								char** ext_collection;
								int ext_collection_length1;
								int ext_it;
								ext_collection = gr->file_types;
								ext_collection_length1 = gr->file_types_length1;
								for (ext_it = 0; (gr->file_types_length1 != -1 && ext_it < gr->file_types_length1) || (gr->file_types_length1 == -1 && ext_collection[ext_it] != NULL); ext_it = ext_it + 1) {
									const char* _tmp2;
									char* ext;
									_tmp2 = NULL;
									ext = (_tmp2 = ext_collection[ext_it], (_tmp2 == NULL ? NULL : g_strdup (_tmp2)));
									{
										if (g_str_has_suffix (filename, ext) && (best == NULL || string_get_length (ext) > best_length)) {
											GtkMateGrammar* _tmp1;
											GtkMateGrammar* _tmp0;
											_tmp1 = NULL;
											_tmp0 = NULL;
											best = (_tmp1 = (_tmp0 = gr, (_tmp0 == NULL ? NULL : g_object_ref (_tmp0))), (best == NULL ? NULL : (best = (g_object_unref (best), NULL))), _tmp1);
											best_length = string_get_length (ext);
										}
										ext = (g_free (ext), NULL);
									}
								}
							}
							(gr == NULL ? NULL : (gr = (g_object_unref (gr), NULL)));
						}
					}
				}
				(bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL)));
			}
		}
	}
	if (best != NULL) {
		GtkMateParser* _tmp3;
		const char* _tmp4;
		char* _tmp5;
		_tmp3 = NULL;
		self->parser = (_tmp3 = gtk_mate_parser_create (best, self), (self->parser == NULL ? NULL : (self->parser = (g_object_unref (self->parser), NULL))), _tmp3);
		_tmp4 = NULL;
		_tmp5 = NULL;
		return (_tmp5 = (_tmp4 = gtk_mate_grammar_get_name (best), (_tmp4 == NULL ? NULL : g_strdup (_tmp4))), (best == NULL ? NULL : (best = (g_object_unref (best), NULL))), _tmp5);
	}
	_tmp6 = NULL;
	return (_tmp6 = NULL, (best == NULL ? NULL : (best = (g_object_unref (best), NULL))), _tmp6);
}


/* Sets the grammar by examining the first line. If unable to find
 a grammar, sets the grammar to null. Returns the grammar
 name or null.*/
char* gtk_mate_buffer_set_grammar_by_first_line (GtkMateBuffer* self) {
	OnigRx* re;
	const char* _tmp2;
	GtkTextIter _tmp1 = {0};
	GtkTextIter _tmp0 = {0};
	char* first_line;
	char* _tmp10;
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (self), NULL);
	re = NULL;
	_tmp2 = NULL;
	first_line = (_tmp2 = gtk_text_buffer_get_text (GTK_TEXT_BUFFER (self), (_tmp0 = gtk_mate_buffer_iter_ (self, 0), &_tmp0), (_tmp1 = gtk_mate_buffer_line_start_iter (self, 1), &_tmp1), FALSE), (_tmp2 == NULL ? NULL : g_strdup (_tmp2)));
	{
		GeeArrayList* bundle_collection;
		int bundle_it;
		bundle_collection = gtk_mate_buffer_bundles;
		for (bundle_it = 0; bundle_it < gee_collection_get_size (GEE_COLLECTION (bundle_collection)); bundle_it = bundle_it + 1) {
			GtkMateBundle* bundle;
			bundle = ((GtkMateBundle*) (gee_list_get (GEE_LIST (bundle_collection), bundle_it)));
			{
				{
					GeeArrayList* gr_collection;
					int gr_it;
					gr_collection = bundle->grammars;
					for (gr_it = 0; gr_it < gee_collection_get_size (GEE_COLLECTION (gr_collection)); gr_it = gr_it + 1) {
						GtkMateGrammar* gr;
						gr = ((GtkMateGrammar*) (gee_list_get (GEE_LIST (gr_collection), gr_it)));
						{
							OnigRx* _tmp4;
							OnigRx* _tmp3;
							_tmp4 = NULL;
							_tmp3 = NULL;
							if ((re = (_tmp4 = (_tmp3 = gr->first_line_match, (_tmp3 == NULL ? NULL : g_object_ref (_tmp3))), (re == NULL ? NULL : (re = (g_object_unref (re), NULL))), _tmp4)) != NULL) {
								OnigMatch* _tmp5;
								gboolean _tmp6;
								_tmp5 = NULL;
								if ((_tmp6 = (_tmp5 = onig_rx_search (re, first_line, 0, ((gint) (strlen (first_line))))) != NULL, (_tmp5 == NULL ? NULL : (_tmp5 = (g_object_unref (_tmp5), NULL))), _tmp6)) {
									GtkMateParser* _tmp7;
									const char* _tmp8;
									char* _tmp9;
									_tmp7 = NULL;
									self->parser = (_tmp7 = gtk_mate_parser_create (gr, self), (self->parser == NULL ? NULL : (self->parser = (g_object_unref (self->parser), NULL))), _tmp7);
									_tmp8 = NULL;
									_tmp9 = NULL;
									return (_tmp9 = (_tmp8 = gtk_mate_grammar_get_name (gr), (_tmp8 == NULL ? NULL : g_strdup (_tmp8))), (gr == NULL ? NULL : (gr = (g_object_unref (gr), NULL))), (bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL))), (re == NULL ? NULL : (re = (g_object_unref (re), NULL))), (first_line = (g_free (first_line), NULL)), _tmp9);
								}
							}
							(gr == NULL ? NULL : (gr = (g_object_unref (gr), NULL)));
						}
					}
				}
				(bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL)));
			}
		}
	}
	_tmp10 = NULL;
	return (_tmp10 = NULL, (re == NULL ? NULL : (re = (g_object_unref (re), NULL))), (first_line = (g_free (first_line), NULL)), _tmp10);
}


/* HELPER METHODS
 Offset from start of document -> Iter*/
GtkTextIter gtk_mate_buffer_iter_ (GtkMateBuffer* self, gint offset) {
	GtkTextIter i = {0};
	0;
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER (self), &i, offset);
	return i;
}


GtkTextIter gtk_mate_buffer_start_iter (GtkMateBuffer* self) {
	GtkTextIter i = {0};
	0;
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER (self), &i, 0);
	return i;
}


GtkTextIter gtk_mate_buffer_end_iter (GtkMateBuffer* self) {
	GtkTextIter i = {0};
	0;
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER (self), &i, gtk_text_buffer_get_char_count (GTK_TEXT_BUFFER (self)));
	return i;
}


GtkTextIter gtk_mate_buffer_cursor_iter (GtkMateBuffer* self) {
	GtkTextIter i = {0};
	GtkTextMark* _tmp0;
	0;
	_tmp0 = NULL;
	gtk_text_buffer_get_iter_at_mark (GTK_TEXT_BUFFER (self), &i, (_tmp0 = gtk_mate_buffer_cursor_mark (self)));
	(_tmp0 == NULL ? NULL : (_tmp0 = (g_object_unref (_tmp0), NULL)));
	return i;
}


GtkTextIter gtk_mate_buffer_iter_from_mark (GtkMateBuffer* self, GtkTextMark* mark) {
	GtkTextIter i = {0};
	0;
	0;
	gtk_text_buffer_get_iter_at_mark (GTK_TEXT_BUFFER (self), &i, mark);
	return i;
}


GtkTextIter gtk_mate_buffer_iter_at_line_offset (GtkMateBuffer* self, gint line, gint line_offset) {
	GtkTextIter i = {0};
	0;
	gtk_text_buffer_get_iter_at_line_offset (GTK_TEXT_BUFFER (self), &i, line, line_offset);
	return i;
}


GtkTextIter gtk_mate_buffer_line_start_iter (GtkMateBuffer* self, gint line) {
	GtkTextIter i = {0};
	0;
	gtk_text_buffer_get_iter_at_line (GTK_TEXT_BUFFER (self), &i, line);
	return i;
}


/* Iter at end of line, after the "\n" (if present).*/
GtkTextIter gtk_mate_buffer_line_end_iter (GtkMateBuffer* self, gint line) {
	0;
	if (line >= gtk_text_buffer_get_line_count (GTK_TEXT_BUFFER (self)) - 1) {
		return gtk_mate_buffer_end_iter (self);
	} else {
		return gtk_mate_buffer_line_start_iter (self, line + 1);
	}
}


/* Iter at end of line, before the "\n" (if present).*/
GtkTextIter gtk_mate_buffer_line_end_iter1 (GtkMateBuffer* self, gint line) {
	0;
	if (line >= gtk_text_buffer_get_line_count (GTK_TEXT_BUFFER (self)) - 1) {
		return gtk_mate_buffer_end_iter (self);
	} else {
		GtkTextIter i;
		i = gtk_mate_buffer_line_start_iter (self, line + 1);
		gtk_text_iter_backward_char (&i);
		return i;
	}
}


GtkTextMark* gtk_mate_buffer_start_mark (GtkMateBuffer* self) {
	GtkTextMark* _tmp0;
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (self), NULL);
	_tmp0 = NULL;
	return (_tmp0 = gtk_text_buffer_get_mark (GTK_TEXT_BUFFER (self), "start_mark"), (_tmp0 == NULL ? NULL : g_object_ref (_tmp0)));
}


GtkTextMark* gtk_mate_buffer_end_mark (GtkMateBuffer* self) {
	GtkTextMark* _tmp0;
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (self), NULL);
	_tmp0 = NULL;
	return (_tmp0 = gtk_text_buffer_get_mark (GTK_TEXT_BUFFER (self), "end_mark"), (_tmp0 == NULL ? NULL : g_object_ref (_tmp0)));
}


GtkTextMark* gtk_mate_buffer_cursor_mark (GtkMateBuffer* self) {
	GtkTextMark* _tmp0;
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (self), NULL);
	_tmp0 = NULL;
	return (_tmp0 = gtk_text_buffer_get_mark (GTK_TEXT_BUFFER (self), "insert"), (_tmp0 == NULL ? NULL : g_object_ref (_tmp0)));
}


GtkTextMark* gtk_mate_buffer_selection_mark (GtkMateBuffer* self) {
	GtkTextMark* _tmp0;
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (self), NULL);
	_tmp0 = NULL;
	return (_tmp0 = gtk_text_buffer_get_mark (GTK_TEXT_BUFFER (self), "selection"), (_tmp0 == NULL ? NULL : g_object_ref (_tmp0)));
}


/* Get text of line, including the "\n" if present. Returns null if line 
 does not exist.*/
char* gtk_mate_buffer_get_line (GtkMateBuffer* self, gint line) {
	GtkTextIter ei = {0};
	const char* _tmp2;
	GtkTextIter _tmp1 = {0};
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (self), NULL);
	if (line == gtk_text_buffer_get_line_count (GTK_TEXT_BUFFER (self)) - 1) {
		ei = gtk_mate_buffer_end_iter (self);
	} else {
		if (line > gtk_text_buffer_get_line_count (GTK_TEXT_BUFFER (self)) - 1 || line < 0) {
			return NULL;
		} else {
			ei = gtk_mate_buffer_line_start_iter (self, line + 1);
		}
	}
	_tmp2 = NULL;
	return (_tmp2 = gtk_text_buffer_get_slice (GTK_TEXT_BUFFER (self), (_tmp1 = gtk_mate_buffer_line_start_iter (self, line), &_tmp1), &ei, TRUE), (_tmp2 == NULL ? NULL : g_strdup (_tmp2)));
}


/* Get text of line, not including the "\n". Returns null if line
 does not exist.*/
char* gtk_mate_buffer_get_line1 (GtkMateBuffer* self, gint line_ix) {
	char* line;
	char* _tmp0;
	char* _tmp4;
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (self), NULL);
	line = NULL;
	_tmp0 = NULL;
	if ((line = (_tmp0 = gtk_mate_buffer_get_line (self, line_ix), (line = (g_free (line), NULL)), _tmp0)) != NULL) {
		if (line_ix == gtk_text_buffer_get_line_count (GTK_TEXT_BUFFER (self)) - 1) {
			return line;
		} else {
			char* _tmp2;
			char* _tmp3;
			_tmp2 = NULL;
			_tmp3 = NULL;
			return (_tmp3 = (_tmp2 = g_utf8_offset_to_pointer (line, ((glong) (0))), g_strndup (_tmp2, g_utf8_offset_to_pointer (_tmp2, string_get_length (line) - 1) - _tmp2)), (line = (g_free (line), NULL)), _tmp3);
		}
	}
	_tmp4 = NULL;
	return (_tmp4 = NULL, (line = (g_free (line), NULL)), _tmp4);
}


gint gtk_mate_buffer_get_line_length (GtkMateBuffer* self, gint line) {
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (self), 0);
	if (line >= gtk_text_buffer_get_line_count (GTK_TEXT_BUFFER (self)) || line < 0) {
		return -1;
	}
	if (line == gtk_text_buffer_get_line_count (GTK_TEXT_BUFFER (self)) - 1) {
		GtkTextIter _tmp2 = {0};
		GtkTextIter _tmp1 = {0};
		return gtk_text_iter_get_offset ((_tmp1 = gtk_mate_buffer_end_iter (self), &_tmp1)) - gtk_text_iter_get_offset ((_tmp2 = gtk_mate_buffer_line_start_iter (self, line), &_tmp2));
	} else {
		GtkTextIter _tmp5 = {0};
		GtkTextIter _tmp4 = {0};
		return gtk_text_iter_get_offset ((_tmp4 = gtk_mate_buffer_line_end_iter (self, line), &_tmp4)) - gtk_text_iter_get_offset ((_tmp5 = gtk_mate_buffer_line_start_iter (self, line), &_tmp5)) - 1;
	}
}


gint gtk_mate_buffer_cursor_line (GtkMateBuffer* self) {
	GtkTextIter _tmp0 = {0};
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (self), 0);
	return gtk_text_iter_get_line ((_tmp0 = gtk_mate_buffer_cursor_iter (self), &_tmp0));
}


gint gtk_mate_buffer_cursor_line_offset (GtkMateBuffer* self) {
	GtkTextIter _tmp0 = {0};
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (self), 0);
	return gtk_text_iter_get_line_offset ((_tmp0 = gtk_mate_buffer_cursor_iter (self), &_tmp0));
}


gint gtk_mate_buffer_cursor_offset (GtkMateBuffer* self) {
	GtkTextIter _tmp0 = {0};
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (self), 0);
	return gtk_text_iter_get_offset ((_tmp0 = gtk_mate_buffer_cursor_iter (self), &_tmp0));
}


GtkMateBuffer* gtk_mate_buffer_new (void) {
	GtkMateBuffer * self;
	self = g_object_newv (GTK_MATE_TYPE_BUFFER, 0, NULL);
	return self;
}


static GObject * gtk_mate_buffer_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GtkMateBufferClass * klass;
	GObjectClass * parent_class;
	GtkMateBuffer * self;
	klass = GTK_MATE_BUFFER_CLASS (g_type_class_peek (GTK_MATE_TYPE_BUFFER));
	parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = GTK_MATE_BUFFER (obj);
	{
		gtk_mate_load_bundles ();
		gtk_mate_load_themes ();
	}
	return obj;
}


static void gtk_mate_buffer_class_init (GtkMateBufferClass * klass) {
	gtk_mate_buffer_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = gtk_mate_buffer_constructor;
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_buffer_finalize;
}


static void gtk_mate_buffer_instance_init (GtkMateBuffer * self) {
}


static void gtk_mate_buffer_finalize (GObject * obj) {
	GtkMateBuffer * self;
	self = GTK_MATE_BUFFER (obj);
	(self->parser == NULL ? NULL : (self->parser = (g_object_unref (self->parser), NULL)));
	G_OBJECT_CLASS (gtk_mate_buffer_parent_class)->finalize (obj);
}


GType gtk_mate_buffer_get_type (void) {
	static GType gtk_mate_buffer_type_id = 0;
	if (gtk_mate_buffer_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateBufferClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_buffer_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateBuffer), 0, (GInstanceInitFunc) gtk_mate_buffer_instance_init };
		gtk_mate_buffer_type_id = g_type_register_static (GTK_TYPE_SOURCE_BUFFER, "GtkMateBuffer", &g_define_type_info, 0);
	}
	return gtk_mate_buffer_type_id;
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




