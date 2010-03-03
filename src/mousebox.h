/*
 * @(#)mousebox.h
 * @author Karl Ljungkvist
 * Last changed: <2010-02-28 08:31:16 CET>
 *
 *   
 */

#ifndef _MOUSEBOX_H
#define _MOUSEBOX_H

#include "mandelbuffer.h"

class Mousebox
{
    friend void Mbuffer::zoomToBox(Mousebox &box);
public:
    Mousebox() :
	click_x(0),
	click_y(0),
	curr_x(0),
	curr_y(0),
	active(false),
	ratio(0) {};
    void click(int x,int y);
    void drag(int x, int y);
    void release();
    void draw();
    const bool is_active(){return active;}
    void setRatio(double r){ratio = r;}
private:
    int click_x, click_y;
    int curr_x, curr_y;
    bool active;
    double ratio;
}; 

#endif /* _MOUSEBOX_H */

