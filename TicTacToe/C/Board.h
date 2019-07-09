#ifndef BOARD_H
#define BOARD_H

#define true 1
#define false 0

#define X 'X'
#define O 'O'
#define NO_ONE ' '

typedef short bool;

typedef char Player;

typedef enum {
    WIN_X, WIN_O, TIE, CONTINUE
} GameStatus;

typedef struct {
    Player firstRow[3];
    Player secondRow[3];
    Player thirdRow[3];
} Board;

void display(Board *);
void makeMove(Board *, int, Player);
void unmakeMove(Board *, int);

bool isMoveLegal(Board *, int);

Board newBoard(void);

GameStatus checkGameStatus(Board *);

#endif
