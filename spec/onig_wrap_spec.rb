
require 'spec/spec_helper'

describe Oniguruma::Regex do
  it "initializes all ok" do
    Oniguruma::Regex.make1("dan").should be_an_instance_of(Oniguruma::Regex)
  end

  it "returns nil for bad regular expressions" do
    Oniguruma::Regex.make1("da(n").should be_nil
  end
  
  it "returns nil if no match" do
    re = Oniguruma::Regex.make1("ros")
    str = "adama"
    re.search(str, 0, str.length).should be_nil
  end
  
  it "returns matchdata" do
    re = Oniguruma::Regex.make1("ros")
    str = "laura roslin"
    re.search(str, 0, str.length).should be_an_instance_of(Oniguruma::Match)
  end
end

describe Oniguruma::Match do
  before(:each) do
    str = "laura roslin"
    @md = Oniguruma::Regex.make1("lau(ra) ros(lin)").search(str, 0, str.length)
  end
  
  it "returns the index of the match" do
    @md.begin(0).should == 0
  end
  
  it "returns the index of each capture" do
    @md.begin(1).should == 3
    @md.begin(2).should == 9
  end
  
  it "returns the end index of each capture" do
    @md.end(1).should == 5
    @md.end(2).should == 12
  end
  
  it "returns -1 for unknown captures" do
    @md.begin(10).should == -1
  end
end
