#include <iostream>

#include "KuhnPoker.h"
#include "Player.h"


Player::Player(int n) { this->n = n; }

void Player::playTurn(KuhnPoker *kp) {
  std::cout << n << "\n";
  switch (kp->getGameState()) {
  case 0:
    printf("Test0");
    break;
  case 1:
    printf("Test1");
    break;
  case 2:
    printf("Test2");
    break;
  }
  printf("\n");
}

void Player::bet(int n) { printf("TurnPlayed"); }