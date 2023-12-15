#include "shell.h"

/**
 * print_list - prints all the elements of a lista_t list.
 * @h: list to be printed.
 * Return: number of nodes.
 */

size_t print_list(const lista_t *h)
{
	size_t nodes = 0;

	while (h != NULL)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		nodes++;
	}

	return (nodes);
}

/**
 * add_node - adds a new node at the begining of a lista_t list.
 * @head: pointer to the first element of the list.
 * @str: string.
 * @num: node index used by history.
 * Return: new list.
 */

lista_t *add_node(lista_t **head, const char *str, int num)
{
	lista_t *new_node;

	if (head == NULL)
		return (NULL);
	new_node = malloc(sizeof(lista_t));
	if (new_node == NULL)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(lista_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

/**
 * get_node_index - gets the index of a node.
 * @head: pointer to the first element of a list.
 * @node: pointer to the node.
 * Return: index of a node or -1.
 */

ssize_t get_node_index(lista_t *head, lista_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}

/**
 * add_node_end - adds a node to the end of the list.
 * @head: address of pointer to head node.
 * @str: str fieled of node.
 * @num: node index used by history.
 * Return: now list.
 */

lista_t *add_node_end(lista_t **head, const char *str, int num)
{
	lista_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(lista_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(lista_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * node_begin_with - returns node whose string bregin with prefix.
 * @node: pointer to list head.
 * @prefix: string to match.
 * @c: the next character after prefix.
 * Return: match node or NULL.
 */

lista_t *node_begin_with(lista_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = begin_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
