
require 'spec/spec_helper'

describe Gtk::Mate::Buffer do
  before(:each) do
    @mb = Gtk::Mate::Buffer.new
  end

  it "sets the grammar by filename" do
    @mb.set_grammar_by_filename("rb").should == "Ruby"
    @mb.set_grammar_by_filename("py").should == "Python"
    @mb.set_grammar_by_filename("foo.rb").should == "Ruby"
    @mb.set_grammar_by_filename("foo_spec.rb").should == "RSpec"
  end

  it "should go with the longest extension" do
    @mb.set_grammar_by_filename("asdf.yaml").should == "YAML"
  end

  it "sets the grammar by first line" do
    @mb.set_grammar_by_first_line("#!/usr/bin/ruby\nfoo").should == "Ruby"
    @mb.set_grammar_by_first_line("#!/usr/bin/dmd\nfoo").should == "D"
  end
  
  it "sets the grammar in the attached parser" do
    @mb.set_grammar_by_filename("rb").should == "Ruby"
    @mb.parser.grammar.name.should == "Ruby"
  end
  
  it "sets the grammar by name" do
    @mb.set_grammar_by_name("Ruby")
    @mb.parser.grammar.name.should == "Ruby"
    @mb.set_grammar_by_name("D")
    @mb.parser.grammar.name.should == "D"
  end
end

describe Gtk::Mate::Buffer, "helper methods" do
  before(:each) do
    @mb = Gtk::Mate::Buffer.new
    @mb.text = "foo\nbar\nbaz"
  end

  it "get_line" do
    @mb.get_line(0).should == "foo\n"
    @mb.get_line(1).should == "bar\n"
    @mb.get_line(2).should == "baz"
    @mb.get_line(3).should be_nil
    @mb.get_line(-1).should be_nil
  end
  
  it "get_line_length" do
    @mb.get_line_length(0).should == 3
    @mb.get_line_length(2).should == 3
    @mb.get_line_length(3).should == -1
  end
end
