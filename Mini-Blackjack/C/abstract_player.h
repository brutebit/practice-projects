#ifndef ABSTRACT_PLAYER_H
#define ABSTRACT_PLAYER_H

#include "hand.h"

typedef struct {
    hand_t hand;
    char *name;
    char *type;
} abstract_player_t;

abstract_player_t new_abstract_player(char *, char *);
bool abstract_player_is_busted(abstract_player_t *);
void abstract_player_bust(abstract_player_t *);
void abstract_player_print(abstract_player_t *);
void delete_abstract_player(abstract_player_t *);

#endif
