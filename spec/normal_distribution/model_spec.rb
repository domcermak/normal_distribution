# frozen_string_literal: true

module NormalDistribution
  RSpec.describe Model do
    it 'has a version number' do
      expect(NormalDistribution::VERSION).not_to be nil
    end

    context 'with successful evaluation' do
      let(:data) { [ 1, 2, 2, 3, 3, 3, 4, 4, 5 ] }

      subject { Model.new data }

      it 'calculates correctly mean of data' do
          expect(subject.mean).to eq 3
      end

      it 'calculates correctly standard deviation of data' do
          expect(subject.standard_deviation).to be_within(0.0001).of(1.1547)
      end

      it 'calculates correctly confidence interval' do
        bottom, top = subject.confidence_interval(95)

        expect(bottom).to be_within(0.0001).of(2.2456)
        expect(top).to be_within(0.0001).of(3.7543)
      end
    end
  end
end