#include "shell.h"

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*len)
    {
        free(*buf);
        *buf = NULL;
        signal(SIGINT, handle_sig);
        r = getline(buf, &len_p, stdin);
        if (r > 0)
        {
            if ((*buf)[r - 1] == '\n')
            {
                (*buf)[r - 1] = '\0';
                r--;
            }
            info->linecount_flag = 1;
            rm_comm(*buf);
            create_hist(info, *buf, info->histcount++);
            *len = r;
            info->cmd_buf = buf;
        }
    }
    return r;
}

ssize_t read_input(info_t *info)
{
    static char *buf = NULL;
    static size_t i = 0, j = 0, len = 0;
    ssize_t r = 0;
    char **buf_p = &(info->arg), *p = NULL;

    _putchar(FLUSH);
    r = input_buf(info, &buf, &len);
    if (r == -1)
        return -1;
    if (len)
    {
        j = i;
        p = buf + i;

        find_chain(info, buf, &j, i, len);
        while (j < len)
        {
            if (chain(info, buf, &j))
                break;
            j++;
        }

        i = j + 1;
        if (i >= len)
        {
            i = len = 0;
            info->cmd_buf_type = N_CMD;
        }

        *buf_p = p;
        return _strlen(p);
    }

    *buf_p = buf;
    return r;
}

void handle_sig(__attribute__((unused)) int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(FLUSH);
}
