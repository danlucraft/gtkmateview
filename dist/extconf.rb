
# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf-gnome2'
# $CFLAGS = "-pg"
$LDFLAGS = "-pg"
extension_name = 'gtkmateview_rb'

PKGConfig.have_package('gtk+-2.0')
PKGConfig.have_package('libxml-2.0')
PKGConfig.have_package('gee-1.0')
PKGConfig.have_package('gtksourceview-2.0')

have_library("onig")

# The destination
dir_config(extension_name)

# Do the work
create_makefile(extension_name)
