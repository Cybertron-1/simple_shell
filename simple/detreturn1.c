#include "libr.h"

/**
 *_insertputschar - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void _insertputschar(char *string)
{
	int iterate = 0;

	if (!string)
		return;
	while (string[iterate] != '\0')
	{
		_insertcharacter(string[iterate]);
		iterate++;
	}
}

/**
 * _insertcharacter - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _einsertcharacter(char c)
{
	static int iterate;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFERMEM_FLASHER || iterate >= WRITE_BUFFER_SIZE)
	{
		write(2, buf, iterate);
		iterate = 0;
	}
	if (c != BUFFERMEM_FLASHER)
		buf[iterate++] = c;
	return (1);
}

/**
 * _insertfd1 - writes the character c to given filedesc_
 * @c: The character to print
 * @filedesc_: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _insertfd1(char c, int filedesc_)
{
	static int iterate;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFERMEM_FLASHER || iterate >= WRITE_BUFFER_SIZE)
	{
		write(filedesc_, buf, iterate);
		iterate = 0;
	}
	if (c != BUFFERMEM_FLASHER)
		buf[iterate++] = c;
	return (1);
}

/**
 *_insertfd - prints an input string
 * @string: the string to be printed
 * @filedesc_: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _insertfd(char *string, int filedesc_)
{
	int iterate = 0;

	if (!string)
		return (0);
	while (*string)
	{
		iterate += _insertfd1(*string++, filedesc_);
	}
	return (iterate);
}


