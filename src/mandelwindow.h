/*
 * @(#)mandelwindow.h
 * @author Karl Ljungkvist
 * Last changed: <2010-02-27 20:07:40 CET>
 *
 *   
 */

#ifndef _MANDELWINDOW_H
#define _MANDELWINDOW_H

class Mwin
{
public:
    bool reshape(int w, int h);
    void beginWinCoord();
    void endWinCoord();
    const double getAspectRatio(){ return ((double)height)/width; }
private:
    int width;
    int height;
};

#endif /* _MANDELWINDOW_H */

