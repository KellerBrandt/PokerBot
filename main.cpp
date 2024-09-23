#include <iostream>
#include <stdio.h>
#include <utility>

class Poker {
  private:
	struct Card {
		Card(char s, int r) : suit(s), rank(r) {}
		char suit;
		int rank;
	};
	const Card *freshDeck[52] = {new Card('C', 2), new Card('C', 3), new Card('C', 4), new Card('C', 5), new Card('C', 6), new Card('C', 7), new Card('C', 8), new Card('C', 9), new Card('C', 10), new Card('C', 11), new Card('C', 12), new Card('C', 13), new Card('C', 14), 
								 new Card('D', 2), new Card('D', 3), new Card('D', 4), new Card('D', 5), new Card('D', 6), new Card('D', 7), new Card('D', 8), new Card('D', 9), new Card('D', 10), new Card('D', 11), new Card('D', 12), new Card('D', 13), new Card('D', 14), 
								 new Card('H', 2), new Card('H', 3), new Card('H', 4), new Card('H', 5), new Card('H', 6), new Card('H', 7), new Card('H', 8), new Card('H', 9), new Card('H', 10), new Card('H', 11), new Card('H', 12), new Card('H', 13), new Card('H', 14), 
								 new Card('S', 2), new Card('S', 3), new Card('S', 4), new Card('S', 5), new Card('S', 6), new Card('S', 7), new Card('S', 8), new Card('S', 9), new Card('S', 10), new Card('S', 11), new Card('S', 12), new Card('S', 13), new Card('S', 14)};

  public:
	Poker() {
	}

	~Poker() {
		// memory deallocation for freshDeck
		for (int i = 0; i < sizeof(freshDeck); ++i) {
			delete freshDeck[i];
			freshDeck[i] = nullptr;
		}
		delete freshDeck;
	}

	int scoreHand() {
	}

	std::pair<int, Card *[]> findBestHand(Card hand[], Card communityCards[]) {
	}
};

int main() {
	return 0;
}