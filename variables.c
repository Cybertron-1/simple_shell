#include "libr.h"

/**
 * chase_itself - current char in buffer
 * @information: parameter struct
 * @buffer: char buffer
 * @pin: address of current position in buffer
 *
 * Return: 1 pass, 0 otherwise
 */
int chase_itself(information_tree *information, char *buffer, size_t *pin)
{
	size_t hind = *pin;

	if (buffer[hind] == '|' && buffer[hind + 1] == '|')
	{
		buffer[hind] = 0;
		hind++;
		information->cmd_buf_type = COMMANDLINE_ORILIZATION;
	}
	else if (buffer[hind] == '&' && buffer[hind + 1] == '&')
	{
		buffer[hind] = 0;
		hind++;
		information->cmd_buf_type = COMMAND_LINE_AND_OPERATOR;
	}
	else if (buffer[hind] == ';')
	{
		buffer[hind] = 0;
		information->cmd_buf_type = COMMAND_LINE_CHAINING;
	}
	else
		return (0);
	*pin = hind;
	return (1);
}

/**
 * verify_chase - checks
 * @information: parameter struct
 * @buffer: char buffer
 * @pin: address of current position in buffer
 * @iterate: starting position in buffer
 * @len: length buff
 *
 * Return: 1
 */
void verify_chase(information_tree *information, char *buffer, size_t *pin, size_t iterate, size_t len)
{
	size_t hind = *pin;

	if (information->cmd_buf_type == COMMAND_LINE_AND_OPERATOR)
	{
		if (information->shell_status)
		{
			buffer[iterate] = 0;
			hind = len;
		}
	}
	if (information->cmd_buf_type == COMMANDLINE_ORILIZATION)
	{
		if (!information->shell_status)
		{
			buffer[iterate] = 0;
			hind = len;
		}
	}

	*pin = hind;
}

/**
 * change_alternative - a replace aliases
 * @information: parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_alternative(information_tree *information)
{
	int iterate;
	listings_tree *node;
	char *pin;

	for (iterate = 0; iterate < 10; iterate++)
	{
		node = starting_point(information->alias, information->argv[0], '=');
		if (!node)
			return (0);
		free(information->argv[0]);
		pin = _string_tcharacter(node->str, '=');
		if (!pin)
			return (0);
		pin = _string_dump(pin + 1);
		if (!pin)
			return (0);
		information->argv[0] = pin;
	}
	return (1);
}

/**
 * exchange_var - ars in th
 * @information: parameter struct
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int exchange_var(information_tree *information)
{
	int iterate = 0;
	listings_tree *node;

	for (iterate = 0; information->argv[iterate]; iterate++)
	{
		if (information->argv[iterate][0] != '$' || !information->argv[iterate][1])
			continue;

		if (!_string_compare(information->argv[iterate], "$?"))
		{
			exchange_string(&(information->argv[iterate]),
				_string_dump(transform_num(information->shell_status, 10, 0)));
			continue;
		}
		if (!_string_compare(information->argv[iterate], "$$"))
		{
			exchange_string(&(information->argv[iterate]),
				_string_dump(transform_num(getpid(), 10, 0)));
			continue;
		}
		node = starting_point(information->env, &information->argv[iterate][1], '=');
		if (node)
		{
			exchange_string(&(information->argv[iterate]),
				_string_dump(_string_tcharacter(node->str, '=') + 1));
			continue;
		}
		exchange_string(&information->argv[iterate], _string_dump(""));

	}
	return (0);
}

/**
 * exchange_string - replaces string
 * @old: address  = old_string
 * @fresh: lastest string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int exchange_string(char **old, char *fresh)
{
	free(*old);
	*old = fresh;
	return (1);
}
