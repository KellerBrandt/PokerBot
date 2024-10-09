#pragma once

#include <iostream>
#include <queue>
#include <random>
#include <vector>


#include "Player.h"

class KuhnPoker {
private:
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
  std::vector<Player> players;
  std::queue<int> deck;
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<> distrib;

public:
  const static std::vector<int> cards;

  KuhnPoker();
  ~KuhnPoker();
  void playGame();
  void resetGame();
  void shuffleDeck();
  void emptyDeck();
  void dealCards();
  int scoreHand(int card);
  // getters
  int getAnte();
  int getGameState();
  // setters
  void addToPot(int n);
};