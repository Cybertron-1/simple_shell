#include "libr.h"

/**
 * _string_length - returns the length of a string
 * @string_nul: the string whose length to check
 *
 * Return: integer length of string
 */
int _string_length(char *string_nul)
{
	int iterate = 0;

	if (!string_nul)
		return (0);

	while (*string_nul++)
		iterate++;
	return (iterate);
}

/**
 * _string_catenation - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_string_catenation(char *destination, char *source)
{
	char *ret = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (ret);
}

/**
 * _string_compare - performs lexicogarphic comparison of two strangs.
 * @number_i1: the first strang
 * @number_i2: the second strang
 *
 * Return: negative if number_i1 < number_i2, positive if number_i1 > number_i2, zero if number_i1 == number_i2
 */
int _string_compare(char *number_i1, char *number_i2)
{
	while (*number_i1 && *number_i2)
	{
		if (*number_i1 != *number_i2)
			return (*number_i1 - *number_i2);
		number_i1++;
		number_i2++;
	}
	if (*number_i1 == *number_i2)
		return (0);
	else
		return (*number_i1 < *number_i2 ? -1 : 1);
}

/**
 * _begins_withwhat - checks if pin starts with dump
 * @dump: string to search
 * @pin: the substring to find
 *
 * Return: address of next char of dump or NULL
 */
char *_begins_withwhat(const char *dump, const char *pin)
{
	while (*pin)
		if (*pin++ != *dump++)
			return (NULL);
	return ((char *)dump);
}
