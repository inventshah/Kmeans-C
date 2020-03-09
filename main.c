// Sachin Shah
// March 9, 2020

#include <stdlib.h>
#include <stdio.h>

#include "image.h"

int main(void)
{
	Image *img = open_image("source.png");

	png_bytep rgb = get_rgb(img, 0, 0);

	printf("%d, %d, %d, %d\n", rgb[0], rgb[1], rgb[2], rgb[3]);

	set_rgb(img, 0, 0, 255, 0, 0);

	save_image(img, "test.png", 1);

	img = free_image(img);
	return 0;
}