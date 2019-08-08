const { gameStatus, gamePiece } = require('./enums');

const { WIN_O, WIN_X, TIE, CONTINUE } = gameStatus;
const { X, EMPTY } = gamePiece;

const winningPositions = [
    [1, 2, 3], [4, 5, 6], [7, 8, 9],
    [1, 4, 7], [2, 5, 8], [3, 6, 9],
    [1, 5, 9], [3, 5, 7]
];

class Board {
    constructor() {
        this.firstRow = [];
        this.secondRow = [];
        this.thirdRow = [];
        for (let i = 0; i < 3; i++) {
            this.firstRow[i] = EMPTY;
            this.secondRow[i] = EMPTY;
            this.thirdRow[i] = EMPTY;
        }
    }

    display() {
        console.log(`\t\t\t${this.firstRow[0]} | ${this.firstRow[1]} | ${this.firstRow[2]}`);
        console.log("\t\t\t---------");
        console.log(`\t\t\t${this.secondRow[0]} | ${this.secondRow[1]} | ${this.secondRow[2]}`);
        console.log("\t\t\t---------");
        console.log(`\t\t\t${this.thirdRow[0]} | ${this.thirdRow[1]} | ${this.thirdRow[2]}\n`);
    }

    _getPiece(position) {
        return (
            position <= 3 ? this.firstRow[position - 1] :
            position <= 6 ? this.secondRow[position - 4] :
            position <= 9 ? this.thirdRow[position - 7] : null
        );
    }

    isMoveLegal(position) {
        return this._getPiece(position) == EMPTY;
    }

    makeMove(position, piece) {
        if (position <= 3) {
            this.firstRow[position - 1] = piece;
        } else if (position <= 6) {
            this.secondRow[position - 4] = piece;
        } else {
            this.thirdRow[position - 7] = piece;
        }
    }

    unmakeMove(position) {
        if (position <= 3) {
            this.firstRow[position - 1] = EMPTY;
        } else if (position <= 6) {
            this.secondRow[position - 4] = EMPTY;
        } else {
            this.thirdRow[position - 7] = EMPTY;
        }
    }

    checkGameStatus() {
        for (const winPos of winningPositions) {
            const firstElement = this._getPiece(winPos[0]);
            const secondElement = this._getPiece(winPos[1]);
            const thirdElement = this._getPiece(winPos[2]);
            if (firstElement == secondElement && secondElement == thirdElement &&
                thirdElement != EMPTY) {
                return thirdElement == X ? WIN_X : WIN_O;
            }
        }
        for (const winPos of winningPositions)
            for (const winp of winPos)
                if (this._getPiece(winp) == EMPTY)
                    return CONTINUE;
        return TIE;
    }
}

module.exports = Board;
