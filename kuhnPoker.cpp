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
	std::vector<double> regretSum;
	std::vector<double> strategy;
	double reachProbability; // maybe include the chance actions that distribute the cards
	int history;
};

class KuhnPoker {
  public:
	std::vector<int> actions;
	std::vector<int> cards;
	int playerCount;
	int actionCount;

	KuhnPoker() {
		actions = {1, 2};  // 1: check, 2: bet
		cards = {0, 1, 2}; // 0: jack, 1: queen, 2: king
		playerCount = 2;   // 0: pA, 1: pB
		actionCount = 2;
	}

	bool isTerminalHistory(int history) {
		if (history == 11 || history > 12) {
			return true;
		}
		return false;
	}

	// P function
	int getPlayer(int history) {
		if (history == 0) {
			return 0;
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
};

int main() {
	return 0;
}