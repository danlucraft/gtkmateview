
require 'spec/spec_helper'

describe Gtk::Mate::Colourer do
  before(:each) do
    @mb = Gtk::Mate::Buffer.new
    @mb.set_grammar_by_name("Ruby")
    @mb.set_theme_by_name("Cobalt")
  end

  it "should asdf" do
    @mb.text = "def foo"
    puts @mb.parser.root.pretty(0)
  end
end
