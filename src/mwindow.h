/*
 * @(#)mwindow.h
 * @author Karl Ljungkvist
 * Last changed: <2010-03-07 20:49:46 CET>
 *
 *   
 */

#ifndef _MWINDOW_H
#define _MWINDOW_H

class Mwin
{
public:
    bool reshape(int w, int h);
    void beginWinCoord();
    void endWinCoord();
    const int getWidth() {return width;}
    const int getHeight() {return height;}
    const float getAspectRatio(){ return float(height)/width; }
private:
    int width;
    int height;
};

#endif /* _MWINDOW_H */

