#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "depends.h"
using namespace std;

void display(void);
void processKeys(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void specialKeyUp(int key, int x, int y);

const int MAX_ENEMY = 20; // number of planes
const int MAX_ROCKET = 100; // number of rockets
const int MAX_BUILDING = 20; // number of buildings

int SPEED = 20000;  // Frame rate, smaller is faster
const double MOVE_SPEED = 1.0; // camera rotate speed
double viewAngle[3] = { 0.0, 0.0, 0.0 }; // camera angle
bool keys[256];
bool specKeys[256];
bool rocketLeft = true; // use left barrel
int gameBegin; // use to time game
int gameEnd;
int level = 1;

// This should prolly be moved to objects directory
struct Building {
   float posx;
   float posz;
   float height;
   float width;
};

/***********************************
 * Declare your scene objects here *
 ***********************************/
Light light;
Cylinder barrel;
Cube landscape;
Cube box;
Rocket ** missile;
Plane ** enemy;
Building ** building;

/*******************************
 * Create a bunch of planes at *
 * random places in the sky.   *
 *******************************/
void createBadGuys() {
   for (int i = 0; i < MAX_ENEMY; ++i) {
      int x = rand() % 200;
      int y = rand() % 20 + 30;
      int z = rand() % 500;
      if (rand() % 2) x *= -1;
      if (rand() % 2) z *= -1;
      enemy[i] = new Plane(x, y, z, level);
   }
   gameBegin = time(0);
}

/*****************************
 * call setup once at the
 * beginning of the program
 *****************************/
void setup() {
   srand(time(0)); // seed psrng

   // create dynamic arrays
   missile = new Rocket*[MAX_ROCKET];
   enemy = new Plane*[MAX_ENEMY];
   building = new Building*[MAX_BUILDING];

   // put buildings in random places
   for (int i = 0; i < MAX_BUILDING; ++i) {
      building[i] = new Building;
      building[i]->posx = rand() % 200;
      building[i]->posz = rand() % 200;
      building[i]->height = rand() % 7 + 2;
      building[i]->width = rand() % 7 + 2;
      if (rand() % 2) building[i]->posx *= -1;
      if (rand() % 2) building[i]->posz *= -1;
   }

   // set rocket pointers to null
   for (int i = 0; i < MAX_ROCKET; ++i) {
      missile[i] = NULL;
   }

   // need something to shoot at
   createBadGuys();
}

/*****************************
 * call cleanup once at the
 * end of the program
 *****************************/
void cleanup() {
   // we should delete all of our memory...
}

/*
 * Launch a rocket.
 */
void fire() {
   int xPos = 3;
   int index = -1;
   for (int i = 0; i < MAX_ROCKET; ++i) {
      // Check if we have any free rockets
      if (missile[i] == NULL) {
         index = i;
         break;
      }
   }
   if (index >= 0) {
      // choose left or right barrel
      if (rocketLeft) {
         xPos *= -1;
      }
      rocketLeft = !rocketLeft; // next barrel is opposite
      missile[index] = new Rocket(280-viewAngle[0], -1*viewAngle[1], xPos, -1);
   }
}

/*********************************
 * Main display function.
 * Will be called once per frame.
 *********************************/
void display(void) {
   int sTime = time(NULL);
   processKeys();

   float mx, my, mz;
   float ex, ey, ez;
   float dist;

   // check if any rockets hit any planes
   for (int i = 0; i < MAX_ROCKET; ++i) {
      // only check if missile has been fired
      if (missile[i]) {
         mx = missile[i]->posX();
         my = missile[i]->posY();
         mz = missile[i]->posZ();
      } else {
         continue;
      }

      // O(n^2), could be optimized
      for (int j = 0; j < MAX_ENEMY; ++j) {
         if (missile[i] && enemy[j]) {
            ex = enemy[j]->posX();
            ey = enemy[j]->posY();
            ez = enemy[j]->posZ();
            // dist between plane and rocket
            dist = sqrt( (mx-ex)*(mx-ex) + 
                         (my-ey)*(my-ey) + 
                         (mz-ez)*(mz-ez) );
            if (dist < 10) {
               // if it's close, count it a hit
               enemy[j]->explode();
               delete missile[i];
               missile[i] = NULL;
            }
         }
      }
   }

   // check if all enemies are dead
   int c = 0;
   for (int i = 0; i < MAX_ENEMY; ++i) {
      if (enemy[i] && enemy[i]->isDead()) {
         // free memory from dead planes
         delete enemy[i];
         enemy[i] = NULL;
      }
      if (enemy[i]) {
         ++c;
      }
   }
   if (c == 0) {
      gameEnd = time(0);
      cout << "ALL BAD GUYS KILLED.\nSCORE: " << 200 - (gameEnd - gameBegin) << endl;
      ++level;
      createBadGuys();
   }

   glPushMatrix();
   glLoadIdentity();

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   light.draw();

   glTranslatef(0, -2, 0);

   /*****************
    * Begin barrels *
    *****************/
   glPushMatrix();
      glColor3f(0.1, 0.1, 0.1);

      glPushMatrix();
         glTranslatef(-3,0,0);
         glRotatef(280, 1.0, 0.0, 0.0);
         glScalef(0.5,18.0,0.5);
         barrel.draw();
      glPopMatrix();

      glPushMatrix();
         glTranslatef(3,0,0);
         glRotatef(280, 1.0, 0.0, 0.0);
         glScalef(0.5,18.0,0.5);
         barrel.draw();
      glPopMatrix();

   glPopMatrix();
   /*****************
    * End barrels *
    *****************/

   // Rotate camera
   glRotatef(viewAngle[0], 1.0, 0.0, 0.0);
   glRotatef(viewAngle[1], 0.0, 1.0, 0.0);

   glPushMatrix();
      /***************
       * Begin scene *
       ***************/

      // draw all buildings
      for (int i = 0; i < MAX_BUILDING; ++i) {
         glPushMatrix();
            glColor3f(0.1, 0.1, 0.1);
            glTranslatef(building[i]->posx, 0, building[i]->posz);
            glScalef(building[i]->width, building[i]->height, building[i]->width);
            box.draw();
         glPopMatrix();
      }

      // draw the green landscape
      glPushMatrix();
         glColor3f(0.1, 0.3, 0.05);
         glTranslatef(0, -1, 0);
         glScalef(100.0,1.0,100.0);
         landscape.draw();
      glPopMatrix();

      // draw all fired missiles
      glColor3f(0.3, 0.05, 0.05);
      for (int i = 0; i < MAX_ROCKET; ++i) {
         if (missile[i]) {
            missile[i]->draw();
            // once it is too far gone, delete it
            if (missile[i]->getDist() > 1000) {
               delete missile[i];
               missile[i] = NULL;
            }
         }
      }

      // draw all living planes
      for (int i = 0; i < MAX_ENEMY; ++i) {
         if (enemy[i]) {
            glColor3f(0.1, 0.1, 0.4);
            enemy[i]->draw();
         }
      }

      /*************
       * End scene *
       *************/
   glPopMatrix();

   glutSwapBuffers();

   // sleep every iteration
   usleep(SPEED);

   glPopMatrix();
}

/*********************************
 * Put your keyboard processing
 * functions here.
 *********************************/
void processKeys(void) {
   // rotate up
   if (specKeys[101])
      viewAngle[0] -= MOVE_SPEED;

   // rotate down
   if (specKeys[103])
      viewAngle[0] += MOVE_SPEED;

   // rotate left
   if (specKeys[100])
      viewAngle[1] -= 3*MOVE_SPEED;

   // rotate right
   if (specKeys[102])
      viewAngle[1] += 3*MOVE_SPEED;

   // rotate to origin
   if (keys[(int)'r']) {
      viewAngle[0] = 0;
      viewAngle[1] = 0;
      viewAngle[2] = 0;
   }

   // exit
   if (keys[27])
      exit(0);

   // shoot a rocket
   if (keys[(int)' ']) {
      if (level > 7) {
         keys[(int)' '] = false;
      }
      fire();
   }
}

void reshape(int w, int h) {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   gluPerspective(32, (float)w/h, .1, 1000);
   glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
   x = 0;
   y = 0;
   keys[(int)key] = true;
}

void keyboardUp(unsigned char key, int x, int y) {
   x = 0;
   y = 0;
   keys[(int)key] = false;
}

void specialKey(int key, int x, int y) {
   x = 0;
   y = 0;
   specKeys[(int)key] = true;
}

void specialKeyUp(int key, int x, int y) {
   x = 0;
   y = 0;
   specKeys[(int)key] = false;
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);

   glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

   glutInitWindowSize(1200, 800);
   glutInitWindowPosition(32, 32);
   glutCreateWindow("Shoot Em!");
   glClearColor(1, 1, 1, 1.0);

   glutDisplayFunc(display);
   glutIdleFunc(display);
   glutReshapeFunc(reshape);

   glutKeyboardFunc(keyboard);
   glutKeyboardUpFunc(keyboardUp);
   glutSpecialFunc(specialKey);
   glutSpecialUpFunc(specialKeyUp);

   glEnable(GL_NORMALIZE);
   glEnable(GL_BLEND);
   glEnable(GL_POLYGON_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   glEnable(GL_LIGHTING);
   glEnable(GL_COLOR_MATERIAL);

   float zero[] = {.7, .7, .7, 1};
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, zero);
   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

   setup();

   glutMainLoop();

   cleanup();
   return 0;
}
