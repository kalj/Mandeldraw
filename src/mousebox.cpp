/*
 * @(#)mousebox.cpp
 * Last changed: <2010-03-07 14:12:48 CET>
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
#include "log.h"

void Mousebox::click(float x,float y){
    LOG("Mousebox::click(%f, %f)\n",x,y);
    active = true;
    click_x = x;
    click_y = y;
    curr_x = x;
    curr_y = y;
}

void Mousebox::drag(float x, float y){
    // LOG("Mousebox::drag(%f, %f)\n",x,y);
    curr_x = x;
    curr_y = y;
}

void Mousebox::release()
{
    LOG("Mousebox::release()%c",'\n');
    LOG("   click_x: %f, click_y: %f, curr_x: %f, curr_y: %f\n",click_x, click_y,curr_x,curr_y);
    active = false;
}

void Mousebox::draw()
{
    float fake_y = click_y + (curr_x - click_x);

    // LOG("Mousebox::draw()%c",'\n');

    // LOG("  curr_x=%f, curr_y=%f, click_x=%f, fake_y=%f\n",curr_x,curr_y,click_x,fake_y);
    // glColor3f(0.5,0,0.5);
    glColor3f(0.0f,1.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(click_x,click_y);
    glVertex2f(curr_x,click_y);
    glVertex2f(curr_x,fake_y);
    glVertex2f(click_x,fake_y);
    glEnd();
}
