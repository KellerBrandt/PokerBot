#pragma once

class KuhnPoker;

class Player {
private:
  KuhnPoker* kp;
  int stack, n;
  int card;
  bool folded;

public:
  Player(KuhnPoker* kp, int n);
  virtual ~Player();
  virtual void playTurn();
  void bet(int n);
  void fold();
  //getters
  int getCard();
  int getNumber();
  bool hasFolded();
  //setters
  void setCard(int card);
};