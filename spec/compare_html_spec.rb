
require 'spec/spec_helper'

describe "Comparison with HTML references" do
	Dir[File.dirname(__FILE__) + "/fixtures/test_case*"].each do |fn|
		it "#{fn.split("/").last} should match" do
			mv = Gtk::Mate::View.new
			mv.buffer = mb = Gtk::Mate::Buffer.new
			mb.text = File.read(fn)
			fn = fn.split("/").last
			mb.set_grammar_by_filename(fn)
			mv.set_theme_by_name("Twilight")
			fn =~ /test_case_(.*)\.(.*)/
			textmate_fn = File.dirname(__FILE__) + "/fixtures/textmate_#{$1}.html"
	    Gtk::Mate::Exporter.new(mv).to_html(fn).should == File.read(textmate_fn)
		end
	end
end
