/*
 * @(#)mandeldraw.cpp
 * Last changed: <2010-03-07 23:13:46 CET>
 * @author Karl Ljungkvist
 *
 * 
 *
 */

#include <cmath>
#include <cstdio>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

#include "mandeldraw.h"
#include "mtexture.h"
#include "mousebox.h"
#include "mwindow.h"

using namespace std;

#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4
#define ESCAPE 27
#define ENTER 13
#define BACKSPACE 8

Mtexture *tex;

Mousebox box;

Mwin win;

int antialiasingLvl;

void keyFunc(unsigned char key, int x, int y)
{
    if(key == ESCAPE || key == 'q')
	exitFunc();
    else if(key == 'i')
    {
	tex->incrementInitialMaxIter();
	glutPostRedisplay();
    }
    else if(key == 'I')
    {
	tex->decrementInitialMaxIter();
	glutPostRedisplay();
    }
    else if(key == 'a' || key == 'A')
    {
	int lvl;
	
	printf("Set level of supersampling (give square root of number of points per ");
	printf("pixel). Please give something reasonable (i.e. 1-5): ");
	
	
	if(scanf("%d",&lvl) == EOF)
	{
	    fprintf(stderr, "Bogus input.\n");
	}
	else if(lvl > 5 || lvl < 1)
	{
	    fprintf(stderr,"Number out of range\n");
	}
	else
	{
	    antialiasingLvl = lvl;

	    tex->resize(lvl*win.getWidth(), lvl*win.getHeight());
	    glutPostRedisplay();
	}
    }

}


void mouseFunc(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
	if(!box.is_active())
	{
	    box.click(float(x)/win.getWidth(),float(y)/win.getHeight());
	}
	else
	{
	    box.release();
	    tex->zoomToBox(box);
	}
    }
    
    glutPostRedisplay();
}


void mouseMotionFunc(int x, int y)
{
    if(box.is_active())
    {
	box.drag(float(x)/win.getWidth(),float(y)/win.getHeight());
    }
    
    glutPostRedisplay();
    
}

void myInit(int initialMaxIterations)
{
    win.reshape(INITIAL_WIN_WIDTH, INITIAL_WIN_HEIGHT);
    
    tex = new Mtexture(INITIAL_UPPER_LEFT_X,
		      INITIAL_UPPER_LEFT_Y,
		      INITIAL_DX / antialiasingLvl,
		      antialiasingLvl * INITIAL_WIN_WIDTH,
		      antialiasingLvl * INITIAL_WIN_HEIGHT,
		      initialMaxIterations);

    box.setRatio( double(INITIAL_WIN_HEIGHT) / (INITIAL_WIN_WIDTH));
    
    glViewport(0, 0, INITIAL_WIN_WIDTH, INITIAL_WIN_HEIGHT);

}


void reshapeFunc(int w, int h)
{
    glViewport(0, 0, w, h);
    box.setRatio( float(h) / w);

    // returnes true if changed
    if(win.reshape(w,h))
    {
	tex->resize(antialiasingLvl*w,
		    antialiasingLvl*h);
    }

    glutPostRedisplay();
	
}



void displayFunc()
{
    glClear(GL_COLOR_BUFFER_BIT );

    tex->draw();

    if(box.is_active())
    {
    	win.beginWinCoord();
    	box.draw();
    	win.endWinCoord();
    }


    glutSwapBuffers();
}

void exitFunc()
{
    delete tex;
    glutLeaveMainLoop();
}
