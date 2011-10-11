#ifndef Building_h
#define Building_h

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Cube.h"

class Building : public Cube {
   private:
      float pos[3];
      float height;
      float width;
   public:
      Building(float x, float z, float h, float w);
      float posX();
      float posZ();
      void draw();
};

#endif
