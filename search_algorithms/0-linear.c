#include "search_algos.h"

/**
 * linear_search - Implements a linear search for the value
 * @array: The array to be searched
 * @size: The size of the array
 * @value: The value to search for
 *
 * Return: The index of the array where value is, or -1 on fail
 */

int linear_search(int *array, size_t size, int value)
{
	size_t i = 0;

	if (array == NULL)
		return (-1);
	for (i = 0; i < size; i++)
	{
		printf("Value checked array[%ld] = [%d]\n", i, array[i]);
		if (array[i] == value)
			return (i);
	}
	return (-1);
}
