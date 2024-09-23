#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "hash_tables.h"

/**
 * key_index - Provides the index of a key
 * @key: The key
 * @size: The size of the array in the table
 *
 * Return: The index where the key/value pair is stored
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	return (hash_djb2(key) % size);
}
