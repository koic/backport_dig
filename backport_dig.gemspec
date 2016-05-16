$:.push File.expand_path('../lib', __FILE__)

require 'backport_dig/version'

Gem::Specification.new do |s|
  s.platform = Gem::Platform::RUBY
  s.name = 'backport_dig'
  s.summary = 'backport_dig is the backport of Hash#dig, Array#dig and OpenStruct#dig in Ruby 2.3 to older Ruby versions.'
  s.description = 'backport_dig is the backport of Hash#dig, Array#dig and OpenStruct#dig in Ruby 2.3 to older Ruby versions.'

  s.version = BackportDig::VERSION

  s.licenses = 'MIT'

  s.authors = ['Koichi ITO']
  s.email = 'koic.ito@gmail.com'
  s.homepage = 'https://github.com/koic/backport_dig'

  s.require_paths = ['lib']
  s.extensions = ['ext/backport_dig/extconf.rb']
  s.files = [
    'Manifest.txt',
    'README.md',
    'Rakefile',
    'ext/backport_dig/extconf.rb',
    'ext/backport_dig/backport_dig.c',
    'lib/backport_dig.rb',
    'lib/backport_dig/ostruct.rb'
  ]

  s.required_ruby_version = ['>= 2.0.0', '< 2.3.0']
  s.post_install_message = <<-EOS
backport_dig is the backport of Hash#dig, Array#dig and OpenStruct#dig in Ruby 2.3 to older Ruby versions.
The best way is to use Ruby 2.3 or later.
Thanks.
  EOS

  s.add_development_dependency('hoe')
  s.add_development_dependency('rake-compiler')
  s.add_development_dependency('rspec', '>= 3.0.0')
end
