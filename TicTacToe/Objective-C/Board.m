#import "Board.h"

static const int winPositions[8][3] = {
    {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
    {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
    {1, 5, 9}, {3, 5, 7}
};

@implementation Board {
    Player firstRow[3], secondRow[3], thirdRow[3];
}

- (instancetype)init {
    if (self = [super init]) {
        for (short i = 0; i < 3; i++) {
            firstRow[i] = NO_ONE;
            secondRow[i] = NO_ONE;
            thirdRow[i] = NO_ONE;
        }
    };
    return self;
}

- (void)display {
    printf("\t\t\t%c | %c | %c\n", firstRow[0], firstRow[1], firstRow[2]);
    printf("\t\t\t---------\n");
    printf("\t\t\t%c | %c | %c\n", secondRow[0], secondRow[1], secondRow[2]);
    printf("\t\t\t---------\n");
    printf("\t\t\t%c | %c | %c\n", thirdRow[0], thirdRow[1], thirdRow[2]);
}

- (BOOL)isMoveLegalAtPosition:(int)position {
    return [self getPlayerAtPosition:position] == NO_ONE;
}

- (void)makeMoveAtPosition:(int)position withPiece:(Player)piece {
    if (position <= 3)
        firstRow[position - 1] = piece;
    else if (position <= 6)
        secondRow[position - 4] = piece;
    else
        thirdRow[position - 7] = piece;
}

- (void)unmakeMoveAtPosition:(int)position {
    if (position <= 3)
        firstRow[position - 1] = ' ';
    else if (position <= 6)
        secondRow[position - 4] = ' ';
    else
        thirdRow[position - 7] = ' ';
}

- (Player)getPlayerAtPosition:(int)position {
    return (
            position <= 3 ? firstRow[position - 1] :
            position <= 6 ? secondRow[position - 4] :
            position <= 9 ? thirdRow[position - 7] :
        (char)NULL);
}

- (GameStatus)checkGameStatus {
    for (short i = 0; i < 8; i++) {
        Player firstElement, secondElement, thirdElement;
        firstElement = [self getPlayerAtPosition:winPositions[i][0]];
        secondElement = [self getPlayerAtPosition:winPositions[i][1]];
        thirdElement = [self getPlayerAtPosition:winPositions[i][2]];
        if (firstElement == secondElement && secondElement == thirdElement &&
            thirdElement != NO_ONE)
            return (thirdElement == X ? WIN_X : WIN_O);
    }
    for (short i = 0; i < 8; i++)
        for (short j = 0; j < 3; j++)
            if ([self getPlayerAtPosition:winPositions[i][j]] == NO_ONE)
                return CONTINUE;
    return TIE;
}

@end
