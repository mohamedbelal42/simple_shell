#include "shell.h"

/**
 * string_copy - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *string_copy(char *destination, char *source)
{
	int j = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[j])
	{
		destination[j] = source[j];
		j++;
	}
	destination[j] = 0;
	return (destination);
}

/**
 * string_dup - duplicates a string
 * @s: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *string_dup(const char *s)
{
	int len = 0;
	char *r;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	for (len++; len--;)
		r[len] = *--s;
	return (r);
}

/**
 * put_str - prints an input string
 *@s: the string to be printed
 *
 * Return: Nothing
 */
void put_str(char *s)
{
	int j = 0;

	if (!s)
		return;
	while (s[j] != '\0')
	{
		put_char(s[j]);
		j++;
	}
}

/**
 * put_char - writes the character c to stdout
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_char(char ch)
{
	static int j;
	static char _buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, _buf, j);
		j = 0;
	}
	if (ch != BUF_FLUSH)
		_buf[j++] = ch;
	return (1);
}
