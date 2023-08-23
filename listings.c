#include "libr.h"

/**
 * additional_endpoint: add endpoint
 * @get_hed: address of get_hed pointer in mem
 * @str: string field for nodation
 * @number: index for history
 * Return: ssize list in memory
 */
listings_tree *additional_endpoint(listings_tree **get_hed, const char *str, int number)
{
	listings_tree *new_head;
	if (!get_hed)
		return (NULL);
	new_head = malloc(sizeof(listings_tree));
	if (!new_head)
		return (NULL);
	_setup_memory((void *)new_head, 0, sizeof(listings_tree));
	new_head->number = number;
	if (str)
	{
		new_head->str = _string_dump(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *get_hed;
	*get_hed = new_head;
	return (new_head);
}

/**
 * additional_endpoint_end 
 * @get_hed: address of pointer to get_hed find_nodation
 * @str: string nodation 
 * @number: find index
 *
 * Return: size(list)
 */
listings_tree *additional_endpoint_end(listings_tree **get_hed, const char *str, int number)
{
	listings_tree *new_node, *get_nodation;
	if (!get_hed)
		return (NULL);

	get_nodation = *get_hed;
	new_node = malloc(sizeof(listings_tree));
	if (!new_node)
		return (NULL);
	_setup_memory((void *)new_node, 0, sizeof(listings_tree));
	new_node->number = number;
	if (str)
	{
		new_node->str = _string_dump(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (get_nodation)
	{
		while (get_nodation->next)
			get_nodation = get_nodation->next;
		get_nodation->next = new_node;
	}
	else
		*get_hed = new_node;
	return (new_node);
}

/**
 * cough_out_chasing - show only string elements
 * @h: pin first of lan
 * Return: integer size of list
 */
size_t cough_out_chasing(const listings_tree *h)
{
	size_t iterate = 0;
	while (h)
	{
		_inserts(h->str ? h->str : "(nil)");
		_inserts("\n");
		h = h->next;
		iterate++;
	}
	return (iterate);
}

/**
 * remove_chasing_atindex - deletes get_nodation at a particular index of arrays
 * @get_hed: address of pointer to i[0] get_nodation
 * @index: index of get_nodation remove
 * Return: 1 true, 0 fail binary
 */
int remove_chasing_atindex(listings_tree **get_hed, unsigned int index)
{
	listings_tree *get_nodation, *prev_node;
	unsigned int iterate = 0;
	if (!get_hed || !*get_hed)
		return (0);
	if (!index)
	{
		get_nodation = *get_hed;
		*get_hed = (*get_hed)->next;
		free(get_nodation->str);
		free(get_nodation);
		return (1);
	}
	get_nodation = *get_hed;
	while (get_nodation)
	{
		if (iterate == index)
		{
			prev_node->next = get_nodation->next;
			free(get_nodation->str);
			free(get_nodation);
			return (1);
		}
		iterate++;
		prev_node = get_nodation;
		get_nodation = get_nodation->next;
	}
	return (0);
}

/**
 * allow_chasing - free-all-nodes in mem
 * @head_ptr: address  = get_hed get_nodation
 *
 * Return: 1 or function
 */
void allow_chasing(listings_tree **head_ptr)
{
	listings_tree *get_nodation, *next_node, *get_hed;
	if (!head_ptr || !*head_ptr)
		return;
	get_hed = *head_ptr;
	get_nodation = get_hed;
	while (get_nodation)
	{
		next_node = get_nodation->next;
		free(get_nodation->str);
		free(get_nodation);
		get_nodation = next_node;
	}
	*head_ptr = NULL;
}
