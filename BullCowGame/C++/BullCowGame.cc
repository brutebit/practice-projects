#include "BullCowGame.hh"
#include <fstream>
#include <ctime>
#include <map>
#include <vector>
#include <string>

using namespace std;

BullCowGame::BullCowGame() {
    reset();
}

bool BullCowGame::isIsogram(const string guess) const {
    if (guess.length() <= 1)
        return true;
    map<char, bool> letterToHaveBeenSeen;
    for (auto letter: guess) {
        letter = tolower(letter);
        if (letterToHaveBeenSeen[letter])
            return false;
        letterToHaveBeenSeen[letter] = true;
    }
    return true;
}

bool BullCowGame::isLowercase(const string guess) const {
    bool isLowCase;
    for (auto letter: guess)
        isLowCase = islower(letter) == true;
    return isLowCase;
}

bool BullCowGame::isGameWon() const {
    return gameIsWon;
}

int BullCowGame::getCurrentTry() const {
    return currentTry;
}

int BullCowGame::getHiddenWordLength() const {
    return hiddenWord.length();
}

int BullCowGame::getMaxTries() const {
    map<int, int> wordLengthToMaxTries = {{3,4}, {4,7}, {5,10}, {6,16}, {7,20}};
    return wordLengthToMaxTries[hiddenWord.length()];
}

string BullCowGame::fetchHiddenWord() const {
    vector<string> words;
    string word = "";
    char ch;
    ifstream fin("words.txt");
    while (fin.get(ch) && !fin.eof()) {
        if (ch == '\n') {
            words.push_back(word);
            word = "";
            continue;
        }
        word += ch;
    }
    fin.close();
    srand(time(NULL));
    return words[rand() % words.size()];
}

void BullCowGame::reset() {
    currentTry = 1;
    hiddenWord = fetchHiddenWord();
    gameIsWon = false;
}

GuessStatus BullCowGame::checkGuessValidity(const string guess) const {
    if (guess.length() != getHiddenWordLength())
        return GuessStatus::WRONG_LENGTH;
    else if (!isIsogram(guess))
        return GuessStatus::NOT_ISOGRAM;
    else if (!isLowercase(guess))
        return GuessStatus::NOT_LOWERCASE;
    return GuessStatus::OK;
}

BullCowCount BullCowGame::submitValidGuess(const string guess) {
    currentTry++;
    BullCowCount bullCowCount;
    const int WORD_LENGTH = hiddenWord.length();
    for (int i = 0; i < WORD_LENGTH; i++)
        for (int j = 0; j < WORD_LENGTH; j++)
            if (guess[j] == hiddenWord[i]) {
                if (i == j)
                    bullCowCount.bulls++;
                else
                    bullCowCount.cows++;
            }
    gameIsWon = bullCowCount.bulls == WORD_LENGTH;
    return bullCowCount;
}
