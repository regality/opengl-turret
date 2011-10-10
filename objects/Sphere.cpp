#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Sphere.h"

void Sphere::draw () {
   glFrontFace(GL_CCW);
   glShadeModel(GL_SMOOTH);

   glPolygonMode(GL_FRONT, GL_FILL);

   float numLats = 30;
   float numLongs = 30;

   float yh, yl;
   float rh, rl;
   float xh, xl;
   float zh, zl;
   
   for (float i = 0; i < numLats; ++i) {
      yh = cos(( i     /numLats) * 3.14159);
      yl = cos(((i + 1)/numLats) * 3.14159);
      rh = sin(( i     /numLats) * 3.14159);
      rl = sin(((i + 1)/numLats) * 3.14159);

      glBegin(GL_QUAD_STRIP);

      glNormal3f(rl, yl, 0);
      glVertex3f(rl, yl, 0);

      glNormal3f(rh, yh, 0);
      glVertex3f(rh, yh, 0);

      for (float j = 1; j <= numLongs; ++j) {
         xh = rh * cos((j/numLongs) * 6.28318);
         xl = rl * cos((j/numLongs) * 6.28318);

         zh = rh * sin((j/numLongs) * 6.28318);
         zl = rl * sin((j/numLongs) * 6.28318);

         glNormal3f(xl, yl, zl);
         glVertex3f(xl, yl, zl);

         glNormal3f(xh, yh, zh);
         glVertex3f(xh, yh, zh);
      }
      glEnd();
   }

}
