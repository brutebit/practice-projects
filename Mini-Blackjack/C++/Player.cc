#include "Player.hh"
#include "AbstractPlayer.hh"
#include <string>

using namespace std;

Player::Player(const string &name):
    AbstractPlayer(name) {}

Player::~Player() {}

bool Player::isHitting() const {
    cout << name << ", do you want a hit? (y/n): ";
    char res;
    cin >> res;
    return (res == 'y' || res == 'Y');
}

void Player::win() const {
    cout << name << " wins.\n";
}

void Player::lose() const {
    cout << name << " loses.\n";
}

void Player::push() const {
    cout << name << " pushes.\n";
}
