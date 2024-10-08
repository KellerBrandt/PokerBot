#pragma once

#include "Player.h"

class PokerBot : public Player {
private:
public:
  PokerBot();
  ~PokerBot();
  void playTurn() override;
};