const WIN_POSITIONS: [[usize; 3]; 8] = [
    [1, 2, 3], [4, 5, 6], [7, 8, 9],
    [1, 4, 7], [2, 5, 8], [3, 6, 9],
    [1, 5, 9], [3, 5, 7]
];

pub struct Board {
    first_row: [char; 3],
    second_row: [char; 3],
    third_row: [char; 3]
}

impl Board {
    pub fn new() -> Board {
        Board {
            first_row: [super::NO_ONE; 3],
            second_row: [super::NO_ONE; 3],
            third_row: [super::NO_ONE; 3]
        }
    }

    pub fn display(&self) -> () {
        print!("\t\t\t{} | {} | {}\n",
               self.first_row[0], self.first_row[1], self.first_row[2]);
        print!("\t\t\t---------\n");
        print!("\t\t\t{} | {} | {}\n",
               self.second_row[0], self.second_row[1], self.second_row[2]);
        print!("\t\t\t---------\n");
        print!("\t\t\t{} | {} | {}\n",
               self.third_row[0], self.third_row[1], self.third_row[2]);
    }

    fn get_player(&self, position: usize) -> char {
        if position <= 3 {
            return self.first_row[position - 1]
        }
        if position <= 6 {
            return self.second_row[position - 4]
        }
        self.third_row[position - 7]
    }

    pub fn is_move_legal(&self, position: usize) -> bool {
        self.get_player(position) == super::NO_ONE
    }

    pub fn make_move(&mut self, position: usize, piece: char) -> () {
        if position <= 3 {
            self.first_row[position - 1] = piece;
        } else if position <= 6 {
            self.second_row[position - 4] = piece;
        } else {
            self.third_row[position - 7] = piece;
        }
    }

    pub fn unmake_move(&mut self, position: usize) -> () {
        if position <= 3 {
            self.first_row[position - 1] = super::NO_ONE;
        } else if position <= 6 {
            self.second_row[position - 4] = super::NO_ONE;
        } else {
            self.third_row[position - 7] = super::NO_ONE;
        }
    }

    pub fn check_game_status(&self) -> i32 {
        for win_pos in WIN_POSITIONS.iter() {
            let first_element = self.get_player(win_pos[0]);
            let second_element = self.get_player(win_pos[1]);
            let third_element = self.get_player(win_pos[2]);
            if first_element == second_element && second_element == third_element &&
                third_element != super::NO_ONE {
                if third_element == super::X {
                    return super::WIN_X;
                }
                return super::WIN_O;
            }
        }
        for win_pos in WIN_POSITIONS.iter() {
            for win_p in win_pos {
                if self.get_player(*win_p) == super::NO_ONE {
                    return super::CONTINUE;
                }
            }
        }
        super::TIE
    }
}
