/*
 * @(#)mousebox.cpp
 * Last changed: <2010-02-28 09:15:59 CET>
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

#include "mousebox.h"

void Mousebox::click(int x,int y){
    // cout << "clicked mouse at " << x << ", " << y << endl;
    active = true;
    click_x = x;
    click_y = y;
    curr_x = x;
    curr_y = y;
}

void Mousebox::drag(int x, int y){
    // cout << "draged mouse at " << x << ", " << y << endl;
    curr_x = x;
    curr_y = y;
}

void Mousebox::release()
{

    active = false;
}

void Mousebox::draw()
{
    int fake_y = click_y + (int)((curr_x - click_x)*ratio);
    glColor3f(0.0f,1.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(click_x,click_y);
    glVertex2f(curr_x,click_y);
    glVertex2f(curr_x,fake_y);
    glVertex2f(click_x,fake_y);
    glEnd();
}
