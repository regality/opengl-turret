#ifndef Animation_h
#define Animation_h

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "SceneObject.h"

class Frame {
   public:
      Frame(){};
      Frame(float rp,
            float dxp, float dyp, float dzp,
            float ap,
            float axp, float ayp, float azp) {
         rate = rp;
         dx = dxp;
         dy = dyp;
         dz = dzp;
         angle = ap;
         ax = axp;
         ay = ayp;
         az = azp;
      }
      float rate;
      float dx;
      float dy;
      float dz;
      float angle;
      float ax;
      float ay;
      float az;
};

class Animation : public SceneObject {
   public:
      Animation(SceneObject * obj);
      ~Animation();
      void init();
      void draw();
      void nextFrame();
      void addFrame(float rate,
                    float dx, float dy, float dz,
                    float angl,
                    float ax, float ay, float az);
   private:
      Frame ** frames;
      Frame * tf;
      Frame * af;
      SceneObject * object;
      int maxFrames;
      int frameIndex;
      int frameCount;
      int steps;
      bool finished;
      float matrix[16];
};

#endif
