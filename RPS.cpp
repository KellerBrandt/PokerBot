#include <iostream>
#include <random>
#include <stdio.h>
#include <vector>

class RPS {
  private:
	const std::vector<std::vector<int>> gameStates = {
		{0, -1, 1},
		{1, 0, -1},
		{-1, 1, 0}};

	std::vector<int> actions;
	std::vector<int> regret;
	std::vector<int> oppRegret;
	std::vector<double> probability;
	std::vector<double> oppProbability;
	std::mt19937 gen;
	std::discrete_distribution<> dist;

  public:
	RPS() : actions{0, 1, 2}, regret(3, 0.0), oppRegret(3, 0.0), probability(3, 1.0 / 3.0), oppProbability(3, 1.0 / 3.0), gen(std::random_device{}()) {
		dist = std::discrete_distribution<>(probability.begin(), probability.end());
	}

	void playGame() {
		int ai1 = getChoice();
		int ai2 = getChoice();
		int reward = getReward(ai1, ai2);
		int oppReward = getReward(ai2, ai1);
		std::vector<int> cfr = getCFR(ai1, ai2);
		std::vector<int> oppcfr = getCFR(ai2, ai1);
	}

	std::vector<int> getCFR(int a, int b) {
		std::vector<int> result;

		return result;
	}

	int getChoice() {
		return dist(gen);
	}

	int getReward(int y, int x) {
		return gameStates[y][x];
	}
};

int main() {
	RPS rps;
	return 0;
}