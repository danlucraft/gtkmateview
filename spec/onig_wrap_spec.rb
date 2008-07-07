
require 'spec/spec_helper'

describe Oniguruma::Regex, "creation" do
  it "initializes all ok" do
    Oniguruma::Regex.make1("dan").should be_an_instance_of(Oniguruma::Regex)
  end

  it "returns nil for bad regular expressions" do
    Oniguruma::Regex.make1("da(n").should be_nil
  end
end

describe Oniguruma::Regex, "matching" do
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
