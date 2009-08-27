
require 'spec/spec_helper'

describe Gtk::Mate::Parser, "when parsing PHP embedded from scratch" do

  before(:each) do
    @mb = Gtk::Mate::Buffer.new
    @mb.set_grammar_by_name("HTML")
  end

  it "Parses embedded PHP at the beginning of the line" do
    @mb.text = "<? print(\"Asdf\") ?>"
    @mb.parser.root.pretty(0).should == (t=<<END)
+ source.html (0,0)-(0,21) open
END
  end

  it "Parses embedded PHP" do
    @mb.text = " <? print(\"Asdf\") ?>"
    @mb.parser.root.pretty(0).should == (t=<<END)
+ source.html (0,0)-(0,21) open
END
  end
end
