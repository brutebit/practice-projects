mod tictactoe;
use tictactoe::{
    TicTacToe, WIN_O, WIN_X, CONTINUE, TIE, X, O
};

fn main() {
    TicTacToe::display_intro();
    let mut game = TicTacToe::new();
    game.decide_first_move();
    let mut current_turn = if game.human_piece == X {
        game.human_piece
    } else {
        game.machine_piece
    };
    let mut status = CONTINUE;
    while status == CONTINUE {
        if current_turn == game.human_piece {
            game.human_move();
            game.display_board();
            current_turn = game.machine_piece;
            status = game.check_game_status();
            continue;
        }
        game.machine_move();
        game.display_board();
        current_turn = game.human_piece;
        status = game.check_game_status();
    }
    if status == TIE {
        print!("It's a tie.\nYou were most lucky, human, and somehow managed to tie me.\n");
        print!("Celebrate... for this is the best you will ever achieve.");
    } else if status == WIN_O && game.human_piece == O ||
        status == WIN_X && game.human_piece == X {
        print!("Human won!\nNo, no! It cannot be! Somehow you tricked me, human.\n");
        print!("But never again! I, the computer, so swear it!");
    } else {
        print!("Machine won!\nAs i predicted, human, I am triumphant once more proof");
        print!(" that computers are superior to humans in all regards.");
    }
}