
require 'rubygems'
require 'fileutils'
require 'yaml'
require 'spec/rake/spectask'

VALA_SOURCES = Dir["lib/*.vala"].map {|n| n =~ /lib\/(.*)\.vala/; $1}

def fix_vala_c_file(name)
  c_src = File.read("#{name}.c")
  c_src.gsub!("#include <#{name}.h>", "#include \"#{name}.h\"")
  File.open("#{name}.c", "w") do |f| 
    f.puts c_src
  end
end

def fix_vala_c_sources(sources)
  sources.each do |srcname|
    c_src = File.read("#{srcname}.c")
    h_src = File.read("#{srcname}.h")
    VALA_SOURCES.each do |srcname2|
      c_src.gsub!("#include <#{srcname2}.h>", "#include \"#{srcname2}.h\"")
      h_src.gsub!("#include <#{srcname2}.h>", "#include \"#{srcname2}.h\"")
    end
    File.open("#{srcname}.c", "w") do |f| 
      f.puts c_src
    end
    File.open("#{srcname}.h", "w") do |f| 
      f.puts h_src
    end
  end
  
  # fix missing ScannerIterator typedefs
  lines = File.readlines("theme.h")
  ix = lines.index("typedef struct _GtkMateScannerClass GtkMateScannerClass;\n")
  raise "couldn't patch theme.h" unless ix
  lines.insert(ix+1, "typedef struct _GtkMateScannerIteratorClass GtkMateScannerIteratorClass;\n")
  lines.insert(ix+1, "typedef struct _GtkMateScannerIterator GtkMateScannerIterator;\n")
  File.open("theme.h", "w") {|f| f.puts lines.join }
end

namespace :build do
  task :clean do
    puts "cleaning..."
    %x{rm lib/*.c lib/*.h lib/*.so lib/*.o lib/Makefile}
  end

  desc "build c files from vala"
  task :build_c do
    sources_to_compile = VALA_SOURCES.map{|n| n+".vala"}
    FileUtils.cd("lib") do
      puts "compiling gtkmateview..."
      if sources_to_compile.empty?
        puts "  nothing to do."
      else
        puts valac="valac -C --library gtkmateview --pkg gtksourceview-2.0 --pkg libxml-2.0 --pkg gee-1.0 --pkg gtksourceview-2.0 --vapidir=./../vapi/ --pkg=oniguruma #{sources_to_compile.join(" ")}"
        puts %x{#{valac}}
        fix_vala_c_sources(VALA_SOURCES)
      end
    end
    VALA_SOURCES.each do |fn|
      if %x{md5sum lib/#{fn}.c}.split(" ").first != %x{md5sum dist/#{fn}.c}.split(" ").first
        puts "different #{fn}.c"
        FileUtils.cp("lib/#{fn}.c", "dist/")
      end
      if %x{md5sum lib/#{fn}.h}.split(" ").first != %x{md5sum dist/#{fn}.h}.split(" ").first
        puts "different #{fn}.h"
        FileUtils.cp("lib/#{fn}.h", "dist/")
      end
      FileUtils.rm_f("lib/#{fn}.h")
      FileUtils.rm_f("lib/#{fn}.c")
    end
  end
  
  desc "build project from scratch"
  task :all => [:build_c] do
    FileUtils.cd("lib") do
      puts "running VALAR..."
      puts %x{ruby ../../valar/bin/valar gtkmateview.vapi --deps="gtk+-2.0,oniguruma,gtksourceview-2.0" --vapidirs="../vapi/oniguruma.vapi"}
    end
    if %x{md5sum lib/gtkmateview_rb.c}.split(" ").first != %x{md5sum dist/gtkmateview_rb.c}.split(" ").first
      FileUtils.mv("lib/gtkmateview_rb.c", "dist/")
    end
    FileUtils.cd("dist") do
      puts 
      puts "compiling gtkmateview_rb..."
      puts %x{ruby extconf.rb}
      puts %x{make}
      puts
    end
  end
end
  
Spec::Rake::SpecTask.new do |t|
  t.spec_opts = ["-c"]#, "-f s"]
end

