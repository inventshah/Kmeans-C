// Sachin Shah
// March 9, 2020
// Main K-Mean methods

#ifndef _KMEANS_H
#define _KMEANS_H

#include "center.h"
#include "image.h"

#include <png.h>

void segment(Image *img, uint k, uint max_gens);

char calculate_centers(uint *nums, Center *sums, Center *old_centers, uint k);

void colorize(Image *img, Center *centers, uint k);

Center *init(uint k);

Color random_color(void);

#endif