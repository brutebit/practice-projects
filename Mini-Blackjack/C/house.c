#include <stdio.h>
#include "house.h"
#include "hand.h"
#include "card.h"

house_t new_house(char *name) {
    return (house_t) {
        .ap = new_abstract_player(name, "HOUSE")
    };
}

bool house_is_hitting(void *house, hand_t *house_hand) {
    return hand_get_total_cards_value(house_hand) <= 16;
}

void house_flip_first_card(house_t *house) {
    if (house->ap.hand.size != 0)
        card_flip(house->ap.hand.cards[0]);
    else
        printf("No card to flip.\n");
}
