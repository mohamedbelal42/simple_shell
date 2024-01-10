#include "shell.h"

/**
 * string_length - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int string_length(char *str)
{
	int j = 0;

	if (!str)
		return (0);

	while (*str++)
		j++;
	return (j);
}

/**
 * string_compare - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @str2: the second strang
 *
 * Return: negative if str1 < str2, positive if str1 > str2, 0 if str1 == str2
 */
int string_compare(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * start_with - checks if needle starts with haystack
 * @h: string to search
 * @n: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *start_with(const char *h, const char *n)
{
	while (*n)
		if (*n++ != *h++)
			return (NULL);
	return ((char *)h);
}

/**
 * string_cat - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *string_cat(char *destination, char *source)
{
	char *r = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (r);
}
