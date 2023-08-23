#include "libr.h"

/**
 **_setup_memory - put in memory
 *@statelite: point to stack in memory
 *@bad: the byte to fill *statelite with
 *@initial: numbers of bytes to fill into memory
 *Return: to the memory area statelite
 */
char *_setup_memory(char *statelite, char bad, unsigned int initial)
{
	unsigned int iterate;

	for (iterate = 0; iterate < initial; iterate++)
		statelite[iterate] = bad;
	return (statelite);
}

/**
 * _free_mallox - release apple string of  multiple strings
 * @pp: string of strings
 */
void _free_mallox(char **pp)
{
	char **apple = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(apple);
}

/**
 * _mem_reallocator - malloc reallocates apple block of memory
 * @ptr: pointer to previous mallocated block
 * @old_size: byte size of plast or former block
 * @new_size: byte size of latest block
 * Return: pointer to da ol'block nameen.
 */
void *_mem_reallocator(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pointer_point;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	pointer_point = malloc(new_size);
	if (!pointer_point)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		pointer_point[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pointer_point);
}
