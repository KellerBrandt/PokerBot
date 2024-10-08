#include <iostream>
#include <stdio.h>
#include <utility>

class KuhnPoker {
  private:
	struct Card {
		Card(char s, int r) : suit(s), rank(r) {}
		char suit;
		int rank;
	};

	class Player {
	  public:
		Player() {
		}
	};

	const Card *freshDeck[52] = {new Card('C', 2), new Card('C', 3), new Card('C', 4), new Card('C', 5), new Card('C', 6), new Card('C', 7), new Card('C', 8), new Card('C', 9), new Card('C', 10), new Card('C', 11), new Card('C', 12), new Card('C', 13), new Card('C', 14),
								 new Card('D', 2), new Card('D', 3), new Card('D', 4), new Card('D', 5), new Card('D', 6), new Card('D', 7), new Card('D', 8), new Card('D', 9), new Card('D', 10), new Card('D', 11), new Card('D', 12), new Card('D', 13), new Card('D', 14),
								 new Card('H', 2), new Card('H', 3), new Card('H', 4), new Card('H', 5), new Card('H', 6), new Card('H', 7), new Card('H', 8), new Card('H', 9), new Card('H', 10), new Card('H', 11), new Card('H', 12), new Card('H', 13), new Card('H', 14),
								 new Card('S', 2), new Card('S', 3), new Card('S', 4), new Card('S', 5), new Card('S', 6), new Card('S', 7), new Card('S', 8), new Card('S', 9), new Card('S', 10), new Card('S', 11), new Card('S', 12), new Card('S', 13), new Card('S', 14)};
	Player *players[2];

  public:
	KuhnPoker() {
		players[0] = new Player();
		players[1] = new Player();
	}

	~KuhnPoker() {
		// memory deallocation for freshDeck
		for (int i = 0; i < sizeof(freshDeck); ++i) {
			delete freshDeck[i];
			freshDeck[i] = nullptr;
		}
		delete[] freshDeck;
		//memory deallocation for players
		delete players[0];
		delete players[1];
		delete[] players;
	}

	void playGame() {
		ante();
		dealCards();
		/*
		player 1 then checks or bets 1
		if p1 checks:
			if p2 checks:
				cards are shown
			if p2 bets:
				if p1 matches/calls:
					cards are shown
				if p1 folds:
					p2 gets the pot

		if p1 bets 1:
			if p2 folds:
				p1 wins
			if p2 calls:
				cards are shown
		*/
	}

	int scoreHand() {
	}

	std::pair<int, Card *[]> findBestHand(Card hand[], Card communityCards[]) {
	}

	void ante() {
	}

	void dealCards() {
	}
};

int main() {
	printf("Test");
	return 0;
}