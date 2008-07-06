
#ifndef __ONIG_TEST_H__
#define __ONIG_TEST_H__

#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>

G_BEGIN_DECLS


#define TYPE_ONIG_TEST (onig_test_get_type ())
#define ONIG_TEST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_ONIG_TEST, OnigTest))
#define ONIG_TEST_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_ONIG_TEST, OnigTestClass))
#define IS_ONIG_TEST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_ONIG_TEST))
#define IS_ONIG_TEST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_ONIG_TEST))
#define ONIG_TEST_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_ONIG_TEST, OnigTestClass))

typedef struct _OnigTest OnigTest;
typedef struct _OnigTestClass OnigTestClass;
typedef struct _OnigTestPrivate OnigTestPrivate;

/* oniguruma test
 valac -o onig_test onig_test.vala --save-temps --vapidir=./../vapi/ --pkg=oniguruma --Xcc="-lonig"*/
struct _OnigTest {
	GObject parent_instance;
	OnigTestPrivate * priv;
};

struct _OnigTestClass {
	GObjectClass parent_class;
};


void onig_test_main (char** args, int args_length1);
void onig_test_search (const char* str_pattern, const char* str_target);
gint onig_test_strlen (gchar* str);
OnigTest* onig_test_new (void);
GType onig_test_get_type (void);


G_END_DECLS

#endif
