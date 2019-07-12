#ifndef HAND_H
#define HAND_H

#include "card.h"

typedef struct {
    card_t **cards;
    int size;
} hand_t;

hand_t new_hand(void);
void delete_hand(hand_t *);
void hand_add_card(hand_t *, card_t *);
void hand_popback_card(hand_t *);
void hand_clear_cards(hand_t *);
int hand_get_total_cards_value(const hand_t *);

#endif
