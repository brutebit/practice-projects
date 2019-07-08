private func askYesNo(_ question: String) -> Bool {
    var res: String!
    repeat {
        print(question, terminator: " (y/n): ")
        res = readLine()
    } while res.first != "y" && res.first != "n"
    return res.first == "y"
}

private func askForNumber(_ question: String, _ low: Int = 1, _ high: Int = 9) -> Int {
    var number: Int?
    repeat {
        print(question, terminator: " (\(low) - \(high)): ")
        number = Int(readLine() ?? "")
        if (number == nil || number! < low || number! > high) {
            print("That's not a valid number.")
        }
    } while number == nil || number! < low || number! > high
    return number!;
}

private func checkForWinMove(_ testBoard: inout Board, _ piece: Player, _ move: inout Int, _ found: inout Bool) {
    move = 1
    while move <= 9 {
        if testBoard.isMoveLegal(atPosition: move) {
            testBoard.makeMove(atPosition: move, withPiece: piece)
            if testBoard.checkGameStatus() == (piece == X ? .winX : .winO) {
                found = true
                break
            }
            testBoard.unmakeMove(atPosition: move)
        }
        move += 1
    }
}

struct TicTacToe {
    private var humanPiece: Player = NO_ONE, machinePiece: Player = NO_ONE
    private var board = Board()
    
    private static func displayIntro() {
        print("""
            Welcome to the ultimate man-machine showdown: TicTacToe, where human
             brain is pit against silicon processor.
            Make your move known by entering a number, 1 - 9.
            The number corresponds to the desired board position as illustrated:
            \t\t\t1 | 2 | 3
            \t\t\t---------
            \t\t\t4 | 5 | 6
            \t\t\t---------
            \t\t\t7 | 8 | 9
            Prepare yourself human! the battle is about to begin.
            """)
    }
    
    private mutating func decideFirstMove() {
        if askYesNo("Do you require the fisrt move?") {
            humanPiece = X
            machinePiece = O
            print("Then take the first move. You will need it.")
        } else {
            machinePiece = X
            humanPiece = O
            print("Your bravery will be your undoing... I will go first.");
        }
    }
    
    private mutating func humanMove() {
        var move: Int
        repeat {
            move = askForNumber("Where will you move?")
            if !board.isMoveLegal(atPosition: move) {
                print("This place is already occupied foolish human!")
            }
        } while !board.isMoveLegal(atPosition: move);
        print("Fine...")
        board.makeMove(atPosition: move, withPiece: humanPiece)
    }
    
    private mutating func machineMove() {
        var move: Int = 0
        var winMoveFound = false
        var boardCopy = board
        checkForWinMove(&boardCopy, machinePiece, &move, &winMoveFound)
        if winMoveFound {
            board.makeMove(atPosition: move, withPiece: machinePiece)
            print("I shall take square number \(move)")
            return
        }
        boardCopy = board
        checkForWinMove(&boardCopy, humanPiece, &move, &winMoveFound)
        if winMoveFound {
            self.board.makeMove(atPosition: move, withPiece: machinePiece)
            print("I shall take square number \(move)")
            return
        }
        let bestMoves = [5, 1, 3, 7, 9, 2, 4, 6, 8]
        for bestMove in bestMoves {
            move = bestMove
            if !board.isMoveLegal(atPosition: move) {
                continue
            }
            board.makeMove(atPosition: move, withPiece: machinePiece)
            break
        }
        print("I shall take square number \(move)")
    }
    
    mutating func run() {
        TicTacToe.displayIntro()
        self.decideFirstMove()
        var currentTurn = humanPiece == X ? humanPiece : machinePiece
        var status: GameStatus
        repeat {
            if currentTurn == humanPiece {
                self.humanMove()
                board.display()
                currentTurn = machinePiece
                status = board.checkGameStatus()
                continue
            }
            self.machineMove()
            board.display()
            currentTurn = humanPiece
            status = board.checkGameStatus()
        } while status == .Continue
        if status == .tie {
            print("""
                It's a tie.
                You were most lucky, human, and somehow managed to tie me.
                Celebrate... for this is the best you will ever achieve.
            """)
        } else if status == .winO && humanPiece == O || status == .winX && humanPiece == X {
            print("""
                Human won!
                No, no! It cannot be! Somehow you tricked me, human.
                But never again! I, the computer, so swear it!
            """)
        } else {
            print("""
                Machine won!
                As i predicted, human, I am triumphant once more proof
                 that computers are superior to humans in all regards.
            """)
        }
    }
}
