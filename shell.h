#ifndef _SHELL_H_
#define _SHELL_H_

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
#define READ_BUFFER 1024
#define WRITE_BUFFER 1024
#define FLUSH -1
#define N_CMD 0
#define O_CMD		1
#define A_CMD		2
#define CHAIN_COMM	3
#define TO_LOWER	1
#define TO_UNSIGNED	2
#define GETLINE_FUNC 0
#define HIST_NAME	".simple_shell_history"
#define MAX_BYTES_HIST	4096
extern char **env_var;
/**
 * struct str_list - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct str_list
{
	int num;
	char *str;
	struct str_list *next;
} list_t;

/**
 *struct send_info - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of env_var
 *@env_var: custom modified copy of env_var from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if env_var was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct send_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **env_var;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;
#define INFO_VARS \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}
/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin;
int shell(info_t *, char **);
int check_builtin(info_t *);
void check_cmd(info_t *);
void fork_proc(info_t *);
int find_cmd(info_t *, char *);
char *copy_char(char *, int, int);
char *get_path(info_t *, char *, char *);
void _eputs(char *);
int _eputchar(char);
int _put_fdesc(char c, int fd);
int _puts_fdesc(char *str, int fd);
int _strlen(char *);
int _strcmp(char *, char *);
char *prefix_c(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **str_to_tok(char *, char *);
char **str_to_tok2(char *, char);
char *_memset(char *, char, unsigned int);
void _free(char **);
void *_realloc(void *, unsigned int, unsigned int);
int _free2(void **);
int for_active(info_t *);
int delimit(char, char *);
int _isalpha(int);
int _atoi(char *);
int err_no(char *);
void _perror(info_t *, char *);
int _dprint(int, int);
char *conv_int(long int, int, int);
void rm_comm(char *);
int b_exit(info_t *);
int b_cd(info_t *);
int b_help(info_t *);
int b_history(info_t *);
int b_alias(info_t *);
ssize_t read_input(info_t *);
int _getline(info_t *, char **, size_t *);
void handle_sig(int);
void reset_info(info_t *);
void add_info(info_t *, char **);
void free_buff(info_t *, int);
char *_getenv(info_t *, const char *);
int b_env(info_t *);
int b_setenv(info_t *);
int b_unsetenv(info_t *);
int add_env_vars(info_t *);
char **get_env_vars(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char *find_file(info_t *info);
int write_file(info_t *info);
int read_file(info_t *info);
int create_hist(info_t *info, char *buf, int linecount);
int renumber_file(info_t *info);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t _plist(const list_t *);
int rm_node(list_t **, unsigned int);
void free_list(list_t **);
size_t count_elements(const list_t *);
char **list_str(list_t *);
size_t print_list(const list_t *);
list_t *node_prefix(list_t *, char *, char);
ssize_t get_index(list_t *, list_t *);
int chain(info_t *, char *, size_t *);
void find_chain(info_t *, char *, size_t *, size_t, size_t)
int new_alias(info_t *);
int new_vars(info_t *);
int new_string(char **, char *);

#endif
