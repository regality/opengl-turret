#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Plane.h"
#include "Sphere.h"
#include "Bomb.h"

Plane::Plane(float x, float y, float z, int h) {
   pos[0] = x;
   pos[1] = y;
   pos[2] = z;
   die = false;
   dead = false;
   smoke = false;
   speed = rand() % 200;
   speed /= 100.0;
   speed += 2.0;
   health = h;
   setMaxExplode(10);
   bomb = NULL;
}

float Plane::posX() { return pos[0]; }
float Plane::posY() { return pos[1]; }
float Plane::posZ() { return pos[2]; }

bool Plane::bombDone() { return bomb && bomb->isDone(); }
float Plane::bombX() { return bomb ? bomb->posX() : 0; }
float Plane::bombZ() { return bomb ? bomb->posZ() : 0; }

bool Plane::isDead() {
   return dead;
}

void Plane::damage(int delt) {
   health -= delt;
   if (health <= 0) {
      health = 0;
      die = true;
   }
   smoke = true;
}

void Plane::draw() {
   if (dead) {
      return;
   }
   Sphere s;
   if (die or smoke) {
      speed = 1;
   }
   pos[2] += speed;
   if (pos[2] > 500) {
      pos[2] = -500;
   }

   glPushMatrix();
      glScalef(3.0, 3.0, 3.0);
      glTranslatef(pos[0], pos[1], pos[2]);

      // body
      glPushMatrix();
         glScalef(1.0, 1.0, 10.0);
         s.draw();
      glPopMatrix();

      // tail
      glPushMatrix();
         glTranslatef(0, 0, -8.5);
         glScalef(3.0, 0.2, 0.5);
         s.draw();
         glPushMatrix();
            glRotatef(90, 0, 0, 1);
            s.draw();
         glPopMatrix();
      glPopMatrix();

      // wing
      glPushMatrix();
         glTranslatef(0, 0, 3.0);
         glScalef(10.0, 0.3, 1.0);
         s.draw();
      glPopMatrix();

      if (smoke) {
         glPushMatrix();
            glColor3f(0.3, 0.3, 0.3);
            for (int i = 0; i < 10 - health/10; ++i) {
               int x = rand() % 2;
               int y = rand() % 1;
               int z = -1* rand() % 7;
               if (rand() & 1) x *= -1;
               glTranslatef(x, y, z);
               s.draw();
            }
         glPopMatrix();
      }

      // ball of fire
      if (die) {
         explode();
         dead = done;
      }

   glPopMatrix();

   if (bomb && bomb->isDone()) {
      delete bomb;
      bomb = NULL;
   }
   if (bomb == NULL && rand() % 100 == 0) {
      bomb = new Bomb(pos[0], pos[1], pos[2], speed);
   }
   if (bomb) {
      bomb->draw();
   }

}
