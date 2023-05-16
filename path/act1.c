#include "shell.h"

/**
* dup_chars - duplicates characters
* @pathstr: the PATH string
* @start: starting index
* @stop: stopping index
**
Return: pointer to new buffer
*/
char *dup_chars(char *pathstr, int start, int stop)
{
        static char buf[1024];
        int i = 0, k = 0;
        for (k = 0, i = start; i < stop; i++)
                if (pathstr[i] != ':')
                        buf[k++] = pathstr[i];
                        buf[k] = 0;
                        return (buf);
}

/**
* convert_number - converter function, a clone of itoa
* @num: number
* @base: base
* @flags: argument flags
**
Return: string
*/
char *convert_number(long int num, int base, int flags)
{
        static char *array;
        static char buffer[50];
        char sign = 0;
        char *ptr;
        unsigned long n = num;
        if (!(flags & CONVERT_UNSIGNED) && num < 0)
        {
                n = -num;
                sign = '-';
        }
        array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" :
        "0123456789ABCDEF";
        ptr = &buffer[49];
        *ptr = '\0';
        do
        {
                *--ptr = array[n % base];
                n /= base;
        } while (n != 0);
        if (sign)
                *--ptr = sign;
        return (ptr);
}

/**
* replace_vars - replaces vars in the tokenized string
* @info: the parameter struct
**
Return: 1 if replaced, 0 otherwise
*/
int replace_vars(info_t *info)
{
int i = 0;
list_t *node;
for (i = 0; info->argv[i]; i++)
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
continue;
if (!_strcmp(info->argv[i], "$?"))
{
replace_string(&(info->argv[i]),
_strdup(convert_number(info->status, 10, 0)));
continue;
} 
if (!_strcmp(info->argv[i], "$$"))
{
replace_string(&(info->argv[i]),
_strdup(convert_number(getpid(), 10, 0)));
continue;
}
node = node_starts_with(info->env, &info->argv[i][1], '=');
if (node)
{
replace_string(&(info->argv[i]),
_strdup(_strchr(node->str, '=') + 1));
continue;
} replace_string(&info->argv[i], _strdup(""));
}
return (0);
}

/**
* replace_string - replaces string
* @old: address of old string
* @new: new string
**
Return: 1 if replaced, 0 otherwise
*/
int replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}

/**
* interactive - returns true if shell is interactive mode
* @info: struct address
**
Return: 1 if interactive mode, 0 otherwise
*/
int interactive(info_t *info)
{
        return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* remove_comments - function replaces first instance of '#' with '\0'
* @buf: address of the string to modify
**
Return: Always 0;
*/
void remove_comments(char *buf)
{
        int i;
        for (i = 0; buf[i] != '\0'; i++)
                if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
                {
                        buf[i] = '\0';
                        break;
                }
}
