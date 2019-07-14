#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "deck.h"
#include "card.h"
#include "hand.h"
#include "player.h"
#include "house.h"
#include "abstract_player.h"

deck_t new_deck() {
    hand_t hand = new_hand();
    card_t *cards = calloc(52, sizeof(card_t));
    int i = 0;
    for (int s = CLUBS; s <= DIAMONDS; s++)
        for (int r = ACE; r <= KING; r++, i++)
            cards[i] = new_card(r, s, true);
    for (i = 0; i < 52; i++)
        hand_add_card(&hand, &cards[i]);
    return (deck_t) {
        .hand = hand
    };
}

void deck_shuffle(deck_t *deck) {
    card_t *temp;
    srand(time(NULL));
    for (int i = 0; i < deck->hand.size; i++) {
        int random = (rand() % deck->hand.size);
        temp = deck->hand.cards[random];
        deck->hand.cards[random] = deck->hand.cards[i];
        deck->hand.cards[i] = temp;
    }
}

void deck_deal(deck_t *deck, hand_t *hand) {
    if (deck->hand.size != 0) {
        hand_add_card(hand, deck->hand.cards[deck->hand.size - 1]);
        hand_popback_card(&deck->hand);
    }
    else
        printf("Out of cards. Unable to deal.\n");
}

void deck_additional_cards(deck_t *deck, abstract_player_t *ap) {
    bool (*hitting_func)(void *, hand_t *);
    if (strcmp(ap->type, "PLAYER") == 0)
        hitting_func = player_is_hitting;
    else if (strcmp(ap->type, "HOUSE") == 0)
        hitting_func = house_is_hitting;
    while (!abstract_player_is_busted(ap) && hitting_func(ap, &ap->hand)) {
        deck_deal(deck, &ap->hand);
        abstract_player_print(ap);
        putchar('\n');
        if (abstract_player_is_busted(ap))
            abstract_player_bust(ap);
    }
}

void delete_deck(deck_t *deck) {
    delete_hand(&deck->hand);
}
