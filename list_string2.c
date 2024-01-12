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
 * strings_of_list - returns an array of strings of the list->str
 * @h: pointer to first node
 *
 * Return: array of strings
 */
char **strings_of_list(list_t *h)
{
	list_t *node = h;
	size_t j = list_length(h), k;
	char **ss;
	char *s;

	if (!h || !j)
		return (NULL);
	ss = malloc(sizeof(char *) * (j + 1));
	if (!ss)
		return (NULL);
	for (j = 0; node; node = node->next, j++)
	{
		s = malloc(string_length(node->s) + 1);
		if (!s)
		{
			for (k = 0; k < j; k++)
				free(ss[k]);
			free(ss);
			return (NULL);
		}

		s = string_copy(s, node->s);
		ss[j] = s;
	}
	ss[j] = NULL;
	return (ss);
}


/**
 * list_print - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t list_print(list_t *head)
{
	size_t j = 0;

	while (head)
	{
		put_str(convert_num(head->n, 10, 0));
		put_char(':');
		put_char(' ');
		put_str(head->s ? head->s : "(nil)");
		put_str("\n");
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * node_start - returns node whose string starts with prefix
 * @node: pointer to list head
 * @pre: string to match
 * @ch: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_start(list_t *node, char *pre, char ch)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = start_with(node->s, pre);
		if (ptr && ((ch == -1) || (*ptr == ch)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * node_index - gets the index of a node
 * @h: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t node_index(list_t *h, list_t *node)
{
	size_t j = 0;

	while (h)
	{
		if (h == node)
			return (j);
		h = h->next;
		j++;
	}
	return (-1);
}
