#include "shot.h"
#include "cmath"

Shot::Shot(Player player) {
    setr(player.getr());
    setx(player.getx() + player.getsiz()*sin(player.getr()));
    sety(player.gety() + player.getsiz()*cos(player.getr()));
}