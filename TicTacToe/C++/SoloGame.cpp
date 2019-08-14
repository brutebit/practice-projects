#include "TicTacToe.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

static int getRandomNumber() {
    srand(static_cast<unsigned int>(time(NULL)));
    return (rand() % 9) + 1;
}

void checkForWinMove(
    TicTacToe::Board * const board, 
    const TicTacToe::GamePiece piece,
    int * const move, bool * const found
) {
    *move = 1;
    while (*move <= 9) {
        if (board->isMoveLegal(*move)) {
            board->makeMove(*move, piece);
            if (board->checkGameStatus() == (piece == TicTacToe::X ? 
                    TicTacToe::WIN_X : TicTacToe::WIN_O)) {
                *found = true;
                break;
            }
            board->unmakeMove(*move);
        }
        (*move)++;
    }
}

void TicTacToe::SoloGame::decideFirstMove() {
    bool res = askYesNo("Do you require the first move?");
    if (res) {
        std::cout << "\nThen take the first move. You will need it.\n";
        humanPiece = X;
        machinePiece = O;
        return;
    }
    std::cout << "\nYour bravery will be your undoing... I will go first.\n";
    machinePiece = X;
    humanPiece = O;
}

void TicTacToe::SoloGame::humanMove() {
    int move;
    do {
        move = askNumber("Where will you move?");
        if (!board.isMoveLegal(move))
            std::cout << "This place is already occupied foolish human!\n";
    } while (!board.isMoveLegal(move));
    std::cout << "fine...\n";
    board.makeMove(move, humanPiece);
}

void TicTacToe::SoloGame::machineMove(SoloGameOption difficulty) {
    if (difficulty == EASY) {
        int randomNum;
        do randomNum = getRandomNumber();
        while (!board.isMoveLegal(randomNum));
        std::cout << "I shall take square number " << randomNum << '\n';
        board.makeMove(randomNum, machinePiece);
        return;
    }
    bool winMoveFound = false;
    int move;
    checkForWinMove(&board, machinePiece, &move, &winMoveFound);
    if (!winMoveFound)
        checkForWinMove(&board, humanPiece, &move, &winMoveFound);
    if (winMoveFound) {
        board.makeMove(move, machinePiece);
        std::cout << "I shall take square number " << move << '\n';
        return;
    }
    if (difficulty == MEDIUM) {
        int randomNum;
        do randomNum = getRandomNumber();
        while (!board.isMoveLegal(randomNum));
        std::cout << "I shall take square number " << randomNum << '\n';
        board.makeMove(randomNum, machinePiece);
        return;
    }
    const int BEST_MOVES[] = {5, 1, 3, 7, 9, 2, 4, 6, 8};
    for (int i = 0; i < 9; i++) {
        move = BEST_MOVES[i];
        if (!board.isMoveLegal(move))
            continue;
        board.makeMove(move, machinePiece);
        break;
    }
    std::cout << "I shall take square number " << move << '\n';
}

void TicTacToe::SoloGame::printEnd(TicTacToe::GameStatus status) const {
    if (status == TIE) {
        std::cout << "It's a tie.\n";
        std::cout << "You were most lucky, human, and somehow managed to tie me.\n";
        std::cout << "Celebrate... for this is the best you will ever achieve.\n";
    }
    else if ((status == WIN_O && humanPiece == O) ||
        (status == WIN_X && humanPiece == X)) {
        std::cout << "Human won!\n";
        std::cout << "No, no! It cannot be! Somehow you tricked me, human.\n";
        std::cout << "But never again! I, the computer, so swear it!\n";
    }
    else {
        std::cout << "Machine won!\n";
        std::cout << "As i predicted, human, I am triumphant once more proof\n";
        std::cout << " that computers are superior to humans in all regards.\n";
    }
}
