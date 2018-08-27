#include "element.h"
#include "math.h"

class Projectile : public Element{

    static bool created;
    public:
        Projectile operator>(double value) { 
            setx(getx() + value*sin(getr())); 
            sety(gety() + value*cos(getr()));             
            return *this;
        }
        static bool get_created() { return created; }
        static void set_created( bool value ) { created = value; }
        Projectile( double originx, double originy, double objectivex, double objectivey, double speed );

};
