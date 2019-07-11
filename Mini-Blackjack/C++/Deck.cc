#include "Deck.hh"
#include "Hand.hh"
#include "Card.hh"
#include "AbstractPlayer.hh"
#include <algorithm>

Deck::Deck() {
    cards.reserve(52);
    populate();
}

Deck::~Deck() {}

void Deck::populate() {
    clear();
    for (int s = Card::CLUBS; s <= Card::SPADES; s++)
        for (int r = Card::ACE; r <= Card::KING; r++)
            add(new Card(static_cast<Card::Rank>(r),
                         static_cast<Card::Suit>(s)));
}

void Deck::shuffle() {
    random_shuffle(cards.begin(), cards.end());
}

void Deck::deal(Hand &hand) {
    if (!cards.empty()) {
        hand.add(cards.back());
        cards.pop_back();
    }
    else
        cout << "Out of cards. Unable to deal.";
}

void Deck::additionalCards(AbstractPlayer &ap) {
    cout << endl;
    while (!ap.isBusted() && ap.isHitting()) {
        deal(ap);
        cout << ap << endl;
        if (ap.isBusted())
            ap.bust();
    }
}
