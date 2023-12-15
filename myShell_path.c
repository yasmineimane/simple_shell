#include "shell.h"

/**
 * find_path - finds this cmd in the path string.
 * @infa: struct contient potentiel arguments.
 * @pathstr: path string.
 * @cmd: the cmd to find.
 * Return: if found full path of cmd or NULL.
 */
char *find_path(infa_t *infa, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && begin_with(cmd, "./"))
	{
		if (is_cmd(infa, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(infa, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * is_cmd - determines if a file is an executable command.
 * @infa: struct contient potentiel arguments.
 * @path: path to the file.
 * Return: 1 if true, 0 else.
 */
int is_cmd(infa_t *infa, char *path)
{
	struct stat st;

	(void)infa;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * dup_chars - duplicates characters.
 * @pathstr: the path string.
 * @start: starting index.
 * @stop: stoping index.
 * Return: pointer.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start ; i < stop ; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}
