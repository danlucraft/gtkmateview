
require 'rubygems'
require 'fileutils'
require 'spec/rake/spectask'

namespace :build do
  task :clean do
    puts "cleaning..."
    %x{rm lib/*.c lib/*.h lib/*.so lib/*.o lib/Makefile}
  end

  desc "build c files from vala"
  task :build_c do
    FileUtils.cd("lib") do
      puts "compiling gtkmateview..."
      puts %x{valac -C --library gtkmateview --pkg libxml-2.0 --pkg gee-1.0 plist.vala}
      
      c_src = File.read("plist.c")
      c_src.gsub!("#include <plist.h>", "#include \"plist.h\"")
      File.open("plist.c", "w") do |f| 
        f.puts c_src
      end
    end
  end
  
  desc "build project from scratch"
  task :all => [:clean, :build_c] do
    FileUtils.cd("lib") do
      puts "linking vlib..."
      puts %x{gcc --shared -fPIC -o gtkmateview.so $(pkg-config --cflags --libs gobject-2.0 gee-1.0 libxml-2.0) plist.c -I/usr/local/lib/ruby/1.8/i686-linux}
    
      puts "running VALAR..."
      puts %x{ruby ../../valar/bin/valar gtkmateview.vapi}

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
