

require 'spec/spec_helper'

describe Gtk::Mate::Matcher do
  def test_match(a, b)
    Gtk::Mate::Matcher.test_match(a, b)
  end
    
  describe "matching correctly" do
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

  describe "ranking correctly" do
    def test_rank(a, b, scope)
      Gtk::Mate::Matcher.test_rank(a, b, scope)
    end

    it "should rank two matches by their element depth" do
      test_rank("string", "ruby", "ruby string").should == "string"
    end

    it "should rank by element depth not by string depth" do
      test_rank("string", "quoted", "string.quoted").should == "string == quoted"
    end

    it "should rank two matches by the length of the match" do
      test_rank("string.quoted", "string", "string.quoted").should == "string.quoted"
    end

    it "should move up the element matches in case of a tie and check element depth" do
      test_rank("ruby string", "source string", "source ruby string").should == "ruby string"
      test_rank("source string", "ruby string", "source ruby string").should == "ruby string"
    end

    it "should move up the element matches in case of a tie and check match length" do
      test_rank("ruby string", "source.ruby string", "source.ruby string").should == "source.ruby string"
    end
  end
end
