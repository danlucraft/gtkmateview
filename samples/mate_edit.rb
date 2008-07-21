
require 'gtk2'
require 'gtksourceview2'
require 'lib/gtkmateview_rb'

win = Gtk::Window.new
win.set_size_request(800, 600)
mv = Gtk::Mate::View.new
mv.buffer = Gtk::Mate::Buffer.new
vb = Gtk::VBox.new

button_gr = Gtk::Button.new("grammar")
button_gr.signal_connect("clicked") do 
  p mv.buffer.set_grammar_by_extension("poipoi")
end

button_rb = Gtk::Button.new("Ruby")
button_rb.signal_connect("clicked") do 
  mv.buffer.set_grammar_by_name("Ruby")
end

toolbar = Gtk::HBox.new
toolbar.pack_start(button_rb)
toolbar.pack_start(button_gr)
vb.pack_start(toolbar, false)
vb.pack_start(mv)
button_on = Gtk::Button.new("on")
button_off = Gtk::Button.new("off")
button_on.signal_connect("clicked") do
  mv.buffer.parser.start_parsing
end
button_off.signal_connect("clicked") do
  mv.buffer.parser.stop_parsing
end
toolbar.pack_start button_on
toolbar.pack_start button_off

win.add(vb)

win.signal_connect("destroy") do
  Gtk.main_quit
end
win.show_all
Gtk.main
