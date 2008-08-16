
require 'spec/spec_helper'

describe Gtk::Mate::Parser do
  before(:each) do
    @mb = Gtk::Mate::Buffer.new
    @apg = Gtk::Mate::Buffer.bundles.find{|b| b.name == "Apache"}.grammars.find{|g| g.name == "Apache"}
    @mb.set_grammar_by_name("Apache")
  end
  
  it "should create a root scope node" do
    @mb.parser.root.name.should == "source.apache-config"
    @mb.parser.root.pretty(1).should == "  + source.apache-config (0,0)-(0,0) open\n"
    @mb.parser.root.is_root.should be_true
  end
  
  it "should complete a simple scope tree" do
    @mb.set_grammar_by_name("Ruby")
    @mb.text =<<-END
class Red < Car
  def foo
  end
end
    END
    @mb.parser.root.pretty(0).should == <<END
+ source.ruby (0,0)-(4,0) open
  + meta.class.ruby (0,0)-(0,15) closed
    + keyword.control.class.ruby (0,0)-(0,5) closed
    + entity.name.type.class.ruby (0,6)-(0,15) closed
      + entity.other.inherited-class.ruby (0,9)-(0,15) closed
        + punctuation.separator.inheritance.ruby (0,10)-(0,11) closed
  + meta.function.method.without-arguments.ruby (1,2)-(1,9) closed
    + keyword.control.def.ruby (1,2)-(1,5) closed
    + entity.name.function.ruby (1,6)-(1,9) closed
  + keyword.control.ruby (2,2)-(2,5) closed
  + keyword.control.ruby (3,0)-(3,3) closed
END
  end
end
