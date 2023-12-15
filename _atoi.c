#include "shell.h"

/**
 * _erratoi - converts a string to an integer.
 * @s: the string to be converted.
 * Return: if no number in string 0, else converted number, -1 if error.
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0 ; s[i] != '\0' ; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
/**
 * _isalpha - checks for alphabetic character.
 * @c: The character to inputt.
 * Return: if c is alphabetic 1, else 0.
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _atoi - converts a string to an integer.
 * @s: the string to be converted.
 * Return: if no numbers in string 0, else converted number.
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0 ; s[i] != '\0' && flag != 2 ; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
/**
 * is_delim - checks if character is a delimeter.
 * @c: the char to check.
 * @delim: the delimeter string.
 * Return: If true 1, else 0.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
