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
