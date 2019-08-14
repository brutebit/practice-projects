#include "TicTacToe.hpp"
#include <iostream>

TicTacToe::Menu::Menu():
    selectedOption(MO_NONE),
    selectedSoloOption(SGO_NONE),
    selectedMultiplayerOption(MGO_NONE) {}

void TicTacToe::Menu::cycle() {
    display();
    if (selectedOption == MO_NONE) {
        readOption();
        display();
    }
    readSubOption();
}

void TicTacToe::Menu::display() const {
    switch (selectedOption) {
        case MO_NONE:
            std::cout <<
            "------------------\n" <<
            "*** MAIN  MENU ***\n" <<
            "------------------\n" <<
            "1. Play vs machine\n" <<
            "2. Play vs friend\n" <<
            "3. Exit game\n" <<
            "------------------\n";
            break;
        case SOLO:
            std::cout <<
            "------------------\n" <<
            "*** PLAY  SOLO ***\n" <<
            "------------------\n" <<
            "1. Easy\n" <<
            "2. Medium\n" <<
            "3. Hard\n" <<
            "4. Back\n" <<
            "------------------\n";
            break;
        case MULTIPLAYER:
            std::cout <<
            "-------------------\n" <<
            "*** MULTIPLAYER ***\n" <<
            "-------------------\n" <<
            "1. Start\n" <<
            "2. Back\n" <<
            "-------------------\n";
            break;
        default:
            break;
    }
}

void TicTacToe::Menu::readOption() {
    if (selectedOption == MO_NONE) {
        int choice;
        do {
            std::cout << "Enter your choice : ";
            std::cin >> choice;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        while (choice < SOLO || choice > EXIT);
        selectedOption = static_cast<MenuOption>(choice);
    }
}

void TicTacToe::Menu::readSubOption() {
    if (selectedOption == SOLO) {
        int choice;
        do {
            std::cout << "Select difficulty or return to main menu: ";
            std::cin >> choice;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        while (choice < EASY || choice > SGO_BACK);
        selectedSoloOption = static_cast<SoloGameOption>(choice);
        if (selectedSoloOption == SGO_BACK) {
            selectedOption = MO_NONE;
            cycle();
        }
    }
    else if (selectedOption == MULTIPLAYER) {
        int choice;
        do {
            std::cout << "Start the game or return to main menu: ";
            std::cin >> choice;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        while (choice < START || choice > MGO_BACK);
        selectedMultiplayerOption = static_cast<MultiplayerGameOption>(choice);
        if (selectedMultiplayerOption == MGO_BACK) {
            selectedOption = MO_NONE;
            cycle();
        }
    }
}
