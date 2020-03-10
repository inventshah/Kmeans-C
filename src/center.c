// Sachin Shah
// March 9, 2020

#include "center.h"
#include "image.h"

#include <math.h>
#include <png.h>
#include <stdlib.h>


Center *create_center(Color red, Color green, Color blue, Color label)
{
	Center *temp = (Center *) malloc(sizeof(Color));
	temp->red = red;
	temp->green = green;
	temp->blue = blue;
	temp->label = label;

	return temp;
}

double center_distance(Center *center, png_bytep rgb)
{
	double rdiff, gdiff, bdiff;
	rdiff = center->red - rgb[0];
	gdiff = center->green - rgb[1];
	bdiff = center->blue - rgb[2];

	rdiff *= rdiff;
	gdiff *= gdiff;
	bdiff *= bdiff;

	return sqrt(rdiff + gdiff + bdiff);
}

void center_add(Center *center, Color red, Color green, Color blue)
{
	center->red += red;
	center->green += green;
	center->blue += blue;
}

void center_divide(Center *center, uint n)
{
	center->red /= n;
	center->green /= n;
	center->blue /= n;
}

Center *center_clone(Center *center)
{
	return create_center(center->red, center->green, center->blue, center->label);
}

void center_copy(Center *src, Center *dest)
{
	dest->red = src->red;
	dest->green = src->green;
	dest->blue = src->blue;
	dest->label = src->label;
}

char center_equals(Center *c, Center *d)
{
	return (c->red == d->red && c->green == d->green && c->blue == d->blue);
}
