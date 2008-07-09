
require 'gtk2'
require 'gtksourceview2'
require 'lib/gtkmateview_rb'

 win = Gtk::Window.new
win.set_size_request(800, 600)
mv = Gtk::Mate::View.new
mv.buffer = Gtk::Mate::Buffer.new
vb = Gtk::VBox.new
vb.pack_start(mv)
button = Gtk::Button.new("grammar")
button.signal_connect("clicked") do 
  p mv.buffer.set_grammar_by_extension("poipoi")
end
vb.pack_start(button)
win.add(vb)

win.signal_connect("destroy") do
  Gtk.main_quit
end
win.show_all
Gtk.main
