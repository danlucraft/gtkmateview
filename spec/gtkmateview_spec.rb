

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
