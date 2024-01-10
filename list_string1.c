#include "shell.h"

/**
 * node_add - adds a node to the start of the list
 * @h: address of pointer to head node
 * @s: str field of node
 * @n: node index used by history
 *
 * Return: size of list
 */
list_t *node_add(list_t **h, const char *s, int n)
{
	list_t *new_h;

	if (!h)
		return (NULL);
	new_h = malloc(sizeof(list_t));
	if (!new_h)
		return (NULL);
	memory_set((void *)new_h, 0, sizeof(list_t));
	new_h->n = n;
	if (s)
	{
		new_h->s = string_dup(s);
		if (!new_h->s)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *h;
	*h = new_h;
	return (new_h);
}

/**
 * end_add - adds a node to the end of the list
 * @h: address of pointer to head node
 * @s: str field of node
 * @n: node index used by history
 *
 * Return: size of list
 */
list_t *end_add(list_t **h, const char *s, int n)
{
	list_t *new_node, *node;

	if (!h)
		return (NULL);

	node = *h;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	memory_set((void *)new_node, 0, sizeof(list_t));
	new_node->n = n;
	if (s)
	{
		new_node->s = string_dup(s);
		if (!new_node->s)
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
		*h = new_node;
	return (new_node);
}

/**
 * print_strlist - prints only the str element of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_strlist(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		put_str(head->s ? head->s : "(nil)");
		put_str("\n");
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * node_delete - deletes node at given index
 * @h: address of pointer to first node
 * @i: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int node_delete(list_t **h, unsigned int i)
{
	list_t *node, *prev_node;
	unsigned int j = 0;

	if (!h || !*h)
		return (0);

	if (!i)
	{
		node = *h;
		*h = (*h)->next;
		free(node->s);
		free(node);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (j == i)
		{
			prev_node->next = node->next;
			free(node->s);
			free(node);
			return (1);
		}
		j++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * list_free - frees all nodes of a list
 * @p: address of pointer to head node
 *
 * Return: void
 */
void list_free(list_t **p)
{
	list_t *node, *next_node, *h;

	if (!p || !*p)
		return;
	h = *p;
	node = h;
	while (node)
	{
		next_node = node->next;
		free(node->s);
		free(node);
		node = next_node;
	}
	*p = NULL;
}
