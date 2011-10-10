#ifndef Light_h
#define Light_h

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "SceneObject.h"

class Light : public SceneObject {
   public:
      Light();
      Light(float * pos);
      Light(float * pos,
            float * spec,
            float * amb,
            float * diff);
      void draw();

   private:
      void defaultPosition();
      void defaultAmbient();
      void defaultSpecular();
      void defaultDiffuse();

      int lightNum;
      static int nextLightNum;
      GLfloat position[4];
      GLfloat specular[4];
      GLfloat ambient[4];
      GLfloat diffuse[4];
};

#endif
