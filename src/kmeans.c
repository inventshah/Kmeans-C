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

void segment(Image *img, uint k, uint max_gens)
{
	char cont = 1;
	uint gen = 0, x, y, center;
	Center *centers = init(k);

	Center *sums = (Center *) calloc(k, sizeof(Center));
	uint *nums = (uint *) calloc(k, sizeof(uint));

	double current_dist, min_dist = MAX_DIST;

	Color closest_label = 0;

	while (cont && gen < max_gens)
	{
		printf("gen=%d\n", gen);
		for (x = 0; x < img->width; x++)
		{
			for (y = 0; y < img->height; y++)
			{
				for (center = 0; center < k; center++)
				{
					current_dist = center_distance(&centers[center], get_rgb(img, x, y));
					if (current_dist < min_dist)
					{
						min_dist = current_dist;
						closest_label = center;
					}
				}

				set_label(img, x, y, closest_label);

				center_add(&sums[closest_label], get_rgb(img, x, y));

				nums[closest_label]++;
				min_dist = MAX_DIST;
			}
		}

		cont = calculate_centers(nums, sums, centers, k);

		free(sums);
		free(nums);
		sums = (Center *) calloc(k, sizeof(Center));
		nums = (uint *) calloc(k, sizeof(uint));
		gen++;
	}

	colorize(img, centers, k);

	free(centers);
	free(sums);
	free(nums);
}

void colorize(Image *img, Center *centers, uint k)
{
	int x, y, label;
	Center center;

	for (x = 0; x < img->width; x++)
	{
		for (y = 0; y < img->height; y++)
		{
			label = *(get_rgb(img, x, y) + 3);

			center = centers[label];
			set_rgba(img, x, y, center.red, center.green, center.blue, 255);
		}
	}
}

char calculate_centers(uint *nums, Center *sums, Center *old_centers, uint k)
{
	int i;
	Center *center;
	char ret = 0;

	for (i = 0; i < k; i++)
	{
		if (nums[i] != 0)
		{
			center_divide(&sums[i], nums[i]);

			if (!center_equals(&old_centers[i], &sums[i])) ret = 1;
			center_copy(&sums[i], &old_centers[i]);
		}
		else
		{
			center = &old_centers[i];
			center->red = random_color();
			center->green = random_color();
			center->blue = random_color();
			ret = 1;
		}
	}

	return ret;
}

Center *init(uint k)
{
	int i;
	Center *center, *centers = (Center *) calloc(k, sizeof(Center));

	if (centers == NULL)
	{
		fprintf(stderr, "Unable to init centers");
		exit(0);
	}

	srand(time(NULL));

	for (i = 0; i < k; i++)
	{
		center = &centers[i];
		center->red = random_color();
		center->green = random_color();
		center->blue = random_color();
		center->label = i;
	}

	for (i = 0; i < k; i++) printf("\ninit %d: rgb(%d, %d, %d)\n", i, centers[i].red, centers[i].green, centers[i].blue);

	return centers;
}

Color random_color(void)
{
	return rand() % 256;
}