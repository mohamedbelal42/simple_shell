#include "shell.h"

/**
 * put_e - prints an input string
 * @s: the string to be printed
 *
 * Return: Nothing
 */
void put_e(char *s)
{
	int j = 0;

	if (!s)
		return;
	while (s[j] != '\0')
	{
		put_echar(s[j]);
		j++;
	}
}

/**
 * put_echar - writes the character c to stderr
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_echar(char ch)
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
 * put_fd - writes the character c to given fd
 * @ch: The character to print
 * @f: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_fd(char ch, int f)
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
 * puts_fd - prints an input string
 * @s: the string to be printed
 * @f: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int puts_fd(char *s, int f)
{
	int j = 0;

	if (!s)
		return (0);
	while (*s)
	{
		j += put_fd(*s++, f);
	}
	return (j);
}
