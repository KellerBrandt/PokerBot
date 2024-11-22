#include <algorithm>
#include <iostream>
#include <random>
#include <stdio.h>
#include <unordered_map>
#include <vector>

/*
N: {0, 1}
A: {1, 2, 3, 4}

Toy games:
Flop texas hold em
Rhode island hold em
Leduc poker
*/

class GameState {
  public:
	int history;

	GameState() {}
};

class Poker {
  public:
	const double chance;
	const int actions[3]; // 1: check, 2: call, 3: raise, 4: fold
	int deck[52];

	Poker() : chance(0.0), actions{1, 2, 3} {
	}

	double cfr() {
		return 0;
	}
	double cfr(int history, double paProb, double pbProb, int paHand[2], int pbHand[2], int commCards[5]) {
		return 0;
	}
	void train(int iterations) {
		for (int i = 0; i < iterations; ++i) {
			double value = cfr();
		}
	}
};

/* int main() {
	return 0;
} */