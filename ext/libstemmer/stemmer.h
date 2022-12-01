#ifndef STEMMER_H
#define STEMMER_H

#include "ruby.h"

static VALUE stemmer_alloc(VALUE self);
static void stemmer_free(void *ptr);
static size_t stemmer_memsize(const void *ptr);
static VALUE stemmer_initialize(int argc, VALUE *argv, VALUE self);
static VALUE stemmer_stem_word(VALUE self, VALUE word);

void Init_stemmer(void);

#endif
