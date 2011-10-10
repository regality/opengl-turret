#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Frog.h"

Frog::Frog() {
   animate = false;
   init();
   speed = 0.005;
   pos[0] = 0;
   pos[1] = 0;
   pos[2] = 0;
}

void Frog::jump() {
   if (!animate) {
      animate = true;
      frame = 0;
   }
}

float * Frog::getPos() {
   if (animateComplete) {
      init();
      pos[0] = 0;
      pos[1] = 0;
      pos[2] = getZ();
      return pos;
   } else {
      return NULL;
   }
}

void Frog::resetPos() {
   if (animateComplete) {
      animateComplete = false;
      init();
   }
}

void Frog::nextFrame() {
   if (frame < 100) {
      legs[0].ankle[1] += speed;

      legs[0].knee[2] -= speed;
      legs[0].knee[1] -= speed;
   
      legs[0].hip[2] += speed;
      legs[0].hip[1] += speed;

      if (frame < 50) {
         legs[2].ankle[1] += speed;

         legs[2].knee[2] -= speed;
         legs[2].knee[1] -= speed;

         legs[2].hip[2] += speed;
         legs[2].hip[1] += speed;
      } else {
         legs[2].toe[1] += speed;
      }
   } else if (frame < 250) {
      legs[0].hip[1] += speed/2;
      legs[0].hip[2] += speed;

      legs[2].toe[1] += speed/2;
      legs[2].toe[2] += speed;
   } else if (frame < 500) {
      legs[0].toe[1] += speed;
      legs[0].toe[2] += speed;
      legs[2].toe[1] += speed;
      legs[2].toe[2] += speed;
   } else if (frame < 600) {

      legs[0].ankle[1] -= speed;

      legs[0].knee[2] += speed;
      legs[0].knee[1] += speed;
   
      legs[0].hip[2] -= speed;
      legs[0].hip[1] -= speed;

      if (frame < 550) {
         legs[2].ankle[1] -= speed;

         legs[2].knee[2] += speed;
         legs[2].knee[1] += speed;

         legs[2].hip[2] -= speed;
         legs[2].hip[1] -= speed;
      } else {
         legs[2].toe[1] -= speed;
      }

      legs[0].toe[1] -= speed;
      legs[0].toe[2] += speed;
      legs[2].toe[1] -= speed;
      legs[2].toe[2] += speed;
      
   } else if (frame < 820) {
      legs[0].toe[1] -= speed;
      legs[0].toe[2] += speed;
      legs[2].toe[1] -= speed;
      legs[2].toe[2] += speed;
      if (frame < 680) {
         legs[0].toe[2] += speed;
         legs[0].toe[1] += speed;

         legs[0].hip[2] -= speed;
         legs[0].hip[1] -= speed;
      }
   } else {
      animate = false;
      animateComplete = true;
      frame = 0;
   }
   ++frame;
   copyLegs();
}

void Frog::drawLimb(float * begin, float * length) {
   Sphere joint;
   Cylinder limb;

   float end[3] = {begin[0] + length[0], begin[1] + length[1], begin[2] + length[2]};
   float mag = sqrt(length[0]*length[0] + length[1]*length[1] + length[2]*length[2]);
   float norm[3] = {length[0]/mag, length[1]/mag, length[2]/mag};
   float cross[3] = {norm[2], 0, -1*norm[0]};
   float angle = acos(norm[1]) * 180 / 3.14159f;

   glColor3f(color[0], color[1], color[2]);
   glPushMatrix();
   glTranslatef(begin[0], begin[1], begin[2]);
   glRotatef(angle, cross[0], cross[1], cross[2]);
   glScalef(.1, mag, .1);
   limb.draw();
   glPopMatrix();

   glColor3f(color[0], color[1], color[2]);
   glPushMatrix();
   glTranslatef(begin[0], begin[1], begin[2]);
   glScalef(.1, .1, .1);
   joint.draw();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(end[0], end[1], end[2]);
   glScalef(.1, .1, .1);
   joint.draw();
   glPopMatrix();
}

void Frog::draw () {
   if (animate)
      for (int i = 0; i < 10; ++i)
         nextFrame();

   glPushMatrix();

   glTranslatef(0, 0, pos[2]);

   float specReflection[] = { 0.5f, 0.9f, 0.5f, 1.0f };
   glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
   glMateriali(GL_FRONT, GL_SHININESS, 84);

   float joint[3];

   for (int i = 0; i < 4; ++i) {
      joint[0] = 0;
      joint[1] = 0;
      joint[2] = 0;

      joint[0] += legs[i].toe[0];
      joint[1] += legs[i].toe[1];
      joint[2] += legs[i].toe[2];
      drawLimb(joint, legs[i].ankle);

      joint[0] += legs[i].ankle[0];
      joint[1] += legs[i].ankle[1];
      joint[2] += legs[i].ankle[2];
      drawLimb(joint, legs[i].knee);

      joint[0] += legs[i].knee[0];
      joint[1] += legs[i].knee[1];
      joint[2] += legs[i].knee[2];
      drawLimb(joint, legs[i].hip);
   }

   joint[0] += legs[3].hip[0];
   joint[1] += legs[3].hip[1];
   joint[2] += legs[3].hip[2];

   glPopMatrix();

   //specReflection = { 0.3f, 0.3f, 0.3f, 1f };
   specReflection[0] = 0.1f;
   specReflection[1] = 0.8f;
   specReflection[2] = 0.1f;
   glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, specReflection);
   glMateriali(GL_FRONT, GL_SHININESS, 126);

   Sphere body;

   glPushMatrix();
   glTranslatef(0, joint[1], joint[2] - .7);
   glTranslatef(0, 0, pos[2]);
   glRotatef(-20, 1, 0, 0);
   glScalef(.8, .6, 1.2);
   body.draw();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0, .75 + joint[1], .5 + joint[2]);
   glTranslatef(0, 0, pos[2]);
   glScalef(.7, .7, .7);
   body.draw();
   glPopMatrix();
}

void Frog::init() {
   backLeft   = &legs[0];
   backRight  = &legs[1];
   frontLeft  = &legs[2];
   frontRight = &legs[3];

   backLeft->toe[0] = -.2;
   backLeft->toe[1] =  0;
   backLeft->toe[2] =  -.2;

   backLeft->ankle[0] = 0;
   backLeft->ankle[1] = 0;
   backLeft->ankle[2] = -.3;

   backLeft->knee[0] = -.8;
   backLeft->knee[1] = 1;
   backLeft->knee[2] = 1.3;

   backLeft->hip[0] = .6;
   backLeft->hip[1] = .0;
   backLeft->hip[2] = -1.4;

   frontLeft->toe[0] = -.2;
   frontLeft->toe[1] = 0;
   frontLeft->toe[2] =  .5;

   frontLeft->ankle[0] = 0;
   frontLeft->ankle[1] = 0;
   frontLeft->ankle[2] = -.2;

   frontLeft->knee[0] = 0;
   frontLeft->knee[1] = .5;
   frontLeft->knee[2] = .2;

   frontLeft->hip[0] = -.1;
   frontLeft->hip[1] = .8;
   frontLeft->hip[2] = .5;
   frontLeft->hip[2] = .5;

   copyLegs();
}

void Frog::copyLegs() {
   *backRight = *backLeft;
   backRight->toe[0] *= -1;
   backRight->ankle[0] *= -1;
   backRight->knee[0] *= -1;
   backRight->hip[0] *= -1;


   *frontRight = *frontLeft;
   frontRight->toe[0] *= -1;
   frontRight->ankle[0] *= -1;
   frontRight->knee[0] *= -1;
   frontRight->hip[0] *= -1;
}
