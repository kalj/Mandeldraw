/*
 * @(#)mandeldraw.h
 * @author Karl Ljungkvist
 * Last changed: <2010-02-28 15:43:47 CET>
 *
 *   
 */

#ifndef _MANDELDRAW_H
#define _MANDELDRAW_H

#define INITIAL_WIN_WIDTH 300
#define INITIAL_WIN_HEIGHT 200
#define INITIAL_UPPER_LEFT_X -2
#define INITIAL_UPPER_LEFT_Y 1

// void timerFunc(int value);

void keyFunc(unsigned char key, int x, int y);

// void specKeyFunc(int key, int x, int y);

void mouseFunc(int button, int state, int x, int y);

void mouseMotionFunc(int x, int y);

void reshapeFunc(int w, int h);

void displayFunc();

void myInit();
// int getDelay();

void exitFunc();


#endif /* _MANDELDRAW_H */

