#include "shell.h"

/**
 * _interactive - returns true if shell is interactive mode
 * @information: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int _interactive(info_t *information)
{
	return (isatty(STDIN_FILENO) && information->readfd <= 2);
}

/**
 * is_delimeter - checks if character is a delimeter
 * @ch: the char to check
 * @del: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimeter(char ch, char *del)
{
	while (*del)
		if (*del++ == ch)
			return (1);
	return (0);
}

/**
 *is_alphabet - checks for alphabetic character
 *@ch: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int is_alphabet(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *strtoi - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int strtoi(char *str)
{
	int j, s = 1, f = 0, o;
	unsigned int r = 0;

	for (j = 0;  str[j] != '\0' && f != 2; j++)
	{
		if (str[j] == '-')
			s *= -1;

		if (str[j] >= '0' && str[j] <= '9')
		{
			f = 1;
			r *= 10;
			r += (str[j] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (s == -1)
		o = -r;
	else
		o = r;

	return (o);
}
