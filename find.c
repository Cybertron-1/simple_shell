#include "libr.h"

/*find built*/
int built(information_tree *information, char *buffer, size_t *pin)
{
	size_t hind = *pin;

	if (buffer[hind] == '|' && buffer[hind + 1] == '|')
	{
		buffer[hind] = 0;
		hind++;
		information->cmd_buf_type = COMMANDLINE_ORILIZATION;
	}
	else if (buffer[hind] == '&' && buffer[hind + 1] == '&')
	{
		buffer[hind] = 0;
		hind++;
		information->cmd_buf_type = COMMAND_LINE_AND_OPERATOR;
	}
	else if (buffer[hind] == ';') /* found end of this command */
	{
		buffer[hind] = 0; /* replace semicolon with null */
		information->cmd_buf_type = COMMAND_LINE_CHAINING;
	}
	else
		return (0);
	*pin = hind;
	return (1);
}