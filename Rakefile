require "bundler/gem_tasks"
require "rspec/core/rake_task"

RSpec::Core::RakeTask.new(:spec)

require "rake/extensiontask"

task :build => :compile

Rake::ExtensionTask.new("normal_distribution") do |ext|
  ext.lib_dir = "lib/normal_distribution"
end

task :default => [:clobber, :compile, :spec]

require "yard"

YARD_FILES = Dir["lib/**/*.rb", "ext/**/*.rb"]

YARD::Rake::YardocTask.new do |t|
  t.files   = YARD_FILES   # optional
  t.options = %w(-o doc --readme README.md) # optional
end
