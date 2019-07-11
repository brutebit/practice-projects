#include "AbstractPlayer.hh"
#include "Card.hh"
#include <string>
#include <vector>

using namespace std;

AbstractPlayer::AbstractPlayer(const string &name):
    name(name) {}

AbstractPlayer::~AbstractPlayer() {}

bool AbstractPlayer::isBusted() const {
    return getTotal() > 21;
}

void AbstractPlayer::bust() const {
    cout << name << " busts.\n";
}

ostream &operator<<(ostream &os, const AbstractPlayer &ap) {
    os << ap.name << ":\t";
    vector<Card *>::const_iterator cardp;
    if (!ap.cards.empty()) {
        for (cardp = ap.cards.begin(); cardp != ap.cards.end(); cardp++)
            os << *(*cardp) << "\t";
        if (ap.getTotal() != 0)
            cout << "(" << ap.getTotal() << ")";
    }
    else
        os << "<empty>";
    return os;
}
