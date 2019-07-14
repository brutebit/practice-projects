#ifndef CARD_H
#define CARD_H

#define true 1
#define false 0

typedef short bool;

typedef enum {
    ACE = 1, TWO, THREE, FOUR, FIVE, SIX,
    SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
} card_rank_t;

typedef enum {
    CLUBS, SPADES, HEARTS, DIAMONDS
} card_suit_t;

typedef struct {
    card_rank_t rank;
    card_suit_t suit;
    bool is_faceup;
} card_t;

card_t new_card(card_rank_t, card_suit_t, bool);
int card_get_value(const card_t *);
void card_flip(card_t *);
void card_print(const card_t *);

#endif
