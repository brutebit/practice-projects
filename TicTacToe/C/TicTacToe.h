#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include "Board.h"

typedef struct {
    Player humanPiece;
    Player machinePiece;
    Board *board;
} TicTacToe;

TicTacToe newTicTacToe(void);

void run(TicTacToe *);

#endif
