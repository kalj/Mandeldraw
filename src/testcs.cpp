/*
 * @(#)testcs.cpp
 * Last changed: <2010-03-05 16:14:47 CET>
 * @author Karl Ljungkvist
 *
 * 
 *
 */

#include <iostream>
#ifdef _WIN32
#include "mymath.h"
#else
#include <cmath>
#endif

using namespace std;

#include "colorspaces.h"


int main(int argc, char *argv[])
{

    rgbf c1 = {1,0,0};
    rgbf c2 = {0,1,0};
    rgbf c3 = {0,0,1};

    cout << "c1 before: " << c1.r << ", "<< c1.g << ", "<< c1.b << endl;
    cout << "c2 before: " << c2.r << ", "<< c2.g << ", "<< c2.b << endl;
    cout << "c3 before: " << c3.r << ", "<< c3.g << ", "<< c3.b << endl;

    hsvf h1;
    rgbf2hsvf(&h1,&c1);
    cout << "c1 in hsv: " << M_1_PI*h1.h << "pi, "<< h1.s << ", "<< h1.v << endl;
    hsvf2rgbf(&c1,&h1);
    rgbf2hsvf(&h1,&c2);
    cout << "c2 in hsv: " << M_1_PI*h1.h << "pi, "<< h1.s << ", "<< h1.v << endl;
    hsvf2rgbf(&c2,&h1);
    rgbf2hsvf(&h1,&c3);
    cout << "c3 in hsv: " << M_1_PI*h1.h << "pi, "<< h1.s << ", "<< h1.v << endl;
    hsvf2rgbf(&c3,&h1);

    cout << "c1 after: " << c1.r << ", "<< c1.g << ", "<< c1.b << endl;
    cout << "c2 after: " << c2.r << ", "<< c2.g << ", "<< c2.b << endl;
    cout << "c3 after: " << c3.r << ", "<< c3.g << ", "<< c3.b << endl;

    
    return 0;
}
