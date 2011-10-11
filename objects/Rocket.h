#ifndef Rocket_h
#define Rocket_h

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "SceneObject.h"

class Rocket : public SceneObject {
   private:
      float xAngle;
      float yAngle;
      float xPos;
      float yPos;
      float dist;
      float speed;
      bool bullet;

   public:
      Rocket(float xa, float ya, float xp, float yp, bool b);
      void draw();
      float getDist();
      float getSpeed();
      float posX();
      float posY();
      float posZ();
};

#endif
