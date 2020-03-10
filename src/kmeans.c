// Sachin Shah
// March 9, 2020

#include "kmeans.h"

#include "center.h"
#include "image.h"

#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DIST 765;

Image *segment(Image *img, uint k, uint max_gens)
{
	char cont = 1 ;
	uint gen = 0, x, y, center;
	Center *centers = init(k);

	Center *sums = (Center *) malloc(sizeof(Center) * k);
	uint *nums = (uint *) malloc(sizeof(uint) * k);

	double min_dist = current_dist = MAX_DIST;

	Color closest_label = 0;

	while (cont && gen < max_gens)
	{
		for (x = 0; x < img->width; x++)
		{
			for (y = 0; y < img->height; y++)
			{
				for (center = 0; center < k; center++)
				{
					current_dist = center_distance(centers[center], get_rgb(img, x, y));
					if (current_dist < min_dist)
					{
						min_dist = current_dist;
						closest_label = center;
					}
				}
				set_rgb
			}
		}


		gen++;
	}


	free(centers);
	free(sums);
	free(nums);

}

char *calculate_centers(uint *nums, Center *sums, Center *old_centers, uint k)
{
	int i;
	Center *center;
	char ret = 0;

	for (i = 0; i < k; i++)
	{
		if (nums[i] != 0)
		{
			center_divide(&sums[i], nums[i]);

			if (!center_equals(&old_centers[i], sums[i])) ret = 1;
			center_copy(sums, &old_centers[i]);
		}
		else
		{
			center = &old_centers[i];
			center->red = random();
			center->green = random();
			center->blue = random();
			ret = 1;
		}
		
	}

	return ret;
}

Center *init(uint k)
{
	int i;
	Center *center, *centers = (Center *) malloc(sizeof(Center) * k);

	if (centers == NULL)
	{
		fprintf("Unable to init centers");
		exit(0);
	}

	srand(time(NULL));

	for (i = 0; i < k; i++)
	{
		center = &centers[i];
		center->red = random();
		center->green = random();
		center->blue = random();
		center->label = i;
	}

	return centers;
}

Color random(void)
{
	return rand() % 256;
}