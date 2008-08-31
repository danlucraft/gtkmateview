

require 'spec/spec_helper'

describe StringHelper do
  describe ".gsub" do
    it "should do string replacement" do
      StringHelper.gsub("abc abc", "a", "foo").should == "foobc foobc"
    end

    it "should work with the empty string" do
      StringHelper.gsub("", "a", "foo").should == ""
    end
  end
  
  describe ".occurrences" do
    it "should return an empty array for no occurrences" do
      StringHelper.occurrences("sadf", "x").should == []
    end

    it "should return an array of occurrences" do
      StringHelper.occurrences("xasdfasdf", "a").should == [1, 5]
    end
  end
end
