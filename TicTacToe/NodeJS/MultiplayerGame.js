const readline = require('readline');

const Board = require('./Board');
const { gamePiece, gameStatus } = require('./enums');

const { X, O } = gamePiece;
const { WIN_O, WIN_X, TIE } = gameStatus

class MultiplayerGame {
    constructor() {
        this.board = new Board();
        this.player1 = {};
        this.player2 = {};
    }

    _askForMove(question, callback, low = 1, high = 9) {
        const rl = readline.createInterface({
            input: process.stdin,
            output: process.stdout,
            prompt: `${this.currentTurn.name} ${question} (${low}-${high}): `
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

    _askName(prompt, onLine, onClose) {
        const rl = readline.createInterface({
            input: process.stdin,
            output: process.stdout,
            prompt: `${prompt}: `
        });
        rl.on('line', line => {
            if (line.trim()) {
                onLine(line);
                rl.close();
            } else 
                rl.prompt();
        }).on('SIGINT', () => {
            console.log('\nThank you for playing TicTacToe. Have a good day ahead :)\n');
            process.exit(0);
        }).on('close', () => {
            onClose();
        });
        rl.prompt();
    }

    decideFirstMove(next) {
        this._askName('Enter the name of player1', line => {
            this.player1.name = line.trim();
            this.player1.piece = X;
            this.currentTurn = this.player1;
        },
        () => {
            this._askName('Enter the name of player2', line => {
                this.player2.name = line.trim();
                this.player2.piece = O;
            },
            () => {
                next();
            });
        });
    }

    playerMove(next) {
        this._askForMove('where will you move?', res => {
            if (!this.board.isMoveLegal(res)) {
                console.log("This place is already occupied!");
                this.playerMove(next);
            } else {
                console.log('fine...\n');
                this.board.makeMove(res, this.currentTurn.piece);
                next();
            }
        });
    }

    printEnd(next) {
        if (this.status == TIE)
            console.log('It\'s a tie.\n');
        else if (this.status == WIN_O && this.player1.piece == O ||
            this.status == WIN_X && this.player1.piece == X)
            console.log(`${this.player1.name} Won!\n`);
        else
            console.log(`${this.player2.name} Won!\n`);
        next();
    }
}

module.exports = MultiplayerGame;
