#include "shell.h"

/**
 **memory_set - fills memory with a constant byte
 *@str: the pointer to the memory area
 *@_b: the byte to fill *s with
 *@num: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *memory_set(char *str, char _b, unsigned int num)
{
	unsigned int j;

	for (j = 0; j < num; j++)
		str[j] = _b;
	return (str);
}

/**
 * str_free - frees a string of strings
 * @p: string of strings
 */
void str_free(char **p)
{
	char **b = p;

	if (!p)
		return;
	while (*p)
		free(*p++);
	free(b);
}

/**
 * real_loc - reallocates a block of memory
 * @p: pointer to previous malloc'ated block
 * @old_s: byte size of previous block
 * @new_s: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *real_loc(void *p, unsigned int old_s, unsigned int new_s)
{
	char *ptr;

	if (!p)
		return (malloc(new_s));
	if (!new_s)
		return (free(p), NULL);
	if (new_s == old_s)
		return (p);

	ptr = malloc(new_s);
	if (!ptr)
		return (NULL);

	old_s = old_s < new_s ? old_s : new_s;
	while (old_s--)
		ptr[old_s] = ((char *)p)[old_s];
	free(p);
	return (ptr);
}
