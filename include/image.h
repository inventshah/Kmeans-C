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

png_bytep get_rgb(Image *img, uint32_t x, uint32_t y);
void set_rgb(Image *img, uint32_t x, uint32_t y, uint8_t red, uint8_t green, uint8_t blue);
void set_rgba(Image *img, uint32_t x, uint32_t y, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
void set_label(Image *img, uint32_t x, uint32_t y, uint8_t label);

void print_info(uint32_t width, uint32_t height, int uint8_t_type, int bit_depth);

int8_t not_in_bounds(Image *img, uint32_t x, uint32_t y);

Image *open_image(char *filename);
void save_image(Image *img, char *filename);

void *free_image(Image *img);

#endif