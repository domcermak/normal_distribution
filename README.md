# NormalDistribution

This gem was created to serve for anomalous values detection in data using normal distribution.

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'normal_distribution'
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install normal_distribution

## Usage

```ruby
data = [1, 1.5, 1.8, 1.9, 2, 2.1, 2, 2.3, 2.7, 2.9, 3.1]
model = NormalDistribution::Model.new data

percentage = 95
bottom, top = model.confidence_interval(percentage)

potential_anomaly = 3.0
if bottom > potential_anomaly or top < potential_anomaly  
    puts "#{ potential_anomaly } is in group of rarest 5 %. Therefore, it's an anomaly"
end
```

## Development

After checking out the repo, run `bin/setup` to install dependencies. Then, run `rake spec` to run the tests. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and tags, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/[USERNAME]/normal_distribution. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [Contributor Covenant](http://contributor-covenant.org) code of conduct.

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

## Code of Conduct

Everyone interacting in the NormalDistribution project’s codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/[USERNAME]/normal_distribution/blob/master/CODE_OF_CONDUCT.md).
