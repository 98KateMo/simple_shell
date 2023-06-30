#include "shell.h"

int for_active(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

int delimit(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return 1;
		delim++;
	}
	return 0;
}
