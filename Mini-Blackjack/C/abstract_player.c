#include <stdio.h>
#include "card.h"
#include "hand.h"
#include "abstract_player.h"

abstract_player_t new_abstract_player(char *name, char *type) {
    return (abstract_player_t) {
        .hand = new_hand(),
        .name = name,
        .type = type
    };
}

bool abstract_player_is_busted(abstract_player_t *ap) {
    return hand_get_total_cards_value(&ap->hand) > 21;
}

void abstract_player_bust(abstract_player_t *ap) {
    printf("%s busts.\n", ap->name);
}

void abstract_player_print(abstract_player_t *ap) {
    printf("%s:\t", ap->name);
    if (ap->hand.size != 0) {
        for (int i = 0; i < ap->hand.size; i++) {
            card_print(ap->hand.cards[i]);
            putchar('\t');
        }
        if (hand_get_total_cards_value(&ap->hand) != 0)
            printf("(%d)", hand_get_total_cards_value(&ap->hand));
    }
    else
        printf("<empty>");
}
