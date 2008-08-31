
#ifndef __THEME_H__
#define __THEME_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gee/hashmap.h>
#include <gee/arraylist.h>
#include "onig_wrap.h"
#include "plist.h"

G_BEGIN_DECLS

typedef struct _GtkMateThemeSetting GtkMateThemeSetting;
typedef struct _GtkMateThemeSettingClass GtkMateThemeSettingClass;
typedef struct _GtkMateTheme GtkMateTheme;
typedef struct _GtkMateThemeClass GtkMateThemeClass;
typedef struct _GtkMateScope GtkMateScope;
typedef struct _GtkMateScopeClass GtkMateScopeClass;
typedef struct _GtkMateTextLoc GtkMateTextLoc;
typedef struct _GtkMateTextLocClass GtkMateTextLocClass;
typedef struct _GtkMateParser GtkMateParser;
typedef struct _GtkMateParserClass GtkMateParserClass;
typedef struct _GtkMateMarker GtkMateMarker;
typedef struct _GtkMateMarkerClass GtkMateMarkerClass;
typedef struct _GtkMateScanner GtkMateScanner;
typedef struct _GtkMateScannerClass GtkMateScannerClass;
typedef struct _GtkMateScannerIterator GtkMateScannerIterator;
typedef struct _GtkMateScannerIteratorClass GtkMateScannerIteratorClass;
typedef struct _GtkMateBuffer GtkMateBuffer;
typedef struct _GtkMateBufferClass GtkMateBufferClass;
typedef struct _GtkMateColourer GtkMateColourer;
typedef struct _GtkMateColourerClass GtkMateColourerClass;

#define GTK_MATE_TYPE_THEME_SETTING (gtk_mate_theme_setting_get_type ())
#define GTK_MATE_THEME_SETTING(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSetting))
#define GTK_MATE_THEME_SETTING_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSettingClass))
#define GTK_MATE_IS_THEME_SETTING(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_THEME_SETTING))
#define GTK_MATE_IS_THEME_SETTING_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_THEME_SETTING))
#define GTK_MATE_THEME_SETTING_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSettingClass))

typedef struct _GtkMateThemeSettingPrivate GtkMateThemeSettingPrivate;

#define GTK_MATE_TYPE_THEME (gtk_mate_theme_get_type ())
#define GTK_MATE_THEME(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_THEME, GtkMateTheme))
#define GTK_MATE_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_THEME, GtkMateThemeClass))
#define GTK_MATE_IS_THEME(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_THEME))
#define GTK_MATE_IS_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_THEME))
#define GTK_MATE_THEME_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_THEME, GtkMateThemeClass))

typedef struct _GtkMateThemePrivate GtkMateThemePrivate;

struct _GtkMateThemeSetting {
	GtkObject parent_instance;
	GtkMateThemeSettingPrivate * priv;
	char* name;
	char* selector;
	GeeHashMap* settings;
	OnigurumaRegex* positive_rx;
	OnigurumaRegex* negative_rx;
	gint specificity;
};

struct _GtkMateThemeSettingClass {
	GtkObjectClass parent_class;
};

struct _GtkMateTheme {
	GtkObject parent_instance;
	GtkMateThemePrivate * priv;
	char* author;
	char* name;
	GeeHashMap* global_settings;
	GeeArrayList* settings;
	gboolean is_initialized;
};

struct _GtkMateThemeClass {
	GtkObjectClass parent_class;
};


GtkMateThemeSetting* gtk_mate_theme_setting_create_from_plist (PListDict* dict);
void gtk_mate_theme_setting_compile_scope_matchers (GtkMateThemeSetting* self);
GtkMateThemeSetting* gtk_mate_theme_setting_new (void);
GType gtk_mate_theme_setting_get_type (void);
extern GeeArrayList* gtk_mate_theme_themes;
GtkMateTheme* gtk_mate_theme_create_from_plist (PListDict* dict);
void gtk_mate_theme_init_for_use (GtkMateTheme* self);
GeeArrayList* gtk_mate_theme_theme_filenames (void);
GtkMateThemeSetting* gtk_mate_theme_settings_for_scope (GtkMateTheme* self, GtkMateScope* scope, gboolean inner);
GtkMateTheme* gtk_mate_theme_new (void);
GType gtk_mate_theme_get_type (void);


G_END_DECLS

#endif
