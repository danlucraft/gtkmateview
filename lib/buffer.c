
#include "buffer.h"
#include <bundle.h>
#include <grammar.h>
#include <parser.h>
#include <onig_wrap.h>
#include <gtkmateview.h>




enum  {
	GTK_MATE_BUFFER_DUMMY_PROPERTY
};
GeeArrayList* gtk_mate_buffer_bundles = NULL;
GeeArrayList* gtk_mate_buffer_themes = NULL;
static GObject * gtk_mate_buffer_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer gtk_mate_buffer_parent_class = NULL;
static void gtk_mate_buffer_dispose (GObject * obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



/* Sets the grammar explicitly by name.*/
gint gtk_mate_buffer_set_grammar_by_name (GtkMateBuffer* self, const char* name) {
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (self), 0);
	g_return_val_if_fail (name != NULL, 0);
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
								gint _tmp1;
								_tmp0 = NULL;
								self->parser = (_tmp0 = gtk_mate_parser_create (gr, self), (self->parser == NULL ? NULL : (self->parser = (g_object_unref (self->parser), NULL))), _tmp0);
								return (_tmp1 = 1, (gr == NULL ? NULL : (gr = (g_object_unref (gr), NULL))), (bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL))), _tmp1);
							}
							(gr == NULL ? NULL : (gr = (g_object_unref (gr), NULL)));
						}
					}
				}
				(bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL)));
			}
		}
	}
	return 0;
}


/* Sets the grammar by the file extension, then checks the
 first line for matches as a fallback. If unable to find
 a grammar, sets the grammar to null. Returns the grammar
 name or null.*/
char* gtk_mate_buffer_set_grammar_by_extension (GtkMateBuffer* self, const char* extension) {
	OnigurumaRegex* re;
	const char* _tmp6;
	GtkTextIter _tmp5 = {0};
	GtkTextIter _tmp4 = {0};
	char* first_line;
	GtkMateParser* _tmp14;
	char* _tmp15;
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (self), NULL);
	g_return_val_if_fail (extension != NULL, NULL);
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
									const char* _tmp3;
									char* ext;
									_tmp3 = NULL;
									ext = (_tmp3 = ext_collection[ext_it], (_tmp3 == NULL ? NULL : g_strdup (_tmp3)));
									{
										if (_vala_strcmp0 (ext, extension) == 0) {
											GtkMateParser* _tmp0;
											const char* _tmp1;
											char* _tmp2;
											_tmp0 = NULL;
											self->parser = (_tmp0 = gtk_mate_parser_create (gr, self), (self->parser == NULL ? NULL : (self->parser = (g_object_unref (self->parser), NULL))), _tmp0);
											_tmp1 = NULL;
											_tmp2 = NULL;
											return (_tmp2 = (_tmp1 = gtk_mate_grammar_get_name (gr), (_tmp1 == NULL ? NULL : g_strdup (_tmp1))), (ext = (g_free (ext), NULL)), (gr == NULL ? NULL : (gr = (g_object_unref (gr), NULL))), (bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL))), _tmp2);
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
	re = NULL;
	_tmp6 = NULL;
	first_line = (_tmp6 = gtk_text_buffer_get_text (GTK_TEXT_BUFFER (self), (_tmp4 = gtk_mate_buffer_iter_ (self, 0), &_tmp4), (_tmp5 = gtk_mate_buffer_iter_line_start (self, 1), &_tmp5), FALSE), (_tmp6 == NULL ? NULL : g_strdup (_tmp6)));
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
							OnigurumaRegex* _tmp8;
							OnigurumaRegex* _tmp7;
							_tmp8 = NULL;
							_tmp7 = NULL;
							if ((re = (_tmp8 = (_tmp7 = gr->first_line_match, (_tmp7 == NULL ? NULL : g_object_ref (_tmp7))), (re == NULL ? NULL : (re = (g_object_unref (re), NULL))), _tmp8)) != NULL) {
								OnigurumaMatch* _tmp9;
								gboolean _tmp10;
								_tmp9 = NULL;
								if ((_tmp10 = (_tmp9 = oniguruma_regex_search (re, first_line, 0, ((gint) (strlen (first_line))))) != NULL, (_tmp9 == NULL ? NULL : (_tmp9 = (g_object_unref (_tmp9), NULL))), _tmp10)) {
									GtkMateParser* _tmp11;
									const char* _tmp12;
									char* _tmp13;
									_tmp11 = NULL;
									self->parser = (_tmp11 = gtk_mate_parser_create (gr, self), (self->parser == NULL ? NULL : (self->parser = (g_object_unref (self->parser), NULL))), _tmp11);
									_tmp12 = NULL;
									_tmp13 = NULL;
									return (_tmp13 = (_tmp12 = gtk_mate_grammar_get_name (gr), (_tmp12 == NULL ? NULL : g_strdup (_tmp12))), (gr == NULL ? NULL : (gr = (g_object_unref (gr), NULL))), (bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL))), (re == NULL ? NULL : (re = (g_object_unref (re), NULL))), (first_line = (g_free (first_line), NULL)), _tmp13);
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
	_tmp14 = NULL;
	self->parser = (_tmp14 = NULL, (self->parser == NULL ? NULL : (self->parser = (g_object_unref (self->parser), NULL))), _tmp14);
	_tmp15 = NULL;
	return (_tmp15 = NULL, (re == NULL ? NULL : (re = (g_object_unref (re), NULL))), (first_line = (g_free (first_line), NULL)), _tmp15);
}


/* Offset from start of document -> Iter*/
GtkTextIter gtk_mate_buffer_iter_ (GtkMateBuffer* self, gint offset) {
	GtkTextIter i = {0};
	0;
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER (self), &i, offset);
	return i;
}


/* Line number -> Iter*/
GtkTextIter gtk_mate_buffer_iter_line_start (GtkMateBuffer* self, gint line) {
	GtkTextIter i = {0};
	0;
	gtk_text_buffer_get_iter_at_line (GTK_TEXT_BUFFER (self), &i, line);
	return i;
}


GtkMateBuffer* gtk_mate_buffer_new (void) {
	GtkMateBuffer * self;
	self = g_object_newv (GTK_MATE_TYPE_BUFFER, 0, NULL);
	return self;
}


/* public TextIter iter_end() {
 }
 Line number -> Iter
 public TextIter iter_line_end(int line) {
 // if num >= line_count - 1
 //   iter(end_mark)
 // else
 //   line_start(num+1)
 // // end
 // TextIter i;
 // if (line >= line_count() - 1)
 // iter(
 // get_iter_at_line(out i, line);
 // return i;
 }*/
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
	G_OBJECT_CLASS (klass)->dispose = gtk_mate_buffer_dispose;
}


static void gtk_mate_buffer_instance_init (GtkMateBuffer * self) {
}


static void gtk_mate_buffer_dispose (GObject * obj) {
	GtkMateBuffer * self;
	self = GTK_MATE_BUFFER (obj);
	(self->parser == NULL ? NULL : (self->parser = (g_object_unref (self->parser), NULL)));
	G_OBJECT_CLASS (gtk_mate_buffer_parent_class)->dispose (obj);
}


GType gtk_mate_buffer_get_type (void) {
	static GType gtk_mate_buffer_type_id = 0;
	if (G_UNLIKELY (gtk_mate_buffer_type_id == 0)) {
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




