# frozen_string_literal: true

RSpec.describe NormalDistribution::Model do
  subject { NormalDistribution::Model.new data }

  context 'with successful evaluation' do
    let(:data) { [1, 2, 2, 3, 3, 3, 4, 4, 5] }

    it 'calculates correctly mean of data' do
      expect(subject.mean).to eq 3
    end

    it 'calculates correctly standard deviation of data' do
      expect(subject.standard_deviation).to be_within(0.0001).of(1.1547)
    end

    it 'calculates correctly confidence interval' do
      bottom, top = subject.confidence_interval(95)

      expect(bottom).to be_within(0.0001).of(0.7368)
      expect(top).to be_within(0.0001).of(5.2631)
    end
  end

  context 'with failure' do
    context 'with invalid percentage value' do
      let(:data) { [1, 2, 3] }

      it 'raises error when greater then 100 %' do
        expect { subject.confidence_interval(101) }.to raise_error ArgumentError,
                                                                   'percentage must be between 0 and 100'
      end

      it 'raises error when lower then 0 %' do
        expect { subject.confidence_interval(-1) }.to raise_error ArgumentError,
                                                                  'percentage must be between 0 and 100'
      end

      it 'raises error when percentage is a string' do
        expect { subject.confidence_interval('invalid_type') }.to raise_error TypeError,
                                                                              'no implicit conversion to float from string'
      end
    end

    context 'with invalid type of data' do
      let(:data) { 'invalid_input' }

      it 'raises error' do
        expect { subject }.to raise_error TypeError, 'wrong argument type String (expected Array)'
      end
    end

    context 'with empty data' do
      let(:data) { [] }

      it 'raises error' do
        expect { subject }.to raise_error ArgumentError, 'data must not be empty'
      end
    end

    context 'with non-numerical array of data' do
      let(:data) { ['invalid_data'] }

      it 'raises error' do
        expect { subject }.to raise_error TypeError, 'no implicit conversion to float from string'
      end
    end
  end
end