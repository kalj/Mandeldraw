
/*
 * @(#)main.cpp
 * Last changed: <2010-02-27 21:49:46 CET>
 * @author Karl Ljungkvist
 *
 * 
 *
 */

#include <cstdio>
#include <iostream>

using namespace std;

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

#include "mandeldraw.h"

int main(int argc, char **argv)
{
    int n,m;

    if(argc != 3)
    {
	cerr << "Wrong number of input arguments." << endl;
	cerr << "Usage: ./mandeldraw <xres> <yres>" << endl;
	exit(1);
    }
    
    sscanf(argv[1], "%d",&n);
    sscanf(argv[2], "%d",&m);

    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(INITIAL_WIN_WIDTH, INITIAL_WIN_HEIGHT);

    glutCreateWindow("Mandeldraw 1.0");
    myInit();

    glutDisplayFunc(displayFunc);
    glutKeyboardFunc(keyFunc);
    // glutSpecialFunc(specKeyFunc);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(mouseMotionFunc);
    glutPassiveMotionFunc(mouseMotionFunc);
    glutReshapeFunc(reshapeFunc);
    /* glutIdleFunc(displayFunc); */
    /* glutTimerFunc(getDelay(), timerFunc, 0); */

    glutMainLoop();

    return 0;
}

