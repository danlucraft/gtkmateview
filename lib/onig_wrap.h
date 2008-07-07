
#ifndef __ONIG_WRAP_H__
#define __ONIG_WRAP_H__

#include <glib.h>
#include <glib-object.h>
#include <oniguruma.h>
#include <stdlib.h>
#include <string.h>

G_BEGIN_DECLS


#define ONIGURUMA_TYPE_ONIG_ERROR (oniguruma_onig_error_get_type ())
#define ONIGURUMA_ONIG_ERROR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIGURUMA_TYPE_ONIG_ERROR, OnigurumaOnigError))
#define ONIGURUMA_ONIG_ERROR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIGURUMA_TYPE_ONIG_ERROR, OnigurumaOnigErrorClass))
#define ONIGURUMA_IS_ONIG_ERROR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIGURUMA_TYPE_ONIG_ERROR))
#define ONIGURUMA_IS_ONIG_ERROR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIGURUMA_TYPE_ONIG_ERROR))
#define ONIGURUMA_ONIG_ERROR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIGURUMA_TYPE_ONIG_ERROR, OnigurumaOnigErrorClass))

typedef struct _OnigurumaOnigError OnigurumaOnigError;
typedef struct _OnigurumaOnigErrorClass OnigurumaOnigErrorClass;
typedef struct _OnigurumaOnigErrorPrivate OnigurumaOnigErrorPrivate;

#define ONIGURUMA_TYPE_MATCH (oniguruma_match_get_type ())
#define ONIGURUMA_MATCH(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIGURUMA_TYPE_MATCH, OnigurumaMatch))
#define ONIGURUMA_MATCH_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIGURUMA_TYPE_MATCH, OnigurumaMatchClass))
#define ONIGURUMA_IS_MATCH(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIGURUMA_TYPE_MATCH))
#define ONIGURUMA_IS_MATCH_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIGURUMA_TYPE_MATCH))
#define ONIGURUMA_MATCH_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIGURUMA_TYPE_MATCH, OnigurumaMatchClass))

typedef struct _OnigurumaMatch OnigurumaMatch;
typedef struct _OnigurumaMatchClass OnigurumaMatchClass;
typedef struct _OnigurumaMatchPrivate OnigurumaMatchPrivate;

#define ONIGURUMA_TYPE_REGEX (oniguruma_regex_get_type ())
#define ONIGURUMA_REGEX(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIGURUMA_TYPE_REGEX, OnigurumaRegex))
#define ONIGURUMA_REGEX_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIGURUMA_TYPE_REGEX, OnigurumaRegexClass))
#define ONIGURUMA_IS_REGEX(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIGURUMA_TYPE_REGEX))
#define ONIGURUMA_IS_REGEX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIGURUMA_TYPE_REGEX))
#define ONIGURUMA_REGEX_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIGURUMA_TYPE_REGEX, OnigurumaRegexClass))

typedef struct _OnigurumaRegex OnigurumaRegex;
typedef struct _OnigurumaRegexClass OnigurumaRegexClass;
typedef struct _OnigurumaRegexPrivate OnigurumaRegexPrivate;

struct _OnigurumaOnigError {
	GObject parent_instance;
	OnigurumaOnigErrorPrivate * priv;
	gint code;
	OnigErrorInfo error_info;
};

struct _OnigurumaOnigErrorClass {
	GObjectClass parent_class;
};

struct _OnigurumaMatch {
	GObject parent_instance;
	OnigurumaMatchPrivate * priv;
};

struct _OnigurumaMatchClass {
	GObjectClass parent_class;
};

struct _OnigurumaRegex {
	GObject parent_instance;
	OnigurumaRegexPrivate * priv;
};

struct _OnigurumaRegexClass {
	GObjectClass parent_class;
};


OnigurumaOnigError* oniguruma_onig_error_new (void);
GType oniguruma_onig_error_get_type (void);
gint oniguruma_match_begin (OnigurumaMatch* self, gint capture);
gint oniguruma_match_end (OnigurumaMatch* self, gint capture);
OnigurumaMatch* oniguruma_match_new (void);
regex_t* oniguruma_match_get_rx (OnigurumaMatch* self);
void oniguruma_match_set_rx (OnigurumaMatch* self, regex_t* value);
OnigRegion* oniguruma_match_get_rg (OnigurumaMatch* self);
void oniguruma_match_set_rg (OnigurumaMatch* self, OnigRegion* value);
GType oniguruma_match_get_type (void);
OnigurumaMatch* oniguruma_regex_search (OnigurumaRegex* self, const char* target, gint start, gint end);
OnigurumaRegex* oniguruma_regex_make (const char* pattern, OnigOptionType* options, OnigurumaOnigError** error);
OnigurumaRegex* oniguruma_regex_make1 (const char* pattern);
OnigurumaRegex* oniguruma_regex_new (void);
regex_t* oniguruma_regex_get_rx (OnigurumaRegex* self);
void oniguruma_regex_set_rx (OnigurumaRegex* self, regex_t* value);
GType oniguruma_regex_get_type (void);


G_END_DECLS

#endif
