const readline = require('readline');

const Menu = require('./Menu');
const SoloGame = require('./SoloGame');
const MultiplayerGame = require('./MultiplayerGame');
const { menuChoices, menuSubChoices, gamePiece, gameStatus } = require('./enums');

const { X } = gamePiece;
const { CONTINUE } = gameStatus

const { SOLO, MULTIPLAYER, EXIT } = menuChoices;
const { solo, multiplayer } = menuSubChoices;

class TicTacToe {
    constructor() {
        this.menu = new Menu();
    }

    static displayIntro() {
        console.log('\nMake your move known by entering a number, 1 - 9.');
        console.log('The number corresponds to the desired board position as illustrated:\n');
        console.log('\t\t\t1 | 2 | 3');
        console.log('\t\t\t---------');
        console.log('\t\t\t4 | 5 | 6');
        console.log('\t\t\t---------');
        console.log('\t\t\t7 | 8 | 9\n');
        console.log('Prepare yourself! the battle is about to begin.\n');
    }

    displayMenu() {
        this.menu.display(this.menu.choice);
    }

    run() {
        this.menu.readChoice(() => {
            switch (this.menu.choice) {
                case SOLO:
                    this.menu.readSubChoice(() => {
                        switch (this.menu.subChoice) {
                            case solo.BACK:
                                this.menu.choice = null;
                                this.menu.display();
                                this.run();
                                break;
                            default:
                                this.ـstart(() => {
                                    this.run();
                                });
                                break;
                        }
                    });
                    break;
                case MULTIPLAYER:
                    this.menu.readSubChoice(() => {
                        switch (this.menu.subChoice) {
                            case multiplayer.BACK:
                                this.menu.choice = null;
                                this.menu.display();
                                this.run();
                                break;
                            default:
                                this.ـstart(() => {
                                    this.run();
                                });
                                break;
                        }
                    });
                    break;
                case EXIT:
                    console.log('\nThank you for playing TicTacToe. Have a good day ahead :)\n');
                    process.exit(0);
            }
            
        });
    }

    _askYesNo(question, callback) {
        const rl = readline.createInterface({
            input: process.stdin,
            output: process.stdout,
            prompt: `${question} (y/n): `
        });
        rl.on('line', line => {
            let first = line.trim()[0];
            if (first == 'y' || first == 'Y') {
                this.userAnswer = true;
                rl.close();
            } else if (first == 'n' || first == 'N') {
                this.userAnswer = false;
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

    ـstart(next) {
        TicTacToe.displayIntro();
        if (this.menu.choice == SOLO) {
            const game = new SoloGame();
            const playTurn = callback => {
                if (game.currentTurn == game.humanPiece) {
                    game.humanMove(() => {
                        game.board.display();
                        game.currentTurn = game.machinePiece;
                        game.status = game.board.checkGameStatus();
                        if (game.status == CONTINUE)
                            playTurn(callback);
                        else 
                            callback();
                    });
                } else {
                    game.machineMove(this.menu.subChoice);
                    game.board.display();
                    game.currentTurn = game.humanPiece;
                    game.status = game.board.checkGameStatus();
                    if (game.status == CONTINUE)
                        playTurn(callback);
                    else 
                        callback();
                }
            }
            game.decideFirstMove(this._askYesNo.bind(game), () => {
                game.currentTurn = game.humanPiece == X ?
                    game.humanPiece : game.machinePiece;
                playTurn(() => {
                    game.printEnd(next);
                });
            });
        } else {
            const game = new MultiplayerGame();
            const playTurn = callback => {
                game.playerMove(() => {
                    game.board.display();
                    game.currentTurn = game.currentTurn == game.player1 ?
                        game.player2: game.player1;
                    game.status = game.board.checkGameStatus();
                    if (game.status == CONTINUE)
                        playTurn(callback);
                    else 
                        callback();
                });
            }
            game.decideFirstMove(() => {
                playTurn(() => {
                    game.printEnd(next);
                });
            });
        }
    }
}

module.exports = TicTacToe;
