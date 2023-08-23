#include "libr.h"

/**
 * get_builting - look for a STRING_BUL command
 * @information: parameter
 */
int get_builting(information_tree *information)
{
	int iterate, built_in_ret = -1;
	STRING_BUL_TABLE builtintbl[] = {
		{"exit", _exit_command},
		{"env", _personenv},
		{"help", _help_command},
		{"history", _personal_history},
		{"setenv", _setupenviron},
		{"unsetenv", _freepersonalenviron},
		{"cd", _cd_command},
		{"alias", _personalalt},
		{NULL, NULL}
	};

	for (iterate = 0; builtintbl[iterate].function_type_s; iterate++)
		if (_string_compare(information->argv[0], builtintbl[iterate].function_type_s) == 0)
		{
			information->getline_counter++;
			built_in_ret = builtintbl[iterate].main_function(information);
			break;
		}
	return (built_in_ret);
}

/**
 * ghash - main shell loop
 * @information: the parameter & return information struct
 * @avatar: the argument vector from main()
 * Return: good for 0 and 1 error meaning fAILED
  */
int ghash(information_tree *information, char **avatar)
{
	ssize_t normal_r = 0;
	int ret_bul = 0;

	while (normal_r != -1 && ret_bul != -2)
	{
		clear_terminal(information);
		if (hc_interact(information))
			_inserts("$ ");
		_einsertcharacter(BUFFERMEM_FLASHER);
		normal_r = capture_input(information);
		if (normal_r != -1)
		{
			intialize_information(information, avatar);
			ret_bul = get_builting(information);
			if (ret_bul == -1)
				commandline_find(information);
		}
		else if (hc_interact(information))
			_insertcharacter('\n');
		release_information(information, 0);
	}
	down_history(information);
	release_information(information, 1);
	if (!hc_interact(information) && information->shell_status)
		exit(information->shell_status);
	if (ret_bul == -2)
	{
		if (information->error_number == -1)
			exit(information->shell_status);
		exit(information->error_number);
	}
	return (ret_bul);
}

/**
 * _hook_commandline - forks a an exec thread to run cmd
 * @information: the parameter & return information struct
 *
 * Return: void
 */
void _hook_commandline(information_tree *information)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* Do: error check*/
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(information->path, information->argv, grab_environment(information)) == -1)
		{
			release_information(information, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* initialize error function*/
	}
	else
	{
		wait(&(information->shell_status));
		if (WIFEXITED(information->shell_status))
		{
			information->shell_status = WEXITSTATUS(information->shell_status);
			if (information->shell_status == 126)
				output_error(information, "Permission denied\n");
		}
	}
}

/**
 * commandline_find - STRING FIND IN COMMAND
 * @information:  return information struct AND PARA
 * Return: 1
 */
void commandline_find(information_tree *information)
{
	char *path = NULL;
	int iterate, uio;

	information->path = information->argv[0];
	if (information->getline_counter_flag == 1)
	{
		information->getline_counter++;
		information->getline_counter_flag = 0;
	}
	for (iterate = 0, uio = 0; information->arg[iterate]; iterate++)
		if (!_delimiterseq(information->arg[iterate], " \t\n"))
			uio++;
	if (!uio)
		return;

	path = _get_path(information, _grabenv(information, "PATH="), information->argv[0]);
	if (path)
	{
		information->path = path;
		_hook_commandline(information);
	}
	else
	{
		if ((hc_interact(information) || _grabenv(information, "PATH=")
			|| information->argv[0][0] == '/') && _commandline(information, information->argv[0]))
			_hook_commandline(information);
		else if (*(information->arg) != '\n')
		{
			information->shell_status = 127;
			output_error(information, "not found\n");
		}
	}
}
