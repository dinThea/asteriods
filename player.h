// Player header file
#include "element.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player : public Element {

    double innersize;
    public:
        Player();
        double      getinner()          { return innersize; }
        Player operator+=(double value);
        Player operator>(double value);
        Player operator<(double value);
        Player operator-=(double value);
        
};

#endif