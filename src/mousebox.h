/*
 * @(#)mousebox.h
 * @author Karl Ljungkvist
 * Last changed: <2010-03-07 21:44:37 CET>
 *
 *   
 */

#ifndef _MOUSEBOX_H
#define _MOUSEBOX_H

#include "mtexture.h"

class Mousebox
{
    friend void Mtexture::zoomToBox(Mousebox &box);
public:
    Mousebox() :
	click_x(0),
	click_y(0),
	curr_x(0),
	curr_y(0),
	active(false),
	ratio(0) {};
    void click(float x,float y);
    void drag(float x, float y);
    void release();
    void draw();
    const bool is_active(){return active;}
    void setRatio(double r){ratio = r;}
private:
    float click_x, click_y;
    float curr_x, curr_y;
    bool active;
    double ratio;
}; 

#endif /* _MOUSEBOX_H */

