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
	new_t->shead = NULL;
	new_t->stail = NULL;
	new_t->array = calloc(size, sizeof(shash_node_t *));
	if (new_t->array == NULL)
	{
		free(new_t);
		return (NULL);
	}
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
	shash_node_t *new_node, *temp, *temp2;

	if ((!key) || (!ht) || *key != '\0')
		return (0);
	index = key_index((unsigned const char *)key, ht->size);
	if (!index)
		index = 0;
	temp = ht->array[index];
	for (; temp; temp = temp->next)
	{
		if (!strcmp(temp->key, key))
		{
			free(temp->value);
			temp->value = strdup(value);
			return (1);
		}
	}
	new_node = malloc(sizeof(shash_node_t));
	if (!new_node)
	{
		return (0);
	}
	new_node->key = strdup(key);
	new_node->value = strdup(value);
	new_node->next = ht->array[index], ht->array[index] = new_node;
	if (!ht->shead)
	{
		ht->shead = new_node, ht->stail = new_node;
		new_node->sprev = NULL, new_node->snext = NULL;
		return (1);
	}
	if (strcmp(ht->shead->key, key) > 0)
	{
		new_node->snext = ht->shead, new_node->sprev = NULL;
		ht->shead->sprev = new_node, ht->shead = new_node;
		return (1);
	}
	temp2 = ht->shead;
	for (; temp2; temp2 = temp2->snext)
	{
		if (strcmp(temp2->key, key) > 0)
		{
			new_node->sprev = temp2->sprev, new_node->snext = temp2;
			temp2->sprev->snext = new_node, temp2->sprev = new_node;
			return (1);
		}
	}
	new_node->sprev = ht->stail, new_node->snext = NULL;
	ht->stail->snext = new_node, ht->stail = new_node;
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
	shash_node_t *temp;

	if (!ht)
		return;
	temp = ht->shead;
	putchar('{');
	for (; temp; temp = temp->snext)
	{
		printf("'%s': '%s'%s", temp->key, temp->value, temp->snext ? ", " : "");
	}
	putchar('}');
	putchar('\n');
}

/**
 * shash_table_delete - Deletes the sorted hash table
 * @ht: The hash table to be deleted
 *
 * Return: No return
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *temp, *node;

	if (!ht)
		return;
	node = ht->shead;
	while (node)
	{
		temp = node->snext;
		free(node->key);
		free(node->value);
		free(node);
		node = temp;
	}
	free(ht->array);
	free(ht);
}

/**
 * shash_table_print_rev - prints the sorted hash table in reverse
 * @ht: hash table to check
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *temp;

	if (!ht)
		return;
	temp = ht->stail;
	putchar('{');
	for (; temp; temp = temp->sprev)
	{
		printf("'%s': '%s'%s", temp->key, temp->value, temp->sprev ? ", " : "");
	}
	putchar('}');
	putchar('\n');
}
