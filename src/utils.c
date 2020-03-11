// Sachin Shah
// March 10, 2020

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

void error(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(0);
}

void check_null(void *ptr, char *msg)
{
	if (ptr == NULL) error(msg);
}