#include "libr.h"

/**
 * input_buf - buffers chained commands
 * @information: parameter struct
 * @buffer: address of buffer
 * @length_: address of length_ var
 *
 * Return: bytes read
 */
ssize_t input_buf(information_tree *information, char **buffer, size_t *length_)
{
	ssize_t recall = 0;
	size_t len_p = 0;

	if (!*length_)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, signal_handle);
#if USE_GETLINE_BINARYCHECK
		recall = getline(buffer, &len_p, stdin);
#else
		recall = _getline(information, buffer, &len_p);
#endif
		if (recall > 0)
		{
			if ((*buffer)[recall - 1] == '\n')
			{
				(*buffer)[recall - 1] = '\0';
				recall--;
			}
			information->getline_counter_flag = 1;
			dispose_comment(*buffer);
			history_populate_list(information, *buffer, information->historycounter++);
			{
				*length_ = recall;
				information->commandline_buffer_unique = buffer;
			}
		}
	}
	return (recall);
}

/**
 * capture_input - gets a line minus the newline
 * @information: parameter struct
 *
 * Return: bytes read
 */
ssize_t capture_input(information_tree *information)
{
	static char *buffer;
	static size_t iteratei, iteratej, length_;
	ssize_t recall = 0;
	char **buf_p = &(information->arg), *finalpointer;

	_insertcharacter(BUFFERMEM_FLASHER);
	recall = input_buf(information, &buffer, &length_);
	if (recall == -1)
		return (-1);
	if (length_)
	{
		iteratej = iteratei;
		finalpointer = buffer + iteratei;

		verify_chase(information, buffer, &iteratej, iteratei, length_);
		while (iteratej < length_)
		{
			if (chase_itself(information, buffer, &iteratej))
				break;
			iteratej++;
		}

		iteratei = iteratej + 1;
		if (iteratei >= length_)
		{
			iteratei = length_ = 0;
			information->cmd_buf_type = COMMANDLINE_NORMILIZATION;
		}

		*buf_p = finalpointer;
		return (_string_length(finalpointer));
	}

	*buf_p = buffer;
	return (recall); /* get length of buffer */
}

/**
 * read_buf - reads a buffer
 * @information: parameter struct
 * @buffer: buffer
 * @iteratei: size
 *
 * Return: recall
 */
ssize_t read_buf(information_tree *information, char *buffer, size_t *iteratei)
{
	ssize_t recall = 0;

	if (*iteratei)
		return (0);
	recall = read(information->byte_reader, buffer, READ_BUFFER_SIZEOF);
	if (recall >= 0)
		*iteratei = recall;
	return (recall);
}

/**
 * _getline - gets the next line of input from STDIN
 * @information: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(information_tree *information, char **ptr, size_t *length)
{
	static char buffer[READ_BUFFER_SIZEOF];
	static size_t iteratei, length_;
	size_t k;
	ssize_t recall = 0, s = 0;
	char *finalpointer = NULL, *new_p = NULL, *c;

	finalpointer = *ptr;
	if (finalpointer && length)
		s = *length;
	if (iteratei == length_)
		iteratei = length_ = 0;

	recall = read_buf(information, buffer, &length_);
	if (recall == -1 || (recall == 0 && length_ == 0))
		return (-1);

	c = _string_tcharacter(buffer + iteratei, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : length_;
	new_p = _mem_reallocator(finalpointer, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE CRASH HMM! */
		return (finalpointer ? free(finalpointer), -1 : -1);

	if (s)
		_string_catentor(new_p, buffer + iteratei, k - iteratei);
	else
		_string_copy_custom(new_p, buffer + iteratei, k - iteratei + 1);

	s += k - iteratei;
	iteratei = k;
	finalpointer = new_p;

	if (length)
		*length = s;
	*ptr = finalpointer;
	return (s);
}

/**
 * signal_handle - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void signal_handle(__attribute__((unused))int sig_num)
{
	_inserts("\n");
	_inserts("$ ");
	_insertcharacter(BUFFERMEM_FLASHER);
}

