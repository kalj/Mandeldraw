
/*
 * @(#)main.cpp
 * Last changed: <2010-03-09 10:24:41 CET>
 * @author Karl Ljungkvist
 *
 * 
 *
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

#include "mandeldraw.h"

void usage();

int main(int argc, char **argv)
{

    const char flags[] = "a:i:h";
    int opt;

    int aaLvl = 0;
    int initialMaxIterations = 120;
    
    while( (opt = getopt(argc, argv, flags)) != -1)
    {
	switch(opt)
	{
	case 'h':
	    usage();
	    exit(0);
	    break;
	case 'a':
	    aaLvl = atoi(optarg);
	    break;
	case 'i':
	    initialMaxIterations = atoi(optarg);
	    break;
	case '?':
	    usage();
	    exit(1);
	    break;
	}
    }

    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(INITIAL_WIN_WIDTH, INITIAL_WIN_HEIGHT);

    glutCreateWindow("Mandeldraw 2.0");
    myInit(initialMaxIterations, aaLvl);

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


void usage()
{
    cerr << "Usage: mandeldraw [-a <level> ] [-i <iterations>]" << endl
	 << endl
	 << "       -a : Specifies the level of supersampling (0, 1, 2, 3)." << endl
	 << "            Note: This is the square root of the 2-logarithm of" << endl
	 << "		 the number of points per pixel, i.e. l where (2^l)*(2^l)" << endl
	 << " 		 is the number of samples per pixel." << endl
	 << "       -i : Specifies the initial number of iterations used." << endl
	 << "       -h : Print this help." << endl;
}
