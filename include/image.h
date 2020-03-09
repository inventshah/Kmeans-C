// Sachin Shah
// March 9, 2020
// PNG image read/write methods

#ifndef _IMAGE_H
#define _IMAGE_H

#include <png.h>
#include <stdint.h>

struct image
{
	unsigned int width;
	unsigned int height;
	png_bytep *image;
};

typedef struct image Image;

typedef uint8_t Color;
typedef unsigned int uint;

png_bytep get_rgb(Image *img, uint x, uint y);
void set_rgb(Image *img, uint x, uint y, Color r, Color g, Color b);

void error(char *msg);
void print_info(uint width, uint height, int color_type, int bit_depth);

Image *open_image(char *filename);
void save_image(Image *img, char *filename, int alpha_channel);

void *free_image(Image *img);

#endif