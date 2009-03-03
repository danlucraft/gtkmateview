
#include "onig_wrap.h"
#include <string.h>




enum  {
	ONIG_ONIG_ERROR_DUMMY_PROPERTY
};
static gpointer onig_onig_error_parent_class = NULL;
static void onig_onig_error_finalize (GObject* obj);
struct _OnigMatchPrivate {
	regex_t* _rx;
	OnigRegion* _rg;
};

#define ONIG_MATCH_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), ONIG_TYPE_MATCH, OnigMatchPrivate))
enum  {
	ONIG_MATCH_DUMMY_PROPERTY,
	ONIG_MATCH_RX,
	ONIG_MATCH_RG
};
gint onig_match_count = 0;
static GObject * onig_match_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer onig_match_parent_class = NULL;
static void onig_match_finalize (GObject* obj);
struct _OnigRxPrivate {
	regex_t* _rx;
};

#define ONIG_RX_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), ONIG_TYPE_RX, OnigRxPrivate))
enum  {
	ONIG_RX_DUMMY_PROPERTY,
	ONIG_RX_RX
};
static gpointer onig_rx_parent_class = NULL;
static void onig_rx_finalize (GObject* obj);



OnigOnigError* onig_onig_error_construct (GType object_type) {
	OnigOnigError * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


OnigOnigError* onig_onig_error_new (void) {
	return onig_onig_error_construct (ONIG_TYPE_ONIG_ERROR);
}


static void onig_onig_error_class_init (OnigOnigErrorClass * klass) {
	onig_onig_error_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = onig_onig_error_finalize;
}


static void onig_onig_error_instance_init (OnigOnigError * self) {
}


static void onig_onig_error_finalize (GObject* obj) {
	OnigOnigError * self;
	self = ONIG_ONIG_ERROR (obj);
	G_OBJECT_CLASS (onig_onig_error_parent_class)->finalize (obj);
}


GType onig_onig_error_get_type (void) {
	static GType onig_onig_error_type_id = 0;
	if (onig_onig_error_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (OnigOnigErrorClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) onig_onig_error_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (OnigOnigError), 0, (GInstanceInitFunc) onig_onig_error_instance_init, NULL };
		onig_onig_error_type_id = g_type_register_static (G_TYPE_OBJECT, "OnigOnigError", &g_define_type_info, 0);
	}
	return onig_onig_error_type_id;
}


gint onig_match_num_captures (OnigMatch* self) {
	g_return_val_if_fail (self != NULL, 0);
	return self->priv->_rg->num_regs;
}


gint onig_match_begin (OnigMatch* self, gint capture) {
	gboolean _tmp0;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0 = FALSE;
	if (capture >= self->priv->_rg->num_regs) {
		_tmp0 = TRUE;
	} else {
		_tmp0 = capture < 0;
	}
	if (_tmp0) {
		return -1;
	}
	return self->priv->_rg->beg[capture];
}


gint onig_match_end (OnigMatch* self, gint capture) {
	gboolean _tmp0;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0 = FALSE;
	if (capture >= self->priv->_rg->num_regs) {
		_tmp0 = TRUE;
	} else {
		_tmp0 = capture < 0;
	}
	if (_tmp0) {
		return -1;
	}
	return self->priv->_rg->end[capture];
}


OnigMatch* onig_match_construct (GType object_type) {
	OnigMatch * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


OnigMatch* onig_match_new (void) {
	return onig_match_construct (ONIG_TYPE_MATCH);
}


regex_t* onig_match_get_rx (OnigMatch* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_rx;
}


void onig_match_set_rx (OnigMatch* self, regex_t* value) {
	g_return_if_fail (self != NULL);
	self->priv->_rx = value;
	g_object_notify ((GObject *) self, "rx");
}


OnigRegion* onig_match_get_rg (OnigMatch* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_rg;
}


void onig_match_set_rg (OnigMatch* self, OnigRegion* value) {
	g_return_if_fail (self != NULL);
	self->priv->_rg = value;
	g_object_notify ((GObject *) self, "rg");
}


static GObject * onig_match_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	OnigMatchClass * klass;
	GObjectClass * parent_class;
	OnigMatch * self;
	klass = ONIG_MATCH_CLASS (g_type_class_peek (ONIG_TYPE_MATCH));
	parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = ONIG_MATCH (obj);
	{
		onig_match_count++;
	}
	return obj;
}


static void onig_match_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	OnigMatch * self;
	gpointer boxed;
	self = ONIG_MATCH (object);
	switch (property_id) {
		case ONIG_MATCH_RX:
		oniguruma_value_set_regex_t (value, onig_match_get_rx (self));
		break;
		case ONIG_MATCH_RG:
		oniguruma_value_set_region (value, onig_match_get_rg (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void onig_match_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	OnigMatch * self;
	self = ONIG_MATCH (object);
	switch (property_id) {
		case ONIG_MATCH_RX:
		onig_match_set_rx (self, oniguruma_value_get_regex_t (value));
		break;
		case ONIG_MATCH_RG:
		onig_match_set_rg (self, oniguruma_value_get_region (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void onig_match_class_init (OnigMatchClass * klass) {
	onig_match_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (OnigMatchPrivate));
	G_OBJECT_CLASS (klass)->get_property = onig_match_get_property;
	G_OBJECT_CLASS (klass)->set_property = onig_match_set_property;
	G_OBJECT_CLASS (klass)->constructor = onig_match_constructor;
	G_OBJECT_CLASS (klass)->finalize = onig_match_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), ONIG_MATCH_RX, g_param_spec_pointer ("rx", "rx", "rx", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), ONIG_MATCH_RG, g_param_spec_pointer ("rg", "rg", "rg", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void onig_match_instance_init (OnigMatch * self) {
	self->priv = ONIG_MATCH_GET_PRIVATE (self);
}


static void onig_match_finalize (GObject* obj) {
	OnigMatch * self;
	self = ONIG_MATCH (obj);
	G_OBJECT_CLASS (onig_match_parent_class)->finalize (obj);
}


GType onig_match_get_type (void) {
	static GType onig_match_type_id = 0;
	if (onig_match_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (OnigMatchClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) onig_match_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (OnigMatch), 0, (GInstanceInitFunc) onig_match_instance_init, NULL };
		onig_match_type_id = g_type_register_static (G_TYPE_OBJECT, "OnigMatch", &g_define_type_info, 0);
	}
	return onig_match_type_id;
}


OnigMatch* onig_rx_search (OnigRx* self, const char* target, gint start, gint end) {
	OnigRegion* rg;
	gchar* ctarget;
	gint r;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (target != NULL, NULL);
	rg = onig_region_new ();
	ctarget = (gchar*) target;
	r = onig_search (self->priv->_rx, ctarget, (ctarget + strlen (target)), ctarget + start, (ctarget + end), rg, (OnigOptionType*) ONIG_OPTION_NONE);
	if (r < 0) {
		return NULL;
	} else {
		OnigMatch* md;
		md = onig_match_new ();
		onig_match_set_rg (md, rg);
		onig_match_set_rx (md, self->priv->_rx);
		return md;
	}
}


OnigRx* onig_rx_make (const char* pattern, OnigOptionType* options, OnigOnigError** error) {
	OnigRx* rx;
	gchar* c_pattern;
	regex_t* rx1;
	OnigErrorInfo _tmp0 = {0};
	OnigErrorInfo err_info;
	gint r;
	g_return_val_if_fail (pattern != NULL, NULL);
	*error = NULL;
	rx = onig_rx_new ();
	c_pattern = (gchar*) pattern;
	rx1 = NULL;
	err_info = (memset (&_tmp0, 0, sizeof (OnigErrorInfo)), _tmp0);
	r = onig_new (&rx1, c_pattern, (c_pattern + strlen (pattern)), options, (OnigEncoding*) ONIG_ENCODING_ASCII, ONIG_SYNTAX_DEFAULT, &err_info);
	rx->matches_start_of_line = g_str_has_prefix (pattern, "^");
	if (r < 0) {
		OnigOnigError* _tmp1;
		OnigRx* _tmp2;
		_tmp1 = NULL;
		(*error) = (_tmp1 = onig_onig_error_new (), ((*error) == NULL) ? NULL : ((*error) = (g_object_unref ((*error)), NULL)), _tmp1);
		(*error)->code = r;
		(*error)->error_info = err_info;
		_tmp2 = NULL;
		return (_tmp2 = NULL, (rx == NULL) ? NULL : (rx = (g_object_unref (rx), NULL)), _tmp2);
	}
	onig_rx_set_rx (rx, rx1);
	return rx;
}


OnigRx* onig_rx_make1 (const char* pattern) {
	OnigOnigError* e;
	OnigOnigError* _tmp2;
	OnigRx* _tmp1;
	OnigOnigError* _tmp0;
	OnigRx* _tmp3;
	g_return_val_if_fail (pattern != NULL, NULL);
	e = NULL;
	_tmp2 = NULL;
	_tmp1 = NULL;
	_tmp0 = NULL;
	_tmp3 = NULL;
	return (_tmp3 = (_tmp1 = onig_rx_make (pattern, (OnigOptionType*) ONIG_OPTION_MULTILINE, &_tmp0), e = (_tmp2 = _tmp0, (e == NULL) ? NULL : (e = (g_object_unref (e), NULL)), _tmp2), _tmp1), (e == NULL) ? NULL : (e = (g_object_unref (e), NULL)), _tmp3);
}


OnigRx* onig_rx_construct (GType object_type) {
	OnigRx * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


OnigRx* onig_rx_new (void) {
	return onig_rx_construct (ONIG_TYPE_RX);
}


regex_t* onig_rx_get_rx (OnigRx* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_rx;
}


void onig_rx_set_rx (OnigRx* self, regex_t* value) {
	g_return_if_fail (self != NULL);
	self->priv->_rx = value;
	g_object_notify ((GObject *) self, "rx");
}


static void onig_rx_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	OnigRx * self;
	gpointer boxed;
	self = ONIG_RX (object);
	switch (property_id) {
		case ONIG_RX_RX:
		oniguruma_value_set_regex_t (value, onig_rx_get_rx (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void onig_rx_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	OnigRx * self;
	self = ONIG_RX (object);
	switch (property_id) {
		case ONIG_RX_RX:
		onig_rx_set_rx (self, oniguruma_value_get_regex_t (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void onig_rx_class_init (OnigRxClass * klass) {
	onig_rx_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (OnigRxPrivate));
	G_OBJECT_CLASS (klass)->get_property = onig_rx_get_property;
	G_OBJECT_CLASS (klass)->set_property = onig_rx_set_property;
	G_OBJECT_CLASS (klass)->finalize = onig_rx_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), ONIG_RX_RX, g_param_spec_pointer ("rx", "rx", "rx", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void onig_rx_instance_init (OnigRx * self) {
	self->priv = ONIG_RX_GET_PRIVATE (self);
}


static void onig_rx_finalize (GObject* obj) {
	OnigRx * self;
	self = ONIG_RX (obj);
	G_OBJECT_CLASS (onig_rx_parent_class)->finalize (obj);
}


GType onig_rx_get_type (void) {
	static GType onig_rx_type_id = 0;
	if (onig_rx_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (OnigRxClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) onig_rx_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (OnigRx), 0, (GInstanceInitFunc) onig_rx_instance_init, NULL };
		onig_rx_type_id = g_type_register_static (G_TYPE_OBJECT, "OnigRx", &g_define_type_info, 0);
	}
	return onig_rx_type_id;
}




