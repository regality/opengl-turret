#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Exploder.h"
#include "Sphere.h"

void Exploder::setMaxExplode(float max) {
   explodeSize = 0;
   maxSize = max;
   done = false;
}

void Exploder::explode() {
   if (!done) {
      Sphere s;

      explodeSize += 0.7;
      if (explodeSize > maxSize) {
         done = true;
      }

      glPushMatrix();
         glColor3f(0.5, 0.3, 0.05);
         glScalef(explodeSize, explodeSize, explodeSize);
         s.draw();
      glPopMatrix();
   }
}
