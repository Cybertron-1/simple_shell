#include "libr.h"

/**
 * unset_alias - alias string
 * @information: para struct
 * @str: string aka
 *
 * Return: good = 0 , bad = 1
 */
int unset_alias(information_tree *information, char *str)
{
	char *pointer, correspond_c;
	int _one;

	pointer = _string_tcharacter(str, '=');
	if (!pointer)
		return (1);
	correspond_c = *pointer;
	*pointer = 0;
	_one = remove_chasing_atindex(&(information->alias),
		starting_point_index(information->alias, starting_point(information->alias, str, -1)));
	*pointer = correspond_c;
	return (_one);
}

/**
 * set_alias - set ssdd
 * @information: para struct
 * @str: string lia
 *
 * Return: good = 0 , bad = 1
 */
int set_alias(information_tree *information, char *str)
{
	char *pointer;

	pointer = _string_tcharacter(str, '=');
	if (!pointer)
		return (1);
	if (!*++pointer)
		return (unset_alias(information, str));

	unset_alias(information, str);
	return (additional_endpoint_end(&(information->alias), str, 0) == NULL);
}

/**
 * print_alias - output alias string
 * @nation_node: alias nation_node
 *
 * Return: good = 0 , bad = 1
 */
int print_alias(listings_tree *nation_node)
{
	char *pointer = NULL, *a = NULL;

	if (nation_node)
	{
		pointer = _string_tcharacter(nation_node->str, '=');
		for (a = nation_node->str; a <= pointer; a++)
			_insertcharacter(*a);
		_insertcharacter('\'');
		_inserts(pointer + 1);
		_inserts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _personalalt - shades shell behaviour
 * @information: Sargs
 *  Return: Const 0
 */
int _personalalt(information_tree *information)
{
	int iterate = 0;
	char *pointer = NULL;
	listings_tree *nation_node = NULL;

	if (information->argc == 1)
	{
		nation_node = information->alias;
		while (nation_node)
		{
			print_alias(nation_node);
			nation_node = nation_node->next;
		}
		return (0);
	}
	for (iterate = 1; information->argv[iterate]; iterate++)
	{
		pointer = _string_tcharacter(information->argv[iterate], '=');
		if (pointer)
			set_alias(information, information->argv[iterate]);
		else
			print_alias(starting_point(information->alias, information->argv[iterate], '='));
	}

	return (0);
}
