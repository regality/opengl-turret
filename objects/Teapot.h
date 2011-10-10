#ifndef Teapot_h
#define Teapot_h

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "SceneObject.h"

class Teapot : public SceneObject {
   public:
      void draw();
};

#endif
