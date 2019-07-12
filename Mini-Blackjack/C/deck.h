#ifndef DECK_H
#define DECK_H

#include "hand.h"
#include "abstract_player.h"

typedef struct {
    hand_t hand;
} deck_t;

deck_t new_deck(void);
void delete_deck(deck_t *);
void deck_shuffle(deck_t *);
void deck_deal(deck_t *, hand_t *);
void deck_additional_cards(deck_t *, abstract_player_t *);

#endif
