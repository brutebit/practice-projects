#include "Board.h"
#include <stdio.h>

static const int winPositions[8][3] = {
    {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
    {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
    {1, 5, 9}, {3, 5, 7}
};

Board newBoard() {
    Board board;
    for (int i = 0; i < 3; i++) {
        board.firstRow[i] = NO_ONE;
        board.secondRow[i] = NO_ONE;
        board.thirdRow[i] = NO_ONE;
    }
    return board;
}

void display(Board *board) {
    printf("\t\t\t%c | %c | %c\n", board->firstRow[0], board->firstRow[1], board->firstRow[2]);
    printf("\t\t\t---------\n");
    printf("\t\t\t%c | %c | %c\n", board->secondRow[0], board->secondRow[1], board->secondRow[2]);
    printf("\t\t\t---------\n");
    printf("\t\t\t%c | %c | %c\n", board->thirdRow[0], board->thirdRow[1], board->thirdRow[2]);
}

static Player getPlayer(Board *board, int position) {
    return (
            position <= 3 ? board->firstRow[position - 1] :
            position <= 6 ? board->secondRow[position - 4] :
            position <= 9 ? board->thirdRow[position - 7] :
            (char)NULL);
}

bool isMoveLegal(Board *board, int move) {
    return getPlayer(board, move) == NO_ONE;
}

void makeMove(Board *board, int position, Player piece) {
    if (position <= 3)
        board->firstRow[position - 1] = piece;
    else if (position <= 6)
        board->secondRow[position - 4] = piece;
    else
        board->thirdRow[position - 7] = piece;
}

void unmakeMove(Board *board, int position) {
    if (position <= 3)
        board->firstRow[position - 1] = NO_ONE;
    else if (position <= 6)
        board->secondRow[position - 4] = NO_ONE;
    else
        board->thirdRow[position - 7] = NO_ONE;
}

GameStatus checkGameStatus(Board *board) {
    for (int i = 0; i < 8; i++) {
        Player firstElement, secondElement, thirdElement;
        firstElement = getPlayer(board, winPositions[i][0]);
        secondElement = getPlayer(board, winPositions[i][1]);
        thirdElement = getPlayer(board, winPositions[i][2]);
        if (firstElement == secondElement && secondElement == thirdElement &&
            thirdElement != NO_ONE)
            return (thirdElement == X ? WIN_X : WIN_O);
    }
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 3; j++)
            if (getPlayer(board, winPositions[i][j]) == NO_ONE)
                return CONTINUE;
    return TIE;
}
