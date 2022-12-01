# typed: true
# frozen_string_literal: true

require "mkmf"

GEM_ROOT = File.expand_path(File.join("..", ".."), __dir__)
LIBSTEMMER_C_ROOT = File.expand_path(File.join("vendor", "libstemmer_c"), GEM_ROOT)
INCLUDE = File.join(LIBSTEMMER_C_ROOT, "include")
LIBSTEMMER_OBJ = File.join(LIBSTEMMER_C_ROOT, "libstemmer.a")

append_cflags("-I#{INCLUDE}")
append_ldflags("-L#{LIBSTEMMER_C_ROOT} #{LIBSTEMMER_OBJ}")

create_makefile("stemmer")
