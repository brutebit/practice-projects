#ifndef HOUSE_HH
#define HOUSE_HH

#include "AbstractPlayer.hh"
#include <string>

class House: public AbstractPlayer {
public:
    House(const std::string &name="House");
    virtual ~House(void);
    virtual bool isHitting(void) const;
    void flipFirstCard(void);
};

#endif
