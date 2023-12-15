#include "shell.h"

/**
 * ffree - frees a string of strings.
 * @st: string of strigs.
 */

void ffree(char **st)
{
	char **w = st;

	if (!st)
		return;
	while (*st)
		free(*st++);
	free(w);
}

/**
 * bfree - frees a pointer and NULLs the address.
 * @ptr: address of the pointer to be free.
 * Return: On success 1, 0 else.
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * _memset - fills memory with a constant byte.
 * @w: the pointer to the memory area.
 * @a: the byte to fill *w with.
 * @n: the amount of bytes to be filed.
 * Return: (w) a pointer to the memory area w.
 */

char *_memset(char *w, char a, unsigned int n)
{
	unsigned int y;

	for (y = 0 ; y < n ; y++)
		w[y] = a;
	return (w);
}
