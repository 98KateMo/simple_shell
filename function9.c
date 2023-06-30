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
