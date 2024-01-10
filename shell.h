#ifndef SHELL_H
#define SHELL_H

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststring - singly linked list
 * @n: the number field
 * @s: a string
 * @next: points to the next node
 */
typedef struct liststring
{
	int n;
	char *s;
	struct liststr *next;
} list_t;

/**
 *struct passinformation - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinformation
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
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
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
} builtin_table;


/* hsh.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* path.c */
int _is_cmd(info_t *, char *);
char *_dup_ch(char *, int, int);
char *_get_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* error_func.c */
void put_e(char *);
int put_echar(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

/* string_func1.c */
int string_length(char *);
int string_compare(char *, char *);
char *start_with(const char *, const char *);
char *string_cat(char *, char *);

/* string_func2.c */
char *string_copy(char *, char *);
char *string_dup(const char *);
void put_str(char *);
int put_char(char);

/* string_func3.c */
char *str_copy(char *, char *, int);
char *str_cat(char *, char *, int);
char *string_ch(char *, char);

/* string_func4.c */
char **string_tow(char *, char *);
char **string_tow2(char *, char);

/* memory_func1.c */
char *memory_set(char *, char, unsigned int);
void str_free(char **);
void *real_loc(void *, unsigned int, unsigned int);

/* memory_func2.c */
int _free(void **);

/* m_func1.c */
int _inactive(info_t *);
int is_delimeter(char, char *);
int is_alphabet(int);
int strtoi(char *);

/* more_func2.c */
int _stoi(char *);
void print_err(info_t *, char *);
int print_dec(int, int);
char *convert_num(long int, int, int);
void comments_remove(char *);

/* emulators1.c */
int _exity(info_t *);
int _cdy(info_t *);
int _helpy(info_t *);

/* emulators2.c */
int _historyy(info_t *);
int _aliasy(info_t *);
int _unset_alias(info_t *, char *);
int _set_alias(info_t *, char *);
int _alias_print(list_t *);

/* getline.c module */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* information.c module */
void clear_information(info_t *);
void set_information(info_t *, char **);
void free_information(info_t *, int);

/* environment.c module */
char *_getenvy(info_t *, const char *);
int _envy(info_t *);
int _setenvy(info_t *);
int _unsetenvy(info_t *);
int envy_list(info_t *);

/* environment2.c module */
char **get_env(info_t *);
int _unset_env(info_t *, char *);
int _set_env(info_t *, char *, char *);

/* io_func.c */
char *get_history(info_t *info);
int _history_write(info_t *info);
int _history_read(info_t *info);
int _history_list(info_t *info, char *buf, int linecount);
int _history_renumber(info_t *info);

/* list_string1.c module */
list_t *node_add(list_t **, const char *, int);
list_t *end_add(list_t **, const char *, int);
size_t print_strlist(const list_t *);
int node_delete(list_t **, unsigned int);
void list_free(list_t **);

/* list_string2.c module */
size_t list_length(const list_t *);
char **strings_of_list(list_t *);
size_t list_print(const list_t *);
list_t *node_start(list_t *, char *, char);
ssize_t node_index(list_t *, list_t *);

/* chain.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int reiplace_vars(info_t *);
int replace_string(char **, char *);

#endif
