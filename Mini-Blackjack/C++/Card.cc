#include "Card.hh"
#include <string>

using namespace std;

Card::Card(Rank r, Suit s, bool ifu):
    rank(r), suit(s), isFaceUp(ifu) {}

int Card::getValue() const {
    int value = 0;
    if (isFaceUp) {
        value = rank;
        if (value > 10)
            value = 10;
    }
    return value;
}

void Card::flip() {
    isFaceUp = !isFaceUp;
}

ostream &operator<<(ostream &os, const Card &card) {
    const string RANKS[] = {
        "0", "A", "2", "3", "4", "5", "6", "7",
        "8", "9", "10", "J", "Q", "K"
    };
    const string SUITS[] = {
        "c", "d", "h", "s"
    };
    if (card.isFaceUp)
        os << RANKS[card.rank] << SUITS[card.suit];
    else
        os << "XX";
    return os;
}
