/*
 * @(#)bmpio.cpp
 * @author Karl Ljungkvist
 * Last changed: <2010-03-13 09:38:08 CET>
 *
 * Mostly stolen from here:
 * http://www.siggraph.org/education/materials/HyperVis/asp_data/compimag/bmpfile.htm
 * 
 */



#include "bmpio.h"

#include "log.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
// #include <cstdint> //should really use these...

// The magic number is stored separately from the header to avoid alignment issues.

typedef struct {
    unsigned char id[2];
} BMPMAGIC;


typedef struct {
    long filesize;
    char reserved[2];
    long headersize;
    long infoSize;
    long width;
    long depth;
    short biPlanes;
    short bits;
    long biCompression;
    long biSizeImage;
    long biXPelsPerMeter;
    long biYPelsPerMeter;
    long biClrUsed;
    long biClrImportant;
} BMPHEAD;


void write_to_BMP(const char *filename, const float *pixels, int width, int height)
{

    LOG("write_to_BMP(%s, 0x%x, %d, %d)\n", \
	filename, (unsigned int)pixels, width, height);

    BMPMAGIC bmag;
    BMPHEAD bh;
 
    memset ((char *)&bh,0,sizeof(BMPHEAD)); /* sets everything to 0 */
    memset ((char *)&bmag,0,sizeof(BMPMAGIC)); /* sets everything to 0 */
    memcpy (bmag.id,"BM",2);
    // bh.filesize  =   calculated size of your file (see below)
    // bh.reserved  = two zero bytes
    bh.headersize  = 54L;  //(for 24 bit images)
    bh.infoSize  =  0x28L;  //(for 24 bit images)
    bh.width     = long(width);//width in pixels of your image
    bh.depth     = long(height);//depth in pixels of your image
    bh.biPlanes  =  1; //(for 24 bit images)
    bh.bits      = 24; //(for 24 bit images)
    bh.biCompression = 0L;  //(no compression)

    // The number of bytes in each line of a .BMP file is always a multiple of 4
    // as Windows does DoubleWord Alignment on line boundaries. You need a
    // variable bytesperline that specifies how many bytes there are in a line.

    int bytesPerLine;

    bytesPerLine = bh.width * 3;  /* (for 24 bit images) */
    /* round up to a dword boundary */
    if (bytesPerLine & 0x0003) 
    {
	bytesPerLine |= 0x0003;
	++bytesPerLine;
    }

    bh.filesize=bh.headersize + (long)bytesPerLine*bh.depth;


    
    FILE * bmpfile;

    bmpfile = fopen(filename, "wb");
    if (bmpfile == NULL)
    {
	fprintf(stderr,"Error opening output file\n");
	/* -- close all open files and free any allocated memory -- */
	exit (1);
    }
    fwrite(&bmag, 1, sizeof (bmag), bmpfile);
    fwrite(&bh, 1, sizeof (bh), bmpfile);
    
    char *linebuf;

    linebuf = (char *) calloc(1, bytesPerLine);
    if (linebuf == NULL)
    {
	printf ("Error allocating memory\n");
	/* -- close all open files and free any allocated memory -- */
	exit (1);   
    }


    int line;

    for (line = 0; line < height; line ++)
    {
	/* fill line linebuf with the image data for that line */
	for (int i = 0; i < width*3; i+=3)
	{
	    // flip order since bmp stores as 'BGR'.
	    linebuf[i+0] = (char) (255*pixels[i + 3*width*line + 2]);
	    linebuf[i+1] = (char) (255*pixels[i + 3*width*line + 1]);
	    linebuf[i+2] = (char) (255*pixels[i + 3*width*line + 0]);
	}

	fwrite(linebuf, 1, bytesPerLine, bmpfile);
    }

    fclose(bmpfile);

}
