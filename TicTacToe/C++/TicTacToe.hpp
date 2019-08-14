#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP
#include <string>

bool askYesNo(const char * const);
int askNumber(const char * const, const int low = 1, const int high = 9);

class TicTacToe {
public:
    enum MenuOption {
        MO_NONE, SOLO, MULTIPLAYER, EXIT
    };

    enum SoloGameOption {
        SGO_NONE, EASY, MEDIUM, HARD, SGO_BACK
    };

    enum MultiplayerGameOption {
        MGO_NONE, START, MGO_BACK
    };

private:
    class Menu {
        MenuOption selectedOption;
        SoloGameOption selectedSoloOption;
        MultiplayerGameOption selectedMultiplayerOption;
        void display() const;
        void readOption();
        void readSubOption();
    public:
        Menu();
        void cycle();
        inline MenuOption getSelectedOption() const {
            return selectedOption;
        }
        inline SoloGameOption getSelectedSoloOption() const {
            return selectedSoloOption;
        }
        inline MultiplayerGameOption getSelectedMultiplayerOption() const {
            return selectedMultiplayerOption;
        }
    };

public:
    enum GamePiece {
        X, O, EMPTY
    };

    enum GameStatus {
        WIN_X, WIN_O, TIE, CONTINUE
    };

private:
    class Board {
        char firstRow[3];
        char secondRow[3];
        char thirdRow[3];
        GamePiece getPiece(const int) const;
        char getPieceAsChar(const GamePiece) const;
    public:
        Board();
        bool isMoveLegal(const int) const;
        void display() const;
        void makeMove(const int, const GamePiece);
        void unmakeMove(const int);
        GameStatus checkGameStatus() const;
    };
    
public:
    class Game {
    protected:
        Board board;
    public:
        virtual void decideFirstMove() =0;
        virtual void printEnd(GameStatus) const =0;
        void displayBoard() const { board.display(); }
        GameStatus checkGameStatus() const { return board.checkGameStatus(); }
    };

    class SoloGame : public Game {
        GamePiece humanPiece;
        GamePiece machinePiece;
    public:
        inline GamePiece getHumanPiece() const { return humanPiece; }
        inline GamePiece getMachinePiece() const { return machinePiece; }
        virtual void decideFirstMove();
        void humanMove();
        void machineMove(SoloGameOption);
        virtual void printEnd(GameStatus) const;
    };

    class MultiplayerGame : public Game {
        struct Player {
            std::string name;
            GamePiece piece;
        };
        Player playerOne;
        Player playerTwo;
    public:
        inline std::string getPlayerOneName(void) const { return playerOne.name; }
        inline std::string getPlayerTwoName(void) const { return playerTwo.name; }
        virtual void decideFirstMove();
        void playerMove(std::string);
        virtual void printEnd(GameStatus) const;
    };

private:
    friend void checkForWinMove(Board * const, const GamePiece, int * const, bool * const);
    Menu menu;
    
public:
    static void displayIntro();
    void menuCycle() { menu.cycle(); }
    inline MenuOption getSelectedOption() const {
        return menu.getSelectedOption();
    }
    inline SoloGameOption getSelectedSoloOption() const {
        return menu.getSelectedSoloOption();
    }
    inline MultiplayerGameOption getSelectedMultiplayerOption() const {
        return menu.getSelectedMultiplayerOption();
    }
};

# endif
