#include "shell.h"

int shell(info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin_ret = 0;

    while (r != -1 && builtin_ret != -2)
    {
        reset_info(info);
        if (for_active(info))
            _puts("$ ");
        _eputchar(FLUSH);
        r = read_input(info);
        if (r != -1)
        {
            add_info(info, av);
            builtin_ret = check_builtin(info);
            if (builtin_ret == -1)
                check_cmd(info);
        }
        else if (for_active(info))
            _putchar('\n');
        free_buff(info, 0);
    }
    write_file(info);
    free_buff(info, 1);
    if (!for_active(info) && info->status)
        exit(info->status);
    if (builtin_ret == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }
    return builtin_ret;
}

int check_builtin(info_t *info)
{
    int i, built_in_ret = -1;
    builtin builtintbl[] = {
        {"exit", b_exit},
        {"env", b_env},
        {"help", b_help},
        {"history", b_history},
        {"setenv", b_setenv},
        {"unsetenv", b_unsetenv},
        {"cd", b_cd},
        {"alias", b_alias},
        {NULL, NULL}
    };

    for (i = 0; builtintbl[i].type; i++)
    {
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            built_in_ret = builtintbl[i].func(info);
            break;
        }
    }
    return built_in_ret;
}

void check_cmd(info_t *info)
{
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, k = 0; info->arg[i]; i++)
    {
        if (!delimit(info->arg[i], " \t\n"))
            k++;
    }
    if (!k)
        return;

    path = get_path(info, _getenv(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        fork_proc(info);
    }
    else
    {
        if ((for_active(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && find_cmd(info, info->argv[0]))
            fork_proc(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            _perror(info, "not found\n");
        }
    }
}

void fork_proc(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_env_vars(info)) == -1)
        {
            free_buff(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                _perror(info, "Permission denied\n");
        }
    }
}
