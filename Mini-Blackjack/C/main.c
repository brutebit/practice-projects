#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mini_blackjack.h"

int main() {
    printf("Welcome to Mini-Blackjack!\n\n");
    int num_player = 0, i;
    while (num_player < 1 || num_player > 7) {
        printf("How many players? (1 - 7): ");
        if ((scanf("%d", &num_player)) != 1)
            while (getchar() != '\n');
    }
    while (getchar() != '\n');
    putchar('\n');
    char **names = calloc(7, sizeof(char **));
    for (i = 0; i < 7; i++) {
        names[i] = calloc(4, sizeof(char *));
    }
    size_t res_size = 4;
    for (i = 0; i < num_player; i++) {
        printf("Enter player name: ");
        getline(&names[i], &res_size, stdin);
        names[i][strlen(names[i]) - 1] = '\0';
    }
    putchar('\n');
    names[i] = NULL;
    char again = 'y';
    while (again != 'n' && again != 'N') {
        mini_blackjack_t game = new_mini_blackjack(names);
        mini_blackjack_play(&game);
        printf("\nDo you want to play again? (y/n): ");
        if (scanf("%c", &again) != 1)
            while (getchar() != '\n');
        while (getchar() != '\n');
    }
    return 0;
}
