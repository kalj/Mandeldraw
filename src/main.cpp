
/*
 * @(#)main.cpp
 * Last changed: <2010-03-03 20:14:02 CET>
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
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
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

