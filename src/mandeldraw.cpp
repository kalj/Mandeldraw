/*
 * @(#)mandeldraw.cpp
 * Last changed: <2010-02-28 08:21:03 CET>
 * @author Karl Ljungkvist
 *
 * 
 *
 */

#include <iostream>
#include <cmath>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

#include "mandeldraw.h"
#include "mandelbuffer.h"
#include "mousebox.h"
#include "mandelwindow.h"

using namespace std;

#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4
#define ESCAPE 27
#define ENTER 13
#define BACKSPACE 8

Mbuffer *buf;

Mousebox box;

Mwin win;

// void timerFunc(int value)
// {

// }

void keyFunc(unsigned char key, int x, int y)
{
    if(key == ESCAPE || key == 'q')
	exitFunc();
    // else if( key == 'u')
    // {
    // 	glutPostRedisplay();
    // }
}


// void specKeyFunc(int key, int x, int y)
// {
    
// }

void mouseFunc(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
	if(!box.is_active())
	{
	    box.click(x,y);
	}
	else
	{
	    box.release();
	    buf->zoomToBox(box);
	}
    }
    
    glutPostRedisplay();
}


void mouseMotionFunc(int x, int y)
{
    if(box.is_active())
    {
	box.drag(x,y);
    }
    
    glutPostRedisplay();
    
}

void myInit()
{
    win.reshape(INITIAL_WIN_WIDTH, INITIAL_WIN_HEIGHT);
    
    buf = new Mbuffer(INITIAL_UPPER_LEFT_X, INITIAL_UPPER_LEFT_Y,
		      INITIAL_DX/(INITIAL_WIN_WIDTH),
		      INITIAL_WIN_WIDTH, INITIAL_WIN_HEIGHT);

    box.setRatio(((double) INITIAL_WIN_HEIGHT) / (INITIAL_WIN_WIDTH));
    
    // buf->compute();

    glViewport(0, 0, INITIAL_WIN_WIDTH, INITIAL_WIN_HEIGHT);

}


void reshapeFunc(int w, int h)
{
    glViewport(0, 0, w, h);
    box.setRatio(((double) h) / w);

    // returnes true if changed
    if(win.reshape(w,h))
    {
	buf->resize(w,h);
    }

    glutPostRedisplay();
	
}



void displayFunc()
{
    glClear(GL_COLOR_BUFFER_BIT );

    buf->draw();

    if(box.is_active())
    {
    	glColor3f(0.5,0,0.5);
    	win.beginWinCoord();
    	box.draw();
    	win.endWinCoord();
    }


    glFlush();
}




// int getDelay()
// {
//     return 1;
// }

void exitFunc()
{
    delete buf;
    glutLeaveMainLoop();
}
