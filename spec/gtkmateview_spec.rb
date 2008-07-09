

describe Gtk::Mate::View, "initialization" do
  it "returns textmate_share_dir" do
    Gtk::Mate.textmate_share_dir.should =~ /\/usr\/local\/(share\/)?textmate/
  end

  it "returns a list of bundle_dirs" do
    Gtk::Mate.bundle_dirs_rb.should include("Ruby.tmbundle")
    Gtk::Mate.bundle_dirs_rb.should include("Python.tmbundle")
    Gtk::Mate.bundle_dirs_rb.should_not include(".svn")
  end

  it "should load bundles" do
    Gtk::Mate.load_bundles
  end
end

describe Gtk::Mate::View do
  before(:each) do
    @mv = Gtk::Mate::View.new
    @mv.buffer = @mb = Gtk::Mate::Buffer.new
  end

  it "sets the grammar by extension" do
    @mb.set_grammar_by_extension("rb").should == "Ruby"
    @mb.set_grammar_by_extension("py").should == "Python"
  end

  it "sets the grammar by first line" do
    @mb.text = "#!/usr/bin/ruby\nfoo"
    @mb.set_grammar_by_extension("").should == "Ruby"
    @mb.text = "#!/usr/bin/dmd\nfoo"
    @mb.set_grammar_by_extension("").should == "D"
  end

  it "loads a grammar for use" do
  end
end
