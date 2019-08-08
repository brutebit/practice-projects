const readline = require('readline');

const Board = require('./Board');
const { menuSubChoices, gamePiece, gameStatus } = require('./enums');

const { X, O } = gamePiece;
const { WIN_O, WIN_X, TIE } = gameStatus

const { EASY, MEDIUM } = menuSubChoices.solo;

class SoloGame {
    constructor() {
        this.board = new Board();
    }

    _askForMove(question, callback, low = 1, high = 9) {
        const rl = readline.createInterface({
            input: process.stdin,
            output: process.stdout,
            prompt: `${question} (${low}-${high}): `
        });
        rl.on('line', line => {
            const number = Number(line.trim());
            if (number <= high && number >= low) {
                this.userAnswer = number;
                rl.close();
            } else
                rl.prompt();
        }).on('SIGINT', () => {
            console.log('\nThank you for playing TicTacToe. Have a good day ahead :)\n');
            process.exit(0);
        }).on('close', () => {
            callback(this.userAnswer);
        });
        rl.prompt();
    }

    decideFirstMove(askYesNo, next) {
        askYesNo('Do you require the first move?', res => {
            if (res) {
                this.humanPiece = X;
                this.machinePiece = O;
                console.log("\nThen take the first move. You will need it.\n");
            } else {
                this.machinePiece = X;
                this.humanPiece = O;
                console.log("\nYour bravery will be your undoing... I will go first.\n");
            }
            next();
        });
    }

    humanMove(next) {
        this._askForMove("Where will you move?", res => {
            if (!this.board.isMoveLegal(res)) {
                console.log("This place is already occupied foolish human!");
                this.humanMove(next);
            } else {
                console.log('fine...');
                this.board.makeMove(res, this.humanPiece);
                next();
            }
        });
    }

    machineMove(difficulty) {
        const playRandom = () => {
            let randMove;
            do randMove = Math.floor((Math.random() * 9) + 1);
            while (!this.board.isMoveLegal(randMove));
            console.log(`I shall take square number ${randMove}\n`);
            this.board.makeMove(randMove, this.machinePiece);
        }
        if (difficulty == EASY) {
            playRandom();
            return;
        }
        let move;
        const checkForWinMove = piece => {
            move = 1;
            while (move != 9) {
                if (this.board.isMoveLegal(move)) {
                    this.board.makeMove(move, piece);
                    if (this.board.checkGameStatus() == (piece == X ? WIN_X : WIN_O)) {
                        this.board.unmakeMove(move);
                        return true;
                    }
                    this.board.unmakeMove(move);
                }
                move++;
            }
            return false;
        }
        let winMoveFound = checkForWinMove(this.machinePiece) ||
            checkForWinMove(this.humanPiece);
        if (winMoveFound) {
            console.log(`I shall take square number ${move}\n`);
            this.board.makeMove(move, this.machinePiece);
            return;
        }
        if (difficulty == MEDIUM) {
            playRandom();
            return;
        }
        let bestMoves = [5, 1, 3, 7, 9, 2, 4, 6, 8];
        for (let bestMove of bestMoves) {
            move = bestMove;
            if (!this.board.isMoveLegal(move))
                continue;
            this.board.makeMove(move, this.machinePiece);
            break;
        }
        console.log(`I shall take square number ${move}\n`);
    }

    printEnd(next) {
        if (this.status == TIE) {
            console.log('It\'s a tie.');
            console.log('You were most lucky, human, and somehow managed to tie me.');
            console.log('Celebrate... for this is the best you will ever achieve.\n');
        } else if (this.status == WIN_O && this.humanPiece == O ||
            this.status == WIN_X && this.humanPiece == X) {
            console.log('Human won!');
            console.log('No, no! It cannot be! Somehow you tricked me, human.');
            console.log('But never again! I, the computer, so swear it!\n');
        } else {
            console.log('Machine won!');
            console.log('As i predicted, human, I am triumphant once more proof');
            console.log(' that computers are superior to humans in all regards.\n');
        }
        next();
    }
}

module.exports = SoloGame;
