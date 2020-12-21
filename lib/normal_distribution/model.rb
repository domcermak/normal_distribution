# frozen_string_literal: true

module NormalDistribution
  # Model class of normal distribution
  #
  # @since 0.1.0
  class Model
    # @!parse [ruby]
    #
    #   # @return [Float] mean of data contained in model
    #   attr_reader :mean
    #
    #   # @return [Float] standard deviation of data contained in model
    #   attr_reader :standard_deviation
    #
    #   # Initializes normal distribution model from given data
    #   #
    #   # @param values [Array<Numeric>] non-empty array of numbers representing data for normal distribution construction
    #   def initialize(values)
    #      # This is stub used for indexing
    #   end
    #
    #   # Calculates confidence interval for given percentage
    #   #
    #   # @param percentage [Numeric] a number in interval <0, 100> representing probability
    #   # @return [Array<Float>] an array containing 2 values, lower bound and upper_bound of confidence interval
    #   #
    #   # @since 0.2.0
    #   def confidence_interval(percentage)
    #      # This is stub used for indexing
    #   end
  end
end
