
require 'gtk2'
require 'gtksourceview2'
require 'dist/gtkmateview_rb'

def new_view
  mv = Gtk::Mate::View.new
  mv.buffer = Gtk::Mate::Buffer.new
  mv.modify_font(Pango::FontDescription.new("Consolas 14"))
  mv
end

win = Gtk::Window.new
win.set_size_request(800, 600)

vb = Gtk::VBox.new

button_gr = Gtk::Button.new("grammar")
button_gr.signal_connect("clicked") do 
  if @current_view
    @current_view.buffer.set_grammar_by_extension("poipoi")
  end
end

button_tree = Gtk::Button.new("tree")
button_tree.signal_connect("clicked") do 
  if @current_view
    puts @current_view.buffer.parser.root.pretty(0)
    puts
  end
end

button_rb = Gtk::Button.new("Ruby")
button_rb.signal_connect("clicked") do 
  if @current_view
    @current_view.buffer.set_grammar_by_name("Ruby")
    @current_view.set_theme_by_name("Twilight")
  end
end

button_file = Gtk::Button.new("Load file")
button_file.signal_connect("clicked") do
  if @current_view
    s = Time.now
    @current_view.buffer.text = File.read("samples/rak")
    puts "took #{Time.now - s} seconds"
  end
end

button_twilight = Gtk::Button.new("Twilight")
button_twilight.signal_connect("clicked") do
  if @current_view
    s = Time.now
    @current_view.set_theme_by_name("Twilight")
    puts "took #{Time.now - s} seconds"
  end
end

button_mc = Gtk::Button.new("Mac Classic")
button_mc.signal_connect("clicked") do
  if @current_view
    s = Time.now
    @current_view.set_theme_by_name("Mac Classic")
    puts "took #{Time.now - s} seconds"
  end
end

toolbar = Gtk::HBox.new
toolbar.pack_start(button_rb)
toolbar.pack_start(button_gr)
toolbar.pack_start(button_file)
toolbar.pack_start(button_tree)
toolbar.pack_start(button_twilight)
toolbar.pack_start(button_mc)
vb.pack_start(toolbar, false)

gtk_notebook = Gtk::Notebook.new
gtk_notebook.set_group_id 0
gtk_notebook.homogeneous = true

gtk_notebook.signal_connect("switch-page") do |nb, _, page_num|
  @current_view = nb.get_nth_page(page_num)
  true
end

button_new = Gtk::Button.new("new")
button_new.signal_connect("clicked") do
  new_mv = new_view
  gtk_notebook.append_page(new_mv, Gtk::Label.new("new"))
  gtk_notebook.set_tab_reorderable(new_mv, true)
  gtk_notebook.set_tab_detachable(new_mv, true)
  gtk_notebook.show_all
  @current_view = new_mv
end

vb.pack_start(gtk_notebook)

button_on = Gtk::Button.new("on")
button_off = Gtk::Button.new("off")
button_on.signal_connect("clicked") do
  @current_view.buffer.parser.start_parsing if @current_view
end
button_off.signal_connect("clicked") do
  @current_view.buffer.parser.stop_parsing if @current_view
end
toolbar.pack_start button_on
toolbar.pack_start button_off
toolbar.pack_start button_new

win.add(vb)

win.signal_connect("destroy") do
  Gtk.main_quit
end

win.show_all

Gtk.main
