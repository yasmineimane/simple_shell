#include "shell.h"

/**
 * find_cmd - finds a command in path.
 * @infa: struct contient potentiel arguments.
 */
void find_cmd(infa_t *infa)
{
	char *path = NULL;
	int i, w;

	infa->path = infa->argv[0];
	if (infa->linecount_flag == 1)
	{
		infa->line_count++;
		infa->linecount_flag = 0;
	}
	for (i = 0, w = 0 ; infa->arg[i] ; i++)
		if (!is_delim(infa->arg[i], "\t\n"))
			w++;
	if (!w)
		return;
	path = find_path(infa, _getenv(infa, "PATH="), infa->argv[0]);
	if (path)
	{
		infa->path = path;
		fork_cmd(infa);
	}
	else
	{
		if ((interactive(infa) || _getenv(infa, "PATH=")
					|| infa->argv[0][0] == '/') && is_cmd(infa, infa->argv[0]))
			fork_cmd(infa);
		else if (*(infa->arg) != '\n')
		{
			infa->status = 127;
			print_error(infa, "not found\n");
		}
	}
}
/**
 * find_builtin - finds a builtin command.
 * @infa: struct contient potentiel arguments.
 * Return: -1.
 */
int find_builtin(infa_t *infa)
{
	int i, builtin_ret = -1;
	builtin_tab builtintb[] = {
		{"ec=xit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0 ; builtintb[i].type ; i++)
		if (_strcmp(infa->argv[0], builtintb[i].type) == 0)
		{
			infa->line_count++;
			builtin_ret = builtintb[i].func(infa);
			break;
		}
	return (builtin_ret);
}

/**
 * fork_cmd - forks an exec thread to run cmd.
 * @infa: struct contient potentiel arguments.
 */
void fork_cmd(infa_t *infa)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infa->path, infa->argv, get_environ(infa)) == -1)
		{
			free_info(infa, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(infa->status));
		if (WIFEXITED(infa->status))
		{
			infa->status = WEXITSTATUS(infa->status);
			if (infa->status == 126)
				print_error(infa, "Permission denied\n");
		}
	}
}
