#include "shell.h"

/**
 * main - entry point
 * @_ac: arg count
 * @_av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int _ac, char **_av)
{
	info_t information[] = { INFO_INIT };
	int f = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (f)
		: "r" (f));

	if (_ac == 2)
	{
		f = open(_av[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				put_e(av[0]);
				put_e(": 0: Can't open ");
				put_e(av[1]);
				put_echar('\n');
				put_echar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		information->readfd = f;
	}
	envy_list(information);
	_history_read(information);
	hsh(information, _av);
	return (EXIT_SUCCESS);
}
