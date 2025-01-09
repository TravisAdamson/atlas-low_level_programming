#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>

#define POSITION(l, h, a, v) \
	(l + (((double)(h - l) / (a[h] - a[l]))) * (v - a[l]))

int binary_search(int *array, size_t min, size_t max, size_t size, int value);
void print_search(int *array, size_t min, size_t max);

int interpolation_search(int *array, size_t size, int value);
int exponential_search(int *array, size_t size, int value);

#endif
