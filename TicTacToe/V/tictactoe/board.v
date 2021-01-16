module tictactoe

pub enum Piece {
	x
	o
	empty
}

pub enum Status {
	win_x
	win_o
	tie
	con
}

const (
	winning_positions = [
		[1, 2, 3],
		[4, 5, 6],
		[7, 8, 9],
		[1, 4, 7],
		[2, 5, 8],
		[3, 6, 9],
		[1, 5, 9],
		[3, 5, 7],
	]
)

pub struct Board {
mut:
	first_row  []Piece = []Piece{len:3,init:.empty}
	second_row []Piece = []Piece{len:3,init:.empty}
	third_row  []Piece = []Piece{len:3,init:.empty}
}

pub fn (b Board) display() {
    piece_to_char := fn (piece Piece) string {
        match piece {
            .empty { return ' ' }
            .x { return 'X' }
            .o { return 'O' }
        }
    }
    first1 := piece_to_char(b.first_row[0])
    first2 := piece_to_char(b.first_row[1])
    first3 := piece_to_char(b.first_row[2])
    second1 := piece_to_char(b.second_row[0])
    second2 := piece_to_char(b.second_row[1])
    second3 := piece_to_char(b.second_row[2])
    third1 := piece_to_char(b.third_row[0])
    third2 := piece_to_char(b.third_row[1])
    third3 := piece_to_char(b.third_row[2])
	println('\t\t\t${first1} | ${first2} | ${first3}')
	println('\t\t\t---------')
	println('\t\t\t${second1} | ${second2} | ${second3}')
	println('\t\t\t---------')
	println('\t\t\t${third1} | ${third2} | ${third3}\n')
}

fn (b Board) get_piece(position int) Piece {
	return if position <= 3 {
		b.first_row[position - 1]
	} else if position <= 6 {
		b.second_row[position - 4]
	} else {
		b.third_row[position - 7]
	}
}

pub fn (b Board) is_move_legal(position int) bool {
    if position in [1,2,3,4,5,6,7,8,9] {
	    return b.get_piece(position) == .empty
    }
    return false
}

pub fn (mut b Board) make_move(position int, piece Piece) {
	if position <= 3 {
		b.first_row[position - 1] = piece
	} else if position <= 6 {
		b.second_row[position - 4] = piece
	} else {
		b.third_row[position - 7] = piece
	}
}

pub fn (mut b Board) unmake_move(position int) {
	if position <= 3 {
		b.first_row[position - 1] = .empty
	} else if position <= 6 {
		b.second_row[position - 4] = .empty
	} else {
		b.third_row[position - 7] = .empty
	}
}

pub fn (b Board) check_game_status() Status {
	for win_pos in winning_positions {
		first_element := b.get_piece(win_pos[0])
		second_element := b.get_piece(win_pos[1])
		third_element := b.get_piece(win_pos[2])
		if first_element == second_element &&
			second_element == third_element && third_element != .empty {
			return if third_element == .x {
				Status.win_x
			} else {
				Status.win_o
			}
		}
	}
	for win_pos in winning_positions {
		for win_p in win_pos {
			if b.get_piece(win_p) == .empty {
				return .con
			}
		}
	}
	return .tie
}
