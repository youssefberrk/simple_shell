#include "shell.h"

/**
 * _mycd - Changes the current directory of the process.
 * @info: Structure with potential arguments for maintaining a constant
 *         function prototype.
 *
 * Return: Always 0.
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}

	if (_strcmp(info->argv[1], "-") == 0)
		return (handle_dash_case(info, s));

	while (info->argv[1])
	{
		chdir_ret = chdir(info->argv[1]);
	}

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
		update_env_and_pwd(info, buffer);

	return (0);
}

/**
 * handle_dash_case - Handles the case when cd is called with "-" argument.
 * @info: Structure with potential arguments for maintaining a constant
 *         function prototype.
 * @s: Current working directory.
 *
 * Return: 1 if successful; 0 otherwise.
 */
int handle_dash_case(info_t *info, char *s)
{
	if (!_getenv(info, "OLDPWD="))
	{
		_puts(s);
		_putchar('\n');
		return (1);
	}
	_puts(_getenv(info, "OLDPWD="));
	_putchar('\n');

	int chdir_ret = chdir(_getenv(info, "OLDPWD="));

	return (chdir_ret == 0);
}

/**
 * update_env_and_pwd - Updates environmental variables and current directory.
 * @info: Structure with potential arguments for maintaining a constant
 *         function prototype.
 * @buffer: Buffer for storing the current working directory.
 */
void update_env_and_pwd(info_t *info, char *buffer)
{
	_setenv(info, "OLDPWD", _getenv(info, "PWD="));
	_setenv(info, "PWD", getcwd(buffer, 1024));
}

