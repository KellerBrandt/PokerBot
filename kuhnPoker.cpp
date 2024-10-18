#include <algorithm>
#include <iostream>
#include <random>
#include <stdio.h>
#include <unordered_map>
#include <vector>

class Node {
  private:
  public:
	std::vector<int> regretSum, strategySum;
	int history; // 1: pass, 2: bet, 0: nothing
	int card;
	int key;

	Node(int card, int history, int key) : card(card), history(history), key(key) {
		regretSum = {0, 0};
		strategySum = {0, 0};
	}

	Node() : card(-1), history(-1) {} // Default constructor

	int getPlayer() {
		int temp = key;
		while (temp / 10 > 0) {
			temp /= 10;
		}
		return temp;
	}

	std::string toString() {
		std::string returnString;
		int sum = strategySum[0] + strategySum[1];
		returnString += std::to_string(card) + " ";
		returnString += std::to_string(history) + " ";
		returnString += std::to_string((double) strategySum[0] / sum) + " " + std::to_string((double) strategySum[1] / sum);
		return returnString;
	}
};

class KuhnPoker {
  private:
  public:
	std::vector<int> cards;	  // 0: jack, 1: queen, 2: king
	std::vector<int> actions; // 1: pass, 2: bet
	std::mt19937 gen;
	std::unordered_map<int, Node> nodes;
	int actionCount;

	KuhnPoker() {
		cards = {0, 1, 2};
		actions = {1, 2};
		gen = std::mt19937(std::random_device()());
		actionCount = 2;
		// add the first three nodes
		nodes[getKey(0, 0, 0)] = Node(0, 0, getKey(0, 0, 0));
		nodes[getKey(0, 1, 0)] = Node(1, 0, getKey(0, 1, 0));
		nodes[getKey(0, 2, 0)] = Node(2, 0, getKey(0, 2, 0));
	}

	std::vector<double> getStrategy(std::vector<int> regretSum) {
		std::vector<double> newSum;
		double normalizingSum = 0;
		for (double i : regretSum)
			newSum.push_back(i * (i > 0));
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

	// returns action to take
	int getAction(std::vector<double> strategy) {
		return actions[std::discrete_distribution<>(strategy.begin(), strategy.end())(gen)];
	}

	// need implement
	int getReward() {
		return 0;
	}

	int getScore(int cardInd) {
		return cards[cardInd];
	}

	// need implement
	int cfr(Node &node) {
		return 0;
	}

	void shuffleDeck() {
		std::shuffle(cards.begin(), cards.end(), gen);
	}

	/*
	p1 check or bet:
	check: 1
		p2 check or bet:
		check: showdown 11
		bet:
			p1 check or bet:
			check: p2 wins 121
			bet: showdown 122
	bet: 2
		p2 check or bet:
		check: p1 wins 21
		bet: showdown 22
	*/

	void playGame() {
		shuffleDeck();
		Node *currentNode;
		std::vector<double> currentPlayerStrategy;
		int currentPlayerAction;
		int currentPlayer = 0; // 0 is p1, 1 is p2
		int history = 0;

		while (!(history == 11 || history > 12)) {
			int key = getKey(currentPlayer, cards[currentPlayer], history);
			if (nodes[key].card == -1) {
				nodes[key] = Node(cards[currentPlayer], history, key);
			}
			currentNode = &nodes[key];

			currentPlayerStrategy = getStrategy(currentNode->regretSum);
			currentPlayerAction = getAction(currentPlayerStrategy);
			history = history * 10 + currentPlayerAction;

			++currentNode->strategySum[currentPlayerAction - 1];

			currentPlayer = !currentPlayer;
		}
	}

	// keys: playerNumber cardNumber history concatenated in a single int
	int getKey(int player, int card, int history) {
		int exponent = (std::log10(history + 1)); // might be a source of time inneficiency
		return (player + 1) * std::pow(10, exponent + 2) + card * std::pow(10, exponent + 1) + history;
	}

	void train(int iterations) {
		for (int i = 0; i < iterations; ++i) {
			playGame();
		}
	}
};

bool comp(Node a, Node b) {
	int playerA = a.getPlayer(), playerB = b.getPlayer();
	if (playerA == playerB) {
		return a.card < b.card;
	}
	return playerA < playerB;
}

int main() {
	KuhnPoker kp;
	for (int i = 0; i < 100000; ++i) {
		kp.playGame();
	}
	int count = 0;
	std::vector<Node> nodes;
	for (auto &pair : kp.nodes) {
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
0 b    ['1.00', '0.00']
0 p    ['0.66', '0.34']
1 b    ['0.64', '0.36']
1 p    ['1.00', '0.00']
2 b    ['0.00', '1.00']
2 p    ['0.00', '1.00']
*/