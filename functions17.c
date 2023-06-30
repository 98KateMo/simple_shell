#include "shell.h"

char *_memset(char *s, char b, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
    {
        s[i] = b;
    }
    return s;
}

void _free(char **pp)
{
    char **a = pp;

    if (!pp)
        return;

    while (*pp)
    {
        free(*pp);
        pp++;
    }
    free(a);
}

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *p;

    if (!ptr)
        return malloc(new_size);
    if (!new_size)
    {
        free(ptr);
        return NULL;
    }
    if (new_size == old_size)
        return ptr;

    p = malloc(new_size);
    if (!p)
        return NULL;

    if (old_size < new_size)
        new_size = old_size;

    while (new_size--)
    {
        p[new_size] = ((char *)ptr)[new_size];
    }

    free(ptr);
    return p;
}
