#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Light.h"

Light::Light() {
   lightNum = nextLightNum;
   nextLightNum++;
   defaultPosition();
   defaultAmbient();
   defaultSpecular();
   defaultDiffuse();
}

Light::Light(float * pos) {
   position[0] = pos[0];
   position[1] = pos[1];
   position[2] = pos[2];
   position[3] = pos[3];
}

Light::Light(float * pos,
             float * spec,
             float * amb,
             float * diff) {
   position[0] = pos[0];
   position[1] = pos[1];
   position[2] = pos[2];
   position[3] = pos[3];
   ambient[0] = amb[0];
   ambient[1] = amb[1];
   ambient[2] = amb[2];
   ambient[3] = amb[3];
   specular[0] = spec[0];
   specular[1] = spec[1];
   specular[2] = spec[2];
   specular[3] = spec[3];
   diffuse[0] = diff[0];
   diffuse[1] = diff[1];
   diffuse[2] = diff[2];
   diffuse[3] = diff[3];
}

void Light::defaultPosition() {
   position[0] = 3.0f;
   position[1] = 0.3f;
   position[2] = 1.0f;
   position[3] = 0.0f;
}

void Light::defaultAmbient() {
   ambient[0] = 0.8f;
   ambient[1] = 0.8f;
   ambient[2] = 0.8f;
   ambient[3] = 1.0f;
}

void Light::defaultSpecular() {
   specular[0] = 1.0f;
   specular[1] = 0.2f;
   specular[2] = 1.0f;
   specular[3] = 1.0f;
}

void Light::defaultDiffuse() {
   diffuse[0] = 1.0f;
   diffuse[1] = 0.2f;
   diffuse[2] = 1.0f;
   diffuse[3] = 1.0f;
}


void Light::draw() {
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0 + lightNum);

   glLightfv(GL_LIGHT0 + lightNum, GL_SPECULAR, specular);
   glLightfv(GL_LIGHT0 + lightNum, GL_POSITION, position);
   glLightfv(GL_LIGHT0 + lightNum, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0 + lightNum, GL_DIFFUSE, diffuse);
}

int Light::nextLightNum = 0;
