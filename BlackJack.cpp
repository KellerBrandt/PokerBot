#include <algorithm>
#include <iostream>
#include <random>
#include <stdio.h>
#include <unordered_map>
#include <vector>

/*
Assumptions:
	dealer stands on soft 17
*/

/*
0: stand, 1: hit
*/
int actions[2] = {0, 1};

int primes[13] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 41, 43};
int suits[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};