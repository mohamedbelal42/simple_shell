#include "shell.h"

/**
 * **string_tow - splits a string into words. Repeat delimiters are ignored
 * @s: the input string
 * @del: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **string_tow(char *s, char *del)
{
	int j, k, l, n, num = 0;
	char **str;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (j = 0; s[j] != '\0'; j++)
		if (!is_delimeter(s[j], del) && (is_delimeter(s[j + 1], del) || !s[j + 1]))
			num++;

	if (num == 0)
		return (NULL);
	str = malloc((1 + num) * sizeof(char *));
	if (!str)
		return (NULL);
	for (j = 0, k = 0; k < num; k++)
	{
		while (is_delimeter(s[j], del))
			j++;
		l = 0;
		while (!is_delimeter(s[j + l], del) && s[j + l])
			l++;
		str[k] = malloc((l + 1) * sizeof(char));
		if (!str[k])
		{
			for (l = 0; l < k; l++)
				free(str[l]);
			free(str);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			str[k][n] = s[j++];
		str[k][n] = 0;
	}
	str[k] = NULL;
	return (str);
}

/**
 * **string_tow2 - splits a string into words
 * @s: the input string
 * @del: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **string_tow2(char *s, char del)
{
	int j, k, l, n, num = 0;
	char **str;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (j = 0; s[j] != '\0'; j++)
		if ((s[j] != del && s[j + 1] == del) ||
		    (s[j] != del && !s[j + 1]) || s[j + 1] == del)
			num++;
	if (num == 0)
		return (NULL);
	str = malloc((1 + num) * sizeof(char *));
	if (!str)
		return (NULL);
	for (j = 0, k = 0; k < num; k++)
	{
		while (s[j] == del && s[j] != del)
			j++;
		l = 0;
		while (s[j + l] != del && s[j + l] && s[j + l] != del)
			l++;
		str[k] = malloc((l + 1) * sizeof(char));
		if (!str[k])
		{
			for (l = 0; l < k; l++)
				free(str[l]);
			free(str);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			str[k][n] = s[j++];
		str[k][n] = 0;
	}
	str[k] = NULL;
	return (str);
}
