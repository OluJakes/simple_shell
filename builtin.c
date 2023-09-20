#include "shell.h"

/**
 * _myhelp - Displays help message. Function not yet implemented.
 * @inf: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */
int _myhelp(info_t *inf)
{
	char **arg_array;

	arg_array = inf->argv;
	_puts("Help call works. Function not yet implemented.\n");
	if (0)
		_puts(*arg_array); /* Temporary att_unused workaround */
	return (0);
}

/**
 * _mycd - Changes the current directory of the process.
 * @inf: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */
int _mycd(info_t *inf)
{
	char *s, *dir, buffer[1024];
	int chgdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dir = _getenv(inf, "HOME=");
		if (!dir)
			chgdir_ret = chdir((dir = _getenv(inf, "PWD=")) ? dir : "/");
		else
			chgdir_ret = chdir(dir);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
		chgdir_ret = chdir((dir = _getenv(inf, "OLDPWD=")) ? dir : "/");
	}
	else
		chgdir_ret = chdir(inf->argv[1]);
	if (chgdir_ret == -1)
	{
		print_error(inf, "Can't cd to ");
		_eputs(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myexit - Exits the shell with a given exit status.
 * @inf: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */
int _myexit(info_t *inf)
{
	int exitchk;

	if (inf->argv[1])  /* Check if there is an exit argument */
	{
		exitchk = _erratoi(inf->argv[1]);
		if (exitchk == -1)
		{
			inf->status = 2;
			print_error(inf, "Illegal number: ");
			_eputs(inf->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inf->err_num = _erratoi(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

