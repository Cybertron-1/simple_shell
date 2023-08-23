#include "libr.h"

/**
 * @_help_command: chande dir
 * @information: info
 * Return: set const 0
 */
int _help_command(information_tree *information)
{
	char **argument_arrays;
	int number = 0;

	argument_arrays = information->argv;
	_inserts("help call works. Function not yet implemented \n");
	if (number)
		_inserts(*argument_arrays);
	return (0);
}

/**
 * _exit_command - exit shell
 * @information: struct info call
 *  Return: exit shell_status
 */
int _exit_command(information_tree *information)
{
	int binary_int_verify;

	if (information->argv[1])  /* only exit command */
	{
		binary_int_verify = _errorautocorrect(information->argv[1]);
		if (binary_int_verify == -1)
		{
			information->shell_status = 2;
			output_error(information, "Illegal number: ");
			_insertputschar(information->argv[1]);
			_einsertcharacter('\n');
			return (1);
		}
		information->error_number = _errorautocorrect(information->argv[1]);
		return (-2);
	}
	information->error_number = -1;
	return (-2);
}

/**
 * _cd_command - change to now directory
 * @information: list trr con info
 *  Return: Const 0
 */
int _cd_command(information_tree *information)
{
	char *s, *directory, buffer[1024];
	int changedirectory_return;
	s = getcwd(buffer, 1024);

	if (!s)
		_inserts("TODO: >>getcwd failure emsg here<<\n");
	if (!information->argv[1])
	{
		directory = _grabenv(information, "HOME=");
		if (!directory)
			changedirectory_return = chdir((directory = _grabenv(information, "PWD=")) ? directory : "/");
		else
			changedirectory_return = chdir(directory);
	}
	else if (_string_compare(information->argv[1], "-") == 0)
	{
		if (!_grabenv(information, "OLDPWD="))
		{
			_inserts(s);
			_insertcharacter('\n');
			return (1);
		}
		_inserts(_grabenv(information, "OLDPWD=")), _insertcharacter('\n');
		changedirectory_return = /* Get what shoud */
			chdir((directory = _grabenv(information, "OLDPWD=")) ? directory : "/");
	}
	else
		changedirectory_return = chdir(information->argv[1]);
	if (changedirectory_return == -1)
	{
		output_error(information, "can't cd to ");
		_insertputschar(information->argv[1]), _insertcharacter('\n');
	}
	else
	{
		_initializeenvironment(information, "OLDPWD", _grabenv(information, "PWD="));
		_initializeenvironment(information, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _personal_history - show history list
 * @information: agrs
 *  Return: static 0
 */
int _personal_history(information_tree *information)
{
	output_listings(information->history);
	return (0);
}
