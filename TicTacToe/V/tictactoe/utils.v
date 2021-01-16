module tictactoe

import readline { read_line }

enum Accept {
	yes
	no
}

fn ask_yes_no(qs string) Accept {
	for {
		input := read_line(qs) or { '' }
		trimmed := input.trim_space()
		if trimmed in ['y', 'Y'] {
			return .yes
		} else if trimmed in ['n', 'N'] {
			return .no
		}
	}
	return .no
}

fn ask_for_move(qs string) int {
    mut answer := 0
	for {
		input := read_line(qs) or { '' }
		trimmed := input.trim_space()
		num := trimmed.int()
		// range gives a weird error here
		if num in [1, 2, 3, 4, 5, 6, 7, 8, 9] {
			answer = num
            break
		}
	}
	return answer
}

fn ask_name(qs string) string {
	for {
		input := read_line(qs) or { '' }
		trimmed := input.trim_space()
		if trimmed != '' {
			return trimmed
		}
	}
	return ''
}

pub fn display_intro() {
	println('\nMake your move known by entering a number, 1 - 9.\n')
	println('The number corresponds to the desired board position as illustrated:\n')
	println('\t\t\t1 | 2 | 3')
	println('\t\t\t---------')
	println('\t\t\t4 | 5 | 6')
	println('\t\t\t---------')
	println('\t\t\t7 | 8 | 9\n')
	println('Prepare yourself! the battle is about to begin.\n')
}
