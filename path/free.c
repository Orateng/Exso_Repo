#include "shell.h"

/**
* bfree - frees a pointer and NULLs the address
* @ptr: address of the pointer to free
**
Return: 1 if freed, otherwise 0.
*/
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
* ffree - frees a string of strings
* @pp: string of strings
*/
void ffree(char **pp)
{
        char **a = pp;
        if (!pp)
                return;
                while (*pp)
                        free(*pp++);
                        free(a);
}

/**
* free_list - frees all nodes of a list
* @head_ptr: address of pointer to head node
**
Return: void
*/
void free_list(list_t **head_ptr)
{
        list_t *node, *next_node, *head;
        if (!head_ptr || !*head_ptr)
                return;
        head = *head_ptr;
        node = head;
        while (node)
        {
                next_node = node->next;
                free(node->str);
                free(node);
                node = next_node;
        }
        *head_ptr = NULL;
}

/**
* free_info - frees info_t struct fields
* @info: struct address
* @all: true if freeing all fields
*/
void free_info(info_t *info, int all)
{
        ffree(info->argv);
        info->argv = NULL;
        info->path = NULL;
        if (all)
        {
                if (!info->cmd_buf)
                        free(info->arg);
                if (info->env)
                        free_list(&(info->env));
                if (info->history)
                        free_list(&(info->history));
                if (info->alias)
                        free_list(&(info->alias));
                        ffree(info->environ);
                        info->environ = NULL;
                        bfree((void **)info->cmd_buf);
                if (info->readfd > 2)
                        close(info->readfd);
                        _putchar(BUF_FLUSH);
        }
}
