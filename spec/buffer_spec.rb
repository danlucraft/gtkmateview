
require 'spec/spec_helper'

describe Gtk::Mate::Buffer do
  before(:each) do
    @mb = Gtk::Mate::Buffer.new
  end

  it "sets the grammar by extension" do
    @mb.set_grammar_by_extension("rb").should == "Ruby"
    @mb.set_grammar_by_extension("py").should == "Python"
  end

#   it "sets the grammar by first line" do
#     @mb.text = "#!/usr/bin/ruby\nfoo"
#     @mb.set_grammar_by_extension("").should == "Ruby"
#     @mb.text = "#!/usr/bin/dmd\nfoo"
#     @mb.set_grammar_by_extension("").should == "D"
#   end
end
