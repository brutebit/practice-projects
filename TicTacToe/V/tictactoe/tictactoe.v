module tictactoe

pub struct TicTacToe {
mut:
	menu                Menu = Menu{}
pub mut:
	selected_option     MenuOption
	selected_sub_option SubOption
}

pub fn (mut t TicTacToe) cycle_menu() {
	t.menu.cycle()
	t.selected_option = t.menu.selected_option
	t.selected_sub_option = t.menu.selected_sub_option
}
