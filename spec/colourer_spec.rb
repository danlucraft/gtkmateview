
require 'spec/spec_helper'

describe Gtk::Mate::Colourer do
  before(:each) do
    mv = Gtk::Mate::View.new
    mv.buffer = Gtk::Mate::Buffer.new
    @mb = mv.buffer
    @mb.set_grammar_by_name("Ruby")
    mv.set_theme_by_name("Cobalt")
  end

  it "should colour" do
    @mb.text = "def foo"
  end
end
