#include <stdio.h>
#include "card.h"

card_t new_card(card_rank_t r, card_suit_t s, bool ifu) {
    return (card_t) {
        .rank = r,
        .suit = s,
        .is_faceup = ifu
    };
}

int card_get_value(const card_t *card) {
    if (!card->is_faceup)
        return 0;
    if (card->rank < 10)
        return card->rank;
    return 10;
}

void card_flip(card_t *card) {
    card->is_faceup = !card->is_faceup;
}

void card_print(const card_t *card) {
    const char *RANKS[] = {
        "0", "A", "2", "3", "4", "5", "6",
        "7", "8", "9", "10", "J", "Q", "K"
    };
    const char *SUITS[] = {
        "c", "s", "h", "d"
    };
    if (card->is_faceup)
        printf("%s%s", RANKS[card->rank], SUITS[card->suit]);
    else
        printf("XX");
}
