#ifndef HOUSE_H
#define HOUSE_H

#include "abstract_player.h"
#include "hand.h"

typedef struct {
    abstract_player_t ap;
} house_t;

house_t new_house(char *);
bool house_is_hitting(void *house, hand_t *house_hand);
void house_flip_first_card(house_t *house);

#endif
