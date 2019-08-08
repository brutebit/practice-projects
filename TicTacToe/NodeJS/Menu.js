const readline = require('readline');

const { menuChoices, menuSubChoices } = require('./enums');

const { SOLO, MULTIPLAYER, EXIT } = menuChoices;
const { solo, multiplayer } = menuSubChoices;
const { EASY, MEDIUM, HARD } = solo;
const { PLAY } = multiplayer;

class Menu {
    constructor() {
        this.choice = null;
        this.options = [
            '------------------',
            '*** MAIN  MENU ***',
            '------------------',
            '1. Play vs machine',
            '2. Play vs friend',
            '3. Exit game',
            '------------------'
        ];
        this.subOptions = {
            solo: [
                '------------------',
                '*** PLAY  SOLO ***',
                '------------------',
                '1. Easy',
                '2. Medium',
                '3. Hard',
                '4. Back',
                '------------------'
            ],
            multiplayer: [
                '-------------------',
                '*** MULTIPLAYER ***',
                '-------------------',
                '1. Start',
                '2. Back',
                '-------------------'
            ]
        }
    }

    display() {
        if (this.choice == null)
            for (let opt of this.options)
                console.log(opt);
        else if (this.choice == SOLO)
            for (let opt of this.subOptions.solo)
                console.log(opt);
        else if (this.choice == MULTIPLAYER)
            for (let opt of this.subOptions.multiplayer)
                console.log(opt);
    }
    
    readChoice(callback) {
        const rl = readline.createInterface({
            input: process.stdin,
            output: process.stdout,
            prompt: 'Enter your choice: '
        });
        rl.on('line', line => {
            switch (Number(line.trim())) {
                case SOLO:
                    this.choice = SOLO;
                    rl.close();
                    break;
                case MULTIPLAYER:
                    this.choice = MULTIPLAYER;
                    rl.close();
                    break;
                case EXIT:
                    this.choice = EXIT;
                    rl.close();
                    break;
                default:
                    rl.prompt();
                    break;
            }
        }).on('SIGINT', () => {
            console.log('\nThank you for playing TicTacToe. Have a good day ahead :)\n');
            process.exit(0);
        }).on('close', () => {
            this.display(this.choice);
            callback();
        });
        if (!this.choice)
            rl.prompt();
        else
            rl.close();
    }

    readSubChoice(callback) {
        if (this.choice == SOLO) {
            const rl = readline.createInterface({
                input: process.stdin,
                output: process.stdout,
                prompt: 'Choose difficulty or return to main menu: '
            });
            rl.on('line', line => {
                switch (Number(line.trim())) {
                    case EASY:
                        this.subChoice = EASY;
                        rl.close();
                        break;
                    case MEDIUM:
                        this.subChoice = MEDIUM;
                        rl.close();
                        break;
                    case HARD:
                        this.subChoice = HARD;
                        rl.close();
                        break;
                    case solo.BACK:
                        this.subChoice = solo.BACK;
                        rl.close();
                        break;
                    default:
                        rl.prompt();
                        break;
                }
            }).on('SIGINT', () => {
                console.log('\nThank you for playing TicTacToe. Have a good day ahead :)\n');
                process.exit(0);
            }).on('close', () => {
                callback();
            });
            rl.prompt();
        } else if (this.choice == MULTIPLAYER) {
            const rl = readline.createInterface({
                input: process.stdin,
                output: process.stdout,
                prompt: 'Start game or return to main menu: '
            });
            rl.on('line', line => {
                switch (Number(line.trim())) {
                    case PLAY:
                        this.subChoice = PLAY;
                        rl.close();
                        break;
                    case multiplayer.BACK:
                        this.subChoice = multiplayer.BACK;
                        rl.close();
                        break;
                    default:
                        rl.prompt();
                        break;
                }
            }).on('SIGINT', () => {
                console.log('\nThank you for playing TicTacToe. Have a good day ahead :)\n');
                process.exit(0);
            }).on('close', () => {
                callback();
            });
            rl.prompt();
        }
    }

}

module.exports = Menu;
