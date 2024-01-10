#include "shell.h"

/**
 * _is_cmd - determines if a file is an executable command
 * @x: the info struct
 * @p: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int _is_cmd(info_t *x, char *p)
{
	struct stat st;

	(void)x;
	if (!p || stat(p, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _dup_ch - duplicates characters
 * @p: the PATH string
 * @start: starting index
 * @end: stopping index
 *
 * Return: pointer to new buffer
 */
char *_dup_ch(char *p, int start, int end)
{
	static char _buf[1024];
	int j = 0, l = 0;

	for (l = 0, j = start; j < end; j++)
		if (p[j] != ':')
			_buf[l++] = p[j];
	_buf[l] = 0;
	return (_buf);
}

/**
 * _get_path - finds this cmd in the PATH string
 * @x: the info struct
 * @p: the PATH string
 * @c: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *_get_path(info_t *x, char *p, char *c)
{
	int j = 0, current = 0;
	char *pa;

	if (!p)
		return (NULL);
	if ((string_length(c) > 2) && start_with(c, "./"))
	{
		if (_is_cmd(x, c))
			return (c);
	}
	while (1)
	{
		if (!p[j] || p[j] == ':')
		{
			pa = _dup_ch(p, current, j);
			if (!*pa)
				string_cat(pa, c);
			else
			{
				string_cat(pa, "/");
				string_cat(pa, c);
			}
			if (_is_cmd(x, pa))
				return (pa);
			if (!p[j])
				break;
			current = j;
		}
		j++;
	}
	return (NULL);
}
