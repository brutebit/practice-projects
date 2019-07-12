#include <stdlib.h>
#include "hand.h"
#include "card.h"

hand_t new_hand() {
    return (hand_t) {
        .cards = calloc(1, sizeof(card_t)),
        .size = 0
    };
}

void hand_add_card(hand_t *hand, card_t *card) {
    hand->cards = realloc(hand->cards, (hand->size + 1) * sizeof(card_t));
    hand->size++;
    hand->cards[hand->size - 1] = card;
}

void hand_popback_card(hand_t *hand) {
    hand->cards[hand->size - 1] = NULL;
    hand->cards = realloc(hand->cards, (hand->size - 1) * sizeof(card_t));
    hand->size--;
}

void hand_clear_cards(hand_t *hand) {
    for (int i = 0; i < hand->size; i++)
        hand->cards[i] = NULL;
    hand->cards = realloc(hand->cards, 1);
    hand->size = 0;
}

int hand_get_total_cards_value(const hand_t *hand) {
    if (hand->size == 0 || card_get_value(hand->cards[0]) == 0)
        return 0;
    int total = 0;
    bool contain_ace = false;
    for (int i = 0; i < hand->size; i++) {
        total += card_get_value(hand->cards[i]);
        if (card_get_value(hand->cards[i]) == ACE)
            contain_ace = true;
    }
    if (contain_ace && total <= 11)
        total += 10;
    return total;
}

void delete_hand(hand_t *hand) {
    hand_clear_cards(hand);
    free(hand->cards);
    hand->cards = NULL;
}
