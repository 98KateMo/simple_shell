#include "shell.h"
#include <stdlib.h>

/**
 * b_env - prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int b_env(info_t *info)
{
    list_t *node = info->env;

    while (node != NULL)
    {
        /* Use allowed I/O function to print environment variable */
        _puts(node->str);
        _putchar('\n');
        node = node->next;
    }

    return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @info: Structure containing potential arguments.
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *p;

    while (node)
    {
        p = prefix_c(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }

    return (NULL);
}

/**
 * b_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int b_setenv(info_t *info)
{
    if (info->argc != 3)
    {
        /* Use allowed I/O function for printing error message */
        _eputs("Incorrect number of arguments\n");
        return (1);
    }

    if (setenv(info->argv[1], info->argv[2], 1) == -1)
    {
        /* Use allowed I/O function for printing error message */
        _eputs("Failed to set environment variable\n");
        return (1);
    }

    return (0);
}

/**
 * b_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int b_unsetenv(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        /* Use allowed I/O function for printing error message */
        _eputs("Too few arguments.\n");
        return (1);
    }

    for (i = 1; i < info->argc; i++)
    {
        unsetenv(info->argv[i]);
    }

    return (0);
}

/**
 * add_env_vars - populates env linked list
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int add_env_vars(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
    {
        add_node_end(&node, environ[i], 0);
    }

    info->env = node;
    return (0);
}
