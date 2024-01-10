#include "shell.h"

/**
 * _stoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _stoi(char *str)
{
	int j = 0;
	unsigned long int r = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	for (j = 0;  str[j] != '\0'; j++)
	{
		if (str[j] >= '0' && str[j] <= '9')
		{
			r *= 10;
			r += (str[j] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (r);
}

/**
 * print_err - prints an error message
 * @information: the parameter & return info struct
 * @s: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_err(info_t *information, char *s)
{
	_eputs(information->fname);
	_eputs(": ");
	print_dec(information->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(information->argv[0]);
	_eputs(": ");
	_eputs(s);
}

/**
 * print_dec - function prints a decimal (integer) number (base 10)
 * @i: the input
 * @f: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_dec(int i, int f)
{
	int (*_put_char)(char) = put_char;
	int j, c = 0;
	unsigned int a, n;

	if (f == STDERR_FILENO)
		_put_char = _eputchar;
	if (i < 0)
	{
		a = -i;
		_put_char('-');
		c++;
	}
	else
		a = i;
	n = a;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (a / j)
		{
			_put_char('0' + n / j);
			c++;
		}
		n %= j;
	}
	_put_char('0' + n);
	c++;

	return (c);
}

/**
 * convert_num - converter function, a clone of itoa
 * @n: number
 * @b: base
 * @f: argument flags
 *
 * Return: string
 */
char *convert_num(long int n, int b, int f)
{
	static char *arr;
	static char _buffer[50];
	char s = 0;
	char *p;
	unsigned long num = n;

	if (!(f & CONVERT_UNSIGNED) && n < 0)
	{
		num = -n;
		s = '-';

	}
	arr = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &_buffer[49];
	*p = '\0';

	do	{
		*--p = arr[num % b];
		num /= b;
	} while (num != 0);

	if (s)
		*--p = s;
	return (p);
}

/**
 * comments_remove - function replaces first instance of '#' with '\0'
 * @_buf: address of the string to modify
 *
 * Return: Always 0;
 */
void comments_remove(char *_buf)
{
	int j;

	for (j = 0; _buf[j] != '\0'; j++)
		if (_buf[j] == '#' && (!j || _buf[j - 1] == ' '))
		{
			_buf[j] = '\0';
			break;
		}
}
