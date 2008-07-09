

describe Gtk::MateView, "initialization" do
  it "returns textmate_share_dir" do
    Gtk::MateView.textmate_share_dir.should =~ /\/usr\/local\/(share\/)?textmate/
  end

  it "returns a list of bundle_dirs" do
    Gtk::MateView.bundle_dirs_rb.should include("Ruby.tmbundle")
    Gtk::MateView.bundle_dirs_rb.should include("Python.tmbundle")
    Gtk::MateView.bundle_dirs_rb.should_not include(".svn")
  end

  it "should load bundles" do
    Gtk::MateView.load_bundles
  end
end

describe Gtk::MateView do
  before(:each) do
    @mv = Gtk::MateView.new
    @mv.buffer = Gtk::SourceBuffer.new
  end

  it "sets the grammar by extension" do
    @mv.set_grammar_by_extension("rb").should == "Ruby"
    @mv.set_grammar_by_extension("py").should == "Python"
  end

  it "sets the grammar by first line" do
    @mv.buffer.text = "#!/usr/bin/ruby\nfoo"
    @mv.set_grammar_by_extension("").should == "Ruby"
    @mv.buffer.text = "#!/usr/bin/dmd \nfoo"
    @mv.set_grammar_by_extension("").should == "D"
  end
end
