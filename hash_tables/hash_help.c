#include "hash_tables.h"

/**
 * hash_djb2 - Implements the djb2 algorithm
 * @str: Data to be processed
 *
 * Return: The resulting hash value
 */
unsigned long int hash_djb2(const unsigned char *str)
{
	unsigned long int hash;
	int c;

	hash = 5381;
	while ((c = *str++))
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	return (hash);
}

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
