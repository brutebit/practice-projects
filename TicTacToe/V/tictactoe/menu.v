module tictactoe

import readline { read_line }

pub enum MenuOption {
	non
	solo
	multi
	exit
}

pub enum SoloGameOption {
	non
	easy
	med
	hard
	back
}

pub enum MultiplayerGameOption {
	non
	start
	back
}

pub type SubOption = MultiplayerGameOption | SoloGameOption

pub struct Menu {
mut:
	selected_option     MenuOption = .non
	selected_sub_option SubOption
}

pub fn (m Menu) display() {
	match m.selected_option {
		.non {
			println('------------------')
			println('*** MAIN  MENU ***')
			println('------------------')
			println('1. Play vs machine')
			println('2. Play vs friend')
			println('3. Exit game')
			println('------------------')
		}
		.solo {
			println('------------------')
			println('*** PLAY  SOLO ***')
			println('------------------')
			println('1. Easy')
			println('2. Medium')
			println('3. Hard')
			println('4. Back')
			println('------------------')
		}
		.multi {
			println('-------------------')
			println('*** MULTIPLAYER ***')
			println('-------------------')
			println('1. Start')
			println('2. Back')
			println('-------------------')
		}
		.exit {
			println('')
		}
	}
}

fn (mut m Menu) cycle() {
	m.display()
	if m.selected_option == .non {
		m.read_option()
		m.display()
	}
	m.read_sub_option()
}

fn (mut m Menu) read_option() {
	mut valid_input := ''
	for {
		input := read_line('Enter your choice: ') or { '' }
		trimmed := input.trim_right('\n')
		if trimmed in ['1', '2', '3'] {
			valid_input = trimmed
			break
		}
	}
	m.set_selected_option(valid_input)
}

fn (mut m Menu) read_sub_option() {
	mut valid_input := ''
	for {
		msg := if m.selected_option == .solo {
			'Choose difficulty or return to main menu: '
		} else if m.selected_option == .multi {
			'Start game or return to main menu: '
		} else {
			''
		}
		input := read_line(msg) or { '' }
		trimmed := input.trim_right('\n')
		if trimmed in ['1', '2'] {
			valid_input = trimmed
			break
		} else if trimmed in ['3', '4'] {
			if m.selected_option == .solo {
				valid_input = trimmed
				break
			}
		}
	}
	m.set_selected_sub_option(valid_input)
}

fn (mut m Menu) set_selected_option(s string) {
	match s {
		'1' { m.selected_option = .solo }
		'2' { m.selected_option = .multi }
		'3' {
            m.selected_option = .exit
            println('Thank you for playing TicTacToe. have a good day ahead:}')
            exit(0)
        }
		else { m.selected_option = .non }
	}
}

fn (mut m Menu) set_selected_sub_option(s string) {
	match m.selected_option {
		.solo {
			if s == '1' {
				m.selected_sub_option = SubOption(SoloGameOption.easy)
			} else if s == '2' {
				m.selected_sub_option = SubOption(SoloGameOption.med)
			} else if s == '3' {
				m.selected_sub_option = SubOption(SoloGameOption.hard)
			} else {
				m.selected_sub_option = SubOption(SoloGameOption.back)
                m.selected_option = .non
                m.cycle()
			}

		}
		.multi {
			if s == '1' {
				m.selected_sub_option = SubOption(MultiplayerGameOption.start)
			} else {
				m.selected_sub_option = SubOption(MultiplayerGameOption.back)
                m.selected_option = .non
                m.cycle()
			}
		}
		else {
			m.selected_sub_option = SubOption(SoloGameOption.non)
		}
	}
}
