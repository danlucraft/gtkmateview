

require 'spec/spec_helper'

describe Gtk::Mate::Scope do
  before(:each) do
    @mb = Gtk::Mate::Buffer.new
    @mb.set_grammar_by_name("Ruby")
  end

  describe ".hierarchy_names" do
    it "scopes have hierarchy names" do
      @mb.text = "def foo"
      @mb.parser.root.scope_at(0, 1).hierarchy_names(false).should == "source.ruby meta.function.method.without-arguments.ruby keyword.control.def.ruby"
    end

    it "shows leaves out content_names for captures" do
      @mb.text = "def foo(aasdf, basd)"
      @mb.parser.root.scope_at(0, 1).hierarchy_names(false).should == "source.ruby meta.function.method.with-arguments.ruby keyword.control.def.ruby"
    end

    it "shows content_names for internal points " do
      @mb.text = "def foo(aasdf, basd)"
      @mb.parser.root.scope_at(0, 10).hierarchy_names(true).should == "source.ruby meta.function.method.with-arguments.ruby variable.parameter.function.ruby"
    end
  end
end
