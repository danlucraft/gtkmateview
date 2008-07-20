
require 'spec/spec_helper'

describe Gtk::Mate::Buffer do
  before(:each) do
    @mb = Gtk::Mate::Buffer.new
  end

  it "sets the grammar by extension" do
    @mb.set_grammar_by_extension("rb").should == "Ruby"
    @mb.set_grammar_by_extension("py").should == "Python"
  end

  it "sets the grammar by first line" do
    @mb.text = "#!/usr/bin/ruby\nfoo"
    @mb.set_grammar_by_extension("").should == "Ruby"
    @mb.text = "#!/usr/bin/dmd\nfoo"
    @mb.set_grammar_by_extension("").should == "D"
  end
  
  it "sets the grammar in the attached parser" do
    @mb.set_grammar_by_extension("rb").should == "Ruby"
    @mb.parser.grammar.name.should == "Ruby"
  end
  
  it "sets the grammar by name" do
    @mb.set_grammar_by_name("Ruby")
    @mb.parser.grammar.name.should == "Ruby"
    @mb.set_grammar_by_name("D")
    @mb.parser.grammar.name.should == "D"
  end
end
