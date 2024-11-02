#include <algorithm>
#include <iostream>
#include <random>
#include <set>
#include <stdio.h>
#include <unordered_map>
#include <vector>

/*
deck:
0-51
ranks = {0: 2, 1: 3, 2: 4, 3: 5, 4: 6, 5: 7, 6: 8, 7: 9, 8: T, 9: J, 10: Q, 11: K, 12: A}
suits = {0: C, 1: D, 2: H, 3: S}
num%13 = rank
num/13 = suit

dealer stands on 17+

blackjack beats anything other than a blackjack

ways a game ends:
player stands
player hits and then busts
player doubles down then busts
player hits to 21
player doubles to 21
player has blackjack at start
*/

class Node {
	std::vector<double> strategySum;
	std::vector<double> strategy;
	std::vector<double> cfrSum;
	int history; // 1: check, 2: bet, 3: chance
	int card;
};

std::unordered_map<int, Node> nodes;

// 1: Hit, 2: Stand, 3: Double down, 4: Split
int actions[] = {1, 2, 3, 4};
int cardValues[] = {};

Node getNode() {
	return Node();
}

int getScore() {
	return 0;
}

bool isTerminal(int history, int player) {
	if (player >= 21) {
		return true;
	}
	return history % 10 == 2;
}

double cfr(int history, int player, int dealer, int hidden, int deck[], double probability) {
	if (isTerminal(history, player)) {
		return getScore();
	}
	return 0;
}

double cfr() {
	std::set<int> set;
	int output = 0;
	int player = 0;
	int dealer = 0;
	int deck[13]; // only one deck used, later try with 8 decks

	for (int i = 0; i < sizeof(deck); ++i) {
		deck[i] = 4;
	}
}

void getFrequencies() {

	for (int i = 0; i < 52; ++i) {
		for (int j = 0; j < 51; ++j) {
			for (int k = 0; k < 50; ++k) {
				for (int l = 0; l < 49; ++l) {
                    
				}
			}
		}
	}
}

double train(int iterations) {
	double output = 0;
	for (int i = 0; i < iterations; ++i) {
		output += cfr();
	}
	return output / iterations;
}

int main() {
	int iterations = 1000;
	// train(iterations);
	cfr();
	int p[] = {1, 2, 3, 4};
	for (int i : p) {
		std::cout << i << std::endl;
	}
	return 0;
}