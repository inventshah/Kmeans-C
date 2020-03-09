// Sachin Shah
// March 9, 2020

#include "kmeans.h"

#include "center.h"
#include "image.h"

#include <png.h>

Image *segment(Image *img, uint k);

Center *calculate_centers(uint *nums, Center *sums, Center *old_centers, uint k);

Center *init(uint k);

Color random(void);