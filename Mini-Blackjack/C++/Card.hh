#ifndef CARD_HH
#define CARD_HH

#include <iostream>

using namespace std;

class Card {
public:
    enum Rank {
        ACE = 1, TWO, THREE, FOUR, SIX, SEVEN,
        EIGHT, NINE, TEN, JACK, QUEEN, KING
    };
    enum Suit {
        CLUBS, DIAMONDS, HEARTS, SPADES
    };
    
    Card(Rank r=ACE, Suit s=SPADES, bool ifu=true);
    int getValue(void) const;
    void flip(void);

private:
    Rank rank;
    Suit suit;
    bool isFaceUp;
    
friend ostream &operator<<(ostream &os, const Card &card);
};

#endif
