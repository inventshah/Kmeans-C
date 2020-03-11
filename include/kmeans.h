// Sachin Shah
// March 9, 2020
// Main K-Mean methods

#ifndef _KMEANS_H
#define _KMEANS_H

#include "center.h"
#include "image.h"

#include <png.h>
#include <stdint.h>

void segment(Image *img, uint8_t k, uint32_t max_gens);

uint8_t calculate_centers(uint32_t *nums, Center *sums, Center *old_centers, uint8_t k);

void colorize(Image *img, Center *centers, uint8_t k);

Center *init(uint8_t k);

uint8_t random_color(void);

#endif