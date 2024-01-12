#include "shell.h"

/**
 * _hsh - main shell loop
 * @x: the parameter & return info struct
 * @_av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int _hsh(info_t *x, char **_av)
{
	ssize_t s = 0;
	int ret = 0;

	while (s != -1 && ret != -2)
	{
		clear_information(x);
		if (interactive(x))
			put_str("$ ");
		put_echar(BUF_FLUSH);
		s = _get_in(x);
		if (s != -1)
		{
			set_information(x, _av);
			ret = _get_builtin(x);
			if (ret == -1)
				_get_cmd(x);
		}
		else if (_interactive(x))
			put_char('\n');
		free_information(x, 0);
	}
	_history_write(x);
	free_information(x, 1);
	if (!_interactive(x) && x->status)
		exit(x->status);
	if (ret == -2)
	{
		if (x->err_num == -1)
			exit(x->status);
		exit(x->err_num);
	}
	return (ret);
}

/**
 * _get_builtin - finds a builtin command
 * @x: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int _get_builtin(info_t *x)
{
	int j, ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _exity},
		{"env", _envy},
		{"help", _helpy},
		{"history", _historyy},
		{"setenv", _setenvy},
		{"unsetenv", _unsetenvy},
		{"cd", _cdy},
		{"alias", _aliasy},
		{NULL, NULL}
	};

	for (j = 0; builtintbl[j].type; j++)
		if (string_compare(x->argv[0], builtintbl[j].type) == 0)
		{
			x->line_count++;
			ret = builtintbl[j].func(x);
			break;
		}
	return (ret);
}

/**
 * _get_cmd - finds a command in PATH
 * @x: the parameter & return info struct
 *
 * Return: void
 */
void _get_cmd(info_t *x)
{
	char *p = NULL;
	int j, l;

	x->path = x->argv[0];
	if (x->linecount_flag == 1)
	{
		x->line_count++;
		x->linecount_flag = 0;
	}
	for (j = 0, l = 0; x->arg[j]; j++)
		if (!is_delimeter(x->arg[j], " \t\n"))
			l++;
	if (!l)
		return;

	p = _get_path(x, _getenvy(x, "PATH="), x->argv[0]);
	if (p)
	{
		x->path = p;
		_fork_cmd(x);
	}
	else
	{
		if ((_interactive(x) || _getenvy(x, "PATH=")
			|| x->argv[0][0] == '/') && _is_cmd(x, x->argv[0]))
			_fork_cmd(x);
		else if (*(x->arg) != '\n')
		{
			x->status = 127;
			print_err(x, "not found\n");
		}
	}
}

/**
 * _fork_cmd - forks a an exec thread to run cmd
 * @x: the parameter & return info struct
 *
 * Return: void
 */
void _fork_cmd(info_t *x)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (pid == 0)
	{
		if (execve(x->path, x->argv, get_env(x)) == -1)
		{
			free_information(x, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(x->status));
		if (WIFEXITED(x->status))
		{
			x->status = WEXITSTATUS(x->status);
			if (x->status == 126)
				print_err(x, "Permission denied\n");
		}
	}
}
