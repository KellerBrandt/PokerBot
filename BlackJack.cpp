#include <algorithm>
#include <iostream>
#include <random>
#include <stdio.h>
#include <unordered_map>
#include <vector>

class Node {
  public:
	std::vector<double> strategySum;
	std::vector<double> strategy;
	std::vector<double> regretSum;
    bool isDefault;
	// may be useless
	std::vector<int> player;
	int dealer;

	Node(std::vector<int> player, int dealer) : player(player), dealer(dealer) {
		strategySum = {0, 0};
		strategy = {1.0 / 2.0, 1.0 / 2.0};
		regretSum = {0, 0};
        isDefault = false;
	}

    Node() {
        isDefault = true;
    }

	// check later
	void updateStrategy() {
		for (int i = 0; i < 2; ++i) {
			strategySum[i] += strategy[i];
		}

		double total = 0;
		for (double i : regretSum) {
			if (i > 0) {
				total += i;
			}
		}
		if (total == 0) {
			strategy = {1.0 / 2.0, 1.0 / 2.0};
		} else {
			for (int i = 0; i < 2; ++i) {
				if (regretSum[i] > 0) {
					strategy[i] = regretSum[i] / total;
				} else {
					strategy[i] = 0;
				}
			}
		}
	}
};

/*
Clubs, Diamonds, Hearts, Spades
0-12   13-25     26-38   39-51
%13 = rank
/13 = suit
*/
int cardsLeft = 52;

/*
0: stad, 1: hit
*/
int actions[2] = {0, 1};

std::unordered_map<int, Node> nodes;

int primes[13] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 41, 43};
int suits[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

// possible idea: abstract out the suits and make just an int[] with the counts of each rank
double cfr() {
	int deckSize = 52;
	double total = 6497400; // 52 * 51 * 50 * 49

	for (int i = 0; i < deckSize; ++i) {
		for (int j = 0; j < deckSize; ++i) {
			if (j == i) {
				continue;
			}
			for (int a = 0; a < deckSize; ++a) {
				if (a == i || a == j) {
					continue;
				}
				for (int b = 0; b < deckSize; ++b) {
					if (b == i || b == j || b == a) {
						continue;
					}
					// possible error source, reducing cards to their suits
					cfr(std::vector<int>{i, j, a, b}, std::vector<int>{i % 13, j % 13}, std::vector<int>{a % 13, b % 13}, 1.0 / total, 1.0);
				}
			}
		}
	}
}

/*
the deck of cards, the players cards, the dealers cards
*/
double cfr(std::vector<int> usedCards, std::vector<int> player, std::vector<int> dealer, double chance, double playerPercent) {
    if (isTerminal(player)) {
        return getReward(player, dealer);
    }
    int key = getKey(player, dealer[0]);
    Node &node = nodes[key]; //dealer 0 is the revealed card
    if (node.isDefault) {
        nodes[key] = Node(player, dealer[0]);
    }

    
}

// possible error source
int getKey(std::vector<int> cards, int dealer) {
	int key = 1;
	key *= primes[dealer % 13];
	for (int i : cards) {
		key *= primes[i % 13];
	}
	return key;
}

bool isTerminal(std::vector<int> player) {
    int sum = 0;
    int aceCount = 0;
    for (int i : player) {
        sum += suits[i];
        aceCount += (i == 12);
    }
}

double getReward(std::vector<int> player, std::vector<int> dealer) {

}

double train(int iterations) {
	double value = 0;
	for (double i = 0; i < iterations; ++i) {
		value += cfr();
	}
	return value / iterations;
}

int main() {
	return 0;
}