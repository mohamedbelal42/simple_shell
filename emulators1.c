#include "shell.h"

/**
 * _exity - exits the shell
 * @x: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _exity(info_t *x)
{
	int exit_check;

	if (x->argv[1])  /* If there is an exit arguement */
	{
		exit_check = _stoi(x->argv[1]);
		if (exit_check == -1)
		{
			x->status = 2;
			print_err(x, "Illegal number: ");
			put_e(x->argv[1]);
			put_echar('\n');
			return (1);
		}
		x->err_num = _stoi(x->argv[1]);
		return (-2);
	}
	x->err_num = -1;
	return (-2);
}

/**
 * _cdy - changes the current directory of the process
 * @x: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _cdy(info_t *x)
{
	char *str, *d, _buffer[1024];
	int ret;

	str = getcwd(_buffer, 1024);
	if (!str)
		put_str("TODO: >>getcwd failure emsg here<<\n");
	if (!x->argv[1])
	{
		d = _getenvy(x, "HOME=");
		if (!d)
			ret = /* TODO: what should this be? */
				chdir((d = _getenvy(x, "PWD=")) ? d : "/");
		else
			ret = chdir(d);
	}
	else if (string_compare(x->argv[1], "-") == 0)
	{
		if (!_getenvy(x, "OLDPWD="))
		{
			put_str(str);
			put_char('\n');
			return (1);
		}
		put_str(_getenvy(x, "OLDPWD=")), put_char('\n');
		ret = /* TODO: what should this be? */
			chdir((d = _getenvy(x, "OLDPWD=")) ? d : "/");
	}
	else
		ret = chdir(x->argv[1]);
	if (ret == -1)
	{
		print_err(x, "can't cd to ");
		put_e(x->argv[1]), put_echar('\n');
	}
	else
	{
		_set_env(x, "OLDPWD", _getenvy(x, "PWD="));
		_set_env(x, "PWD", getcwd(_buffer, 1024));
	}
	return (0);
}

/**
 * _helpy - changes the current directory of the process
 * @x: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _helpy(info_t *x)
{
	char **arr;

	arr = x->argv;
	put_str("help call works. Function not yet implemented \n");
	if (0)
		put_str(*arr); /* temp att_unused workaround */
	return (0);
}
