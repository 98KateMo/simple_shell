#include "shell.h"
#include <unistd.h>

void _eputs(char *str)
{
if (str != NULL)
write(2, str, _strlen(str));
}

int _eputchar(char c)
{
	return (write(2, &c, 1));
}
int _put_fdesc(char c, int fd)
{
return (write(fd, &c, 1));
}

int _puts_fdesc(char *str, int fd)
{
if (str != NULL)
return (write(fd, str, _strlen(str)));
return (0);
}

