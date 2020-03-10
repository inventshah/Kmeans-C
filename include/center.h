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

double center_distance(Center *center, png_bytep rgb);

void center_add(Center *center, Color red, Color green, Color blue);
void center_divide(Center *center, uint n);

Center *center_clone(Center *center);

void center_copy(Center *src, Center *dest);
char center_equals(Center *c, Center *d);

#endif