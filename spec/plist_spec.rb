
require 'spec/spec_helper'

describe PList do
  it "raises IO ValaError if file not found" do
    lambda { PList.parse("nosuchfile.xml") }.should raise_error(ValaError)
  end
  
  it "parses a file and returns a Dict" do
    PList.parse("spec/fixtures/Ruby.plist").should be_an_instance_of(PList::Dict)
  end
  
end

describe PList::Dict do
  before(:each) do 
    @dict = PList.parse("spec/fixtures/Ruby.plist")
  end
  
  it "lets you retrieve values" do
    @dict.get("fileTypes").should be_an_instance_of(PList::Array)
  end
  
  it "lets you get a list of keys" do
    @dict.keys.should be_an_instance_of(Array)
    @dict.keys[0].should be_an_instance_of(String)
  end
end

describe PList::Array do
  before(:each) do
    dict = PList.parse("spec/fixtures/Ruby.plist")
    @array = dict.get("fileTypes")
  end
  
  it "lets you get an element" do
    @array.get(0).should be_an_instance_of(PList::String)
  end
end

describe PList::String do
  before(:each) do
    dict = PList.parse("spec/fixtures/Ruby.plist")
    array = dict.get("fileTypes")
    @string = array.get(0)
  end
  
  it "lets you get the String" do
    @string.str.should be_an_instance_of(String)
  end
end

describe PList::Integer do
  before(:each) do
    @dict = PList.parse("spec/fixtures/Ruby.plist")
  end

  it "lets you get the Integer" do
    int_node = @dict.get("dummy_integer")
    int_node.value.should be_an_instance_of(Fixnum)
  end
end
