#pragma once

#include <iostream>
#include <vector>
#include <queue>

#include "Player.h"

class KuhnPoker {
private:
  std::vector<Player> players;
  int pot; // total amount in the pot
  int ante;
  int roundBetSize;
  int gameState;
  /*
  0: ante round
  1: first round
  2: second round
  ...
  */
  bool hasBet; // whether or not a player has bet this round
  bool playingGame;
  constexpr static int cards[] = {0, 1, 2};

public:
  KuhnPoker();
  ~KuhnPoker();
  void playGame();
  void resetGame();
  void shuffleDeck();
  void dealCards();
  // getters
  int getAnte();
  int getGameState();
  // setters
  void addToPot(int n);
};