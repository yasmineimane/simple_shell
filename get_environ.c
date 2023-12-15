#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ.
 * @infa: struct contient potentiel arguments.
 * Return: Always 0.
 */

char **get_environ(infa_t *infa)
{
	if (!infa->environ || infa->env_changed)
	{
		infa->environ = list_to strings(infa->env);
		infa->env_changed = 0;
	}

	return (infa->environ);
}

/**
 * _myunsetenv - Remone an environ variable.
 * @infa: struct contient potentiel arguments.
 * Return: Always 0.
 */

int _myunsetenv(infa_t *infa)
{
	int i;

	if (infa->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1 ; i <= infa->argc ; i++)
		_unsetenv(infa, infa->argv[i]);
	return (0);
}

/**
 * _unsetenv - Remove en environ variable.
 * @infa: struct contient potentiel arguments.
 * @var: string env property.
 * Return: 1 on delete, 0 else.
 */

int _unsetenv(infa_t *infa, char *var)
{
	lista_t *node = infa->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);
	while (node)
	{
		p = begin_with(node->str, var);
		if (p && *p == '=')
		{
			infa->env_changed = delete_node_at_index(&(infa->env), i);
			node = infa->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (infa->env_changed);
}

/**
 * populate_env_list - populates env linked list.
 * @infa: struct contient potentiel arguments.
 * Return: Always 0.
 */

int populate_env_list(infa_t *infa)
{
	lista_t *node = NULL;
	size_t i;

	for (i = 0 ; environ[i] ; i++)
		add_node_end(&node, environ[i], 0);
	infa->env = node;
	return (0);
}
