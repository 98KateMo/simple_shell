#include "shell.h"

/**
 * @find_file - will find file.
 */

char *find_file(info_t *info)
{
char *buf, *dir;

dir = _getenv(info, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_NAME) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
_strcpy(buf, dir);
_strcat(buf, "/");
_strcat(buf, HIST_NAME);
return (buf);
}

int write_file(info_t *info)
{
ssize_t fd;
char *filename = find_file(info);
list_t *node = NULL;

if (!filename)
return (-1);

fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = info->history; node; node = node->next)
{
_puts_fdesc(node->str, fd);
