#include "shell.h"

/**
 * get_history_file - gets the history file.
 * @infa: struct contient potentiel arguments.
 * Return: allocated string containing history file.
 */
char *get_history_file(infa_t *infa)
{
	char *buf, *dir;

	dir = _getenv(infa, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * renumber_history - renumbers the history linked list after changes.
 * @infa: struct contient potentiel arguments.
 * Return: the new histcount.
 */
int renumber_history(infa_t *infa)
{
	lista_t *node = infa->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (infa->histcount = i);
}

/**
 * build_history_list - adds entry to a history linked list.
 * @infa: struct contient potentiel arguments.
 * @buf: buffer.
 * @linecount: the history linecount, history.
 * Return: Always 0.
 */
int build_history_list(infa_t *infa, char *buf, int linecount)
{
	lista_t *node = NULL;

	if (infa->history)
		node = infa->history;
	add_node_end(&node, buf, linecount);
	if (!infa->history)
		infa->history = node;
	return (0);
}

/**
 * read_history - reads history from file.
 * @infa: struct contient potentiel arguments.
 * Return: histcount on success, 0 else.
 */
int read_history(infa_t *infa)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(infa);

	if (!filename)
		return (0);
	fd = open(filenamen 0_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0 ; i < fsize ; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(infa, buf + last, linecount++);
			last = i + 1;
		}
	}
	if (last != i)
		build_history_list(infa, buf + last, linecount++);
	free(buf);
	infa->histcount = linecount;
	while (infa->histcount-- >= HIST_MAX)
		delete_node_at_index(&(infa->history), 0);
	renumber_history(infa);
	return (infa->histcount);
}

/**
 * write_history - creates a file.
 * @infa: struct contient potentiel arguments.
 * Return: 1on success, -1 else.
 */
int write_history(infa_t *infa)
{
	ssize_t fd;
	char *filename = get_history_file(infa);
	lista_t *node = NULL;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREATE | 0_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = infa->history ; node ; node  = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
