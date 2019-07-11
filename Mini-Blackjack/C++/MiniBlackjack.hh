#ifndef MiniBlackjack_HH
#define MiniBlackjack_HH

#include "Deck.hh"
#include "House.hh"
#include "Player.hh"
#include <vector>
#include <string>

using namespace std;

class MiniBlackjack {
    Deck deck;
    House house;
    vector<Player> players;
    
public:
    MiniBlackjack(const vector<string> &names);
    void play(void);
};

#endif
