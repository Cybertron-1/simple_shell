#include "libr.h"

/**
 * clear_terminal - initializes information_tree struct
 * @information: struct address
 */
void clear_terminal(information_tree *information)
{
	information->arg = NULL;
	information->argv = NULL;
	information->path = NULL;
	information->argc = 0;
}

/**
 * intialize_information - initializes information_tree struct
 * @information: struct address
 * @av: argument vector
 */
void intialize_information(information_tree *information, char **av)
{
	int i = 0;

	information->first_name = av[0];
	if (information->arg)
	{
		information->argv = _string_tower_split(information->arg, " \t");
		if (!information->argv)
		{
			information->argv = malloc(sizeof(char *) * 2);
			if (information->argv)
			{
				information->argv[0] = _string_dump(information->arg);
				information->argv[1] = NULL;
			}
		}
		for (i = 0; information->argv && information->argv[i]; i++)
			;
		information->argc = i;

		change_alternative(information);
		exchange_var(information);
	}
}

/**
 * release_information - frees information_tree struct fields
 * @information: struct address
 * @all: true if freeing all fields
 */
void release_information(information_tree *information, int all)
{
	_free_mallox(information->argv);
	information->argv = NULL;
	information->path = NULL;
	if (all)
	{
		if (!information->commandline_buffer_unique)
			free(information->arg);
		if (information->env)
			allow_chasing(&(information->env));
		if (information->history)
			allow_chasing(&(information->history));
		if (information->alias)
			allow_chasing(&(information->alias));
		_free_mallox(information->environ);
			information->environ = NULL;
		buffer_free((void **)information->commandline_buffer_unique);
		if (information->byte_reader > 2)
			close(information->byte_reader);
		_insertcharacter(BUFFERMEM_FLASHER);
	}
}

