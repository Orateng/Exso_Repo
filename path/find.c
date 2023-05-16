#include "shell.h"

/**
* find_builtin - finds a builtin command
* @info: the parameter & return info struct
**
Return: -1 if builtin not found,
* 0 if builtin executed successfully,
* 1 if builtin found but not successful,
* 2 if builtin signals exit()
*/
int find_builtin(info_t *info)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", _myexit},
{"env", _myenv},
{"help", _myhelp},
{"history", _myhistory},
{"setenv", _mysetenv},
{"unsetenv", _myunsetenv},
{"cd", _mycd},
{"alias", _myalias},
{NULL, NULL}
};
for (i = 0; builtintbl[i].type; i++)
if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
built_in_ret = builtintbl[i].func(info);
break;
}
return (built_in_ret);
}

/**
* find_cmd - finds a command in PATH
* @info: the parameter & return info struct
**
Return: void
*/
void find_cmd(info_t *info)
{
char *path = NULL;
int i, k;
info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
} for (i = 0, k = 0; info->arg[i]; i++)
if (!is_delim(info->arg[i], " \t\n"))
k++;
if (!k)
return;
path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
fork_cmd(info);
}
else
{
if ((interactive(info) || _getenv(info, "PATH=")
|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
fork_cmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
print_error(info, "not found\n");
}
}
}

/**
* find_path - finds this cmd in the PATH string
* @info: the info struct
* @pathstr: the PATH string
* @cmd: the cmd to find
**
Return: full path of cmd if found or NULL
*/
char *find_path(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;
if (!pathstr)
return (NULL);
if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_cmd(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = dup_chars(pathstr, curr_pos, i);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
} if (
is_cmd(info, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
} i++;
} return (
NULL);
}
