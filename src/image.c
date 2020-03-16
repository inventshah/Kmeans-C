// Sachin Shah
// March 9, 2020

#include "image.h"
#include "utils.h"

#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

// Get a pointer to RGB array of (x, y) pixel
png_bytep get_rgb(Image *img, uint32_t x, uint32_t y)
{
	if (not_in_bounds(img, x, y)) return NULL;
	return &(img->image[y][x * 4]);
}

// Set the RGB values of an (x, y) pixel
void set_rgb(Image *img, uint32_t x, uint32_t y, uint8_t red, uint8_t green, uint8_t blue)
{
	if (not_in_bounds(img, x, y)) return;

	png_bytep pixel = &(img->image[y][x * 4]);
	pixel[0] = red;
	pixel[1] = green;
	pixel[2] = blue;
}

// Set the RGBA values of an (x, y) pixel
void set_rgba(Image *img, uint32_t x, uint32_t y, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	if (not_in_bounds(img, x, y)) return;

	png_bytep pixel = &(img->image[y][x * 4]);
	pixel[0] = red;
	pixel[1] = green;
	pixel[2] = blue;
	pixel[3] = alpha;
}

// Set the Alpha value of an (x, y) pixel, acts as label for kmeans
void set_label(Image *img, uint32_t x, uint32_t y, uint8_t label)
{
	if (not_in_bounds(img, x, y)) return;
	img->image[y][x * 4 + 3] = label;
}

// Print image info
void print_info(uint32_t width, uint32_t height, int uint8_t_type, int bit_depth)
{
	printf("\twidth:  %d\n", width);
	printf("\theight: %d\n", height);
	printf("\ttype:   %d\n", uint8_t_type);
	printf("\tdepth:  %d\n", bit_depth);
}

// Check if a point (x, y) is in the image
int8_t not_in_bounds(Image *img, uint32_t x, uint32_t y)
{
	return (x < 0 || y < 0 || x > img->width || y > img->height);
}

// Gamma correction and normalization
uint8_t gamma_correct(uint32_t num)
{
	return (num * num) >> 8;
}

uint8_t gamma_reset(uint32_t num)
{
	return sqrt(num << 8);
}

// Open and read an image
Image *open_image(char *filename)
{
	int num_row_bytes, i;

	FILE *fp;

	png_infop info;
	png_structp png;
	png_byte color_type, bit_depth;

	// Allocate space
	Image *img = (Image *) malloc(sizeof(Image));
	check_null(img, "Unable to malloc Image in open_png");

	printf("Opening %s...\n", filename);
	fp = fopen(filename, "rb");
	check_null(fp, "Unable to open file");

	png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	check_null(png, "Unable to create png struct in open_png");

	info = png_create_info_struct(png);
	check_null(info, "Unable to create info struct in open_png");

	if(setjmp(png_jmpbuf(png))) error("setjmp() returned true in open_png");

	png_init_io(png, fp);

	png_read_info(png, info);

	// Get image info
	img->width = png_get_image_width(png, info);
	img->height = png_get_image_height(png, info);

	color_type = png_get_color_type(png, info);
	bit_depth  = png_get_bit_depth(png, info);

	print_info(img->width, img->height, color_type, bit_depth);

	// Configure the png
	if(bit_depth == 16) png_set_strip_16(png);
	if(color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png);
	if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png);
	if(png_get_valid(png, info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png);

	png_read_update_info(png, info);

	// Allocate the image space
	num_row_bytes = png_get_rowbytes(png, info);
	img->image = (png_bytep *) malloc(sizeof(png_bytep) * img->height);
	check_null(img, "Unable to malloc png_bytep for Image in open_png");

	for (i = 0; i < img->height; i++)
	{
		img->image[i] = (png_bytep) malloc(num_row_bytes);
		check_null(img, "Unable to malloc png_bytep for Image in open_png");
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

void save_image(Image *img, char *filename)
{
	int i;
	FILE *fp;

	png_infop info;
	png_structp png;
	png_byte color_type, bit_depth;

	printf("Saving file %s...\n", filename);

	fp = fopen(filename, "wb");
	check_null(fp, "Unable to open file");

	png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	check_null(png, "Unable to create png struct in open_png");

	info = png_create_info_struct(png);
	check_null(info, "Unable to create info struct in open_png");

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

	check_null(img->image, "Image data was null");

	png_write_image(png, img->image);
	png_write_end(png, NULL);

	fclose(fp);

	png_destroy_write_struct(&png, &info);
}
