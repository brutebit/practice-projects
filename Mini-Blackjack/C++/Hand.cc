#include "Hand.hh"
#include "Card.hh"
#include <vector>

using namespace std;

Hand::Hand() {
    cards.reserve(7);
}

Hand::~Hand() {
   clear();
}

void Hand::add(Card *card) {
    cards.push_back(card);
}

void Hand::clear() {
    vector<Card *>::iterator iter = cards.begin();
    for (iter = cards.begin(); iter != cards.end(); iter++) {
        delete *iter;
        *iter = nullptr;
    }
    cards.clear();
}

int Hand::getTotal() const {
    if (cards.empty() || cards[0]->getValue() == 0)
        return 0;
    int total = 0;
    bool containAce = false;
    vector<Card *>::const_iterator iter;
    for (iter = cards.begin(); iter != cards.end(); iter++) {
        total += (*iter)->getValue();
        if ((*iter)->getValue() == Card::ACE)
            containAce = true;
    }
    if (containAce && total <= 11)
        total += 10;
    return total;
}
