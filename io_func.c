#include "shell.h"

/**
 * _get_history - gets the history file
 * @information: parameter struct
 *
 * Return: allocated string containg history file
 */

char *_get_history(info_t *information)
{
	char *_buf, *d;

	d = _getenvy(information, "HOME=");
	if (!d)
		return (NULL);
	_buf = malloc(sizeof(char) *
			(string_length(d) + string_length(HIST_FILE) + 2));
	if (!_buf)
		return (NULL);
	_buf[0] = 0;
	string_copy(_buf, d);
	string_cat(_buf, "/");
	string_cat(_buf, HIST_FILE);
	return (_buf);
}

/**
 * _history_write - creates a file, or appends to an existing file
 * @information: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int _history_write(info_t *information)
{
	ssize_t fd;
	char *f = _get_history(information);
	list_t *node = NULL;

	if (!f)
		return (-1);

	fd = open(f, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f);
	if (fd == -1)
		return (-1);
	for (node = information->history; node; node = node->next)
	{
		puts_fd(node->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * _history_read - reads history from file
 * @information: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int _history_read(info_t *information)
{
	int j, l = 0, c = 0;
	ssize_t fd, readlen, s = 0;
	struct stat st;
	char *_buf = NULL, *f = _get_history(information);

	if (!f)
		return (0);

	fd = open(f, O_RDONLY);
	free(f);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		s = st.st_size;
	if (s < 2)
		return (0);
	_buf = malloc(sizeof(char) * (s + 1));
	if (!_buf)
		return (0);
	readlen = read(fd, _buf, s);
	_buf[s] = 0;
	if (readlen <= 0)
		return (free(_buf), 0);
	close(fd);
	for (j = 0; j < s; j++)
		if (_buf[j] == '\n')
		{
			_buf[j] = 0;
			_history_list(information, _buf + l, c++);
			l = j + 1;
		}
	if (l != j)
		_history_list(information, _buf + l, c++);
	free(_buf);
	information->histcount = c;
	while (information->histcount-- >= HIST_MAX)
		node_delete(&(information->history), 0);
	_history_renumber(information);
	return (information->histcount);
}

/**
 * _history_list - adds entry to a history linked list
 * @information: Structure containing potential arguments. Used to maintain
 * @_buf: buffer
 * @c: the history linecount, histcount
 *
 * Return: Always 0
 */
int _history_list(info_t *information, char *_buf, int c)
{
	list_t *node = NULL;

	if (information->history)
		node = information->history;
	end_add(&node, _buf, c);

	if (!information->history)
		information->history = node;
	return (0);
}

/**
 * _history_renumber - renumbers the history linked list after changes
 * @information: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int _history_renumber(info_t *information)
{
	list_t *node = information->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (information->histcount = j);
}
