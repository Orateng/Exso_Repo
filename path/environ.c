#include "shell.h"

/**
* _getenv - gets the value of an environ variable
* @info: Structure containing potential arguments. Used to maintain
* @name: env var name
**
Return: the value
*/
char *_getenv(info_t *info, const char *name)
{
        list_t *node = info->env;
        char *p;
        while (node)
        {
                p = starts_with(node->str, name);
                if (p && *p)
                        return (p);
                        node = node->next;
        }
         return (NULL);
}

/**
* get_environ - returns the string array copy of our environ
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
char **get_environ(info_t *info)
{
        if (!info->environ || info->env_changed)
        {
                info->environ = list_to_strings(info->env);
                info->env_changed = 0;
        }
        return (info->environ);
}


/**
* populate_env_list - populates env linked list
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int populate_env_list(info_t *info)
{
        list_t *node = NULL;
        size_t i;
        for (i = 0; environ[i]; i++)
                add_node_end(&node, environ[i], 0);
                info->env = node;
        return (0);
}

/**
* _setenv - Initialize a new environment variable,
* or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* @var: the string env var property
* @value: the string env var value
* Return: Always 0
*/
int _setenv(info_t *info, char *var, char *value)
{
        char *buf = NULL;
        list_t *node;
        char *p;
        if (!var || !value)
                return (0);
        buf = malloc(_strlen(var) + _strlen(value) + 2);
        if (!buf)
                return (1);
                _strcpy(buf, var);
                _strcat(buf, "=");
                _strcat(buf, value);
                node = info->env;
                while (node)
		{
                        p = starts_with(node->str, var);
                        if (p && *p == '=')
                        {
                        free(node->str);
                        node->str = buf;
                        info->env_changed = 1;
                        return (0);
                        }
                        node = node->next;
                }
                add_node_end(&(info->env), buf, 0);
                free(buf);
                info->env_changed = 1;
                return (0);
}
