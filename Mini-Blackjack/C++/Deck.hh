#ifndef DECK_HH
#define DECK_HH

#include "Hand.hh"
#include "AbstractPlayer.hh"

class Deck: public Hand {
public:
    Deck(void);
    virtual ~Deck(void);
    void populate(void);
    void shuffle(void);
    void deal(Hand &hand);
    void additionalCards(AbstractPlayer &ap);
};

#endif
