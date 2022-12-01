# typed: true
# frozen_string_literal: true

require "test_helper"

module Libstemmer
  class StemmerTest < Minitest::Test
    def test_stemming_an_english_word
      stemmer = Stemmer.new(lang: "english")

      assert_equal("walk", stemmer.stem_word("walking"))
    end

    def test_incorrect_argument_raises_argument_error
      stemmer = Stemmer.new(lang: "english")

      assert_raises(ArgumentError, "Argument `word' must be a String") do
        stemmer.stem_word(:walking)
      end
    end

    def test_stemming_a_blank_string
      stemmer = Stemmer.new(lang: "english")

      assert_equal("", stemmer.stem_word(""))
    end
  end
end
