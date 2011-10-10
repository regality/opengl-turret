#ifndef Plane_h
#define Plane_h

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "SceneObject.h"

class Plane : public SceneObject {
   private:
      float pos[3];
      float angle[3];
      bool die;
      bool dead;
      float explodeSize;

   public:
      Plane(float x, float y, float z);
      void draw();
      void explode();
      float posX();
      float posY();
      float posZ();
      bool isDead();
};

#endif
