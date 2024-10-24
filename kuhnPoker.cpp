#include <algorithm>
#include <iostream>
#include <random>
#include <stdio.h>
#include <unordered_map>
#include <vector>

/*
N: {0, 1}
H: {0, 1, 2, 11, 12, 21, 22, 121, 122}
Z: {11, 21, 22, 121, 122}
A: {1, 2}

pA:
	bet: 2
		pB:
			bet: 22
				showdown for 2
			check: 21
				pA wins 1
	check: 1
		pB:
			bet: 12
				pA:
					bet: 122
						showdown for 2
					check: 121
						pB wins 1
			check: 11
				showdown for 1
*/

class GameState {
  public:
	std::vector<double> strategySum;
	std::vector<double> strategy;
	std::vector<double> cfrSum;
	double reachProbability; // maybe include the chance actions that distribute the cards
	int history;			 // 1: check, 2: bet, 3: chance

	GameState(double rp, int history) : reachProbability(rp), history(history) {
		strategySum = {0, 0};
		strategy = {1.0 / 2.0, 1.0 / 2.0};
		cfrSum = {0, 0};
	}

	void updateStrategy() {
	}
};

class KuhnPoker {
  public:
	std::vector<int> actions;
	std::vector<int> cards;
	std::mt19937 gen;
	int playerCount;
	int actionCount;

	KuhnPoker() {
		actions = {1, 2};  // 1: check, 2: bet
		cards = {0, 1, 2}; // 0: jack, 1: queen, 2: king
		gen = std::mt19937(std::random_device()());
		playerCount = 2; // 0: pA, 1: pB
		actionCount = 2;
	}

	void shuffleCards() {
		std::shuffle(cards.begin(), cards.end(), gen);
	}

	bool isTerminalHistory(int history) {
		if (history == 11 || history > 12) {
			return true;
		}
		return false;
	}

	bool isChance(int history) {
		if (history == 0 || history == 3) {
			return true;
		}
		return false;
	}

	// P function
	int getPlayer(int history) {
		if (history == 0 || history == 3) {
			return -1; // no player
		}
		return std::to_string(history).length() % 2; // if the history length is even, it is pA's turn, if it is odd, it is pB's turn
	}

	// utility function
	int getUtility(int history) {
		int player = getPlayer(history);
		if (history % 10 == 1) {
			if (history == 11) {
				if (cards[player] > cards[!player]) {
					return 1;
				} else {
					return -1;
				}
			}
			return 1;
		}
		if (cards[player] > cards[!player]) {
			return 2;
		}
		return -2;
	}

	// return the utility of a given node, maybe
	double cfr(int history, int pAprob, int pBprob) {
		if (isChance(history)) {
			// call 3 cfr, one for each card
		}
		if (isTerminalHistory(history)) {
			return getUtility(history);
		}
	}

	void train(int iterations) {
		for (int i = 0; i < iterations; ++i) {
			shuffleCards();
			cfr(0, 1, 1);
		}
	}
};

int main() {
	return 0;
}