#include "shell.h"

/**
 * _strlen - Function that return the length of a string.
 * @s: parameter to be checked.
 * Return: On success 1.
 * On error, -1 is returned, and errno appropriately.
 */

int _strlen(char *s)
{
	int L;

	L = strlen(s);
	return (L);
}

/**
 * _strcpy - Fuction that copies the string pointed.
 * @dest: The string to print.
 * @src: The string to be copied.
 * Return: On success 1, else 0.
 */

char *_strcpy(char *dest, char *src)
{
	char *s;

	s = strcpy(dest, src);
	return (s);
}

/**
 * _strcmp - Function that compares two strings.
 * @s1: The string to be compare.
 * @s2: The string to be compare.
 * Return: On success 1, 0 else.
 */

int _strcmp(char *s1, char *s2)
{
	int n;

	n = strcmp(s1, s2);
	return (n);
}

/**
 * _strdup - Funstion that duplicates string.
 * @str: The string to be duplicate.
 * Return: Pointer to the duplicate string.
 */

char *_strdup(const char *str)
{
	int L = 0;
	char *r;

	if (str == NULL)
		return (NULL);

	while (*str++)
		L++;
	r = malloc(sizeof(char) * (L + 1));
	if (!r)
		return (NULL);
	for (L++; L--;)
		r[L] = *--str;
	return (r);
}

/**
 * begin_with - cheeks if needle begins with haystack.
 * @haystack: string to search.
 * @needle: The substring to find.
 * Return: address of next char of haystack or NULL.
 */

char *begin_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
