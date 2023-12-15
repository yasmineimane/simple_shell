#include "shell.h"

/**
 * _myhelp - Changes the current directory to the process.
 * @infa: struct contient potentiel arguments.
 * Return: Always 0.
 */

int _myhelp(infa_t *infa)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

/**
 * unset_alias - sets alias to string.
 * @infa: struct contient potentiel arguments.
 * @str: string.
 * Return: On success 0, else 1.
 */
int unset_alias(infa_t *infa, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(infa->alias),
			get_node_index(infa->alias, node_begin_with(infa->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string.
 * @infa: struct contient potentiel arguments.
 * @str: string.
 * Return: On success 0, else 1.
 */
int set_alias(infa_t *infa, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++p)
		return (unset_alias(infa, str));

	unset_alias(infa, str);
	return (add_node_end(&(infa->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string.
 * @node: the alias node.
 * Return: On success 0, else 1.
 */
int print_alias(lisat_t *node)
{
	char *ptr = NULL, *w = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (w = node->str ; w <= ptr ; w++)
			_putchar(*w);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin.
 * @infa: struct contient potentiel arguments.
 * Return: Always 0.
 */

int _myalias(infa_t *infa)
{
	int i = 0;
	char *ptr;
	lista_t *node = NULL;

	if (infa->argc == 1)
	{
		node = infa->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1 ; infa->argv[i] ; i++)
	{
		ptr = _strchr(infa->argv[i], '=');
		if (ptr)
			set_alias(infa->argv[i]);
		else
			print_alias(node_begin_with(infa->alias, infa->argv[i], '='));
	}
	return (0);
}
