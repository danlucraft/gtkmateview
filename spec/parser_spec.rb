
require 'spec/spec_helper'

describe Gtk::Mate::Parser do
  before(:each) do
    @mb = Gtk::Mate::Buffer.new
    @apg = Gtk::Mate::Buffer.bundles.find{|b| b.name == "Apache"}.grammars.find{|g| g.name == "Apache"}
    @mb.set_grammar_by_name("Apache")
  end
  
  it "should create a root scope node" do
    @mb.parser.root.name.should == "source.apache-config"
    @mb.parser.root.pretty(1).should == "  source.apache-config (inf)-(inf)\n"
    @mb.parser.root.is_root.should be_true
  end
end