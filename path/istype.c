#include "shell.h"

/**
* is_chain - test if current char in buffer is a chain delimeter
* @info: the parameter struct
* @buf: the char buffer
* @p: address of current position in buf
**
Return: 1 if chain delimeter, 0 otherwise
*/
int is_chain(info_t *info, char *buf, size_t *p)
{
size_t j = *p;
if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
info->cmd_buf_type = CMD_OR;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
info->cmd_buf_type = CMD_AND;
}
else if (buf[j] == ';') /* found end of this command */
{
buf[j] = 0; /* replace semicolon with null */
info->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*p = j;
return (1);
}

/**
* is_delim - checks if character is a delimeter
* @c: the char to check
* @delim: the delimeter string
* Return: 1 if true, 0 if false
*/
int is_delim(char c, char *delim)
{
while (*delim)
if (*delim++ == c)
return (1);
return (0);
}

/**
* is_cmd - determines if a file is an executable command
* @info: the info struct
* @path: path to the file
**
Return: 1 if true, 0 otherwise
*/
int is_cmd(info_t *info, char *path)
{
struct stat st;
(void)info;
if (!path || stat(path, &st))
return (0);
if (st.st_mode & S_IFREG)
{
return (1);
} return (
0);
}
