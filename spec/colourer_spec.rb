
require 'spec/spec_helper'

describe Gtk::Mate::Colourer do
  before(:each) do
    @mv = Gtk::Mate::View.new
    @mv.buffer = Gtk::Mate::Buffer.new
    @mb = @mv.buffer
    @mb.set_grammar_by_name("Ruby")
    @mv.set_theme_by_name("Cobalt")
  end

  it "should colour" do
    @mb.text = "def foo"
  end

  it "should not crash if you enter a '[' then a ']'" do
    win = Gtk::Window.new
    win.add(@mv)
    win.show_all
    @mb.insert(@mb.get_iter_at_offset(0), "[")
    @mb.parser.stop_parsing
    @mb.insert(@mb.get_iter_at_offset(1), "]")
    @mb.parser.start_parsing
  end
end
