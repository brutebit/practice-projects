#ifndef PLAYER_H
#define PLAYER_H

#include "abstract_player.h"
#include "hand.h"

typedef struct {
    abstract_player_t ap;
} player_t;

player_t new_player(char *);
bool player_is_hitting(void *player, hand_t *player_hand);
void player_win(player_t *);
void player_lose(player_t *);
void player_push(player_t *);

#endif
