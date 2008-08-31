

require 'spec/spec_helper'

describe Gtk::Mate::Matcher do
  describe "matching correctly" do
    def test_match(a, b)
      Gtk::Mate::Matcher.test_match(a, b)
    end
    
    it "should match simple words" do
      test_match("comment", "ruby.comment").should be_true
      test_match("string", "ruby.comment").should be_false
      test_match("source.ruby", "source.ruby comment").should be_true
    end

    it "should transform .s" do
      test_match("source.ruby", "sourcearuby comment").should be_false
      test_match("source.ruby", "source.ruby comment").should be_true
    end

    it "should match at separate locations in the string" do
      test_match("ruby string", "ruby interpolated string.quoted").should be_true
    end

    it "should match with selector 'or's" do
      test_match("string, comment", "ruby.string").should be_true
      test_match("string, comment", "ruby.comment").should be_true
    end

    it "should deal with negative matches" do
      test_match("string - string.double", "ruby.string").should be_true
      test_match("string - string.double", "ruby.string.double").should be_false
    end

    it "should deal with multiple negative matches" do
      test_match("string - string.double - comment", "ruby.string.double").should be_false
      test_match("string - string.double - comment", "ruby.string.comment").should be_false
    end
  end
end
