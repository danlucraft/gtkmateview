
require 'spec/spec_helper'

describe Gtk::Mate::Parser, "When parsing PHP embedded: " do

  before(:each) do
    @mb = Gtk::Mate::Buffer.new
    @mb1 = Gtk::Mate::Buffer.new
    @mb.set_grammar_by_name("HTML")
    @mb1.set_grammar_by_name("HTML")
  end

  it "Compare 2 embedded php strings. One begins at the beginning of the line, other is not" do
    @mb.text = "<? print(\"Asdf\") ?>"
    @mb1.text = " <? print(\"Asdf\") ?>"
    @mb.parser.root.pretty(0).should == @mb1.parser.root.pretty(0)
  end
end
