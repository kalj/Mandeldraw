/*
 * @(#)mandelbuffer.h
 * @author Karl Ljungkvist
 * Last changed: <2010-03-03 22:02:41 CET>
 *
 *   
 */

#ifndef _MANDELBUFFER_H
#define _MANDELBUFFER_H

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

#define INITIAL_MAX_ITERATIONS 120
#define INITIAL_DX 3.0

// #include "mousebox.h"
// #include <vector>
class Mousebox;


class Mbuffer
{
public:
    Mbuffer(double ulx, double uly, double dx, int width, int height);
    ~Mbuffer(){delete[] pixels;}
    void zoomToBox(Mousebox &box);
    void resize(int w, int h);
    void outdate(){uptodate = false;}
    void compute();
    void bind();
    void draw();
    GLuint textureId;
private:
    const void colorize(float *dest, double param);
    void compute_pixel(int row, int col, double lly);
    bool uptodate;
    double ulx;
    double uly;
    double dx;
    int width;
    int height;
    int max_iterations;
    float *pixels;
    // vector pixels;
};



#endif /* _MANDELBUFFER_H */

