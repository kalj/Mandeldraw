/*
 * @(#)mandeldraw.cpp
 * Last changed: <2010-03-14 18:37:03 CET>
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

// int antialiasingLvl;

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
	
	printf("Set level of supersampling (give l where 2^l * 2^l is the number of points per ");
	printf("pixel). Please give something reasonable (i.e. 0-3): ");
	
	
	if(scanf("%d",&lvl) == EOF)
	{
	    fprintf(stderr, "Bogus input.\n");
	}
	else if(lvl > 3 || lvl < 0)
	{
	    fprintf(stderr,"Number out of range\n");
	}
	else
	{
	    tex->setAALvl(lvl);
	    glutPostRedisplay();
	}
    }
    else if(key == 'w')
    {
	const char *filename = "mandelbrot.bmp";
	printf("writing current image to file '%s'\n", filename);

	tex->writeToBMP(filename);

    }
    else if(key == 'b')
    {
	printf("Benchmarking...\n");
	double ulx = -1.003817;
	double uly = 0.282004;
	double dx = 0.000003;
	unsigned int height = 600;
	unsigned int width = 1000;
	unsigned int maxIter = 120;
	int aaLvl = 2;
    

	glutPositionWindow(20,20);
	glutReshapeWindow(width,height);
	tex->reset(ulx, uly, dx, width, height, maxIter, aaLvl);
	glutPostRedisplay();
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

void myInit(int initialMaxIterations, int aaLvl)
{
    win.reshape(INITIAL_WIN_WIDTH, INITIAL_WIN_HEIGHT);
    
    tex = new Mtexture(INITIAL_UPPER_LEFT_X,
		       INITIAL_UPPER_LEFT_Y,
		       INITIAL_DX,
		       INITIAL_WIN_WIDTH,
		       INITIAL_WIN_HEIGHT,
		       initialMaxIterations,
		       aaLvl);

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
	tex->resize(w,h);
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
