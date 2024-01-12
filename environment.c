#include "shell.h"

/**
 * _envy - prints the current environment
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _envy(info_t *information)
{
	print_strlist(information->env);
	return (0);
}

/**
 * _getenvy - gets the value of an environ variable
 * @information: Structure containing potential arguments. Used to maintain
 * @n: env var name
 *
 * Return: the value
 */
char *_getenvy(info_t *information, const char *n)
{
	list_t *node = information->env;
	char *ptr;

	while (node)
	{
		ptr = start_with(node->str, n);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _setenvy - Initialize a new environment variable,
 *             or modify an existing one
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _setenvy(info_t *information)
{
	if (information->argc != 3)
	{
		put_e("Incorrect number of arguements\n");
		return (1);
	}
	if (_set_env(information, information->argv[1], information->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenvy - Remove an environment variable
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _unsetenvy(info_t *information)
{
	int j;

	if (information->argc == 1)
	{
		put_e("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= information->argc; j++)
		_unset_env(information, information->argv[j]);

	return (0);
}

/**
 * envy_list - populates env linked list
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int envy_list(info_t *information)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		end_add(&node, environ[j], 0);
	information->env = node;
	return (0);
}
