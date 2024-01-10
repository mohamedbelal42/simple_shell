#include "shell.h"

/**
 * clear_information - initializes info_t struct
 * @information: struct address
 */
void clear_information(info_t *information)
{
	information->arg = NULL;
	information->argv = NULL;
	information->path = NULL;
	information->argc = 0;
}

/**
 * set_information - initializes info_t struct
 * @information: struct address
 * @_av: argument vector
 */
void set_information(info_t *information, char **_av)
{
	int j = 0;

	information->fname = _av[0];
	if (information->arg)
	{
		information->argv = string_tow(information->arg, " \t");
		if (!information->argv)
		{

			information->argv = malloc(sizeof(char *) * 2);
			if (information->argv)
			{
				information->argv[0] = string_dup(information->arg);
				information->argv[1] = NULL;
			}
		}
		for (j = 0; information->argv && information->argv[j]; j++)
			;
		information->argc = j;

		_alias_replace(information);
		_var_replace(information);
	}
}

/**
 * free_information - frees info_t struct fields
 * @information: struct address
 * @a: true if freeing all fields
 */
void free_information(info_t *information, int a)
{
	str_free(information->argv);
	information->argv = NULL;
	information->path = NULL;
	if (a)
	{
		if (!information->cmd_buf)
			free(information->arg);
		if (information->env)
			list_free(&(information->env));
		if (information->history)
			list_free(&(information->history));
		if (information->alias)
			list_free(&(information->alias));
		str_free(information->environ);
			information->environ = NULL;
		_free((void **)information->cmd_buf);
		if (information->readfd > 2)
			close(information->readfd);
		put_char(BUF_FLUSH);
	}
}
