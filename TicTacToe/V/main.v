import tictactoe { TicTacToe, SoloGame, MultiplayerGame }

fn main() {
	signal(2, fn () {
		println('\nThank you for playing TicTacToe. Have a good day ahead.)\n')
		exit(0)
	})
	mut game := TicTacToe{}
	game.cycle_menu()
	for game.selected_option != tictactoe.MenuOption.exit {
		tictactoe.display_intro()
		if game.selected_option == tictactoe.MenuOption.solo {
			difficulty := if (game.selected_sub_option as tictactoe.SoloGameOption) ==
				tictactoe.SoloGameOption.easy {
				tictactoe.Difficulty.easy
			} else if (game.selected_sub_option as tictactoe.SoloGameOption) ==
				tictactoe.SoloGameOption.med {
				tictactoe.Difficulty.med
			} else {
				tictactoe.Difficulty.hard
			}
			mut solo_game := SoloGame{
				difficulty: difficulty
			}
			solo_game.decide_first_move()
			mut current_turn := if solo_game.human_piece == tictactoe.Piece.x {
				solo_game.human_piece
			} else {
				solo_game.machine_piece
			}
			mut status := tictactoe.Status.con
			for status == tictactoe.Status.con {
				if current_turn == solo_game.human_piece {
					solo_game.human_move()
					solo_game.display_board()
					status = solo_game.check_game_status()
					current_turn = solo_game.machine_piece
				} else {
					solo_game.machine_move()
					solo_game.display_board()
					status = solo_game.check_game_status()
					current_turn = solo_game.human_piece
				}
			}
			solo_game.print_end(status)
			game.cycle_menu()
		} else if game.selected_option == tictactoe.MenuOption.multi {
			mut multi_game := MultiplayerGame{}
			multi_game.decide_first_move()
			mut status := tictactoe.Status.con
			for status == tictactoe.Status.con {
				multi_game.player_move()
				multi_game.display_board()
				status = multi_game.check_game_status()
			}
			multi_game.print_end(status)
			game.cycle_menu()
		}
	}
	println('Thank you for playing TicTacToe. Have a good day ahead.)')
}
