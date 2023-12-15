#include "shell.h"

/**
 * list_len - returns an array of strings.
 * @h: pointer to the first element.
 * Return: array of strings.
 */

size_t list_len(lista_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * print_list_str - prints only the str element of a list.
 * @h: pointer to the first element.
 * Return: number of nodes.
 */

size_t print_list_str(const lista_t *h)
{
	size_t nodes = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		nodes++;
	}
	return (nodes);
}

/**
 * free_list - frees a lista_t list.
 * @head: list.
 */

void free_list(lista_t **head)
{
	lista_t *temp;

	if (!head || !*head)
		return;

	while ((*head)->next != NULL)
	{
		temp = (*head)->next;
		free((*head)->str);
		free(*head);
		*head = temp;
	}
	free((*head)->str);
	free(*head);
}

/**
 * list_to_strings - returns an array of strings.
 * @head: pointer to the first element.
 * Return: array of strings.
 */

char **list_to_strings(lista_t *head)
{
	lista_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0 ; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0 ; j < i ; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * delete_node_at_index - deletes node at given index.
 * @head: pointer to the first element.
 * @index: index of the node to be delete.
 * Return: On success 1, 0 else.
 */

int delete_node_at_index(lista_t **head, unsigned int index)
{
	lista_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}
