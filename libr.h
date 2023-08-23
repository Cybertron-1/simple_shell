#ifndef _SIMPLE_SHELL_PROC
#define _SIMPLE_SHELL_PROC

#include <sys/wait.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

/* For read/write buffers */
#define WRITE_BUFFER_SIZE 1024
#define BUFFERMEM_FLASHER -1
#define READ_BUFFER_SIZEOF 1024
#define COMMANDLINE_NORMILIZATION  0
#define COMMANDLINE_ORILIZATION    1
#define COMMAND_LINE_CHAINING      3
#define COMMAND_LINE_AND_OPERATOR  2
#define CHANGE_LOWERCASE_CHAR  1
#define CHANGE_UNSIGNED_CHAR   2
#define USE_GETLINE_BINARYCHECK 0
#define HISTORY_FILE_ON_DISK  ".simple_shell_history"
#define HISTORY_MAXIMUM_LINES 4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @number: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int call;
	int caller1;
    int number;
    char *str;
    struct liststr *next;
} listings_tree;

#define INFORMATION_INITER \
{ \
    NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0 \
}

/**
 * @arg: a string generated from getline containing arguments
 * @argv: Array of created arrays from string path
 * @path: real time string path check
 * @argc: tcount args
 * @getline_counter: count errors made
 * @error_number: generate error code
 * @getline_counter_flag: check count on line
 * @first_name: exe file name
 * @env: linakage of local copy
 * @environ: custom environ
 * @history: history nodatiin
 * @alias: alias nodation
 * @environ_changed: 1 if changed
 * @shell_status: get return last command
 * @commandline_buffer_unique: Address of pointer pointing tocommandline_buffer_unique
 * @cmd_buf_type: COMMANDLINE_type &&, ||, ;
 * @byte_reader: the line input read
 * @historycounter: history counting of numbers
 */
typedef struct pass_to_function
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int getline_counter;
    int error_number;
    int getline_counter_flag;
    char *first_name;
    listings_tree *env;
    listings_tree *history;
    listings_tree *alias;
    char **environ;
    int environ_changed;
    int shell_status;
    char **commandline_buffer_unique;
    int cmd_buf_type;
    int byte_reader;
    int historycounter;
} information_tree;

/**
 * struct STRING_BUL - contains a STRING_BUL string and related function
 * @function_type_s: STRING_BUL flag
 * @main_function: the function main step progran
 */
typedef struct STRING_BUL
{
    char *function_type_s;
    int (*main_function)(information_tree *);
	
} STRING_BUL_TABLE;

/* all functions definitions*/
int ghash(information_tree *, char **);
int get_builting(information_tree *);
void commandline_find(information_tree *);
void _hook_commandline(information_tree *);
int _commandline(information_tree *, char *);
char *_dump_characters(char *, int, int);
char *_get_path(information_tree *, char *, char *);
void _insertputschar(char *);
int _einsertcharacter(char);
int _insertfd1(char c, int fd);
int _insertfd(char *str, int fd);
int _string_length(char *);
int _string_compare(char *, char *);
char *_begins_withwhat(const char *, const char *);
char *_string_catenation(char *, char *);
char *_string_copy_custom1(char *, char *);
char *_string_dump(const char *);
void _inserts(char *);
int _insertcharacter(char);
char *_string_copy_custom(char *, char *, int);
char *_string_catentor(char *, char *, int);
char *_string_tcharacter(char *, char);
char **_string_tower_split(char *, char *);
char **_string_tower(char *, char);
char *_setup_memory(char *, char, unsigned int);
void _free_mallox(char **);
void *_mem_reallocator(void *, unsigned int, unsigned int);
int buffer_free(void **);
int hc_interact(information_tree *);
int _delimiterseq(char, char *);
int _checkalphanumeric(int);
int _cyber(char *);
int _errorautocorrect(char *);
void output_error(information_tree *, char *);
int output_dato(int, int);
char *transform_num(long int, int, int);
void dispose_comment(char *);
int _exit_command(information_tree *);
int _cd_command(information_tree *);
int _help_command(information_tree *);
int _personal_history(information_tree *);
int _personalalt(information_tree *);
ssize_t capture_input(information_tree *);
int _getline(information_tree *, char **, size_t *);
void signal_handle(int);
void clear_terminal(information_tree *);
void intialize_information(information_tree *, char **);
void release_information(information_tree *, int);
char *_grabenv(information_tree *, const char *);
int _personenv(information_tree *);
int _setupenviron(information_tree *);
int _freepersonalenviron(information_tree *);
int initialize_environment(information_tree *);
char **grab_environment(information_tree *);
int _releaseenviron(information_tree *, char *);
int _initializeenvironment(information_tree *, char *, char *);
char *collecthistory(information_tree *information);
int down_history(information_tree *information);
int file_read_history(information_tree *information);
int history_populate_list(information_tree *information, char *buf, int linecount);
int historylist_reindexing(information_tree *information);
listings_tree *additional_endpoint(listings_tree **, const char *, int);
listings_tree *additional_endpoint_end(listings_tree **, const char *, int);
size_t cough_out_chasing(const listings_tree *);
int remove_chasing_atindex(listings_tree **, unsigned int);
void allow_chasing(listings_tree **);
size_t listing_length(const listings_tree *);
char **convertlistings_tostrings(listings_tree *);
size_t output_listings(const listings_tree *);
listings_tree *starting_point(listings_tree *, char *, char);
ssize_t starting_point_index(listings_tree *, listings_tree *);
int chase_itself(information_tree *, char *, size_t *);
void verify_chase(information_tree *, char *, size_t *, size_t, size_t);
int change_alternative(information_tree *);
int exchange_var(information_tree *);
int exchange_string(char **, char *);

#endif
