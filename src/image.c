// Sachin Shah
// March 9, 2020

#include "image.h"

#include <png.h>
#include <stdio.h>
#include <stdlib.h>


png_bytep get_rgb(Image *img, uint x, uint y)
{
	if (x < 0 || y < 0 || x > img->width || y > img->height) return NULL;
	return &(img->image[y][x * 4]);
}

void set_rgb(Image *img, uint x, uint y, Color r, Color g, Color b)
{
	if (x < 0 || y < 0 || x > img->width || y > img->height) return;

	png_bytep pixel = &(img->image[y][x * 4]);
	pixel[0] = r;
	pixel[1] = g;
	pixel[2] = b;
	pixel[3] = 100;
}

void error(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(0);
}

void print_info(uint width, uint height, int color_type, int bit_depth)
{
	printf("\twidth:  %d\n", width);
	printf("\theight: %d\n", height);
	printf("\ttype:   %d\n", color_type);
	printf("\tdepth:  %d\n", bit_depth);
}

// Open and read an image
Image *open_image(char *filename)
{
	int num_row_bytes, i;

	FILE *fp;

	png_infop info;
	png_structp png;
	png_byte color_type, bit_depth;

	Image *img = (Image *) malloc(sizeof(Image));
	if (img == NULL) error("Unable to malloc Image in open_png");

	printf("Opening %s...\n", filename);
	fp = fopen(filename, "rb");
	if (fp == NULL) error("Unable to open file");

	png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(png == NULL) error("Unable to create png struct in open_png");

	info = png_create_info_struct(png);
	if(info == NULL) error("Unable to create info struct in open_png");

	if(setjmp(png_jmpbuf(png))) error("setjmp() returned true in open_png");

	png_init_io(png, fp);

	png_read_info(png, info);

	img->width = png_get_image_width(png, info);
	img->height = png_get_image_height(png, info);

	color_type = png_get_color_type(png, info);
	bit_depth  = png_get_bit_depth(png, info);

	print_info(img->width, img->height, color_type, bit_depth);

	if(bit_depth == 16) png_set_strip_16(png);
	if(color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png);
	if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png);
	if(png_get_valid(png, info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png);

	png_read_update_info(png, info);

	// Allocate the image space
	num_row_bytes = png_get_rowbytes(png, info);
	img->image = (png_bytep *) malloc(sizeof(png_bytep) * img->height);
	for (i = 0; i < img->height; i++)
	{
		img->image[i] = (png_bytep) malloc(num_row_bytes);
	}

	png_read_image(png, img->image);

	fclose(fp);
	png_destroy_read_struct(&png, &info, NULL);

	return img;
}

// Free image memory allocations
void *free_image(Image *img)
{
	int i;

	if (img == NULL) return NULL;
	if (img->image == NULL) return NULL;

	for (i = 0; i < img->height; i++) free(img->image[i]);

	free(img->image);
	free(img);

	return NULL;
}

void save_image(Image *img, char *filename, int alpha_channel)
{
	int i;
	FILE *fp;

	png_infop info;
	png_structp png;
	png_byte color_type, bit_depth;

	printf("Saving file %s...\n", filename);

	fp = fopen(filename, "wb");
	if(fp == NULL) error("Unable to save file");

	png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png == NULL) error("Unable to create png struct in save_png");

	info = png_create_info_struct(png);
	if (info == NULL) error("Unable to create info struct in save_png");

	if (setjmp(png_jmpbuf(png))) error("setjmp() returned true in save_png");

	png_init_io(png, fp);

	// Output is 8-bit depth, RGBA format
	png_set_IHDR(
		png,
		info,
		img->width, img->height,
		8,
		PNG_COLOR_TYPE_RGBA,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT
	);
	png_write_info(png, info);

	// remove alpha channel
	if (alpha_channel == 0) png_set_filler(png, 0, PNG_FILLER_AFTER);

	if (img->image == NULL) abort();

	png_write_image(png, img->image);
	png_write_end(png, NULL);

	fclose(fp);

	png_destroy_write_struct(&png, &info);
}
