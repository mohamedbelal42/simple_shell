#include "shell.h"

/**
 * _is_chain - test if current char in buffer is a chain delimeter
 * @x: the parameter struct
 * @_buf: the char buffer
 * @ptr: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int _is_chain(info_t *x, char *_buf, size_t *ptr)
{
	size_t k = *ptr;

	if (_buf[k] == '|' && _buf[k + 1] == '|')
	{
		_buf[k] = 0;
		k++;
		x->cmd_buf_type = CMD_OR;
	}
	else if (_buf[k] == '&' && _buf[k + 1] == '&')
	{
		_buf[k] = 0;
		k++;
		x->cmd_buf_type = CMD_AND;
	}
	else if (_buf[k] == ';') /* found end of this command */
	{
		_buf[k] = 0; /* replace semicolon with null */
		x->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = k;
	return (1);
}

/**
 * _chain_check - checks we should continue chaining based on last status
 * @x: the parameter struct
 * @_buf: the char buffer
 * @ptr: address of current position in buf
 * @j: starting position in buf
 * @l: length of buf
 *
 * Return: Void
 */
void _chain_check(info_t *x, char *_buf, size_t *ptr, size_t j, size_t l)
{
	size_t k = *ptr;

	if (x->cmd_buf_type == CMD_AND)
	{
		if (x->status)
		{
			_buf[j] = 0;
			k = l;
		}
	}
	if (x->cmd_buf_type == CMD_OR)
	{
		if (!x->status)
		{
			_buf[j] = 0;
			k = l;
		}
	}

	*ptr = k;
}

/**
 * _alias_replace - replaces an aliases in the tokenized string
 * @x: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _alias_replace(info_t *x)
{
	int j;
	list_t *node;
	char *ptr;

	for (j = 0; j < 10; j++)
	{
		node = node_start(x->alias, x->argv[0], '=');
		if (!node)
			return (0);
		free(x->argv[0]);
		ptr = string_ch(node->str, '=');
		if (!ptr)
			return (0);
		ptr = string_dup(ptr + 1);
		if (!ptr)
			return (0);
		x->argv[0] = ptr;
	}
	return (1);
}

/**
 * _var_replace - replaces vars in the tokenized string
 * @x: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _var_replace(info_t *x)
{
	int j = 0;
	list_t *node;

	for (j = 0; x->argv[j]; j++)
	{
		if (x->argv[j][0] != '$' || !x->argv[j][1])
			continue;

		if (!string_compare(x->argv[j], "$?"))
		{
			_string_replace(&(x->argv[j]),
				string_dup(convert_num(x->status, 10, 0)));
			continue;
		}
		if (!string_compare(x->argv[j], "$$"))
		{
			_string_replace(&(x->argv[j]),
				string_dup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = node_start(x->env, &x->argv[j][1], '=');
		if (node)
		{
			_string_replace(&(x->argv[j]),
				string_dup(string_ch(node->str, '=') + 1));
			continue;
		}
		_string_replace(&x->argv[j], string_dup(""));

	}
	return (0);
}

/**
 * _string_replace - replaces string
 * @o: address of old string
 * @n: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _string_replace(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
