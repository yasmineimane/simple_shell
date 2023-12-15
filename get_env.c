#include "shell.h"

/**
 * _getenv - gets the value of an environ variable.
 * @infa: struct contient potentiel arguments.
 * @name: env var name.
 * Return: the value.
 */

char *_getenv(infa_t *infa, const char *name)
{
	lista_t *node = infa->env;
	char *ptr;

	while (node)
	{
		ptr = begin_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable.
 * @infa: struct contient potentiel arguments.
 * Return: Always 0.
 */

int _mysetenv(infa_t *infa)
{
	if (infa->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(infa, infa->argv[1], infa->argv[2]))
		return (0);
	return (1);
}

/**
 * _setenv - Intialize or modifie an environment variable.
 * @infa: struct contient potentiel arguments.
 * @var: the string env var property.
 * @value: the string env var value.
 * Return: Always 0.
 */

int _setenv(infa_t *infa, char *var, char *value)
{
	char *buf = NULL;
	lista_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = infa->env;
	while (node)
	{
		p = begin_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			infa->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(infa->env), buf, 0);
	free(buf);
	infa->env_changed = 1;
	return (0);
}

/**
 * _myenv - prints the current environment.
 * @infa: struct contient potentiel arguments.
 * Return: Always 0.
 */

int _myenv(infa_t *infa)
{

	print_list_str(infa->env);
	return (0);
}
