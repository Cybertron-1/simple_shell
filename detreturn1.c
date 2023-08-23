#include "libr.h"

/**
 *_insertputschar - output inputed string
 * @string: outputed string previous in mem
 *
 * Return: null
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
 * _insertcharacter - char -> stderr
 * @c: The character to print
 *
 * Return: 1 for pass else otherwise
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
 * _insertfd1 - char -> filedesc_
 * @c: char to output
 * @filedesc_: put into filedesc
 *
 * Return: 1 pass otherwise failed.
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
 *_insertfd - output str
 * @string: str to be printed
 * @filedesc_: put into filedesc
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


