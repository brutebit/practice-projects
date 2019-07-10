var game = BullCowGame()

func askToPlayAgain() -> Bool {
    var res: String!
    repeat {
        print("Do you want to play again?", terminator: " (y/n): ")
        res = readLine()
    } while (res.first != "y" || res.first == "Y") && (res.first != "n" ||  res.first == "N")
    return res.first == "y" || res.first == "Y"
}

func printIntro() {
    print("""
        Welcome to bulls and cows, a fun word game.
        Can you guess the \(game.getHiddenWordLength()) letters isogram i'm thinking of?!
        """)
}

func printSummary() {
    print(game.isGameWon() ? "WELL DONE! YOU WON :)" : "Better luck next time :(")
}

func getValidGuess() -> String {
    var guess: String?
    var status: GuessStatus = .Invalid
    repeat {
        print("Try \(game.getCurrentTry()) of \(game.getMaxTries()). Enter your guess: ", terminator: "")
        guess = readLine()
        status = game.checkGuessValidity(guess ?? " ")
        if status == .WrongLength {
            print("Please enter a \(game.getHiddenWordLength()) word length.")
        } else if status == .NotLowercase {
            print("Please enter all letters in lowercase.")
        } else if status == .NotIsogram {
            print("The word you've entered is not an isogram. Please enter a word without repeating any letter in it.")
        }
    } while status != .Ok
    return guess ?? " "
}

func play() {
    game.reset()
    var guess: String?
    while !game.isGameWon() && game.getCurrentTry() <= game.getMaxTries() {
        guess = getValidGuess()
        let bullCowCount = game.submitValidGuess(guess ?? " ")
        print("Bulls = \(bullCowCount.bulls). Cows = \(bullCowCount.cows).")
    }
    printSummary()
}

func main() {
    printIntro()
    var wantsToPlayAgain = false
    repeat {
        play()
        wantsToPlayAgain = askToPlayAgain()
    } while wantsToPlayAgain
}

main()
