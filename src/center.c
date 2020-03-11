// Sachin Shah
// March 9, 2020

#include "center.h"
#include "image.h"
#include "utils.h"

#include <math.h>
#include <png.h>
#include <stdint.h>
#include <stdlib.h>

// Create a new ceneter with RGB inital values
Center *create_center(uint8_t red, uint8_t green, uint8_t blue)
{
	Center *temp = (Center *) malloc(sizeof(uint8_t));
	check_null(temp, "malloc failed to find space for Center");

	temp->red = red;
	temp->green = green;
	temp->blue = blue;

	return temp;
}

// Calculate squared Euclidean distance between a center and a pixel
int center_distance(Center *center, png_bytep rgb)
{
	int rdiff, gdiff, bdiff;
	rdiff = center->red - rgb[0];
	gdiff = center->green - rgb[1];
	bdiff = center->blue - rgb[2];

	rdiff *= rdiff;
	gdiff *= gdiff;
	bdiff *= bdiff;

	return rdiff + gdiff + bdiff;
}

// Add RGB to a center's RGB
void center_add(Center *center, png_bytep rgb)
{
	center->red += rgb[0];
	center->green += rgb[1];
	center->blue += rgb[2];
}

// Divide the center RGB by a umber
void center_divide(Center *center, uint32_t n)
{
	center->red /= n;
	center->green /= n;
	center->blue /= n;
}

// Copy Center struct from src to dest
void center_copy(Center *src, Center *dest)
{
	dest->red = src->red;
	dest->green = src->green;
	dest->blue = src->blue;
}

// Check if the RGB of two centers are equal
uint8_t center_equals(Center *c, Center *d)
{
	return (c->red == d->red && c->green == d->green && c->blue == d->blue);
}
