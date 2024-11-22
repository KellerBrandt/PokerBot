#include <algorithm>
#include <iostream>
#include <random>
#include <stdio.h>
#include <unordered_map>
#include <vector>

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

std::unordered_map<int, std::vector<int>> nodes;

//possible idea: abstract out the suits and make just an int[] with the counts of each rank
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
                    cfr(std::vector<int>{i, j, a, b}, std::vector<int>{i, j}, std::vector<int>{a, b}, 1.0 / total, 1.0);
                }
            }
        }
    }
}

/*
the deck of cards, the players cards, the dealers cards
*/
double cfr(std::vector<int> usedCards, std::vector<int> player, std::vector<int> dealer, double chance, double playerPercent) {

}

void makeDeck(int (&deck)[]) {
	for (int i = 0; i < 52; ++i) {
		deck[i] = i;
	}
	std::random_shuffle(&deck[0], &deck[51]);
}

std::vector<int> makeDeck(int deckSize) {
    std::vector<int> deck;
    for (int i = 0; i < deckSize; ++i) {
        deck.push_back(i);
    }
    return deck;
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