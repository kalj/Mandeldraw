/*
 * @(#)mtexture.cpp
 * Last changed: <2010-03-13 08:30:10 CET>
 * @author Karl Ljungkvist
 *
 * 
 *
 */

#include <iostream>
#include <ctime>
#include <cstdlib>

#ifdef _WIN32
#include "winmath.h"
#else
#include <cmath>
#endif

using namespace std;

#include "omp.h"
#include "mtexture.h"
#include "colorspaces.h"
#include "mousebox.h"
#include "log.h"
#include "bmpio.h"

#ifdef _WIN32 
#define GL_CLAMP_TO_EDGE 0x812F
#endif

const rgbf tint1 = {0,
		    0,
		    1};
const rgbf tint2 = {252.0/255,
		   177.0/255,
		   3.0/255};

hslf tint1_hsl;
hslf tint2_hsl;


void colorize(float *dest, double param, int maxIter);
void compute_pixel(float *dest, double x, double y, int maxIter);

Mtexture::Mtexture(double ulx, double uly, double dx, int width, int height, int maxIter, int aaLvl)
{

    LOG("Mtexture::Mtexture(%f, %f, %f, %d, %d, %d, %d)\n",ulx,uly,dx,width,height, maxIter, aaLvl);
    
    this->ulx = ulx;
    this->uly = uly;
    this->dx = dx;
    this->width = width;
    this->height = height;
    this->initialMaxIter = maxIter;
    this->aaLvl = aaLvl;
    
    this->pixels = new float[3*this->width*this->height];
    
    rgbf2hslf(&tint1_hsl,&tint1);
    rgbf2hslf(&tint2_hsl,&tint2);

    glGenTextures(1, &(this->textureId)); //Make room for our texture

    this->outdate();
}


Mtexture::~Mtexture()
{
    glDeleteTextures(1, &(this->textureId));
    delete[] pixels;
}

void Mtexture::zoomToBox(Mousebox &box)
{
    LOG("Mtexture::zoomToBox(box)%c",'\n');
    
    this-> ulx += this->width*this->dx*box.click_x;
    this-> uly -= this->height*this->dx*box.click_y;

    this->dx = this->dx * (box.curr_x - box.click_x);

    LOG("   ulx: %f, uly: %f, dx: %f\n", this->ulx, this->uly, this->dx);

    this->outdate();
}

void Mtexture::resize(int w, int h)
{
    LOG("Mtexture::resize(%d, %d)\n",w,h);
    
    this->dx = this->dx * double(this->height) / double(h);
    LOG("   this->dx: %f\n",this->dx);
    
    this->width = w;
    this->height = h;

    LOG("    new size of array: %d\n",3*this->width*this->height);
    delete[] this->pixels;
    this->pixels = new float[3*this->width*this->height];

    this->outdate();
}


void Mtexture::setAALvl(int lvl)
{

    if(lvl != this->aaLvl)
    {
	this->aaLvl = lvl;
	
	this->outdate();
	
    }
}

/**
 * Loops through all the texels
 *
 * 
 */


void Mtexture::compute()
{

    LOG("Mtexture::compute()%c",'\n');
    clock_t t1 = clock();
    
    double lly = this->uly - (this->height-1)*this->dx;
    LOG("   uly: %f, lly: %f, height: %d, dx: %f\n", this->uly, lly, this->height, this->dx);
    int row, col;

    const int n_side = 1 << this->aaLvl;
    const int n_samples = n_side*n_side;

    int maxIter = this->initialMaxIter * (1 - log2( (this->dx/ n_side) / INITIAL_DX));

    LOG("   n_side: %d, maxIter: %d\n", n_side, maxIter);
    
    const int nrows = this->height;
    const int ncols = this->width;

    double x;
    double y;
    switch(this->aaLvl)
    {
    case 0:
#pragma omp parallel for private(col,row,x,y) schedule(dynamic)
	for(row=0; row < nrows; row++)
	{
	    for(col=0; col < ncols; col++)
	    {
		
		x = this->ulx + col*this->dx;
		y = lly + row*this->dx;
		
		compute_pixel(this->pixels + 3*(row*ncols + col), x, y, maxIter);
		
	    }
	}
	break;
    case 1:
    case 2:
    case 3:
	int i;
	float buffer[3];
	double x_local;
	double y_local;
	
#pragma omp parallel for private(col,row,buffer,i,x,y,x_local,y_local) schedule(dynamic)
	for(row=0; row < nrows; row++)
	{
	    for(col=0; col < ncols; col++)
	    {
		
		x = this->ulx + col*this->dx;
		y = lly + row*this->dx;

		this->pixels[3*(row*ncols + col)] = 0;
		this->pixels[3*(row*ncols + col) + 1] = 0;
		this->pixels[3*(row*ncols + col) + 2] = 0;

		
		for(i=0; i<n_samples; i++)
		{
		    x_local = x + this->dx * ( (0.5 + (i % n_side)) / n_side  - 0.5);
		    y_local = y + this->dx * ( (0.5 + (i / n_side)) / n_side  - 0.5);
		    
		    compute_pixel(buffer,
				  x_local,
				  y_local,
				  maxIter);
		
		    this->pixels[3*(row*ncols + col)] += buffer[0];
		    this->pixels[3*(row*ncols + col) + 1] += buffer[1];
		    this->pixels[3*(row*ncols + col) + 2] += buffer[2];
		}
		
		this->pixels[3*(row*ncols + col)] /= n_samples;
		this->pixels[3*(row*ncols + col) + 1] /= n_samples;
		this->pixels[3*(row*ncols + col) + 2] /= n_samples;
	    }
	}
	
	break;
    default:
	cerr << "Invalid antialiasing level specified" << endl;
	exit(1);
	break;
    }

    uptodate = true;

    
    clock_t t2 = clock();
    cout << "Time in compute: "<< ((double)(t2-t1))/CLOCKS_PER_SEC << " s" << endl;
}




void compute_pixel(float *dest, double x, double y, int maxIter)
{
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
	for (k=1; zx*zx + zy*zy <4 && k<maxIter ; k++)
	{
	    temp = zx;
	    zx = zx*zx - zy*zy + x;
	    zy = 2*temp*zy + y;
	}

	// if we escaped, perform two additional rounds
	if(k < maxIter)
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
	dest[0] = 0;
	dest[1] = 0;
	dest[2] = 0;

    }
    else
    {
	colorize(dest, res, maxIter);
    }

}

inline
void colorize(float *dest, double param,int maxIter)
{
    hslf t1 = tint1_hsl;
    hslf t2 = tint2_hsl;
    

    if( int(10*(param)/maxIter) % 2 == 0)
    {
	t1.l = 0.5 + 0.5*sin(5*M_PI*(2*param/maxIter - 0.5));
	t2.l = 0;
    }
    else
    {
	t1.l = 0;
	t2.l = 0.5 + 0.5*sin(5*M_PI*(2*param/maxIter - 0.5));
    }
    
    rgbf col1, col2;
    
    hslf2rgbf(&col1,&t1);
    hslf2rgbf(&col2,&t2);
    
    dest[0] = col1.r + col2.r;
    dest[1] = col1.g + col2.g;
    dest[2] = col1.b + col2.b;
}


void Mtexture::bind()
{
    glBindTexture(GL_TEXTURE_2D, this->textureId); //Tell OpenGL which texture to edit
    
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
    		 0,                            //0 for now
    		 GL_RGB,                       //Format OpenGL uses for image
    		 this->width, this->height,    //Width and height
    		 0,                            //The border of the image
    		 GL_RGB, //GL_RGB, because pixels are stored in RGB format
    		 GL_FLOAT, //GL_UNSIGNED_BYTE, because pixels are stored
    		 		   //as unsigned numbers
    		 this->pixels);               //The actual pixel data

    
}


void Mtexture::draw()
{
    if(!this->uptodate)
    {
	this->compute();
	this->bind();
    }
    

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

void Mtexture::writeToBMP(const char *filename)
{
    write_to_BMP(filename, this->pixels, width, height);
    
}
