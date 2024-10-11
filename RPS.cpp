#include <iostream>
#include <random>
#include <stdio.h>
#include <vector>

class RPS {
  private:
	const std::vector< std::vector<int> > gameState = {
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
	std::discrete_distribution<> oppdist;

  public:
	RPS() {
		actions = {0, 1, 2};
		regret = {0, 0, 0};
		oppRegret = {0, 0, 0};
		probability = {1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0};
		oppProbability = {1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0};
		gen = std::mt19937(std::random_device{}());
		dist = std::discrete_distribution<>(probability.begin(), probability.end());
		oppdist = std::discrete_distribution<>(oppProbability.begin(), oppProbability.end());
	}

	void playGame() {
		dist = std::discrete_distribution<>(probability.begin(), probability.end());
		oppdist = std::discrete_distribution<>(oppProbability.begin(), oppProbability.end());

		int ai1 = getChoice();
		int ai2 = getChoice();
		int reward = getReward(ai1, ai2);
		int oppReward = getReward(ai2, ai1);
		std::vector<int> cfr = getCFR(ai2);
		std::vector<int> oppcfr = getCFR(ai1);

		int sum = 0, oppsum = 0;

		//recalculates regret
		for (int i = 0; i < 3; ++i) {
			regret[i] += cfr[i] - reward;
			oppRegret[i] += oppcfr[i] - oppReward;
			sum += (regret[i] > 0) * regret[i];
			oppsum += (oppRegret[i] > 0) * oppRegret[i];
		}

		//recalculates strategies
		for (int i = 0; i < 3; ++i) {
			probability[i] = (double) regret[i] / sum;
			oppProbability[i] = (double) oppRegret[i] / sum;
		}
	}

	void print() {
		std::cout << "regret: " << regret[0] << " " << regret[1] << " " << regret[2] << "\n";
		std::cout << "oppRegret: " << oppRegret[0] << " " << oppRegret[1] << " " << oppRegret[2] << "\n";
		std::cout << "probability : " << probability[0] << " " << probability[1] << " " << probability[2] << "\n";
		std::cout << "oppProbability : " << oppProbability[0] << " " << oppProbability[1] << " " << oppProbability[2] << "\n";
	}

	std::vector<int> getCFR(int b) {
		return std::vector<int>{gameState[0][b], gameState[1][b], gameState[2][b]};
	}

	int getChoice() {
		return dist(gen);
	}

	int getReward(int y, int x) {
		return gameState[y][x];
	}
};

int main() {
	RPS rps;
	rps.print();
	for (int i = 0; i < 10000; ++i) {
		rps.playGame();
	}
	rps.print();
	return 0;
}