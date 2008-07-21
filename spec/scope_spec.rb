

require 'spec/spec_helper'

describe Gtk::Mate::Scope do
  before(:each) do
    @mb = Gtk::Mate::Buffer.new
    @mb.set_grammar_by_name("Apache")
  end
  
  it "should be comparable" do
    Gtk::Mate::Scope.compare(@mb.parser.root, @mb.parser.root).should == 0
  end
end
