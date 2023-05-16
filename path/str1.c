#include "shell.h"
/**
* _strlen - returns the length of a string
* @s: the string whose length to check
**
Return: integer length of string
*/
int _strlen(char *s)
{
int i = 0;
if (!s)
return (0);
while (*s++)
i++;
return (i);
}

/**
* _strcat - concatenates two strings
* @dest: the destination buffer
* @src: the source buffer
**
Return: pointer to destination buffer
*/
char *_strcat(char *dest, char *src)
{
char *ret = dest;
while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (ret);
}

/**
* _strdup - duplicates a string
* @str: the string to duplicate
**
Return: pointer to the duplicated string
*/
char *_strdup(const char *str)
{
int length = 0;
char *ret;
if (str == NULL)
return (NULL);
while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}

/**
**_strchr - locates a character in a string
*@s: the string to be parsed
*@c: the character to look for
*Return: (s) a pointer to the memory area s
*/
char *_strchr(char *s, char c)
{
        do
        {
                if (*s == c)
                        return (s);
        } while (*s++ != '\0');
        return (NULL);
}

/**
* _strcmp - performs lexicogarphic comparison of two strangs.
* @s1: the first strang
* @s2: the second strang
**
Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
*/
int _strcmp(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
return (*s1 - *s2);
s1++;
s2++;
} if (*s1 == *
s2)
return (0);
else
return (*s1 < *s2 ? -1 : 1);
}
