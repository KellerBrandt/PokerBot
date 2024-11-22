#include <algorithm>
#include <iostream>
#include <random>
#include <stdio.h>
#include <unordered_map>
#include <vector>

/*
0: stand, 1: hit
*/
int actions[2] = {0, 1};

int primes[13] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 41, 43};
int suits[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

// whether or not the dealer stands on soft 17
bool standOnSeventeen = true;

// returns the score of a given hand
int getScore(std::vector<int> hand) {
	int score = 0;
	int aceCount = 0;

	for (int i : hand) {
		score += suits[i];
		aceCount += (i == 12);
	}

	for (int i = 0; i < aceCount; ++i) {
		if (score <= 21) {
			return score;
		}
		score -= 10;
	}

	return score;
}

// tie is currently counted as a loss
bool playerWins(std::vector<int> player, std::vector<int> dealer) {
	int playerScore = getScore(player);
	int dealerScore = getScore(dealer);

	if (playerScore > 21) {
		return false;
	}

	if (dealerScore > 21) {
		return true;
	}

	return playerScore > dealerScore;
}

// possible error source
bool dealerStand(std::vector<int> dealer) {
	int score = getScore(dealer);
	if (standOnSeventeen) {
		if (score >= 17) {
			return true;
		}
		return false;
	} else { // not implimented yet because not in use
	}
}

bool isBlackjack(std::vector<int> hand) {
	if (hand.size() > 2) {
		return false;
	}
	if (hand[0] + hand[1] == 21) {
		return true;
	}
	return false;
}

std::vector<double> standCounts(int deck[], std::vector<int> player, std::vector<int> dealer) {
	if (dealerStand(dealer)) {
		double playerWin = playerWins(player, dealer);
		return std::vector<double>{playerWin, 1};
	}

	std::vector<double> counts = {0.0, 0.0};

	// go through every possible card the dealer can get
	for (int i = 0; i < 13; ++i) {
		if (deck[i] > 0) {
			--deck[i];
			dealer.push_back(i);
			std::vector<double> temp = standCounts(deck, player, dealer);
			dealer.pop_back();
			++deck[i];
			// mult by the count of the card left to account for the number of times you could draw that card
			counts[0] += deck[i] * temp[0];
			counts[1] += deck[i] * temp[1];
		}
	}

	return counts;
}

// returns the win count [0] and total count [1], doesn't worry about blackjacks because they are accounted for in getWinRate
std::vector<double> getCounts(int deck[], std::vector<int> player, std::vector<int> dealer) {
	if (getScore(player) >= 21) {
		return standCounts(deck, player, dealer);
	}

	std::vector<double> counts = {0.0, 0.0};

	// if player stands
	std::vector<double> totals = standCounts(deck, player, dealer);
	counts[0] += totals[0];
	counts[1] = totals[1];

	// if player hits
	for (int i = 0; i < 13; ++i) {
		if (deck[i] > 0) {
			--deck[i];
			player.push_back(i);
			std::vector<double> temp = getCounts(deck, player, dealer);
			player.pop_back();
			++deck[i];
			// mult by the count of the card left to account for the number of times you could draw that card
			counts[0] += deck[i] * temp[0];
			counts[1] += deck[i] * temp[1];
		}
	}

	std::cout << "here" << std::endl;

	return counts;
}

// deck[] contains the count of each card left in the deck
double getWinRate(int deck[]) {
	std::vector<double> counts;
	for (int i = 0; i < 13; ++i) {
		if (deck[i] <= 0) {
			continue;
		}
		--deck[i];
		for (int j = 0; j < 13; ++j) {
			if (deck[j] <= 0) {
				continue;
			}
			--deck[j];
			for (int a = 0; a < 13; ++a) {
				if (deck[a] <= 0) {
					continue;
				}
				--deck[a];
				for (int b = 0; b < 13; ++b) {
					if (deck[b] <= 0) {
						continue;
					}
					--deck[b];

					std::vector<double> temp;

					bool playerBlackjack = isBlackjack(std::vector<int>{i, j});
					bool dealerBlackjack = isBlackjack(std::vector<int>{a, b});

					if (playerBlackjack) {
						if (dealerBlackjack) {
							temp = std::vector<double>{0.0, 1.0};
						}
						temp = std::vector<double>{1.0, 1.0};
					} else if (dealerBlackjack) {
						temp = std::vector<double>{0.0, 1.0};
					} else {
						temp = getCounts(deck, std::vector<int>{i, j}, std::vector<int>{a, b});
					}

					counts[0] += temp[0];
					counts[1] += temp[1];
					++deck[b];
					std::cout << "b: " << b << std::endl;
				}
				++deck[a];
				std::cout << "a: " << a << std::endl;
			}
			++deck[j];
			std::cout << "j: " << j << std::endl;
		}
		++deck[i];
		std::cout << "i: " << i << std::endl;
	}
	return counts[0] / counts[1];
}

// start by using lowest b for kelly criterion, b = 1; doesnt account for blackjacks 3:2 return
double getBetAmount(int deck[], double bankRoll) {
	double winRate = getWinRate(deck);
	double odds = 1.0 / 1.0;
	double percentBet = (winRate - (1 - winRate) / odds);
	return bankRoll * percentBet * (percentBet > 0);
}

int main() {
	double amount;
	int deck[13];

	for (int i = 0; i < 13; ++i) {
		deck[i] = 8;
	}

	amount = getBetAmount(deck, 100);

	std::cout << amount << std::endl;

	return 0;
}