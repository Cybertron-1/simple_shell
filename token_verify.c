#include "libr.h"

/**
 * **_string_tower_split - split strs into words
 * @f_string: input str
 * @findd: the delimeter str
 * Return: a pointer
 */

char **_string_tower_split(char *f_string, char *findd)
{
	int iterate, jin, kil, get_m, get_numberwords = 0;
	char **set;

	if (f_string == NULL || f_string[0] == 0)
		return (NULL);
	if (!findd)
		findd = " ";
	for (iterate = 0; f_string[iterate] != '\0'; iterate++)
		if (!_delimiterseq(f_string[iterate], findd) && (_delimiterseq(f_string[iterate + 1], findd) || !f_string[iterate + 1]))
			get_numberwords++;

	if (get_numberwords == 0)
		return (NULL);
	set = malloc((1 + get_numberwords) * sizeof(char *));
	if (!set)
		return (NULL);
	for (iterate = 0, jin = 0; jin < get_numberwords; jin++)
	{
		while (_delimiterseq(f_string[iterate], findd))
			iterate++;
		kil = 0;
		while (!_delimiterseq(f_string[iterate + kil], findd) && f_string[iterate + kil])
			kil++;
		set[jin] = malloc((kil + 1) * sizeof(char));
		if (!set[jin])
		{
			for (kil = 0; kil < jin; kil++)
				free(set[kil]);
			free(set);
			return (NULL);
		}
		for (get_m = 0; get_m < kil; get_m++)
			set[jin][get_m] = f_string[iterate++];
		set[jin][get_m] = 0;
	}
	set[jin] = NULL;
	return (set);
}

/**
 * **_string_tower - splits str -> words
 * @f_string: the input string
 * @findd: delimet
 * Return: a pointer
 */
char **_string_tower(char *f_string, char findd)
{
	int iterate, jin, kil, get_m, get_numberwords = 0;
	char **set;

	if (f_string == NULL || f_string[0] == 0)
		return (NULL);
	for (iterate = 0; f_string[iterate] != '\0'; iterate++)
		if ((f_string[iterate] != findd && f_string[iterate + 1] == findd) ||
		    (f_string[iterate] != findd && !f_string[iterate + 1]) || f_string[iterate + 1] == findd)
			get_numberwords++;
	if (get_numberwords == 0)
		return (NULL);
	set = malloc((1 + get_numberwords) * sizeof(char *));
	if (!set)
		return (NULL);
	for (iterate = 0, jin = 0; jin < get_numberwords; jin++)
	{
		while (f_string[iterate] == findd && f_string[iterate] != findd)
			iterate++;
		kil = 0;
		while (f_string[iterate + kil] != findd && f_string[iterate + kil] && f_string[iterate + kil] != findd)
			kil++;
		set[jin] = malloc((kil + 1) * sizeof(char));
		if (!set[jin])
		{
			for (kil = 0; kil < jin; kil++)
				free(set[kil]);
			free(set);
			return (NULL);
		}
		for (get_m = 0; get_m < kil; get_m++)
			set[jin][get_m] = f_string[iterate++];
		set[jin][get_m] = 0;
	}
	set[jin] = NULL;
	return (set);
}

/**
 **_string_tcharacter - locates a character in a string
 *@hello: the string to be parsed
 *@c: the character to look for
 *Return: (hello) a pointer to the memory area hello
 */
char *_string_tcharacter(char *hello, char c)
{
	do {
		if (*hello == c)
			return (hello);
	} while (*hello++ != '\0');

	return (NULL);
}

