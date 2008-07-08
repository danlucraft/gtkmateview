
#include "grammar.h"
#include <stdio.h>
#include <gee/collection.h>




struct _GtkMateGrammarPrivate {
	char* _name;
	PListDict* _plist;
};

#define GTK_MATE_GRAMMAR_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammarPrivate))
enum  {
	GTK_MATE_GRAMMAR_DUMMY_PROPERTY,
	GTK_MATE_GRAMMAR_NAME,
	GTK_MATE_GRAMMAR_PLIST
};
static void gtk_mate_grammar_set_name (GtkMateGrammar* self, const char* value);
static void gtk_mate_grammar_set_plist (GtkMateGrammar* self, PListDict* value);
static gpointer gtk_mate_grammar_parent_class = NULL;
static void gtk_mate_grammar_dispose (GObject * obj);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);



GtkMateGrammar* gtk_mate_grammar_new (PListDict* plist) {
	GtkMateGrammar * self;
	g_return_val_if_fail (PLIST_IS_DICT (plist), NULL);
	self = g_object_newv (GTK_MATE_TYPE_GRAMMAR, 0, NULL);
	gtk_mate_grammar_set_plist (self, plist);
	return self;
}


void gtk_mate_grammar_init_for_reference (GtkMateGrammar* self) {
	PListNode* nm;
	PListNode* flm;
	PListNode* ke;
	PListNode* sn;
	PListNode* cm;
	PListNode* filetypes;
	g_return_if_fail (GTK_MATE_IS_GRAMMAR (self));
	nm = plist_dict_get (self->priv->_plist, "name");
	if (nm != NULL) {
		gtk_mate_grammar_set_name (self, (PLIST_STRING (nm))->str);
	}
	flm = plist_dict_get (self->priv->_plist, "firstLineMatch");
	if (flm != NULL) {
		OnigurumaRegex* _tmp0;
		_tmp0 = NULL;
		self->first_line_match = (_tmp0 = oniguruma_regex_make1 ((PLIST_STRING (flm))->str), (self->first_line_match == NULL ? NULL : (self->first_line_match = (g_object_unref (self->first_line_match), NULL))), _tmp0);
	}
	ke = plist_dict_get (self->priv->_plist, "keyEquivalent");
	if (ke != NULL) {
		char* _tmp2;
		const char* _tmp1;
		_tmp2 = NULL;
		_tmp1 = NULL;
		self->key_equivalent = (_tmp2 = (_tmp1 = (PLIST_STRING (ke))->str, (_tmp1 == NULL ? NULL : g_strdup (_tmp1))), (self->key_equivalent = (g_free (self->key_equivalent), NULL)), _tmp2);
	}
	sn = plist_dict_get (self->priv->_plist, "scopeName");
	if (sn != NULL) {
		char* _tmp4;
		const char* _tmp3;
		_tmp4 = NULL;
		_tmp3 = NULL;
		self->scope_name = (_tmp4 = (_tmp3 = (PLIST_STRING (sn))->str, (_tmp3 == NULL ? NULL : g_strdup (_tmp3))), (self->scope_name = (g_free (self->scope_name), NULL)), _tmp4);
	}
	cm = plist_dict_get (self->priv->_plist, "comment");
	if (cm != NULL) {
		char* _tmp6;
		const char* _tmp5;
		_tmp6 = NULL;
		_tmp5 = NULL;
		self->comment = (_tmp6 = (_tmp5 = (PLIST_STRING (cm))->str, (_tmp5 == NULL ? NULL : g_strdup (_tmp5))), (self->comment = (g_free (self->comment), NULL)), _tmp6);
	}
	fprintf (stdout, "%s     %s.\n", self->priv->_name, self->scope_name);
	filetypes = plist_dict_get (self->priv->_plist, "fileTypes");
	if (filetypes != NULL) {
		PListArray* _tmp7;
		PListArray* fts;
		char** _tmp9;
		gint _tmp8;
		gint i;
		_tmp7 = NULL;
		fts = (_tmp7 = PLIST_ARRAY (filetypes), (_tmp7 == NULL ? NULL : g_object_ref (_tmp7)));
		_tmp9 = NULL;
		self->file_types = (_tmp9 = g_new0 (char*, (_tmp8 = gee_collection_get_size (GEE_COLLECTION (fts->array))) + 1), (self->file_types = (_vala_array_free (self->file_types, self->file_types_length1, ((GDestroyNotify) (g_free))), NULL)), self->file_types_length1 = _tmp8, _tmp9);
		i = 0;
		{
			GeeArrayList* n_collection;
			int n_it;
			n_collection = fts->array;
			for (n_it = 0; n_it < gee_collection_get_size (GEE_COLLECTION (n_collection)); n_it = n_it + 1) {
				PListNode* n;
				n = ((PListNode*) (gee_list_get (GEE_LIST (n_collection), n_it)));
				{
					gint _tmp12;
					char* _tmp11;
					const char* _tmp10;
					_tmp11 = NULL;
					_tmp10 = NULL;
					_tmp12 = i++;
					self->file_types[_tmp12] = (_tmp11 = (_tmp10 = (PLIST_STRING (n))->str, (_tmp10 == NULL ? NULL : g_strdup (_tmp10))), (self->file_types[_tmp12] = (g_free (self->file_types[_tmp12]), NULL)), _tmp11);
					(n == NULL ? NULL : (n = (g_object_unref (n), NULL)));
				}
			}
		}
		(fts == NULL ? NULL : (fts = (g_object_unref (fts), NULL)));
	}
	(nm == NULL ? NULL : (nm = (g_object_unref (nm), NULL)));
	(flm == NULL ? NULL : (flm = (g_object_unref (flm), NULL)));
	(ke == NULL ? NULL : (ke = (g_object_unref (ke), NULL)));
	(sn == NULL ? NULL : (sn = (g_object_unref (sn), NULL)));
	(cm == NULL ? NULL : (cm = (g_object_unref (cm), NULL)));
	(filetypes == NULL ? NULL : (filetypes = (g_object_unref (filetypes), NULL)));
}


void gtk_mate_grammar_init_for_use (GtkMateGrammar* self) {
	g_return_if_fail (GTK_MATE_IS_GRAMMAR (self));
}


const char* gtk_mate_grammar_get_name (GtkMateGrammar* self) {
	g_return_val_if_fail (GTK_MATE_IS_GRAMMAR (self), NULL);
	return self->priv->_name;
}


static void gtk_mate_grammar_set_name (GtkMateGrammar* self, const char* value) {
	char* _tmp2;
	const char* _tmp1;
	g_return_if_fail (GTK_MATE_IS_GRAMMAR (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_name = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_strdup (_tmp1))), (self->priv->_name = (g_free (self->priv->_name), NULL)), _tmp2);
}


PListDict* gtk_mate_grammar_get_plist (GtkMateGrammar* self) {
	g_return_val_if_fail (GTK_MATE_IS_GRAMMAR (self), NULL);
	return self->priv->_plist;
}


static void gtk_mate_grammar_set_plist (GtkMateGrammar* self, PListDict* value) {
	PListDict* _tmp2;
	PListDict* _tmp1;
	g_return_if_fail (GTK_MATE_IS_GRAMMAR (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_plist = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), (self->priv->_plist == NULL ? NULL : (self->priv->_plist = (g_object_unref (self->priv->_plist), NULL))), _tmp2);
}


static void gtk_mate_grammar_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GtkMateGrammar * self;
	self = GTK_MATE_GRAMMAR (object);
	switch (property_id) {
		case GTK_MATE_GRAMMAR_NAME:
		g_value_set_string (value, gtk_mate_grammar_get_name (self));
		break;
		case GTK_MATE_GRAMMAR_PLIST:
		g_value_set_object (value, gtk_mate_grammar_get_plist (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_grammar_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GtkMateGrammar * self;
	self = GTK_MATE_GRAMMAR (object);
	switch (property_id) {
		case GTK_MATE_GRAMMAR_NAME:
		gtk_mate_grammar_set_name (self, g_value_get_string (value));
		break;
		case GTK_MATE_GRAMMAR_PLIST:
		gtk_mate_grammar_set_plist (self, g_value_get_object (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gtk_mate_grammar_class_init (GtkMateGrammarClass * klass) {
	gtk_mate_grammar_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GtkMateGrammarPrivate));
	G_OBJECT_CLASS (klass)->get_property = gtk_mate_grammar_get_property;
	G_OBJECT_CLASS (klass)->set_property = gtk_mate_grammar_set_property;
	G_OBJECT_CLASS (klass)->dispose = gtk_mate_grammar_dispose;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_GRAMMAR_NAME, g_param_spec_string ("name", "name", "name", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GTK_MATE_GRAMMAR_PLIST, g_param_spec_object ("plist", "plist", "plist", PLIST_TYPE_DICT, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void gtk_mate_grammar_instance_init (GtkMateGrammar * self) {
	self->priv = GTK_MATE_GRAMMAR_GET_PRIVATE (self);
}


static void gtk_mate_grammar_dispose (GObject * obj) {
	GtkMateGrammar * self;
	self = GTK_MATE_GRAMMAR (obj);
	self->priv->_name = (g_free (self->priv->_name), NULL);
	(self->priv->_plist == NULL ? NULL : (self->priv->_plist = (g_object_unref (self->priv->_plist), NULL)));
	self->file_types = (_vala_array_free (self->file_types, self->file_types_length1, ((GDestroyNotify) (g_free))), NULL);
	(self->first_line_match == NULL ? NULL : (self->first_line_match = (g_object_unref (self->first_line_match), NULL)));
	self->key_equivalent = (g_free (self->key_equivalent), NULL);
	self->scope_name = (g_free (self->scope_name), NULL);
	self->comment = (g_free (self->comment), NULL);
	G_OBJECT_CLASS (gtk_mate_grammar_parent_class)->dispose (obj);
}


GType gtk_mate_grammar_get_type (void) {
	static GType gtk_mate_grammar_type_id = 0;
	if (G_UNLIKELY (gtk_mate_grammar_type_id == 0)) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateGrammarClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_grammar_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateGrammar), 0, (GInstanceInitFunc) gtk_mate_grammar_instance_init };
		gtk_mate_grammar_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateGrammar", &g_define_type_info, 0);
	}
	return gtk_mate_grammar_type_id;
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if (array != NULL && destroy_func != NULL) {
		int i;
		if (array_length >= 0)
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) (array))[i] != NULL)
			destroy_func (((gpointer*) (array))[i]);
		}
		else
		for (i = 0; ((gpointer*) (array))[i] != NULL; i = i + 1) {
			destroy_func (((gpointer*) (array))[i]);
		}
	}
	g_free (array);
}




