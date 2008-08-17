
#include "onig_wrap.h"




enum  {
	ONIGURUMA_ONIG_ERROR_DUMMY_PROPERTY
};
static gpointer oniguruma_onig_error_parent_class = NULL;
static void oniguruma_onig_error_finalize (GObject * obj);
struct _OnigurumaMatchPrivate {
	regex_t* _rx;
	OnigRegion* _rg;
};

#define ONIGURUMA_MATCH_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), ONIGURUMA_TYPE_MATCH, OnigurumaMatchPrivate))
enum  {
	ONIGURUMA_MATCH_DUMMY_PROPERTY,
	ONIGURUMA_MATCH_RX,
	ONIGURUMA_MATCH_RG
};
static gpointer oniguruma_match_parent_class = NULL;
static void oniguruma_match_finalize (GObject * obj);
struct _OnigurumaRegexPrivate {
	regex_t* _rx;
};

#define ONIGURUMA_REGEX_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), ONIGURUMA_TYPE_REGEX, OnigurumaRegexPrivate))
enum  {
	ONIGURUMA_REGEX_DUMMY_PROPERTY,
	ONIGURUMA_REGEX_RX
};
static gpointer oniguruma_regex_parent_class = NULL;
static void oniguruma_regex_finalize (GObject * obj);



OnigurumaOnigError* oniguruma_onig_error_new (void) {
	OnigurumaOnigError * self;
	self = g_object_newv (ONIGURUMA_TYPE_ONIG_ERROR, 0, NULL);
	return self;
}


static void oniguruma_onig_error_class_init (OnigurumaOnigErrorClass * klass) {
	oniguruma_onig_error_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = oniguruma_onig_error_finalize;
}


static void oniguruma_onig_error_instance_init (OnigurumaOnigError * self) {
}


static void oniguruma_onig_error_finalize (GObject * obj) {
	OnigurumaOnigError * self;
	self = ONIGURUMA_ONIG_ERROR (obj);
	G_OBJECT_CLASS (oniguruma_onig_error_parent_class)->finalize (obj);
}


GType oniguruma_onig_error_get_type (void) {
	static GType oniguruma_onig_error_type_id = 0;
	if (oniguruma_onig_error_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (OnigurumaOnigErrorClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) oniguruma_onig_error_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (OnigurumaOnigError), 0, (GInstanceInitFunc) oniguruma_onig_error_instance_init };
		oniguruma_onig_error_type_id = g_type_register_static (G_TYPE_OBJECT, "OnigurumaOnigError", &g_define_type_info, 0);
	}
	return oniguruma_onig_error_type_id;
}


gint oniguruma_match_begin (OnigurumaMatch* self, gint capture) {
	g_return_val_if_fail (ONIGURUMA_IS_MATCH (self), 0);
	if (capture >= self->priv->_rg->num_regs || capture < 0) {
		return -1;
	}
	return self->priv->_rg->beg[capture];
}


gint oniguruma_match_end (OnigurumaMatch* self, gint capture) {
	g_return_val_if_fail (ONIGURUMA_IS_MATCH (self), 0);
	if (capture >= self->priv->_rg->num_regs || capture < 0) {
		return -1;
	}
	return self->priv->_rg->end[capture];
}


OnigurumaMatch* oniguruma_match_new (void) {
	OnigurumaMatch * self;
	self = g_object_newv (ONIGURUMA_TYPE_MATCH, 0, NULL);
	return self;
}


regex_t* oniguruma_match_get_rx (OnigurumaMatch* self) {
	g_return_val_if_fail (ONIGURUMA_IS_MATCH (self), NULL);
	return self->priv->_rx;
}


void oniguruma_match_set_rx (OnigurumaMatch* self, regex_t* value) {
	regex_t* _tmp2;
	regex_t* _tmp1;
	g_return_if_fail (ONIGURUMA_IS_MATCH (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_rx = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL :  (_tmp1))), (self->priv->_rx == NULL ? NULL : (self->priv->_rx = ( (self->priv->_rx), NULL))), _tmp2);
	g_object_notify (((GObject *) (self)), "rx");
}


OnigRegion* oniguruma_match_get_rg (OnigurumaMatch* self) {
	g_return_val_if_fail (ONIGURUMA_IS_MATCH (self), NULL);
	return self->priv->_rg;
}


void oniguruma_match_set_rg (OnigurumaMatch* self, OnigRegion* value) {
	OnigRegion* _tmp2;
	OnigRegion* _tmp1;
	g_return_if_fail (ONIGURUMA_IS_MATCH (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_rg = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL :  (_tmp1))), (self->priv->_rg == NULL ? NULL : (self->priv->_rg = ( (self->priv->_rg), NULL))), _tmp2);
	g_object_notify (((GObject *) (self)), "rg");
}


static void oniguruma_match_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	OnigurumaMatch * self;
	self = ONIGURUMA_MATCH (object);
	switch (property_id) {
		case ONIGURUMA_MATCH_RX:
		g_value_set_pointer (value, oniguruma_match_get_rx (self));
		break;
		case ONIGURUMA_MATCH_RG:
		g_value_set_pointer (value, oniguruma_match_get_rg (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void oniguruma_match_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	OnigurumaMatch * self;
	self = ONIGURUMA_MATCH (object);
	switch (property_id) {
		case ONIGURUMA_MATCH_RX:
		oniguruma_match_set_rx (self, g_value_get_pointer (value));
		break;
		case ONIGURUMA_MATCH_RG:
		oniguruma_match_set_rg (self, g_value_get_pointer (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void oniguruma_match_class_init (OnigurumaMatchClass * klass) {
	oniguruma_match_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (OnigurumaMatchPrivate));
	G_OBJECT_CLASS (klass)->get_property = oniguruma_match_get_property;
	G_OBJECT_CLASS (klass)->set_property = oniguruma_match_set_property;
	G_OBJECT_CLASS (klass)->finalize = oniguruma_match_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), ONIGURUMA_MATCH_RX, g_param_spec_pointer ("rx", "rx", "rx", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), ONIGURUMA_MATCH_RG, g_param_spec_pointer ("rg", "rg", "rg", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void oniguruma_match_instance_init (OnigurumaMatch * self) {
	self->priv = ONIGURUMA_MATCH_GET_PRIVATE (self);
}


static void oniguruma_match_finalize (GObject * obj) {
	OnigurumaMatch * self;
	self = ONIGURUMA_MATCH (obj);
	(self->priv->_rx == NULL ? NULL : (self->priv->_rx = ( (self->priv->_rx), NULL)));
	(self->priv->_rg == NULL ? NULL : (self->priv->_rg = ( (self->priv->_rg), NULL)));
	G_OBJECT_CLASS (oniguruma_match_parent_class)->finalize (obj);
}


GType oniguruma_match_get_type (void) {
	static GType oniguruma_match_type_id = 0;
	if (oniguruma_match_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (OnigurumaMatchClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) oniguruma_match_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (OnigurumaMatch), 0, (GInstanceInitFunc) oniguruma_match_instance_init };
		oniguruma_match_type_id = g_type_register_static (G_TYPE_OBJECT, "OnigurumaMatch", &g_define_type_info, 0);
	}
	return oniguruma_match_type_id;
}


OnigurumaMatch* oniguruma_regex_search (OnigurumaRegex* self, const char* target, gint start, gint end) {
	OnigRegion* rg;
	gchar* ctarget;
	gint r;
	g_return_val_if_fail (ONIGURUMA_IS_REGEX (self), NULL);
	g_return_val_if_fail (target != NULL, NULL);
	rg = onig_region_new ();
	ctarget = ((gchar*) (target));
	r = onig_search (self->priv->_rx, ctarget, (ctarget + strlen (target)), ctarget + start, (ctarget + end), rg, ONIG_OPTION_NONE);
	if (r < 0) {
		OnigurumaMatch* _tmp0;
		_tmp0 = NULL;
		return (_tmp0 = NULL, (rg == NULL ? NULL : (rg = ( (rg), NULL))), _tmp0);
	} else {
		OnigurumaMatch* md;
		OnigurumaMatch* _tmp1;
		md = oniguruma_match_new ();
		oniguruma_match_set_rg (md, rg);
		oniguruma_match_set_rx (md, self->priv->_rx);
		_tmp1 = NULL;
		return (_tmp1 = md, (rg == NULL ? NULL : (rg = ( (rg), NULL))), _tmp1);
	}
	(rg == NULL ? NULL : (rg = ( (rg), NULL)));
}


OnigurumaRegex* oniguruma_regex_make (const char* pattern, OnigOptionType* options, OnigurumaOnigError** error) {
	OnigurumaRegex* rx;
	gchar* c_pattern;
	regex_t* rx1;
	OnigErrorInfo err_info = {0};
	regex_t* _tmp2;
	gint _tmp1;
	regex_t* _tmp0;
	gint r;
	OnigurumaRegex* _tmp5;
	g_return_val_if_fail (pattern != NULL, NULL);
	(*error) = NULL;
	rx = oniguruma_regex_new ();
	c_pattern = ((gchar*) (pattern));
	rx1 = NULL;
	/* OnigSyntaxType syntax;
	 stdout.printf("foo\n");
	 Oniguruma.Syntax.copy(&syntax, Syntax.DEFAULT);
	 // stdout.printf("bar\n");
	 // stdout.printf("op2; %d\n", (int) syntax.get_op2()); 
	 int newop2 = (int) (syntax.get_op2() | Syntax.Op2.ATMARK_CAPTURE_HISTORY);
	 // stdout.printf("newop2; %d\n", newop2);
	 syntax.set_op2((int) newop2);
	 stdout.printf("baz\n");*/
	_tmp2 = NULL;
	_tmp0 = NULL;
	r = (_tmp1 = onig_new (&_tmp0, c_pattern, (c_pattern + strlen (pattern)), options, ((gint) (ONIG_ENCODING_ASCII)), ONIG_SYNTAX_DEFAULT, &err_info), rx1 = (_tmp2 = _tmp0, (rx1 == NULL ? NULL : (rx1 = ( (rx1), NULL))), _tmp2), _tmp1);
	rx->matches_start_of_line = g_str_has_prefix (pattern, "^");
	if (r < 0) {
		OnigurumaOnigError* _tmp3;
		OnigurumaRegex* _tmp4;
		_tmp3 = NULL;
		(*error) = (_tmp3 = oniguruma_onig_error_new (), ((*error) == NULL ? NULL : ((*error) = (g_object_unref ((*error)), NULL))), _tmp3);
		(*error)->code = r;
		(*error)->error_info = err_info;
		_tmp4 = NULL;
		return (_tmp4 = NULL, (rx == NULL ? NULL : (rx = (g_object_unref (rx), NULL))), (rx1 == NULL ? NULL : (rx1 = ( (rx1), NULL))), _tmp4);
	}
	oniguruma_regex_set_rx (rx, rx1);
	_tmp5 = NULL;
	return (_tmp5 = rx, (rx1 == NULL ? NULL : (rx1 = ( (rx1), NULL))), _tmp5);
}


OnigurumaRegex* oniguruma_regex_make1 (const char* pattern) {
	OnigurumaOnigError* e;
	OnigurumaOnigError* _tmp2;
	OnigurumaRegex* _tmp1;
	OnigurumaOnigError* _tmp0;
	OnigurumaRegex* _tmp3;
	g_return_val_if_fail (pattern != NULL, NULL);
	e = NULL;
	_tmp2 = NULL;
	_tmp1 = NULL;
	_tmp0 = NULL;
	_tmp3 = NULL;
	return (_tmp3 = (_tmp1 = oniguruma_regex_make (pattern, ONIG_OPTION_MULTILINE, &_tmp0), e = (_tmp2 = _tmp0, (e == NULL ? NULL : (e = (g_object_unref (e), NULL))), _tmp2), _tmp1), (e == NULL ? NULL : (e = (g_object_unref (e), NULL))), _tmp3);
}


OnigurumaRegex* oniguruma_regex_new (void) {
	OnigurumaRegex * self;
	self = g_object_newv (ONIGURUMA_TYPE_REGEX, 0, NULL);
	return self;
}


regex_t* oniguruma_regex_get_rx (OnigurumaRegex* self) {
	g_return_val_if_fail (ONIGURUMA_IS_REGEX (self), NULL);
	return self->priv->_rx;
}


void oniguruma_regex_set_rx (OnigurumaRegex* self, regex_t* value) {
	regex_t* _tmp2;
	regex_t* _tmp1;
	g_return_if_fail (ONIGURUMA_IS_REGEX (self));
	_tmp2 = NULL;
	_tmp1 = NULL;
	self->priv->_rx = (_tmp2 = (_tmp1 = value, (_tmp1 == NULL ? NULL :  (_tmp1))), (self->priv->_rx == NULL ? NULL : (self->priv->_rx = ( (self->priv->_rx), NULL))), _tmp2);
	g_object_notify (((GObject *) (self)), "rx");
}


static void oniguruma_regex_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	OnigurumaRegex * self;
	self = ONIGURUMA_REGEX (object);
	switch (property_id) {
		case ONIGURUMA_REGEX_RX:
		g_value_set_pointer (value, oniguruma_regex_get_rx (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void oniguruma_regex_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	OnigurumaRegex * self;
	self = ONIGURUMA_REGEX (object);
	switch (property_id) {
		case ONIGURUMA_REGEX_RX:
		oniguruma_regex_set_rx (self, g_value_get_pointer (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void oniguruma_regex_class_init (OnigurumaRegexClass * klass) {
	oniguruma_regex_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (OnigurumaRegexPrivate));
	G_OBJECT_CLASS (klass)->get_property = oniguruma_regex_get_property;
	G_OBJECT_CLASS (klass)->set_property = oniguruma_regex_set_property;
	G_OBJECT_CLASS (klass)->finalize = oniguruma_regex_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), ONIGURUMA_REGEX_RX, g_param_spec_pointer ("rx", "rx", "rx", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void oniguruma_regex_instance_init (OnigurumaRegex * self) {
	self->priv = ONIGURUMA_REGEX_GET_PRIVATE (self);
}


static void oniguruma_regex_finalize (GObject * obj) {
	OnigurumaRegex * self;
	self = ONIGURUMA_REGEX (obj);
	(self->priv->_rx == NULL ? NULL : (self->priv->_rx = ( (self->priv->_rx), NULL)));
	G_OBJECT_CLASS (oniguruma_regex_parent_class)->finalize (obj);
}


GType oniguruma_regex_get_type (void) {
	static GType oniguruma_regex_type_id = 0;
	if (oniguruma_regex_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (OnigurumaRegexClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) oniguruma_regex_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (OnigurumaRegex), 0, (GInstanceInitFunc) oniguruma_regex_instance_init };
		oniguruma_regex_type_id = g_type_register_static (G_TYPE_OBJECT, "OnigurumaRegex", &g_define_type_info, 0);
	}
	return oniguruma_regex_type_id;
}




