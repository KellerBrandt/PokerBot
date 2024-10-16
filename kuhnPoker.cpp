#include <iostream>
#include <random>
#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <algorithm>

class KuhnPoker {
  private:
	class Node {
	  private:
	  public:
		Node *parent, *left, *right; // left is pass, right is bet
		std::vector<int> regretSum, strategySum;
		int history; // 0 means you start, 1 means they pass, 2 means they bet
		int card;
		bool isShowdown;

		Node(int card, int history, bool isShowdown) {
			this->card = card;
			this->history = history;
			regretSum = {0, 0};
			strategySum = {0, 0};
			this->isShowdown = isShowdown;
		}
	};

  public:
	std::vector<int> cards;	  // 0: jack, 1: queen, 2: king
	std::vector<int> actions; // 0: pass, 1: bet
	std::mt19937 gen;
	std::unordered_map<int, Node> p1Nodes, p2Nodes;
	int actionCount;

	KuhnPoker() {
		cards = {0, 1, 2};
		actions = {0, 1};
		gen = std::mt19937(std::random_device()());
		actionCount = 2;
	}

	std::vector<double> getStrategy(std::vector<int> regretSum) {
		std::vector<double> newSum;
		double normalizingSum = 0;
		for (double i : regretSum)
			newSum.push_back(i * (i > 0)); // could be source of error
		for (double i : newSum)
			normalizingSum += i;
		if (normalizingSum > 0) {
			for (int i = 0; i < actionCount; ++i)
				newSum[i] /= normalizingSum;
		} else {
			newSum = {1.0 / actionCount, 1.0 / actionCount};
		}
		return newSum;
	}

	int getAction(std::vector<double> strategy) {
		return std::discrete_distribution<>(strategy.begin(), strategy.end())(gen);
	}

	int getReward() {
	}

	int getScore(int cardInd) {
		return cards[cardInd];
	}

	int cfr(Node &node) {
	}

	void shuffleDeck() {
		std::shuffle(cards.begin(), cards.end(), gen);
	}

	/*
	p1 check or bet:
	check:
		p2 check or bet:
		check:
			showdown
		bet:
			p1 check or bet:
			check:
				p2 wins
			bet:
				showdown
	bet:
		p2 check or bet:
		check:
			p1 wins
		bet:
			showdown
	*/

	void playGame(int p1Card, int p2Card) {
		
	}

	void train(int iterations) {
		std::vector<double> strategy, oppStrategy;
		for (int i = 0; i < iterations; ++i) {
			
		}
	}

	Node getNode(int card, int history) {

	}
};

/*
Expected results:
player 1 strategies:
0      ['0.79', '0.21']
0 pb   ['1.00', '0.00']
1      ['0.98', '0.02']
1 pb   ['0.45', '0.55']
2      ['0.36', '0.64']
2 pb   ['0.00', '1.00']

player 2 strategies:
0 b    ['1.00', '0.00']
0 p    ['0.66', '0.34']
1 b    ['0.64', '0.36']
1 p    ['1.00', '0.00']
2 b    ['0.00', '1.00']
2 p    ['0.00', '1.00']
*/