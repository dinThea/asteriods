#include "player.h"
#define ACELERATION 0.02
#define MAX_SPEED 0.03

Player::Player() {
    setr(0);
    setspeed(0, 0);
    setx(0);
    sety(0);
    setsize(0.06);
    innersize = 0.05;
}

Player Player::operator+=(double value){

    if (getspeedx() <= MAX_SPEED) {
        setspeed(getspeedx()+ACELERATION*value, getspeedy());
    }
    if (value == 0) {
        setx(getx()+getspeedx());
        setspeed (getspeedx()/1.01, getspeedy()/1.01);
    }
    return *this;
}

Player Player::operator>(double value) {
    
    setr(getr()+value);
    return *this;

}

Player Player::operator<(double value) {

    setr(getr()-value);
    return *this;

}

Player Player::operator-=(double value) {

    if (getspeedy() <= MAX_SPEED) {
        setspeed(getspeedx(), ACELERATION*value+getspeedy());
    } 

    if (value == 0) sety(gety()+getspeedy());
    return *this;

}