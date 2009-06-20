
require 'spec/spec_helper'

describe Gtk::Mate::Theme do
  before(:all) do
    Gtk::Mate.load_themes
    @th = Gtk::Mate::Theme.themes.find{|t| t.name == "Twilight"}
  end
  
  it "knows where to find themes" do
    Gtk::Mate::Theme.theme_filenames.should include("./spec/../../../textmate/Themes/Twilight.tmTheme")
    Gtk::Mate::Theme.theme_filenames.should include("./spec/../../../textmate/Themes/Amy.tmTheme")
  end
  
  it "loads all themes" do
    Gtk::Mate::Theme.themes.find{|t| t.name == "Twilight"}.should_not be_nil
  end
  
  it "loads the global settings of the themes" do
    @th.global_settings["background"].should == "#141414"
  end
  
  it "loads the settings of the themes" do
    @th.settings[0].name.should == "Comment"
    @th.settings[0].settings["fontStyle"].should == "italic"
  end
end
