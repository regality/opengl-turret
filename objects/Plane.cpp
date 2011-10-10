#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Plane.h"
#include "Sphere.h"

Plane::Plane(float x, float y, float z, int l) {
   pos[0] = x;
   pos[1] = y;
   pos[2] = z;
   die = false;
   dead = false;
   explodeSize = 0;
   speed = rand() % 200;
   speed /= 100.0;
   speed += 2.0;
   lives = l;
   if (lives > 7) {
      lives = 7;
   }
}

float Plane::posX() { return pos[0]; }
float Plane::posY() { return pos[1]; }
float Plane::posZ() { return pos[2]; }

bool Plane::isDead() {
   return dead;
}

void Plane::explode() {
   if (lives == 1) {
      die = true;
   }
   smoke = true;
   --lives;
}

void Plane::draw() {
   if (dead) {
      return;
   }
   Sphere s;
   if (die) {
      pos[2] += 1;
   } else {
      pos[2] += speed;
   }
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
            for (int i = 0; i < 7 - lives; ++i) {
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
         glPushMatrix();
            glColor3f(0.5, 0.3, 0.05);
            glScalef(explodeSize, explodeSize, explodeSize);
            s.draw();
            explodeSize += 0.3;
            if (explodeSize > 10) {
               dead = true;
            }
         glPopMatrix();
      }

   glPopMatrix();
}
