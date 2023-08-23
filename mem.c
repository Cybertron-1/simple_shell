#include "libr.h"

/**
 * buffer_free - free *p
 * @pointer: address = free free pointer
 * Return: freeing on success 1 else opposite
 */
int buffer_free(void **pointer)
{
	int heck = (pointer && *pointer);
	if (heck)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
