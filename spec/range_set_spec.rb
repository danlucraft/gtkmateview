
require 'spec/spec_helper'

describe RangeSet, "when empty" do
  before(:each) do
   @rs = RangeSet.new 
  end
  
  it "should report empty" do
    @rs.length.should == 0
    @rs.size.should == 0
  end
  
  it "should add a range" do
    @rs.add(1, 3)
    @rs.length.should == 1
    @rs.size.should == 3
  end
end

describe RangeSet, "with contents" do
  before(:each) do
    @rs = RangeSet.new
    @rs.add(1, 3)
    @rs.add(5, 5)
    @rs.add(10, 15)
  end
  
  it "should report length" do
    @rs.length.should == 3
  end
  
  it "should report size" do
    @rs.size.should == 10
  end
  
  it "should merge ranges" do
    @rs.add(14, 16)
    @rs.present.should == "1-3, 5, 10-16, "
  end
  
  it "should merge ranges 2" do
    @rs.add(7, 11)
    @rs.present.should == "1-3, 5, 7-15, "
  end
  
  it "should merge two ranges" do
    @rs.add(4, 11)
    @rs.present.should == "1-3, 4-15, "
  end
end

