#include "shell.h"

/**
 * _strcat - Fuction that concatenates two strings.
 * @dest: The string to be concatenate.
 * @src: The string to be concatenate.
 * Return: On success 1, else 0.
 */

char *_strcat(char *dest, char *src)
{
	char *s;

	s = strcat(dest, src);
	return (s);
}

/**
 * **strtow - splits a string into words.
 * @str: The input string.
 * @d: The delimeter string.
 * Return: A pointer to an array of strings.
 */

char **strtow(char *str, char *d)
{
	int i, j, k, m, words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

	if (!d)
		d = " ";
	for (i = 0 ; str[i] != '\0' ; i++)
	{
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			words++;
	}
	if (words == 0)
		return (NULL);
	s = malloc((1 + words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0 ; j < words ; j++)
	{
		while (is_delim(str[i + k], d) && str[i + k])
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
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = 0;

	return (s);
}

/**
 * _putchar - write the character c to stdout.
 * @c: The character to print.
 * Return: On succes 1, 0 else.
 */

int _putchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * _strchr - Function that locates a character in a string.
 * @c: Parameter to be checked.
 * @s: Parameter to be checked.
 * Return: On success 1, 0 else.
 */

char *_strchr(char *s, char c)
{
	char *res;

	res = strchr(s, c);
	return (res);
}

/**
 * _puts - Function that prints a string.
 * @str: Parameter to be checked.
 * Return: On success 1, 0 else.
 */

void _puts(char *str)
{
	int i;

	for (i = 0 ; str[i] != '\0' ; i++)
		_putchar(str[i]);
	_putchar('\n');
}
