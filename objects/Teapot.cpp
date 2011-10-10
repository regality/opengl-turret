#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Teapot.h"

void Teapot::draw() {
   glFrontFace(GL_CW);

   float specReflection[] = { 0.3f, 0.3f, 0.3f, 0.7f };
   glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
   glMateriali(GL_FRONT, GL_SHININESS, 128);

   glutSolidTeapot(1.0);
}

