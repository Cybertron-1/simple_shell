#include "libr.h"

/**
 * _personenv - prints the current environ
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _personenv(information_tree *information)
{
	cough_out_chasing(information->env);
	return (0);
}

/**
 * _grabenv - gets the value of an environ variable
 * @information: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_grabenv(information_tree *information, const char *name)
{
	listings_tree *get_node = information->env;
	char *peace;

	while (get_node)
	{
		peace = _begins_withwhat(get_node->str, name);
		if (peace && *peace)
			return (peace);
		get_node = get_node->next;
	}
	return (NULL);
}

/**
 * _setupenviron - Initialize a new environ variable,
 *             or modify an existing one
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _setupenviron(information_tree *information)
{
	if (information->argc != 3)
	{
		_insertputschar("Incorrect number of arguements\n");
		return (1);
	}
	if (_initializeenvironment(information, information->argv[1], information->argv[2]))
		return (0);
	return (1);
}

/**
 * _freepersonalenviron - Remove an environ variable
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _freepersonalenviron(information_tree *information)
{
	int iterate;

	if (information->argc == 1)
	{
		_insertputschar("Too few arguements.\n");
		return (1);
	}
	for (iterate = 1; iterate <= information->argc; iterate++)
		_releaseenviron(information, information->argv[iterate]);

	return (0);
}

/**
 * initialize_environment - populates env linked list
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int initialize_environment(information_tree *information)
{
	listings_tree *get_node = NULL;
	size_t iterate;

	for (iterate = 0; environ[iterate]; iterate++)
		additional_endpoint_end(&get_node, environ[iterate], 0);
	information->env = get_node;
	return (0);
}
