#include "shell.h"

/**
 * hsh - main shell loop.
 * @infa: struct contient potentiel arguments.
 * @av: the arguments vector.
 * Return: On cuccess 0, else 1.
 */
int hsh(infa_t *infa, char **av)
{
	ssize_t w = 0;
	int builtin_ret = 0;

	while (w != -1 && builtin_ret != -2)
	{
		clear_info(infa);
		if (interactive(infa))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		w = get_input(infa);
		if (w != -1)
		{
			set_info(infa, av);
			builtin_ret = find_builtin(infa);
			if (builtin_ret == -1)
				find_cmd(infa);
		}
		else if (interactive(infa))
			_putchar('\n');
		free_info(infa, 0);
	}
	write_history(infa);
	free_info(infa, 1);
	if (!interactive(infa) && infa->status)
		exit(infa->status);
	if (builtin_ret == -2)
	{
		if (infa->err_num == -1)
			exit(infa->status);
		exit(infa->err_num);
	}
	return (builtin_ret);
}
