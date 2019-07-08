#import <Foundation/Foundation.h>

typedef NS_ENUM(char, Player) {
    X = 'X', O = 'O', NO_ONE = ' '
};

typedef NS_ENUM(short, GameStatus) {
    WIN_X, WIN_O, TIE, CONTINUE
};

NS_ASSUME_NONNULL_BEGIN

@interface Board : NSObject
- (BOOL)isMoveLegalAtPosition:(int)position;
- (void)makeMoveAtPosition:(int)position withPiece:(Player)piece;
- (void)unmakeMoveAtPosition:(int)position;
- (GameStatus)checkGameStatus;
- (void)display;
@end

NS_ASSUME_NONNULL_END
