
#include <glib.h>
#include <glib-object.h>
#include <oniguruma.h>
#include <stdlib.h>
#include <string.h>


#define ONIG_TYPE_ONIG_ERROR (onig_onig_error_get_type ())
#define ONIG_ONIG_ERROR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIG_TYPE_ONIG_ERROR, OnigOnigError))
#define ONIG_ONIG_ERROR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIG_TYPE_ONIG_ERROR, OnigOnigErrorClass))
#define ONIG_IS_ONIG_ERROR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIG_TYPE_ONIG_ERROR))
#define ONIG_IS_ONIG_ERROR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIG_TYPE_ONIG_ERROR))
#define ONIG_ONIG_ERROR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIG_TYPE_ONIG_ERROR, OnigOnigErrorClass))

typedef struct _OnigOnigError OnigOnigError;
typedef struct _OnigOnigErrorClass OnigOnigErrorClass;
typedef struct _OnigOnigErrorPrivate OnigOnigErrorPrivate;

#define ONIG_TYPE_MATCH (onig_match_get_type ())
#define ONIG_MATCH(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIG_TYPE_MATCH, OnigMatch))
#define ONIG_MATCH_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIG_TYPE_MATCH, OnigMatchClass))
#define ONIG_IS_MATCH(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIG_TYPE_MATCH))
#define ONIG_IS_MATCH_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIG_TYPE_MATCH))
#define ONIG_MATCH_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIG_TYPE_MATCH, OnigMatchClass))

typedef struct _OnigMatch OnigMatch;
typedef struct _OnigMatchClass OnigMatchClass;
typedef struct _OnigMatchPrivate OnigMatchPrivate;

#define ONIG_TYPE_RX (onig_rx_get_type ())
#define ONIG_RX(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIG_TYPE_RX, OnigRx))
#define ONIG_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIG_TYPE_RX, OnigRxClass))
#define ONIG_IS_RX(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIG_TYPE_RX))
#define ONIG_IS_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIG_TYPE_RX))
#define ONIG_RX_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIG_TYPE_RX, OnigRxClass))

typedef struct _OnigRx OnigRx;
typedef struct _OnigRxClass OnigRxClass;
typedef struct _OnigRxPrivate OnigRxPrivate;

struct _OnigOnigError {
	GObject parent_instance;
	OnigOnigErrorPrivate * priv;
	gint code;
	OnigErrorInfo error_info;
};

struct _OnigOnigErrorClass {
	GObjectClass parent_class;
};

struct _OnigMatch {
	GObject parent_instance;
	OnigMatchPrivate * priv;
	char* text;
};

struct _OnigMatchClass {
	GObjectClass parent_class;
};

struct _OnigMatchPrivate {
	regex_t* _rx;
	OnigRegion* _rg;
};

struct _OnigRx {
	GObject parent_instance;
	OnigRxPrivate * priv;
	gboolean matches_start_of_line;
};

struct _OnigRxClass {
	GObjectClass parent_class;
};

struct _OnigRxPrivate {
	regex_t* _rx;
};



GType onig_onig_error_get_type (void);
enum  {
	ONIG_ONIG_ERROR_DUMMY_PROPERTY
};
OnigOnigError* onig_onig_error_new (void);
OnigOnigError* onig_onig_error_construct (GType object_type);
OnigOnigError* onig_onig_error_new (void);
static gpointer onig_onig_error_parent_class = NULL;
static void onig_onig_error_finalize (GObject* obj);
GType onig_match_get_type (void);
#define ONIG_MATCH_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), ONIG_TYPE_MATCH, OnigMatchPrivate))
enum  {
	ONIG_MATCH_DUMMY_PROPERTY,
	ONIG_MATCH_RX,
	ONIG_MATCH_RG
};
extern gint onig_match_count;
gint onig_match_count = 0;
OnigRegion* onig_match_get_rg (OnigMatch* self);
gint onig_match_num_captures (OnigMatch* self);
gint onig_match_begin (OnigMatch* self, gint capture);
gint onig_match_end (OnigMatch* self, gint capture);
OnigMatch* onig_match_new (void);
OnigMatch* onig_match_construct (GType object_type);
OnigMatch* onig_match_new (void);
regex_t* onig_match_get_rx (OnigMatch* self);
void onig_match_set_rx (OnigMatch* self, regex_t* value);
void onig_match_set_rg (OnigMatch* self, OnigRegion* value);
static GObject * onig_match_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer onig_match_parent_class = NULL;
static void onig_match_finalize (GObject* obj);
static void onig_match_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void onig_match_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
GType onig_rx_get_type (void);
#define ONIG_RX_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), ONIG_TYPE_RX, OnigRxPrivate))
enum  {
	ONIG_RX_DUMMY_PROPERTY,
	ONIG_RX_RX
};
regex_t* onig_rx_get_rx (OnigRx* self);
OnigMatch* onig_rx_search (OnigRx* self, const char* target, gint start, gint end);
OnigRx* onig_rx_new (void);
OnigRx* onig_rx_construct (GType object_type);
void onig_rx_set_rx (OnigRx* self, regex_t* value);
OnigRx* onig_rx_make (const char* pattern, OnigOptionType* options, OnigOnigError** _error_);
OnigRx* onig_rx_make1 (const char* pattern);
OnigRx* onig_rx_new (void);
static gpointer onig_rx_parent_class = NULL;
static void onig_rx_finalize (GObject* obj);
static void onig_rx_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void onig_rx_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);



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
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = FALSE;
	if (capture >= self->priv->_rg->num_regs) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = capture < 0;
	}
	if (_tmp0_) {
		return -1;
	}
	return self->priv->_rg->beg[capture];
}


gint onig_match_end (OnigMatch* self, gint capture) {
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = FALSE;
	if (capture >= self->priv->_rg->num_regs) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = capture < 0;
	}
	if (_tmp0_) {
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
	self->text = (g_free (self->text), NULL);
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


OnigMatch* onig_rx_search (OnigRx* self, const char* target, gint start, gint end) {
	OnigRegion* rg;
	gchar* ctarget;
	gint r;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (target != NULL, NULL);
	rg = onig_region_new ();
	ctarget = (gchar*) target;
	r = onig_search (self->priv->_rx, ctarget, ctarget + strlen (target), ctarget + start, ctarget + end, rg, (OnigOptionType*) ONIG_OPTION_NONE);
	if (r < 0) {
		return NULL;
	} else {
		OnigMatch* md;
		char* _tmp2_;
		const char* _tmp1_;
		md = onig_match_new ();
		onig_match_set_rg (md, rg);
		onig_match_set_rx (md, self->priv->_rx);
		_tmp2_ = NULL;
		_tmp1_ = NULL;
		md->text = (_tmp2_ = (_tmp1_ = target, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), md->text = (g_free (md->text), NULL), _tmp2_);
		return md;
	}
}


OnigRx* onig_rx_make (const char* pattern, OnigOptionType* options, OnigOnigError** _error_) {
	OnigRx* rx;
	gchar* c_pattern;
	regex_t* rx1;
	OnigErrorInfo _tmp0_ = {0};
	OnigErrorInfo err_info;
	gint r;
	g_return_val_if_fail (pattern != NULL, NULL);
	*_error_ = NULL;
	rx = onig_rx_new ();
	c_pattern = (gchar*) pattern;
	rx1 = NULL;
	err_info = (memset (&_tmp0_, 0, sizeof (OnigErrorInfo)), _tmp0_);
	r = onig_new (&rx1, c_pattern, c_pattern + strlen (pattern), options, (OnigEncoding**) ONIG_ENCODING_UTF8, ONIG_SYNTAX_DEFAULT, &err_info);
	rx->matches_start_of_line = g_str_has_prefix (pattern, "^");
	if (r < 0) {
		OnigOnigError* _tmp1_;
		OnigRx* _tmp2_;
		_tmp1_ = NULL;
		(*_error_) = (_tmp1_ = onig_onig_error_new (), ((*_error_) == NULL) ? NULL : ((*_error_) = (g_object_unref ((*_error_)), NULL)), _tmp1_);
		(*_error_)->code = r;
		(*_error_)->error_info = err_info;
		_tmp2_ = NULL;
		return (_tmp2_ = NULL, (rx == NULL) ? NULL : (rx = (g_object_unref (rx), NULL)), _tmp2_);
	}
	onig_rx_set_rx (rx, rx1);
	return rx;
}


OnigRx* onig_rx_make1 (const char* pattern) {
	OnigOnigError* e;
	OnigOnigError* _tmp2_;
	OnigRx* _tmp1_;
	OnigOnigError* _tmp0_;
	OnigRx* _tmp3_;
	g_return_val_if_fail (pattern != NULL, NULL);
	e = NULL;
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp3_ = NULL;
	return (_tmp3_ = (_tmp1_ = onig_rx_make (pattern, (OnigOptionType*) ONIG_OPTION_MULTILINE, &_tmp0_), e = (_tmp2_ = _tmp0_, (e == NULL) ? NULL : (e = (g_object_unref (e), NULL)), _tmp2_), _tmp1_), (e == NULL) ? NULL : (e = (g_object_unref (e), NULL)), _tmp3_);
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




