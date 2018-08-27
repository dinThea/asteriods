#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
#include "player.h"
#include "shot.h"
#include "projectile.h"
#include <list>
#include <cstdlib>
#include <ctime>
#define PI 3.141592
#define STEP 0.01
#define SHOT_SPEED 0.01
#define KEY_SHIFT 112
#define WINDOW_SIZ 700

Player player;
std::list<Shot> shots;
std::list<Projectile> asteroids;

void callback( int value );

void genAsteroids( int value );

void draw();

void callback( int value );

void keyboard(int key, int x, int y);

void drawPolygon( double x[], double y[], int sides );

int main(int argc, char **argv) {

    srand (time(NULL));

    // Initialize GLUT and process user parameters
    glutInit(&argc, argv);

    // Request double buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_SINGLE);

    glutInitWindowSize(WINDOW_SIZ,WINDOW_SIZ);
    glutInitWindowPosition(100, 100);
    glutSetKeyRepeat(1);

    // Create window
    glutCreateWindow("Linux Journal OpenGL Cube");
    glutDisplayFunc(draw);
    glutSpecialFunc(keyboard);

    // Pass control to GLUT for events
    glutMainLoop();

    return 0;


}

void drawPolygon ( double x[], double y[], int sides, int color ) {

    glBegin(GL_LINE_LOOP);            
    glColor3f(color, color, color); 

    for ( int i = 0; i < sides; i++ )
        glVertex3f(x[i], y[i], 0);        
    
    glEnd();     

}

void draw() {

    // std::cout << "draw\n";
    // std::cout << player.gety() << std::endl;
    glClearColor(0, 0, 0, 1.0);    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glBegin(GL_TRIANGLES);            
    glColor3f(1, 1, 1);
    
    glVertex3f(player.getx(), player.gety(), 0);
    glVertex3f(player.getx() + player.getsiz()*sin(PI/6)*sin(player.getr()) , player.gety() + player.getsiz()*sin(PI/3)*cos(player.getr()), 0);
    glVertex3f(player.getx() - player.getsiz()*sin(PI/6)*sin(player.getr() + PI/3)   , player.gety() - player.getsiz()*sin(PI/3)*cos(player.getr() + PI/3), 0);

    glEnd(); 

    glBegin(GL_TRIANGLES);                
    glColor3f(1, 1, 1);
    
    glVertex3f(player.getx(), player.gety(), 0);
    glVertex3f(player.getx() + player.getsiz()*sin(PI/6)*sin(player.getr()) , player.gety() + player.getsiz()*sin(PI/3)*cos(player.getr()), 0);
    glVertex3f(player.getx() + player.getsiz()*sin(PI/6)*sin(player.getr() + 2*PI/3) , player.gety() + player.getsiz()*sin(PI/3)*cos(player.getr() + 2*PI/3), 0);            

    glEnd(); 


    glBegin(GL_TRIANGLES);            
    glColor3f(0, 0, 0);
    
    glVertex3f(player.getx() + 0.01*sin(player.getr()), player.gety() + 0.01*cos(player.getr()), 0);    
    glVertex3f(player.getx() + player.getinner()*sin(PI/6)*sin(player.getr()) , player.gety() + player.getinner()*sin(PI/3)*cos(player.getr()), 0);
    glVertex3f(player.getx() + player.getinner()*sin(PI/6)*sin(player.getr() + 2*PI/3) , player.gety() + player.getinner()*sin(PI/3)*cos(player.getr() + 2*PI/3), 0);            

    glEnd();        

    glBegin(GL_TRIANGLES);            
    glColor3f(0, 0, 0);
    
    glVertex3f(player.getx() + 0.01*sin(player.getr()), player.gety() + 0.01*cos(player.getr()), 0);    
    glVertex3f(player.getx() + player.getinner()*sin(PI/6)*sin(player.getr()) , player.gety() + player.getinner()*sin(PI/3)*cos(player.getr()), 0);
    glVertex3f(player.getx() - player.getinner()*sin(PI/6)*sin(player.getr() + PI/3)   , player.gety() - player.getinner()*sin(PI/3)*cos(player.getr() + PI/3), 0);

    glEnd();        


    for (std::list<Shot>::iterator it = shots.begin(); it != shots.end(); ++it) {

        double x[] = { it->getx() + 0.02*sin(PI/6)*sin(it->getr()), it->getx() - 0.02*sin(PI/6)*sin(it->getr() + PI/3) , it->getx() + 0.02*sin(PI/6)*sin(it->getr() + 2*PI/3) };
        double y[] = { it->gety() + 0.02*sin(PI/3)*cos(it->getr()), it->gety() - 0.02*sin(PI/3)*cos(it->getr() + PI/3), it->gety() + 0.02*sin(PI/3)*cos(it->getr() + 2*PI/3) };
        drawPolygon( x, y, 3, 1);

        glBegin(GL_TRIANGLES);            
        glColor3f(0, 0, 0);

        glVertex3f(it->getx() + 0.01*sin(PI/6)*sin(it->getr()) , it->gety() + 0.01*sin(PI/3)*cos(it->getr()), 0);
        glVertex3f(it->getx() - 0.01*sin(PI/6)*sin(it->getr() + PI/3)   , it->gety() - 0.01*sin(PI/3)*cos(it->getr() + PI/3), 0);
        glVertex3f(it->getx() + 0.01*sin(PI/6)*sin(it->getr() + 2*PI/3) , it->gety() + 0.01*sin(PI/3)*cos(it->getr() + 2*PI/3), 0);            

        glEnd();        
        (*it)>SHOT_SPEED;
        if (abs(it->getx()) > 1) {
            it = shots.erase(it);
        }
        if (abs(it->gety()) > 1) {
            it = shots.erase(it);
        }
    }

    for (std::list<Projectile>::iterator it = asteroids.begin(); it != asteroids.end(); ++it) {

        glBegin(GL_TRIANGLES);            
        glColor3f(1, 1, 1);

        glVertex3f(it->getx() + 0.02*sin(PI/6)*sin(it->getr()) , it->gety() + 0.02*sin(PI/3)*cos(it->getr()), 0);
        glVertex3f(it->getx() - 0.02*sin(PI/6)*sin(it->getr() + PI/3)   , it->gety() - 0.02*sin(PI/3)*cos(it->getr() + PI/3), 0);
        glVertex3f(it->getx() + 0.02*sin(PI/6)*sin(it->getr() + 2*PI/3) , it->gety() + 0.02*sin(PI/3)*cos(it->getr() + 2*PI/3), 0);            

        glEnd(); 

        glBegin(GL_TRIANGLES);            
        glColor3f(0, 0, 0);

        glVertex3f(it->getx() + 0.01*sin(PI/6)*sin(it->getr()) , it->gety() + 0.01*sin(PI/3)*cos(it->getr()), 0);
        glVertex3f(it->getx() - 0.01*sin(PI/6)*sin(it->getr() + PI/3)   , it->gety() - 0.01*sin(PI/3)*cos(it->getr() + PI/3), 0);
        glVertex3f(it->getx() + 0.01*sin(PI/6)*sin(it->getr() + 2*PI/3) , it->gety() + 0.01*sin(PI/3)*cos(it->getr() + 2*PI/3), 0);            

        glEnd();        
        (*it)>SHOT_SPEED;
        if (abs(it->getx()) > 1) {
            it = asteroids.erase(it);
        }
        if (abs(it->gety()) > 1) {
            it = asteroids.erase(it);
        }
    }

       
    glFlush();
    glutTimerFunc(25, callback, 0);
    if (Projectile::get_created() == true) {
        glutTimerFunc(300, genAsteroids, 0);
        Projectile::set_created (false);        
    }
    
}

void callback( int value ) {

    player+=0;
    player-=0;
    // std::cout << "callback\n";
    draw();

}

void keyboard(int key, int x, int y) {

    // std::cout << key << std::endl;
    if (key == GLUT_KEY_RIGHT) {
        glutSetKeyRepeat(1);    
        player>(STEP*30);
    }
    else if (key == GLUT_KEY_LEFT) {
        glutSetKeyRepeat(1);    
        player<(STEP*30);
    }
    if (key == GLUT_KEY_DOWN) {
        glutSetKeyRepeat(1);    
        player-=(-STEP*cos(player.getr()));
        player+=(-STEP*sin(player.getr()));
        
    }
    else if (key == GLUT_KEY_UP) {
        glutSetKeyRepeat(1);    
        player-=( STEP*cos(player.getr()));
        player+=( STEP*sin(player.getr()));
        
    } if (key == KEY_SHIFT) {
        glutSetKeyRepeat(1);    
        Shot shot(player);
        shots.push_back(shot);
        // std::cout << "shot!" << std::endl;   
    }

    // glutPostRedisplay();

}

void genAsteroids( int value ) {
    static int counter = 0;
    double x[] = { (rand() % 100) / 100.0 ,(rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0, 1 };
    if ( rand() % 100 > 50 ) {
        if ( rand() % 100 > 50 ) x[0] = -1;
        else    x[1] = -1;
    } else {                
        if ( rand() % 100 > 50 ) x[0] = 1; 
        else    x[1] = 1;
    }
    Projectile asteroid( x[0], x[1], x[2], x[3], 1);         
    asteroids.push_back( asteroid );
    std::cout << "Asteroid " << counter << std::endl;   
    counter++;
}
