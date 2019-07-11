#include "House.hh"
#include "AbstractPlayer.hh"
#include <string>

House::House(const string &name):
    AbstractPlayer(name) {}

House::~House() {}

bool House::isHitting() const {
    return getTotal() <= 16;
}

void House::flipFirstCard() {
    if (!cards.empty())
        cards[0]->flip();
    else
        cout << "No card to flip.\n";
}
