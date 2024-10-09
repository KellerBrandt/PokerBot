#include "KuhnPoker.h"
#include <algorithm>

KuhnPoker::cards.std::push_back(0);
KuhnPoker::cards.std::push_back(1);
KuhnPoker::cards.std::push_back(2);

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
  
  std::copy(cards, cards + sizeof(cards), temp); 
  while () {

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