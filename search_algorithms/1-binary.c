#include "search_algos.h"

/**
 * binary_search - Implements a binary search for the value
 * @array: The array to be searched
 * @size: The size of the array
 * @value: The value to search for
 *
 * Return: The index of the array where value is, or -1 on fail
 */

int binary_search(int *array, size_t size, int value)
{
	size_t low = 0, high = size - 1, middle = 0;

	if (array == NULL)
		return (-1);
	print_array(array, low, high);
	while (low <= high)
	{
		middle = (low + high) / 2;
		if (array[middle] == value)
			return (middle);
		else if (array[middle] < value)
			low = middle + 1;
		else
			high = middle - 1;
		print_array(array, low, high);
	}
	return (-1);
}

/**
 * print_array - Prints the array being searched
 * @array: The array to be printed
 * @low: The starting index
 * @high: The highest index to be printed
 *
 * Return: No return
 */
void print_array(int *array, size_t low, size_t high)
{
	size_t i;

	i = low;
	if (i > high)
		return;
	printf("Searching in array: ");
	while (array && i <= high)
	{
		if (i > low)
			printf(", ");
		printf("%d", array[i]);
		i++;
	}
	printf("\n");
}
