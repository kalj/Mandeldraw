/*
 * @(#)testbmpio.cpp
 * Last changed: <2010-03-13 09:25:21 CET>
 * @author Karl Ljungkvist
 *
 * 
 *
 */

#include "bmpio.h"


int main(int argc, char *argv[])
{

    float pixels[40*40*3];

    for (int i = 0; i < 40; ++i)
    {
	for (int j = 0; j < 40; ++j)
	{
	    pixels[3*(i + j*40) + 0] = 1.0f;
	    pixels[3*(i + j*40) + 1] = 0.0f;
	    pixels[3*(i + j*40) + 2] = 0.0f;
	}
    }

    write_to_BMP("test.bmp",pixels,40,40);
    
    return 0;
}
