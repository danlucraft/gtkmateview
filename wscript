#!/usr/bin/env python

VERSION = "0.0.1"
VERSION_MAJOR_MINOR = ".".join(VERSION.split(".")[0:2])
APPNAME = "gtkmateview"

srcdir = '.'
blddir = '_build_'

def set_options(opt):
    opt.tool_options('compiler_cc')

def configure(conf):
    conf.check_tool('compiler_cc')
    conf.check_tool('checks')
    conf.check_tool('vala')
    conf.env.append_value('CXXFLAGS', '-pg')
    conf.env.append_value('LDFLAGS', '-pg')
    conf.env.append_value('LIB', 'onig')
    onigconf = conf.create_library_configurator()
    onigconf.name = "onig"
    onigconf.run()
    
    conf.check_pkg('glib-2.0', destvar='GLIB', vnum='2.10.0')
    conf.check_pkg('gobject-2.0', destvar='GOBJECT', vnum='2.10.0')
    conf.check_pkg('gtk+-2.0', destvar='GTK+', vnum='2.10.0')
    conf.check_pkg('gtksourceview-2.0', destvar='GTKSOURCEVIEW2', vnum='0')
    conf.check_pkg('libxml-2.0', destvar='LIBXML', vnum='0')
    conf.check_pkg('gee-1.0', destvar='GEE', vnum='0')

    conf.define('PACKAGE', APPNAME)
    conf.define('PACKAGE_NAME', APPNAME)
    conf.define('PACKAGE_STRING', APPNAME + '-' + VERSION)
    conf.define('PACKAGE_VERSION', APPNAME + '-' + VERSION)

    conf.define('VERSION', VERSION)
    conf.define('VERSION_MAJOR_MINOR', VERSION_MAJOR_MINOR)

def build(bld):
    bld.add_subdirs('lib')
    bld.add_subdirs('bin')

def shutdown():
    import UnitTest, Object
    unittest = UnitTest.unit_test()
    unittest.want_to_see_test_output = True
    unittest.want_to_see_test_error = True
    unittest.run()
    unittest.print_results()
    import Params
    Params.pprint ('YELLOW', 'You may find the resulting objects in the %s folder' % blddir)

