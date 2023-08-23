#include "libr.h"

/**
 * chase_itself - test if current char in buffer is a chain delimeter
 * @information: the parameter struct
 * @buffer: the char buffer
 * @pin: address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
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
	else if (buffer[hind] == ';') /* found end of this command */
	{
		buffer[hind] = 0; /* replace semicolon with null */
		information->cmd_buf_type = COMMAND_LINE_CHAINING;
	}
	else
		return (0);
	*pin = hind;
	return (1);
}

/**
 * verify_chase - checks we should continue chaining based on last shell_status
 * @information: the parameter struct
 * @buffer: the char buffer
 * @pin: address of current position in buffer
 * @iterate: starting position in buffer
 * @len: length of buffer
 *
 * Return: Void
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
 * change_alternative - replaces an aliases in the tokenized string
 * @information: the parameter struct
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
 * exchange_var - replaces vars in the tokenized string
 * @information: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
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
