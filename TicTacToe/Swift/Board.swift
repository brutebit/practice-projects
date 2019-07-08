enum GameStatus {
    case winX
    case winO
    case tie
    case Continue
}

typealias Player = Character
typealias BoardRow = [Player]

let X: Character = "X", O: Character = "O", NO_ONE: Character = " "

let winPositions: [[Int]] = [
    [1, 2, 3], [4, 5, 6], [7, 8, 9],
    [1, 4, 7], [2, 5, 8], [3, 6, 9],
    [1, 5, 9], [3, 5, 7]
]

struct Board {
    private var firstRow, secondRow, thirdRow: BoardRow
    
    init() {
        firstRow = Array(repeating: NO_ONE, count: 3)
        secondRow = Array(repeating: NO_ONE, count: 3)
        thirdRow = Array(repeating: NO_ONE, count: 3)
    }
    
    func display() {
        print("\t\t\t\(firstRow[0]) | \(firstRow[1]) | \(firstRow[2])")
        print("\t\t\t---------")
        print("\t\t\t\(secondRow[0]) | \(secondRow[1]) | \(secondRow[2])")
        print("\t\t\t---------")
        print("\t\t\t\(thirdRow[0]) | \(thirdRow[1]) | \(thirdRow[2])")
    }
    
    private func getPlayer(atPosition position: Int) -> Player! {
        return (
            position <= 3 ? firstRow[position - 1] :
            position <= 6 ? secondRow[position - 4] :
            position <= 9 ? thirdRow[position - 7] : nil
        )
    }
    
    func isMoveLegal(atPosition position: Int) -> Bool {
        return self.getPlayer(atPosition: position) == NO_ONE
    }
    
    mutating func makeMove(atPosition position: Int, withPiece piece: Player) {
        if position <= 3 {
            firstRow[position - 1] = piece
        } else if position <= 6 {
            secondRow[position - 4] = piece
        } else {
            thirdRow[position - 7] = piece
        }
    }
    
    mutating func unmakeMove(atPosition position: Int) {
        if position <= 3 {
            firstRow[position - 1] = NO_ONE
        } else if position <= 6 {
            secondRow[position - 4] = NO_ONE
        } else {
            thirdRow[position - 7] = NO_ONE
        }
    }
    
    func checkGameStatus() -> GameStatus {
        for winPos in winPositions {
            var firstElement, secondElement, thirdElement: Player
            firstElement = self.getPlayer(atPosition: winPos[0])
            secondElement = self.getPlayer(atPosition: winPos[1])
            thirdElement = self.getPlayer(atPosition: winPos[2])
            if firstElement == secondElement && secondElement == thirdElement  &&
                thirdElement != NO_ONE {
                return (thirdElement == X ? .winX : .winO)
            }
        }
        for winPos in winPositions {
            for winp in winPos {
                if self.getPlayer(atPosition: winp) == NO_ONE {
                    return .Continue
                }
            }
        }
        return .tie
    }
}
