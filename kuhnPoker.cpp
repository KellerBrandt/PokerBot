#include <iostream>
#include <vector>

class Player {
private:
  int stack;
  int bet;

public:
  Player() {}
  void playTurn(int round) {
    switch (round) {
    case 0:
      printf("Test0");
      break;
    case 1:
      printf("Test1");
    case 2:
      printf("Test2");
    }
  }
};

class PokerBot : public Player {};

class KuhnPoker {
private:
  std::vector<Player> players;
  int pot; // total amount in the pot
  int gameState;
  /*
  0: ante round
  1: first round
  2: second round
  ...
  */
  bool hasBet; // whether or not a player has bet this round
  bool playingGame;

public:
  KuhnPoker() {
    pot = 0;
    gameState = 0;
    hasBet = false;
    playingGame = true;
    players.push_back(Player());
    players.push_back(Player());
  }

  ~KuhnPoker() {}

  void playGame() {
    while (playingGame) {
      for (Player p : players) {
        p.playTurn(0);
      }
      if (gameState == 2) {
        playingGame = false;
      }

      ++gameState;
    }
  }

  void resetGame() {
    pot = 0;
    gameState = 0;
    hasBet = false;
    playingGame = true;
  }
};

int main() {
  printf("Test");
  KuhnPoker kPokerGame = KuhnPoker();
  kPokerGame.playGame();
  return 0;
}