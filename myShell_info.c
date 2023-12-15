#include "shell.h"

/**
 * set_info - intializes infa_t struct.
 * @infa: struct contient potentiel arguments.
 * @av: argument vector.
 */

void set_info(infa_t *infa, char **av)
{
	int i = 0;

	infa->fname = av[0];
	if (infa->arg)
	{
		infa->argv = strtow(infa->arg, " \t");
		if (!infa->argv)
		{
			infa->argv = malloc(sizeof(char *) * 2);
			if (infa->argv)
			{
				infa->argv[0] = _strdup(infa->arg);
				infa->argv[1] = NULL;
			}
		}
		for (i = 0 ; infa->argv && infa->argv[i] ; i++)
			;
		infa->argc = i;
		replace_alias(infa);
		replace_vars(infa);
	}
}

/**
 * print_error - prints an error message.
 * @infa: struct contient potentiel arguments.
 * @estr: string.
 * Return: 0 if no numbers in string, 1 else.
 */
void print_error(infa_t *infa, char *estr)
{
	_eputs(infa->fname);
	_eputs(": ");
	print_d(infa->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(infa->argv[0]);
	_eputs(": ");
	_eputs(estr);
}
/**
 * free_info - free infa_t struct fields.
 * @infa: struct contient potentoniel arguments.
 * @all: true if freeing all fields.
 */
void free_info(infa_t *infa, int all)
{
	ffree(infa->argv);
	infa->argv = NULL;
	infa->path = NULL;
	if (all)
	{
		if (!infa->cmd_buf)
			free(infa->arg);
		if (infa->env)
			free_list(&(infa->env));
		if (infa->history)
			free_list(&(infa->history));
		if (infa->alias)
			free_list(&(infa->alias));
		ffree(infa->environ);
			infa->environ = NULL;
		bfree((void **)infa->cmd_buf);
		if (infa->readfd > 2)
			close(infa->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * clear_info - intialqies infa_t struct.
 * @infa: struct contient potentiel argument.
 */
void clear_info(infa_t *infa)
{
	infa->arg = NULL;
	infa->argv = NULL;
	infa->path = NULL;
	infa->argc = 0;
}
