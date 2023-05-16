#include "shell.h"
/**
* _myenv - prints the current environment
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int _myenv(info_t *info)
{
print_list_str(info->env);
return (0);
}

/**
* _mysetenv - Initialize a new environment variable,
* or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int _mysetenv(info_t *info)
{
if (info->argc != 3)
{
_eputs("Incorrect number of arguements\n");
return (1);
} if (_setenv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}
/**
* _myunsetenv - Remove an environment variable
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int _myunsetenv(info_t *info)
{
int i;
if (info->argc == 1)
{
_eputs("Too few arguements.\n");
return (1);
} for (
i
=
1; i
<= info->argc; i++)
_unsetenv(info, info->argv[i]);
return (0);
}

/**
* _unsetenv - Remove an environment variable
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: 1 on delete, 0 otherwise
* @var: the string env var property
*/
int _unsetenv(info_t *info, char *var)
{
        list_t *node = info->env;
        size_t i = 0;
        char *p;
        if (!node || !var)
                return (0);
                while (node)
                {
                        p = starts_with(node->str, var);
                        if (p && *p == '=')
                        {
                                info->env_changed = delete_node_at_index(&(info->env), i);
                                i = 0;
                                node = info->env;
                                continue;
                        }
                        node = node->next;
                        i++;
                }
                return (info->env_changed);
}
