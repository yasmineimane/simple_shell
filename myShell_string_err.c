#include "shell.h"

/**
 * _eputchar - Writes the character ch to stdrr.
 * @ch: the character to print.
 * Return: On success 1, 0 else.
 */
int _eputchar(char ch)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (ch != BUF_FLUSH)
		buf[j++] = ch;

	return (1);
}

/**
 * _putfd - Writes the character c to given fd.
 * @c: the character to print.
 * @fd: the filr descriptor to write.
 * Return: Ob$n success 1, else 0.
 */

int _putfd(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != Buf_FLUSH)
		buf[j++] = c;

	return (1);
}

/**
 * _eputs - prints an input string.
 * @str: The string to be printed.
 */

void _eputs(char *str)
{
	int j = 0;

	if (!str)
		return;

	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _putsfd - prints an input string.
 * @str: the string to be printed.
 * @fd: the filedescriptor to write to.
 * Return: the number of chars put.
 */

int _putsfd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);

	while (*str)
	{
		j += _putfd(*str++, fd);
	}

	return (i);
}
