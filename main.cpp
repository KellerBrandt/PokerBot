class Poker {
  private:
	struct Card {
		Card(char s, char r) : suit(s), rank(r) {}
		char suit;
		char rank;
	};
	const Card freshDeck[1] = {Card('S', 'A')};

  public:
	Poker() {
	}

    ~Poker() {
	}

	int
	scoreHand() {
	}

	void
	findBestHand() {
	}
};

int main() {
	return 0;
}