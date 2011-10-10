#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Cylinder.h"

void Cylinder::draw(float * begin, float * length) {
   float end[3] = {begin[0] + length[0], begin[1] + length[1], begin[2] + length[2]};
   float mag = sqrt(length[0]*length[0] + length[1]*length[1] + length[2]*length[2]);
   float norm[3] = {length[0]/mag, length[1]/mag, length[2]/mag};
   float cross[3] = {norm[2], 0, -1*norm[0]};
   float angle = acos(norm[1]) * 180 / 3.14159f;

   glPushMatrix();
   glTranslatef(begin[0], begin[1], begin[2]);
   glRotatef(angle, cross[0], cross[1], cross[2]);
   glScalef(1, mag, 1);
   draw();
   glPopMatrix();
}

void Cylinder::draw () {
   glPushMatrix();
   //glFrontFace(GL_CW);
   glDisable(GL_CULL_FACE);
   glShadeModel(GL_SMOOTH);
   glPolygonMode(GL_FRONT, GL_FILL);

   float numLats = 20;
   float numLongs = 20;
   float length = 1;
   float radius = 1;
   float latSize = length/numLats;
   float x1, x2, y1, y2, z1, z2;
   float cosA, sinA, cosB, sinB;

   if (image != 0) {
      glBindTexture(GL_TEXTURE_2D, image);
   }
   
   for (float i = 0; i < numLats; ++i) {

      cosA = cos(( i     /numLats) * 6.28318);
      sinA = sin(( i     /numLats) * 6.28318);
      cosB = cos(((i + 1)/numLats) * 6.28318);
      sinB = sin(((i + 1)/numLats) * 6.28318);
      x1 = radius * cosA;
      x2 = radius * cosB;
      y1 = 0;
      y2 = 0;
      z1 = radius * sinA;
      z2 = radius * sinB;
      glBegin(GL_QUAD_STRIP);
      if (image != 0)
         glTexCoord2f(i/numLats, 0);
      glNormal3f(cosA, sinA, 0);
      glVertex3f(x1, y1, z1);

      if (image != 0)
         glTexCoord2f((i + 1)/numLats, 0);
      glNormal3f(cosB, sinB, 0);
      glVertex3f(x2, y2, z2);
      for (float j = 0; j < numLongs; ++j) {
         y1 += latSize;
         y2 += latSize;

         if (image != 0)
            glTexCoord2f(i/numLats, j/numLongs);
         glNormal3f(cosA, sinA, 0);
         glVertex3f(x1, y1, z1);

         if (image != 0)
            glTexCoord2f((i + 1)/numLats, j/numLongs);
         glNormal3f(cosB, sinB, 0);
         glVertex3f(x2, y2, z2);
      }
      glEnd();
   }

   glPopMatrix();
   glEnable(GL_CULL_FACE);
}
