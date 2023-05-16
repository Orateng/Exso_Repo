#include "shell.h"

ssize_t read_buf(info_t *info, char *buf, size_t *i);

/**
* fork_cmd - forks a an exec thread to run cmd
* @info: the parameter & return info struct
**
Return: void
*/
void fork_cmd(info_t *info)
{
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
} if (
child_pid == 0)
{
if (execve(info->path, info->argv, get_environ(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
/* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}

/**
* hsh - main shell loop
* @info: the parameter & return info struct
* @av: the argument vector from main()
**
Return: 0 on success, 1 on error, or error code
*/
int hsh(info_t *info, char **av)
{
        ssize_t r = 0;
        int builtin_ret = 0;
        while (r != -1 && builtin_ret != -2)
        {
                clear_info(info);
                if (interactive(info))
                        _puts("$ ");
                        _eputchar(BUF_FLUSH);
                r = get_input(info);
                if (r != -1)
                {
                        set_info(info, av);
                        builtin_ret = find_builtin(info);
                        if (builtin_ret == -1)
                                find_cmd(info);
                }
                else if (interactive(info))
                        _putchar('\n');
                        free_info(info, 0);
        }
        write_history(info);
        free_info(info, 1);
        if (!interactive(info) && info->status)
                exit(info->status);
        if (builtin_ret == -2)
        {
                if (info->err_num == -1)
                        exit(info->status);
                        exit(info->err_num);
        }
        return (builtin_ret);
}

/**
* _getline - gets the next line of input from STDIN
* @info: parameter struct
* @ptr: address of pointer to buffer, preallocated or NULL
* @length: size of preallocated ptr buffer if not NULL
**
Return: s
*/
int _getline(info_t *info, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;
p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;
r = read_buf(info, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);
c = _strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _realloc(p, s, s ? s + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);
if (s)
_strncat(new_p, buf + i, k - i);
else
_strncpy(new_p, buf + i, k - i + 1);
s += k - i;
i = k;
p = new_p;
if (length)
*length = s;
*ptr = p;
return (s);
}

/**
* read_buf - reads a buffer
* @info: parameter struct
* @buf: buffer
* @i: size
**
Return: r
*/
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
        ssize_t r = 0;
        if (*i)
                return (0);
        r = read(info->readfd, buf, READ_BUF_SIZE);
        if (r >= 0)
                *i = r;
        return (r);
}

/**
* sigintHandler - blocks ctrl-C
* @sig_num: the signal number
**
Return: void
*/
void sigintHandler(__attribute__((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
