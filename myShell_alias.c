#include "shell.h"

/**
 * replace_alias - replaces an alias in the tokenized string.
 * @infa: struct contient potentiel arguments.
 * Return: 1if replaced, 0 else.
 */
int replace_alias(infa_t *infa)
{
	int i;
	lista_t *node;
	char *p;

	for (i = 0 ; i < 10 ; i++)
	{
		node = node_begin_with(infa->alias, infa->argv[0], '=');
		if (!node)
			return (0);
		free(infa->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		infa->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized.
 * @infa: struct contient potentiel arguments.
 * Return: 1 if replaced, 0 else.
 */
int replace_vars(infa_t *infa)
{
	int i = 0;
	lista_t *node;

	for (i = 0 ; infa->argv[i] ; i++)
	{
		if (infa->argv[i][0] != '$' || !infa->argv[i][1])
			continue;
		if (!_strcmp(infa->argv[i], "$?"))
		{
			replace_string(&(infa->argv[i]),
					_strdup(convert_number(infa->status, 10, 0)));
			continue;
		}
		if (!_strcmp(infa->argv[i], "$$"))
		{
			replace_string(&(infa->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_begin_with(infa->env, &infa->argv[i][1], ')');
		if (nod)
		{
			replace_string(&(infa->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&infa->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * check_chain - checks chain.
 * @infa: struct contient potentiel arguments.
 * @buf: the char buffer.
 * @p: address of current position in buf.
 * @i: starting position in buf.
 * @len: length of buf.
 */
void check_chain(infa_t *infa, char *buf, size_t *p, size_t i, size_t len)
{
	size_t w = *p;

	if (infa->cmd_buf_type == CMD_AND)
	{
		if (infa->status)
		{
			buf[i] = 0;
			w = len;
		}
	}
	*p = w;
}

/**
 * replace_string - replaces a string.
 * @old: address of old string.
 * @new: new string.
 * Return: 1 if replaced, 0 else.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * is_chain - test if current char in buffer is a chain.
 * @infa: struct contient potentiel arguments.
 * @buf: the char buffer.
 * @p: adress of current position in buf.
 * Return: 1 if chain delimeter, 0 else.
 */
int is_chain(infa_t *infa, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		infa->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		infa->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		infa->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}
