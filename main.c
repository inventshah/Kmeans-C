// Sachin Shah
// March 9, 2020

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "kmeans.h"
#include "image.h"
#include "utils.h"

int main(int argc, char **argv)
{
	Image *img = NULL;
	char *source, *save;
	uint8_t k;
	uint32_t gens = 100;

	if (argc < 4) error("Too few command line arguments. Need [source filename] [output filename] [K value]. Optional [Max gens]");

	img = open_image(argv[1]);
	k = atoi(argv[3]);

	if (argc == 5) gens = atoi(argv[4]);

	segment(img, k, gens);
	save_image(img, argv[2]);

	img = free_image(img);

	return 0;
}