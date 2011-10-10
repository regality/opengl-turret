#ifndef Frog_h
#define Frog_h

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "SceneObject.h"
#include "Sphere.h"
#include "Cylinder.h"

struct FrogLeg {
   float toe[3];
   float ankle[3];
   float knee[3];
   float hip[3];
};

class Frog : public SceneObject {
public:
   Frog();
   void draw();
   void init();
   void jump();
   void nextFrame();
   float getX() { return (legs[0].toe[0] + legs[1].toe[0])/2.0;  }
   float getY() { return legs[0].toe[1]; }
   float getZ() { return legs[0].toe[2]; }
   float * getPos();
   void resetPos();
	virtual ~Frog() {}

   float color[3];
protected:
   void drawLimb(float * begin, float * end);
   void copyLegs();

   bool animate;
   bool animateComplete;
   unsigned int frame;
   float speed;
   float pos[3];

   FrogLeg legs[4];

   FrogLeg * backLeft;
   FrogLeg * backRight;
   FrogLeg * frontLeft;
   FrogLeg * frontRight;
};

#endif
