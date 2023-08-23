#include "libr.h"

/**
 * _string_copy_custom1 - copies a string
 * @end: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *_string_copy_custom1(char *end, char *source)
{
	int iterate = 0;

	if (end == source || source == 0)
		return (end);
	while (source[iterate])
	{
		end[iterate] = source[iterate];
		iterate++;
	}
	end[iterate] = 0;
	return (end);
}

/**
 * _string_dump - duplicates a string
 * @stringz_fu: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_string_dump(const char *stringz_fu)
{
	int length = 0;
	char *return_kl;

	if (stringz_fu == NULL)
		return (NULL);
	while (*stringz_fu++)
		length++;
	return_kl = malloc(sizeof(char) * (length + 1));
	if (!return_kl)
		return (NULL);
	for (length++; length--;)
		return_kl[length] = *--stringz_fu;
	return (return_kl);
}

/**
 *_inserts - prints an input string
 *@stringz_fu: the string to be printed
 *
 * Return: Nothing
 */
void _inserts(char *stringz_fu)
{
	int iterate = 0;

	if (!stringz_fu)
		return;
	while (stringz_fu[iterate] != '\0')
	{
		_insertcharacter(stringz_fu[iterate]);
		iterate++;
	}
}

/**
 * _insertcharacter - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _insertcharacter(char c)
{
	static int iterate;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFERMEM_FLASHER || iterate >= WRITE_BUFFER_SIZE)
	{
		write(1, buf, iterate);
		iterate = 0;
	}
	if (c != BUFFERMEM_FLASHER)
		buf[iterate++] = c;
	return (1);
}
