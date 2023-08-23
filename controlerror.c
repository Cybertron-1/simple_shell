#include "libr.h"

/**
 * _errorautocorrect - string -> int
 * @s: the string to be converted
 * Return: 0 if num in str else opposite
 */
int _errorautocorrect(char *s)
{
	int iterate = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (iterate = 0;  s[iterate] != '\0'; iterate++)
	{
		if (s[iterate] >= '0' && s[iterate] <= '9')
		{
			result *= 10;
			result += (s[iterate] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * output_error - output error
 * @information: the parameter & return information struct
 * @estr: string containing specified error function_type_s
 * Return: 0 if no numb in str else otherwise
 */
void output_error(information_tree *information, char *estr)
{
	_insertputschar(information->first_name);
	_insertputschar(": ");
	output_dato(information->getline_counter, STDERR_FILENO);
	_insertputschar(": ");
	_insertputschar(information->argv[0]);
	_insertputschar(": ");
	_insertputschar(estr);
}

/**
 * output_dato - foutput decimal in base 10 maths
 * @input: input
 * @fd: filedescriptor trep to
 *
 * Return: nnum of chars outputed
 */
int output_dato(int input, int fd)
{
	int (*__putchar)(char) = _insertcharacter;
	int iterate, counter = 0;
	unsigned int ups_, now;

	if (fd == STDERR_FILENO)
		__putchar = _einsertcharacter;
	if (input < 0)
	{
		ups_ = -input;
		__putchar('-');
		counter++;
	}
	else
		ups_ = input;
	now = ups_;
	for (iterate = 1000000000; iterate > 1; iterate /= 10)
	{
		if (ups_ / iterate)
		{
			__putchar('0' + now / iterate);
			counter++;
		}
		now %= iterate;
	}
	__putchar('0' + now);
	counter++;

	return (counter);
}

/**
 * transform_num - func convert
 * @num: number
 * @base: base in 10
 * @flags: args flags
 *
 * Return: string
 */
char *transform_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CHANGE_UNSIGNED_CHAR) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CHANGE_LOWERCASE_CHAR ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * dispose_comment - replace str
 * @buf: * = to address to perform changes
 * Return: Const 0;
 */
void dispose_comment(char *buf)
{
	int iterate;

	for (iterate = 0; buf[iterate] != '\0'; iterate++)
		if (buf[iterate] == '#' && (!iterate || buf[iterate - 1] == ' '))
		{
			buf[iterate] = '\0';
			break;
		}
}
