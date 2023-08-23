#include "libr.h"

/**
 * listing_length - get-length of list
 * @h: point = first nodation_i
 * Return: size of list
 */
size_t listing_length(const listings_tree *h)
{
	size_t iterate = 0;

	while (h)
	{
		h = h->next;
		iterate++;
	}
	return (iterate);
}

/**
 * convertlistings_tostrings - li->str mapping pointer
 * @head: address point = first nodation_i
 *
 * Return: array of strings
 */
char **convertlistings_tostrings(listings_tree *head)
{
	listings_tree *nodation_i = head;
	size_t iterate = listing_length(head), j;
	char **strs;
	char *str;

	if (!head || !iterate)
		return (NULL);
	strs = malloc(sizeof(char *) * (iterate + 1));
	if (!strs)
		return (NULL);
	for (iterate = 0; nodation_i; nodation_i = nodation_i->next, iterate++)
	{
		str = malloc(_string_length(nodation_i->str) + 1);
		if (!str)
		{
			for (j = 0; j < iterate; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _string_copy_custom1(str, nodation_i->str);
		strs[iterate] = str;
	}
	strs[iterate] = NULL;
	return (strs);
}


/**
 * output_listings - output entities of a tree linked list
 * @h: * -=first nodation_i
 * Return: get_size_list
 */
size_t output_listings(const listings_tree *h)
{
	size_t iterate = 0;

	while (h)
	{
		_inserts(transform_num(h->number, 10, 0));
		_insertcharacter(':');
		_insertcharacter(' ');
		_inserts(h->str ? h->str : "(nil)");
		_inserts("\n");
		h = h->next;
		iterate++;
	}
	return (iterate);
}

/**
 * starting_point - returns nodation_i with string starting with fixpreagenda --
 * @nodation_i: pointer to list head
 * @fixpreagenda: string to match
 * @d: the next character after fixpreagenda to match
 *
 * Return: match nodation_i or null
 */
listings_tree *starting_point(listings_tree *nodation_i, char *fixpreagenda, char d)
{
	char *gin = NULL;

	while (nodation_i)
	{
		gin = _begins_withwhat(nodation_i->str, fixpreagenda);
		if (gin && ((d == -1) || (*gin == d)))
			return (nodation_i);
		nodation_i = nodation_i->next;
	}
	return (NULL);
}

/**
 * starting_point_index grab index of nodation_i
 * @head:  -> head information_treew
 * @nodation_i: pointer to the nodation_i
 * Return: index of nodation_i or -1
 */
ssize_t starting_point_index(listings_tree *head, listings_tree *nodation_i)
{
	size_t iterate = 0;

	while (head)
	{
		if (head == nodation_i)
			return (iterate);
		head = head->next;
		iterate++;
	}
	return (-1);
}
