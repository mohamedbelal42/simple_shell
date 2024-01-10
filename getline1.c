#include "shell.h"

/**
 * _in_buf - buffers chained commands
 * @x: parameter struct
 * @_buf: address of buffer
 * @l: address of len var
 *
 * Return: bytes read
 */
ssize_t _in_buf(info_t *x, char **_buf, size_t *l)
{
	ssize_t s = 0;
	size_t lp = 0;

	if (!*l) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*_buf);
		*_buf = NULL;
		signal(SIGINT, signtHand);
#if USE_GETLINE
		s = getline(_buf, &lp, stdin);
#else
		s = _get_line(x, _buf, &lp);
#endif
		if (s > 0)
		{
			if ((*_buf)[s - 1] == '\n')
			{
				(*_buf)[s - 1] = '\0'; /* remove trailing newline */
				s--;
			}
			x->linecount_flag = 1;
			comments_remove(*_buf);
			_history_list(x, *_buf, x->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*l = s;
				x->cmd_buf = _buf;
			}
		}
	}
	return (s);
}

/**
 * _get_in - gets a line minus the newline
 * @x: parameter struct
 *
 * Return: bytes read
 */
ssize_t _get_in(info_t *x)
{
	static char *_buf; /* the ';' command chain buffer */
	static size_t j, k, l;
	ssize_t s = 0;
	char **buf_p = &(x->arg), *ptr;

	put_char(BUF_FLUSH);
	s = input_buf(x, &_buf, &l);
	if (s == -1) /* EOF */
		return (-1);
	if (l)	/* we have commands left in the chain buffer */
	{
		k = j; /* init new iterator to current buf position */
		ptr = _buf + j; /* get pointer for return */

		_chain_check(x, _buf, &k, j, l);
		while (k < l) /* iterate to semicolon or end */
		{
			if (_is_chain(x, _buf, &k))
				break;
			k++;
		}

		j = k + 1; /* increment past nulled ';'' */
		if (j >= l) /* reached end of buffer? */
		{
			j = l = 0; /* reset position and length */
			x->cmd_buf_type = CMD_NORM;
		}

		*buf_p = ptr; /* pass back pointer to current command position */
		return (string_length(ptr)); /* return length of current command */
	}

	*buf_p = _buf; /* else not a chain, pass back buffer from _getline() */
	return (s); /* return length of buffer from _getline() */
}

/**
 * _buf_read - reads a buffer
 * @x: parameter struct
 * @_buf: buffer
 * @j: size
 *
 * Return: r
 */
ssize_t _buf_read(info_t *x, char *_buf, size_t *j)
{
	ssize_t s = 0;

	if (*j)
		return (0);
	s = read(x->readfd, _buf, READ_BUF_SIZE);
	if (s >= 0)
		*j = s;
	return (s);
}

/**
 * _get_line - gets the next line of input from STDIN
 * @x: parameter struct
 * @p: address of pointer to buffer, preallocated or NULL
 * @l: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _get_line(info_t *x, char **p, size_t *l)
{
	static char _buf[READ_BUF_SIZE];
	static size_t j, len;
	size_t m;
	ssize_t s = 0, str = 0;
	char *ptr = NULL, *np = NULL, *ch;

	ptr = *p;
	if (ptr && l)
		str = *l;
	if (j == len)
		j = len = 0;

	s = _buf_read(x, _buf, &len);
	if (s == -1 || (s == 0 && len == 0))
		return (-1);

	ch = string_ch(_buf + j, '\n');
	m = ch ? 1 + (unsigned int)(ch - _buf) : len;
	np = real_loc(ptr, str, str ? str + m : m + 1);
	if (!np) /* MALLOC FAILURE! */
		return (ptr ? free(ptr), -1 : -1);

	if (str)
		str_cat(np, _buf + j, m - j);
	else
		str_copy(np, _buf + j, m - j + 1);

	str += m - j;
	j = m;
	ptr = np;

	if (l)
		*l = str;
	*p = ptr;
	return (str);
}

/**
 * signtHand - blocks ctrl-C
 * @num: the signal number
 *
 * Return: void
 */
void signtHand(__attribute__((unused))int num)
{
	put_str("\n");
	put_str("$ ");
	put_char(BUF_FLUSH);
}
