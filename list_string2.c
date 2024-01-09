#include "shell.h"

/**
 * list_length - determines length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t list_length(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * list_strings - returns an array of strings of the list->str
 * @h: pointer to first node
 *
 * Return: array of strings
 */
char **list_strings(list_t *h)
{
	list_t *nod = h;
	size_t j = list_length(h), k;
	char **ss;
	char *s;

	if (!h || !j)
		return (NULL);
	ss = malloc(sizeof(char *) * (j + 1));
	if (!ss)
		return (NULL);
	for (j = 0; nod; nod = nod->next, j++)
	{
		s = malloc(_strlength(nod->s) + 1);
		if (!s)
		{
			for (k = 0; k < j; k++)
				free(ss[k]);
			free(ss);
			return (NULL);
		}

		s = _strcopy(s, nod->s);
		ss[j] = s;
	}
	ss[j] = NULL;
	return (ss);
}


/**
 * print__list - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print__list(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		_puts(convert_number(head->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->s ? head->s : "(nil)");
		_puts("\n");
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * node_startswith - returns node whose string starts with prefix
 * @nod: pointer to list head
 * @pref: string to match
 * @ch: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_startswith(list_t *nod, char *pref, char ch)
{
	char *ptr = NULL;

	while (nod)
	{
		ptr = starts_with(nod->s, pref);
		if (ptr && ((ch == -1) || (*ptr == ch)))
			return (nod);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * get_node_ind - gets the index of a node
 * @h: pointer to list head
 * @nod: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_ind(list_t *h, list_t *nod)
{
	size_t j = 0;

	while (h)
	{
		if (h == nod)
			return (j);
		h = h->next;
		j++;
	}
	return (-1);
}
