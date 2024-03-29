#include "shell.h"

/**
 * _historyy - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @x: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _historyy(info_t *x)
{
	print_list(x->history);
	return (0);
}

/**
 * _unset_alias - sets alias to string
 * @x: parameter struct
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _unset_alias(info_t *x, char *s)
{
	char *ptr, ch;
	int r;

	ptr = string_ch(s, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	r = node_delete(&(x->alias),
		node_index(x->alias, node_start(x->alias, s, -1)));
	*ptr = ch;
	return (r);
}

/**
 * _set_alias - sets alias to string
 * @x: parameter struct
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _set_alias(info_t *x, char *s)
{
	char *ptr;

	ptr = string_ch(s, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (_unset_alias(x, s));

	_unset_alias(x, s);
	return (end_add(&(x->alias), s, 0) == NULL);
}

/**
 * _alias_print - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int _alias_print(list_t *node)
{
	char *ptr = NULL, *b = NULL;

	if (node)
	{
		ptr = string_ch(node->str, '=');
		for (b = node->str; b <= ptr; b++)
			put_char(*b);
		put_char('\'');
		put_str(ptr + 1);
		put_str("'\n");
		return (0);
	}
	return (1);
}

/**
 * _aliasy - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _aliasy(info_t *info)
{
	int j = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_alias_print(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		ptr = string_ch(info->argv[j], '=');
		if (ptr)
			_set_alias(info, info->argv[j]);
		else
			_alias_print(node_start(info->alias, info->argv[j], '='));
	}

	return (0);
}
