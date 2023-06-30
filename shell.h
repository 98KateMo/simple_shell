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
int shell(info_t *var, char **str);
int check_builtin(info_t *var);
void check_cmd(info_t *var);
void fork_proc(info_t *var);
int find_cmd(info_t *var, char *str);
char *copy_char(char *str, int n, int i);
char *get_path(info_t *var, char *str, char *str2);
void _eputs(char *str);
int _eputchar(char c);
int _put_fdesc(char c, int fd);
int _puts_fdesc(char *str, int fd);
int _strlen(char *str);
int _strcmp(char *str, char *str2);
char *prefix_c(const char *str, const char *str2);
char *_strcat(char *str, char *str2);
char *_strcpy(char *str, char *str2);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);
char *_strncpy(char *str, char *str2, int n);
char *_strncat(char *str, char *str2, int n);
char *_strchr(char *str, char c);
char **str_to_tok(char *str, char *str2);
char **str_to_tok2(char *str, char c);
char *_memset(char *str, char c, unsigned int n);
void _free(char **str);
void *_realloc(void *var, unsigned int n, unsigned int i);
int _free2(void **str);
int for_active(info_t *var);
int delimit(char n, char *str);
int _isalpha(int n);
int _atoi(char *str);
int err_no(char *str);
void _perror(info_t *var, char *str);
int _dprint(int n, int i);
char *conv_int(long int n, int i, int j);
void rm_comm(char *str);
int b_exit(info_t *var);
int b_cd(info_t *var);
int b_help(info_t *var);
int b_history(info_t *var);
int b_alias(info_t *var);
ssize_t read_input(info_t *var);
int _getline(info_t *var, char **arr, size_t *n);
void handle_sig(int n);
void reset_info(info_t *var);
void add_info(info_t *var, char **arr);
void free_buff(info_t *var, int n);
char *_getenv(info_t *var, const char *str);
int b_env(info_t *var);
int b_setenv(info_t *var);
int b_unsetenv(info_t *var);
int add_env_vars(info_t *var);
char **get_env_vars(info_t *var);
int _unsetenv(info_t *var, char *str);
int _setenv(info_t *var, char *str, char *str2);
char *find_file(info_t *info);
int write_file(info_t *info);
int read_file(info_t *info);
int create_hist(info_t *info, char *buf, int linecount);
int renumber_file(info_t *info);
list_t *add_node(list_t **var, const char *str, int n);
list_t *add_node_end(list_t **var, const char *str, int n);
size_t _plist(const list_t *var);
int rm_node(list_t **var, unsigned int n);
void free_list(list_t **var);
size_t count_elements(const list_t *var);
char **list_str(list_t *var);
size_t print_list(const list_t *var);
list_t *node_prefix(list_t *var, char *str, char c);
ssize_t get_index(list_t *var, list_t *n);
int chain(info_t *var, char *str, size_t *n);
void find_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int new_alias(info_t *var);
int new_vars(info_t *var);
int new_string(char **arr, char *str);
#endif
