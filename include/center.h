// Sachin Shah
// March 9, 2020
// Keep track of group centers

#ifndef _CENTERS_H
#define _CENTERS_H

#include "image.h"

#include <png.h>

struct center
{
	uint red;
	uint blue;
	uint green;
	Color label;
};

typedef struct center Center;

Center *create_center(Color red, Color green, Color blue, Color label);

double distance(Center *center, png_bytep rgb);

void add(Center *center, Color red, Color green, Color blue);
void divide(Center *center, uint n);

Center *clone(Center *center);
char equals(Center *c, Center *d);

#endif