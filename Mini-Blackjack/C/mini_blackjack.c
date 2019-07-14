#include <stdio.h>
#include <stdlib.h>
#include "mini_blackjack.h"
#include "player.h"
#include "deck.h"
#include "hand.h"

mini_blackjack_t new_mini_blackjack(char *names[]) {
    int players_size = 0;
    player_t *players = calloc(1, sizeof(player_t));
    while(*names != NULL) {
        players = realloc(players, (players_size + 1) * sizeof(player_t));
        players[players_size] = new_player(*names++);
        players_size++;
    }
    deck_t deck = new_deck();
    deck_shuffle(&deck);
    return (mini_blackjack_t) {
        .players = players,
        .players_length = players_size,
        .deck = deck,
        .house = new_house("House")
    };
}

static void print_player(abstract_player_t *ap) {
    abstract_player_print(ap);
    putchar('\n');
}

static void delete_mini_blackjack(mini_blackjack_t *game) {
    for (int i = 0; i < game->players_length; i++)
        delete_abstract_player(&game->players[i].ap);
    delete_abstract_player(&game->house.ap);
    delete_deck(&game->deck);
    free(game->players);
}

void mini_blackjack_play(mini_blackjack_t *game) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < game->players_length; j++)
            deck_deal(&game->deck, &game->players[j].ap.hand);
        deck_deal(&game->deck, &game->house.ap.hand);
    }
    house_flip_first_card(&(game->house));
    for (int i = 0; i < game->players_length; i++)
        print_player(&game->players[i].ap);
    print_player(&game->house.ap);
    putchar('\n');
    for (int i = 0; i < game->players_length; i++) {
        deck_additional_cards(&game->deck, &game->players[i].ap);
        putchar('\n');
    }
    house_flip_first_card(&game->house);
    print_player(&game->house.ap);
    deck_additional_cards(&game->deck, &game->house.ap);
    if (abstract_player_is_busted(&game->house.ap)) {
        for (int i = 0; i < game->players_length; i++)
            if (!abstract_player_is_busted(&game->players[i].ap))
                player_win(&game->players[i]);
    }
    else {
        int house_total = hand_get_total_cards_value(&game->house.ap.hand);
        for (int i = 0; i < game->players_length; i++)
            if (!abstract_player_is_busted(&game->players[i].ap)) {
                int player_total = hand_get_total_cards_value(&game->players[i].ap.hand);
                if (player_total > house_total)
                    player_win(&game->players[i]);
                else if (player_total < house_total)
                    player_lose(&game->players[i]);
                else
                    player_push(&game->players[i]);
            }
    }
    delete_mini_blackjack(game);
}
