#include <algorithm>
#include <iostream>
#include <random>
#include <stdio.h>
#include <unordered_map>
#include <vector>

class KuhnPoker {
  private:
	class Node {
	  private:
	  public:
		Node *parent, *left, *right; // left is pass, right is bet
		std::vector<int> regretSum, strategySum;
		int history; // 1: pass, 2: bet
		int card;

		Node(int card, int history) : card(card), history(history) {
			regretSum = {0, 0};
			strategySum = {0, 0};
		}

		Node() : card(-1), history(-1) {} // Default constructor
	};

  public:
	std::vector<int> cards;	  // 0: jack, 1: queen, 2: king
	std::vector<int> actions; // 1: pass, 2: bet
	std::mt19937 gen;
	// key: card number, followed by the history
	std::unordered_map<int, Node> p1Nodes, p2Nodes;
	int actionCount;

	KuhnPoker() {
		cards = {0, 1, 2};
		actions = {1, 2};
		gen = std::mt19937(std::random_device()());
		actionCount = 2;
		for (int i = 0; i < sizeof(cards); ++i) {
			p1Nodes.insert({getKey(i, 0), Node(i, 0)}); // p1 always starts, so no history
			for (int j = 0; j < actionCount; ++j) {
				p2Nodes.insert({getKey(i, j + 1), Node(i, j + 1)});
			}
		}
	}

	std::vector<double> getStrategy(std::vector<int> regretSum) {
		std::vector<double> newSum;
		double normalizingSum = 0;
		for (double i : regretSum)
			newSum.push_back(i * (i > 0)); // could be source of error
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

	int getAction(std::vector<double> strategy) {
		return std::discrete_distribution<>(strategy.begin(), strategy.end())(gen);
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
	check:
		p2 check or bet:
		check:
			showdown
		bet:
			p1 check or bet:
			check:
				p2 wins
			bet:
				showdown
	bet:
		p2 check or bet:
		check:
			p1 wins
		bet:
			showdown
	*/

	void playGame(int p1Card, int p2Card) {
		Node p1Node = p1Nodes[getKey(p1Card, 0)];

		std::vector<double> p1Strategy = getStrategy(p1Node.regretSum);

		std::cout << p1Strategy[0] << " " << p1Strategy[1] << "\n";
	}

	void train(int iterations) {
		std::vector<double> strategy, oppStrategy;
		for (int i = 0; i < iterations; ++i) {
			playGame(0, 1);
		}
	}

	// wrong
	int getKey(int card, int history) {
		int exponent = (std::log10(history));  //might be a source of time inneficiency
		return card * std::pow(10, exponent + 1) + history;
	}
};

/*int main() {
	KuhnPoker kp;
	kp.playGame(0, 1);
	return 0;
}*/

int nearestPowerOf10(double num) {
    if (num <= 0) {
        std::cerr << "Number must be greater than 0" << std::endl;
        return -1; // Invalid input
    }
    
    int exponent = (int)(std::log10(num)); // Find the nearest integer exponent
    return std::pow(10, exponent); // Raise 10 to that exponent
}

int main() {
    double number = 100;

    int nearestPower = nearestPowerOf10(number);
    std::cout << "The nearest power of 10 is: " << nearestPower << std::endl;

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