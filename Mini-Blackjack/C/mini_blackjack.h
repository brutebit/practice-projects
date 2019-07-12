#ifndef MINI_BLACKJACK_H
#define MINI_BLACKJACK_H

#include "deck.h"
#include "house.h"
#include "player.h"

typedef struct {
    deck_t deck;
    house_t house;
    player_t *players;
    int players_length;
}
mini_blackjack_t;

mini_blackjack_t new_mini_blackjack(char **);
void mini_blackjack_play(mini_blackjack_t *);

#endif
