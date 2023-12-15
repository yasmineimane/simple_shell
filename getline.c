#include "shell.h"

/**
 * input_buf - buffers chained command.
 * @infa: struct contient potentiel arguments.
 * @buf: address of buffer.
 * @len: address of length var.
 * Return: bytes read.
 */
ssize_t input_buf(infa_t *infa, char **buf, size_t *len)
{
	ssize_t w = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		w = getline(buf, &len_p, stdin);
#else
		w = _getline(infa, buf, &len_p);
#endif
		if (w > 0)
		{
			if ((*buf)[w - 1] == '\n')
			{
				(*buf)[w - 1] = '\0';
				w--;
			}
			infa->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(infa, *buf, infa->histcount++);
			{
				*len = w;
				infa->cmd_buf = buf;
			}
		}
	}
	return (w);
}

/**
 * read_buf - reads a buffer.
 * @infa: struct contient potentiel arguments.
 * @buf: buffer.
 * @w: size.
 * Return: r.
 */
ssize_t read_buf(infa_t *infa, char *buf, size_t *w)
{
	ssize_t r = 0;

	if (*w)
		return (0);
	r = read(infa->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*w = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN.
 * @infa: struct contient potentiel arguments.
 * @ptr: pointer to buffer.
 * @length: size of preallocated ptr buffer.
 * Return: s.
 */
int _getline(infa_t *infa, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t w;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(infa, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	w = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + w : w + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buf + i, w - i);
	else
		_strncpy(new_p, buf + i, w - i + 1);

	s += w - i;
	i = w;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * get_input - gets a line minus the new line.
 * @infa: struct contient potentiel arguments.
 * Return: bytes read.
 */
ssize_t get_input(infa_t *infa)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(infa->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(infa, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;
		check_chain(infa, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(infa, buf, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			infa->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (_strlen(p));
	}
	*buf_p = buf;
	return (r);
}

/**
 * sigintHandler - blocks ctrl-c.
 * @sig_num: the signal number.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
