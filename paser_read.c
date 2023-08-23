#include "libr.h"

/**
 * _commandline - check commandline input is exe
 * @information: information struct
 * @get_path: get_path = file
 * Return: binary 1 true else otherway
 */
int _commandline(information_tree *information, char *get_path)
{
	struct stat end_;

	(void)information;
	if (!get_path || stat(get_path, &end_))
		return (0);
	if (end_.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _dump_characters - dul chara
 * @pathstr: the get_path 
 * @begin: index starting point
 * @end: sindex ending point
 * Return: pointer = *new buffer
 */
char *_dump_characters(char *pathstr, int begin, int end)
{
	static char buf[1024];
	int iterate = 0, calc = 0;

	for (calc = 0, iterate = begin; iterate < end; iterate++)
		if (pathstr[iterate] != ':')
			buf[calc++] = pathstr[iterate];
	buf[calc] = 0;
	return (buf);
}

/**
 * _get_path - ffgignmkdnfngngh
 * @information: the information struct
 * @pathstr: the get_path string
 * @command_line: the command_line to find
 *
 * Return: full get_path of command_line if found or NULL
 */
char *_get_path(information_tree *information, char *pathstr, char *command_line)
{
	int iterate = 0, current_position = 0;
	char *get_path;

	if (!pathstr)
		return (NULL);
	if ((_string_length(command_line) > 2) && _begins_withwhat(command_line, "./"))
	{
		if (_commandline(information, command_line))
			return (command_line);
	}
	while (1)
	{
		if (!pathstr[iterate] || pathstr[iterate] == ':')
		{
			get_path = _dump_characters(pathstr, current_position, iterate);
			if (!*get_path)
				_string_catenation(get_path, command_line);
			else
			{
				_string_catenation(get_path, "/");
				_string_catenation(get_path, command_line);
			}
			if (_commandline(information, get_path))
				return (get_path);
			if (!pathstr[iterate])
				break;
			current_position = iterate;
		}
		iterate++;
	}
	return (NULL);
}
