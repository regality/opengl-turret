#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Rocket.h"
#include "Cylinder.h"
#include "Pyramid.h"

Rocket::Rocket(float xa, float ya, float xp, float yp) {
   xAngle = xa;
   yAngle = ya;
   xPos = xp;
   yPos = yp;
   dist = 0;
   speed = 25;
}

void Rocket::draw() {
   Pyramid p;
   Cylinder c;
   dist += speed;
   speed += 0.1;

   glPushMatrix();
      glRotatef(yAngle, 0.0, 1.0, 0.0);
      glRotatef(xAngle, 1.0, 0.0, 0.0);
      glTranslatef(0,dist,0);
      glTranslatef(xPos,yPos,0);

      glPushMatrix();
         glScalef(0.6,1.3,0.6);
         glTranslatef(0,7,0);
         p.draw();
      glPopMatrix();

      glPushMatrix();
         glScalef(0.7,1.3,0.7);
         p.draw();
      glPopMatrix();

      glPushMatrix();
         glScalef(0.5, 7, 0.5);
         c.draw();
      glPopMatrix();
   glPopMatrix();
}

float Rocket::getDist() {
   return dist;
}

float Rocket::posX() {
   float cd = cos((xAngle-270)*3.141/180)*dist;
   return -1*sin((yAngle)*3.141/180)*cd;
}

float Rocket::posY() {
   return sin((xAngle-270)*3.141/180)*dist;
}

float Rocket::posZ() {
   float cd = cos((xAngle-270)*3.141/180)*dist;
   return -1*cos((yAngle)*3.141/180)*cd;
}
