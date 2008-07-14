
#include "buffer.h"
#include <bundle.h>
#include <onig_wrap.h>
#include <gtkmateview.h>




enum  {
	GTK_MATE_BUFFER_DUMMY_PROPERTY,
	GTK_MATE_BUFFER_GRAMMAR
};
GeeArrayList* gtk_mate_buffer_bundles = NULL;
GeeArrayList* gtk_mate_buffer_themes = NULL;
static GtkMateGrammar* gtk_mate_buffer__grammar;
static GObject * gtk_mate_buffer_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer gtk_mate_buffer_parent_class = NULL;
static void gtk_mate_buffer_dispose (GObject * obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



/* Sets the grammar with the file extension, then checks the
 first line for matches as a fallback. If unable to find
 a grammar, sets the grammar to null. Returns the grammar
 name or null.*/
char* gtk_mate_buffer_set_grammar_by_extension (GtkMateBuffer* self, const char* extension) {
	OnigurumaRegex* re;
	const char* _tmp4;
	GtkTextIter _tmp3 = {0};
	GtkTextIter _tmp2 = {0};
	char* first_line;
	char* _tmp11;
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
								GeeArrayList* ext_collection;
								int ext_it;
								ext_collection = gr->file_types;
								for (ext_it = 0; ext_it < gee_collection_get_size (GEE_COLLECTION (ext_collection)); ext_it = ext_it + 1) {
									char* ext;
									ext = ((char*) (gee_list_get (GEE_LIST (ext_collection), ext_it)));
									{
										if (_vala_strcmp0 (ext, extension) == 0) {
											const char* _tmp0;
											char* _tmp1;
											gtk_mate_buffer_set_grammar (self, gr);
											_tmp0 = NULL;
											_tmp1 = NULL;
											return (_tmp1 = (_tmp0 = gtk_mate_grammar_get_name (gr), (_tmp0 == NULL ? NULL : g_strdup (_tmp0))), (ext = (g_free (ext), NULL)), (gr == NULL ? NULL : (gr = (g_object_unref (gr), NULL))), (bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL))), _tmp1);
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
	_tmp4 = NULL;
	first_line = (_tmp4 = gtk_text_buffer_get_text (GTK_TEXT_BUFFER (self), (_tmp2 = gtk_mate_buffer_iter_ (self, 0), &_tmp2), (_tmp3 = gtk_mate_buffer_iter_line_start (self, 1), &_tmp3), FALSE), (_tmp4 == NULL ? NULL : g_strdup (_tmp4)));
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
							OnigurumaRegex* _tmp6;
							OnigurumaRegex* _tmp5;
							_tmp6 = NULL;
							_tmp5 = NULL;
							if ((re = (_tmp6 = (_tmp5 = gr->first_line_match, (_tmp5 == NULL ? NULL : g_object_ref (_tmp5))), (re == NULL ? NULL : (re = (g_object_unref (re), NULL))), _tmp6)) != NULL) {
								OnigurumaMatch* _tmp7;
								gboolean _tmp8;
								_tmp7 = NULL;
								if ((_tmp8 = (_tmp7 = oniguruma_regex_search (re, first_line, 0, ((gint) (strlen (first_line))))) != NULL, (_tmp7 == NULL ? NULL : (_tmp7 = (g_object_unref (_tmp7), NULL))), _tmp8)) {
									const char* _tmp9;
									char* _tmp10;
									gtk_mate_buffer_set_grammar (self, gr);
									_tmp9 = NULL;
									_tmp10 = NULL;
									return (_tmp10 = (_tmp9 = gtk_mate_grammar_get_name (gr), (_tmp9 == NULL ? NULL : g_strdup (_tmp9))), (gr == NULL ? NULL : (gr = (g_object_unref (gr), NULL))), (bundle == NULL ? NULL : (bundle = (g_object_unref (bundle), NULL))), (re == NULL ? NULL : (re = (g_object_unref (re), NULL))), (first_line = (g_free (first_line), NULL)), _tmp10);
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
	gtk_mate_buffer_set_grammar (self, NULL);
	_tmp11 = NULL;
	return (_tmp11 = NULL, (re == NULL ? NULL : (re = (g_object_unref (re), NULL))), (first_line = (g_free (first_line), NULL)), _tmp11);
}


GtkTextIter gtk_mate_buffer_iter_ (GtkMateBuffer* self, gint offset) {
	GtkTextIter i = {0};
	0;
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER (self), &i, offset);
	return i;
}


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


GtkMateGrammar* gtk_mate_buffer_get_grammar (GtkMateBuffer* self) {
	g_return_val_if_fail (GTK_MATE_IS_BUFFER (self), NULL);
	return gtk_mate_buffer__grammar;
}


void gtk_mate_buffer_set_grammar (GtkMateBuffer* self, GtkMateGrammar* value) {
	GtkMateGrammar* _tmp2;
	GtkMateGrammar* _tmp1;
	g_return_if_fail (GTK_MATE_IS_BUFFER (self));
	if (value != NULL) {
		gtk_mate_grammar_init_for_use (value);
	}
	_tmp2 = NULL;
	_tmp1 = NULL;
	gtk_mate_buffer__grammar = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (gtk_mate_buffer__grammar == NULL ? NULL : (gtk_mate_buffer__grammar = (g_object_unref (gtk_mate_buffer__grammar), NULL))), _tmp2);
	g_object_notify (((GObject *) (self)), "grammar");
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
	}
	return obj;
}


static void gtk_mate_buffer_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateBuffer * self;
	self = GTK_MATE_BUFFER (object);
	switch (property_id) {
		case GTK_MATE_BUFFER_GRAMMAR:
		g_value_set_object (value, gtk_mate_buffer_get_grammar (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_buffer_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GtkMateBuffer * self;
	self = GTK_MATE_BUFFER (object);
	switch (property_id) {
		case GTK_MATE_BUFFER_GRAMMAR:
		gtk_mate_buffer_set_grammar (self, g_value_get_object (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_buffer_class_init (GtkMateBufferClass * klass) {
	gtk_mate_buffer_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->get_property = gtk_mate_buffer_get_property;
	G_OBJECT_CLASS (klass)->set_property = gtk_mate_buffer_set_property;
	G_OBJECT_CLASS (klass)->constructor = gtk_mate_buffer_constructor;
	G_OBJECT_CLASS (klass)->dispose = gtk_mate_buffer_dispose;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_BUFFER_GRAMMAR, g_param_spec_object ("grammar", "grammar", "grammar", GTK_MATE_TYPE_GRAMMAR, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void gtk_mate_buffer_instance_init (GtkMateBuffer * self) {
}


static void gtk_mate_buffer_dispose (GObject * obj) {
	GtkMateBuffer * self;
	self = GTK_MATE_BUFFER (obj);
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




