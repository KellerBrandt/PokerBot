#include "KuhnPoker.h"
#include <algorithm>
#include <vector>

KuhnPoker::KuhnPoker() {
  pot = 0;
  ante = 1;
  roundBetSize = 1;
  gameState = 0;
  hasBet = false;
  playingGame = true;
  players.push_back(Player(this, 1));
  players.push_back(Player(this, 2));
  deck = std::queue<int>();
  shuffleDeck();
}

KuhnPoker::~KuhnPoker() {}

void KuhnPoker::playGame() {
  while (playingGame) {
    for (Player p : players) {
      p.playTurn();
    }
    if (gameState == 2) {
      playingGame = false;
    }
    ++gameState;
  }
}

void KuhnPoker::resetGame() {
  pot = 0;
  ante = 1;
  gameState = 0;
  hasBet = false;
  playingGame = true;
}

void KuhnPoker::shuffleDeck() {
  emptyDeck();
  std::vector<int> temp = cards; //supposedly copies but might not
  while (!temp.empty()) {
    int tempRand = std::rand() * temp.size();
    deck.push(temp[tempRand]);
    temp.
  }
}

void KuhnPoker::emptyDeck() {
  while(!deck.empty()) {
    deck.pop();
  }
}

void KuhnPoker::dealCards() {

}

// getters
int KuhnPoker::getAnte() { return ante; }
int KuhnPoker::getGameState() { return gameState; }
// setters
void KuhnPoker::addToPot(int n) { pot += n; }

int main() {
  printf("Test\n");
  KuhnPoker kPokerGame = KuhnPoker();
  kPokerGame.playGame();
  return 0;
}