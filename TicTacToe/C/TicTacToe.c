#include "TicTacToe.h"
#include <stdio.h>
#include <stdlib.h>

TicTacToe newTicTacToe() {
    TicTacToe game;
    Board board = newBoard();
    game.board = &board;
    return game;
}

static bool askYesOrNo(const char *question) {
    size_t resSize = 4;
    char *buf = malloc(resSize * sizeof(char));
    char res = '\0';
    do {
        printf("%s (y/n): ", question);
        getline(&buf, &resSize, stdin);
        res = buf[0];
        if (res != 'y' && res != 'n')
            printf("Answer yes or no.\n");
    }
    while (res != 'y' && res != 'n');
    free(buf);
    return res == 'y';
}

static int askForNumber(const char *question, int low, int high) {
    int number = 0;
    do {
        printf("%s (%d - %d): ", question, low, high);
        if (scanf("%d", &number) != 1) {
            printf("That's not a valid number.\n");
            while (getchar() != '\n');
        }
        else if (number > high || number < low)
            printf("That's not a valid number.\n");
    }
    while (number > high || number < low);
    return number;
}

static void checkForWinMove(Board *board, Player piece, int *move, bool *found) {
    *move = 1;
    while (*move <= 9) {
        if (isMoveLegal(board, *move)) {
            makeMove(board, *move, piece);
            if (checkGameStatus(board) == (piece == X ? WIN_X : WIN_O)) {
                *found = true;
                break;
            }
            unmakeMove(board, *move);
        }
        (*move)++;
    }
}

static void displayInto() {
    printf("Welcome to the ultimate man-machine showdown: TicTacToe, where human\n"
           " brain is pit against silicon processor.\n"
           "Make your move known by entering a number, 1 - 9.\n"
           "The number corresponds to the desired board position as illustrated:\n\t\t\t"
           "1 | 2 | 3\n\t\t\t"
           "---------\n\t\t\t"
           "4 | 5 | 6\n\t\t\t"
           "---------\n\t\t\t"
           "7 | 8 | 9\n"
           "Prepare yourself human! the battle is about to begin.\n");
}

static void decideFirstMove(TicTacToe *game) {
    if (askYesOrNo("Do you require the fisrt move?")) {
        game->humanPiece = X;
        game->machinePiece = O;
        printf("Then take the first move. You will need it.\n");
    } else {
        game->machinePiece = X;
        game->humanPiece = O;
        printf("Your bravery will be your undoing... I will go first.\n");
    }
}

static void humanMove(TicTacToe *game) {
    int move;
    do {
        move = askForNumber("Where will you move", 1, 9);
        if (!isMoveLegal(game->board, move))
            printf("This place is already occupied foolish human!\n");
    }
    while (!isMoveLegal(game->board, move));
    printf("Fine...\n");
    makeMove(game->board, move, game->humanPiece);
}

static void machineMove(TicTacToe *game) {
    int move;
    bool winMoveFound = false;
    checkForWinMove(game->board, game->machinePiece, &move, &winMoveFound);
    if (winMoveFound) {
        makeMove(game->board, move, game->machinePiece);
        printf("I shall take square number %d\n", move);
        return;
    }
    checkForWinMove(game->board, game->humanPiece, &move, &winMoveFound);
    if (winMoveFound) {
        makeMove(game->board, move, game->machinePiece);
        printf("I shall take square number %d\n", move);
        return;
    }
    const int bestMoves[9] = {5, 1, 3, 7, 9, 2, 4, 6, 8};;
    for (short i = 0; i < 9; i++) {
        move = bestMoves[i];
        if (!isMoveLegal(game->board, move))
            continue;
        makeMove(game->board, move, game->machinePiece);
        break;
    }
    printf("I shall take square number %d\n", move);
}

void run(TicTacToe * game) {
    GameStatus status;
    displayInto();
    decideFirstMove(game);
    Player currentTurn = game->humanPiece == X ? game->humanPiece : game->machinePiece;
    while ((status = checkGameStatus(game->board)) == CONTINUE) {
        if (currentTurn == game->humanPiece) {
            humanMove(game);
            display(game->board);
            currentTurn = game->machinePiece;
            continue;
        }
        machineMove(game);
        display(game->board);
        currentTurn = game->humanPiece;
    }
    if (status == TIE)
        printf("It's a tie\n"
               "You were most lucky, human, and somehow managed to tie me.\n"
               "Celebrate... for this is the best you will ever achieve.\n");
    else if ((status == WIN_O && game->humanPiece == O) || (status == WIN_X && game->humanPiece == X))
        printf("Human won!\n"
               "No, no! It cannot be! Somehow you tricked me, human.\n"
               "But never again! I, the computer, so swear it!\n");
    else
        printf("Machine won!\n"
               "As i predicted, human, I am triumphant once more proof"
               "that computers are superior to humans in all regards.\n");
}
