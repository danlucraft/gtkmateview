
#include <glib.h>
#include <glib-object.h>
#include <gtksourceview/gtksourceview.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/arraylist.h>
#include <gee/hashmap.h>
#include <gee/collection.h>


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

#define GTK_MATE_TYPE_GRAMMAR (gtk_mate_grammar_get_type ())
#define GTK_MATE_GRAMMAR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammar))
#define GTK_MATE_GRAMMAR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammarClass))
#define GTK_MATE_IS_GRAMMAR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_GRAMMAR))
#define GTK_MATE_IS_GRAMMAR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_GRAMMAR))
#define GTK_MATE_GRAMMAR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_GRAMMAR, GtkMateGrammarClass))

typedef struct _GtkMateGrammar GtkMateGrammar;
typedef struct _GtkMateGrammarClass GtkMateGrammarClass;

#define GTK_MATE_TYPE_BUNDLE (gtk_mate_bundle_get_type ())
#define GTK_MATE_BUNDLE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_BUNDLE, GtkMateBundle))
#define GTK_MATE_BUNDLE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_BUNDLE, GtkMateBundleClass))
#define GTK_MATE_IS_BUNDLE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_BUNDLE))
#define GTK_MATE_IS_BUNDLE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_BUNDLE))
#define GTK_MATE_BUNDLE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_BUNDLE, GtkMateBundleClass))

typedef struct _GtkMateBundle GtkMateBundle;
typedef struct _GtkMateBundleClass GtkMateBundleClass;
typedef struct _GtkMateBundlePrivate GtkMateBundlePrivate;

#define GTK_MATE_TYPE_THEME (gtk_mate_theme_get_type ())
#define GTK_MATE_THEME(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_THEME, GtkMateTheme))
#define GTK_MATE_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_THEME, GtkMateThemeClass))
#define GTK_MATE_IS_THEME(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_THEME))
#define GTK_MATE_IS_THEME_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_THEME))
#define GTK_MATE_THEME_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_THEME, GtkMateThemeClass))

typedef struct _GtkMateTheme GtkMateTheme;
typedef struct _GtkMateThemeClass GtkMateThemeClass;

#define GTK_MATE_TYPE_COLOURER (gtk_mate_colourer_get_type ())
#define GTK_MATE_COLOURER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_COLOURER, GtkMateColourer))
#define GTK_MATE_COLOURER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_COLOURER, GtkMateColourerClass))
#define GTK_MATE_IS_COLOURER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_COLOURER))
#define GTK_MATE_IS_COLOURER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_COLOURER))
#define GTK_MATE_COLOURER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_COLOURER, GtkMateColourerClass))

typedef struct _GtkMateColourer GtkMateColourer;
typedef struct _GtkMateColourerClass GtkMateColourerClass;

#define GTK_MATE_TYPE_SCOPE (gtk_mate_scope_get_type ())
#define GTK_MATE_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_SCOPE, GtkMateScope))
#define GTK_MATE_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_SCOPE, GtkMateScopeClass))
#define GTK_MATE_IS_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_SCOPE))
#define GTK_MATE_IS_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_SCOPE))
#define GTK_MATE_SCOPE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_SCOPE, GtkMateScopeClass))

typedef struct _GtkMateScope GtkMateScope;
typedef struct _GtkMateScopeClass GtkMateScopeClass;
typedef struct _GtkMateParserPrivate GtkMateParserPrivate;

#define TYPE_RANGE_SET (range_set_get_type ())
#define RANGE_SET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_RANGE_SET, RangeSet))
#define RANGE_SET_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_RANGE_SET, RangeSetClass))
#define IS_RANGE_SET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_RANGE_SET))
#define IS_RANGE_SET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_RANGE_SET))
#define RANGE_SET_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_RANGE_SET, RangeSetClass))

typedef struct _RangeSet RangeSet;
typedef struct _RangeSetClass RangeSetClass;
typedef struct _GtkMateGrammarPrivate GtkMateGrammarPrivate;

#define ONIG_TYPE_RX (onig_rx_get_type ())
#define ONIG_RX(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIG_TYPE_RX, OnigRx))
#define ONIG_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIG_TYPE_RX, OnigRxClass))
#define ONIG_IS_RX(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIG_TYPE_RX))
#define ONIG_IS_RX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIG_TYPE_RX))
#define ONIG_RX_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIG_TYPE_RX, OnigRxClass))

typedef struct _OnigRx OnigRx;
typedef struct _OnigRxClass OnigRxClass;

#define GTK_MATE_TYPE_PATTERN (gtk_mate_pattern_get_type ())
#define GTK_MATE_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_MATE_TYPE_PATTERN, GtkMatePattern))
#define GTK_MATE_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_MATE_TYPE_PATTERN, GtkMatePatternClass))
#define GTK_MATE_IS_PATTERN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_MATE_TYPE_PATTERN))
#define GTK_MATE_IS_PATTERN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_MATE_TYPE_PATTERN))
#define GTK_MATE_PATTERN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_MATE_TYPE_PATTERN, GtkMatePatternClass))

typedef struct _GtkMatePattern GtkMatePattern;
typedef struct _GtkMatePatternClass GtkMatePatternClass;

#define ONIG_TYPE_MATCH (onig_match_get_type ())
#define ONIG_MATCH(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ONIG_TYPE_MATCH, OnigMatch))
#define ONIG_MATCH_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), ONIG_TYPE_MATCH, OnigMatchClass))
#define ONIG_IS_MATCH(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ONIG_TYPE_MATCH))
#define ONIG_IS_MATCH_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), ONIG_TYPE_MATCH))
#define ONIG_MATCH_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), ONIG_TYPE_MATCH, OnigMatchClass))

typedef struct _OnigMatch OnigMatch;
typedef struct _OnigMatchClass OnigMatchClass;

struct _GtkMateBuffer {
	GtkSourceBuffer parent_instance;
	GtkMateBufferPrivate * priv;
	GtkMateParser* parser;
};

struct _GtkMateBufferClass {
	GtkSourceBufferClass parent_class;
};

struct _GtkMateBundle {
	GtkObject parent_instance;
	GtkMateBundlePrivate * priv;
	GeeArrayList* grammars;
};

struct _GtkMateBundleClass {
	GtkObjectClass parent_class;
};

struct _GtkMateParser {
	GtkObject parent_instance;
	GtkMateParserPrivate * priv;
	GtkMateScope* root;
	gint deactivation_level;
	GtkTextTag* dummy_tag;
	GtkTextTag* dummy_tag2;
	GSequence* tags;
	RangeSet* changes;
	gint parsed_upto;
	gint last_visible_line;
	gboolean always_parse_all;
};

struct _GtkMateParserClass {
	GtkObjectClass parent_class;
};

struct _GtkMateGrammar {
	GtkObject parent_instance;
	GtkMateGrammarPrivate * priv;
	char** file_types;
	gint file_types_length1;
	OnigRx* first_line_match;
	char* key_equivalent;
	char* scope_name;
	char* comment;
	GeeArrayList* all_patterns;
	OnigRx* folding_start_marker;
	OnigRx* folding_stop_marker;
	GeeArrayList* patterns;
	GeeHashMap* repository;
	gboolean loaded;
};

struct _GtkMateGrammarClass {
	GtkObjectClass parent_class;
};



GType gtk_mate_buffer_get_type (void);
GType gtk_mate_parser_get_type (void);
enum  {
	GTK_MATE_BUFFER_DUMMY_PROPERTY
};
extern GeeArrayList* gtk_mate_buffer_bundles;
GeeArrayList* gtk_mate_buffer_bundles = NULL;
extern GeeArrayList* gtk_mate_buffer_themes;
GeeArrayList* gtk_mate_buffer_themes = NULL;
GType gtk_mate_grammar_get_type (void);
GtkMateGrammar* gtk_mate_parser_get_grammar (GtkMateParser* self);
const char* gtk_mate_grammar_get_name (GtkMateGrammar* self);
GType gtk_mate_bundle_get_type (void);
GType gtk_mate_theme_get_type (void);
GType gtk_mate_colourer_get_type (void);
GtkMateColourer* gtk_mate_parser_get_colourer (GtkMateParser* self);
GtkMateTheme* gtk_mate_colourer_get_theme (GtkMateColourer* self);
GType gtk_mate_scope_get_type (void);
void gtk_mate_colourer_uncolour_scope (GtkMateColourer* self, GtkMateScope* scope, gboolean recurse);
GType range_set_get_type (void);
void gtk_mate_parser_close (GtkMateParser* self);
GtkMateParser* gtk_mate_parser_create (GtkMateGrammar* grammar, GtkMateBuffer* buffer);
void gtk_mate_parser_last_visible_line_changed (GtkMateParser* self, gint new_last_visible_line);
void gtk_mate_parser_change_theme (GtkMateParser* self, GtkMateTheme* theme);
gboolean gtk_mate_buffer_set_grammar_by_name (GtkMateBuffer* self, const char* name);
GType onig_rx_get_type (void);
GType gtk_mate_pattern_get_type (void);
char* gtk_mate_buffer_set_grammar_by_filename (GtkMateBuffer* self, const char* filename);
GType onig_match_get_type (void);
OnigMatch* onig_rx_search (OnigRx* self, const char* target, gint start, gint end);
char* gtk_mate_buffer_set_grammar_by_first_line (GtkMateBuffer* self, const char* first_line);
GtkTextIter gtk_mate_buffer_iter_ (GtkMateBuffer* self, gint offset);
GtkTextIter gtk_mate_buffer_start_iter (GtkMateBuffer* self);
GtkTextIter gtk_mate_buffer_end_iter (GtkMateBuffer* self);
GtkTextMark* gtk_mate_buffer_cursor_mark (GtkMateBuffer* self);
GtkTextIter gtk_mate_buffer_cursor_iter (GtkMateBuffer* self);
GtkTextIter gtk_mate_buffer_iter_from_mark (GtkMateBuffer* self, GtkTextMark* mark);
GtkTextIter gtk_mate_buffer_iter_at_line_offset (GtkMateBuffer* self, gint line, gint line_offset);
GtkTextIter gtk_mate_buffer_iter_at_line_index (GtkMateBuffer* self, gint line, gint line_offset);
GtkTextIter gtk_mate_buffer_line_start_iter (GtkMateBuffer* self, gint line);
GtkTextIter gtk_mate_buffer_line_end_iter (GtkMateBuffer* self, gint line);
GtkTextIter gtk_mate_buffer_line_end_iter1 (GtkMateBuffer* self, gint line);
GtkTextMark* gtk_mate_buffer_start_mark (GtkMateBuffer* self);
GtkTextMark* gtk_mate_buffer_end_mark (GtkMateBuffer* self);
GtkTextMark* gtk_mate_buffer_selection_mark (GtkMateBuffer* self);
char* gtk_mate_buffer_get_line (GtkMateBuffer* self, gint line);
char* gtk_mate_buffer_get_line1 (GtkMateBuffer* self, gint line_ix);
gint gtk_mate_buffer_get_line_length (GtkMateBuffer* self, gint line);
gint gtk_mate_buffer_cursor_line (GtkMateBuffer* self);
gint gtk_mate_buffer_cursor_line_offset (GtkMateBuffer* self);
gint gtk_mate_buffer_cursor_offset (GtkMateBuffer* self);
GtkMateScope* gtk_mate_scope_scope_at (GtkMateScope* self, gint line, gint line_offset);
GtkTextIter gtk_mate_scope_start_iter (GtkMateScope* self);
GtkTextIter gtk_mate_scope_end_iter (GtkMateScope* self);
void gtk_mate_buffer_select_current_scope (GtkMateBuffer* self);
GeeArrayList* gtk_mate_buffer_current_scope_range (GtkMateBuffer* self);
GtkMateBuffer* gtk_mate_buffer_new (void);
GtkMateBuffer* gtk_mate_buffer_construct (GType object_type);
GtkMateBuffer* gtk_mate_buffer_new (void);
gint gtk_mate_load_bundles (void);
void gtk_mate_load_themes (void);
static GObject * gtk_mate_buffer_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer gtk_mate_buffer_parent_class = NULL;
static void gtk_mate_buffer_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



/* Sets the grammar explicitly by name.*/
gboolean gtk_mate_buffer_set_grammar_by_name (GtkMateBuffer* self, const char* name) {
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (name != NULL, FALSE);
	_tmp0_ = FALSE;
	if (self->parser != NULL) {
		_tmp0_ = _vala_strcmp0 (gtk_mate_grammar_get_name (gtk_mate_parser_get_grammar (self->parser)), name) == 0;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		return TRUE;
	}
	{
		GeeIterator* _bundle_it;
		_bundle_it = gee_iterable_iterator ((GeeIterable*) gtk_mate_buffer_bundles);
		while (gee_iterator_next (_bundle_it)) {
			GtkMateBundle* bundle;
			bundle = (GtkMateBundle*) gee_iterator_get (_bundle_it);
			{
				GeeIterator* _gr_it;
				_gr_it = gee_iterable_iterator ((GeeIterable*) bundle->grammars);
				while (gee_iterator_next (_gr_it)) {
					GtkMateGrammar* gr;
					gr = (GtkMateGrammar*) gee_iterator_get (_gr_it);
					if (_vala_strcmp0 (gtk_mate_grammar_get_name (gr), name) == 0) {
						gint parsed_upto;
						GtkMateTheme* theme;
						GtkMateParser* _tmp4_;
						gboolean _tmp5_;
						parsed_upto = 150;
						theme = NULL;
						if (self->parser != NULL) {
							GtkMateTheme* _tmp3_;
							GtkMateTheme* _tmp2_;
							_tmp3_ = NULL;
							_tmp2_ = NULL;
							theme = (_tmp3_ = (_tmp2_ = gtk_mate_colourer_get_theme (gtk_mate_parser_get_colourer (self->parser)), (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (theme == NULL) ? NULL : (theme = (g_object_unref (theme), NULL)), _tmp3_);
							gtk_mate_colourer_uncolour_scope (gtk_mate_parser_get_colourer (self->parser), self->parser->root, TRUE);
							parsed_upto = self->parser->parsed_upto;
							gtk_mate_parser_close (self->parser);
						}
						_tmp4_ = NULL;
						self->parser = (_tmp4_ = gtk_mate_parser_create (gr, self), (self->parser == NULL) ? NULL : (self->parser = (g_object_unref (self->parser), NULL)), _tmp4_);
						gtk_mate_parser_last_visible_line_changed (self->parser, parsed_upto);
						g_signal_emit_by_name (self, "grammar_changed", gtk_mate_grammar_get_name (gr), NULL);
						if (theme != NULL) {
							gtk_mate_parser_change_theme (self->parser, theme);
						}
						return (_tmp5_ = TRUE, (theme == NULL) ? NULL : (theme = (g_object_unref (theme), NULL)), (gr == NULL) ? NULL : (gr = (g_object_unref (gr), NULL)), (_gr_it == NULL) ? NULL : (_gr_it = (g_object_unref (_gr_it), NULL)), (bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL)), (_bundle_it == NULL) ? NULL : (_bundle_it = (g_object_unref (_bundle_it), NULL)), _tmp5_);
					}
					(gr == NULL) ? NULL : (gr = (g_object_unref (gr), NULL));
				}
				(_gr_it == NULL) ? NULL : (_gr_it = (g_object_unref (_gr_it), NULL));
			}
			(bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL));
		}
		(_bundle_it == NULL) ? NULL : (_bundle_it = (g_object_unref (_bundle_it), NULL));
	}
	return FALSE;
}


static glong string_get_length (const char* self) {
	g_return_val_if_fail (self != NULL, 0L);
	return g_utf8_strlen (self, -1);
}


/* Sets the grammar by the file extension. If unable to find
 a grammar, sets the grammar to null. Returns the grammar
 name or null.*/
char* gtk_mate_buffer_set_grammar_by_filename (GtkMateBuffer* self, const char* filename) {
	char* best_name;
	glong best_length;
	char* _tmp7_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (filename != NULL, NULL);
	best_name = NULL;
	best_length = (glong) 0;
	{
		GeeIterator* _bundle_it;
		_bundle_it = gee_iterable_iterator ((GeeIterable*) gtk_mate_buffer_bundles);
		while (gee_iterator_next (_bundle_it)) {
			GtkMateBundle* bundle;
			bundle = (GtkMateBundle*) gee_iterator_get (_bundle_it);
			{
				GeeIterator* _gr_it;
				_gr_it = gee_iterable_iterator ((GeeIterable*) bundle->grammars);
				while (gee_iterator_next (_gr_it)) {
					GtkMateGrammar* gr;
					gr = (GtkMateGrammar*) gee_iterator_get (_gr_it);
					{
						char** ext_collection;
						int ext_collection_length1;
						int ext_it;
						ext_collection = gr->file_types;
						ext_collection_length1 = gr->file_types_length1;
						for (ext_it = 0; ext_it < gr->file_types_length1; ext_it = ext_it + 1) {
							const char* _tmp4_;
							char* ext;
							_tmp4_ = NULL;
							ext = (_tmp4_ = ext_collection[ext_it], (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_));
							{
								gboolean _tmp0_;
								_tmp0_ = FALSE;
								if (g_str_has_suffix (filename, ext)) {
									gboolean _tmp1_;
									_tmp1_ = FALSE;
									if (best_name == NULL) {
										_tmp1_ = TRUE;
									} else {
										_tmp1_ = string_get_length (ext) > best_length;
									}
									_tmp0_ = _tmp1_;
								} else {
									_tmp0_ = FALSE;
								}
								if (_tmp0_) {
									char* _tmp3_;
									const char* _tmp2_;
									_tmp3_ = NULL;
									_tmp2_ = NULL;
									best_name = (_tmp3_ = (_tmp2_ = gtk_mate_grammar_get_name (gr), (_tmp2_ == NULL) ? NULL : g_strdup (_tmp2_)), best_name = (g_free (best_name), NULL), _tmp3_);
									best_length = string_get_length (ext);
								}
								ext = (g_free (ext), NULL);
							}
						}
					}
					(gr == NULL) ? NULL : (gr = (g_object_unref (gr), NULL));
				}
				(_gr_it == NULL) ? NULL : (_gr_it = (g_object_unref (_gr_it), NULL));
			}
			(bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL));
		}
		(_bundle_it == NULL) ? NULL : (_bundle_it = (g_object_unref (_bundle_it), NULL));
	}
	if (best_name != NULL) {
		gboolean _tmp5_;
		_tmp5_ = FALSE;
		if (self->parser == NULL) {
			_tmp5_ = TRUE;
		} else {
			_tmp5_ = _vala_strcmp0 (gtk_mate_grammar_get_name (gtk_mate_parser_get_grammar (self->parser)), best_name) != 0;
		}
		if (_tmp5_) {
			gtk_mate_buffer_set_grammar_by_name (self, best_name);
		}
		return best_name;
	}
	_tmp7_ = NULL;
	return (_tmp7_ = NULL, best_name = (g_free (best_name), NULL), _tmp7_);
}


/* Sets the grammar by examining the first line. If unable to find
 a grammar, sets the grammar to null. Returns the grammar
 name or null.*/
char* gtk_mate_buffer_set_grammar_by_first_line (GtkMateBuffer* self, const char* first_line) {
	OnigRx* re;
	char* _tmp6_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (first_line != NULL, NULL);
	re = NULL;
	{
		GeeIterator* _bundle_it;
		_bundle_it = gee_iterable_iterator ((GeeIterable*) gtk_mate_buffer_bundles);
		while (gee_iterator_next (_bundle_it)) {
			GtkMateBundle* bundle;
			bundle = (GtkMateBundle*) gee_iterator_get (_bundle_it);
			{
				GeeIterator* _gr_it;
				_gr_it = gee_iterable_iterator ((GeeIterable*) bundle->grammars);
				while (gee_iterator_next (_gr_it)) {
					GtkMateGrammar* gr;
					OnigRx* _tmp1_;
					OnigRx* _tmp0_;
					gr = (GtkMateGrammar*) gee_iterator_get (_gr_it);
					_tmp1_ = NULL;
					_tmp0_ = NULL;
					if ((re = (_tmp1_ = (_tmp0_ = gr->first_line_match, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (re == NULL) ? NULL : (re = (g_object_unref (re), NULL)), _tmp1_)) != NULL) {
						OnigMatch* _tmp2_;
						gboolean _tmp3_;
						_tmp2_ = NULL;
						if ((_tmp3_ = (_tmp2_ = onig_rx_search (re, first_line, 0, (gint) strlen (first_line))) != NULL, (_tmp2_ == NULL) ? NULL : (_tmp2_ = (g_object_unref (_tmp2_), NULL)), _tmp3_)) {
							const char* _tmp4_;
							char* _tmp5_;
							gtk_mate_buffer_set_grammar_by_name (self, gtk_mate_grammar_get_name (gr));
							_tmp4_ = NULL;
							_tmp5_ = NULL;
							return (_tmp5_ = (_tmp4_ = gtk_mate_grammar_get_name (gr), (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_)), (gr == NULL) ? NULL : (gr = (g_object_unref (gr), NULL)), (_gr_it == NULL) ? NULL : (_gr_it = (g_object_unref (_gr_it), NULL)), (bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL)), (_bundle_it == NULL) ? NULL : (_bundle_it = (g_object_unref (_bundle_it), NULL)), (re == NULL) ? NULL : (re = (g_object_unref (re), NULL)), _tmp5_);
						}
					}
					(gr == NULL) ? NULL : (gr = (g_object_unref (gr), NULL));
				}
				(_gr_it == NULL) ? NULL : (_gr_it = (g_object_unref (_gr_it), NULL));
			}
			(bundle == NULL) ? NULL : (bundle = (g_object_unref (bundle), NULL));
		}
		(_bundle_it == NULL) ? NULL : (_bundle_it = (g_object_unref (_bundle_it), NULL));
	}
	_tmp6_ = NULL;
	return (_tmp6_ = NULL, (re == NULL) ? NULL : (re = (g_object_unref (re), NULL)), _tmp6_);
}


/* HELPER METHODS
 Offset from start of document -> Iter*/
GtkTextIter gtk_mate_buffer_iter_ (GtkMateBuffer* self, gint offset) {
	GtkTextIter i = {0};
	gtk_text_buffer_get_iter_at_offset ((GtkTextBuffer*) self, &i, offset);
	return i;
}


GtkTextIter gtk_mate_buffer_start_iter (GtkMateBuffer* self) {
	GtkTextIter i = {0};
	gtk_text_buffer_get_iter_at_offset ((GtkTextBuffer*) self, &i, 0);
	return i;
}


GtkTextIter gtk_mate_buffer_end_iter (GtkMateBuffer* self) {
	GtkTextIter i = {0};
	gtk_text_buffer_get_iter_at_offset ((GtkTextBuffer*) self, &i, gtk_text_buffer_get_char_count ((GtkTextBuffer*) self));
	return i;
}


GtkTextIter gtk_mate_buffer_cursor_iter (GtkMateBuffer* self) {
	GtkTextIter i = {0};
	GtkTextMark* _tmp0_;
	_tmp0_ = NULL;
	gtk_text_buffer_get_iter_at_mark ((GtkTextBuffer*) self, &i, _tmp0_ = gtk_mate_buffer_cursor_mark (self));
	(_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_object_unref (_tmp0_), NULL));
	return i;
}


GtkTextIter gtk_mate_buffer_iter_from_mark (GtkMateBuffer* self, GtkTextMark* mark) {
	GtkTextIter i = {0};
	gtk_text_buffer_get_iter_at_mark ((GtkTextBuffer*) self, &i, mark);
	return i;
}


GtkTextIter gtk_mate_buffer_iter_at_line_offset (GtkMateBuffer* self, gint line, gint line_offset) {
	GtkTextIter i = {0};
	gtk_text_buffer_get_iter_at_line_offset ((GtkTextBuffer*) self, &i, line, line_offset);
	return i;
}


GtkTextIter gtk_mate_buffer_iter_at_line_index (GtkMateBuffer* self, gint line, gint line_offset) {
	GtkTextIter i = {0};
	gtk_text_buffer_get_iter_at_line_index ((GtkTextBuffer*) self, &i, line, line_offset);
	return i;
}


GtkTextIter gtk_mate_buffer_line_start_iter (GtkMateBuffer* self, gint line) {
	GtkTextIter i = {0};
	gtk_text_buffer_get_iter_at_line ((GtkTextBuffer*) self, &i, line);
	return i;
}


/* Iter at end of line, after the "\n" (if present).*/
GtkTextIter gtk_mate_buffer_line_end_iter (GtkMateBuffer* self, gint line) {
	if (line >= (gtk_text_buffer_get_line_count ((GtkTextBuffer*) self) - 1)) {
		return gtk_mate_buffer_end_iter (self);
	} else {
		return gtk_mate_buffer_line_start_iter (self, line + 1);
	}
}


/* Iter at end of line, before the "\n" (if present).*/
GtkTextIter gtk_mate_buffer_line_end_iter1 (GtkMateBuffer* self, gint line) {
	if (line >= (gtk_text_buffer_get_line_count ((GtkTextBuffer*) self) - 1)) {
		return gtk_mate_buffer_end_iter (self);
	} else {
		GtkTextIter i;
		i = gtk_mate_buffer_line_start_iter (self, line + 1);
		gtk_text_iter_backward_char (&i);
		return i;
	}
}


GtkTextMark* gtk_mate_buffer_start_mark (GtkMateBuffer* self) {
	GtkTextMark* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = NULL;
	return (_tmp0_ = gtk_text_buffer_get_mark ((GtkTextBuffer*) self, "start_mark"), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
}


GtkTextMark* gtk_mate_buffer_end_mark (GtkMateBuffer* self) {
	GtkTextMark* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = NULL;
	return (_tmp0_ = gtk_text_buffer_get_mark ((GtkTextBuffer*) self, "end_mark"), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
}


GtkTextMark* gtk_mate_buffer_cursor_mark (GtkMateBuffer* self) {
	GtkTextMark* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = NULL;
	return (_tmp0_ = gtk_text_buffer_get_mark ((GtkTextBuffer*) self, "insert"), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
}


GtkTextMark* gtk_mate_buffer_selection_mark (GtkMateBuffer* self) {
	GtkTextMark* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = NULL;
	return (_tmp0_ = gtk_text_buffer_get_mark ((GtkTextBuffer*) self, "selection_bound"), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
}


/* Get text of line, including the "\n" if present. Returns null if line 
 does not exist.*/
char* gtk_mate_buffer_get_line (GtkMateBuffer* self, gint line) {
	GtkTextIter ei = {0};
	const char* _tmp3_;
	GtkTextIter _tmp2_ = {0};
	g_return_val_if_fail (self != NULL, NULL);
	if (line == (gtk_text_buffer_get_line_count ((GtkTextBuffer*) self) - 1)) {
		ei = gtk_mate_buffer_end_iter (self);
	} else {
		gboolean _tmp0_;
		_tmp0_ = FALSE;
		if (line > (gtk_text_buffer_get_line_count ((GtkTextBuffer*) self) - 1)) {
			_tmp0_ = TRUE;
		} else {
			_tmp0_ = line < 0;
		}
		if (_tmp0_) {
			return NULL;
		} else {
			ei = gtk_mate_buffer_line_start_iter (self, line + 1);
		}
	}
	_tmp3_ = NULL;
	return (_tmp3_ = gtk_text_buffer_get_slice ((GtkTextBuffer*) self, (_tmp2_ = gtk_mate_buffer_line_start_iter (self, line), &_tmp2_), &ei, TRUE), (_tmp3_ == NULL) ? NULL : g_strdup (_tmp3_));
}


static char* string_substring (const char* self, glong offset, glong len) {
	glong string_length;
	const char* start;
	g_return_val_if_fail (self != NULL, NULL);
	string_length = g_utf8_strlen (self, -1);
	if (offset < 0) {
		offset = string_length + offset;
		g_return_val_if_fail (offset >= 0, NULL);
	} else {
		g_return_val_if_fail (offset <= string_length, NULL);
	}
	if (len < 0) {
		len = string_length - offset;
	}
	g_return_val_if_fail ((offset + len) <= string_length, NULL);
	start = g_utf8_offset_to_pointer (self, offset);
	return g_strndup (start, ((gchar*) g_utf8_offset_to_pointer (start, len)) - ((gchar*) start));
}


/* Get text of line, not including the "\n". Returns null if line
 does not exist.*/
char* gtk_mate_buffer_get_line1 (GtkMateBuffer* self, gint line_ix) {
	char* line;
	char* _tmp0_;
	char* _tmp3_;
	g_return_val_if_fail (self != NULL, NULL);
	line = NULL;
	_tmp0_ = NULL;
	if ((line = (_tmp0_ = gtk_mate_buffer_get_line (self, line_ix), line = (g_free (line), NULL), _tmp0_)) != NULL) {
		if (line_ix == (gtk_text_buffer_get_line_count ((GtkTextBuffer*) self) - 1)) {
			return line;
		} else {
			char* _tmp2_;
			_tmp2_ = NULL;
			return (_tmp2_ = string_substring (line, (glong) 0, string_get_length (line) - 1), line = (g_free (line), NULL), _tmp2_);
		}
	}
	_tmp3_ = NULL;
	return (_tmp3_ = NULL, line = (g_free (line), NULL), _tmp3_);
}


gint gtk_mate_buffer_get_line_length (GtkMateBuffer* self, gint line) {
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = FALSE;
	if (line >= gtk_text_buffer_get_line_count ((GtkTextBuffer*) self)) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = line < 0;
	}
	if (_tmp0_) {
		return -1;
	}
	if (line == (gtk_text_buffer_get_line_count ((GtkTextBuffer*) self) - 1)) {
		GtkTextIter _tmp3_ = {0};
		GtkTextIter _tmp2_ = {0};
		return gtk_text_iter_get_offset ((_tmp2_ = gtk_mate_buffer_end_iter (self), &_tmp2_)) - gtk_text_iter_get_offset ((_tmp3_ = gtk_mate_buffer_line_start_iter (self, line), &_tmp3_));
	} else {
		GtkTextIter _tmp6_ = {0};
		GtkTextIter _tmp5_ = {0};
		return (gtk_text_iter_get_offset ((_tmp5_ = gtk_mate_buffer_line_end_iter (self, line), &_tmp5_)) - gtk_text_iter_get_offset ((_tmp6_ = gtk_mate_buffer_line_start_iter (self, line), &_tmp6_))) - 1;
	}
}


gint gtk_mate_buffer_cursor_line (GtkMateBuffer* self) {
	GtkTextIter _tmp0_ = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_line ((_tmp0_ = gtk_mate_buffer_cursor_iter (self), &_tmp0_));
}


gint gtk_mate_buffer_cursor_line_offset (GtkMateBuffer* self) {
	GtkTextIter _tmp0_ = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_line_offset ((_tmp0_ = gtk_mate_buffer_cursor_iter (self), &_tmp0_));
}


gint gtk_mate_buffer_cursor_offset (GtkMateBuffer* self) {
	GtkTextIter _tmp0_ = {0};
	g_return_val_if_fail (self != NULL, 0);
	return gtk_text_iter_get_offset ((_tmp0_ = gtk_mate_buffer_cursor_iter (self), &_tmp0_));
}


void gtk_mate_buffer_select_current_scope (GtkMateBuffer* self) {
	GtkTextIter _tmp1_ = {0};
	GtkTextIter _tmp0_ = {0};
	GtkMateScope* current_scope;
	GtkTextIter start_iter;
	GtkTextIter end_iter;
	GtkTextMark* _tmp2_;
	GtkTextMark* _tmp3_;
	g_return_if_fail (self != NULL);
	current_scope = gtk_mate_scope_scope_at (self->parser->root, gtk_text_iter_get_line ((_tmp0_ = gtk_mate_buffer_cursor_iter (self), &_tmp0_)), gtk_text_iter_get_line_offset ((_tmp1_ = gtk_mate_buffer_cursor_iter (self), &_tmp1_)));
	start_iter = gtk_mate_scope_start_iter (current_scope);
	end_iter = gtk_mate_scope_end_iter (current_scope);
	_tmp2_ = NULL;
	gtk_text_buffer_move_mark ((GtkTextBuffer*) self, _tmp2_ = gtk_mate_buffer_selection_mark (self), &start_iter);
	(_tmp2_ == NULL) ? NULL : (_tmp2_ = (g_object_unref (_tmp2_), NULL));
	_tmp3_ = NULL;
	gtk_text_buffer_move_mark ((GtkTextBuffer*) self, _tmp3_ = gtk_mate_buffer_cursor_mark (self), &end_iter);
	(_tmp3_ == NULL) ? NULL : (_tmp3_ = (g_object_unref (_tmp3_), NULL));
	(current_scope == NULL) ? NULL : (current_scope = (g_object_unref (current_scope), NULL));
}


GeeArrayList* gtk_mate_buffer_current_scope_range (GtkMateBuffer* self) {
	GtkTextIter _tmp1_ = {0};
	GtkTextIter _tmp0_ = {0};
	GtkMateScope* current_scope;
	GtkTextIter start_iter;
	GtkTextIter end_iter;
	GeeArrayList* range;
	GeeArrayList* _tmp2_;
	g_return_val_if_fail (self != NULL, NULL);
	current_scope = gtk_mate_scope_scope_at (self->parser->root, gtk_text_iter_get_line ((_tmp0_ = gtk_mate_buffer_cursor_iter (self), &_tmp0_)), gtk_text_iter_get_line_offset ((_tmp1_ = gtk_mate_buffer_cursor_iter (self), &_tmp1_)));
	start_iter = gtk_mate_scope_start_iter (current_scope);
	end_iter = gtk_mate_scope_end_iter (current_scope);
	range = gee_array_list_new (G_TYPE_INT, NULL, NULL, g_direct_equal);
	gee_collection_add ((GeeCollection*) range, GINT_TO_POINTER (gtk_text_iter_get_offset (&start_iter)));
	gee_collection_add ((GeeCollection*) range, GINT_TO_POINTER (gtk_text_iter_get_offset (&end_iter)));
	_tmp2_ = NULL;
	return (_tmp2_ = range, (current_scope == NULL) ? NULL : (current_scope = (g_object_unref (current_scope), NULL)), _tmp2_);
}


GtkMateBuffer* gtk_mate_buffer_construct (GType object_type) {
	GtkMateBuffer * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


GtkMateBuffer* gtk_mate_buffer_new (void) {
	return gtk_mate_buffer_construct (GTK_MATE_TYPE_BUFFER);
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
		gtk_mate_load_themes ();
	}
	return obj;
}


static void gtk_mate_buffer_class_init (GtkMateBufferClass * klass) {
	gtk_mate_buffer_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = gtk_mate_buffer_constructor;
	G_OBJECT_CLASS (klass)->finalize = gtk_mate_buffer_finalize;
	g_signal_new ("grammar_changed", GTK_MATE_TYPE_BUFFER, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__STRING, G_TYPE_NONE, 1, G_TYPE_STRING);
}


static void gtk_mate_buffer_instance_init (GtkMateBuffer * self) {
}


static void gtk_mate_buffer_finalize (GObject* obj) {
	GtkMateBuffer * self;
	self = GTK_MATE_BUFFER (obj);
	(self->parser == NULL) ? NULL : (self->parser = (g_object_unref (self->parser), NULL));
	G_OBJECT_CLASS (gtk_mate_buffer_parent_class)->finalize (obj);
}


GType gtk_mate_buffer_get_type (void) {
	static GType gtk_mate_buffer_type_id = 0;
	if (gtk_mate_buffer_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateBufferClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_buffer_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateBuffer), 0, (GInstanceInitFunc) gtk_mate_buffer_instance_init, NULL };
		gtk_mate_buffer_type_id = g_type_register_static (GTK_TYPE_SOURCE_BUFFER, "GtkMateBuffer", &g_define_type_info, 0);
	}
	return gtk_mate_buffer_type_id;
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




