#include "main.h"
/**
 * tokenize - creates array of tokens based on user string
 * @buffer: pointer to user string
 *
 * Return: pointer to array of user strings
 */
char **tokenize(char *buffer)
{
        char *token = NULL;
        int i = 0, wordcount = 0;
        char *delimiter = " \n";
        char **av = NULL;

        wordcount = _splitstring(buffer);
        if (!wordcount)
                return (NULL);
        av = malloc((wordcount + 1) * sizeof(char *));
        if (av == NULL)
                exit(1);
        token = strtok(buffer, delimiter);
        while (token != NULL)
        {
                av[i] = _strdup(token);
                token = strtok(NULL, delimiter);
                i++;
        }
        av[i] = NULL;
        return (av);
}

/**
 * _splitstring - counts number of words in string
 * @str: pointer to string to count
 *
 * Return: number of words in string
 */
int _splitstring(char *str)
{
        int i, searchflag = 1, wordcount = 0;

        for (i = 0; str[i]; i++)
        {
                if (str[i] != ' ' && searchflag == 1)
                {
                        wordcount += 1;
                        searchflag = 0;
                }
                if (str[i + 1] == ' ')
                        searchflag = 1;
        }
        return (wordcount);
}

/**
 * _getenv - gets PATH member from environ
 * @name: pointer to PATH string
 *
 * Return: pointer to PATH member string or NULL if not found
 */
char *_getenv(const char *name)
{
        int i, result;

        for (i = 0; environ[i]; i++)
        {
                result = _PATHstrcmp(name, environ[i]);
                if (result == 0)
                {
                        return (environ[i]);
                }
        }
        return (NULL);
}

/**
 * _PATHstrcmp - compares PATH with environ to find PATH value
 * @s1: pointer PATH string
 * @s2: pointer to environ string with actual value
 *
 * Return: 0 on success
 */
int _PATHstrcmp(const char *s1, const char *s2)
{
        int i;

        for (i = 0; s2[i] != '='; i++)
        {
                if (s1[i] != s2[i])
                        return (-1);
        }
        return (0);
}
