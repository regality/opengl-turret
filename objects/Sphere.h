#ifndef Sphere_h
#define Sphere_h

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "SceneObject.h"

class Sphere : public SceneObject {
   public:
      void draw();
      ~Sphere() {}
};

#endif
