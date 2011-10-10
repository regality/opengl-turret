#ifndef Pyramid_h
#define Pyramid_h

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "SceneObject.h"

class Pyramid : public SceneObject {
   public:
      void draw();
      ~Pyramid() {};
};

#endif
