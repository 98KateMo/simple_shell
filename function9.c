#include "shell.h"

/**
 * reset_info - initializes info_t struct
 * @info: struct address
 */
void reset_info(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * add_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void add_info(info_t *info, char **av)
{
    info->fname = av[0];
    if (info->arg)
    {
        info->argv = str_to_tok(info->arg, " \t");
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = _strdup(info->arg);
                info->argv[1] = NULL;
            }
        }
        info->argc = _str_array_len(info->argv);

        new_alias(info);
        new_vars(info);
    }
}

/**
 * free_buff - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_buff(info_t *info, int all)
{
    _free(info->argv);
    info->argv = NULL;
    info->path = NULL;
    if (all)
    {
        if (!info->cmd_buf)
            _free(info->arg);
        free_list(&(info->env));
        free_list(&(info->history));
        free_list(&(info->alias));
        _free(info->env_var);
        info->env_var = NULL;
        _free2((void **)info->cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        _putchar(FLUSH);
    }
}
