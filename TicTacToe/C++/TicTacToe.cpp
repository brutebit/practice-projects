#include "TicTacToe.hpp"
#include <iostream>
#include <string>

bool askYesNo(const char * const question) {
    std::string res;
    do {
        std::cout << question << " (y/n) : ";
        std::cin >> res;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    while (res[0] != 'y' && res[0] != 'n');
    return res[0] == 'y';
}

int askNumber(const char * const question, const int low, const int high) {
    int move;
    do {
        std::cout << question << " (" << low << " - " << high << ") : ";
        std::cin >> move;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    while (move < low || move > high);
    return move;
}

void TicTacToe::displayIntro() {
    std::cout << "\nMake your move known by entering a number, 1 - 9.\n";
    std::cout << "The number corresponds to the desired board position as illustrated:\n\n";
    std::cout << "\t\t\t1 | 2 | 3\n";
    std::cout << "\t\t\t---------\n";
    std::cout << "\t\t\t4 | 5 | 6\n";
    std::cout << "\t\t\t---------\n";
    std::cout << "\t\t\t7 | 8 | 9\n\n";
    std::cout << "Prepare yourself! the battle is about to begin.\n\n";
}
