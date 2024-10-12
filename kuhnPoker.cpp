#include <iostream>
#include <random>
#include <stdio.h>
#include <unordered_map>
#include <vector>

class KuhnPoker {
  private:
  public:
	std::vector<int> cards;	  // 0: jack, 1: queen, 2: king
	std::vector<int> actions; // 0: pass, 1: bet
  int actionCount;

	KuhnPoker() {
		cards = {0, 1, 2};
		actions = {0, 1};
    actionCount = 2;
	}

	std::vector<double> getStrategy(std::vector<int> regretSum) {
	}

	int getAction(std::vector<double> strategy) {
		//std::mt19937 gen(std::random_device()()); // optimization to be had here
		//return std::discrete_distribution<>(strategy.begin(), strategy.end())(gen);
	}

	int getReward() {
	}

	int getScore(int cardInd) {
		return cards[cardInd];
	}

  void cfr() {

  }

	void train(int iterations) {
    std::vector<double> strategy, oppStrategy;
    for (int i = 0; i < iterations; ++i) {

    }
	}

	class Node {
	  private:
	  public:
		std::vector<int> regretSum, strategySum;
    int history; //0 means they checked(passed), 1 means they bet
    int card;

		Node(int card, int history) {
      this.card = card;
      this.history = history;
      regretSum = {0, 0};
      strategySum = {0, 0};
    }
	};
};