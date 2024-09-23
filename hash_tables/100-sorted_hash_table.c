#include "hash_tables.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/**
 * shash_table_create - Creates a new sorted hash table of given size
 * @size: The size of the hash table
 *
 * Return: A pointer to the new table, or NULL
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	unsigned long int i;
	shash_table_t *new_t;

	if (size <= 0)
		return (NULL);
	new_t = malloc(sizeof(shash_table_t));
	if (!new_t)
		return (NULL);
	new_t->size = size;
	new_t->array = malloc(size * sizeof(shash_node_t *));
	if (new_t->array == NULL)
	{
		free(new_t);
		return (NULL);
	}
	for (i = 0; i < size; i++)
		new_t->array[i] = NULL;
	return (new_t);
}

/**
 * shash_table_set - Adds an element to the sorted hash table
 * @ht: The hash table to be used
 * @key: The key
 * @value: The value associated with the key
 *
 * Return: 1 if successful 0 if not
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	char *tvalue, *tkey;
	shash_node_t *new_node, *temp;

	if ((!key) || (!ht))
		return (0);
	tkey = strdup(key);
	tvalue = strdup(value);
	index = key_index((unsigned const char *)tkey, ht->size);
	if (!index)
		index = 0;
	temp = ht->array[index];
	while (temp != NULL)
	{
		if (strncmp(key, temp->key, strlen(key)) == 0)
		{
			free(temp->value);
			free(tkey);
			temp->value = tvalue;
			if (temp->value == NULL)
				return (0);
			else
				return (1);
		}
		temp = temp->next;
	}
	new_node = malloc(sizeof(shash_node_t));
	if (!new_node)
	{
		return (0);
	}
	new_node->key = tkey;
	new_node->value = tvalue;
	new_node->next = ht->array[index];
	ht->array[index] = new_node;
	return (1);
}

/**
 * shash_table_get - Finds value that matches key
 * @ht: The hash table to be used
 * @key: The key
 *
 * Return: Value if successful NULL if not
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int index;
	char *tkey, *tvalue;
	shash_node_t *temp;

	if ((!key) || (!ht))
		return (0);
	tkey = strdup(key);
	index = key_index((unsigned const char *)tkey, ht->size);
	if (!index)
		return (NULL);
	temp = ht->array[index];
	while (temp != NULL)
	{
		if (strncmp(key, temp->key, strlen(key)) == 0)
		{
			tvalue = temp->value;
			return (tvalue);
		}
		temp = temp->next;
	}
	return (NULL);
}

/**
 * shash_table_print - Prints the sorted hash table
 * @ht: The hash table to be used
 *
 * Return: No return
 */
void shash_table_print(const shash_table_t *ht)
{
	unsigned long int i, j;
	shash_node_t *temp;
	char *tkey, *tvalue;

	j = 0;
	if (ht != NULL)
	{
		putchar('{');
		for (i = 0; i < ht->size; i++)
		{
			if (ht->array[i] != NULL)
			{
				temp = ht->array[i];
				while (temp)
				{
					if (j > 0)
						printf(", ");
					tkey = temp->key;
					tvalue = temp->value;
					printf("'%s': '%s'", tkey, tvalue);
					temp = temp->next;
					j = 1;
				}
			}
		}
		printf("}\n");
	}
}

/**
 * shash_node_delete - Deletes the current node of the table
 * @temp: The node to be deleted recursively
 *
 * Return: No return
 */
void shash_node_delete(shash_node_t *temp)
{
	if (temp == NULL)
		return;
	shash_node_delete(temp->next);
	free(temp->key);
	free(temp->value);
	free(temp);
}

/**
 * shash_table_delete - Deletes the sorted hash table
 * @ht: The hash table to be deleted
 *
 * Return: No return
 */
void shash_table_delete(shash_table_t *ht)
{
	unsigned long int i;
	shash_node_t *temp;

	if (ht != NULL)
	{
		for (i = 0; i < ht->size; i++)
		{
			if (ht->array[i] != NULL)
			{
				temp = ht->array[i];
				shash_node_delete(temp);
			}
		}
	}
	free(ht->array);
	free(ht);
}
