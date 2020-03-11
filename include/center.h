// Sachin Shah
// March 9, 2020
// Keep track of group centers

#ifndef _CENTERS_H
#define _CENTERS_H

#include "image.h"

#include <png.h>
#include <stdint.h>

struct center
{
	uint32_t red;
	uint32_t green;
	uint32_t blue;
};

typedef struct center Center;

Center *create_center(uint8_t red, uint8_t green, uint8_t blue);

int center_distance(Center *center, png_bytep rgb);

void center_add(Center *center, png_bytep rgb);
void center_divide(Center *center, uint32_t n);


void center_copy(Center *src, Center *dest);
uint8_t center_equals(Center *c, Center *d);

#endif