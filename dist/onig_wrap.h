
#ifndef __ONIG_WRAP_H__
#define __ONIG_WRAP_H__

#include <glib.h>
#include <glib-object.h>
#include <oniguruma.h>
#include <stdlib.h>
#include <string.h>

G_BEGIN_DECLS


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
};

struct _OnigMatchClass {
	GObjectClass parent_class;
};

struct _OnigRx {
	GObject parent_instance;
	OnigRxPrivate * priv;
	gboolean matches_start_of_line;
};

struct _OnigRxClass {
	GObjectClass parent_class;
};


OnigOnigError* onig_onig_error_new (void);
GType onig_onig_error_get_type (void);
extern gint onig_match_count;
gint onig_match_num_captures (OnigMatch* self);
gint onig_match_begin (OnigMatch* self, gint capture);
gint onig_match_end (OnigMatch* self, gint capture);
OnigMatch* onig_match_new (void);
regex_t* onig_match_get_rx (OnigMatch* self);
void onig_match_set_rx (OnigMatch* self, regex_t* value);
OnigRegion* onig_match_get_rg (OnigMatch* self);
void onig_match_set_rg (OnigMatch* self, OnigRegion* value);
GType onig_match_get_type (void);
OnigMatch* onig_rx_search (OnigRx* self, const char* target, gint start, gint end);
OnigRx* onig_rx_make (const char* pattern, OnigOptionType* options, OnigOnigError** error);
OnigRx* onig_rx_make1 (const char* pattern);
OnigRx* onig_rx_new (void);
regex_t* onig_rx_get_rx (OnigRx* self);
void onig_rx_set_rx (OnigRx* self, regex_t* value);
GType onig_rx_get_type (void);


G_END_DECLS

#endif
