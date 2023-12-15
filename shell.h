#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define CMD_NORM  0
#define CMD_AND   2
#define CMD_OR    1
#define CMD_CHAIN 3
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED  2
#define USE_GETLINE 0
#define USE_STRTOK  0
#define HIST_FILE  ".simple_shell_history"
#define HIST_MAX  4096

extern char **environ;

/**
 * struct liststr - singly linked list.
 * @num: The number filed.
 * @str: String.
 * @next: Pointer to the next node.
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} lista_t;

/**
 * struct passinfo - Contains pseudo-arguments to pass into a function.
 * @arg: The string generated from getline containing arguments.
 * @argv: AN array of strings generated from arg.
 * @path: A string path for the current command.
 * @argc: The argument count.
 * @line_count: The error count.
 * @err_num: The error code for the exit()s.
 * @linecount_flag: if on count this line of input.
 * @fname: The programm file name.
 * @env: Linked list local copy of environ.
 * @environ: custom modified copy of environ from LL env.
 * @history: The history node.
 * @alias: The alias node.
 * @env_changed: on if environ was changed.
 * @status: the return status of the last exec'd command.
 * @cmd_buf: address of pointer to cmd_buf, on if changing.
 * @cmd_buf_type: CMD_TYPE ||, &&, ;
 * @readfd: The fd from which to read line input.
 * @histcount: The history line number count.
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	lista_t *env;
	lista_t *history;
	lista_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} infa_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - Contains a builtin string and related function.
 * @type: The builtin command flag.
 * @func: THe function.
 */

typedef struct builtin
{
	char *type;
	int (*func)(infa_t *);
} builtin_tab;

int _strlen(char *);
char *_strcpy(char *, char *);
int _strcmp(char *, char *);
char *_strdup(const char *);
char *begin_with(const char *, const char *);
char *_strcat(char *, char *);
char **strtow(char *, char *);
void _puts(char *);
char *_strchr(char *, char);
int _putchar(char);
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char **strtow2(char *, char);
int _eputchar(char);
int _putfd(char c, int fd);
void _eputs(char *);
int _putsfd(char *str, int fd);
size_t print_list(const lista_t *);
lista_t *add_node(lista_t **, const char *, int);
ssize_t get_node_index(lista_t *, lista_t *);
lista_t *add_node_end(lista_t **, const char *, int);
lista_t *node_begin_with(lista_t *, char *, char);
char **list_to_strings(lista_t *);
size_t print_list_str(const lista_t *);
void free_list(lista_t **);
size_t list_len(const lista_t *);
int delete_node_at_index(lista_t **, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);
int bfree(void **);
char *_memset(char *, char, unsigned int);
int _myhistory(infa_t *);
int _mycd(infa_t *);
int _myexit(infa_t *);
int _myhelp(infa_t *);
int _myalias(infa_t *);
int find_builtin(infa_t *);
char *_getenv(infa_t *, const char *);
int _mysetenv(infa_t *);
int _setenv(infa_t *, char *, char *);
int _myenv(infa_t *);
char **get_environ(infa_t *);
int _myunsetenv(infa_t *);
int _unsetenv(infa_t *, char *);
int populate_env_list(infa_t *);
void find_cmd(infa_t *);
int hsh(infa_t *, char **);
void fork_cmd(infa_t *);
char *find_path(infa_t *, char *, char *);
int is_cmd(infa_t *, char *);
char *dup_chars(char *, int, int);
int loophsh(char **);
int _erratoi(char *);
int _isalpha(int);
int _atoi(char *);
int is_delim(char, char *);
int interactive(infa_t *);
int print_d(int, int);
void remove_comments(char *);
char *convert_number(long int, int, int);
void set_info(infa_t *, char **);
void print_error(infa_t *, char *);
void free_info(infa_t *, int);
void clear_info(infa_t *);
int _getline(infa_t *, char **, size_t *);
ssize_t get_input(infa_t *);
void sigintHandler(int);
char *get_history_file(infa_t *infa);
int replace_vars(infa_t *);
int renumber_history(infa_t *infa);
int read_history(infa_t *infa);
int write_history(infa_t *infa);
int replace_alias(infa_t *);
int build_history_list(infa_t *infa, char *buf, int linecount);
void check_chain(infa_t *, char *, size_t *, size_t, size_t);
int replace_string(char **, char *);
int is_chain(infa_t *, char *, size_t *);

#endif
