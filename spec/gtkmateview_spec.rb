

describe Gtk::Mate::View, "initialization" do
  it "returns textmate_share_dir" do
    Gtk::Mate.textmate_share_dir.should =~ /\/usr\/local\/(share\/)?textmate/
  end

  it "returns a list of bundle_dirs" do
    Gtk::Mate.bundle_dirs.should include("Ruby.tmbundle")
    Gtk::Mate.bundle_dirs.should include("Python.tmbundle")
    Gtk::Mate.bundle_dirs.should_not include(".svn")
  end

  it "should load bundles" do
    Gtk::Mate.load_bundles
  end
end
