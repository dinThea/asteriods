#include "element.h"
#include "player.h"
#include "cmath"
#include <iostream>

class Shot : public Element {
    public:
        Shot(Player player);
        Shot operator>(double value) { 
            setx(getx() + value*sin(getr())); 
            sety(gety() + value*cos(getr()));             
            return *this;
        }
        bool operator == (Shot& s) { return this->getx() == s.getx() && this->gety() == s.gety(); }
};
