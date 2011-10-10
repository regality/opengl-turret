#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Pyramid.h"

void Pyramid::draw() {

   glPushMatrix();
   glDisable(GL_CULL_FACE);
   glShadeModel(GL_SMOOTH);
   glPolygonMode(GL_FRONT, GL_FILL);

   glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glVertex3f(-1.0,-1.0,-1.0);
      glVertex3f(-1.0,-1.0, 1.0);
      glVertex3f( 1.0,-1.0, 1.0);
      glVertex3f( 1.0,-1.0,-1.0);
   glEnd();

   glBegin(GL_POLYGON);
      glNormal3f(0,0,-1);
      glVertex3f(-1.0,-1.0,-1.0);
      glVertex3f(0.0, 1.0, 0.0);
      glVertex3f(-1.0,-1.0, 1.0);
   glEnd();

   glBegin(GL_POLYGON);
      glNormal3f(0,0,1);
      glVertex3f( 1.0,-1.0, 1.0);
      glVertex3f(0.0, 1.0, 0.0);
      glVertex3f( 1.0,-1.0,-1.0);
   glEnd();

   glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glVertex3f(-1.0,-1.0, 1.0);
      glVertex3f(0.0, 1.0, 0.0);
      glVertex3f( 1.0,-1.0, 1.0);
   glEnd();

   glBegin(GL_POLYGON);
      glNormal3f(1,0,0);
      glVertex3f(-1.0,-1.0,-1.0);
      glVertex3f(0.0, 1.0, 0.0);
      glVertex3f( 1.0,-1.0,-1.0);
   glEnd();

   glPopMatrix();
}

