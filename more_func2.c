#include "shell.h"

/**
 * _errtoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _errtoi(char *str)
{
	int j = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	for (j = 0;  str[j] != '\0'; j++)
	{
		if (str[j] >= '0' && str[j] <= '9')
		{
			res *= 10;
			res += (str[j] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * error_print - prints an error message
 * @information: the parameter & return info struct
 * @errorstr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void error_print(info_t *information, char *errorstr)
{
	_eputs(information->fname);
	_eputs(": ");
	print_d(information->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(information->argv[0]);
	_eputs(": ");
	_eputs(errorstr);
}

/**
 * print_dec - function prints a decimal (integer) number (base 10)
 * @in: the input
 * @f: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_dec(int in, int f)
{
	int (*__putchar)(char) = _putchar;
	int j, c = 0;
	unsigned int _abs, _current;

	if (f == STDERR_FILENO)
		__putchar = _eputchar;
	if (in < 0)
	{
		_abs = -in;
		__putchar('-');
		c++;
	}
	else
		_abs = in;
	_current = _abs;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs / j)
		{
			__putchar('0' + _current / i);
			c++;
		}
		_current %= j;
	}
	__putchar('0' + _current);
	c++;

	return (c);
}

/**
 * number_convert - converter function, a clone of itoa
 * @n: number
 * @b: base
 * @f: argument flags
 *
 * Return: string
 */
char *number_convert(long int n, int b, int f)
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
