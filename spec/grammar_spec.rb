
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
    @apg.patterns.each {|p| p.respond_to?(:captures)? p(p.captures) : p.begin_captures }
    @apg.patterns.find{|p| p.respond_to? :captures and p.captures and p.captures.values == ["support.constant.rewritecond.apache-config"]}.should_not be_nil
  end

#   it "should replace all include patterns" do
#     @apg.patterns.each do |p| 
#       p.class.should_not == Gtk::Mate::IncludePattern
#       if p.is_a? Gtk::Mate::DoublePattern
#         p.patterns.each do |p1|
#           p1.class.should_not == Gtk::Mate::IncludePattern
#           if p1.is_a? Gtk::Mate::DoublePattern
#             p1.patterns.each do |p2|
#               p2.class.should_not == Gtk::Mate::IncludePattern
#             end
#           end
#         end
#       end
#     end
#     # check replaces $base properly:
#     pt = @apg.patterns.find{|p| p.name == "meta.vhost.apache-config"}
#     pt.patterns.map{ |pat| pat.name}.should include("meta.vhost.apache-config")

#     # check replaces #vars properly:
#     pt = @apg.patterns.find{|p| p.respond_to? :captures and p.captures and p(p.captures)} #.values == ["support.constant.rewritecond.apache-config"]}
#     p pt
#   end
  
#   it "should load captures" do
#     p = @apg.patterns.find{|p| p.name == "comment.line.number-sign.apache-config"}
#     p.captures.should == {1 => "punctuation.definition.comment.apache-config"}
#   end
end
