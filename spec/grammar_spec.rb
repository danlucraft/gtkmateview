
require 'spec/spec_helper'

describe Gtk::Mate::Grammar do
  before(:each) do
    @mb = Gtk::Mate::Buffer.new
    @apb = Gtk::Mate::Buffer.bundles.find {|b| b.name == "Apache"}
    @apg = @apb.grammars.find{|b| p b.name; b.name == "Apache" }
    @apg.init_for_use
  end
  
  it "should load patterns into memory" do
    @apg.patterns.should_not be_empty
    pnames = @apg.patterns.map{|p| p.name}
    pnames.should include("comment.line.number-sign.apache-config")
    pnames.should include("source.include.apache-config")
    pnames.should include("support.constant.apache-config")
  end

  it "should replace all include patterns" do
    @apg.patterns.each do |p| 
      p.class.should_not == Gtk::Mate::IncludePattern
      if p.is_a? Gtk::Mate::DoublePattern
        p.patterns.each do |p1|
          p1.class.should_not == Gtk::Mate::IncludePattern
          if p1.is_a? Gtk::Mate::DoublePattern
            p1.patterns.each do |p2|
              p2.class.should_not == Gtk::Mate::IncludePattern
            end
          end
        end
      end
    end
  end
  
  it "should load captures" #do
#    p = @apg.patterns.find{|p| p.name == "comment.line.number-sign.apache-config"}
#  end
end
