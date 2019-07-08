#import "TicTacToe.h"

@implementation TicTacToe {
    Player humanPiece, machinePiece;
    Board *board;
}

static BOOL askYesOrNo(const char *question) {
    size_t resSize = 4;
    char *buf = malloc(resSize * sizeof(char));
    char res = '\0';
    do {
        printf("%s (y/n): ", question);
        getline(&buf, &resSize, stdin);
        res = buf[0];
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

static void checkForWinMove(Board *board, Player piece, int *move, BOOL *found) {
    *move = 1;
    while (*move <= 9) {
        if ([board isMoveLegalAtPosition:*move]) {
            [board makeMoveAtPosition:*move withPiece:piece];
            if ([board checkGameStatus] == (piece == X ? WIN_X : WIN_O)) {
                *found = YES;
                break;
            }
            [board unmakeMoveAtPosition:*move];
        }
        (*move)++;
    }
}

- (instancetype)init {
    if (self = [super init])
        board = [[Board alloc] init];
    return self;
}

+ (void)displayIntro {
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

- (void)decideFirstMove {
    if (askYesOrNo("Do you require the fisrt move?")) {
        humanPiece = X;
        machinePiece = O;
        printf("Then take the first move. You will need it.\n");
    } else {
        machinePiece = X;
        humanPiece = O;
        printf("Your bravery will be your undoing... I will go first.\n");
    }
}

- (void)humanMove {
    int move;
    do {
        move = askForNumber("Where will you move", 1, 9);
        if (![board isMoveLegalAtPosition:move])
            printf("This place is already occupied foolish human!\n");
    }
    while (![board isMoveLegalAtPosition:move]);
    printf("Fine...\n");
    [board makeMoveAtPosition:move withPiece:humanPiece];
}

- (void)machineMove {
    int move;
    BOOL winMoveFound = NO;
    checkForWinMove(board, machinePiece, &move, &winMoveFound);
    if (winMoveFound) {
        [board makeMoveAtPosition:move withPiece:machinePiece];
        printf("I shall take square number %d\n", move);
        return;
    }
    checkForWinMove(board, humanPiece, &move, &winMoveFound);
    if (winMoveFound) {
        [board makeMoveAtPosition:move withPiece:machinePiece];
        printf("I shall take square number %d\n", move);
        return;
    }
    const int bestMoves[9] = {5, 1, 3, 7, 9, 2, 4, 6, 8};;
    for (short i = 0; i < 9; i++) {
        move = bestMoves[i];
        if (![board isMoveLegalAtPosition:move])
            continue;
        [board makeMoveAtPosition:move withPiece:machinePiece];
        break;
    }
    printf("I shall take square number %d\n", move);
}

- (void)run {
    GameStatus status;
    [TicTacToe displayIntro];
    [self decideFirstMove];
    Player currentTurn = humanPiece == X ? humanPiece : machinePiece;
    while ((status = [board checkGameStatus]) == CONTINUE) {
        if (currentTurn == humanPiece) {
            [self humanMove];
            [board display];
            currentTurn = machinePiece;
            continue;
        }
        [self machineMove];
        [board display];
        currentTurn = humanPiece;
    }
    if (status == TIE)
        printf("It's a tie\n"
               "You were most lucky, human, and somehow managed to tie me.\n"
               "Celebrate... for this is the best you will ever achieve.\n");
    else if ((status == WIN_O && humanPiece == O) || (status == WIN_X && humanPiece == X))
        printf("Human won!\n"
               "No, no! It cannot be! Somehow you tricked me, human.\n"
               "But never again! I, the computer, so swear it!\n");
    else
        printf("Machine won!\n"
               "As i predicted, human, I am triumphant once more proof"
               "that computers are superior to humans in all regards.\n");
}

@end
