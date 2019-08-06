use std::io::Write;

mod board;

pub const WIN_X: i32 = 0;
pub const WIN_O: i32 = 1;
pub const CONTINUE: i32 = 2;
pub const TIE: i32 = 0;

pub const X: char = 'X';
pub const O: char = 'O';
const NO_ONE: char = ' ';

fn ask_yes_no(question: &str) -> bool {
    let mut res = String::new();
    loop {
        print!("{} (y/n): ", question);
        std::io::stdout().flush();
        std::io::stdin().read_line(&mut res)
            .expect("Failed to read input");
        if res.as_bytes()[0].eq(&b'n') || res.as_bytes()[0].eq(&b'y') {
            break;
        }
        res.clear();
    }
    res.as_bytes()[0].eq(&b'y')
}

fn ask_number(question: &str, low: usize, high: usize) -> usize {
    let mut number_str = String::new();
    loop {
        print!("{} ({}/{}): ", question, low, high);
        std::io::stdout().flush();
        std::io::stdin().read_line(&mut number_str)
            .expect("Failed to read number");
        let number = match number_str.trim().parse::<usize>() {
            Ok(num) => num,
            Err(_) => 0
        };
        if number >= low && number <= high {
            break;
        }
        number_str.clear();
        println!("That's not a valid number");
    }
    number_str.trim().parse::<usize>().unwrap()
}

fn check_win_move(board: &mut board::Board, piece: char, mov: &mut usize, found: &mut bool) {
    *mov = 1;
    while *mov <= 9 {
        if board.is_move_legal(*mov) {
            board.make_move(*mov, piece);
            let game_status = board.check_game_status();
            let check_against = if piece == X {
                WIN_X
            } else {
                WIN_O
            };
            if game_status == check_against {
                *found = true;
                break;
            }
            board.unmake_move(*mov);
        }
        *mov += 1;
    }
}

pub struct TicTacToe {
    pub human_piece: char,
    pub machine_piece: char,
    board: board::Board
}

impl TicTacToe {
    pub fn new() -> TicTacToe {
        TicTacToe {
            board: board::Board::new(),
            human_piece: NO_ONE,
            machine_piece: NO_ONE
        }
    }

    pub fn display_intro() -> () {
        print!("Welcome to the ultimate man-machine showdown: TicTacToe, where human\n");
        print!(" brain is pit against silicon processor.\nMake your move known by ");
        print!("entering a number, 1 - 9.\nThe number corresponds to the desired board ");
        print!("position as illustrated:\n\t\t\t1 | 2 | 3\n\t\t\t---------\n\t\t\t4 | 5 | 6\n");
        print!("\t\t\t---------\n\t\t\t7 | 8 | 9\nPrepare yourself human!");
        print!(" the battle is about to begin.\n");
    }

    pub fn decide_first_move(&mut self) -> () {
        if ask_yes_no("do you require the first move?") {
            self.human_piece = X;
            self.machine_piece = O;
        } else {
            self.human_piece = O;
            self.machine_piece = X;
        }
    }

    pub fn human_move(&mut self) -> () {
        let mut mov = 0;
        loop {
            mov = ask_number("Where will you move?", 1, 9);
            if !self.board.is_move_legal(mov) {
                print!("This place is already occupied foolish human!\n");
                continue;
            }
            break;
        }
        print!("Fine...\n");
        self.board.make_move(mov, self.human_piece);
    }

    pub fn display_board(&self) -> () {
        self.board.display();
    }

    pub fn check_game_status(&self) -> i32 {
        self.board.check_game_status()
    }

    pub fn machine_move(&mut self) -> () {
        let mut mov = 0;
        let mut win_move_found = false;
        check_win_move(&mut self.board, self.machine_piece, &mut mov, &mut win_move_found);
        if win_move_found {
            self.board.make_move(mov, self.machine_piece);
            print!("I shall take square number {}\n", mov);
            return;
        }
        check_win_move(&mut self.board, self.human_piece, &mut mov, &mut win_move_found);
        if win_move_found {
            self.board.make_move(mov, self.machine_piece);
            print!("I shall take square number {}\n", mov);
            return;
        }
        const BEST_MOVES: [usize; 9] = [5, 1, 3, 7, 9, 2, 4, 6, 8];
        for best_move in BEST_MOVES.iter() {
            mov = *best_move;
            if !self.board.is_move_legal(mov) {
                continue;
            }
            self.board.make_move(mov, self.machine_piece);
            break;
        }
        print!("I shall take square number {}\n", mov);
    }
}