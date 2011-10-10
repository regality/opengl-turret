#ifndef Cube_h
#define Cube_h

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "SceneObject.h"

class Cube : public SceneObject {
   public:
      void draw();
      ~Cube() {};
};

#endif
