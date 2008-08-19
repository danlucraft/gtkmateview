

require 'spec/spec_helper'

describe Gtk::Mate::Parser, "when reparsing Ruby after changes" do
  before(:each) do
    @mb = Gtk::Mate::Buffer.new
    @mb.set_grammar_by_name("Ruby")
  end
  
  it "reparses flat SinglePatterns with no changes to scopes" do
    @mb.text = "1 + 2 + Redcar"
    @mb.type(0, 1, " ")
    @mb.pretty.should == @mb.clean_reparse
  end
  
  it "reparses flat SinglePatterns with changes to scopes" do
    @mb.text = "1 + 2 + Redcar"
    @mb.type(0, 4, "2")
#    @mb.type(0, 12, "o")
    @mb.pretty.should == @mb.clean_reparse
  end
end
