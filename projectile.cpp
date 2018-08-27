#include "projectile.h"
#include "math.h"

Projectile::Projectile ( double ox, double oy, double fx, double fy, double speed ) {

    setr( (ox - fx)/(oy - fy) );
    setspeed( speed*sin(getr()), speed*cos(getr()) );
    setx( ox );
    sety( oy );
    setsize( 0.02 );
    created = true;

}

bool Projectile::created = true;
