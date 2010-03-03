/*
 * @(#)mandelwindow.cpp
 * Last changed: <2010-02-27 20:07:31 CET>
 * @author Karl Ljungkvist
 *
 * 
 *
 */

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>

using namespace std;

#include "mandelwindow.h"


bool Mwin::reshape(int w, int h){

    if(width != w || height != h)
    {
	width=w;
	height=h;
	return true;
    }
    else
	return false;
}

// --- set up matrix for drawing in window coordinates ----

void Mwin::beginWinCoord(){

    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glTranslatef(0,1.0,0);
    glScalef(1.0,-1.0, 0.0f);
    glScalef(1.0/float(width),1.0/float(height), 0.0f);

 }

// --- ...and reset it ----

void Mwin::endWinCoord(){

  glPopMatrix();

}


