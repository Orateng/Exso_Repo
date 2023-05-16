#include "shell.h"


/**
* _realloc - reallocates a block of memory
* @ptr: pointer to previous malloc'ated block
* @old_size: byte size of previous block
* @new_size: byte size of new block
**
Return: pointer to da ol'block nameen.
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
        char *p;
        if (!ptr)
                return (malloc(new_size));
        if (!new_size)
                return (free(ptr), NULL);
        if (new_size == old_size)
                return (ptr);
        p = malloc(new_size);
        if (!p)
                return (NULL);
        old_size = old_size < new_size ? old_size : new_size;
        while (old_size--)
                p[old_size] = ((char *)ptr)[old_size];
                free(ptr);
        return (p);
}

/**
* _memset - fills memory with a constant byte
* @s: the pointer to the memory area
* @b: the byte to fill *s with
* @n: the amount of bytes to be filled
* Return: (s) a pointer to the memory area s
*/
char *_memset(char *s, char b, unsigned int n)
{
unsigned int i;
for (i = 0; i < n; i++)
s[i] = b;
return (s);
}

/**
* check_chain - checks we should continue chaining based on last status
* @info: the parameter struct
* @buf: the char buffer
* @p: address of current position in buf
* @i: starting position in buf
* @len: length of buf
**
Return: Void
*/
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;
if (info->cmd_buf_type == CMD_AND)
{
if (info->status)
{
buf[i] = 0;
j = len;
}
} if (
info->cmd_buf_type == CMD_OR)
{
if (!info->status)
{
buf[i] = 0;
j = len;
}
}
*p = j;
}

/**
* starts_with - checks if needle starts with haystack
* @haystack: string to search
* @needle: the substring to find
**
Return: address of next char of haystack or NULL
*/
char *starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}

/**
* _erratoi - converts a string to an integer
* @s: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
* -1 on error
*/
int _erratoi(char *s)
{
        int i = 0;
        unsigned long int result = 0;
        if (*s == '+')
                s++; /* TODO: why does this make main return 255? */
                for (i = 0; s[i] != '\0'; i++)
                {
                        if (s[i] >= '0' && s[i] <= '9')
                        {
                                result *= 10;
                                result += (s[i] - '0');
                                if (result > INT_MAX)
                                        return (-1);
                        }
                        else
                                return (-1);
                }
                 return (result);
}
