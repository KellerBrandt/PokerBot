#include <algorithm>
#include <iostream>
#include <random>
#include <stdio.h>
#include <unordered_map>
#include <vector>

/*
N: {0, 1}
H: {33, 331, 332, 3311, 3312, 3321, 3322, 33121, 33122}
Z: {3311, 3321, 3322, 33121, 33122}
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
	double reachProbability, reachProbabilitySum;
	int history; // 1: check, 2: bet, 3: chance
	int card;

	GameState(int history, int card) : history(history), card(card) {
		strategySum = {0, 0};
		strategy = {1.0 / 2.0, 1.0 / 2.0};
		cfrSum = {0, 0};
		reachProbability = 0; // might delete
		reachProbabilitySum = 0;
	}

	GameState() {
	}

	void updateStrategy() {
		reachProbabilitySum += reachProbability;
		reachProbability = 0;
		for (int i = 0; i < 2; ++i) {
			strategySum[i] += strategy[i];
		}

		double total = 0;
		for (double i : cfrSum) {
			if (i > 0) {
				total += i;
			}
		}
		if (total == 0) {
			strategy = {1.0 / 2.0, 1.0 / 2.0};
		} else {
			for (int i = 0; i < 2; ++i) {
				if (cfrSum[i] > 0) {
					strategy[i] = cfrSum[i] / total;
				} else {
					strategy[i] = 0;
				}
			}
		}
	}

	int getPlayer() {
		if (history == 0 || history == 3) {
			return -1; // no player
		}
		return std::to_string(history).length() % 2; // if the history length is even, it is pA's turn, if it is odd, it is pB's turn
	}

	std::string toString() {
		std::string returnString;
		int sum = strategySum[0] + strategySum[1];
		returnString += std::to_string(card) + " ";
		if (history == 33) {
			returnString += std::to_string(history) + "   ";
		} else {
			returnString += std::to_string(history) + " ";
		}
		if (sum == 0) {
			returnString += std::to_string((double)1 / 2) + " " + std::to_string((double)1 / 2);
		} else {
			returnString += std::to_string((double)strategySum[0] / sum) + " " + std::to_string((double)strategySum[1] / sum);
		}
		// returnString += std::to_string((double)strategySum[0]) + " " + std::to_string((double)strategySum[1]);

		return returnString;
	}
};

class KuhnPoker {
  public:
	std::unordered_map<int, GameState> gameStates;
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

		for (int i : {33, 331, 332, 3312}) {
			gameStates[getKey(i, 0)] = GameState(i, 0);
			gameStates[getKey(i, 1)] = GameState(i, 1);
			gameStates[getKey(i, 2)] = GameState(i, 2);
		}
	}

	void shuffleCards() {
		std::shuffle(cards.begin(), cards.end(), gen);
	}

	bool isTerminalHistory(int history) {
		if (history == 3311 || history > 3312) {
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

	int getKey(int history, int card) {
		return history * 10 + card;
	}

	// utility function
	int getUtility(int history, int pAcard, int pBcard) {
		int currentPlayerCard, opponentCard;
		if (getPlayer(history) == 0) {
			currentPlayerCard = pAcard;
			opponentCard = pBcard;
		} else {
			currentPlayerCard = pBcard;
			opponentCard = pAcard;
		}
		if (history % 10 == 1) {
			if (history == 3311) {
				if (currentPlayerCard > opponentCard) {
					return 1;
				} else {
					return -1;
				}
			}
			return 1;
		}
		if (currentPlayerCard > opponentCard) {
			return 2;
		}
		return -2;
	}

	// return the utility of a given node, maybe
	double cfr(int history, double pAprob, double pBprob, double chance, int pAcard, int pBcard) {
		if (isTerminalHistory(history)) {
			return getUtility(history, pAcard, pBcard);
		}

		int currentPlayer = getPlayer(history);
		int currentCard = (!currentPlayer) * pAcard + currentPlayer * pBcard;

		GameState &currentGameState = gameStates[getKey(history, currentCard)]; // should work, just marking incase there is an error
		std::vector<double> strategy = currentGameState.strategy;

		double currentCFUtil;
		double checkCFUtil;
		double betCFUtil;

		double currentProb = currentPlayer * pAprob + (!currentPlayer) * pBprob;

		if (!currentPlayer) {
			checkCFUtil = -1 * cfr(history * 10 + 1, pAprob * strategy[0], pBprob, chance, pAcard, pBcard);
			betCFUtil = -1 * cfr(history * 10 + 2, pAprob * strategy[1], pBprob, chance, pAcard, pBcard);
		} else {
			checkCFUtil = -1 * cfr(history * 10 + 1, pAprob, pBprob * strategy[0], chance, pAcard, pBcard);
			betCFUtil = -1 * cfr(history * 10 + 2, pAprob, pBprob * strategy[1], chance, pAcard, pBcard);
		}

		currentCFUtil = (checkCFUtil * strategy[0] + betCFUtil * strategy[1]);

		currentGameState.cfrSum[0] += chance * currentProb * (checkCFUtil - currentCFUtil);
		currentGameState.cfrSum[1] += chance * currentProb * (betCFUtil - currentCFUtil);

		return currentCFUtil;
	}

	void train(int iterations) {
		double output = 0;
		double gameUtility = 0;
		for (int x = 0; x < iterations; ++x) {
			// shuffleCards();
			for (int i = 0; i < cards.size(); ++i) {
				for (int j = 0; j < cards.size(); ++j) {
					if (i != j) {
						gameUtility += cfr(33, 1, 1, 1.0 / 6.0, i, j);
					}
				}
			}
			gameUtility /= 6.0;
			output += gameUtility;
			gameUtility = 0;

			// cfr(33, 1, 1, 1.0 / 6.0, 0, 1);
			for (auto &pair : gameStates) {
				pair.second.updateStrategy();
			}
		}
		std::cout << "output: " << output / iterations << "\n";
	}
};

bool comp(GameState a, GameState b) {
	int playerA = a.getPlayer(), playerB = b.getPlayer();
	if (playerA == playerB) {
		if (a.card == b.card) {
			return a.history < b.history;
		} else {
			return a.card < b.card;
		}
	}
	return playerA < playerB;
}

// might need fixing
int main() {
	KuhnPoker kp;
	kp.train(1000000);
	int count = 0;
	std::vector<GameState> nodes;
	for (auto &pair : kp.gameStates) {
		nodes.push_back(pair.second);
		++count;
	}
	std::sort(nodes.begin(), nodes.end(), comp);

	std::cout << "Player 1:\n";
	for (int i = 0; i < count / 2; ++i) {
		std::cout << nodes[i].toString() << "\n";
	}
	std::cout << "\n";

	std::cout << "Player 2:\n";
	for (int i = count / 2; i < count; ++i) {
		std::cout << nodes[i].toString() << "\n";
	}
	std::cout << "\n";

	std::cout << "Count: " << count << "\n";
	std::cout << "Time: " << (double)clock() / CLOCKS_PER_SEC << "\n";

	return 0;
}

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
0 p    ['0.66', '0.34']
0 b    ['1.00', '0.00']
1 p    ['1.00', '0.00']
1 b    ['0.64', '0.36']
2 p    ['0.00', '1.00']
2 b    ['0.00', '1.00']
*/