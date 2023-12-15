#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode.
 * @infa: struct contient potentiel arguments.
 * Return: 1 if interactive mode, 0 else.
 */
int interactive(infa_t *infa)
{
	return (isatty(STDIN_FILENO) && infa->readfd <= 2);
}
/**
 * print_d - prints a decimal number.
 * @input: the input.
 * @fd: the file descriptor to write to.
 * Return: number of character printed.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000 ; i > 1 ; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;
	return (count);
}
/**
 * remove_comments - replaces the first instance of '#' with '\0'.
 * @buf: adress of the string to be modified.
 * Return: Always 0.
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0 ; buf[i] != '\0' ; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
/**
 * convert_number - converter function.
 * @num: number.
 * @base: base.
 * @flags: argument flag.
 * Return: string.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *arr;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = arr[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}
