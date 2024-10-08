#pragma once

class KuhnPoker;

class Player {
private:
  KuhnPoker* kp;
  int stack, n;

public:
  Player(KuhnPoker* kp, int n);
  virtual ~Player();
  virtual void playTurn();
  void bet(int n);
};