
require 'spec/spec_helper'

describe "Comparison with HTML references" do
	YAML.load(File.read(File.dirname(__FILE__) + "/fixtures/test_cases.yml")).each do |hash|
		it "#{hash[:file]} should match" do
			fn = hash[:file]
			theme = hash[:theme]
			mv = Gtk::Mate::View.new
			mv.buffer = mb = Gtk::Mate::Buffer.new
			mb.text = File.read(File.dirname(__FILE__) + "/fixtures/#{fn}")
			mb.set_grammar_by_filename(fn)
			mv.set_theme_by_name(theme)
			fn =~ /test_case_(.*)\.(.*)/
			textmate_fn = File.dirname(__FILE__) + "/fixtures/textmate_#{$1}.html"
	    redcar_html = Gtk::Mate::Exporter.new(mv).to_html(fn)
			File.open(File.dirname(__FILE__) + "/fixtures/redcar_#{$1}.html", "w") {|fout| fout.puts redcar_html}
			redcar_html.should == File.read(textmate_fn)
		end
	end
end
