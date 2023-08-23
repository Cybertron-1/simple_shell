#include "libr.h"

/**
 * main: entry point of all programs lol
 * @acount: arg counter
 * @acountv: arg para vector
 * Return: good =1 else
 */
int main(int acount, char **acountv)
{
	information_tree information[] = { INFORMATION_INITER };
	int find_data = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (find_data)
		: "r" (find_data));
	if (acount == 2)
	{
		find_data = open(acountv[1], O_RDONLY);
		if (find_data == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_insertputschar(acountv[0]);
				_insertputschar(": 0: Can't open ");
				_insertputschar(acountv[1]);
				_insertcharacter('\n');
				_einsertcharacter(BUFFERMEM_FLASHER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		information->byte_reader = find_data;
	}
	initialize_environment(information);
	file_read_history(information);
	ghash(information, acountv);
	return (EXIT_SUCCESS);
}
