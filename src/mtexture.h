/*pp
 * @(#)mtexture.h
 * @author Karl Ljungkvist
 * Last changed: <2010-03-07 22:13:20 CET>
 *
 *   
 */

#ifndef _MTEXTURE_H
#define _MTEXTURE_H

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

#define INITIAL_DX 0.01

// #include "mousebox.h"
// #include <vector>
class Mousebox;


class Mtexture
{
public:
    Mtexture(double ulx, double uly, double dx, int width, int height, int maxIter);
    ~Mtexture(){delete[] pixels;}
    void zoomToBox(Mousebox &box);
    void resize(int w, int h);
    void outdate(){uptodate = false;}
    void compute();
    void bind();
    void draw();
    GLuint textureId;
private:
    void compute_pixel(int row, int col, double lly, int maxIter);
    bool uptodate;
    double ulx;
    double uly;
    double dx;
    int width;
    int height;
    int initialMaxIter;
    float *pixels;
    // vector pixels;
};



#endif /* _MTEXTURE_H */

