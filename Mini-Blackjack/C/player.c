#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "abstract_player.h"

player_t new_player(char *name) {
    return (player_t) {
        .ap = new_abstract_player(name, "PLAYER")
    };
}

bool player_is_hitting(void *player, hand_t *player_hand) {
    size_t res_size = 4;
    char res = '\0';
    char *buf = malloc(res_size * sizeof(char));
    printf("%s, do you want a hit? (y/n): ", ((abstract_player_t *)player)->name);
    getline(&buf, &res_size, stdin);
    res = buf[0];
    free(buf);
    return res == 'y' || res == 'Y';
}

void player_win(player_t *player) {
    printf("%s wins.\n", player->ap.name);
}

void player_lose(player_t *player) {
    printf("%s loses.\n", player->ap.name);
}

void player_push(player_t *player) {
    printf("%s pushes.\n", player->ap.name);
}
