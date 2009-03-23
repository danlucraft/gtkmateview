
class Redcar < Editor
  include Textmate
  include Ruby
  
  def initialize(files)
    open_window("Redcar")
    files.each { |file| open_file(file, :tab => true) }
    ARGV.each do |fn|
      if File.exist?(fn)
        open_file(fn)
      end
    end
    welcome = <<-HTML
      <h1>Redcar</h1>
      <p>Programmer's editor for GNOME</p>
    HTML
  end
end
