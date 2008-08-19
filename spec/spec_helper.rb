
require 'gtk2'
require 'gtksourceview2'
require 'lib/gtkmateview_rb'

class Gtk::Mate::Buffer
  def type(line, line_offset, text)
    insert(get_iter_at_line_offset(line, line_offset), text)
  end
  
#   def backspace(line, pos)
#     buf.delete(buf.get_iter_at_line_offset(line, pos-1)
#   end
  
  def clean_reparse
    newbuf = Gtk::Mate::Buffer.new
    newbuf.set_grammar_by_name("Ruby")
    newbuf.text = text
    newbuf.parser.root.pretty(0)
  end
  
  def pretty
    parser.root.pretty(0)
  end
end
