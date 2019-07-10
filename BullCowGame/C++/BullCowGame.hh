#ifndef BULL_COW_GAME_HH
#define BULL_COW_GAME_HH

#include <string>

using std::string;

struct BullCowCount {
    int bulls = 0;
    int cows = 0;
};

enum GuessStatus {
    INVALID,
    OK,
    NOT_ISOGRAM,
    WRONG_LENGTH,
    NOT_LOWERCASE
};

class BullCowGame {
    int currentTry;
    bool gameIsWon;
    string hiddenWord;
    
    bool isIsogram(const string) const;
    bool isLowercase(const string) const;
    string fetchHiddenWord(void) const;
    
    
public:
    BullCowGame(void);
    void reset(void);
    bool isGameWon(void) const;
    int getMaxTries(void) const;
    int getCurrentTry(void) const;
    int getHiddenWordLength(void) const;
    GuessStatus checkGuessValidity(const string) const;
    BullCowCount submitValidGuess(const string);
};

#endif
