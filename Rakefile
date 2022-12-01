# frozen_string_literal: true

require "bundler/gem_tasks"
require "rake/extensiontask"
require "rake/testtask"

Rake::TestTask.new(:test) do |t|
  t.libs << "test"
  t.libs << "lib"
  t.test_files = FileList["test/**/test_*.rb"]
end

Rake::ExtensionTask.new("stemmer") do |ext|
  File.join("vendor", "libstemmer_c", "include")
    .then { |relative_include| File.expand_path(relative_include, __dir__) }
    .then { |vendor_include| ext.config_includes << vendor_include }

  ext.cross_compile = true
  ext.cross_platform = ["x86_64-linux", "x86_64-darwin", "arm64-darwin"]
  ext.ext_dir = "ext/libstemmer"
  ext.lib_dir = "lib/libstemmer"
end

namespace :compile do
  desc "Compiles the libstemmer object file"
  task :libstemmer do
    require "open3"
    Open3.popen3("make libstemmer.a", chdir: "vendor/libstemmer_c")
  end
end

Rake::Task["compile:stemmer"].enhance(["compile:libstemmer"])
Rake::Task["test"].enhance(["compile:stemmer"])

task default: :test
