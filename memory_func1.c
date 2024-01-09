#include "shell.h"

/**
 **_memoryset - fills memory with a constant byte
 *@ar: the pointer to the memory area
 *@b: the byte to fill *ar with
 *@num: the amount of bytes to be filled
 *Return: (ar) a pointer to the memory area s
 */
char *_memoryset(char *ar, char b, unsigned int num)
{
	unsigned int j;

	for (j = 0; j < num; j++)
		ar[j] = b;
	return (ar);
}

/**
 * _free - frees a string of strings
 * @str: string of strings
 */
void _free(char **str)
{
	char **b = str;

	if (!str)
		return;
	while (*str)
		free(*str++);
	free(b);
}

/**
 * _reallocation - reallocates a block of memory
 * @p: pointer to previous malloc'ated block
 * @size_old: byte size of previous block
 * @size_new: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_reallocation(void *p, unsigned int size_old, unsigned int size_new)
{
	char *q;

	if (!p)
		return (malloc(size_new));
	if (!size_new)
		return (free(p), NULL);
	if (size_new == size_old)
		return (p);

	q = malloc(size_new);
	if (!q)
		return (NULL);

	size_old = size_old < size_new ? size_old : size_new;
	while (size_old--)
		q[size_old] = ((char *)p)[size_old];
	free(p);
	return (q);
}
