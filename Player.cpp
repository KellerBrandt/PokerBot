#include <iostream>

#include "KuhnPoker.h"
#include "Player.h"

Player::Player(KuhnPoker *kp, int n) {
  this->kp = kp;
  this->n = n;
  this->stack = 10;
  card = -1;
  folded = false;
}

Player::~Player() {}

void Player::playTurn() {
  switch (kp->getGameState()) {
  case 0: // first round ante
    bet(kp->getAnte());
    break;
  case 1:
    bet(1);
    break;
  }
}

void Player::bet(int n) {
  stack -= n;
  kp->addToPot(n);
}

void Player::fold() { folded = true; }

int Player::getCard() { return card; }

int Player::getNumber() { return n; }

bool Player::hasFolded() { return folded; }

void Player::setCard(int card) { this->card = card; }