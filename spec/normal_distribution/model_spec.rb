# frozen_string_literal: true

RSpec.describe NormalDistribution::Model do
  context 'with successful evaluation' do
    let(:data) { [1, 2, 2, 3, 3, 3, 4, 4, 5] }

    subject { NormalDistribution::Model.new data }

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
end