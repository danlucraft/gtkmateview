
#include <glib.h>
#include <glib-object.h>
#include <gtksourceview/gtksourceview.h>
#include <gee/arraylist.h>
#include <gtk/gtk.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <stdlib.h>
#include <string.h>
#include <gee/hashmap.h>
#include <gdk/gdk.h>


#define GTK_MATE_TYPE_VIEW (gtk_mate_view_get_type ())
#define GTK_MATE_VIEW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_VIEW, GtkMateView))
#define GTK_MATE_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_VIEW, GtkMateViewClass))
#define GTK_MATE_IS_VIEW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_VIEW))
#define GTK_MATE_IS_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_VIEW))
#define GTK_MATE_VIEW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_VIEW, GtkMateViewClass))

typedef struct _GtkMateView GtkMateView;
typedef struct _GtkMateViewClass GtkMateViewClass;
typedef struct _GtkMateViewPrivate GtkMateViewPrivate;

#define GTK_MATE_TYPE_THEME (gtk_mate_theme_get_type ())
#define GTK_MATE_THEME(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_THEME, GtkMateTheme))
#define GTK_MATE_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_THEME, GtkMateThemeClass))
#define GTK_MATE_IS_THEME(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_THEME))
#define GTK_MATE_IS_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_THEME))
#define GTK_MATE_THEME_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_THEME, GtkMateThemeClass))

typedef struct _GtkMateTheme GtkMateTheme;
typedef struct _GtkMateThemeClass GtkMateThemeClass;
typedef struct _GtkMateThemePrivate GtkMateThemePrivate;

#define GTK_MATE_TYPE_THEME_SETTING (gtk_mate_theme_setting_get_type ())
#define GTK_MATE_THEME_SETTING(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSetting))
#define GTK_MATE_THEME_SETTING_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSettingClass))
#define GTK_MATE_IS_THEME_SETTING(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_THEME_SETTING))
#define GTK_MATE_IS_THEME_SETTING_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_THEME_SETTING))
#define GTK_MATE_THEME_SETTING_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_THEME_SETTING, GtkMateThemeSettingClass))

typedef struct _GtkMateThemeSetting GtkMateThemeSetting;
typedef struct _GtkMateThemeSettingClass GtkMateThemeSettingClass;

#define GTK_MATE_TYPE_BUFFER (gtk_mate_buffer_get_type ())
#define GTK_MATE_BUFFER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_BUFFER, GtkMateBuffer))
#define GTK_MATE_BUFFER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_BUFFER, GtkMateBufferClass))
#define GTK_MATE_IS_BUFFER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_BUFFER))
#define GTK_MATE_IS_BUFFER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_BUFFER))
#define GTK_MATE_BUFFER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_BUFFER, GtkMateBufferClass))

typedef struct _GtkMateBuffer GtkMateBuffer;
typedef struct _GtkMateBufferClass GtkMateBufferClass;
typedef struct _GtkMateBufferPrivate GtkMateBufferPrivate;

#define GTK_MATE_TYPE_PARSER (gtk_mate_parser_get_type ())
#define GTK_MATE_PARSER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_PARSER, GtkMateParser))
#define GTK_MATE_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_PARSER, GtkMateParserClass))
#define GTK_MATE_IS_PARSER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_PARSER))
#define GTK_MATE_IS_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_PARSER))
#define GTK_MATE_PARSER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_PARSER, GtkMateParserClass))

typedef struct _GtkMateParser GtkMateParser;
typedef struct _GtkMateParserClass GtkMateParserClass;

#define GTK_MATE_TYPE_COLOURER (gtk_mate_colourer_get_type ())
#define GTK_MATE_COLOURER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_COLOURER, GtkMateColourer))
#define GTK_MATE_COLOURER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_COLOURER, GtkMateColourerClass))
#define GTK_MATE_IS_COLOURER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_COLOURER))
#define GTK_MATE_IS_COLOURER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_COLOURER))
#define GTK_MATE_COLOURER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_COLOURER, GtkMateColourerClass))

typedef struct _GtkMateColourer GtkMateColourer;
typedef struct _GtkMateColourerClass GtkMateColourerClass;

struct _GtkMateView {
	GtkSourceView parent_instance;
	GtkMateViewPrivate * priv;
};

struct _GtkMateViewClass {
	GtkSourceViewClass parent_class;
};

struct _GtkMateTheme {
	GtkObject parent_instance;
	GtkMateThemePrivate * priv;
	char* author;
	char* name;
	GeeHashMap* global_settings;
	GeeArrayList* settings;
	gboolean is_initialized;
	GeeHashMap* cached_setting_for_scopes;
};

struct _GtkMateThemeClass {
	GtkObjectClass parent_class;
};

struct _GtkMateBuffer {
	GtkSourceBuffer parent_instance;
	GtkMateBufferPrivate * priv;
	GtkMateParser* parser;
};

struct _GtkMateBufferClass {
	GtkSourceBufferClass parent_class;
};



GType gtk_mate_view_get_type (void);
enum  {
	GTK_MATE_VIEW_DUMMY_PROPERTY
};
GType gtk_mate_theme_get_type (void);
GeeArrayList* gtk_mate_theme_themes (void);
GType gtk_mate_theme_setting_get_type (void);
void gtk_mate_theme_init_for_use (GtkMateTheme* self);
GType gtk_mate_buffer_get_type (void);
GType gtk_mate_parser_get_type (void);
void gtk_mate_parser_change_theme (GtkMateParser* self, GtkMateTheme* theme);
void gtk_mate_view_set_global_theme_settings (GtkMateView* self);
gboolean gtk_mate_view_set_theme_by_name (GtkMateView* self, const char* name);
GType gtk_mate_colourer_get_type (void);
GtkMateColourer* gtk_mate_parser_get_colourer (GtkMateParser* self);
void gtk_mate_colourer_set_global_settings (GtkMateColourer* self, GtkMateView* view);
GtkMateParser* gtk_mate_view_get_parser (GtkMateView* self);
void gtk_mate_parser_last_visible_line_changed (GtkMateParser* self, gint new_last_visible_line);
gint gtk_mate_view_last_visible_line (GtkMateView* self);
void gtk_mate_view_value_changed_handler (GtkMateView* self);
gint gtk_mate_view_first_visible_line (GtkMateView* self);
GtkMateView* gtk_mate_view_new (void);
GtkMateView* gtk_mate_view_construct (GType object_type);
GtkMateView* gtk_mate_view_new (void);
static gpointer gtk_mate_view_parent_class = NULL;
static int _vala_strcmp0 (const char * str1, const char * str2);



gboolean gtk_mate_view_set_theme_by_name (GtkMateView* self, const char* name) {
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (name != NULL, FALSE);
	{
		GeeArrayList* _tmp0_;
		GeeIterator* _tmp1_;
		GeeIterator* _theme_it;
		_tmp0_ = NULL;
		_tmp1_ = NULL;
		_theme_it = (_tmp1_ = gee_iterable_iterator ((GeeIterable*) (_tmp0_ = gtk_mate_theme_themes ())), (_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_object_unref (_tmp0_), NULL)), _tmp1_);
		while (gee_iterator_next (_theme_it)) {
			GtkMateTheme* theme;
			theme = (GtkMateTheme*) gee_iterator_get (_theme_it);
			if (_vala_strcmp0 (theme->name, name) == 0) {
				gboolean _tmp2_;
				gtk_mate_theme_init_for_use (theme);
				gtk_mate_parser_change_theme (GTK_MATE_BUFFER (gtk_text_view_get_buffer ((GtkTextView*) self))->parser, theme);
				gtk_mate_view_set_global_theme_settings (self);
				return (_tmp2_ = TRUE, (theme == NULL) ? NULL : (theme = (g_object_unref (theme), NULL)), (_theme_it == NULL) ? NULL : (_theme_it = (g_object_unref (_theme_it), NULL)), _tmp2_);
			}
			(theme == NULL) ? NULL : (theme = (g_object_unref (theme), NULL));
		}
		(_theme_it == NULL) ? NULL : (_theme_it = (g_object_unref (_theme_it), NULL));
	}
	return FALSE;
}


void gtk_mate_view_set_global_theme_settings (GtkMateView* self) {
	gboolean _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp0_ = FALSE;
	if (GTK_MATE_BUFFER (gtk_text_view_get_buffer ((GtkTextView*) self))->parser != NULL) {
		_tmp0_ = gtk_mate_parser_get_colourer (GTK_MATE_BUFFER (gtk_text_view_get_buffer ((GtkTextView*) self))->parser) != NULL;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		gtk_mate_colourer_set_global_settings (gtk_mate_parser_get_colourer (GTK_MATE_BUFFER (gtk_text_view_get_buffer ((GtkTextView*) self))->parser), self);
	}
}


/* TODO finish this off once Vala gets signal_connect_after support
 public void connect_signals() {
 stdout.printf("mateview connect_signals\n");
 this.parent_set += (prev_parent) => {
 if (this.get_parent() is Gtk.ScrolledWindow) {
 stdout.printf("parent is scrolled window\n");
 }
 };
 }*/
void gtk_mate_view_value_changed_handler (GtkMateView* self) {
	GtkMateParser* parser;
	g_return_if_fail (self != NULL);
	parser = gtk_mate_view_get_parser (self);
	if (parser != NULL) {
		gtk_mate_parser_last_visible_line_changed (parser, gtk_mate_view_last_visible_line (self));
	}
	(parser == NULL) ? NULL : (parser = (g_object_unref (parser), NULL));
}


GtkMateParser* gtk_mate_view_get_parser (GtkMateView* self) {
	GtkMateParser* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = NULL;
	return (_tmp0_ = GTK_MATE_BUFFER (gtk_text_view_get_buffer ((GtkTextView*) self))->parser, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
}


gint gtk_mate_view_first_visible_line (GtkMateView* self) {
	GdkRectangle rect = {0};
	gint bufy;
	GtkTextIter iter = {0};
	gint line;
	g_return_val_if_fail (self != NULL, 0);
	gtk_text_view_get_visible_rect ((GtkTextView*) self, &rect);
	bufy = rect.y;
	gtk_text_view_get_line_at_y ((GtkTextView*) self, &iter, bufy, NULL);
	line = gtk_text_iter_get_line (&iter);
	return line;
}


gint gtk_mate_view_last_visible_line (GtkMateView* self) {
	GdkRectangle rect = {0};
	gint bufy;
	GtkTextIter iter = {0};
	gint line;
	g_return_val_if_fail (self != NULL, 0);
	gtk_text_view_get_visible_rect ((GtkTextView*) self, &rect);
	bufy = rect.y + rect.height;
	gtk_text_view_get_line_at_y ((GtkTextView*) self, &iter, bufy, NULL);
	line = gtk_text_iter_get_line (&iter);
	return line;
}


GtkMateView* gtk_mate_view_construct (GType object_type) {
	GtkMateView * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


GtkMateView* gtk_mate_view_new (void) {
	return gtk_mate_view_construct (GTK_MATE_TYPE_VIEW);
}


static void gtk_mate_view_class_init (GtkMateViewClass * klass) {
	gtk_mate_view_parent_class = g_type_class_peek_parent (klass);
}


static void gtk_mate_view_instance_init (GtkMateView * self) {
}


GType gtk_mate_view_get_type (void) {
	static GType gtk_mate_view_type_id = 0;
	if (gtk_mate_view_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateViewClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_view_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateView), 0, (GInstanceInitFunc) gtk_mate_view_instance_init, NULL };
		gtk_mate_view_type_id = g_type_register_static (GTK_TYPE_SOURCE_VIEW, "GtkMateView", &g_define_type_info, 0);
	}
	return gtk_mate_view_type_id;
}


static int _vala_strcmp0 (const char * str1, const char * str2) {
	if (str1 == NULL) {
		return -(str1 != str2);
	}
	if (str2 == NULL) {
		return str1 != str2;
	}
	return strcmp (str1, str2);
}




