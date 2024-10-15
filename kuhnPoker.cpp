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
		bool isShowdown;

		Node(int card, int history, bool isShowdown) {
			this->card = card;
			this->history = history;
			regretSum = {0, 0};
			strategySum = {0, 0};
			this->isShowdown = isShowdown;
		}

		static void exploreTree(Node &n) {
			n.left = new Node(n.card, n.history, n.isShowdown);
			n.right = new Node(n.card, n.history, n.isShowdown);
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

		for (int i = 0; i < 3; ++i) {
			p1Nodes[i] = Node(i, 0, false);
			Node::exploreTree(p1Nodes[i]);
			for (int j = 0; j < 2; ++j) {
				p2Nodes[2 * i + j] = Node(i, j + 1, false);
				Node::exploreTree(p2Nodes[2 * i + j]);
			}
		}
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

	std::vector<int> dealCards() {

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
		Node p1Node = p1Nodes[p1Card];
		Node p2Node = p2Nodes[p2Card];
		std::vector<double> p1Strategy = getStrategy(p1Node.regretSum);

		if (getAction(p1Strategy)) { //if p1 bet
			if () {

			}
		} else {

		}
	}

	void train(int iterations) {
		std::vector<double> strategy, oppStrategy;
		for (int i = 0; i < iterations; ++i) {
			std::vector<int> cards = dealCards();
			int p1Card = cards[1];
			int p2Card = cards[2];
			playGame(p1Card, p1Card);
			cfr(p1Nodes[p1Card]);
			cfr(p2Nodes[p2Card]);
		}
	}
};