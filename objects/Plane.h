#ifndef Plane_h
#define Plane_h

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Exploder.h"
#include "Bomb.h"

class Plane : public Exploder {
   private:
      float pos[3];
      float angle[3];
      float speed;
      int health;
      bool smoke;
      bool die;
      bool dead;
      Bomb * bomb;

   public:
      Plane(float x, float y, float z, int h);
      void draw();
      void damage(int delt);
      float posX();
      float posY();
      float posZ();
      bool isDead();
      bool bombDone();
      float bombX();
      float bombZ();
};

#endif
