#include "libr.h"

/**
 *_checkalphanumeric - check for alpha char
 *@ischaralpha: the character the user is inputing
 *Return: 1 if ischaralpha is alphabetic or 0 if not
 */
int _checkalphanumeric(int ischaralpha)
{
	int checkalpha = (ischaralpha >= 'a' && ischaralpha <= 'z') || (ischaralpha >= 'A' && ischaralpha <= 'Z');
	if (checkalpha)
		return (1);
	else
		return (0);
}

/**
 * @ischaralpha: the char to check
  * _delimiterseq - check character is delimeter
 * @delimitersh: the delimeter string
 */
int _delimiterseq(char ischaralpha, char *delimitersh)
{
	while (*delimitersh)
		if (*delimitersh++ == ischaralpha)
			return (1);
	return (0);
}

/**
 *_cyber - convert string to Integer
 *@sign: string to convert
 *Return: if no num in strings 0 else ..
 */
int _cyber(char *sign)
{
	int iterate, signular = 1, binary_flag = 0, binary_out;
	unsigned int numeric_compare = 0;

	for (iterate = 0;  sign[iterate] != '\0' && binary_flag != 2; iterate++)
	{
		if (sign[iterate] == '-')
			signular *= -1;

		if (sign[iterate] >= '0' && sign[iterate] <= '9')
		{
			binary_flag = 1;
			numeric_compare *= 10;
			numeric_compare += (sign[iterate] - '0');
		}
		else if (binary_flag == 1)
			binary_flag = 2;
	}

	if (signular == -1)
		binary_out = -numeric_compare;
	else
		binary_out = numeric_compare;

	return (binary_out);
}

/**
 * hc_interact - return true if shell = hc_interact mode
 * @information: struct address to point to memory
 *
 * Return: 1 if hc_interact mode, 0 otherwise
 */
int hc_interact(information_tree *information)
{
	int keeper = (isatty(STDIN_FILENO) && information->byte_reader <= 2);
	return (keeper);
}
