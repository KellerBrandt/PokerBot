import random

class Poker:

    FRESH_DECK = ('C2', 'C3', 'C4', 'C5', 'C6', 'C7', 'C8', 'C9', 'C10', 'CJ', 'CQ', 'CK', 'CA',
                  'D2', 'D3', 'D4', 'D5', 'D6', 'D7', 'D8', 'D9', 'D10', 'DJ', 'DQ', 'DK', 'DA',
                  'H2', 'H3', 'H4', 'H5', 'H6', 'H7', 'H8', 'H9', 'H10', 'HJ', 'HQ', 'HK', 'HA',
                  'S2', 'S3', 'S4', 'S5', 'S6', 'S7', 'S8', 'S9', 'S10', 'SJ', 'SQ', 'SK', 'SA')
    

    def __init__(self):
        self.shuffle_deck()

    def shuffle_deck(self, unshuffled_deck=FRESH_DECK):
        temporary_deck = list(unshuffled_deck)
        shuffled_deck = []
        while (temporary_deck) :
            rand = random.randint(0, len(temporary_deck) - 1)
            shuffled_deck.append(temporary_deck[rand])
            temporary_deck.pop(rand)
        self.current_deck = shuffled_deck

    def score(self, hand, community_cards):
        return
    def find_best_hand(self, hand, community_cards):
        return