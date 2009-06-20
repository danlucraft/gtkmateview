require 'rubygems'
require 'fileutils'
require 'yaml'
require 'spec/rake/spectask'

VALA_SOURCES = Dir["lib/*.vala"].map {|n| n =~ /lib\/(.*)\.vala/; $1}

def fix_vala_c_sources
  Dir.glob('*.{c,h}').each do |srcname|
    source = File.read("#{srcname}")
    VALA_SOURCES.each do |srcname2|
      source.gsub!("#include <#{srcname2}.h>", "#include \"#{srcname2}.h\"")
    end
    File.open("#{srcname}", "w") do |f| 
      f.puts source
    end
  end
end


namespace :build do
  desc "Clean the build directories prior to a new build"
  task :clean do
    puts "cleaning..."
    FileUtils.rm Dir.glob("lib/*.{o,h,c,so}")
    FileUtils.rm Dir.glob("dist/*.{o,h,c,so}")
  end

  desc "build c files from vala"
  task :build_c do
    puts "Getting to ./lib"
    FileUtils.cd("lib") do
      puts "compiling gtkmateview..."
      if Dir.glob('*.vala').empty?
        puts "No vala files detected. Nothing to do."
      else
        puts "running valac"
        sh "valac -C --library gtkmateview --pkg gtksourceview-2.0 --pkg libxml-2.0 --pkg gee-1.0 --pkg gtksourceview-2.0 --vapidir=./../vapi/ --pkg=oniguruma *.vala"
        fix_vala_c_sources
      end
    end
    Dir.glob('lib/*.{h,c}').each do |file|
      unless %x{md5sum #{file}}.split(" ").first == %x{md5sum dist/#{file.split("/").last}}.split(" ").first
        puts "changed #{file}"
        FileUtils.cp("#{file}", "dist/")
      end
      FileUtils.rm_f("#{file}")  
    end
  end
  
  desc "build project from scratch"
  task :all => [:build_c] do
    puts 'Building ruby extension'
    FileUtils.cd("lib") do
      puts "running VALAR..."
      sh "ruby ../../valar/bin/valar gtkmateview.vapi --deps=\"gtk+-2.0,oniguruma,gtksourceview-2.0\" --vapidirs=../vapi/oniguruma.vapi"
    end
    FileUtils.mv("lib/gtkmateview_rb.c", "dist/", :force => true, :verbose => true)
    FileUtils.cd("dist") do
      puts 
      puts "compiling gtkmateview_rb..."
      sh "ruby extconf.rb"
      sh "make"
    end
  end
end
  
Spec::Rake::SpecTask.new do |t|
  t.spec_opts = ["-c"]#, "-f s"]
end

