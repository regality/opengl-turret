#ifndef Exploder_h
#define Exploder_h

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "SceneObject.h"

class Exploder : public SceneObject {
   protected:
      float explodeSize;
      float maxSize;
      bool done;
   public:
      void setMaxExplode(float max);
      void explode();
};

#endif
