/*
 * @(#)colorspaces.h
 * @author Karl Ljungkvist
 * Last changed: <2010-02-28 12:09:28 CET>
 *
 *   
 */

#ifndef _COLORSPACES_H
#define _COLORSPACES_H

typedef struct {
    float r;
    float g;
    float b;
} rgbf;

typedef struct {
    float h;
    float s;
    float v;
} hsvf;

typedef struct {
    float h;
    float s;
    float l;
} hslf;

void hsvf2rgbf(rgbf *dest, const hsvf *src);
void rgbf2hsvf(hsvf *dest, const rgbf *src);

void hslf2rgbf(rgbf *dest, const hslf *src);
void rgbf2hslf(hslf *dest, const rgbf *src);


#endif /* _COLORSPACES_H */

