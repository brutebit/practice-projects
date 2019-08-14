#include "TicTacToe.hpp"
#include <iostream>
#include <string>

static std::string askName(const char * const req) {
    std::string name;
    std::cout << req << " : ";
    std::cin >> name;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return name;
}

void TicTacToe::MultiplayerGame::decideFirstMove() {
    playerOne.name = askName("Enter player's one name");
    playerTwo.name = askName("Enter player's two name");
    playerOne.piece = X;
    playerTwo.piece = O;
}

void TicTacToe::MultiplayerGame::playerMove(std::string playerName) {
    std::string question = playerName + " where will you move?";
    int move;
    do {
        move = askNumber(question.c_str());
        if (!board.isMoveLegal(move))
            std::cout << "This place is already occupied!";
    }
    while (!board.isMoveLegal(move));
    std::cout << "fine...\n";
    if (playerOne.name == playerName)
        board.makeMove(move, playerOne.piece);
    else
        board.makeMove(move, playerTwo.piece);
}

void TicTacToe::MultiplayerGame::printEnd(GameStatus status) const {
    if (status == TIE)
        std::cout << "It's a tie.\n";
    else if (status == WIN_O)
        std::cout << playerTwo.name << " Won!\n";
    else
        std::cout << playerOne.name << " Won!\n";
}
