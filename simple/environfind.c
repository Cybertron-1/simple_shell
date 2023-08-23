#include "libr.h"

/**
 * grab_environment - returns the string array copy of our environ
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **grab_environment(information_tree *information)
{
	if (!information->environ || information->environ_changed)
	{
		information->environ = convertlistings_tostrings(information->env);
		information->environ_changed = 0;
	}

	return (information->environ);
}

/**
 * _releaseenviron - Remove an environ variable
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _releaseenviron(information_tree *information, char *var)
{
	listings_tree *nodation_ = information->env;
	size_t i = 0;
	char *point;

	if (!nodation_ || !var)
		return (0);

	while (nodation_)
	{
		point = _begins_withwhat(nodation_->str, var);
		if (point && *point == '=')
		{
			information->environ_changed = remove_chasing_atindex(&(information->env), i);
			i = 0;
			nodation_ = information->env;
			continue;
		}
		nodation_ = nodation_->next;
		i++;
	}
	return (information->environ_changed);
}

/**
 * _initializeenvironment - Initialize a new environ variable,
 *             or modify an existing one
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _initializeenvironment(information_tree *information, char *var, char *value)
{
	char *buffer = NULL;
	listings_tree *nodation_;
	char *point;
	int check = (!var || !value);

	if (check)
		return (0);

	buffer = malloc(_string_length(var) + _string_length(value) + 2);
	if (!buffer)
		return (1);
	_string_copy_custom1(buffer, var);
	_string_catenation(buffer, "=");
	_string_catenation(buffer, value);
	nodation_ = information->env;
	while (nodation_)
	{
		point = _begins_withwhat(nodation_->str, var);
		if (point && *point == '=')
		{
			free(nodation_->str);
			nodation_->str = buffer;
			information->environ_changed = 1;
			return (0);
		}
		nodation_ = nodation_->next;
	}
	additional_endpoint_end(&(information->env), buffer, 0);
	free(buffer);
	information->environ_changed = 1;
	return (0);
}

