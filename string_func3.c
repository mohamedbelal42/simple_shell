#include "shell.h"

/**
 **str_copy - copies a string
 *@destination: the destination string to be copied to
 *@source: the source string
 *@num: the amount of characters to be copied
 *Return: the concatenated string
 */
char *str_copy(char *destination, char *source, int num)
{
	int j, k;
	char *str = destination;

	j = 0;
	while (source[j] != '\0' && j < num - 1)
	{
		destination[j] = source[j];
		j++;
	}
	if (j < num)
	{
		k = j;
		while (k < num)
		{
			destination[k] = '\0';
			k++;
		}
	}
	return (str);
}

/**
 ** str_cat - concatenates two strings
 *@destination: the first string
 *@source: the second string
 *@num: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *str_cat(char *destination, char *source, int num)
{
	int j, k;
	char *str = destination;

	j = 0;
	k = 0;
	while (destination[j] != '\0')
		j++;
	while (source[k] != '\0' && k < num)
	{
		destination[j] = source[k];
		j++;
		k++;
	}
	if (k < num)
		destination[j] = '\0';
	return (str);
}

/**
 **string_ch - locates a character in a string
 *@str: the string to be parsed
 *@ch: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *string_ch(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
