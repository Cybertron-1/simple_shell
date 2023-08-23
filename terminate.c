#include "libr.h"

/**
 **_string_copy_custom - copy string to memory
 *@destination: the destination to be copued to in mem
 *@src: ource string
 *@n: char to copy int
 *Return: &&string returning
 */
char *_string_copy_custom(char *destination, char *src, int n)
{
	int iterate, iteratej;
	char *hello = destination;

	iterate = 0;
	while (src[iterate] != '\0' && iterate < n - 1)
	{
		destination[iterate] = src[iterate];
		iterate++;
	}
	if (iterate < n)
	{
		iteratej = iterate;
		while (iteratej < n)
		{
			destination[iteratej] = '\0';
			iteratej++;
		}
	}
	return (hello);
}

/**
 **_string_catentor -  add two Strings
 *@destination: 1st_string
 *@src: s2nd_string
 *@n: Max > string
 *Return: && string
 */
char *_string_catentor(char *destination, char *src, int n)
{
	int iterate, iteratej;
	char *hello = destination;

	iterate = 0;
	iteratej = 0;
	while (destination[iterate] != '\0')
		iterate++;
	while (src[iteratej] != '\0' && iteratej < n)
	{
		destination[iterate] = src[iteratej];
		iterate++;
		iteratej++;
	}
	if (iteratej < n)
		destination[iterate] = '\0';
	return (hello);
}



