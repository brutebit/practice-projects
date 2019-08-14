#include "TicTacToe.hpp"
#include <iostream>

const int WIN_POSITIONS[8][3] = {
    {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
    {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
    {1, 5, 9}, {3, 5, 7}
};

TicTacToe::Board::Board() {
    for (int i = 0; i < 3; i++) {
        firstRow[i] = EMPTY;
        secondRow[i] = EMPTY;
        thirdRow[i] = EMPTY;
    }
}

void TicTacToe::Board::display() const {
    std::cout << "\t\t\t" <<
    getPieceAsChar(static_cast<TicTacToe::GamePiece>(firstRow[0])) << " | " <<
    getPieceAsChar(static_cast<TicTacToe::GamePiece>(firstRow[1])) << " | " << 
    getPieceAsChar(static_cast<TicTacToe::GamePiece>(firstRow[2])) <<
    "\n\t\t\t---------\n\t\t\t" <<
    getPieceAsChar(static_cast<TicTacToe::GamePiece>(secondRow[0])) << " | " <<
    getPieceAsChar(static_cast<TicTacToe::GamePiece>(secondRow[1])) << " | " <<
    getPieceAsChar(static_cast<TicTacToe::GamePiece>(secondRow[2])) <<
    "\n\t\t\t---------\n\t\t\t" <<
    getPieceAsChar(static_cast<TicTacToe::GamePiece>(thirdRow[0])) << " | " <<
    getPieceAsChar(static_cast<TicTacToe::GamePiece>(thirdRow[1])) << " | " << 
    getPieceAsChar(static_cast<TicTacToe::GamePiece>(thirdRow[2])) << "\n\n";
}

char TicTacToe::Board::getPieceAsChar(const GamePiece piece) const {
    switch (piece) {
        case X:
            return 'X';
        case O:
            return 'O';
        case EMPTY:
            return ' ';
        default:
            break;
    }
}

TicTacToe::GamePiece TicTacToe::Board::getPiece(const int position) const {
    if (position <= 3)
       return static_cast<TicTacToe::GamePiece>(firstRow[position - 1]);
    else if (position <= 6)
        return static_cast<TicTacToe::GamePiece>(secondRow[position - 4]);
    return static_cast<TicTacToe::GamePiece>(thirdRow[position - 7]);
}

bool TicTacToe::Board::isMoveLegal(const int position) const {
    return getPiece(position) == EMPTY;
}

void TicTacToe::Board::makeMove(const int position, const GamePiece piece) {
    if (position <= 3)
        firstRow[position - 1] = piece;
    else if (position <= 6)
        secondRow[position - 4] = piece;
    else
        thirdRow[position - 7] = piece;
}

void TicTacToe::Board::unmakeMove(const int position) {
    if (position <= 3)
        firstRow[position - 1] = EMPTY;
    else if (position <= 6)
        secondRow[position - 4] = EMPTY;
    else
        thirdRow[position - 7] = EMPTY;
}

TicTacToe::GameStatus TicTacToe::Board::checkGameStatus() const {
    for (int i = 0; i < 8; i++) {
        TicTacToe::GamePiece firstEl = getPiece(WIN_POSITIONS[i][0]);
        TicTacToe::GamePiece secondEl = getPiece(WIN_POSITIONS[i][1]);
        TicTacToe::GamePiece thirdEl = getPiece(WIN_POSITIONS[i][2]);
        if (firstEl == secondEl && secondEl == thirdEl && thirdEl != EMPTY)
            return (thirdEl == X ? WIN_X : WIN_O);
    }
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 3; j++)
            if (getPiece(WIN_POSITIONS[i][j]) == EMPTY)
                return CONTINUE;
    return TIE;
}
