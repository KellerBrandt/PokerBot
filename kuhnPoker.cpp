#include <iostream>
#include <random>
#include <stdio.h>
#include <unordered_map>
#include <vector>

class KuhnPoker {
  private:
	class Node {
	  private:
	  public:
		Node *parent, *left, *right; // left is pass, right is bet
		std::vector<int> regretSum, strategySum;
		int history; // 0 means you start, 1 means they pass, 2 means they bet
		int card;

		Node(int card, int history) {
			this->card = card;
			this->history = history;
			regretSum = {0, 0};
			strategySum = {0, 0};
		}
	};

  public:
	std::vector<int> cards;	  // 0: jack, 1: queen, 2: king
	std::vector<int> actions; // 0: pass, 1: bet
	std::mt19937 gen;
	std::unordered_map<int, Node> playerOneNodes, playerTwoNodes;
	int actionCount;

	KuhnPoker() {
		cards = {0, 1, 2};
		actions = {0, 1};
		gen = std::mt19937(std::random_device()());
		actionCount = 2;
	}

	std::vector<double> getStrategy(std::vector<int> regretSum) {
	}

	int getAction(std::vector<double> strategy) {
		return std::discrete_distribution<>(strategy.begin(), strategy.end())(gen);
	}

	int getReward() {
	}

	int getScore(int cardInd) {
		return cards[cardInd];
	}

	int cfr(Node &n) {
		
	}

	void playGame() {
		
	}

	void train(int iterations) {
		std::vector<double> strategy, oppStrategy;
		for (int i = 0; i < iterations; ++i) {
			playGame
		}
	}
};