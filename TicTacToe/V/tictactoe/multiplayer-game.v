module tictactoe

import readline { read_line }

struct Player {
	name  string
	piece Piece
}

pub struct MultiplayerGame {
mut:
    board        Board = Board{}
	current_turn Player
	status       Status
pub mut:
	player1      Player
	player2      Player
}

pub fn (mut m MultiplayerGame) decide_first_move() {
	mut name := ask_name('Enter the name of player1: ')
	m.player1 = Player{
		name: name
		piece: .x
	}
	name = ask_name('Enter the name of player2: ')
	m.player2 = Player{
		name: name
		piece: .o
	}
	m.current_turn = m.player1
}

pub fn (mut m MultiplayerGame) player_move() {
	mut move := ask_for_move('${m.current_turn.name} where will you move? (1-9): ')
	if !m.board.is_move_legal(move) {
		println('This place is already occupied!')
		m.player_move()
	} else {
		println('fine...')
		m.board.make_move(move, m.current_turn.piece)
	}
    m.current_turn = if m.current_turn == m.player1 {
        m.player2
    } else {
        m.player1
    }
}

pub fn (m MultiplayerGame) print_end(status Status) {
	if status == .tie {
		println('It\'s a tie.\n')
	} else if (status == .win_x && m.player1.piece == .x)
        || (status == .win_o && m.player1.piece == .o) {
		println('${m.player1.name} won!\n')
	} else {
		println('${m.player2.name} won!\n')
	}
}

pub fn (m MultiplayerGame) display_board() {
    m.board.display()
}

pub fn (m MultiplayerGame) check_game_status() Status {
    return m.board.check_game_status()
}
