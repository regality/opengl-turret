#ifndef SceneObject_h
#define SceneObject_h

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>

class SceneObject {
   public:
      virtual void draw() = 0;
      virtual ~SceneObject() {}
};

#endif
