#include "shell.h"

/**
* set_alias - sets alias to string
* @info: parameter struct
* @str: the string alias
**
Return: Always 0 on success, 1 on error
*/
int set_alias(info_t *info, char *str)
{
char *p;
p = _strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (unset_alias(info, str));
unset_alias(info, str);
return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
* print_alias - prints an alias string
* @node: the alias node
**
Return: Always 0 on success, 1 on error
*/
int print_alias(list_t *node)
{
char *p = NULL, *a = NULL;
if (node)
{
p = _strchr(node->str, '=');
for (a = node->str; a <= p; a++)
_putchar(*a);
_putchar('\'');
_puts(p + 1);
_puts("'\n");
return (0);
} return (
1);
}

/**
* replace_alias - replaces an aliases in the tokenized string
* @info: the parameter struct
**
Return: 1 if replaced, 0 otherwise
*/
int replace_alias(info_t *info)
{
int i;
list_t *node;
char *p;
for (i = 0; i < 10; i++)
{
node = node_starts_with(info->alias, info->argv[0], '=');
if (!node)
return (0);
free(info->argv[0]);
p = _strchr(node->str, '=');
if (!p)
return (0);
p = _strdup(p + 1);
if (!p)
return (0);
info->argv[0] = p;
} return (
1);
}

/**
* unset_alias - sets alias to string
* @info: parameter struct
* @str: the string alias
**
Return: Always 0 on success, 1 on error
*/
int unset_alias(info_t *info, char *str)
{
        char *p, c;
        int ret;
        p = _strchr(str, '=');
        if (!p)
                return (1);
        c = *p;
        *p = 0;
        ret = delete_node_at_index(&(info->alias),
        get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
        *p = c;
        return (ret);
}
