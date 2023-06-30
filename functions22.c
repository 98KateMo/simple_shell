#include "shell.h"

int chain(info_t *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = '\0';
        j++;
        info->cmd_buf_type = O_CMD;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = '\0';
        j++;
        info->cmd_buf_type = A_CMD;
    }
    else if (buf[j] == ';')
    {
        buf[j] = '\0';
        info->cmd_buf_type = CHAIN_COMM;
    }
    else
        return 0;
    *p = j;
    return 1;
}

void find_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (info->cmd_buf_type == A_CMD)
    {
        if (info->status)
        {
            buf[i] = '\0';
            j = len;
        }
    }
    if (info->cmd_buf_type == O_CMD)
    {
        if (!info->status)
        {
            buf[i] = '\0';
            j = len;
        }
    }

    *p = j;
}

int new_alias(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = node_prefix(info->alias, info->argv[0], '=');
        if (!node)
            return 0;
        free(info->argv[0]);
        p = _strchr(node->str, '=');
        if (!p)
            return 0;
        p = _strdup(p + 1);
        if (!p)
            return 0;
        info->argv[0] = p;
    }
    return 1;
}

int new_vars(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        if (!_strcmp(info->argv[i], "$?"))
        {
            new_string(&(info->argv[i]), _strdup(conv_int(info->status, 10, 0)));
            continue;
        }
        if (!_strcmp(info->argv[i], "$$"))
        {
            new_string(&(info->argv[i]), _strdup(conv_int(getpid(), 10, 0)));
            continue;
        }
        node = node_prefix(info->env, &info->argv[i][1], '=');
        if (node)
        {
            new_string(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
            continue;
        }
        new_string(&info->argv[i], _strdup(""));
    }
    return 0;
}

int new_string(char **old, char *new)
{
    free(*old);
    *old = new;
    return 1;
}
