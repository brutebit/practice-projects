module tictactoe

import readline { read_line }
import rand { int_in_range }

pub enum Difficulty {
	easy
	med
	hard
}

pub struct SoloGame {
	difficulty    Difficulty [required]
mut:
	board         Board = Board{}
	status        Status
pub mut:
	human_piece   Piece
	machine_piece Piece
}

pub fn (mut s SoloGame) decide_first_move() {
	answer := ask_yes_no('do you require the first move? (y/n): ')
	if answer == .yes {
		s.human_piece = .x
		s.machine_piece = .o
	} else {
		s.human_piece = .o
		s.machine_piece = .x
	}
}

pub fn (mut s SoloGame) human_move() {
	for {
		move := ask_for_move('where will you move? (1-9): ')
		if s.board.is_move_legal(move) {
			println('fine...')
			s.board.make_move(move, s.human_piece)
			break
		} else {
			println('This place is already occupied foolish human!')
		}
	}
}

pub fn (mut s SoloGame) machine_move() {
	play_random := fn (mut s_ptr &SoloGame) {
		mut random := 0
		for !s_ptr.board.is_move_legal(random) {
			random = int_in_range(1, 9)
		}
		println('i shall take square number $random\n')
		s_ptr.board.make_move(random, s_ptr.machine_piece)
	}
	if s.difficulty == .easy {
		play_random(mut s)
		return
	}
	check_for_win_move := fn (mut s_ptr &SoloGame, p Piece) (bool,int) {
		mut move := 1
		for move <= 9 {
			if s_ptr.board.is_move_legal(move) {
				s_ptr.board.make_move(move, p)
				status := if p == .x { Status.win_x } else { Status.win_o }
				if s_ptr.board.check_game_status() == status {
					s_ptr.board.unmake_move(move)
					return true,move
				}
				s_ptr.board.unmake_move(move)
			}
			move++
		}
		return false,move
	}
    human_win_found, h_move := check_for_win_move(mut s, s.human_piece)
    machine_win_found, m_move := check_for_win_move(mut s, s.machine_piece)
	win_move_found := human_win_found || machine_win_found
	if win_move_found {
        move := if human_win_found { h_move } else { m_move }
		println('i shall take square number $move\n')
		s.board.make_move(move, s.machine_piece)
		return
	}
	if s.difficulty == .med {
		play_random(mut s)
		return
	}
	best_moves := [5, 1, 3, 7, 9, 2, 4, 6, 8]
	for m in best_moves {
		if !s.board.is_move_legal(m) {
			continue
		}
	    println('i shall take square number $m\n')
		s.board.make_move(m, s.machine_piece)
		break
	}
}

pub fn (s SoloGame) display_board() {
    s.board.display()
}

pub fn (s SoloGame) check_game_status() Status {
    return s.board.check_game_status()
}

pub fn (s SoloGame) print_end(status Status) {
	if status == .tie {
		println("It\'s a tie.")
		println('You were most lucky, human, and somehow managed to tie me.')
		println('Celebrate... for this is the best you will ever achieve.\n')
	} else if (s.status == .win_o &&
		s.human_piece == .o) ||
		(status == .win_x && s.human_piece == .x) {
		println('Human won!')
		println('No, no! It cannot be! Somehow you tricked me, human.')
		println('But never again! I, the computer, so swear it!\n')
	} else {
		println('Machine won!')
		println('As i predicted, human, I am triumphant once more proof')
		println(' that computers are superior to humans in all regards.\n')
	}
}
