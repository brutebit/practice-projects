#include "BullCowGame.hh"
#include <iostream>
#include <string>

using namespace std;

BullCowGame game;

bool askToPlayAgain(void);
void printIntro(void);
void playGame(void);
void printSummary(void);
string getValidGuess(void);

int main() {
    bool wantsToPlayAgain = false;
    printIntro();
    do
        playGame();
    while ((wantsToPlayAgain = askToPlayAgain()));
    return 0;
}

void printIntro() {
    cout << "Welcome to bulls and cows, a fun word game." << endl;
    cout << "Can you guess the " << game.getHiddenWordLength() << " letters isogram i'm thinking of ?!" << endl;
}

string getValidGuess() {
    string guess = "";
    GuessStatus status = GuessStatus::INVALID;
    do {
        int currentTry = game.getCurrentTry();
        cout << "Try " << currentTry << " of " << game.getMaxTries() << ". Enter your guess: ";
        getline(cin, guess);
        status = game.checkGuessValidity(guess);
        switch (status) {
            case GuessStatus::WRONG_LENGTH:
                cout << "Please enter a " << game.getHiddenWordLength();
                cout << " word length." << endl;
                break;
            case GuessStatus::NOT_LOWERCASE:
                cout << "Please enter all letters in lowercase." << endl;
                break;
            case GuessStatus::NOT_ISOGRAM:
                cout << "The word you've entered is not an isogram.";
                cout << " Please enter a word without repeating any letter in it." << endl;
                break;
            default:
                break;
        }
    }
    while (status != GuessStatus::OK);
    return guess;
}

void playGame() {
    game.reset();
    string guess = "";
    while (!game.isGameWon() && game.getCurrentTry() != game.getMaxTries()) {
        guess = getValidGuess();
        BullCowCount bullCowCount = game.submitValidGuess(guess);
        cout << "Bulls = " << bullCowCount.bulls;
        cout << ". Cows = " << bullCowCount.cows << endl;
    }
    cout << endl;
    printSummary();
}

bool askToPlayAgain() {
    cout << "Do you want to play again? (y/n): " << endl;
    string res = "";
    getline(cin, res);
    return res[0] == 'y' || res[0] == 'Y';
}

void printSummary() {
    cout << (game.isGameWon() ? "WELL DONE! YOU WON :)" : "Better luck next time :(");
    cout << endl;
}
