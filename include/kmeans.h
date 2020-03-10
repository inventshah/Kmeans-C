// Sachin Shah
// March 9, 2020
// Main K-Mean methods

#ifndef _KMEANS_H
#define _KMEANS_H

#include "center.h"
#include "image.h"

#include <png.h>

Image *segment(Image *img, uint k);

char *calculate_centers(uint *nums, Center *sums, Center *old_centers, uint k);

Center *init(uint k);

Color random(void);

#endif