# frozen_string_literal: true

RSpec.describe NormalDistribution::ConfidenceInterval do
  describe 'functionality' do
    context 'with success' do
      it 'correctly returns given bounds' do
        interval = NormalDistribution::ConfidenceInterval.new -2.1, 4.4

        expect(interval).to have_attributes lower_bound: -2.1,
                                            upper_bound: 4.4
      end

      it 'includes value between bounds' do
        interval = NormalDistribution::ConfidenceInterval.new -2.1, 4.4

        expect(interval.include?(0.1)).to eq true
      end

      it 'does not include value between bounds' do
        interval = NormalDistribution::ConfidenceInterval.new -2.1, 4.4

        expect(interval.include?(4.41)).to eq false
      end
    end

    context 'with raised error' do
      it 'raises type error when lower bound is not a number' do
        expect {
          NormalDistribution::ConfidenceInterval.new 'hello', 4.4
        }.to raise_error TypeError, 'no implicit conversion to float from string'
      end

      it 'raises type error when upper bound is not a number' do
        expect {
          NormalDistribution::ConfidenceInterval.new -2.1, 'world'
        }.to raise_error TypeError, 'no implicit conversion to float from string'
      end

      it 'raises argument error when lower bound is greater then upper bound' do
        expect {
          NormalDistribution::ConfidenceInterval.new 4.0, 2.0
        }.to raise_error ArgumentError, 'lower bound must not be greater then upper bound'
      end

      it 'raises error when #include? non-numerical argument' do
        interval = NormalDistribution::ConfidenceInterval.new -2.1, 4.4

        expect { interval.include?('hello') }.to raise_error TypeError,
                                                             'no implicit conversion to float from string'
      end
    end
  end
end