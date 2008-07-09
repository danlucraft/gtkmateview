
require 'gtk2'
require 'gtksourceview'
require 'lib/gtkmateview_rb'

Gtk::MateView.load_bundles

 win = Gtk::Window.new
win.set_size_request(800, 600)
mv = Gtk::MateView.new
mv.buffer = Gtk::SourceBuffer.new
vb = Gtk::VBox.new
vb.pack_start(mv)
button = Gtk::Button.new("grammar")
button.signal_connect("clicked") do 
  p mv.set_grammar_by_extension("poipoi")
end
vb.pack_start(button)
win.add(vb)
win.show_all
Gtk.main
