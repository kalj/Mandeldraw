/*
 * @(#)colorspaces.cpp
 * Last changed: <2010-03-10 07:20:55 WEST>
 * @author Karl Ljungkvist
 *
 * 
 *
 */

#ifdef _WIN32
#include "winmath.h"
#else
#include <cmath>
#endif

#include "colorspaces.h"

static float min(float a, float b)
{
    return a < b ? a : b;
}

static float max(float a, float b)
{
    return a > b ? a : b;
}


void hsvf2rgbf(rgbf *dest, const hsvf *src)
{
    if(src->h < 2*M_PI/3)
    {
	dest->b = src->v * (1 - src->s);
	dest->r = src->v * (1 + src->s * cos(src->h)/cos(M_PI/3 - src->h));
	dest->g = 3*src->v - (dest->r + dest->b);
			    
    }
    else if(src->h < 4*M_PI/3)
    {
	dest->r = src->v * (1 - src->s);
	dest->g = src->v * (1 + src->s * cos(src->h - 2*M_PI/3)/cos(M_PI - src->h));
	dest->b = 3*src->v - (dest->r + dest->g);
    }
    else // src < 2*M_PI
    {
	dest->g = src->v * (1 - src->s);
	dest->b = src->v * (1 + src->s * cos(src->h - 4*M_PI/3)/cos(5*M_PI/3 - src->h));
	dest->r = 3*src->v - (dest->g + dest->b);
	
    }
}



    
void rgbf2hsvf(hsvf *dest, const rgbf *src)
{
    float theta;

    theta = acos(0.5*(2*src->r - src->g - src->b)/sqrt(pow(src->r - src->g,2)
							  + (src->r - src->b)*
							  (src->g - src->b)));
    
    dest->h = src->g < src->b ? 2*M_PI - theta : theta;

    
    dest->s = 1 - 3/(src->r + src->g + src->b)*min(src->r,
						   min(src->g,src->b));
    
    dest->v = (src->r + src->g + src->b)/3;

}



void hslf2rgbf(rgbf *dest, const hslf *src)
{
    float C;
    if(src->l > 0.5)
	C = (2 - 2*src->l)*src->s;
    else
	C = 2*src->l*src->s;

    float Hp = src->h * 3 / M_PI;
    
    float help = (Hp / 2);
    float X = C *(1 -  fabs(2*(help - floorf(help)) - 1));

    if(C == 0)
    {
	dest->r = 0;
	dest->g = 0;
	dest->b = 0;
    }
    else if( Hp < 1)
    {
	dest->r = C;
	dest->g = X;
	dest->b = 0;
    }
    else if(Hp < 2)
    {
	dest->r = X;
	dest->g = C;
	dest->b = 0;
    }
    else if(Hp < 3)
    {
	dest->r = 0;
	dest->g = C;
	dest->b = X;
    }
    else if(Hp < 4)
    {
	dest->r = 0;
	dest->g = X;
	dest->b = C;
    }
    else if(Hp < 5)
    {
	dest->r = X;
	dest->g = 0;
	dest->b = C;
    }
    else
    {
	dest->r = C;
	dest->g = 0;
	dest->b = X;
    }

    float m = src->l - 0.5*C;

    dest->r += m;
    dest->g += m;
    dest->b += m;
}



    
void rgbf2hslf(hslf *dest, const rgbf *src)
{
    float theta;


    theta = acos(0.5*(2*src->r - src->g - src->b)/sqrt(pow(src->r - src->g,2)
							  + (src->r - src->b)*
							  (src->g - src->b)));
    
    dest->h = src->g < src->b ? 2*M_PI - theta : theta;


    float m = min(src->r,min(src->g,src->b));
    float M = max(src->r,max(src->g,src->b));

    dest->l = 0.5*(m + M);

    float C = M-m;

    if(C == 0)
	dest->s = 0;
    else if( dest->l > 0.5)
	dest->s = C/(2-2*dest->l);
    else
	dest->s = C/(2*dest->l);
	    

}
