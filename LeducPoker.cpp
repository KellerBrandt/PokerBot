#include <algorithm>
#include <iostream>
#include <random>
#include <stdio.h>
#include <unordered_map>
#include <vector>

class Node {
    std::vector<double> strategySum;
	std::vector<double> strategy;
	std::vector<double> cfrSum;
	int history; // 1: check, 2: bet, 3: chance
	int card;
};
