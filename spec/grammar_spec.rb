
require 'spec/spec_helper'

describe Gtk::Mate::Grammar do
  before(:each) do
    @mb = Gtk::Mate::Buffer.new
  end
  
  it "should load patterns into memory" do
    @mb.set_grammar_by_extension("htaccess")
  end
end
