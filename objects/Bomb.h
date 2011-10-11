#ifndef Bomb_h
#define Bomb_h

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Exploder.h"

class Bomb : public Exploder {
   private:
      float pos[3];
      float forwardSpeed;
      float dropSpeed;
      bool boom;
   public:
      Bomb(float x, float y, float z, float fs);
      void draw();
      bool isDone();
      float posX();
      float posZ();
};

#endif
