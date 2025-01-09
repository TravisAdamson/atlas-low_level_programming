#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>

void print_array(int *array, size_t low, size_t high);
int linear_search(int *array, size_t size, int value);
int binary_search(int *array, size_t size, int value);

#endif
