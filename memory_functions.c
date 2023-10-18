#include "shell.h"

/**
 * _memset - Fills memory with a constant byte.
 * @s: A pointer to the memory area.
 * @b: The byte to fill *s with.
 * @n: The number of bytes to be filled.
 *
 * Return: A pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = b;
	}
	return (s);
}

/**
 * ffree - Frees a string of strings.
 * @pp: A string of strings to free.
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
	{
		return;
	}
	while (*pp)
	{
		free(*pp);
		pp++;
	}
	free(a);
}

/**
 * _realloc - Reallocates a block of memory.
 * @ptr: A pointer to the previous malloc'ated block.
 * @old_size: The byte size of the previous block.
 * @new_size: The byte size of the new block.
 *
 * Return: A pointer to the old block if realloc fails; otherwise, a pointer to the new block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;
	unsigned int i;

	if (!ptr)
	{
		return (malloc(new_size));
	}
	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
	{
		return (ptr);
	}

	p = malloc(new_size);
	if (!p)
	{
		return (NULL);
	}

	for (i = 0; i < old_size && i < new_size; i++)
	{
		p[i] = ((char *)ptr)[i];
	}
	free(ptr);
	return (p);
}

