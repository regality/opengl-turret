#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Rocket.h"
#include "Cylinder.h"
#include "Pyramid.h"

Rocket::Rocket(float xa, float ya, float xp, float yp, bool b) {
   xAngle = xa;
   yAngle = ya;
   xPos = xp;
   yPos = yp;
   bullet = b;
   if (bullet) {
      dist = 0;
      speed = 33;
   } else {
      dist = 15;
      speed = 1;
   }
}

void Rocket::draw() {
   Pyramid p;
   Cylinder c;
   dist += speed;
   if (speed < 25) {
      speed *= 2.0;
   } else {
      speed += 0.3;
   }

   glPushMatrix();
      glRotatef(yAngle, 0.0, 1.0, 0.0);
      glRotatef(xAngle, 1.0, 0.0, 0.0);
      glTranslatef(0,dist,0);
      glTranslatef(xPos,yPos,0);

      if (!bullet) {
         glPushMatrix();
            glScalef(0.6,1.3,0.6);
            glTranslatef(0,7,0);
            p.draw();
         glPopMatrix();
      }

      glPushMatrix();
         if (bullet) {
            glScalef(0.1, 3, 0.1);
         } else {
            glScalef(0.49, 7, 0.49);
         }
         c.draw();
      glPopMatrix();
   glPopMatrix();
}

float Rocket::getSpeed() {
   return speed;
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
