# backport_dig [![Build Status](https://travis-ci.org/koic/backport_dig.svg)](https://travis-ci.org/koic/backport_dig)

backport_dig is the backport of Hash#dig and Array#dig in Ruby 2.3.0 to older Ruby versions.

The best way is to use Ruby 2.3.0 or later. Because you can use original dig methods and so on.

## Ruby 2.3 incompatible

* Struct#dig is not supported

## Synopsis

```ruby
h = {foo: {bar: {baz: 1}}}
h.dig(:foo, :bar, :baz) #=> 1

a = [[1, [2, 3]]]
a.dig(0, 1, 1) #=> 3
```

## Supported Versions

* Ruby 2.0
* Ruby 2.1
* Ruby 2.2

## INSTALL

Add these lines to your application's Gemfile:

```
gem 'backport_dig'
```

And then execute:

```
$ bundle
```

Or install it yourself as:

```
$ gem install backport_dig
```

And require it as:

```
require 'backport_dig'
```

## Special Thanks

* Ruby Development Team
* Pay homage to [ruby_dig](https://rubygems.org/gems/ruby_dig)

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request

## License

backport_dig is released under the [MIT License](http://www.opensource.org/licenses/MIT).
