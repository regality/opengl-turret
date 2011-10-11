#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Bomb.h"
#include "Sphere.h"

Bomb::Bomb(float x, float y, float z, float fs) {
   pos[0] = x;
   pos[1] = y;
   pos[2] = z;
   forwardSpeed = fs;
   dropSpeed = 0;
   boom = false;
   setMaxExplode(10);
}

bool Bomb::isDone() {
   return done;
}

float Bomb::posX() { return pos[0]; }
float Bomb::posZ() { return pos[2]; }

void Bomb::draw() {
   if (done) {
      return;
   }
   Sphere s;

   if (!boom) {
      pos[2] += forwardSpeed;
      pos[1] -= dropSpeed;
      forwardSpeed *= 0.85;
      dropSpeed += 0.1;
   }

   if (pos[1] <= 0) {
      boom = true;
   }

   glPushMatrix();
      glTranslatef(pos[0], pos[1], pos[2]);
      glPushMatrix();
         glScalef(1, 1, 5);
         s.draw();
      glPopMatrix();
      if (boom) {
         explode();
      }
   glPopMatrix();
}
