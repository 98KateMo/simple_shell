#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
void reset_info(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

void add_info(info_t *info, char **av)
{
    int i = 0;

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
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        new_alias(info);
        new_vars(info);
    }
}

void free_buff(info_t *info, int all)
{
    _free(info->argv);
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
        _free(info->env_var);
        info->env_var = NULL;
        _free2((void **)info->cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        _putchar(FLUSH);
    }
}
