#include "shell.h"
char **get_env_vars(info_t *info)
{
    if (!info->env_var || info->env_changed)
    {
        info->env_var = list_str(info->env);
        info->env_changed = 0;
    }

    return (info->env_var);
}
int _unsetenv(info_t *info, char *var)
{
    list_t *node = info->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return (0);

    while (node)
    {
        p = _strchr(node->str, '=');
        if (p && _strcmp(p + 1, var) == 0)
        {
            info->env_changed = rm_node(&(info->env), i);
            i = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        i++;
    }
    return (info->env_changed);
}

int _setenv(info_t *info, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;

if (!var || !value)
return (0);

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);
 _strcpy(buf, var);
 _strcat(buf, "=");
 _strcat(buf, value);
 node = info->env;
 while (node)
 {
 p = _strchr(node->str, '=');
 if (p && _strcmp(p + 1, var) == 0)
 {
 free(node->str);
 node->str = buf;
 info->env_changed = 1;
 return (0);
 }
 node = node->next;
 }
 add_node_end(&(info->env), buf, 0);
 free(buf);
 info->env_changed = 1;
 return (0);
}

