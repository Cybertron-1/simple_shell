#include "libr.h"

/**
 * collecthistory - grab the history file
 * @information: parameter struct
 * Return: realloc mem string containg history file
 */

char *collecthistory(information_tree *information)
{
	char *buffer_, *directory_get;

	directory_get = _grabenv(information, "HOME=");
	if (!directory_get)
		return (NULL);
	buffer_ = malloc(sizeof(char) * (_string_length(directory_get) + _string_length(HISTORY_FILE_ON_DISK) + 2));
	if (!buffer_)
		return (NULL);
	buffer_[0] = 0;
	_string_copy_custom1(buffer_, directory_get);
	_string_catenation(buffer_, "/");
	_string_catenation(buffer_, HISTORY_FILE_ON_DISK);
	return (buffer_);
}

/**
 * down_history - creates a file, or appends to an existing file
 * @information: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int down_history(information_tree *information)
{
	ssize_t find_data;
	char *filename = collecthistory(information);
	listings_tree *end_noc = NULL;

	if (!filename)
		return (-1);

	find_data = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (find_data == -1)
		return (-1);
	for (end_noc = information->history; end_noc; end_noc = end_noc->next)
	{
		_insertfd(end_noc->str, find_data);
		_insertfd1('\n', find_data);
	}
	_insertfd1(BUFFERMEM_FLASHER, find_data);
	close(find_data);
	return (1);
}

/**
 * file_read_history - reads history from file
 * @information: the parameter struct
 *
 * Return: historycounter on success, 0 otherwise
 */
int file_read_history(information_tree *information)
{
	int iteration, last = 0, line_counter = 0;
	ssize_t find_data, rdlen, find_size = 0;
	struct stat st;
	char *buffer_ = NULL, *filename = collecthistory(information);

	if (!filename)
		return (0);

	find_data = open(filename, O_RDONLY);
	free(filename);
	if (find_data == -1)
		return (0);
	if (!fstat(find_data, &st))
		find_size = st.st_size;
	if (find_size < 2)
		return (0);
	buffer_ = malloc(sizeof(char) * (find_size + 1));
	if (!buffer_)
		return (0);
	rdlen = read(find_data, buffer_, find_size);
	buffer_[find_size] = 0;
	if (rdlen <= 0)
		return (free(buffer_), 0);
	close(find_data);
	for (iteration = 0; iteration < find_size; iteration++)
		if (buffer_[iteration] == '\n')
		{
			buffer_[iteration] = 0;
			history_populate_list(information, buffer_ + last, line_counter++);
			last = iteration + 1;
		}
	if (last != iteration)
		history_populate_list(information, buffer_ + last, line_counter++);
	free(buffer_);
	information->historycounter = line_counter;
	while (information->historycounter-- >= HISTORY_MAXIMUM_LINES)
		remove_chasing_atindex(&(information->history), 0);
	historylist_reindexing(information);
	return (information->historycounter);
}

/**
 * history_populate_list - adds entry to a history linked list
 * @information: Structure containing potential arguments. Used to maintain
 * @buffer_: buffer
 * @line_counter: the history line_counter, historycounter
 *
 * Return: Always 0
 */
int history_populate_list(information_tree *information, char *buffer_, int line_counter)
{
	listings_tree *end_noc = NULL;

	if (information->history)
		end_noc = information->history;
	additional_endpoint_end(&end_noc, buffer_, line_counter);

	if (!information->history)
		information->history = end_noc;
	return (0);
}

/**
 * historylist_reindexing - renumbers the history linked list after changes
 * @information: Structure containing potential arguments. Used to maintain
 *
 * Return: the new historycounter
 */
int historylist_reindexing(information_tree *information)
{
	listings_tree *end_noc = information->history;
	int iteration = 0;

	while (end_noc)
	{
		end_noc->number = iteration++;
		end_noc = end_noc->next;
	}
	return (information->historycounter = iteration);
}
