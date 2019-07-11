#include <iostream>
#include <vector>
#include <string>
#include "MiniBlackjack.hh"

using namespace std;

int main() {
    cout << "Welcome to Mini-Blackjack!\n\n";
    int numPlayer = 0;
    while (numPlayer < 1 || numPlayer > 7) {
        cout << "How many players? (1 - 7): ";
        cin >> numPlayer;
    }
    vector<string> names;
    string name;
    for (int i = 0; i < numPlayer; i++) {
        cout << "Enter player name: ";
        cin >> name;
        names.push_back(name);
    }
    cout << endl;
    MiniBlackjack game(names);
    char again = 'y';
    while (again != 'n' && again != 'N') {
        game.play();
        cout << "\nDo you want to play again? (y/n): ";
        cin >> again;
    }
    return 0;
}
