#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Plane.h"
#include "Sphere.h"

Plane::Plane(float x, float y, float z) {
   pos[0] = x;
   pos[1] = y;
   pos[2] = z;
   die = false;
   dead = false;
   explodeSize = 0;
}

float Plane::posX() { return pos[0]; }
float Plane::posY() { return pos[1]; }
float Plane::posZ() { return pos[2]; }

bool Plane::isDead() {
   return dead;
}

void Plane::explode() {
   die = true;
}

void Plane::draw() {
   if (dead) {
      return;
   }
   Sphere s;
   if (die) {
      pos[2] += 1;
   } else {
      pos[2] += 3;
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
