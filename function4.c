#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * b_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int b_env(info_t *info)
{
    _plist(info->env);
    return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
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
        p = strstr(node->str, name);
        if (p == node->str && *(p + strlen(name)) == '=')
            return p + strlen(name) + 1;
        node = node->next;
    }
    return NULL;
}

/**
 * b_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int b_setenv(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (_setenv(info, info->argv[1], info->argv[2]) != 0)
        return (0);
    return (1);
}

/**
 * b_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int b_unsetenv(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= info->argc; i++)
        _unsetenv(info, info->argv[i]);

    return (0);
}

/**
 * add_env_vars - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int add_env_vars(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; env_var[i]; i++)
        add_node_end(&node, env_var[i], 0);
    info->env = node;
    return (0);
}
