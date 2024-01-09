#include "shell.h"

/**
 *_eputs - prints an input string
 * @s: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *s)
{
	int j = 0;

	if (!s)
		return;
	while (s[j] != '\0')
	{
		_eputchar(s[j]);
		j++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char ch)
{
	static int j;
	static char _buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, _buf, j);
		j = 0;
	}
	if (ch != BUF_FLUSH)
		_buf[j++] = ch;
	return (1);
}

/**
 * _putf - writes the character c to given fd
 * @ch: The character to print
 * @f: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putf(char ch, int f)
{
	static int j;
	static char _buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(f, _buf, j);
		j = 0;
	}
	if (ch != BUF_FLUSH)
		_buf[j++] = ch;
	return (1);
}

/**
 *_putsf - prints an input string
 * @s: the string to be printed
 * @f: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsf(char *s, int f)
{
	int j = 0;

	if (!s)
		return (0);
	while (*s)
	{
		j += _putf(*s++, f);
	}
	return (j);
}
