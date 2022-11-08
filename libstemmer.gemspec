# frozen_string_literal: true

require_relative "lib/libstemmer/version"

Gem::Specification.new do |spec|
  spec.name = "libstemmer"
  spec.version = Libstemmer::VERSION
  spec.authors = ["Michael Herold"]
  spec.email = ["opensource@michaeljherold.com"]

  spec.summary = "Ruby bindings for Porter's Snowball stemming algorithms"
  spec.description = spec.summary
  spec.homepage = "https://github.com/michaelherold/libstemmer-ruby"
  spec.license = "MIT"
  spec.required_ruby_version = ">= 3.0.0"

  spec.metadata["homepage_uri"] = spec.homepage
  spec.metadata["source_code_uri"] = spec.homepage
  spec.metadata["changelog_uri"] = "https://github.com/michaelherold/libstemmer-ruby/blob/main/CHANGELOG.md"

  spec.files = ["CHANGELOG.md", "CONTRIBUTING.md", "LICENSE.md", "README.md", "libstemmer.gemspec"]
  spec.files += Dir["lib/**/*.rb"]
  spec.require_paths = ["lib"]

  spec.add_development_dependency("bundler")
end
