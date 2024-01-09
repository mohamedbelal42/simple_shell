#include "shell.h"

/**
 * adds_node - adds a node to the start of the list
 * @h: address of pointer to head node
 * @s: str field of node
 * @n: node index used by history
 *
 * Return: size of list
 */
list_t *adds_node(list_t **h, const char *s, int n)
{
	list_t *new_h;

	if (!h)
		return (NULL);
	new_h = malloc(sizeof(list_t));
	if (!new_h)
		return (NULL);
	_memset((void *)new_h, 0, sizeof(list_t));
	new_h->n = n;
	if (s)
	{
		new_h->s = _strdup(s);
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
 * adds_node_end - adds a node to the end of the list
 * @h: address of pointer to head node
 * @s: str field of node
 * @n: node index used by history
 *
 * Return: size of list
 */
list_t *adds_node_end(list_t **h, const char *s, int n)
{
	list_t *new_nod, *nod;

	if (!h)
		return (NULL);

	nod = *h;
	new_nod = malloc(sizeof(list_t));
	if (!new_nod)
		return (NULL);
	_memset((void *)new_nod, 0, sizeof(list_t));
	new_nod->n = n;
	if (s)
	{
		new_nod->s = _strdup(s);
		if (!new_nod->s)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->next)
			nod = nod->next;
		nod->next = new_nod;
	}
	else
		*h = new_nod;
	return (new_nod);
}

/**
 * print_list_string - prints only the str element of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_string(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		_puts(head->s ? head->s : "(nil)");
		_puts("\n");
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * delete_node_index - deletes node at given index
 * @h: address of pointer to first node
 * @ind: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_index(list_t **h, unsigned int ind)
{
	list_t *nod, *prev_nod;
	unsigned int j = 0;

	if (!h || !*h)
		return (0);

	if (!ind)
	{
		nod = *h;
		*h = (*h)->next;
		free(nod->s);
		free(nod);
		return (1);
	}
	nod = *h;
	while (nod)
	{
		if (j == ind)
		{
			prev_nod->next = nod->next;
			free(nod->s);
			free(nod);
			return (1);
		}
		j++;
		prev_nod = nod;
		nod = nod->next;
	}
	return (0);
}

/**
 * list_free - frees all nodes of a list
 * @h_p: address of pointer to head node
 *
 * Return: void
 */
void list_free(list_t **h_p)
{
	list_t *nod, *next_nod, *h;

	if (!h_p || !*h_p)
		return;
	h = *h_p;
	nod = h;
	while (nod)
	{
		next_nod = nod->next;
		free(nod->s);
		free(nod);
		nod = next_nod;
	}
	*h_p = NULL;
}
