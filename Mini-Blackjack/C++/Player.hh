#ifndef PLAYER_HH
#define PLAYER_HH

#include "AbstractPlayer.hh"
#include <string>

using namespace std;

class Player: public AbstractPlayer {
public:
    Player(const string &name="");
    virtual ~Player(void);
    virtual bool isHitting(void) const;
    void win(void) const;
    void lose(void) const;
    void push(void) const;
};

#endif
