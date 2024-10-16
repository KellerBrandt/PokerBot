#include <iostream>
#include <random>
#include <stdio.h>
#include <vector>

class RPS {
  private:
  public:
	int numActions;
	std::vector<double> possibleActions, regretSum, strategySum, oppRegretSum, oppStrategySum;
	std::vector<std::vector<int>> actionUtility;
	std::mt19937 gen;

	RPS() {
		numActions = 3;
		possibleActions = {0, 1, 2};
		actionUtility = {{0, -1, 1},
						 {1, 0, -1},
						 {-1, 1, 0}};
		regretSum = {0, 0, 0};
		strategySum = {0, 0, 0};
		oppRegretSum = {0, 0, 0};
		oppStrategySum = {0, 0, 0};
		gen = std::mt19937(std::random_device()());
	}

	std::vector<double> getStrategy(std::vector<double> regretSum) {
		std::vector<double> newSum;
		double normalizingSum = 0;
		for (double i : regretSum)
			newSum.push_back(i * (i > 0)); // could be source of error
		for (double i : newSum)
			normalizingSum += i;
		if (normalizingSum > 0) {
			for (int i = 0; i < numActions; ++i)
				newSum[i] /= normalizingSum;
		} else {
			newSum = {1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0};
		}
		return newSum;
	}

	std::vector<double> getAverageStrategy(std::vector<double> strategySum) {
		std::vector<double> averageStrategy = {0, 0, 0};
		double normalizingSum = 0;
		for (double i : strategySum)
			normalizingSum += i;
		for (int i = 0; i < numActions; ++i) {
			if (normalizingSum > 0) {
				averageStrategy[i] = strategySum[i] / normalizingSum;
			} else {
				averageStrategy[i] = 1.0 / numActions;
			}
		}
		return averageStrategy;
	}

	double getAction(std::vector<double> strategy) {
		return std::discrete_distribution<>(strategy.begin(), strategy.end())(gen);
	}

	double getReward(int myAction, int oppAction) {
		return actionUtility[myAction][oppAction];
	}

	void train(int iterations) {
		std::vector<double> strategy, oppStrategy;
		for (int i = 0; i < iterations; ++i) {
			strategy = getStrategy(regretSum);
			oppStrategy = {1.0, 0, 0};
			for (int i = 0; i < numActions; ++i) {
				strategySum[i] += strategy[i];
				oppStrategySum[i] += oppStrategy[i];
			}
			double myAction = getAction(strategy);
			double oppAction = getAction(oppStrategy);

			double myReward = getReward(myAction, oppAction);
			double oppReward = getReward(oppAction, myAction);

			for (int i = 0; i < numActions; ++i) {
				regretSum[i] += getReward(i, oppAction) - myReward;
				oppRegretSum[i] += getReward(i, myAction) - oppReward;
			}
		}
	}
};

static void printVector(std::vector<double> vect) {
	for (double i : vect)
		std::cout << i << " ";
	std::cout << "\n";
}

static void train(RPS rps) {
	rps.train(1000000);
	std::vector<double> targetPolicy = rps.getAverageStrategy(rps.strategySum);
	std::vector<double> oppTargetPolicy = rps.getAverageStrategy(rps.oppStrategySum);

	std::cout << "Player 1 policy: ";
	printVector(targetPolicy);
	std::cout << "Player 2 policy: ";
	printVector(oppTargetPolicy);
	std::cout << "Player 1 regret sum: ";
	printVector(rps.regretSum);
	std::cout << "Player 2 regret sum: ";
	printVector(rps.oppRegretSum);
	std::cout << "Player 1 strategy sum: ";
	printVector(rps.strategySum);
	std::cout << "Player 2 strategy sum: ";
	printVector(rps.oppStrategySum);
}

/*
int main() {
	RPS rps;
	for (int i = 0; i < 1; ++i) {
		train(rps);
		std::cout << "\n";
	}
}
*/