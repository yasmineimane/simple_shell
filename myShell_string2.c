#include "shell.h"

/**
 * _strncat - Finction that concatenates two strings.
 * @dest: The string to be concatenate.
 * @src: The string to be concatenate.
 * @n: The size of the string.
 * Return: On success 1, 0 else.
 */

char *_strncat(char *dest, char *src, int n)
{
	char *s;

	s = strncat(dest, src, n);
	return (s);
}

/**
 * _strncpy - Function that copies a string.
 * @dest: The string to be copy.
 * @src: The sting to be copy.
 * @n: The size of the string.
 * Return: On succes 1, 0 else.
 */

char *_strncpy(char *dest, char *src, int n)
{
	char *s;

	s = strncpy(dest, src, n);
	return (s);
}

/**
 * **strtow2 - splits a string into words.
 * @str: The input string.
 * @d: The delimeter.
 * Return: A pointer.
 */

char **strtow2(char *str, char d)
{
	int i, j, k, m, words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0 ; str[i] != '\0' ; i++)
	{
		if ((str[i] != d && str[i + 1] == d) ||
			(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			words++;
	}
	if (words == 0)
		return (NULL);
	s = malloc((1 + words) * sizeof(char *));
	if (!s)
		return (NULL);

	for (i = 0 ; j = 0 ; j < words ; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0 ; k < j ; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0 ; m < k ; m++)
		{
			s[j][m] = str[i++];
		}
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
