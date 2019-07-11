#ifndef ABSTRACT_PLAYER_HH
#define ABSTRACT_PLAYER_HH

#include "Hand.hh"
#include <string>
#include <iostream>

using namespace std;

class AbstractPlayer : public Hand {
    friend ostream &operator<<(ostream &os, const AbstractPlayer &ap);
    
public:
    AbstractPlayer(const string &name="");
    virtual ~AbstractPlayer(void);
    virtual bool isHitting() const =0;
    bool isBusted(void) const;
    void bust(void) const;
    
protected:
    string name;
};

#endif
