#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>

#define POSITION(l, h, a, v) \
	(l + (((double)(h - l) / (a[h] - a[l]))) * (v - a[l]))

void print_array(int *array, size_t low, size_t high);
int linear_search(int *array, size_t size, int value);
int binary_search(int *array, size_t size, int value);

int interpolation_search(int *array, size_t size, int value);
int exponential_search(int *array, size_t size, int value);

#endif
