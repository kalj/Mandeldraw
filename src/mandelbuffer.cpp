/*
 * @(#)mandelbuffer.cpp
 * Last changed: <2010-03-03 22:04:21 CET>
 * @author Karl Ljungkvist
 *
 * 
 *
 */

#include <iostream>
#include <cmath>

using namespace std;

#include "omp.h"
#include "mandelbuffer.h"
#include "colorspaces.h"
#include "mousebox.h"

const rgbf tint1 = {0,
		    0,
		    1};
const rgbf tint2 = {252.0/255,
		   177.0/255,
		   3.0/255};

hslf tint1_hsl;
hslf tint2_hsl;

Mbuffer::Mbuffer(double ulx, double uly, double dx, int width, int height)
{

    this->ulx = ulx;
    this->uly = uly;
    this->dx = dx;
    this->width = width;
    this->height = height;
    this->max_iterations = INITIAL_MAX_ITERATIONS;
    
    this->pixels = new float[3*width*height];
    // this->pixels.reserve(3*width*height);
    rgbf2hslf(&tint1_hsl,&tint1);
    rgbf2hslf(&tint2_hsl,&tint2);

    glGenTextures(1, &(this->textureId)); //Make room for our texture

    this->outdate();
}

void Mbuffer::zoomToBox(Mousebox &box)
{
    this-> ulx = this->ulx + this->dx*box.click_x;
    this-> uly =  this->uly - this->dx*box.click_y;

    this->dx = this->dx * double(box.curr_x - box.click_x) / double(this->width);
    this->max_iterations = (INITIAL_MAX_ITERATIONS) *
	(1 - log2(double(this->dx)/INITIAL_DX));

    this->outdate();
}

void Mbuffer::resize(int w, int h)
{
    this->dx *= double(this->height) / double(h);
    this->width = w;
    this->height = h;

    delete[] this->pixels;
    this->pixels = new float[3*w*h];
    this->max_iterations = (INITIAL_MAX_ITERATIONS) *
	(1 - log2(double(this->dx)/INITIAL_DX));

    this->outdate();
    
}
void Mbuffer::compute()
{
    clock_t t1 = clock();
    
    double lly = this->uly - (this->height-1)*this->dx;
    int row, col;

#pragma omp parallel for private(col,row)
    for(row=0; row < this->height; row++)
    {
	for(col=0; col < this->width; col++)
	{
	    compute_pixel(row,col,lly);

	}
    }

    uptodate = true;

    
    clock_t t2 = clock();
    cout << "Time in compute: "<< ((double)(t2-t1))/CLOCKS_PER_SEC << " s" << endl;
}


void Mbuffer::compute_pixel(int row, int col, double lly)
{
    double x = this->ulx + col*this->dx;
    double y = lly + row*this->dx;
    
    double p = sqrt((x - 0.25)*(x - 0.25) + y*y);
    
    double res;

    if( x < p- 2*p*p + 0.25 || (x + 1)*(x + 1) + y*y < 0.0625)
    {
	res = 0;
	
    }
    else
    {
	int k;
	double zx = 0;
	double zy = 0;
	double temp;
	for (k=1; zx*zx + zy*zy <4 && k<max_iterations ; k++)
	{
	    temp = zx;
	    zx = zx*zx - zy*zy + x;
	    zy = 2*temp*zy + y;
	}

	// if we escaped, perform two additional rounds
	if(k < max_iterations)
	{

	    temp = zx;
	    zx = zx*zx - zy*zy + x;
	    zy = 2*temp*zy + y;

	    temp = zx;
	    zx = zx*zx - zy*zy + x;
	    zy = 2*temp*zy + y;
		    
	    res = k+ 2 + 1 - log2(.5*log2(zx*zx + zy*zy));
	}
	else
	{
	    res = 0;
	}

    }
	    
    if (res == 0)
    {
	this->pixels[(row*this->width + col)*3] = 0;
	this->pixels[(row*this->width + col)*3 +1] = 0;
	this->pixels[(row*this->width + col)*3 +2] = 0;
    }
    else
    {
	colorize(pixels + (row*width + col)*3, res);
    }

}

const void Mbuffer::colorize(float *dest, double param)
{
    if( int(10*(param)/max_iterations) % 2 == 0)
    {
	tint1_hsl.l = 0.5 + 0.5*sin(5*M_PI*(2*param/max_iterations - 0.5));
	tint2_hsl.l = 0;
    }
    else
    {
	tint1_hsl.l = 0;
	tint2_hsl.l = 0.5 + 0.5*sin(5*M_PI*(2*param/max_iterations - 0.5));
    }
    
    rgbf col1, col2;
    
    hslf2rgbf(&col1,&tint1_hsl);
    hslf2rgbf(&col2,&tint2_hsl);
    
    dest[0] = col1.r + col2.r;
    dest[1] = col1.g + col2.g;
    dest[2] = col1.b + col2.b;
}


void Mbuffer::bind()
{
    glBindTexture(GL_TEXTURE_2D, this->textureId); //Tell OpenGL which texture to edit

    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		 0,                            //0 for now
		 GL_RGB,                       //Format OpenGL uses for image
		 this->width, this->height,  	       //Width and height
		 0,                            //The border of the image
		 GL_RGB, //GL_RGB, because pixels are stored in RGB format
		 GL_FLOAT, //GL_UNSIGNED_BYTE, because pixels are stored
		 		   //as unsigned numbers
		 this->pixels);               //The actual pixel data

}


void Mbuffer::draw()
{
    if(!this->uptodate)
    {
	this->compute();
	this->bind();
    }
    

    // glDisable(GL_CULL_FACE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
    
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1,0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.f,1.f,1.f);

    glBegin(GL_QUADS);
    glTexCoord2f(0.f, 0.f);
    glVertex2f(0.0f, 0.f);
    glTexCoord2f(0.f, 1.f);
    glVertex2f(0.0f, 1.f);
    glTexCoord2f(1.f, 1.f);
    glVertex2f(1.0f, 1.0f);
    glTexCoord2f(1.f, 0.f);
    glVertex2f(1.0f, 0.f);
    glEnd();
    
}
