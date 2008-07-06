
require 'spec/spec_helper'

describe Oniguruma::Regex, "creation" do
  it "initializes all ok" do
    Oniguruma::Regex.make("dan", Oniguruma::Option::NONE)
  end
end
