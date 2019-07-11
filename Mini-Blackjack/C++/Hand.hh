#ifndef HAND_HH
#define HAND_HH

#include "Card.hh"
#include <vector>

class Hand {
public:
    Hand(void);
    virtual ~Hand(void);
    int getTotal(void) const;
    void add(Card *card);
    void clear(void);
    
protected:
    std::vector<Card *> cards;
};

#endif
