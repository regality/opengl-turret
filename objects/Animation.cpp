#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Animation.h"

Animation::Animation(SceneObject * obj) {
   object = obj;
   maxFrames = 20;
   frameIndex = -1;
   frameCount = 0;
   frames = new Frame*[maxFrames];
   af = new Frame(1,0,0,0,0,0,0,0);
   tf = new Frame(1,0,0,0,0,0,0,0);
   glPushMatrix();
      glLoadIdentity();
      glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
   glPopMatrix();
}

Animation::~Animation() {
   for (int i = 0; i < frameCount; ++i) {
      delete frames[i];
   }
   delete[] frames;
   delete af;
   delete tf;
}

void Animation::addFrame(float rate,
                         float dx, float dy, float dz,
                         float angle,
                         float ax, float ay, float az) {
   if (frameCount == maxFrames) {
      return;
   }
   frames[frameCount] = new Frame(rate, dx, dy, dz, angle, ax, ay, az);
   ++frameCount;
}

void Animation::init() {
   if (frameCount == 0) {
      return;
   }
   frameIndex = 0;
   tf = frames[0];
   steps = 0;
}

void Animation::nextFrame() {
   if (frameCount == 0) {
      return;
   }
   af->dx += tf->dx;
   af->dy += tf->dy;
   af->dz += tf->dz;

   glPushMatrix();
      glLoadIdentity();
      glRotatef(tf->angle, tf->ax, tf->ay, tf->az);
      glMultMatrixf(matrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
   glPopMatrix();

   if (frameIndex == frameCount - 1) {
      finished = true;
      delete tf;
      tf = new Frame(1,0,0,0,0,0,0,0);
   } else {
      ++frameIndex;
      tf = frames[frameIndex];
      steps = 0;
   }
}

void Animation::draw() {
   if (steps >= tf->rate) {
      nextFrame();
   }
   glPushMatrix();
      glTranslatef(af->dx + tf->dx*(steps/tf->rate),
                   af->dy + tf->dy*(steps/tf->rate),
                   af->dz + tf->dz*(steps/tf->rate));
      glRotatef(tf->angle*(steps/tf->rate),
                tf->ax,
                tf->ay,
                tf->az);
      glMultMatrixf(matrix);

   object->draw();

   glPopMatrix();
   ++steps;
}
