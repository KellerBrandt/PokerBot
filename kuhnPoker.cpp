#include <iostream>
#include <random>
#include <stdio.h>
#include <vector>
#include <unordered_map>

class KuhnPoker {
  private:
  public:
  std::vector<int> cards; //0: jack, 1: queen, 2: king
  std::vector<int> actions; //0: fold, 1: check, 2: bet
  std::vector<std::vector<std::vector<int>>> regret, oppRegret, strategySum, oppStrategySum;

  KuhnPoker() {
    cards = {0, 1, 2};
    actions = {0, 1, 2};
    regret = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};
  }

  std::vector<int> getStrategy(std::vector<double> regretSum) {
    
	}

	int getAction(std::vector<double> strategy) {
		std::mt19937 gen(std::random_device()); //optimization to be had here
		return std::discrete_distribution<>(strategy.begin(), strategy.end())(gen);
	}

	int getReward() {

	}

	void train() {

	}
};