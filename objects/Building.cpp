#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Building.h"

Building::Building(float x, float z, float h, float w) {
   pos[0] = x;
   pos[1] = 0;
   pos[2] = z;
   height = h;
   width = w;
}

float Building::posX() { return pos[0]; }
float Building::posZ() { return pos[2]; }

void Building::draw() {
   glColor3f(0.1, 0.1, 0.1);
   glPushMatrix();
      glTranslatef(pos[0], 0, pos[2]);
      glScalef(width, height, width);
      Cube::draw();
   glPopMatrix();
}
