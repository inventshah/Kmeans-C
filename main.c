// Sachin Shah
// March 9, 2020

#include <stdlib.h>
#include <stdio.h>

#include "kmeans.h"
#include "image.h"

int main(void)
{
	Image *img = open_image("source.png");

	segment(img, 3, 10);

	save_image(img, "test.png", 1);

	img = free_image(img);
	return 0;
}