

require 'spec/spec_helper'

describe Gtk::Mate::Parser, "when parsing Ruby from scratch" do
  before(:each) do
    @mb = Gtk::Mate::Buffer.new
    @mb.set_grammar_by_name("Ruby")
  end
  
  it "parses flat SinglePatterns" do
    @mb.text = "1 + 2 + Redcar"
    @mb.parser.root.pretty(0).should == <<END
+ source.ruby (0,0)-(0,14) open
  + constant.numeric.ruby (0,0)-(0,1) closed
  + keyword.operator.arithmetic.ruby (0,2)-(0,3) closed
  + constant.numeric.ruby (0,4)-(0,5) closed
  + keyword.operator.arithmetic.ruby (0,6)-(0,7) closed
  + variable.other.constant.ruby (0,8)-(0,14) closed
END
  end
  
  it "parses flat SinglePatterns on multiple lines" do
    @mb.text = "1 + \n3 + Redcar"
    @mb.parser.root.pretty(0).should == <<END
+ source.ruby (0,0)-(1,10) open
  + constant.numeric.ruby (0,0)-(0,1) closed
  + keyword.operator.arithmetic.ruby (0,2)-(0,3) closed
  + constant.numeric.ruby (1,0)-(1,1) closed
  + keyword.operator.arithmetic.ruby (1,2)-(1,3) closed
  + variable.other.constant.ruby (1,4)-(1,10) closed
END
  end
  
  it "arranges SinglePattern captures into trees" do
    @mb.text = "class Red < Car"
    @mb.parser.root.pretty(0).should == <<END
+ source.ruby (0,0)-(0,15) open
  + meta.class.ruby (0,0)-(0,15) closed
    + keyword.control.class.ruby (0,0)-(0,5) closed
    + entity.name.type.class.ruby (0,6)-(0,15) closed
      + entity.other.inherited-class.ruby (0,9)-(0,15) closed
        + punctuation.separator.inheritance.ruby (0,10)-(0,11) closed
END
  end
  
  it "opens DoublePatterns" do
    @mb.text = "\"asdf"
    @mb.parser.root.pretty(0).should == <<END
+ source.ruby (0,0)-(0,5) open
  + string.quoted.double.ruby (0,0)-(0,5) open
    + punctuation.definition.string.begin.ruby (0,0)-(0,1) closed
END
  end
  
  it "closes DoublePatterns" do
    @mb.text = "\"asdf\""
    @mb.parser.root.pretty(0).should == <<END
+ source.ruby (0,0)-(0,6) open
  + string.quoted.double.ruby (0,0)-(0,6) closed
    + punctuation.definition.string.begin.ruby (0,0)-(0,1) closed
    + punctuation.definition.string.end.ruby (0,5)-(0,6) closed
END
  end
  
  it "knows content_names of DoublePatterns" do
    @mb.text = "def foo(a, b)"
    @mb.parser.root.pretty(0).should == <<END
+ source.ruby (0,0)-(0,13) open
  + meta.function.method.with-arguments.ruby variable.parameter.function.ruby (0,0)-(0,13) closed
    + keyword.control.def.ruby (0,0)-(0,3) closed
    + entity.name.function.ruby (0,4)-(0,7) closed
    + punctuation.definition.parameters.ruby (0,7)-(0,8) closed
    + punctuation.separator.object.ruby (0,9)-(0,10) closed
    + punctuation.definition.parameters.ruby (0,12)-(0,13) closed
END
  end
  
  it "creates scopes as children of DoublePatterns" do
    @mb.text = "\"laura\\nroslin\""
    @mb.parser.root.pretty(0).should == <<END
+ source.ruby (0,0)-(0,15) open
  + string.quoted.double.ruby (0,0)-(0,15) closed
    + punctuation.definition.string.begin.ruby (0,0)-(0,1) closed
    + constant.character.escape.ruby (0,6)-(0,8) closed
    + punctuation.definition.string.end.ruby (0,14)-(0,15) closed
END
  end
  
  it "creates closing regexes correctly" do
    @mb.text = "foo=\<\<END\nstring\nEND"
    @mb.parser.root.pretty(0).should == <<END
+ source.ruby (0,0)-(2,3) open
  + string.unquoted.heredoc.ruby (0,3)-(2,3) closed
    + punctuation.definition.string.begin.ruby (0,3)-(0,9) closed
    + punctuation.definition.string.end.ruby (2,0)-(2,3) closed
END
  end
  
  it "creates multiple levels of scopes" do
    @mb.text = "\"william \#{:joseph} adama\""
    puts @mb.parser.root.pretty(0)
    @mb.parser.root.pretty(0).should == <<END
+ source.ruby (0,0)-(0,26) open
  + string.quoted.double.ruby (0,0)-(0,26) closed
    + punctuation.definition.string.begin.ruby (0,0)-(0,1) closed
    + source.ruby.embedded.source (0,9)-(0,19) closed
      + punctuation.section.embedded.ruby (0,9)-(0,11) closed
      + constant.other.symbol.ruby (0,11)-(0,18) closed
        + punctuation.definition.constant.ruby (0,11)-(0,12) closed
      + punctuation.section.embedded.ruby (0,18)-(0,19) closed
    + punctuation.definition.string.end.ruby (0,25)-(0,26) closed
END
  end
  
  it "parses some Ruby correctly" do
    @mb.text = <<END
class Red < Car
  attr :foo
  Dir["*"].each do |fn|
    p fn
  end
end
END
    @mb.parser.root.pretty(0).should == <<END
+ source.ruby (0,0)-(6,0) open
  + meta.class.ruby (0,0)-(0,15) closed
    + keyword.control.class.ruby (0,0)-(0,5) closed
    + entity.name.type.class.ruby (0,6)-(0,15) closed
      + entity.other.inherited-class.ruby (0,9)-(0,15) closed
        + punctuation.separator.inheritance.ruby (0,10)-(0,11) closed
  + keyword.other.special-method.ruby (1,2)-(1,6) closed
  + constant.other.symbol.ruby (1,7)-(1,11) closed
    + punctuation.definition.constant.ruby (1,7)-(1,8) closed
  + support.class.ruby (2,2)-(2,5) closed
  + punctuation.section.array.ruby (2,5)-(2,6) closed
  + string.quoted.double.ruby (2,6)-(2,9) closed
    + punctuation.definition.string.begin.ruby (2,6)-(2,7) closed
    + punctuation.definition.string.end.ruby (2,8)-(2,9) closed
  + punctuation.section.array.ruby (2,9)-(2,10) closed
  + punctuation.separator.method.ruby (2,10)-(2,11) closed
  + keyword.control.start-block.ruby (2,16)-(2,19) closed
  +  (2,19)-(2,23) closed
    + punctuation.separator.variable.ruby (2,19)-(2,20) closed
    + variable.other.block.ruby (2,20)-(2,22) closed
    + punctuation.separator.variable.ruby (2,22)-(2,23) closed
  + keyword.control.ruby (4,2)-(4,5) closed
  + keyword.control.ruby (5,0)-(5,3) closed
END
  end

  it "embeds HTML in Ruby" do
    @mb.text = <<END
foo=<<-HTML
<p>FOO</p>
HTML
END
    @mb.parser.root.pretty(0).should == <<END
+ source.ruby (0,0)-(3,0) open
  + keyword.operator.assignment.ruby (0,3)-(0,4) closed
  + string.unquoted.embedded.html.ruby text.html.embedded.ruby (0,4)-(2,4) closed
    + punctuation.definition.string.begin.ruby (0,4)-(0,11) closed
    + meta.tag.block.any.html (1,0)-(1,3) closed
      + punctuation.definition.tag.begin.html (1,0)-(1,1) closed
      + entity.name.tag.block.any.html (1,1)-(1,2) closed
      + punctuation.definition.tag.end.html (1,2)-(1,3) closed
    + meta.tag.block.any.html (1,6)-(1,10) closed
      + punctuation.definition.tag.begin.html (1,6)-(1,8) closed
      + entity.name.tag.block.any.html (1,8)-(1,9) closed
      + punctuation.definition.tag.end.html (1,9)-(1,10) closed
    + punctuation.definition.string.end.ruby (2,0)-(2,4) closed
END
  end

  it "embeds CSS in HTML in Ruby" do
    @mb.text = <<END
foo=<<-HTML
<style>
  .foo {
    
  }
</style>
HTML
END
    @mb.parser.root.pretty(0).should == <<END
+ source.ruby (0,0)-(7,0) open
  + keyword.operator.assignment.ruby (0,3)-(0,4) closed
  + string.unquoted.embedded.html.ruby text.html.embedded.ruby (0,4)-(6,4) closed
    + punctuation.definition.string.begin.ruby (0,4)-(0,11) closed
    + source.css.embedded.html (1,0)-(5,8) closed
      + punctuation.definition.tag.html (1,0)-(1,1) closed
      + entity.name.tag.style.html (1,1)-(1,6) closed
      +  (1,6)-(5,0) closed
        + punctuation.definition.tag.html (1,6)-(1,7) closed
        + meta.selector.css (2,0)-(2,7) closed
          + entity.other.attribute-name.class.css (2,2)-(2,6) closed
            + punctuation.definition.entity.css (2,2)-(2,3) closed
        + source.smarty.embedded.html (2,7)-(4,3) closed
      + punctuation.definition.tag.html (5,0)-(5,2) closed
      + entity.name.tag.style.html (5,2)-(5,7) closed
      + punctuation.definition.tag.html (5,7)-(5,8) closed
    + punctuation.definition.string.end.ruby (6,0)-(6,4) closed
END
  end
end
