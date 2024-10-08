#include "KuhnPoker.h"

KuhnPoker::KuhnPoker() {
  pot = 0;
  ante = 1;
  roundBetSize = 1;
  gameState = 0;
  hasBet = false;
  playingGame = true;
  players.push_back(Player(1));
  players.push_back(Player(2));
}

KuhnPoker::~KuhnPoker() {}

void KuhnPoker::playGame() {
  while (playingGame) {
    for (Player p : players) {
      p.playTurn(this);
    }
    if (gameState == 2) {
      playingGame = false;
    }

    ++gameState;
  }
}

void KuhnPoker::addToPot(int n) { pot += n; }

void KuhnPoker::resetGame() {
  pot = 0;
  ante = 1;
  gameState = 0;
  hasBet = false;
  playingGame = true;
}

// getters
int KuhnPoker::getAnte() { return ante; }
int KuhnPoker::getGameState() { return gameState; }
// setters

int main() {
  printf("Test\n");
  KuhnPoker kPokerGame = KuhnPoker();
  kPokerGame.playGame();
  return 0;
}