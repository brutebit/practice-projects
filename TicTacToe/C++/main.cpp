#include "TicTacToe.hpp"
#include <iostream>
#include <string>
#include <csignal>
#include <cstdlib>
#include <unistd.h>

void sigintHandler(int s){
    std::cout << "\nThank you for playing TicTacToe. Have a good day ahead :)\n";
    exit(0); 
}

int main() {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = sigintHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

    TicTacToe mainGame;
    mainGame.menuCycle();
    while (mainGame.getSelectedOption() != TicTacToe::EXIT) {
        TicTacToe::displayIntro();
        if (mainGame.getSelectedOption() == TicTacToe::SOLO) {
            TicTacToe::SoloGame game;
            game.decideFirstMove();
            TicTacToe::GamePiece currentTurn = game.getHumanPiece() == TicTacToe::X ?
                game.getHumanPiece() : game.getMachinePiece();
            TicTacToe::GameStatus status = TicTacToe::CONTINUE;
            while (status == TicTacToe::CONTINUE) {
                if (currentTurn == game.getHumanPiece()) {
                    game.humanMove();
                    game.displayBoard();
                    status = game.checkGameStatus();
                    currentTurn = game.getMachinePiece();
                }
                else {
                    game.machineMove(mainGame.getSelectedSoloOption());
                    game.displayBoard();
                    status = game.checkGameStatus();
                    currentTurn = game.getHumanPiece();
                }
            }
            game.printEnd(status);
            mainGame.menuCycle();
        }
        else if (mainGame.getSelectedOption() == TicTacToe::MULTIPLAYER) {
            TicTacToe::MultiplayerGame game;
            game.decideFirstMove();
            std::string currentTurn = game.getPlayerOneName();
            TicTacToe::GameStatus status = TicTacToe::CONTINUE;
            while (status == TicTacToe::CONTINUE) {
                game.playerMove(currentTurn);
                game.displayBoard();
                status = game.checkGameStatus();
                currentTurn = currentTurn == game.getPlayerOneName() ?
                    game.getPlayerTwoName() : game.getPlayerOneName();
            }
            game.printEnd(status);
            mainGame.menuCycle();
        }
    }
    std::cout << "\nThank you for playing TicTacToe. Have a good day ahead :)\n";
    return 0;
}
