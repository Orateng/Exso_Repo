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
/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096
extern char **environ;
/**
* struct liststr - singly linked list
* @num: the number field
* @str: a string
* @next: points to the next node
*/
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;
/**
* struct passinfo - contains pseudo-arguements to pass into a function,
* allowing uniform prototype for function pointer struct
* @arg: a string generated from getline containing arguements
* @argv:an array of strings generated from arg
* @path: a string path for the current command
* @argc: the argument count
* @line_count: the error count
* @err_num: the error code for exit()s
* @linecount_flag: if on count this line of input
* @fname: the program filename
* @env: linked list local copy of environ
* @environ: custom modified copy of environ from LL env
* @history: the history node
* @alias: the alias node
* @env_changed: on if environ was changed
* @status: the return status of the last exec'd command
* @cmd_buf: address of pointer to cmd_buf, on if chaining
* @cmd_buf_type: CMD_type ||, &&, ;
* @readfd: the fd from which to read line input
* @histcount: the history line number count
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
* struct builtin - contains a builtin string and related function
* @type: the builtin command flag
* @func: the function
*/
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* act1.c */
char *dup_chars(char *, int, int);
char *convert_number(long int, int, int);
int replace_vars(info_t *);
int interactive(info_t *);
void remove_comments(char *);
/* alias.c */
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int replace_alias(info_t *info);
int unset_alias(info_t *info, char *str);
/*  cox.c */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memset(char *s, char b, unsigned int n);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
char *starts_with(const char *haystack, const char *needle);
int _erratoi(char *s);
/* environ.c */
char *_getenv(info_t *info, const char *name);
char **get_environ(info_t *info);
int populate_env_list(info_t *info);
int _setenv(info_t *info, char *var, char *value);
/* find.c */
int find_builtin(info_t *info);
void find_cmd(info_t *info);
char *find_path(info_t *info, char *pathstr, char *cmd);
/* free.c */
int bfree(void **ptr);
void ffree(char **pp);
void free_list(list_t **head_ptr);
void free_info(info_t *info, int all);
/* getinfo.c */
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
/* hist.c */
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
char *get_history_file(info_t *info);
int write_history(info_t *info);
/* input.c */
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
int _putfd(char c, int fd);
/* istype.c */
int is_chain(info_t *info, char *buf, size_t *p);
int is_delim(char c, char *delim);
int is_cmd(info_t *info, char *path);
/* list1.c */
size_t print_list_str(const list_t *h);
size_t print_list_str(const list_t *h);
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
/*  loop.c */
void fork_cmd(info_t *info);
int hsh(info_t *info, char **av);
int _getline(info_t *info, char **ptr, size_t *length);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
void sigintHandler(__attribute__((unused))int sig_num);
/* myenv.c */
int _myenv(info_t *info);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int _unsetenv(info_t *info, char *var);
/* myfunc.c */
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);
int _myhistory(info_t *info);
int _myalias(info_t *info);
/* node1.c */
int delete_node_at_index(list_t **head, unsigned int index);
list_t *add_node_end(list_t **head, const char *str, int num);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);
/* print.c */
int print_d(int input, int fd);
void print_error(info_t *info, char *estr);
/* puts1.c */
void _eputs(char *str);
int _eputchar(char c);
void _puts(char *str);
int _putchar(char c);
int _putsfd(char *str, int fd);
/* str1.c */
int _strlen(char *s);
char *_strcat(char *dest, char *src);
char *_strdup(const char *str);
char *_strchr(char *s, char c);
int _strcmp(char *s1, char *s2);
/* str2.c */
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strcpy(char *dest, char *src);
char **strtow(char *str, char *d);

#endif
