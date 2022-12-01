#include "ruby.h"
#include <libstemmer.h>
#include "stemmer.h"

static VALUE mLibstemmer;
static VALUE cStemmer;
static VALUE eStemmerError;

typedef struct stemmer_t {
    struct sb_stemmer *stemmer;
} stemmer_t;

static const rb_data_type_t stemmer_data_type_t = {
    .wrap_struct_name = "Libstemmer::Stemmer",
    .function = {
        .dmark = NULL,
        .dfree = &stemmer_free,
        .dsize = &stemmer_memsize,
    },
    .data = NULL,
};

static VALUE
stemmer_alloc(VALUE self) {
    stemmer_t *data = ALLOC(stemmer_t);
    data->stemmer = NULL;

    return TypedData_Wrap_Struct(self, &stemmer_data_type_t, data);
}

static void
stemmer_free(void *ptr) {
    stemmer_t *data = (stemmer_t *)ptr;

    sb_stemmer_delete(data->stemmer);
    free(data);
}

static size_t
stemmer_memsize(const void *ptr) {
    stemmer_t *data = (stemmer_t *)ptr;

    return sizeof(data) + sizeof(data->stemmer);
}

/*
 * Document-method: initialize
 * call-seq: Libstemmer::Stemmer.new
 *
 * Creates a new Stemmer for a given <tt>:language</tt>. By default, a Stemmer
 * will be for English.
 *
 *   require "libstemmer"
 *   stemmer = Libstemmer::Stemmer.new(lang: "jp")
 */
static VALUE
stemmer_initialize(int argc, VALUE *argv, VALUE self) {
    struct stemmer_t *data;
    static ID keyword_ids[1];
    char encoding[] = "UTF_8";
    VALUE args[1] = {Qundef};
    VALUE kwargs;

    if (!keyword_ids[0]) { keyword_ids[0] = rb_intern("lang"); }

    TypedData_Get_Struct(self, stemmer_t, &stemmer_data_type_t, data);

    if (data) sb_stemmer_delete(data->stemmer);

    rb_scan_args(argc, argv, "0:", &kwargs);
    rb_get_kwargs(kwargs, keyword_ids, 0, 1, args);

    if (args[0] == Qundef) { args[0] = rb_str_new2("english"); }

    data->stemmer = sb_stemmer_new(RSTRING_PTR(args[0]), encoding);

    if (!data->stemmer) {
        rb_raise(
            eStemmerError,
            "Language `%s' not available for stemming",
            RSTRING_PTR(args[0])
        );
    }

    return self;
}

/*
 * Document-method: stem_word
 * call-seq: stemmer.stem_word(word) -> string
 *
 * Stems a <tt>word</tt>.
 *
 *   require "libstemmer"
 *   stemmer = Libstemmer::Stemmer.new
 *   stemmer.stem_word("dancing") #=> "danc"
 */
static VALUE
stemmer_stem_word(VALUE self, VALUE word) {
    struct stemmer_t *data;

    if (!RB_TYPE_P(word, T_STRING)) {
        rb_raise(
            rb_eArgError,
            "Argument `word' must be a String"
        );
    }

    TypedData_Get_Struct(self, stemmer_t, &stemmer_data_type_t, data);

    if (!data->stemmer) { rb_raise(eStemmerError, "Stemmer is not initialized"); }

    const sb_symbol *stemmed = sb_stemmer_stem(
        data->stemmer,
        (sb_symbol *)RSTRING_PTR(word),
        (int) RSTRING_LEN(word)
    );

    return rb_str_new2((char *) stemmed);
}

void Init_stemmer(void)
{
    mLibstemmer = rb_define_module("Libstemmer");
    rb_define_const(mLibstemmer, "SO_VERSION", rb_str_new2("2.2.0"));

    cStemmer = rb_define_class_under(mLibstemmer, "Stemmer", rb_cObject);
    rb_define_alloc_func(cStemmer, &stemmer_alloc);
    rb_define_method(cStemmer, "initialize", &stemmer_initialize, -1);
    rb_define_method(cStemmer, "stem_word", &stemmer_stem_word, 1);

    eStemmerError = rb_define_class_under(mLibstemmer, "StemmerError", rb_eStandardError);
}
