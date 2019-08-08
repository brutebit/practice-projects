exports.menuChoices = {
    SOLO: 1,
    MULTIPLAYER: 2,
    EXIT: 3,
};

exports.menuSubChoices = {
    solo: {
        EASY: 1,
        MEDIUM: 2,
        HARD: 3,
        BACK: 4
    },
    multiplayer: {
        PLAY: 1,
        BACK: 2
    }
}

exports.gameStatus = {
    WIN_X: 0,
    WIN_O: 1,
    TIE: 2,
    CONTINUE: 3
};

exports.gamePiece = {
    X: 'X',
    O: 'O',
    EMPTY: ' '
};
