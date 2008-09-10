
require 'gtk2'
require 'gtksourceview2'

v = Gtk::SourceView.new

win = Gtk::Window.new
win.set_size_request(800, 600)
sw = Gtk::ScrolledWindow.new
sw.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC)
sw.add(v)
h = v.signal_connect_after("expose-event") do |_, event|
  p :adsf
  p event
  p event.window
  p v
  p v.window
  if event.window == v.window
    v.modify_base(Gtk::StateType::NORMAL, Gdk::Color.parse("#00FF00"))
    v.signal_handler_disconnect(h)
  end
end
win.add(sw)
win.show_all

Gtk.main
