#include "KuhnPoker.h"
#include <experimental/random>
#include <vector>

const std::vector<int> KuhnPoker::cards = {0, 1, 2};

KuhnPoker::KuhnPoker() {
  pot = 0;
  ante = 1;
  roundBetSize = 1;
  gameState = 0;
  hasBet = false;
  playingGame = true;
  players.push_back(Player(this, 1));
  players.push_back(Player(this, 2));
  shuffleDeck();
}

KuhnPoker::~KuhnPoker() {}

void KuhnPoker::playGame() {
  dealCards();
  while (playingGame) {
    for (Player &p : players) {
      if (!p.hasFolded()) {
        p.playTurn();
      }
    }
    if (gameState == 1) {
      playingGame = false;
    }
    ++gameState;
  }
  int maxScore = 0;
  int winnerSofar = -1;
  for (Player &p : players) {
    if (!p.hasFolded()) {
      int temp = scoreHand(p.getCard());
      std::cout << p.getNumber() << " " << temp << "\n";
      if (maxScore < temp) {
        maxScore = temp;
        winnerSofar = p.getNumber();
      }
    }
  }
  std::cout << "player " << winnerSofar << " wins\n";
}

void KuhnPoker::resetGame() {
  pot = 0;
  ante = 1;
  roundBetSize = 1;
  gameState = 0;
  hasBet = false;
  playingGame = true;
  shuffleDeck();
}

void KuhnPoker::shuffleDeck() {
  emptyDeck();
  std::vector<int> temp = cards; // supposedly copies but might not
  while (!temp.empty()) {
    int tempRand = std::experimental::randint(0, 100) % temp.size();
    deck.push(temp[tempRand]);
    temp.erase(temp.begin() + tempRand);
  }
}

void KuhnPoker::emptyDeck() {
  while (!deck.empty()) {
    deck.pop();
  }
}

void KuhnPoker::dealCards() {
  for (Player &p : players) {
    p.setCard(deck.front());
    deck.pop();
  }
}

int KuhnPoker::scoreHand(int card) { return card; }

// getters
int KuhnPoker::getAnte() { return ante; }
int KuhnPoker::getGameState() { return gameState; }
// setters
void KuhnPoker::addToPot(int n) { pot += n; }