
require 'spec/spec_helper'

describe Gtk::Mate::Parser, "when reparsing Ruby after changes" do
  before(:each) do
    @mb = Gtk::Mate::Buffer.new
    @mb.set_grammar_by_name("Ruby")
  end

  it "reparses lines with only whitespace changes" do
    @mb.text = <<-END
    class Red < Car
      def foo
      end
    end
    END
    5.times { @mb.type(1, 9, " ") }
    @mb.pretty.should == @mb.clean_reparse
  end
  
  it "reparses lines with only whitespace changes, even when they have scope openers" do
    @mb.text = <<-END
puts "hello"
foo=<<HI
  Here.foo
  Here.foo
HI
puts "hello"
END
    5.times { @mb.type(1, 8, " ") }
    @mb.pretty.should == @mb.clean_reparse
  end
  
  it "reparses flat SinglePatterns that have no changes to scopes" do
    @mb.text = "1 + 2 + Redcar"
    @mb.type(0, 1, " ")
    @mb.pretty.should == @mb.clean_reparse
  end
  
  it "reparses flat SinglePatterns that have changes to scopes" do
    @mb.text = "1 + 2 + Redcar"
    @mb.type(0, 4, "2")
    @mb.type(0, 12, "o")
    @mb.pretty.should == @mb.clean_reparse
  end
  
  it "reparses when blank lines inserted" do
    @mb.text = <<-END
    class Red < Car
      def foo
      end
    end
    END
    @mb.type(1, 0, "\n")
    @mb.type(1, 0, "\n")
    @mb.pretty.should == @mb.clean_reparse
  end
  
  it "reparses lines with only whitespace changes, even when they have closing scopes" do
    @mb.text = <<-END
puts "hello"
foo=<<HI
  Here.foo
  Here.foo
HI
puts "hello"
END
    1.times { @mb.type(4, 2, " ") }
    @mb.pretty.should == @mb.clean_reparse
  end
  
  it "opens expected scopes again" do
    @mb.text = "def foo(a, b, c"
    @mb.type(0, 15, ")")
    @mb.pretty.should == @mb.clean_reparse
  end

  it "clears after at multiple levels correctly" do
    @mb.text =<<END
f=<<-HTML
  <style>
    .foo {
    }
  </style>
  <br />
HTML
p :asdf
END
    8.times { |i| @mb.backspace(4, 10-i) }
    @mb.pretty.should == @mb.clean_reparse
  end
end
