#include "shell.h"

/**
 * get_env - returns the string array copy of our environ
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_env(info_t *information)
{
	if (!information->environ || information->env_changed)
	{
		information->environ = strings_of_list(information->env);
		information->env_changed = 0;
	}

	return (information->environ);
}

/**
 * _unset_env - Remove an environment variable
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @v: the string env var property
 */
int _unset_env(info_t *information, char *v)
{
	list_t *node = information->env;
	size_t j = 0;
	char *ptr;

	if (!node || !v)
		return (0);

	while (node)
	{
		ptr = start_with(node->str, v);
		if (ptr && *ptr == '=')
		{
			information->env_changed = node_delete(&(information->env), j);
			j = 0;
			node = information->env;
			continue;
		}
		node = node->next;
		j++;
	}
	return (information->env_changed);
}

/**
 * _set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @v: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int _set_env(info_t *information, char *v, char *val)
{
	char *_buf = NULL;
	list_t *node;
	char *ptr;

	if (!v || !val)
		return (0);

	_buf = malloc(string_length(v) + string_length(val) + 2);
	if (!_buf)
		return (1);
	string_copy(_buf, v);
	string_cat(_buf, "=");
	string_cat(_buf, val);
	node = information->env;
	while (node)
	{
		ptr = start_with(node->str, v);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = _buf;
			information->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	end_add(&(information->env), _buf, 0);
	free(_buf);
	information->env_changed = 1;
	return (0);
}
