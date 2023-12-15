#include "shell.h"

/**
 * _myhistory - displays the history list.
 * @infa: struct contient potentiel arguments.
 * Return: Always 0.
 */

int _myhistory(infa_t *infa)
{
	print_list(infa->history);
	return (0);
}

/**
 * _mycd - Changes the current directory of the process.
 * @infa: struct contient potentiel arguments.
 * Return: Always 0.
 */

int _mycd(infa_t *infa)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here <<\n");
	if (!infa->argv[1])
	{
		dir = _getenv(infa, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(infa, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(infa->argv[1], "-") == 0)
	{
		if (!_getenv(infa, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(infa, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _getenv(infa, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(infa->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(infa, "can't cd to");
		_eputs(infa->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(infa, "OLDPWD", _getenv(infa, "PWD="));
		_setenv(infa, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myexit - exit the shell.
 * @infa: struct contient potentiel arguments.
 * Return: 0
 */

int _myexit(infa_t *infa)
{
	int checkexit;

	if (infa->argv[1])
	{
		checkexit = _erratoi(infa->argv[1]);
		if (checkexit == -1)
		{
			infa->status = 2;
			print_error(infa, "Illegal number : ");
			_eputs(infa->argv[1]);
			_eputchar('\n');
			return (1);
		}
		infa->err_num = _erratoi(infa->argv[1]);
		return (-2);
	}
	infa->err_num = -1;
	return (-2);
}
