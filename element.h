#ifndef ELEMENT_H
#define ELEMENT_H

class Element {
    double rx;
    double speed[2];
    double pos[2];
    double size;    
    double innersize;
    public:
        double      getx()              { return pos[0];    }
        double      gety()              { return pos[1];    }     
        double      getsiz()            { return size;      } 
        double      getr()              { return rx;        }
        double      getspeedx()         { return speed[0];  }
        double      getspeedy()         { return speed[1];  }        
        void        setr(       double rx )         { this->rx = rx;                    }
        void        setx(       double x  )         { this->pos[0]  = x;                }
        void        sety(       double y  )         { this->pos[1]  = y;                }
        void        setspeed(   double x, double y) { this->speed[0]=x;speed[1]=y;      }
        void        setsize(    double val)         { this->size    = val;              }

};

#endif