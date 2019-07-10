import Foundation

struct BullCowCount {
    var bulls = 0
    var cows = 0
}

enum GuessStatus {
    case Invalid
    case Ok
    case NotIsogram
    case WrongLength
    case NotLowercase
}

struct BullCowGame {
    private var currentTry: Int = 0
    private var gameIsWon: Bool = false
    private var hiddenWord: String = ""
    
    init() {
        self.reset()
    }
    
    mutating func reset() {
        currentTry = 1
        hiddenWord = self.fetchHiddenWord()
        gameIsWon = false
    }
    
    private func fetchHiddenWord() -> String {
        let file: FileHandle? = FileHandle(forReadingAtPath: "words.txt")
        var res: String?
        if file != nil {
            let data = file!.readDataToEndOfFile()
            file!.closeFile()
            let str = NSString(data: data, encoding: 4) as String?
            let arr = str!.components(separatedBy:"\n")
            let rand = Int(arc4random_uniform(UInt32(arr.count - 1)))
            res = arr[rand]
        }
        return res ?? ""
    }
    
    private func isIsogram(_ guess: String) -> Bool {
        if guess.count <= 1 {
            return true
        }
        var letterToHaveBeenSeen = [Character: Bool]()
        let temp = guess.lowercased()
        for letter in temp {
            if letterToHaveBeenSeen[letter] ?? false {
                return false
            } else {
                letterToHaveBeenSeen[letter] = true
            }
        }
        return true
    }
    
    private func isLowercase(_ guess: String) -> Bool {
        var isLowercased: Bool = false
        for letter in guess {
            isLowercased = letter.isLowercase == true
        }
        return isLowercased
    }
    
    func getMaxTries() -> Int {
        let wordLengthToMaxTries: [Int: Int] = [3:4, 4:7, 5:10, 6:16, 7:20]
        return wordLengthToMaxTries[hiddenWord.count]!
    }
    
    func getCurrentTry() -> Int {
        return currentTry
    }
    
    func getHiddenWordLength() -> Int {
        return hiddenWord.count
    }
    
    func isGameWon() -> Bool {
        return gameIsWon
    }
    
    func checkGuessValidity(_ guess: String) -> GuessStatus {
        if guess.count != self.getHiddenWordLength() {
            return .WrongLength
        } else if !self.isIsogram(guess) {
            return .NotIsogram
        } else if !self.isLowercase(guess) {
            return .NotLowercase
        }
        return .Ok
    }
    
    mutating func submitValidGuess(_ guess: String) -> BullCowCount {
        currentTry = currentTry + 1
        var bullCowCount = BullCowCount()
        for i in 0..<self.getHiddenWordLength() {
            for j in 0..<self.getHiddenWordLength() {
                if guess[guess.index(guess.startIndex, offsetBy: j)] ==
                    hiddenWord[hiddenWord.index(hiddenWord.startIndex, offsetBy: i)] {
                    if i == j {
                        bullCowCount.bulls = bullCowCount.bulls + 1
                    } else {
                        bullCowCount.cows = bullCowCount.cows + 1
                    }
                }
            }
        }
        gameIsWon = bullCowCount.bulls == self.getHiddenWordLength()
        return bullCowCount
    }
}
