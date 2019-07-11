#include "MiniBlackjack.hh"
#include "Player.hh"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

MiniBlackjack::MiniBlackjack(const vector<string> &names) {
    vector<string>::const_iterator name;
    for (name = names.begin(); name != names.end(); name++)
        players.push_back(Player(*(name)));
    srand(static_cast<unsigned int>(time(0)));
    deck.populate();
    deck.shuffle();
}

void MiniBlackjack::play() {
    vector<Player>::iterator player;
    for (int i = 0; i < 2; i++) {
        for (player = players.begin(); player != players.end(); player++)
            deck.deal(*player);
        deck.deal(house);
    }
    house.flipFirstCard();
    for (player = players.begin(); player != players.end(); player++)
        cout << *player << endl;
    cout << house << endl;
    for (player = players.begin(); player != players.end(); player++)
        deck.additionalCards(*player);
    house.flipFirstCard();
    cout << house << endl;
    deck.additionalCards(house);
    if (house.isBusted()) {
        for (player = players.begin(); player != players.end(); player++)
            if (!player->isBusted())
                player->win();
    }
    else
        for (player = players.begin(); player != players.end(); player++)
            if (!player->isBusted()) {
                if (player->getTotal() > house.getTotal())
                    player->win();
                else if (player->getTotal() < house.getTotal())
                    player->lose();
                else
                    player->push();
            }
    for (player = players.begin(); player != players.end(); player++)
        player->clear();
    house.clear();
}
