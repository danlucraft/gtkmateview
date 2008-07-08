
require 'rubygems'
require 'fileutils'
require 'spec/rake/spectask'

VALA_SOURCES = Dir["lib/*.vala"].map {|n| n =~ /lib\/(.*)\.vala/; $1}

def fix_vala_c_file(name)
  c_src = File.read("#{name}.c")
  c_src.gsub!("#include <#{name}.h>", "#include \"#{name}.h\"")
  File.open("#{name}.c", "w") do |f| 
    f.puts c_src
  end
end

namespace :build do
  task :clean do
    puts "cleaning..."
    %x{rm lib/*.c lib/*.h lib/*.so lib/*.o lib/Makefile}
  end

  desc "build c files from vala"
  task :build_c do
    FileUtils.cd("lib") do
      puts "compiling gtkmateview..."
      puts %x{valac -C --library gtkmateview --pkg gtksourceview-2.0 --pkg libxml-2.0 --pkg gee-1.0 --pkg gtksourceview-2.0 --vapidir=./../vapi/ --pkg=oniguruma #{VALA_SOURCES.map{|n| n+".vala"}.join(" ")}} #plist.vala onig_wrap.vala gtkmateview.vala}
      VALA_SOURCES.each do |name|
        fix_vala_c_file(name)
      end
    end
  end
  
  desc "build project from scratch"
  task :all => [:clean, :build_c] do
    FileUtils.cd("lib") do
#       puts "linking gtkmateview..."
#       puts %x{gcc --shared -fPIC -o gtkmateview.so $(pkg-config --cflags --libs gobject-2.0 gee-1.0 libxml-2.0) -lonig plist.c onig_test.c -I/usr/local/lib/ruby/1.8/i686-linux -I/usr/local/lib/}
    
      puts "running VALAR..."
      puts %x{ruby ../../valar/bin/valar gtkmateview.vapi --deps="gtk+-2.0,oniguruma,gtksourceview-2.0" --vapidirs="../vapi/oniguruma.vapi"}

      puts 
      puts "compiling gtkmateview_rb..."
      puts %x{ruby extconf.rb}
      puts %x{make}
      puts
    end
  end
end
  
Spec::Rake::SpecTask.new do |t|
  t.spec_opts = ["-c", "-f s"]
end
