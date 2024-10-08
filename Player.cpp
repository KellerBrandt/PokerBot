#include <iostream>

#include "KuhnPoker.h"
#include "Player.h"

Player::Player(KuhnPoker* kp, int n) {
  this->kp = kp;
  this->n = n;
  this->stack = 10;
}

Player::~Player() {

}

void Player::playTurn() {
  std::cout << n << "\n";
  switch (kp->getGameState()) {
  case 0: // first round ante
    bet(kp->getAnte());
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

void Player::bet(int n) { stack -= n; }