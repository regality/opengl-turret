#ifndef Cylinder_h
#define Cylinder_h

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "SceneObject.h"

class Cylinder : public SceneObject {
   public:
      void draw();
      void draw(float * begin, float * length);
      ~Cylinder() { image = 0; }
      void setImage(GLuint img) { image = img; }
   private:
      GLuint image;
};

#endif
