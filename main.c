// Sachin Shah
// March 9, 2020

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "kmeans.h"
#include "image.h"

int main(void)
{
	Image *img = open_image("source.png");

	segment(img, 3, 50);

	save_image(img, "kmean.png");

	img = free_image(img);

	return 0;
}