#include <algorithm>
#include <iostream>
#include <random>
#include <stdio.h>
#include <unordered_map>
#include <vector>

/*
N: {0, 1}
A: {1, 2, 3, 4}
*/

class GameState {
  public:
	int history; 

	GameState() {}
};

class Poker {
  public:
	const double chance;
    const int actions[3]; //1: check, 2: call, 3: raise, 4: fold

	Poker() : chance(0.0), actions{1, 2, 3} {}

	int scoreHand(int hand[2], int commCards[5]) {
		return 0;
	}

	double cfr(int history, double paProb, double pbProb, int paHand[2], int pbHand[2], int commCards[5]) {}
	void train(int iterations) {}
};

int main() {
	return 0;
}