#pragma once

class KuhnPoker;

class Player {
private:
  int stack, n;

public:
  Player(int n);
  void playTurn(KuhnPoker *kp);
  void bet(int n);
};